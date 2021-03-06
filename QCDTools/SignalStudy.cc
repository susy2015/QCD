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
#include "TInterpreter.h"

#include "SusyAnaTools/Tools/samples.h"
#include "SusyAnaTools/Tools/searchBins.h"

#include "SignalStudy.h"

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"Please give 1 argument " << "inputFileName " << std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./SignalStudy root://cmseos.fnal.gov//store/user/lpcsusyhad/Spring15_74X_Oct_2015_Ntp_v2X/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/QCD_HT500to700_Spring15DR74_Asympt25ns_Ntp_v2/150928_140039/0000/stopFlatNtuples_1.root" << std::endl;
    return -1;
  }
  std::string input_str(argv[1]);
  std::string trim;

  std::string output_str;
  //here is a little bit tricky when dealing with the slash... need to improve
  //for all the MC samples
  //std::string tag = input_str.substr(find_Nth(input_str,10,"/") + 1,find_Nth(input_str,11,"/")-find_Nth(input_str,10,"/")-1);
  //for all the data samples
  //std::string tag = input_str.substr(find_Nth(input_str,9,"/") + 1,find_Nth(input_str,10,"/")-find_Nth(input_str,9,"/")-1);
  std::string tag = input_str.substr(find_Nth(input_str,10,"/") + 1,find_Nth(input_str,11,"/")-find_Nth(input_str,10,"/")-1);
  //std::string tag = input_str.substr(find_Nth(input_str,11,"/") + 1,find_Nth(input_str,12,"/")-find_Nth(input_str,11,"/")-1);
  std::size_t idpos = input_str.find("stopFlatNtuples");
  std::string fileid = input_str.substr (idpos);

  output_str = "SignalStudy_" + tag + "_" + fileid;
  //output_str = "SignalStudy_Test.root";
  std::cout << "Output File Name: " << output_str << std::endl;

  TChain *originalTree = new TChain("stopTreeMaker/AUX");
  originalTree->Add(input_str.c_str());
  originalTree->SetBranchStatus("*", 1);

  TFile* output = new TFile((output_str).c_str(), "RECREATE");
  TDirectory *mydict = output->mkdir("stopTreeMaker");
  mydict->cd();
  TTree* selectedTree = new TTree("QCDTFTree","QCDTFTree");
  Double_t met, genmet, allgenmet, sNugenmet, sNuNufromTopWgenmet, sNuNufromTopBgenmet, sNuNuOthergenmet;
  selectedTree->Branch("met",&met,"met/D");
  selectedTree->Branch("genmet",&genmet,"genmet/D");
  selectedTree->Branch("allgenmet",&allgenmet,"allgenmet/D");
  selectedTree->Branch("sNugenmet",&sNugenmet,"sNugenmet/D");
  selectedTree->Branch("sNuNufromTopWgenmet",&sNuNufromTopWgenmet,"sNuNufromTopWgenmet/D");
  selectedTree->Branch("sNuNufromTopBgenmet",&sNuNufromTopBgenmet,"sNuNufromTopBgenmet/D");
  selectedTree->Branch("sNuNuOthergenmet",&sNuNuOthergenmet,"sNuNuOthergenmet/D");

  //LSP and mediator mass for SUS Signal
  Double_t SusyMotherMass, SusyLSPMass;
  selectedTree->Branch("SusyMotherMass",&SusyMotherMass,"SusyMotherMass/D");
  selectedTree->Branch("SusyLSPMass"   ,&SusyLSPMass   ,"SusyLSPMass/D");

  Bool_t ifAllHadTop;
  selectedTree->Branch("ifAllHadTop",&ifAllHadTop,"ifAllHadTop/O");

  std::shared_ptr<topTagger::type3TopTagger>type3Ptr(nullptr);
  NTupleReader *tr=0;
  //initialize the type3Ptr defined in the customize.h
  AnaFunctions::prepareForNtupleReader();
  tr = new NTupleReader(originalTree, AnaConsts::activatedBranchNames);
  const std::string spec = "lostlept";
  BaselineVessel *myBaselineVessel = 0;
  myBaselineVessel = new BaselineVessel(*tr, spec, "fastsim");
  if( !useNewTagger ){ myBaselineVessel->SetupTopTagger(false, "Legacy_TopTagger.cfg" ); }
  else
  {
    if( useLegacycfg ){ myBaselineVessel->SetupTopTagger(true, "Legacy_TopTagger.cfg" ); }
    else{ myBaselineVessel->SetupTopTagger(true, "TopTagger.cfg" ); }
  }
  //The passBaseline is registered here
  tr->registerFunction(*myBaselineVessel);

  while(tr->getNextEvent())
  {
    bool passLeptVeto = tr->getVar<bool>("passLeptVeto"+spec);
    //bool passnJets = tr->getVar<bool>("passnJets"+spec);
    //bool passMET = tr->getVar<bool>("passMET"+spec);
    //bool passHT = tr->getVar<bool>("passHT"+spec);
    //bool passMT2 = tr->getVar<bool>("passMT2"+spec);
    //bool passTagger = tr->getVar<bool>("passTagger"+spec);
    //bool passBJets = tr->getVar<bool>("passBJets"+spec);
    //bool passNoiseEventFilter = tr->getVar<bool>("passNoiseEventFilter"+spec);
    //bool passQCDHighMETFilter = tr->getVar<bool>("passQCDHighMETFilter"+spec);
    //bool passdPhis = tr->getVar<bool>("passdPhis"+spec);
    bool passSSTrimAndSlim = tr->getVar<bool>("passBaseline"+spec);
    //bool passSSTrimAndSlim = true;
    //passSSTrimAndSlim = ( met > 200)
    //            && passnJets
    //            && passHT
    //            && passMT2
    //            && passTagger
    //            && passBJets
    //            && passNoiseEventFilter;
    if(passSSTrimAndSlim && passLeptVeto)
    {
      met = tr->getVar<double>("met");
      genmet = tr->getVar<double>("genmet");

      std::vector<TLorentzVector> sNuLVec = tr->getVec<TLorentzVector>("sNuLVec");
      std::vector<TLorentzVector> NuFromTopBLVec = tr->getVec<TLorentzVector>("NuFromTopBLVec");
      std::vector<TLorentzVector> NuFromTopWLVec = tr->getVec<TLorentzVector>("NuFromTopWLVec");
      std::vector<TLorentzVector> NuOtherLVec = tr->getVec<TLorentzVector>("NuOtherLVec");

      std::vector<TLorentzVector> allLVec = sNuLVec;
      allLVec.insert(allLVec.end(), NuFromTopBLVec.begin(), NuFromTopBLVec.end());
      allLVec.insert(allLVec.end(), NuFromTopWLVec.begin(), NuFromTopWLVec.end());
      allLVec.insert(allLVec.end(), NuOtherLVec.begin(), NuOtherLVec.end());
      
      std::vector<TLorentzVector> sNuNufromTopWLVec = sNuLVec;
      sNuNufromTopWLVec.insert(sNuNufromTopWLVec.end(), NuFromTopWLVec.begin(), NuFromTopWLVec.end());
      //std::cout << NuFromTopBLVec.size() << std::endl;
      std::vector<TLorentzVector> sNuNufromTopBLVec = sNuLVec;
      sNuNufromTopBLVec.insert(sNuNufromTopBLVec.end(), NuFromTopBLVec.begin(), NuFromTopBLVec.end());

      std::vector<TLorentzVector> sNuNuOtherLVec = sNuLVec;
      sNuNuOtherLVec.insert(sNuNuOtherLVec.end(), NuOtherLVec.begin(), NuOtherLVec.end());

      allgenmet = GetPartonGenMET(allLVec);
      sNugenmet = GetPartonGenMET(sNuLVec);
      sNuNufromTopWgenmet = GetPartonGenMET(sNuNufromTopWLVec);
      sNuNufromTopBgenmet = GetPartonGenMET(sNuNufromTopBLVec);
      sNuNuOthergenmet = GetPartonGenMET(sNuNuOtherLVec);

      SusyMotherMass = tr->getVar<double>("SusyMotherMass");
      SusyLSPMass    = tr->getVar<double>("SusyLSPMass");
 
      std::vector<int> W_emuVec = tr->getVec<int>("W_emuVec");
      std::vector<int> W_tau_emuVec = tr->getVec<int>("W_tau_emuVec");
      std::vector<int> W_tauVec = tr->getVec<int>("W_tauVec");
      ifAllHadTop = (W_emuVec.size()==0) && (W_tau_emuVec.size()==0) && (W_tauVec.size()==0);

      //if(ifAllHadTop && NuFromTopWLVec.size()!=0){ std::cout << tr->getVar<unsigned int>("run") <<":" << tr->getVar<unsigned int>("lumi") << ":" << tr->getVar<unsigned long long int>("event") << std::endl; }
      if(ifAllHadTop && NuOtherLVec.size()!=0){ std::cout << tr->getVar<unsigned int>("run") <<":" << tr->getVar<unsigned int>("lumi") << ":" << tr->getVar<unsigned long long int>("event") << std::endl; }

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
