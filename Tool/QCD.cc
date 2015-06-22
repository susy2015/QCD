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
#include "Baseline.h"
#include "QCD.h"
#include "QCDReWeighting.h"

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

  //clock to monitor the run time
  size_t t0 = clock();
  //define my QCDFactors class to stroe counts and Translation factors
  QCDFactors myQCDFactors;
  //define my histgram class
  BaseHistgram myBaseHistgram;
  myBaseHistgram.BookHistgram(outFileName);

  QCDSampleWeight myQCDSampleWeight;
  myQCDSampleWeight.FillQCDSampleInfos(inputFileList);

  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  int i = 0;  

  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    NTupleReader tr((*iter_QCDSampleInfos).chain);
    //initialize the type3Ptr defined in the customize.h
    AnaFunctions::prepareTopTagger();
    //The passBaselineFunc is registered here
    tr.registerFunction(&passBaselineFunc);
        
    double thisweight = (*iter_QCDSampleInfos).weight;
    std::cout << "Weight" << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //filling HT variables for quick weight check
      double ht = tr.getVar<double>("ht");
      (myBaseHistgram.h_b_all_HT)->Fill(ht,thisweight);

      //met variables for fast running
      double met = tr.getVar<double>("met");
      //if( met < 175 ) continue;

      int metbin_number = Set_metbin_number(met);

      bool passBaselineQCD = tr.getVar<bool>("passBaselineQCD");
      bool passdPhis = tr.getVar<bool>("passdPhisQCD");
      bool passBaseline = false;
      passBaseline = passBaselineQCD && passdPhis;
    
      if (passBaseline)
      {
        myQCDFactors.nQCDNormal_MC[i][metbin_number]++;
        myQCDFactors.nQCDNormal[i][metbin_number]+=thisweight;

      }  

      bool passBaseline_dPhisInverted = false;
      passBaseline_dPhisInverted = passBaselineQCD && (!passdPhis);

      if (passBaseline_dPhisInverted)
      {
        myQCDFactors.nQCDInverted_MC[i][metbin_number]++;
        myQCDFactors.nQCDInverted[i][metbin_number]+=thisweight;
        myQCDFactors.MET_sum[i][metbin_number] = myQCDFactors.MET_sum[i][metbin_number] + met;
      }
    }//end of inner loop
    i++;
  }//end of QCD Samples loop

  myQCDFactors.NumbertoTFactor();
  //myQCDFactors.NumberNormalize();
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
  int i_cal,j_cal;

  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(j_cal = 0 ; j_cal < QCD_BINS ; j_cal++)
    {
       nQCDNormal_all[i_cal] += nQCDNormal[j_cal][i_cal];
       nQCDInverted_all[i_cal] += nQCDInverted[j_cal][i_cal];
    }
    
    QCDTFactor[i_cal] = nQCDNormal_all[i_cal]/nQCDInverted_all[i_cal];
    //QCDTFactor_err[i_cal] = get_stat_Error(nQCDNormal_MC[i_cal], nQCDInverted_MC[i_cal]);
    //MET_mean[i_cal] = MET_sum[i_cal]/nQCDInverted_MC[i_cal];
  }
}

/*
void fitexample()
{
  TFile *f = new TFile("hsimple.root");

  TH1F *hpx = (TH1F*)f->Get("hpx");
  //create a function with 3 parameters in the range [-3,3]
  TF1 *func = new TF1("fit",linearfitf,-3,3,3);
  func->SetParameters(500,hpx->GetMean(),hpx->GetRMS());
  func->SetParNames("Constant","Mean_value","Sigma");
  hpx->Fit("fit");
}
*/

void QCDFactors::printQCDFactorInfo()
{
  int i_cal,j_cal;

  std::cout << "Counting Normal MC: " << std::endl;
  for( i_cal=0 ; i_cal < QCD_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MET_BINS ; j_cal++)
    {
      std::cout << nQCDNormal_MC[i_cal][j_cal] << " , ";
      if( j_cal == MET_BINS-1 )
      {
        std::cout << std::endl;
      }
    }
  }

  std::cout << "Counting Normal: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    std::cout << nQCDNormal_all[i_cal] << " , ";
    if( i_cal == MET_BINS-1 )
    {
      std::cout << std::endl;
    }
  }

  std::cout << "Counting Inverted MC: " << std::endl;
  for( i_cal=0 ; i_cal < QCD_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MET_BINS ; j_cal++)
    {
      std::cout << nQCDInverted_MC[i_cal][j_cal] << " , ";
      if( j_cal == MET_BINS-1 )
      {
        std::cout << std::endl;
      }
    }
  }

  std::cout << "Counting Inverted: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    std::cout << nQCDInverted_all[i_cal] << " , ";
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
