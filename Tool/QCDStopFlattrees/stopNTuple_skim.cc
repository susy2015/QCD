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
  if (argc < 1)
  {
    std::cerr <<"Please give 1 argument " << "inputFileName " << std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./ stopFlatNtuples_1.root" << std::endl;
    return -1;
  }
  std::string input_str(argv[1]); 
  std::string trim;
  std::string output_str;

  if (input_str.find("TTJets_") != std::string::npos) 
  {
    trim = "met>200 && ht>500";
    output_str = "Skimmed_MET200_HT500_" + input_str;
    std::cout << "Output File Name: " << output_str << std::endl;
  }
  else if(input_str.find("QCD_") != std::string::npos)
  {
    trim = "met>175";
    output_str = "Skimmed_MET175_" + input_str;
    std::cout << "Output File Name: " << output_str << std::endl;
  }
  else
  {
    std::cout << "No Trim Parameters available for this Tree!" << std::endl;
    return 0;
  }

  TFile* input = TFile::Open(input_str.c_str());
  TTree* originalTree = (TTree*)input->Get("/stopTreeMaker/AUX");

  TFile* output = new TFile(output_str.c_str(), "RECREATE");
  TDirectory *mydict = output->mkdir("stopTreeMaker");
  mydict->cd();
  TTree* selectedTree = originalTree->CopyTree(trim.c_str());

  selectedTree->Write();
  output->Close();

  return 0;
}
