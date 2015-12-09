#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TChain.h"

#include "Math/QuantFuncMathCore.h"
#include "TMath.h"

#include "SusyAnaTools/Tools/NTupleReader.h"
//define lumi in pb-1
//#define LUMI 2153.736
#define LUMI 3000
//Fill chain from txt file
bool FillChain(TChain *chain, const TString &inputFileList, std::string tag)
{
  std::ifstream infile( inputFileList, std::ifstream::in );
  std::string buffer;

  if(!infile.is_open())
  {
    std::cerr << "** ERROR: Can't open '" << inputFileList << "' for input" << std::endl;
    return false;
  }

  std::cout << "TreeUtilities : FillChain " << tag << std::endl;
  while(1)
  {
    buffer.clear();
    infile >> buffer;

    if(!infile.good()) break;
    //std::cout << "Adding tree from " << buffer.c_str() << std::endl;
    //std::cout << (buffer.find(tag) != std::string::npos) << std::endl;
    if (buffer.find(tag) != std::string::npos) 
    {
      //std::cout << tag << " found!" << std::endl;
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
  void QCDSampleInfo_push_back( std::string tag, double xsec, double nevents, double lumi, double kf, const TString &inputFileList );
};

//ttbar test
//QCDSampleInfo_push_back( "_ttbar_", 806.1, 25446993, LUMI, inputFileList );

//QCD HT binnning samples, all
//QCDSampleInfo_push_back( "QCD_HT100to200_"  , 27540000, 80093092, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_HT200to300_"  , 1735000 , 18717349, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_HT300to500_"  , 367000  , 20086103, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_HT500to700_"  , 29370   , 19542847, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_HT700to1000_" , 6524    , 15011016, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_HT1000to1500_", 1064    ,  4963895, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_HT1500to2000_", 121.5   ,  3848411, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_HT2000toInf_" , 25.42   ,  1856112, LUMI, inputFileList );

//QCD PT binning Samples
//QCDSampleInfo_push_back( "QCD_Pt_10to15_"    , 5887580000 , 3449170, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_15to30_"    , 1837410000 , 4942232, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_30to50_"    , 140932000  , 4957245, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_50to80_"    , 19204300   , 4978425, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_80to120_"   , 2762530    , 3424782, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_120to170_"  , 471100     , 3452896, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_170to300_"  , 117276     , 3364368, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_300to470_"  , 7823       , 2933611, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_470to600_"  , 648.2      , 1936832, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_600to800_"  , 186.9      , 1964128, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_800to1000_" , 32.293     , 1937216, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_1000to1400_", 9.4183     , 1487136, LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_1400to1800_", 0.84265    , 197959 , LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_1800to2400_", 0.114943   , 193608 , LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_2400to3200_", 0.00682981 , 194456 , LUMI, inputFileList );
//QCDSampleInfo_push_back( "QCD_Pt_3200toInf_" , 0.000165445, 192944 , LUMI, inputFileList );

void QCDSampleWeight::QCDSampleInfo_push_back( std::string tag, double xsec, double nevents, double lumi, double kf, const TString &inputFileList)
{
  QCDSampleInfo oneInfo;

  oneInfo.QCDTag = tag;
  oneInfo.weight = xsec*lumi*kf/nevents;
  //weight is one if we are reading data
  //if( tag.find("HTMHT") != std::string::npos ) oneInfo.weight = 1;
  //negative weight for the sample other than QCD and HTMHT
  //if( !(tag.find("QCD") != std::string::npos) ) oneInfo.weight = -xsec*lumi/nevents;
  //if( tag.find("HTMHT") != std::string::npos ) oneInfo.weight = 1;

  oneInfo.chain= new TChain("stopTreeMaker/AUX");
  if(!FillChain(oneInfo.chain, inputFileList, oneInfo.QCDTag))
  {
    std::cerr << "Cannot get the tree " << std::endl;
  }
  QCDSampleInfos.push_back(oneInfo);
  oneInfo = {};
}
