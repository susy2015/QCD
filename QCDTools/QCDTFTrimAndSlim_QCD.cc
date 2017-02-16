#include <fstream>
#include <map>
#include <iomanip>
#include <locale>
#include <sstream>
#include <stdlib.h>

#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TInterpreter.h"

#include "SusyAnaTools/Tools/samples.h"
#include "SusyAnaTools/Tools/searchBins.h"

#include "QCDTFTrimAndSlimCommon.h"

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"Please give 1 argument " << "inputFileName " << std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./QCDTFTrimAndSlim_QCD root://cmseos.fnal.gov//store/user/lpcsusyhad/Spring16_80X_Jun_2016_Ntp_v5X/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Spring16_80X_Jun_2016_Ntp_v5p0_QCD_HT2000toInf_ext1/160609_112453/0000/stopFlatNtuples_105.root" << std::endl;
    return -1;
  }
  std::string input_str(argv[1]);
  std::string output_str = QCDOutputFileNameGenerator(input_str,false);

  TChain *originalTree = new TChain("stopTreeMaker/AUX");
  originalTree->Add(input_str.c_str());
   
  TFile* output = new TFile((output_str).c_str(), "RECREATE");
  TDirectory *mydict = output->mkdir("stopTreeMaker"); mydict->cd();
  TTree* selectedTree = new TTree("QCDTFTree","QCDTFTree");
  
  //search bin variables
  Double_t met,mt2; Int_t ntopjets,nbotjets;
  selectedTree->Branch("met",&met,"met/D");
  selectedTree->Branch("mt2",&mt2,"mt2/D");
  selectedTree->Branch("nTop",&ntopjets,"nTop/I");
  selectedTree->Branch("nBot",&nbotjets,"nBot/I");
  //AUX variables maybe useful for research
  Int_t njets30,njets50; Double_t ht,mht;
  selectedTree->Branch("nJets30",&njets30,"nJets30/I");
  selectedTree->Branch("nJets50",&njets50,"nJets50/I");
  selectedTree->Branch("ht",&ht,"ht/D");
  selectedTree->Branch("mht",&mht,"mht/D");
  Double_t metphi, mhtphi;
  selectedTree->Branch("metphi",&metphi,"metphi/D");
  selectedTree->Branch("mhtphi",&mhtphi,"mhtphi/D");
  std::vector<TLorentzVector> jetsLVec;
  selectedTree->Branch("jetsLVec","std::vector<TLorentzVector>",&jetsLVec);
  Int_t nmus,nels;
  selectedTree->Branch("nMuons"    ,&nmus,"nMuons/I"    );
  selectedTree->Branch("nElectrons",&nels,"nElectrons/I");
  //Boolean related to the baseline
  Bool_t passLeptVeto, passTagger,passBJets,passQCDHighMETFilter,passdPhis,passNoiseEventFilter;
  selectedTree->Branch("passLeptVeto"        ,&passLeptVeto        ,"passLeptVeto/O");
  selectedTree->Branch("passTagger"          ,&passTagger          ,"passTagger/O");
  selectedTree->Branch("passBJets"           ,&passBJets           ,"passBJets/O");
  selectedTree->Branch("passQCDHighMETFilter",&passQCDHighMETFilter,"passQCDHighMETFilter/O");
  selectedTree->Branch("passdPhis"           ,&passdPhis           ,"passdPhis/O");
  selectedTree->Branch("passNoiseEventFilter",&passNoiseEventFilter,"passNoiseEventFilter/O");
  //Correction factors
  Double_t ISRCorr,BTagCorr;
  selectedTree->Branch("ISRCorr",&ISRCorr,"ISRCorr/D");
  selectedTree->Branch("BTagCorr",&BTagCorr,"BTagCorr/D");
  //calo MET and calo MET phi to get rid of trash in QCD
  Double_t calomet, calometphi;
  selectedTree->Branch("calomet"   ,&calomet   ,"calomet/D");
  selectedTree->Branch("calometphi",&calometphi,"calometphi/D");

  std::shared_ptr<topTagger::type3TopTagger>type3Ptr(nullptr);
  NTupleReader *tr=0;
  //initialize the type3Ptr defined in the customize.h
  AnaFunctions::prepareForNtupleReader();
  tr = new NTupleReader(originalTree, AnaConsts::activatedBranchNames);
  const std::string spec = "lostlept";
  BaselineVessel *myBaselineVessel = 0;
  myBaselineVessel = new BaselineVessel(*tr, spec);
  if( !useNewTagger ){ myBaselineVessel->SetupTopTagger(false, "Legacy_TopTagger.cfg" ); }
  else
  {
    if( useLegacycfg ){ myBaselineVessel->SetupTopTagger(true, "Legacy_TopTagger.cfg" ); }
    else{ myBaselineVessel->SetupTopTagger(true, "TopTagger.cfg" ); }
  }
  //The passBaseline is registered here
  tr->registerFunction(*myBaselineVessel);
  
  ISRReWeightingSet(*tr,output_str);
  BTagReWeightingSet(*tr,output_str);

  while(tr->getNextEvent())
  {
    met = tr->getVar<double>("met");
    bool passnJets = tr->getVar<bool>("passnJets"+spec);
    bool passHT = tr->getVar<bool>("passHT"+spec);
    bool passMT2 = tr->getVar<bool>("passMT2"+spec);
    bool passQCDTFTrimAndSlim = ( met > trigger_turn_on_met)
                             && passnJets
                             && passHT
                             && passMT2;
    jetsLVec.clear();
    if(passQCDTFTrimAndSlim)
    {
      //searchbin variables
      mt2 = tr->getVar<double>("best_had_brJet_MT2"+spec);       
      ntopjets = tr->getVar<int>("nTopCandSortedCnt"+spec);
      nbotjets = tr->getVar<int>("cntCSVS"+spec);
      //AUX variables
      njets30 = tr->getVar<int>("cntNJetsPt30Eta24"+spec);
      njets50 = tr->getVar<int>("cntNJetsPt50Eta24"+spec);
      ht = tr->getVar<double>("HT"+spec);
      TLorentzVector mht_TLV = AnaFunctions::calcMHT(tr->getVec<TLorentzVector>("jetsLVec"), AnaConsts::pt30Eta24Arr);
      mht = mht_TLV.Pt(); 
      metphi = tr->getVar<double>("metphi");
      mhtphi = mht_TLV.Phi();
      jetsLVec = tr->getVec<TLorentzVector>("jetsLVec");
      nmus = tr->getVar<int>("nMuons_CUT"+spec);
      nels = tr->getVar<int>("nElectrons_CUT"+spec);
      passLeptVeto = tr->getVar<bool>("passLeptVeto"+spec);
      passTagger = tr->getVar<bool>("passTagger"+spec);
      passBJets = tr->getVar<bool>("passBJets"+spec);
      passQCDHighMETFilter = tr->getVar<bool>("passQCDHighMETFilter"+spec);
      passdPhis = tr->getVar<bool>("passdPhis"+spec);
      passNoiseEventFilter = tr->getVar<bool>("passNoiseEventFilter"+spec);
      ISRCorr = tr->getVar<double>("isr_Unc_Cent");
      BTagCorr = tr->getVar<double>("bTagSF_EventWeightSimple_Central");
      calomet = tr->getVar<double>("calomet");
      calometphi = tr->getVar<double>("calometphi");

      selectedTree->Fill();
    }
    else continue;
  }
  selectedTree->Write();
  output->Write(); 
  output->Close();

  if (originalTree) delete originalTree;

  std::string d = "root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15";
  std::system(("xrdcp " + output_str + " " + d).c_str());
  std::system(("rm " + output_str).c_str());

  return 0;
}
