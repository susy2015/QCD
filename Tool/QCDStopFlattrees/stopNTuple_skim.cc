#include <string>
#include <iostream>
#include <vector>

#include "TFile.h"
#include "TChain.h"
//#include "TH1.h"
//#include "TH2.h"
//#include "TProfile.h"
//#include "TRandom.h"
#include "TDirectory.h"
#include "TTree.h"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr <<"Please give 2 arguments " << "inputFileName " << " " << "outputFileName"<< std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./a.out stopFlatNtuples_1.root skimmedtree_1.root" << std::endl;
    return -1;
  }
  const char *inputFileName  = argv[1];
  const char *outputFileName = argv[2];

  TFile* input = TFile::Open(inputFileName);
  //TChain *chainDATA = new TChain("/stopTreeMaker/AUX");
  TTree* originalTree = (TTree*)input->Get("/stopTreeMaker/AUX");
  //TFile* output = TFile::Open(outputFileName,"RECREATE");

  TFile* output = new TFile(outputFileName, "RECREATE");
  TDirectory *mydict = output->mkdir("stopTreeMaker");
  mydict->cd();
  TTree* selectedTree = originalTree->CopyTree("met>200.");

  selectedTree->Write();
  output->Close();

  return 0;
}

