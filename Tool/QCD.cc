#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <cmath>
#include <set>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <fstream>

#include <vector>

#include "SusyAnaTools/Tools/samples.h"
#include "SusyAnaTools/Tools/customize.h"

#include "TStopwatch.h"
#include "TString.h"

#include "Baseline.h"
#include "QCD.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH1D.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"

#include "Math/QuantFuncMathCore.h"
#include "TMath.h"
#include "TLorentzVector.h"
//#include "TROOT.h"
//#include "TInterpreter.h"
using namespace std;

int main(int argc, char* argv[])
{

  if (argc < 2)
  {
    std::cerr <<"Please give 2 arguments " << "runList " << " " << "outputFileName" << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./QCD runlist_QCD.txt test.root" << std::endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName   = argv[2];

  //TChain *fChain = new TChain("stopTreeMaker/AUX");
  TChain *fChain = new TChain("AUX");

  if(!FillChain(fChain, inputFileList))
  {
    std::cerr << "Cannot get the tree " << std::endl;
  }

  //clock to monitor the run time
  size_t t0 = clock();

  NTupleReader tr(fChain);
  //initialize the type3Ptr defined in the customize.h
  AnaFunctions::prepareTopTagger();
  //The passBaselineFunc is registered here
  tr.registerFunction(&passBaselineFunc);
  //define my QCDFactors class to stroe counts and Translation factors
  QCDFactors myQCDFactors;

  //define my histgram class
  BaseHistgram myBaseHistgram;
  myBaseHistgram.BookHistgram(outFileName);

  while(tr.getNextEvent())
  {
    if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

    double ht = tr.getVar<double>("ht");
    (myBaseHistgram.h_b_all_HT)->Fill(ht);
    double met = tr.getVar<double>("met");
    int metbin_number = Set_metbin_number(met);

    bool passBaseline = tr.getVar<bool>("passBaseline");
    if (passBaseline)
    {
      myQCDFactors.nQCDNormal_MC[metbin_number]++;
    }

    bool passBaseline_dPhisInverted = tr.getVar<bool>("passBaseline_dPhisInverted");
    if (passBaseline_dPhisInverted)
    {
      myQCDFactors.nQCDInverted_MC[metbin_number]++;
      myQCDFactors.MET_sum[metbin_number] = myQCDFactors.MET_sum[metbin_number] + met;
    }

  }//end of first loop

  myQCDFactors.NumbertoTFactor();
  myQCDFactors.NumberNormalize();
  myQCDFactors.printQCDFactorInfo();
  //write into histgram
  (myBaseHistgram.oFile)->Write();
  //std::cout << "Normal:" << nevents_baseline << "Inverted:" << nevents_baseline_dPhisInverted << std::endl;
  //const double ttbarCrossSection=806.1;
  //const double lumi=1000.0;
  //const double ntoteventsttbar=25446993.0;
  //std::cout << "nevents_muonCS = " << nevents_muonCS << std::endl;
  //std::cout << "nevents_muonCS_norm (1fb-1) = " << nevents_muonCS*ttbarCrossSection*lumi/ntoteventsttbar << std::endl;
  //std::cout << "nevents_baseline = " << nevents_baseline << std::endl;
  //std::cout << "nevents_baseline_ref = " << nevents_baseline_ref << std::endl;
  //std::cout << "nevents_baseline_norm (1fb-1) = " << nevents_baseline*ttbarCrossSection*lumi/ntoteventsttbar << std::endl;
  return 0;
}

void QCDFactors::NumbertoTFactor()
{
  int i_cal;

  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    QCDTFactor[i_cal] = nQCDNormal_MC[i_cal]/nQCDInverted_MC[i_cal];
    QCDTFactor_err[i_cal] = get_stat_Error(nQCDNormal_MC[i_cal], nQCDInverted_MC[i_cal]);
    MET_mean[i_cal] = MET_sum[i_cal]/nQCDInverted_MC[i_cal];
  }
}

void QCDFactors::NumberNormalize()
{
  double XSec = 670500+26740+769.7;
  double Lumi = 1000.0;
  //double Nevents = 663953+849033+333733;
  double Nevents = 2004219+3214312+1130720;

  double scale = XSec*Lumi/Nevents;

  std::cout << "scale: " << scale << std::endl;

  for(int i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    nQCDNormal[i_cal] = nQCDNormal_MC[i_cal]*scale;
    nQCDInverted[i_cal]= nQCDInverted_MC[i_cal]*scale;
  }
}

void QCDFactors::printQCDFactorInfo()
{
  int i_cal = 0;

  std::cout << "Counting Normal MC: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    std::cout << nQCDNormal_MC[i_cal] << " , ";
    if( i_cal == MET_BINS-1 )
    {
      std::cout << std::endl;
    }
  }

  std::cout << "Counting Normal: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    std::cout << nQCDNormal[i_cal] << " , ";
    if( i_cal == MET_BINS-1 )
    {
      std::cout << std::endl;
    }
  }

  std::cout << "Counting Inverted MC: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    std::cout << nQCDInverted_MC[i_cal] << " , ";
    if( i_cal == MET_BINS-1 )
    {
      std::cout << std::endl;
    }
  }

  std::cout << "Counting Inverted: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    std::cout << nQCDInverted[i_cal] << " , ";
    if( i_cal == MET_BINS-1 )
    {
      std::cout << std::endl;
    }
  }

  std::cout << "Translation Factors: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    std::cout << QCDTFactor[i_cal] <<"(" << QCDTFactor_err[i_cal] << ")" << " , ";
    if( i_cal == MET_BINS-1 )
    {
      std::cout << std::endl;
    }
  }

  std::cout << "Mean MET: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    std::cout << MET_mean[i_cal] <<"(" << MET_mean[i_cal] << ")" << " , ";
    if( i_cal == MET_BINS-1 )
    {
      std::cout << std::endl;
    }
  }
}
