#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <utility>

#include "TH1D.h"
#include "TH2D.h"
#include "THStack.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TChain.h"
#include "TList.h"

#include "Math/QuantFuncMathCore.h"
#include "TMath.h"

#include "SusyAnaTools/Tools/NTupleReader.h"
#include "SusyAnaTools/Tools/searchBins.h"

//#include "CMSStylePlot/CMS_lumi.h"

#include "QCDFactors.h"
#include "QCDReWeighting.h"
#include "QCDBinFunction.h"
#include "CalHistgram.h"
#include "ClosureHistgram.h"
#include "BasicCheckHistgram.h"
#include "SBCheckHistgram.h"
#include "TriggerEff.h"

//Scale Tfactors with the Tfactor from Real Data
#include "ConstantsSnippet.h"
//#include "CMSStylePlot/tdrstyle.h"
#include "QCDHardCodedInput/TFactorsHeader.h"
#include "QCDHardCodedInput/DataDriven.h"

//all the root file for plotting will go to this directory
std::string dir_out = "RootForPlotting/";

//QCD background model bag
QCDBGModel myQCDBGModel;
//search bin definition, with era
//SearchBins mySearchBins("SB_59_2016");
//SearchBins mySearchBins("SB_Aggregate_ICHEP_2016");
SearchBins mySearchBins("SB_v1_2017");
//Trigger Eff
TriggerEff myTriggerEff;
//overall scale for all plots, will be set to be 1 if no special need
const double Scale = 1;
//const double Scale = 591.5/2153.736;


//AUX functions for non closure unc
double IntegrateTH1D(double xdn, double xup, TH1D *&hist)
{
  int bindn = hist->GetXaxis()->FindBin(xdn);
  int binup = hist->GetXaxis()->FindBin(xup);
  double error = -1;
  double integral = hist->IntegralAndError(bindn,binup,error);
  //std::cout << bindn << " " << binup << " " << integral << " " << error << std::endl;
  return integral;
}

double ErrorTH1D(double xdn, double xup, TH1D *&hist)
{ 
  int bindn = hist->GetXaxis()->FindBin(xdn);
  int binup = hist->GetXaxis()->FindBin(xup);
  double error = -1;
  double integral = hist->IntegralAndError(bindn,binup,error); 
  //std::cout << bindn << " " << binup << " " << integral << " " << error << std::endl;
  return error;
}

