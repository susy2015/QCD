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

#define MET_BINS 3
#define NJETS_BINS 1
#define QCD_BINS 7
#define NSEARCH_BINS 64
//############finish the definition of class AccRecoEffs######################
class QCDFactors
{
 public:
  double nQCDNormal_MC[QCD_BINS][MET_BINS][NJETS_BINS] = {{{0}}}, nQCDInverted_MC[QCD_BINS][MET_BINS][NJETS_BINS] = {{{0}}};
  double nQCDNormal[QCD_BINS][MET_BINS][NJETS_BINS] = {{{0}}}, nQCDInverted[QCD_BINS][MET_BINS][NJETS_BINS] = {{{0}}};
  double nQCDNormal_all[MET_BINS][NJETS_BINS] = {{0}}, nQCDInverted_all[MET_BINS][NJETS_BINS] = {{0}};
  double nQCDNormal_all_err[MET_BINS][NJETS_BINS] = {{0}}, nQCDInverted_all_err[MET_BINS][NJETS_BINS] = {{0}};
  double QCDTFactor[MET_BINS][NJETS_BINS] = {{0}}, QCDTFactor_err[MET_BINS][NJETS_BINS] = {{0}};
  double MET_sum[QCD_BINS][MET_BINS][NJETS_BINS] = {{{0}}}, MET_sum_weight[QCD_BINS][MET_BINS][NJETS_BINS] = {{{0}}};
  double MET_sum_all[MET_BINS][NJETS_BINS] = {{0}}, MET_sum_weight_all[MET_BINS][NJETS_BINS] = {{0}};
  double MET_mean[MET_BINS][NJETS_BINS] = {{0}}, MET_mean_err[MET_BINS][NJETS_BINS] = {{0}};

  double QCDWeights[QCD_BINS] = {0};
  double nQCD_exp_sb[NSEARCH_BINS] = {0}, nQCD_pred_sb[NSEARCH_BINS] = {0};

  TFile *TFactorFitPlots = new TFile("TFactorFitPlots.root", "recreate");

  void NumbertoTFactor();
  void TFactorFit();
  void printQCDFactorInfo(); 
  void printQCDClosure();

 private:
  double get_stat_Error(
                        double a,
                        double an
                       );
 
  double linearfitf(double *v, double *par);
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

int Set_metbin_number(
                       double met
                     )
{
  int metbin_num;

  if(met >= 175 && met < 200)
  {
    metbin_num = 0;
  }
  else if(met >= 200 && met < 350)
  {
    metbin_num = 1;
  }
  else if(met >= 350)
  {
    metbin_num = 2;
  }

  return metbin_num;
}

int Set_njetsbin_number(
                        int njets
                       )
{
  int njetsbin_num = 0;

  //if( njets == 4 || njets == 5 )
  //{
    //njetsbin_num = 0;
  //}
  //else if( njets == 6 || njets == 7 || njets == 8 )
  //{
    //njetsbin_num = 1;
  //}
  //else if(njets >= 6)
  //{
    //njetsbin_num = 1;
  //}

  return njetsbin_num;
}

