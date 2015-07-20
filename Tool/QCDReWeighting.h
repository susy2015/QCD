#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TChain.h"

#include "Math/QuantFuncMathCore.h"
#include "TMath.h"

#include "SusyAnaTools/Tools/NTupleReader.h"

//Fill chain from txt file
bool FillChain(TChain *chain, const TString &inputFileList, std::string tag)
{
  std::ifstream infile(inputFileList, std::ifstream::in);
  std::string buffer;

  if(!infile.is_open())
  {
    std::cerr << "** ERROR: Can't open '" << inputFileList << "' for input" << std::endl;
    return false;
  }

  std::cout << "TreeUtilities : FillChain " << std::endl;
  while(1)
  {
    infile >> buffer;
    if(!infile.good()) break;
    //std::cout << "Adding tree from " << buffer.c_str() << std::endl;      
    if (buffer.find(tag) != std::string::npos) 
    {
      //std::cout << "found!" << '\n';
      chain->Add(buffer.c_str());
    }
  }
  std::cout << "No. of Entries in this tree : " << chain->GetEntries() << std::endl;
  return true;
}

struct QCDSampleInfo
{
  std::string QCDTag;
  double weight;
  TChain *chain;
};

class QCDSampleWeight
{
 public:
  std::vector<QCDSampleInfo> QCDSampleInfos;
  
  void FillQCDSampleInfos( const TString &inputFileList );
 private:
  void QCDSampleInfo_push_back( std::string tag, double xsec, double nevents, double lumi, const TString &inputFileList );
};

void QCDSampleWeight::FillQCDSampleInfos( const TString &inputFileList )
{
  QCDSampleInfos.clear();
 
  //ttbar test
  //QCDSampleInfo_push_back( "_ttbar_", 806.1, 25446993, 10000, inputFileList );
  //QCD HT binning Samples
  //QCDSampleInfo_push_back( "QCD_HT_250To500_", 670500, 2004219, 10000, inputFileList );
  //QCDSampleInfo_push_back( "QCD_HT_500To1000_", 26740, 3214312, 10000, inputFileList );
  //QCDSampleInfo_push_back( "QCD_HT_1000ToInf_", 769.7, 1130720, 10000, inputFileList );
  //QCD PT binning Samples
  //QCDSampleInfo_push_back( "QCD_PT_30To50_", 161500000, , 10000, inputFileList );
  //QCDSampleInfo_push_back( "QCD_PT_50To80_", 22110000, , 10000, inputFileList );
  //QCDSampleInfo_push_back( "QCD_PT_80To120_", 3000114, , 10000, inputFileList );
  //QCDSampleInfo_push_back( "QCD_PT_120To170_", 493200, , 10000, inputFileList );
  //QCDSampleInfo_push_back( "QCD_PT_170To300_", 120300, 2000704, 10000, inputFileList );
  QCDSampleInfo_push_back( "QCD_PT_300To470_", 7475, 2700637, 10000, inputFileList );
  QCDSampleInfo_push_back( "QCD_PT_470To600_", 587.1, 2907137, 10000, inputFileList );
  QCDSampleInfo_push_back( "QCD_PT_600To800_", 167, 2853619, 10000, inputFileList );
  QCDSampleInfo_push_back( "QCD_PT_800To1000_", 28.25, 2875729, 10000, inputFileList );
  QCDSampleInfo_push_back( "QCD_PT_1000To1400_", 8.195, 2884228, 10000, inputFileList );
  QCDSampleInfo_push_back( "QCD_PT_1400To1800_", 0.7346, 2931414, 10000, inputFileList );
  QCDSampleInfo_push_back( "QCD_PT_1800ToInf_", 0.1086, 2935195, 10000, inputFileList );
}

void QCDSampleWeight::QCDSampleInfo_push_back( std::string tag, double xsec, double nevents, double lumi, const TString &inputFileList)
{
  QCDSampleInfo oneInfo;

  oneInfo.QCDTag = tag;
  oneInfo.weight = xsec*lumi/nevents;
  oneInfo.chain= new TChain("AUX");
  //oneInfo.chain= new TChain("stopTreeMaker/AUX");
  if(!FillChain(oneInfo.chain, inputFileList,oneInfo.QCDTag))
  {
    std::cerr << "Cannot get the tree " << std::endl;
  }
  QCDSampleInfos.push_back(oneInfo);
  oneInfo = {};
}
