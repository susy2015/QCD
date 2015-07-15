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
#include "SusyAnaTools/Tools/searchBins.h"

#include "TStopwatch.h"
#include "TString.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH1D.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TPad.h"
#include "TStyle.h"

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

  std::cout << "First Loop start(Factorization and Expectation): " << std::endl;

  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    NTupleReader tr((*iter_QCDSampleInfos).chain);
    //initialize the type3Ptr defined in the customize.h
    AnaFunctions::prepareTopTagger();
    //The passBaselineFunc is registered here
    tr.registerFunction(&passBaselineFunc);
        
    double thisweight = (*iter_QCDSampleInfos).weight;
    myQCDFactors.QCDWeights[i] = thisweight;
    std::cout << "Weight " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //filling HT variables for quick weight check
      //double ht = tr.getVar<double>("ht");
      //(myBaseHistgram.h_b_all_HT)->Fill(ht,thisweight);
      //searchbin variables
      int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      int nbottomjets = tr.getVar<int>("cntCSVS"+spec);
      double MT2 = tr.getVar<double>("best_had_brJet_MT2"+spec);      
      double met = tr.getVar<double>("met");
      //closure plots variables
      int njets30 = tr.getVar<int>("cntNJetsPt30Eta24"+spec);
      double ht = tr.getVar<double>("ht");
      double bestTopJetMass = tr.getVar<double>("bestTopJetMass"+spec);
      double mht = tr.getVar<double>("mht");

      //if( met < 175 ) continue;
      int metbin_number = Set_metbin_number(met);
      int njetsbin_number = Set_nbjetsbin_number(nbottomjets);

      bool passBaselineQCD = tr.getVar<bool>("passBaselineQCD");
      bool passdPhis = tr.getVar<bool>("passdPhisQCD");
      //std::cout << !passdPhis << std::endl;
      
      //normal baseline
      bool passBaseline = false;
      passBaseline = passBaselineQCD && passdPhis;
    
      if (passBaseline)
      {
        myQCDFactors.nQCDNormal_MC[i][metbin_number][njetsbin_number]++;
        myQCDFactors.nQCDNormal[i][metbin_number][njetsbin_number]+=thisweight;
 
        (myBaseHistgram.h_exp_met)->Fill(met,thisweight);
        (myBaseHistgram.h_exp_njets)->Fill(njets30,thisweight);
        (myBaseHistgram.h_exp_mt2)->Fill(MT2,thisweight);
        (myBaseHistgram.h_exp_topmass)->Fill(bestTopJetMass,thisweight);
        (myBaseHistgram.h_exp_ht)->Fill(ht,thisweight);
        (myBaseHistgram.h_exp_mht)->Fill(mht,thisweight);
        (myBaseHistgram.h_exp_ntopjets)->Fill(ntopjets,thisweight);
        (myBaseHistgram.h_exp_nbjets)->Fill(nbottomjets,thisweight);

        int searchbin_id = find_Binning_Index( nbottomjets , ntopjets , MT2, met );
        if( searchbin_id >= 0 )
        {
          myQCDFactors.nQCD_exp_sb[searchbin_id] += thisweight;
          myQCDFactors.nQCD_exp_sb_MC[i][searchbin_id]++;
        }
      }  

      bool passBaseline_dPhisInverted = false;
      passBaseline_dPhisInverted = passBaselineQCD && (!passdPhis);

      if (passBaseline_dPhisInverted)
      {
        myQCDFactors.nQCDInverted_MC[i][metbin_number][njetsbin_number]++;
        myQCDFactors.nQCDInverted[i][metbin_number][njetsbin_number]+=thisweight;
        myQCDFactors.MET_sum[i][metbin_number][njetsbin_number] = myQCDFactors.MET_sum[i][metbin_number][njetsbin_number] + met * thisweight;
        myQCDFactors.MET_sum_weight[i][metbin_number][njetsbin_number] = myQCDFactors.MET_sum_weight[i][metbin_number][njetsbin_number] + thisweight;
      }
    }//end of inner loop
    i++;
  }//end of QCD Samples loop

  myQCDFactors.NumbertoTFactor();
  //myQCDFactors.TFactorFit();

  std::cout << "Second Loop start(Prediction): " << std::endl;
  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    NTupleReader tr((*iter_QCDSampleInfos).chain);
    //initialize the type3Ptr defined in the customize.h
    AnaFunctions::prepareTopTagger();
    //The passBaselineFunc is registered here
    tr.registerFunction(&passBaselineFunc);
        
    double thisweight = (*iter_QCDSampleInfos).weight;
    std::cout << "Weight " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      int nbottomjets = tr.getVar<int>("cntCSVS"+spec);
      double MT2 = tr.getVar<double>("best_had_brJet_MT2"+spec);
      double met = tr.getVar<double>("met");
      //closure plots variables
      int njets30 = tr.getVar<int>("cntNJetsPt30Eta24"+spec);
      double ht = tr.getVar<double>("ht");
      double bestTopJetMass = tr.getVar<double>("bestTopJetMass"+spec);
      double mht = tr.getVar<double>("mht");

      //if( met < 175 ) continue;
      int metbin_number = Set_metbin_number(met);
      int njetsbin_number = Set_nbjetsbin_number(nbottomjets);

      bool passBaselineQCD = tr.getVar<bool>("passBaselineQCD");
      bool passdPhis = tr.getVar<bool>("passdPhisQCD");
      bool passBaseline_dPhisInverted = false;
      passBaseline_dPhisInverted = passBaselineQCD && (!passdPhis);

      if (passBaseline_dPhisInverted)
      {
        double predweight = thisweight * myQCDFactors.QCDTFactor[metbin_number][njetsbin_number];
        (myBaseHistgram.h_pred_met)->Fill(met,predweight);
        (myBaseHistgram.h_pred_njets)->Fill(njets30,predweight);
        (myBaseHistgram.h_pred_mt2)->Fill(MT2,predweight);
        (myBaseHistgram.h_pred_topmass)->Fill(bestTopJetMass,predweight);
        (myBaseHistgram.h_pred_ht)->Fill(ht,predweight);
        (myBaseHistgram.h_pred_mht)->Fill(mht,predweight);
        (myBaseHistgram.h_pred_ntopjets)->Fill(ntopjets,predweight);
        (myBaseHistgram.h_pred_nbjets)->Fill(nbottomjets,predweight);

        int searchbin_id = find_Binning_Index( nbottomjets , ntopjets , MT2, met );
        if( searchbin_id >= 0 )
        {
          //std::cout << predweight << std::endl;
          myQCDFactors.nQCD_pred_sb[searchbin_id] += (predweight);
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop

  myQCDFactors.printQCDFactorInfo();
  myQCDFactors.printQCDClosure(myBaseHistgram);
  //write into histgram
  (myBaseHistgram.oFile)->Write();
  return 0;
}

void QCDFactors::NumbertoTFactor()
{
  //value calculation
  for(int i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(int j_cal = 0 ; j_cal < NBJETS_BINS ; j_cal++)
    {
      for(int k_cal = 0 ; k_cal < QCD_BINS ; k_cal++)
      {
         nQCDNormal_all[i_cal][j_cal] += nQCDNormal[k_cal][i_cal][j_cal];
         nQCDInverted_all[i_cal][j_cal] += nQCDInverted[k_cal][i_cal][j_cal];
         MET_sum_all[i_cal][j_cal] += MET_sum[k_cal][i_cal][j_cal];
         MET_sum_weight_all[i_cal][j_cal] += MET_sum_weight[k_cal][i_cal][j_cal];
      }
      QCDTFactor[i_cal][j_cal] = nQCDNormal_all[i_cal][j_cal]/nQCDInverted_all[i_cal][j_cal];
      MET_mean[i_cal][j_cal] = MET_sum_all[i_cal][j_cal]/MET_sum_weight_all[i_cal][j_cal];
    }
  }

  //TFactor uncertainty calculation
  for(int i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(int j_cal = 0 ; j_cal < NBJETS_BINS ; j_cal++)
    {
      for(int k_cal = 0 ; k_cal < QCD_BINS ; k_cal++)
      {
        nQCDNormal_all_err[i_cal][j_cal] += nQCDNormal_MC[k_cal][i_cal][j_cal] * QCDWeights[k_cal] * QCDWeights[k_cal] ;
        nQCDInverted_all_err[i_cal][j_cal] += nQCDInverted_MC[k_cal][i_cal][j_cal] * QCDWeights[k_cal] * QCDWeights[k_cal];
      }
      nQCDNormal_all_err[i_cal][j_cal] = std::sqrt( nQCDNormal_all_err[i_cal][j_cal] );
      nQCDInverted_all_err[i_cal][j_cal] = std::sqrt( nQCDInverted_all_err[i_cal][j_cal] );
      QCDTFactor_err[i_cal][j_cal] = QCDTFactor[i_cal][j_cal] * std::sqrt( nQCDNormal_all_err[i_cal][j_cal]*nQCDNormal_all_err[i_cal][j_cal]/nQCDNormal_all[i_cal][j_cal]/nQCDNormal_all[i_cal][j_cal] + nQCDInverted_all_err[i_cal][j_cal]*nQCDInverted_all_err[i_cal][j_cal]/nQCDInverted_all[i_cal][j_cal]/nQCDInverted_all[i_cal][j_cal] );
    }
  }

  //Expected QCD uncertainty calculation
  for(int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++)
  {
    for(int j_cal = 0 ; j_cal < QCD_BINS ; j_cal++)
    {
      nQCD_exp_sb_err[i_cal] += nQCD_exp_sb_MC[j_cal][i_cal] * QCDWeights[j_cal] * QCDWeights[j_cal];
    }
    nQCD_exp_sb_err[i_cal] = std::sqrt( nQCD_exp_sb_err[i_cal] );
  }
}
/*
void QCDFactors::TFactorFit()
{
  TCanvas *c = new TCanvas("c","A Simple Graph with error bars",200,10,700,500);
  //c->SetFillColor(42);
  //c->SetGrid();
  //c->GetFrame()->SetFillColor(21);
  //c->GetFrame()->SetBorderSize(12);

  TGraphErrors *gr = new TGraphErrors( MET_BINS , MET_mean , QCDTFactor , MET_mean_err , QCDTFactor_err );
  gr->SetTitle("MC Translation Factor vs. MET");
  gr->GetXaxis()->SetTitle("MET [GeV]");
  gr->GetYaxis()->SetTitle("T QCD");
  gr->SetMarkerColor(2);
  gr->SetMarkerStyle(21);
  gr->Draw("ALP");

  c->SaveAs( "TFactor.png" );
  c->SaveAs( "TFactor.C" );
  TFactorFitPlots->Write();
}
*/

void QCDFactors::printQCDFactorInfo()
{
  int i_cal,j_cal,k_cal;

  std::cout << "Counting Normal MC: " << std::endl;
  for( i_cal=0 ; i_cal < QCD_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MET_BINS ; j_cal++)
    {
      for(k_cal = 0 ; k_cal < NBJETS_BINS ; k_cal++)
      {
        std::cout << nQCDNormal_MC[i_cal][j_cal][k_cal] << " , ";
        if( k_cal == NBJETS_BINS-1 )
        {
          std::cout << std::endl;
        }
      }
    }
  }

  std::cout << "Counting Normal: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < NBJETS_BINS ; j_cal++)
    {
      std::cout << nQCDNormal_all[i_cal][j_cal] << "(" << nQCDNormal_all_err[i_cal][j_cal] << ") , ";
      if( j_cal == NBJETS_BINS-1 )
      {
        std::cout << std::endl;
      }
    }
  }

  std::cout << "Counting Inverted MC: " << std::endl;
  for( i_cal=0 ; i_cal < QCD_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MET_BINS ; j_cal++)
    {
      for(k_cal = 0 ; k_cal < NBJETS_BINS ; k_cal++)
      {
        std::cout << nQCDInverted_MC[i_cal][j_cal][k_cal] << " , ";
        if( k_cal == NBJETS_BINS-1 )
        {
          std::cout << std::endl;
        }
      }
    }
  }

  std::cout << "Counting Inverted: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < NBJETS_BINS ; j_cal++)
    {
      std::cout << nQCDInverted_all[i_cal][j_cal] << "(" << nQCDInverted_all_err[i_cal][j_cal] << ") , ";;
      if( j_cal == NBJETS_BINS-1 )
      {
        std::cout << std::endl;
      }
    }
  }

  std::cout << "Translation Factors: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < NBJETS_BINS ; j_cal++)
    {
      std::cout << QCDTFactor[i_cal][j_cal] <<"(" << QCDTFactor_err[i_cal][j_cal] << ")" << " , ";
      if( j_cal == NBJETS_BINS-1 )
      {
        std::cout << std::endl;
      }
    }
  }

  /*
  std::cout << "Mean MET: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    std::cout << MET_mean[i_cal][j_cal] <<"(" << MET_mean_err[i_cal][j_cal] << ")" << " , ";
    if( i_cal == MET_BINS-1 )
    {
      std::cout << std::endl;
    }
  }
  */
  std::cout << "#QCD in Search Bins: " << std::endl;
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    std::cout << "Search Bin Id:" << i_cal << "; Exp: " << nQCD_exp_sb[i_cal] << "(" << nQCD_exp_sb_err[i_cal] << "); Pred: " << nQCD_pred_sb[i_cal] << "(" << nQCD_pred_sb_err[i_cal] << "); (exp - pred)/pred: " << (nQCD_exp_sb[i_cal] - nQCD_pred_sb[i_cal])/nQCD_pred_sb[i_cal] << std::endl;
  }
}


void QCDFactors::printQCDClosure(BaseHistgram& myBaseHistgram)
{
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    myBaseHistgram.h_pred_sb->SetBinContent( i_cal+1 , nQCD_pred_sb[i_cal] );
    myBaseHistgram.h_pred_sb->SetBinError( i_cal+1 , nQCD_pred_sb_err[i_cal] );
    myBaseHistgram.h_exp_sb->SetBinContent( i_cal+1 , nQCD_exp_sb[i_cal] );
    myBaseHistgram.h_exp_sb->SetBinError( i_cal+1 , nQCD_exp_sb_err[i_cal] );
  }
  return ;
}

