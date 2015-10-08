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
  TH1D *h_b_baseline_nMuons, *h_b_baseline_njets, *h_b_baseline_nbjetsCSVM, *h_b_baseline_bestTopMass, *h_b_baseline_MET, *h_b_baseline_jetpt2, *h_b_baseline_jetpt4, *h_b_baseline_jet1_met_phi_diff, *h_b_baseline_jet2_met_phi_diff, *h_b_baseline_jet3_met_phi_diff;
  TH1D *h_b_acc_njets, *h_b_acc_nbjetsCSVM, *h_b_acc_bestTopMass, *h_b_acc_MET, *h_b_acc_jetpt2, *h_b_acc_jetpt4, *h_b_acc_jet1_met_phi_diff, *h_b_acc_jet2_met_phi_diff, *h_b_acc_jet3_met_phi_diff;
  TH1D *h_b_reco_nMuons, *h_b_reco_njets, *h_b_reco_nbjetsCSVM, *h_b_reco_bestTopMass, *h_b_reco_MET, *h_b_reco_jetpt2, *h_b_reco_jetpt4, *h_b_reco_jet1_met_phi_diff, *h_b_reco_jet2_met_phi_diff, *h_b_reco_jet3_met_phi_diff;

  //closure plots on different variables and search bins
  TH1D *h_pred_met, *h_pred_njets, *h_pred_mt2, *h_pred_topmass, *h_pred_ht, *h_pred_mht, *h_pred_ntopjets, *h_pred_nbjets;
  TH1D *h_exp_met, *h_exp_njets, *h_exp_mt2, *h_exp_topmass, *h_exp_ht, *h_exp_mht, *h_exp_ntopjets, *h_exp_nbjets;
  TH1D *h_inverted_met, *h_inverted_njets, *h_inverted_mt2, *h_inverted_topmass, *h_inverted_ht, *h_inverted_mht, *h_inverted_ntopjets, *h_inverted_nbjets;
  TH1D *h_exp_sb, *h_pred_sb;

  TH2D *h_met_mt2;
  TH1D *h_mt2_cutmet0, *h_mt2_cutmet50, *h_mt2_cutmet100, *h_mt2_cutmet150, *h_mt2_cutmet200;
};

void BaseHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");

  h_b_all_MET = new TH1D("h_b_all_MET","",1000,0,1000);
  h_b_all_HT = new TH1D("h_b_all_HT","",200,0,2000);

  h_b_baseline_nMuons = new TH1D("h_b_baseline_nMuons","",10,0,10);
  h_b_baseline_njets = new TH1D("h_b_baseline_njets","",10,0,10);
  h_b_baseline_nbjetsCSVM = new TH1D("h_b_baseline_nbjetsCSVM","",10,0,10);
  h_b_baseline_bestTopMass = new TH1D("h_b_baseline_bestTopMass","",1000,0,500);
  h_b_baseline_MET = new TH1D("h_b_baseline_MET","",1000,0,1000);
  h_b_baseline_jetpt4 = new TH1D("h_b_baseline_jetpt4","",1000,0,1000);
  h_b_baseline_jetpt2 = new TH1D("h_b_baseline_jetpt2","",1000,0,1000);
  h_b_baseline_jet1_met_phi_diff = new TH1D("h_b_baseline_jet1_met_phi_diff","",1000,-5,5);
  h_b_baseline_jet2_met_phi_diff = new TH1D("h_b_baseline_jet2_met_phi_diff","",1000,-5,5);
  h_b_baseline_jet3_met_phi_diff = new TH1D("h_b_baseline_jet3_met_phi_diff","",1000,-5,5);

  h_b_reco_nMuons = new TH1D("h_b_reco_nMuons","",10,0,10);
  h_b_reco_njets = new TH1D("h_b_reco_njets","",10,0,10);
  h_b_reco_nbjetsCSVM = new TH1D("h_b_reco_nbjetsCSVM","",10,0,10);
  h_b_reco_bestTopMass = new TH1D("h_b_reco_bestTopMass","",1000,0,500);
  h_b_reco_MET = new TH1D("h_b_reco_MET","",1000,0,1000);
  h_b_reco_jetpt4 = new TH1D("h_b_reco_jetpt4","",1000,0,1000);
  h_b_reco_jetpt2 = new TH1D("h_b_reco_jetpt2","",1000,0,1000);
  h_b_reco_jet1_met_phi_diff = new TH1D("h_b_reco_jet1_met_phi_diff","",1000,-5,5);
  h_b_reco_jet2_met_phi_diff = new TH1D("h_b_reco_jet2_met_phi_diff","",1000,-5,5);
  h_b_reco_jet3_met_phi_diff = new TH1D("h_b_reco_jet3_met_phi_diff","",1000,-5,5);

  //closure plots on different variables
  h_pred_met = new TH1D("h_pred_met","",50,0,1000);
  h_pred_njets = new TH1D("h_pred_njets","",20,0,20);
  h_pred_mt2 = new TH1D("h_pred_mt2","",50,0,1000);
  h_pred_topmass = new TH1D("h_pred_topmass","",100,50,300);
  h_pred_ht = new TH1D("h_pred_ht","",150,0,3000);
  h_pred_mht = new TH1D("h_pred_mht","",50,0,1000);
  h_pred_ntopjets = new TH1D("h_pred_ntopjets","",20,0,20);
  h_pred_nbjets = new TH1D("h_pred_nbjets","",20,0,20);

  h_exp_met = new TH1D("h_exp_met","",50,0,1000);
  h_exp_njets = new TH1D("h_exp_njets","",20,0,20);
  h_exp_mt2 = new TH1D("h_exp_mt2","",50,0,1000);
  h_exp_topmass = new TH1D("h_exp_topmass","",100,50,300);
  h_exp_ht = new TH1D("h_exp_ht","",150,0,3000);
  h_exp_mht = new TH1D("h_exp_mht","",50,0,1000);
  h_exp_ntopjets = new TH1D("h_exp_ntopjets","",20,0,20);
  h_exp_nbjets = new TH1D("h_exp_nbjets","",20,0,20);

  h_inverted_met = new TH1D("h_inverted_met","",50,0,1000);
  h_inverted_njets = new TH1D("h_inverted_njets","",20,0,20);
  h_inverted_mt2 = new TH1D("h_inverted_mt2","",50,0,1000);
  h_inverted_topmass = new TH1D("h_inverted_topmass","",100,50,300);
  h_inverted_ht = new TH1D("h_inverted_ht","",150,0,3000);
  h_inverted_mht = new TH1D("h_inverted_mht","",50,0,1000);
  h_inverted_ntopjets = new TH1D("h_inverted_ntopjets","",20,0,20);
  h_inverted_nbjets = new TH1D("h_inverted_nbjets","",20,0,20);

  h_exp_sb = new TH1D("h_exp_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_pred_sb = new TH1D("h_pred_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  //study mt2 met correlation, run on the full QCD HT bin sample
  h_met_mt2  = new TH2D("h_met_mt2","",30,0,300,40,0,400);
  h_mt2_cutmet0 = new TH1D("h_mt2_cutmet0","",50,0,1000);
  h_mt2_cutmet50 = new TH1D("h_mt2_cutmet50","",50,0,1000); 
  h_mt2_cutmet100 = new TH1D("h_mt2_cutmet100","",50,0,1000); 
  h_mt2_cutmet150 = new TH1D("h_mt2_cutmet150","",50,0,1000); 
  h_mt2_cutmet200 = new TH1D("h_mt2_cutmet200","",50,0,1000); 
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
