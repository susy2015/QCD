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

class BaseHistgram;

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


  //TFile *TFactorFitPlots = new TFile("TFactorFitPlots.root", "recreate");

  void NumbertoTFactor();
  void TFactorFit();
  void printQCDFactorInfo(); 
  void printQCDClosure( BaseHistgram& myBaseHistgram );
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

class BaseHistgram
{
 public:
  void BookHistgram(const char *);

  TFile *oFile;
  TH1D *h_b_all_MET;
  TH1D *h_b_all_HT;

  TH1D *h_b_mt2_nbnt, *h_b_mt2_ybyt, *h_b_met_nbnt, *h_b_met_ybyt;
  TH1D *h_b_dphi0_nbnt, *h_b_dphi0_ybyt, *h_b_dphi1_nbnt, *h_b_dphi1_ybyt, *h_b_dphi2_nbnt, *h_b_dphi2_ybyt;
  //closure plots on different variables and search bins
  TH1D *h_pred_met, *h_pred_njets, *h_pred_mt2, *h_pred_ht, *h_pred_mht, *h_pred_ntopjets, *h_pred_nbjets;
  TH1D *h_exp_met, *h_exp_njets, *h_exp_mt2, *h_exp_ht, *h_exp_mht, *h_exp_ntopjets, *h_exp_nbjets;
  TH1D *h_inverted_met, *h_inverted_njets, *h_inverted_mt2, *h_inverted_ht, *h_inverted_mht, *h_inverted_ntopjets, *h_inverted_nbjets;
  TH1D *h_exp_sb, *h_pred_sb;
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
  h_b_dphi0_nbnt = new TH1D("h_b_dphi0_nbnt","",1000,-5,5);
  h_b_dphi0_ybyt = new TH1D("h_b_dphi0_ybyt","",1000,-5,5);
  h_b_dphi1_nbnt = new TH1D("h_b_dphi1_nbnt","",1000,-5,5);
  h_b_dphi1_ybyt = new TH1D("h_b_dphi1_ybyt","",1000,-5,5);
  h_b_dphi2_nbnt = new TH1D("h_b_dphi2_nbnt","",1000,-5,5);
  h_b_dphi2_ybyt = new TH1D("h_b_dphi2_ybyt","",1000,-5,5);

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

  h_inverted_met = new TH1D("h_inverted_met","",50,0,1000);
  h_inverted_njets = new TH1D("h_inverted_njets","",20,0,20);
  h_inverted_mt2 = new TH1D("h_inverted_mt2","",50,0,1000);
  h_inverted_ht = new TH1D("h_inverted_ht","",150,0,3000);
  h_inverted_mht = new TH1D("h_inverted_mht","",50,0,1000);
  h_inverted_ntopjets = new TH1D("h_inverted_ntopjets","",20,0,20);
  h_inverted_nbjets = new TH1D("h_inverted_nbjets","",20,0,20);

  h_exp_sb = new TH1D("h_exp_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_pred_sb = new TH1D("h_pred_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
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
