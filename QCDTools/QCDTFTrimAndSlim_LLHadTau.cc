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
    std::cerr <<"./QCDTFTrimAndSlim_LLHadTau root://cmseos.fnal.gov//store/user/lpcsusyhad/Spring15_74X_Feb_2016_Ntp_v6X_forMoriond/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Spring15_74X_Feb_2016_Ntp_v6p0_forMoriond_TTJets_SingleLeptFromT/160213_195624/0000/stopFlatNtuples_2.root" << std::endl;
    return -1;
  }
  std::string input_str(argv[1]);
  std::string trim;
  //std::string outputpath = "/eos/uscms/store/group/lpcsusyhad/hua/Skimmed_2015Nov15/";

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
  Int_t njets30,njets50; Double_t ht;
  selectedTree->Branch("nJets30",&njets30,"nJets30/I");
  selectedTree->Branch("nJets50",&njets50,"nJets50/I");
  selectedTree->Branch("ht",&ht,"ht/D");
  //Boolean related to the baseline
  Bool_t passTagger,passBJets,passQCDHighMETFilter,passdPhis;
  selectedTree->Branch("passTagger"          ,&passTagger          ,"passTagger/O");
  selectedTree->Branch("passBJets"           ,&passBJets           ,"passBJets/O");
  selectedTree->Branch("passQCDHighMETFilter",&passQCDHighMETFilter,"passQCDHighMETFilter/O");
  selectedTree->Branch("passdPhis"           ,&passdPhis           ,"passdPhis/O");
  //LL information for TTJets Wjets and singleTop
  Bool_t isLL;
  selectedTree->Branch("isLL",&isLL,"isLL/O");

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
    bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter"+spec);
    //bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter"+spec);
    //bool passdPhis = tr.getVar<bool>("passdPhis"+spec);
 
    bool passQCDTFTrimAndSlim = ( met > 175)
                             && passLeptVeto
                             && passnJets
                             && passHT
                             && passMT2
                             //&& passTagger
                             //&& passBJets
                             && passNoiseEventFilter;
    
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
      //double mht = tr.getVar<double>("mht"); 
      passTagger = tr.getVar<bool>("passTagger"+spec);
      passBJets = tr.getVar<bool>("passBJets"+spec);
      passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter"+spec);
      passdPhis = tr.getVar<bool>("passdPhis"+spec);

      //determine if LL or HadTau. be careful! we need to set passLeptVeto first
      std::vector<int> W_emuVec = tr.getVec<int>("W_emuVec");
      std::vector<int> W_tau_emuVec = tr.getVec<int>("W_tau_emuVec");
      std::vector<int> emuVec_merge;
      emuVec_merge.reserve( W_emuVec.size() + W_tau_emuVec.size() );
      emuVec_merge.insert( emuVec_merge.end(), W_emuVec.begin(), W_emuVec.end() );
      emuVec_merge.insert( emuVec_merge.end(), W_tau_emuVec.begin(), W_tau_emuVec.end() );
      int gen_emus_count = emuVec_merge.size();
      (gen_emus_count>0 && passLeptVeto) ? isLL = true : isLL =false;

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