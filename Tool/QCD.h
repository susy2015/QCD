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
#include "SusyAnaTools/Tools/baselineDef.h"

#include "QCDBinFunction.h"

//############finish the definition of class AccRecoEffs######################
//baseline cut function definition
static BaselineVessel *myBaselineVessel;
void mypassBaselineFunc(NTupleReader& tr)
{
  (*myBaselineVessel)(tr);
}

class ClosureHistgram
{
 public:
  void BookHistgram(const char *);
  TFile *oFile;
  //closure plots on different variables and search bins
  TH1D *h_pred_met, *h_pred_njets, *h_pred_mt2, *h_pred_ht, *h_pred_mht, *h_pred_ntopjets, *h_pred_nbjets;
  TH1D *h_exp_met, *h_exp_njets, *h_exp_mt2, *h_exp_ht, *h_exp_mht, *h_exp_ntopjets, *h_exp_nbjets;
  TH1D *h_exp_sb, *h_pred_sb;
};

void ClosureHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");
  //closure plots on different variables
  h_pred_met = new TH1D("h_pred_met","",50,0,1000);
  h_pred_njets = new TH1D("h_pred_njets","",20,0,20);
  h_pred_mt2 = new TH1D("h_pred_mt2","",50,0,1000);
  h_pred_ht = new TH1D("h_pred_ht","",150,0,3000);
  h_pred_mht = new TH1D("h_pred_mht","",50,0,1000);
  h_pred_ntopjets = new TH1D("h_pred_ntopjets","",20,0,20);
  h_pred_nbjets = new TH1D("h_pred_nbjets","",20,0,20);

  h_exp_met = new TH1D("h_exp_met","",50,0,1000);
  h_exp_njets = new TH1D("h_exp_njets","",20,0,20);
  h_exp_mt2 = new TH1D("h_exp_mt2","",50,0,1000);
  h_exp_ht = new TH1D("h_exp_ht","",150,0,3000);
  h_exp_mht = new TH1D("h_exp_mht","",50,0,1000);
  h_exp_ntopjets = new TH1D("h_exp_ntopjets","",20,0,20);
  h_exp_nbjets = new TH1D("h_exp_nbjets","",20,0,20);

  h_exp_sb = new TH1D("h_exp_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_pred_sb = new TH1D("h_pred_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
}

class BaseHistgram
{
 public:
  void BookHistgram(const char *);

  TFile *oFile;
  TH1D *h_b_all_MET;
  TH1D *h_b_all_HT;

  TH1D *h_b_mt2_nbnt, *h_b_mt2_ybyt, *h_b_met_nbnt, *h_b_met_ybyt;
  TH1D *h_b_dphi0_nbnt, *h_b_dphi0_ybyt, *h_b_dphi1_nbnt, *h_b_dphi1_ybyt, *h_b_dphi2_nbnt, *h_b_dphi2_ybyt;
  TH1D *h_inverted_met, *h_inverted_njets, *h_inverted_mt2, *h_inverted_ht, *h_inverted_mht, *h_inverted_ntopjets, *h_inverted_nbjets;
};

void BaseHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");

  h_b_all_MET = new TH1D("h_b_all_MET","",1000,0,1000);
  h_b_all_HT = new TH1D("h_b_all_HT","",200,0,2000);

  h_b_mt2_nbnt = new TH1D("h_b_mt2_nbnt","",100,0,1000);
  h_b_mt2_ybyt = new TH1D("h_b_mt2_ybyt","",100,0,1000);
  h_b_met_nbnt = new TH1D("h_b_met_nbnt","",85,150,1000);
  h_b_met_ybyt = new TH1D("h_b_met_ybyt","",85,150,1000);
  h_b_dphi0_nbnt = new TH1D("h_b_dphi0_nbnt","",40,-5,5);
  h_b_dphi0_ybyt = new TH1D("h_b_dphi0_ybyt","",40,-5,5);
  h_b_dphi1_nbnt = new TH1D("h_b_dphi1_nbnt","",40,-5,5);
  h_b_dphi1_ybyt = new TH1D("h_b_dphi1_ybyt","",40,-5,5);
  h_b_dphi2_nbnt = new TH1D("h_b_dphi2_nbnt","",40,-5,5);
  h_b_dphi2_ybyt = new TH1D("h_b_dphi2_ybyt","",40,-5,5);

  h_inverted_met = new TH1D("h_inverted_met","",50,0,1000);
  h_inverted_njets = new TH1D("h_inverted_njets","",20,0,20);
  h_inverted_mt2 = new TH1D("h_inverted_mt2","",50,0,1000);
  h_inverted_ht = new TH1D("h_inverted_ht","",150,0,3000);
  h_inverted_mht = new TH1D("h_inverted_mht","",50,0,1000);
  h_inverted_ntopjets = new TH1D("h_inverted_ntopjets","",20,0,20);
  h_inverted_nbjets = new TH1D("h_inverted_nbjets","",20,0,20);
}

