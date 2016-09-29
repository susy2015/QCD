#include "QCDReWeighting.h"

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
  //oneInfo.chain= new TChain("stopTreeMaker/QCDTFTree");
  if(!FillChain(oneInfo.chain, inputFileList, oneInfo.QCDTag))
  {
    std::cerr << "Cannot get the tree " << std::endl;
  }
  QCDSampleInfos.push_back(oneInfo);
  oneInfo = {};
}

//Fill chain from txt file
bool QCDSampleWeight::FillChain(TChain *chain, const TString &inputFileList, std::string tag)
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

