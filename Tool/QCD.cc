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
      double ht = tr.getVar<double>("ht");
      (myBaseHistgram.h_b_all_HT)->Fill(ht,thisweight);
      //searchbin variables
      int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      int nbottomjets = tr.getVar<int>("cntCSVS"+spec);
      double MT2 = tr.getVar<double>("best_had_brJet_MT2"+spec);
      
      double met = tr.getVar<double>("met");
      int njets30 = tr.getVar<int>("cntNJetsPt30Eta24"+spec);

      //if( met < 175 ) continue;
      int metbin_number = Set_metbin_number(met);
      int njetsbin_number = Set_njetsbin_number(njets30);

      bool passBaselineQCD = tr.getVar<bool>("passBaselineQCD");
      bool passdPhis = tr.getVar<bool>("passdPhisQCD");
      //std::cout << !passdPhis << std::endl;
      bool passBaseline = false;
      passBaseline = passBaselineQCD && passdPhis;
    
      if (passBaseline)
      {
        myQCDFactors.nQCDNormal_MC[i][metbin_number][njetsbin_number]++;
        myQCDFactors.nQCDNormal[i][metbin_number][njetsbin_number]+=thisweight;
        
        int searchbin_id = find_Binning_Index( nbottomjets , ntopjets , MT2, met );
        if( searchbin_id >= 0 )
        {
          myQCDFactors.nQCD_exp_sb[searchbin_id] += thisweight;
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
      int njets30 = tr.getVar<int>("cntNJetsPt30Eta24"+spec);
      //if( met < 175 ) continue;
      int metbin_number = Set_metbin_number(met);
      int njetsbin_number = Set_njetsbin_number(njets30);

      bool passBaselineQCD = tr.getVar<bool>("passBaselineQCD");
      bool passdPhis = tr.getVar<bool>("passdPhisQCD");
      bool passBaseline_dPhisInverted = false;
      passBaseline_dPhisInverted = passBaselineQCD && (!passdPhis);
      if (passBaseline_dPhisInverted)
      {
        int searchbin_id = find_Binning_Index( nbottomjets , ntopjets , MT2, met );
        if( searchbin_id >= 0 )
        {
          myQCDFactors.nQCD_pred_sb[searchbin_id] += (thisweight * myQCDFactors.QCDTFactor[metbin_number][njetsbin_number]);
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop

  myQCDFactors.printQCDFactorInfo();
  myQCDFactors.printQCDClosure();
  //write into histgram
  (myBaseHistgram.oFile)->Write();
  return 0;
}

void QCDFactors::NumbertoTFactor()
{
  //value calculation
  for(int i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(int j_cal = 0 ; j_cal < NJETS_BINS ; j_cal++)
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

  //uncertainty calculation
  for(int i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(int j_cal = 0 ; j_cal < NJETS_BINS ; j_cal++)
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
      for(k_cal = 0 ; k_cal < NJETS_BINS ; k_cal++)
      {
        std::cout << nQCDNormal_MC[i_cal][j_cal][k_cal] << " , ";
        if( k_cal == NJETS_BINS-1 )
        {
          std::cout << std::endl;
        }
      }
    }
  }

  std::cout << "Counting Normal: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < NJETS_BINS ; j_cal++)
    {
      std::cout << nQCDNormal_all[i_cal][j_cal] << "(" << nQCDNormal_all_err[i_cal][j_cal] << ") , ";
      if( j_cal == NJETS_BINS-1 )
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
      for(k_cal = 0 ; k_cal < NJETS_BINS ; k_cal++)
      {
        std::cout << nQCDInverted_MC[i_cal][j_cal][k_cal] << " , ";
        if( k_cal == NJETS_BINS-1 )
        {
          std::cout << std::endl;
        }
      }
    }
  }

  std::cout << "Counting Inverted: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < NJETS_BINS ; j_cal++)
    {
      std::cout << nQCDInverted_all[i_cal][j_cal] << "(" << nQCDInverted_all_err[i_cal][j_cal] << ") , ";;
      if( j_cal == NJETS_BINS-1 )
      {
        std::cout << std::endl;
      }
    }
  }

  std::cout << "Translation Factors: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < NJETS_BINS ; j_cal++)
    {
      std::cout << QCDTFactor[i_cal][j_cal] <<"(" << QCDTFactor_err[i_cal][j_cal] << ")" << " , ";
      if( j_cal == NJETS_BINS-1 )
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
    std::cout << "Search Bin Id:" << i_cal << "; Exp: " << nQCD_exp_sb[i_cal] << "; Pred: " << nQCD_pred_sb[i_cal] << "; (exp - pred)/pred: " << (nQCD_exp_sb[i_cal] - nQCD_pred_sb[i_cal])/nQCD_pred_sb[i_cal] << std::endl;
  }
}


void QCDFactors::printQCDClosure()
{
  TCanvas *c = new TCanvas("c","A Simple Graph Example",200,10,700,500); 
  gStyle->SetOptStat(0);

  TPad *pad = (TPad*) c->GetPad(0); 
  pad->Clear();
  pad->Divide(2, 1);

  double divRatio = 0.20;
  double labelRatio = (1-divRatio)/divRatio;
  double small = 0;

  pad->cd(1); 
  TPad *pad1 = (TPad*) pad->GetPad(1);
  pad1->SetPad("", "", 0, divRatio, 1.0, 1.0, kWhite);
  pad1->SetBottomMargin(0.005);
  pad1->SetBorderMode(0);

  TH1D *h_pred, *h_exp;
  h_pred = new TH1D("h_pred_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_exp = new TH1D("h_exp_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  h_pred->SetLineColor(1);
  h_pred->SetLineWidth(3);

  h_exp->SetLineColor(2);
  h_exp->SetLineWidth(3);

  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    h_pred->SetBinContent( i_cal+1 , nQCD_pred_sb[i_cal] );
    h_pred->SetBinError( i_cal+1 , std::sqrt( nQCD_pred_sb[i_cal] ) );
    h_exp->SetBinContent( i_cal+1 , nQCD_exp_sb[i_cal] );
    h_exp->SetBinError( i_cal+1 , std::sqrt( nQCD_exp_sb[i_cal] ) );
  }

  h_exp->Draw();
  h_pred->Draw("same");

  const std::string titre="CMS Preliminary 2015, 10 fb^{-1}, #sqrt{s} = 13 TeV";
  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);
  title->Draw("same");

  TLegend* leg = new TLegend(0.6,0.75,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  leg->AddEntry(h_pred,"Prediction","l");
  leg->AddEntry(h_exp,"Expectation","l");
  leg->Draw("same");

  c->Update(); 
 
  pad->cd(2); 
  TPad *pad2 = (TPad*) pad->GetPad(2);
  pad2->SetPad("ratio", "", 0, 0, 1.0, divRatio, kWhite);
  pad2->SetBottomMargin(0.3);
  pad2->SetTopMargin(small);
  pad2->SetBorderMode(0);

  TH1D *ratio = (TH1D*) h_exp->Clone();
  TH1D *allmc = (TH1D*) h_pred->Clone();

  ratio->Add(allmc, -1);
  ratio->Divide(allmc);
  ratio->GetYaxis()->SetTitle( "(exp - pred)/pred" );

  TAxis* xHT = ratio->GetXaxis();

  xHT->SetTickLength(xHT->GetTickLength()*labelRatio);
  xHT->SetLabelSize(xHT->GetLabelSize()*labelRatio);
  xHT->SetLabelOffset(xHT->GetLabelOffset()*labelRatio);
  ratio->SetMinimum(-1.0);
  ratio->SetMaximum(1.0);

  TAxis* yHT = ratio->GetYaxis();
  yHT->SetNdivisions(010);
  yHT->SetLabelSize(yHT->GetLabelSize()*2.0);
  yHT->SetTitleOffset(0.3);
  yHT->SetTitleSize(0.08);

  ratio->SetTitleSize(0.15);
  ratio->SetStats(kFALSE);
  ratio->SetMarkerStyle(kFullDotMedium);
  ratio->Sumw2();
  ratio->DrawCopy();

  TH1D *zero = (TH1D*)ratio->Clone(); 
  zero->Reset();
  for(int ib=0; ib<ratio->GetNbinsX(); ib++){ zero->SetBinContent(ib+1, 0); }
  zero->SetLineColor(kRed); zero->SetLineWidth(1);
  zero->DrawCopy("same");

  c->SaveAs( "QCDClosure_sb.png" );
  c->SaveAs( "QCDClosure_sb.C" );
}