class QCDFactors
{
 public:
  double nQCDNormal_MC[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}}, nQCDInverted_MC[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}};
  double nQCDNormal[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}}, nQCDInverted[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}};
  double nQCDNormal_all[MET_BINS][MT2_BINS] = {{0}}, nQCDInverted_all[MET_BINS][MT2_BINS] = {{0}};
  double nQCDNormal_all_err[MET_BINS][MT2_BINS] = {{0}}, nQCDInverted_all_err[MET_BINS][MT2_BINS] = {{0}};
  double QCDTFactor[MET_BINS][MT2_BINS] = {{0}}, QCDTFactor_err[MET_BINS][MT2_BINS] = {{0}};
  double MET_sum[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}}, MET_sum_weight[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}};
  double MET_sum_all[MET_BINS][MT2_BINS] = {{0}}, MET_sum_weight_all[MET_BINS][MT2_BINS] = {{0}};
  double MET_mean[MET_BINS][MT2_BINS] = {{0}}, MET_mean_err[MET_BINS][MT2_BINS] = {{0}};

  double QCDWeights[QCD_BINS] = {0};
  double nQCD_exp_sb[NSEARCH_BINS] = {0}, nQCD_pred_sb[NSEARCH_BINS] = {0};
  double nQCD_exp_sb_MC[QCD_BINS][NSEARCH_BINS] = {{0}}, nQCD_pred_sb_MC[QCD_BINS][NSEARCH_BINS] = {{0}};
  double nQCD_exp_sb_err[NSEARCH_BINS] = {0}, nQCD_pred_sb_err[NSEARCH_BINS] = {0};

  void NumbertoTFactor();
  void TFactorFit();
  void printQCDFactorInfo(); 
  void printQCDClosureExp( ClosureHistgram& myClosureHistgram );
  void printQCDClosurePred( ClosureHistgram& myClosureHistgram );
  void TFactorsPlotsGen();
  void CountingPlotsGen();

 private:
  double get_stat_Error(
                        double a,
                        double an
                       );
 
};

double QCDFactors::get_stat_Error(
                                  double a,
                                  double an
                                 )
{
  double n;
  n = an - a;

  double err;
  err = 1000;

  double alpha;
  alpha = 1-0.6827;

  if( a>=0 && n>=0 )
  {
    err = std::sqrt(n/(a+n)/(a+n)*n/(a+n)/(a+n)*ROOT::Math::gamma_quantile_c(alpha/2,a+1,1)+a/(a+n)/(a+n)*a/(a+n)/(a+n)*ROOT::Math::gamma_quantile_c(alpha/2,n+1,1));
    return err;
  }
  else
  {
    return -1;
  }
}