double OneBinNonClosureUnc(double pred, double exp, double pred_err, double exp_err)
{
  if ( (pred > 0) && (exp > 0) )
  {
    double r = exp/pred;
    double e = std::sqrt( exp_err*exp_err + pred_err*pred_err*r*r ) / pred;
    return std::max( std::abs(e) , std::abs((exp-pred)/pred) );
  }
  return -5;
}
//Important function to get non closure uncertainty
void getNonClosureUnc(double (&QCD_NonClosure_relative_err)[NSEARCH_BINS])
{
  TFile * finPred; finPred = TFile::Open("RootForPlotting/PredQCDMC.root");
  TFile * finExp; finExp = TFile::Open("RootForPlotting/ExpQCD.root");
  
  /*
  TH1D * h_pred;
  TH1D * h_exp;

  h_pred = (TH1D*)finPred->Get("h_pred_sb")->Clone();
  h_exp = (TH1D*)finExp->Get("h_exp_sb")->Clone();

  for (int j = 1; j < NSEARCH_BINS+1 ; j++)
  {
    double pred = h_pred->GetBinContent(j);
    double exp = h_exp->GetBinContent(j);
    double pred_err = h_pred->GetBinError(j);
    double exp_err = h_exp->GetBinError(j);
    //std::cout << "i: " << i << " pred_err: " << pred_err << " exp_err: " << exp_err << std::endl;
    double e = 5;
    if ( (pred > 0) && (exp > 0) )
    {
      double r = exp/pred;
      e = std::sqrt( exp_err*exp_err + pred_err*pred_err*r*r ) / pred;
      QCD_NonClosure_relative_err[j-1] = std::max( std::abs(e) , std::abs((exp-pred)/pred) );
      //std::cout << "j: " << j << " Pred: "<< pred << " Exp: "<< exp << " Error: " << e << std::endl;
    }
    else if( j!=1 && ((pred <= 0) || (exp <= 0)) ){ QCD_NonClosure_relative_err[j-1] = QCD_NonClosure_relative_err[j-2]; }
    else { std::cout << "First Bin have werid behavior, too bad, WTF??!!" << std::endl; return ;}
  }
  return ;
  */

  TH1D *h_pred_met, *h_pred_mt2, *h_pred_ht, *h_pred_ntopjets, *h_pred_nbjets;
  TH1D *h_exp_met, *h_exp_mt2, *h_exp_ht, *h_exp_ntopjets, *h_exp_nbjets;
  h_pred_met = (TH1D*)finPred->Get("h_pred_met")->Clone();
  h_exp_met = (TH1D*)finExp->Get("h_exp_met")->Clone();
  h_pred_mt2 = (TH1D*)finPred->Get("h_pred_mt2")->Clone();
  h_exp_mt2 = (TH1D*)finExp->Get("h_exp_mt2")->Clone();
  h_pred_ht = (TH1D*)finPred->Get("h_pred_ht")->Clone();
  h_exp_ht = (TH1D*)finExp->Get("h_exp_ht")->Clone();
  h_pred_ntopjets = (TH1D*)finPred->Get("h_pred_ntopjets")->Clone();
  h_exp_ntopjets = (TH1D*)finExp->Get("h_exp_ntopjets")->Clone();
  h_pred_nbjets = (TH1D*)finPred->Get("h_pred_nbjets")->Clone();
  h_exp_nbjets = (TH1D*)finExp->Get("h_exp_nbjets")->Clone();
  
  for(int i = 0; i < NSEARCH_BINS; i++)
  {
    SearchBins::searchBinDef outBinDef; mySearchBins.find_BinBoundaries( i, outBinDef );
    //MET
    double intup_met = -10; outBinDef.met_hi_>0 ? intup_met = outBinDef.met_hi_ : intup_met = h_pred_met->GetXaxis()->GetXmax();
    double intdn_met = outBinDef.met_lo_;
    //if(outBinDef.met_hi_<0) std::cout << intup_met << std::endl;
    //Tricky things in MT2/HT
    double intup_mt2 = -10; outBinDef.MT2_hi_>0 ? intup_mt2 = outBinDef.MT2_hi_ : intup_mt2 = h_pred_mt2->GetXaxis()->GetXmax();
    double intdn_mt2 = outBinDef.MT2_lo_;
    double intup_ht = -10; outBinDef.MT2_hi_>0 ? intup_ht = outBinDef.MT2_hi_ : intup_ht = h_pred_ht->GetXaxis()->GetXmax();
    double intdn_ht = outBinDef.MT2_lo_;
    //Ntop,Nbot
    double intup_ntop = -10; outBinDef.top_hi_>0 ? intup_ntop = outBinDef.top_hi_ : intup_ntop = h_pred_ntopjets->GetXaxis()->GetXmax();
    double intdn_ntop = outBinDef.top_lo_;
    double intup_nbot = -10; outBinDef.bJet_hi_>0 ? intup_nbot = outBinDef.bJet_hi_ : intup_nbot = h_pred_nbjets->GetXaxis()->GetXmax();
    double intdn_nbot = outBinDef.bJet_lo_;

    //search bin uncertainty variables
    double nc_unc_met = -0.2, nc_unc_mt2 = -0.3, nc_unc_ht = -0.1, nc_unc_ntop = -0.1, nc_unc_nbot = -0.1;

    double int_pred_met = IntegrateTH1D(intdn_met, intup_met, h_pred_met);
    double int_exp_met  = IntegrateTH1D(intdn_met, intup_met, h_exp_met);
    double err_pred_met = ErrorTH1D(intdn_met, intup_met, h_pred_met);
    double err_exp_met  = ErrorTH1D(intdn_met, intup_met, h_exp_met);

    double int_pred_mt2 = IntegrateTH1D(intdn_mt2, intup_mt2, h_pred_mt2);
    double int_exp_mt2  = IntegrateTH1D(intdn_mt2, intup_mt2, h_exp_mt2);
    double err_pred_mt2 = ErrorTH1D(intdn_mt2, intup_mt2, h_pred_mt2);
    double err_exp_mt2  = ErrorTH1D(intdn_mt2, intup_mt2, h_exp_mt2);
    double int_pred_ht = IntegrateTH1D(intdn_ht, intup_ht, h_pred_ht);
    double int_exp_ht  = IntegrateTH1D(intdn_ht, intup_ht, h_exp_ht);
    double err_pred_ht = ErrorTH1D(intdn_ht, intup_ht, h_pred_ht);
    double err_exp_ht  = ErrorTH1D(intdn_ht, intup_ht, h_exp_ht);

    double int_pred_nbot = IntegrateTH1D(intdn_nbot, intup_nbot, h_pred_nbjets);
    double int_exp_nbot  = IntegrateTH1D(intdn_nbot, intup_nbot, h_exp_nbjets);
    double err_pred_nbot = ErrorTH1D(intdn_nbot, intup_nbot, h_pred_nbjets);
    double err_exp_nbot  = ErrorTH1D(intdn_nbot, intup_nbot, h_exp_nbjets);
    double int_pred_ntop = IntegrateTH1D(intdn_ntop, intup_ntop, h_pred_ntopjets);
    double int_exp_ntop  = IntegrateTH1D(intdn_ntop, intup_ntop, h_exp_ntopjets);
    double err_pred_ntop = ErrorTH1D(intdn_ntop, intup_ntop, h_pred_ntopjets);
    double err_exp_ntop  = ErrorTH1D(intdn_ntop, intup_ntop, h_exp_ntopjets);

    nc_unc_met = OneBinNonClosureUnc(int_pred_met, int_exp_met, err_pred_met, err_exp_met);

    nc_unc_mt2 = OneBinNonClosureUnc(int_pred_mt2, int_exp_mt2, err_pred_mt2, err_exp_mt2);
    nc_unc_ht = OneBinNonClosureUnc(int_pred_ht, int_exp_ht, err_pred_ht, err_exp_ht);

    nc_unc_ntop = OneBinNonClosureUnc(int_pred_ntop, int_exp_ntop, err_pred_ntop, err_exp_ntop);
    nc_unc_nbot = OneBinNonClosureUnc(int_pred_nbot, int_exp_nbot, err_pred_nbot, err_exp_nbot);

    bool ismt2sb = false, ishtsb = false;
    ismt2sb = (outBinDef.top_lo_==1 && outBinDef.top_hi_==2 && outBinDef.bJet_lo_==1 && outBinDef.bJet_hi_==2)
           || (outBinDef.top_lo_==1 && outBinDef.top_hi_==2 && outBinDef.bJet_lo_==2 && outBinDef.bJet_hi_==3)
           || (outBinDef.top_lo_==2 && outBinDef.top_hi_==3 && outBinDef.bJet_lo_==1 && outBinDef.bJet_hi_==2)
           || (outBinDef.top_lo_==2 && outBinDef.top_hi_==3 && outBinDef.bJet_lo_==2 && outBinDef.bJet_hi_==3);
    ishtsb = outBinDef.top_lo_==3 || outBinDef.bJet_lo_==3;
    if( (ismt2sb && ishtsb) || (!ismt2sb && !ishtsb) ){ std::cout << "error sb : " << i << std::endl; }

    if     (ismt2sb && !ishtsb) QCD_NonClosure_relative_err[i] = std::sqrt(nc_unc_met*nc_unc_met+nc_unc_mt2*nc_unc_mt2+nc_unc_ntop*nc_unc_ntop+nc_unc_nbot*nc_unc_nbot);
    else if(!ismt2sb && ishtsb) QCD_NonClosure_relative_err[i] = std::sqrt(nc_unc_met*nc_unc_met+nc_unc_ht*nc_unc_ht+nc_unc_ntop*nc_unc_ntop+nc_unc_nbot*nc_unc_nbot);

    if(ismt2sb && !ishtsb)
    { 
      if(!(nc_unc_met>0 && nc_unc_mt2>0 && nc_unc_ntop>0 && nc_unc_nbot>0))
      { 
        QCD_NonClosure_relative_err[i]=QCD_NonClosure_relative_err[i-1];
        //QCD_NonClosure_relative_err[i]=-1; 
        //std::cout<<"??"<<std::endl; 
      } 
    }
    else if(!ismt2sb && ishtsb)
    { 
      if(!(nc_unc_met>0 && nc_unc_ht>0  && nc_unc_ntop>0 && nc_unc_nbot>0))
      { 
        QCD_NonClosure_relative_err[i]=QCD_NonClosure_relative_err[i-1];
        //QCD_NonClosure_relative_err[i]=-1; 
        //std::cout<<"??"<<std::endl; 
      } 
    }
  }
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
