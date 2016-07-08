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
//2016 Moriond
//#define LUMI 2262.946
//2016 ICHEP
//#define LUMI 8000
#define LUMI 4004.345

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
 private:
  bool FillChain(TChain *chain, const TString &inputFileList, std::string tag);
};