void QCDFactors::NumbertoTFactor()
{
  //value calculation
  for(int i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(int j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
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
    for(int j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
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

void QCDFactors::printQCDFactorInfo()
{
  int i_cal,j_cal,k_cal;

  std::cout << "Counting Normal MC: " << std::endl;
  for( i_cal=0 ; i_cal < QCD_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MET_BINS ; j_cal++)
    {
      for(k_cal = 0 ; k_cal < MT2_BINS ; k_cal++)
      {
        std::cout << "QCD Files:" << i_cal << ", METBin:" << j_cal << ",MT2Bin:" << k_cal << "; :" << nQCDNormal_MC[i_cal][j_cal][k_cal] << std::endl;
      }
    }
  }

  std::cout << "Counting Normal: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      std::cout << "METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << nQCDNormal_all[i_cal][j_cal] << "(" << nQCDNormal_all_err[i_cal][j_cal] << ")"<< std::endl;
    }
  }

  std::cout << "Counting Inverted MC: " << std::endl;
  for( i_cal=0 ; i_cal < QCD_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MET_BINS ; j_cal++)
    {
      for(k_cal = 0 ; k_cal < MT2_BINS ; k_cal++)
      {
        std::cout << "QCD Files:" << i_cal << ", METBin:" << j_cal << ",MT2Bin:" << k_cal << "; :" << nQCDInverted_MC[i_cal][j_cal][k_cal] << std::endl;
      }
    }
  }

  std::cout << "Counting Inverted: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      std::cout << "METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << nQCDInverted_all[i_cal][j_cal] << "(" << nQCDInverted_all_err[i_cal][j_cal] << ")"<< std::endl;
    }
  }

  std::cout << "Translation Factors: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      std::cout << "METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << QCDTFactor[i_cal][j_cal] << "(" << QCDTFactor_err[i_cal][j_cal] << ")"<< std::endl;
    }
  }

  /*
  std::cout << "#QCD in Search Bins: " << std::endl;
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    std::cout << "Search Bin Id:" << i_cal << "; Exp: " << nQCD_exp_sb[i_cal] << "(" << nQCD_exp_sb_err[i_cal] << "); Pred: " << nQCD_pred_sb[i_cal] << "(" << nQCD_pred_sb_err[i_cal] << "); (exp - pred)/pred: " << (nQCD_exp_sb[i_cal] - nQCD_pred_sb[i_cal])/nQCD_pred_sb[i_cal] << std::endl;
  }
  */
}

void QCDFactors::printQCDClosureExp(ClosureHistgram& myClosureHistgram)
{
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    myClosureHistgram.h_exp_sb->SetBinContent( i_cal+1 , nQCD_exp_sb[i_cal] );
    myClosureHistgram.h_exp_sb->SetBinError( i_cal+1 , nQCD_exp_sb_err[i_cal] );
  }
  return ;
}

void QCDFactors::printQCDClosurePred(ClosureHistgram& myClosureHistgram)
{
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    myClosureHistgram.h_pred_sb->SetBinContent( i_cal+1 , nQCD_exp_sb[i_cal] );
    myClosureHistgram.h_pred_sb->SetBinError( i_cal+1 , nQCD_exp_sb_err[i_cal] );
  }
  return ;
}

void QCDFactors::TFactorsPlotsGen()
{
  const std::string titre="CMS Simulation 2015, #sqrt{s} = 13 TeV";

  TCanvas *c = new TCanvas("c", "c",0,51,1920,1004);
  c->SetFillColor(0);
  c->cd();

  double metbins[MET_BINS+1] = {175.0,200.0,350.0,650.0};
  //double ybins[MT2_BINS+1] = {1.0,2.0,5.0};
  double mt2bins[MT2_BINS+1] = {200.0,300.0,400.0,500.0};

  TH2D *tfactors2d  = new TH2D("tfactors","TFactors",MET_BINS,metbins,MT2_BINS,mt2bins);

  int i_cal;
  int j_cal;

  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      tfactors2d->SetBinContent( i_cal+1 , j_cal+1, QCDTFactor[i_cal][j_cal] );
      tfactors2d->SetBinError( i_cal+1 , j_cal+1, QCDTFactor_err[i_cal][j_cal] );
    }
  }

  tfactors2d->SetTitle("");
  tfactors2d->SetXTitle("MET [GeV]");
  tfactors2d->SetYTitle("MT2 [GeV]");
  //tfactors2d->SetYTitle("NbJets");
  tfactors2d->SetStats(0);

  gStyle->SetPaintTextFormat("1.2f");
  tfactors2d->Draw("colztexte");

  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);
  title->Draw("same");

  c->SaveAs( "_tfactors2d.png" );
  c->SaveAs( "_tfactors2d.pdf" );
  c->SaveAs( "_tfactors2d.C" );
  c->Close();
  return ;
}

