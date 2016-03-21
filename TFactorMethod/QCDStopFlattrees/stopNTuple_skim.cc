#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "TFile.h"
#include "TChain.h"
//#include "TH1.h"
//#include "TH2.h"
//#include "TProfile.h"
//#include "TRandom.h"
#include "TDirectory.h"
#include "TTree.h"

size_t find_Nth
(
  const std::string & str ,   // where to work
  unsigned            N ,     // N'th ocurrence
  const std::string & find    // what to 'find'
) 
{
  if ( 0==N ) { return std::string::npos; }
  size_t pos,from=0;
  unsigned i=0;
  while ( i<N ) 
  {
    pos=str.find(find,from);
    if ( std::string::npos == pos ) { break; }
    from = pos + 1; // from = pos + find.size();
    ++i;
  }
  return pos;
}

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"Please give 1 argument " << "inputFileName " << std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./PrivateSkim root://cmseos.fnal.gov//store/user/lpcsusyhad/Spring15_74X_Oct_2015_Ntp_v2X/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/QCD_HT500to700_Spring15DR74_Asympt25ns_Ntp_v2/150928_140039/0000/stopFlatNtuples_1.root" << std::endl;
    return -1;
  }
  std::string input_str(argv[1]); 
  std::string trim;
  //std::string outputpath = "/eos/uscms/store/group/lpcsusyhad/hua/Skimmed_2015Nov15/";
 
  std::string output_str;
  //here is a little bit tricky when dealing with the slash... need to improve
  //for all the MC samples
  //std::string tag = input_str.substr(find_Nth(input_str,10,"/") + 1,find_Nth(input_str,11,"/")-find_Nth(input_str,10,"/")-1);
  //for all the data samples
  std::string tag = input_str.substr(find_Nth(input_str,8,"/") + 1,find_Nth(input_str,9,"/")-find_Nth(input_str,8,"/")-1);
  //std::string tag = input_str.substr(find_Nth(input_str,10,"/") + 1,find_Nth(input_str,11,"/")-find_Nth(input_str,10,"/")-1);
  std::size_t idpos = input_str.find("stopFlatNtuples");
  std::string fileid = input_str.substr (idpos);
  
  //cut every tree with MET 200 and HT 500 except QCD tree
  //if( input_str.find("QCD_") != std::string::npos || input_str.find("_HTMHT") != std::string::npos )
  //{
    trim = "met>175";
    output_str = "Skimmed_MET175_" + tag + fileid;
    std::cout << "Output File Name: " << output_str << std::endl;
  //}
  //else
  //{ 
  //  trim = "met>200 && ht>500";
  //  output_str = "Skimmed_MET200_HT500_" + tag + fileid;
  //  std::cout << "Output File Name: " << output_str << std::endl;
  //}

  TFile* input = TFile::Open(input_str.c_str());
  TTree* originalTree = (TTree*)input->Get("/stopTreeMaker/AUX");

  TFile* output = new TFile((output_str).c_str(), "RECREATE");
  TDirectory *mydict = output->mkdir("stopTreeMaker");
  mydict->cd();
  TTree* selectedTree = originalTree->CopyTree(trim.c_str());

  selectedTree->Write();
  output->Close();

  std::string d = "root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15";
  std::system(("xrdcp " + output_str + " " + d).c_str());
  std::system(("rm " + output_str).c_str());

  return 0;
}
