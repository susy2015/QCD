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

#include "JetResponse.h"

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"Please give 1 argument " << "inputFileName " << std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./JetResponse root://cmseos.fnal.gov//store/user/lpcsusyhad/Spring15_74X_Oct_2015_Ntp_v2X/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/QCD_HT500to700_Spring15DR74_Asympt25ns_Ntp_v2/150928_140039/0000/stopFlatNtuples_1.root" << std::endl;
    return -1;
  }
  std::string input_str(argv[1]);

  TChain *originalTree = new TChain("stopTreeMaker/AUX");
  originalTree->Add(input_str.c_str());
  
  /* 
  TFile* output = new TFile((output_str).c_str(), "RECREATE");
  TDirectory *mydict = output->mkdir("stopTreeMaker");
  mydict->cd();
  TTree* selectedTree = originalTree->CloneTree(0);
  */

  //const std::string spec = "QCD";
  //myBaselineVessel = new BaselineVessel(spec);

  //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
  NTupleReader tr(originalTree);
  //initialize the type3Ptr defined in the customize.h
  //AnaFunctions::prepareTopTagger();
  //The passBaseline is registered here
  //tr.registerFunction(&mypassBaselineFunc);

  while(tr.getNextEvent())
  {
    //MET information if needed
    //double met = tr.getVar<double>("met");
    //reco Jet
    std::vector<TLorentzVector> jetsLVec = tr.getVec<TLorentzVector>("jetsLVec");
    //Gen Jet information
    std::vector<TLorentzVector> selGenParticle = tr.getVec<TLorentzVector>("selGenParticle");
    int selPDGid = tr.getVar<int>("selPDGid");

  }

  return 0;
}