void QCDFactors::CountingPlotsGen()
{
  const std::string titre="CMS Simulation 2015, 3fb-1, #sqrt{s} = 13 TeV";
  double metbins[MET_BINS+1] = {175.0,200.0,350.0,650.0};
  //double ybins[MT2_BINS+1] = {1.0,2.0,5.0};  
  double mt2bins[MT2_BINS+1] = {200.0,300.0,400.0,500.0};

  TH2D *countNormal_MC  = new TH2D("countNormal_MC","countNormal_MC",MET_BINS,metbins,MT2_BINS,mt2bins);
  TH2D *countNormal  = new TH2D("countNormal","countNormal",MET_BINS,metbins,MT2_BINS,mt2bins);
  TH2D *countInverted_MC  = new TH2D("countInverted_MC","countInverted_MC",MET_BINS,metbins,MT2_BINS,mt2bins);
  TH2D *countInverted  = new TH2D("countInverted","countInverted",MET_BINS,metbins,MT2_BINS,mt2bins);
      
  double nQCDNormal_MC_all[MET_BINS][MT2_BINS] = {{0}}, nQCDInverted_MC_all[MET_BINS][MT2_BINS] = {{0}};

  int i_cal;
  int j_cal;

  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      for(int tmp = 0 ; tmp < QCD_BINS ; tmp++)
      {
        nQCDNormal_MC_all[i_cal][j_cal] +=nQCDNormal_MC[tmp][i_cal][j_cal];
        nQCDInverted_MC_all[i_cal][j_cal] +=nQCDInverted_MC[tmp][i_cal][j_cal];
      }

      countNormal_MC->SetBinContent( i_cal+1 , j_cal+1, nQCDNormal_MC_all[i_cal][j_cal] );
      countNormal->SetBinContent( i_cal+1 , j_cal+1, nQCDNormal_all[i_cal][j_cal] );
      countNormal->SetBinError( i_cal+1 , j_cal+1, nQCDNormal_all_err[i_cal][j_cal] );

      countInverted_MC->SetBinContent( i_cal+1 , j_cal+1, nQCDInverted_MC_all[i_cal][j_cal] );
      countInverted->SetBinContent( i_cal+1 , j_cal+1, nQCDInverted_all[i_cal][j_cal] );
      countInverted->SetBinError( i_cal+1 , j_cal+1, nQCDInverted_all_err[i_cal][j_cal] );
    }
  }

  countNormal_MC->SetTitle("QCD Signal MC");
  countNormal_MC->SetXTitle("MET [GeV]");
  countNormal_MC->SetYTitle("MT2 [GeV]");
  countNormal_MC->SetStats(0);
  countNormal->SetTitle("QCD Signal Normalized");
  countNormal->SetXTitle("MET [GeV]");
  countNormal->SetYTitle("MT2 [GeV]");
  countNormal->SetStats(0);
  countInverted_MC->SetTitle("QCD Inverted DeltaPhi MC");
  countInverted_MC->SetXTitle("MET [GeV]");
  countInverted_MC->SetYTitle("MT2 [GeV]");
  countInverted_MC->SetStats(0);
  countInverted->SetTitle("QCD Inverted DeltaPhi Normalized");
  countInverted->SetXTitle("MET [GeV]");
  countInverted->SetYTitle("MT2 [GeV]");
  countInverted->SetStats(0);

  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);

  TCanvas *c = new TCanvas("c", "c",0,51,1920,1004);
  c->Divide(2,2);
  c->SetFillColor(0);
  gStyle->SetPaintTextFormat("1.2f");
  
  c->cd(1);
  countNormal_MC->Draw("colztexte");
  title->Draw("same");

  c->cd(2);
  countNormal->Draw("colztexte");
  title->Draw("same");

  c->cd(3);
  countInverted_MC->Draw("colztexte");
  title->Draw("same");

  c->cd(4);
  countInverted->Draw("colztexte");
  title->Draw("same");

  c->SaveAs( "_Allcount2d.png" );
  c->SaveAs( "_Allcount2d.pdf" );
  c->SaveAs( "_Allcount2d.C" );
  c->Close();

  return ;
}

//##########functions to calculate Delta_R and Delta Phi###############
double DeltaPhi(double phi1, double phi2) 
{
  double result = phi1 - phi2;
  while (result > M_PI)    result -= 2 * M_PI;
  while (result <= -M_PI)  result += 2 * M_PI;
  return result;
}

double DeltaR(double eta1, double phi1, double eta2, double phi2) 
{
  double deta = eta1 - eta2;
  double dphi = DeltaPhi(phi1, phi2);
  return std::sqrt(deta*deta + dphi*dphi);
}
