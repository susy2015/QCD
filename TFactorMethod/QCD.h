#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stdlib.h>

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
  
  for (int i = 0; i < NSEARCH_BINS ; i++)
  {
    SearchBins::searchBinDef outBinDef; mySearchBins.find_BinBoundaries( i, outBinDef );
    //double intup_met = -10; outBinDef.met_hi_>0 ? intup_met = (outBinDef.met_hi_ + outBinDef.met_lo_)/2 : LastOption_met = outBinDef.met_lo_+10;
    double intdn_met = outBinDef.met_lo_;
    //double intdn_met = -10; outBinDef.MT2_hi_>0 ? LastOption_mt2ht = (outBinDef.MT2_hi_ + outBinDef.MT2_lo_)/2 : LastOption_mt2ht = outBinDef.MT2_lo_+10;
    QCD_NonClosure_relative_err[i] = 0.2;
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
