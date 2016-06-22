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

#include "QCDTFTrimAndSlim.h"

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
  std::string trim;
  //std::string outputpath = "/eos/uscms/store/group/lpcsusyhad/hua/Skimmed_2015Nov15/";
  
  //gSystem->Load("libPhysics.so");

  std::string output_str;
  //here is a little bit tricky when dealing with the slash... need to improve
  //for all the data samples and ttbar leptonic MC samples
  std::string tag = input_str.substr(find_Nth(input_str,9,"/") + 1,find_Nth(input_str,10,"/")-find_Nth(input_str,9,"/")-1);
  std::size_t idpos = input_str.find("stopFlatNtuples");
  std::string fileid = input_str.substr (idpos);

  output_str = "QCDTFTrimAndSlim_" + tag + fileid;
  std::cout << "Output File Name: " << output_str << std::endl;

  TChain *originalTree = new TChain("stopTreeMaker/AUX");
  originalTree->Add(input_str.c_str());
  //originalTree->SetBranchStatus("*", 1);
   
  TFile* output = new TFile((output_str).c_str(), "RECREATE");
  TDirectory *mydict = output->mkdir("stopTreeMaker");
  mydict->cd();
  TTree* selectedTree = new TTree("QCDTFTree","QCDTFTree");
  //TTree* selectedTree = originalTree->CloneTree(0);
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
  //selectedTree->SetBranchAddress("jetsLVec",&jetsLVec);
  selectedTree->Branch("jetsLVec","std::vector<TLorentzVector>",&jetsLVec);
  //Boolean related to the baseline
  Bool_t passTagger,passBJets,passQCDHighMETFilter,passdPhis,passNoiseEventFilter;
  selectedTree->Branch("passTagger"          ,&passTagger          ,"passTagger/O");
  selectedTree->Branch("passBJets"           ,&passBJets           ,"passBJets/O");
  selectedTree->Branch("passQCDHighMETFilter",&passQCDHighMETFilter,"passQCDHighMETFilter/O");
  selectedTree->Branch("passdPhis"           ,&passdPhis           ,"passdPhis/O");
  selectedTree->Branch("passNoiseEventFilter",&passNoiseEventFilter,"passNoiseEventFilter/O");
  //calo MET and calo MET phi to get rid of trash in QCD
  Double_t calomet, calometphi;
  selectedTree->Branch("calomet"   ,&calomet   ,"calomet/D");
  selectedTree->Branch("calometphi",&calometphi,"calometphi/D");

  const std::string spec = "QCD";
  myBaselineVessel = new BaselineVessel(spec);

  //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
  NTupleReader tr(originalTree);
  //initialize the type3Ptr defined in the customize.h
  AnaFunctions::prepareTopTagger();
  //The passBaseline is registered here
  tr.registerFunction(&mypassBaselineFunc);

  while(tr.getNextEvent())
  {
    met = tr.getVar<double>("met");
    bool passLeptVeto = tr.getVar<bool>("passLeptVeto"+spec);
    bool passnJets = tr.getVar<bool>("passnJets"+spec);
    bool passHT = tr.getVar<bool>("passHT"+spec);
    bool passMT2 = tr.getVar<bool>("passMT2"+spec);
    //bool passTagger = tr.getVar<bool>("passTagger"+spec);
    //bool passBJets = tr.getVar<bool>("passBJets"+spec);
    //bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter"+spec);
    //bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter"+spec);
    //bool passdPhis = tr.getVar<bool>("passdPhis"+spec);
 
    bool passQCDTFTrimAndSlim = ( met > 175)
                             && passLeptVeto
                             && passnJets
                             && passHT
                             && passMT2;
                             //&& passTagger
                             //&& passBJets
                             //&& passNoiseEventFilter;
    jetsLVec.clear();
    if(passQCDTFTrimAndSlim)
    {
      //searchbin variables
      //met = tr.getVar<double>("met");
      mt2 = tr.getVar<double>("best_had_brJet_MT2"+spec);       
      ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      nbotjets = tr.getVar<int>("cntCSVS"+spec);
      //AUX variables
      njets30 = tr.getVar<int>("cntNJetsPt30Eta24"+spec);
      njets50 = tr.getVar<int>("cntNJetsPt50Eta24"+spec);
      ht = tr.getVar<double>("HT"+spec);
      TLorentzVector mht_TLV = AnaFunctions::calcMHT(tr.getVec<TLorentzVector>("jetsLVec"), AnaConsts::pt30Eta24Arr);
      mht = mht_TLV.Pt(); 
      metphi = tr.getVar<double>("metphi");
      mhtphi = mht_TLV.Phi();
      jetsLVec = tr.getVec<TLorentzVector>("jetsLVec");
      passTagger = tr.getVar<bool>("passTagger"+spec);
      passBJets = tr.getVar<bool>("passBJets"+spec);
      passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter"+spec);
      passdPhis = tr.getVar<bool>("passdPhis"+spec);
      passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter"+spec);
      calomet = tr.getVar<double>("calomet");
      calometphi = tr.getVar<double>("calometphi");

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
