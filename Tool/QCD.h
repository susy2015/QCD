#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "TH1D.h"
#include "TH2D.h"
#include "THStack.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TChain.h"
#include "TList.h"
#include "TF1.h"
#include "TFrame.h"
#include "TGraphErrors.h"
#include "TVirtualFitter.h"

#include "Math/QuantFuncMathCore.h"
#include "TMath.h"

#include "SusyAnaTools/Tools/NTupleReader.h"
#include "SusyAnaTools/Tools/baselineDef.h"

#include "QCDBinFunction.h"
#include "QCDReWeighting.h"
//Scale Tfactors with the Tfactor from Real Data
#include "TFactorsfromDataHeader.h"

std::string dir_out = "/eos/uscms/store/group/lpcsusyhad/hua/AnaOut_QCD/";

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
  TH1D *h_pred_met, *h_pred_njets30, *h_pred_njets50, *h_pred_mt2, *h_pred_ht, *h_pred_mht, *h_pred_ntopjets, *h_pred_nbjets;
  TH1D *h_exp_met, *h_exp_njets30, *h_exp_njets50, *h_exp_mt2, *h_exp_ht, *h_exp_mht, *h_exp_ntopjets, *h_exp_nbjets;
  TH1D *h_exp_sb, *h_pred_sb;
};

void ClosureHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");
  //closure plots on different variables
  h_pred_met = new TH1D("h_pred_met","",50,0,1000);
  h_pred_njets30 = new TH1D("h_pred_njets30","",20,0,20);
  h_pred_njets50 = new TH1D("h_pred_njets50","",20,0,20);
  h_pred_mt2 = new TH1D("h_pred_mt2","",50,0,1000);
  h_pred_ht = new TH1D("h_pred_ht","",150,0,3000);
  h_pred_mht = new TH1D("h_pred_mht","",50,0,1000);
  h_pred_ntopjets = new TH1D("h_pred_ntopjets","",20,0,20);
  h_pred_nbjets = new TH1D("h_pred_nbjets","",20,0,20);

  h_exp_met = new TH1D("h_exp_met","",50,0,1000);
  h_exp_njets30 = new TH1D("h_exp_njets30","",20,0,20);
  h_exp_njets50 = new TH1D("h_exp_njets50","",20,0,20);
  h_exp_mt2 = new TH1D("h_exp_mt2","",50,0,1000);
  h_exp_ht = new TH1D("h_exp_ht","",150,0,3000);
  h_exp_mht = new TH1D("h_exp_mht","",50,0,1000);
  h_exp_ntopjets = new TH1D("h_exp_ntopjets","",20,0,20);
  h_exp_nbjets = new TH1D("h_exp_nbjets","",20,0,20);

  h_exp_sb = new TH1D("h_exp_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_pred_sb = new TH1D("h_pred_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  return ;
}

class TFactorsUncHistgram
{
 public:
  void BookHistgram(const char *);
  TFile *oFile;
  //closure plots on different variables and search bins
  TH1D *h_pred_sb_TFactorsUnc[MET_BINS][MT2_BINS];
};

void TFactorsUncHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");
  for(int i=0;i<MET_BINS;i++)
  {
    for(int j=0;j<MT2_BINS;j++)
    {
      std::string met_index = std::to_string(i);
      std::string mt2_index = std::to_string(j);
      h_pred_sb_TFactorsUnc[i][j] = new TH1D( ("h_pred_sb_TFactorsUnc_" + met_index + mt2_index).c_str(),"",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
    }
  }
  return ;
}

class CombineHistgram
{
 public:
  void BookHistgram(const char *);
  TFile *oFile;
  //Plots for zhenbin
  TH1D *h_zb_met, *h_zb_njets30, *h_zb_njets50, *h_zb_mt2, *h_zb_ht, *h_zb_ntopjets, *h_zb_nbjets;
  TH1D *h_zb_sb;

  //Plots for zhenbin, top tagger study
  TH1D *h_zb_htnjets30, *h_zb_htnjets50, *h_zb_htntopjets, *h_zb_htnbjets, *h_zb_htmet, *h_zb_htht;
  TH1D *h_zb_httoppt, *h_zb_httopeta, *h_zb_httopphi, *h_zb_httopmass;

  TH1D *h_cutflow;
};

void CombineHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");

  h_zb_met = new TH1D("hMET","MET;#slash{E}_{T} [GeV];Events",24,200,800);
  h_zb_njets30 = new TH1D("hNJets30","NJets30;N_{jets} (p_{T} > 30);Events",10,0,10);
  h_zb_njets50 = new TH1D("hNJets50","NJets30;N_{jets} (p_{T} > 50);Events",10,0,10);
  h_zb_mt2 = new TH1D("hMT2","MT2;M_{T2} [GeV];Events",24,200,800);
  h_zb_ht = new TH1D("hHT","HT;H_{T} [GeV];Events",20,500,1000);
  h_zb_ntopjets = new TH1D("hNTops","NTops;N_{tops};Events",5,0,5);
  h_zb_nbjets = new TH1D("hNbJets","NbJets;N_{bjets};Events",5,0,5);

  h_zb_sb = new TH1D("hSearchBins","Search Bins;Search Bin;Events",NSEARCH_BINS,0,NSEARCH_BINS);

  h_zb_htnjets30 = new TH1D("hHTNJets30"    , "NJets30;N_{jets} (p_{T} > 30);Events" , 10 , 0    , 10);   // "cntNJetsPt30Eta24"
  h_zb_htnjets50 = new TH1D("hHTNJets50"    , "NJets50;N_{jets} (p_{T} > 50);Events" , 10 , 0    , 10);   // "cntNJetsPt50Eta24"
  h_zb_htntopjets = new TH1D("hHTNTops"      , "NTops;N_{tops};Events"                , 5  , 0    , 5);    // "nTopCandSortedCnt"
  h_zb_htnbjets = new TH1D("hHTNbJets"     , "NbJets;N_{bjets};Events"              , 5  , 0    , 5);    // "cntCSVS"
  h_zb_htmet = new TH1D("hHTMET"        , "MET;#slash{E}_{T} [GeV];Events"       , 24 , 200  , 800);  // "met"
  h_zb_htht = new TH1D("hHTHT"         , "HT;H_{T} [GeV];Events"                , 20 , 500  , 1000); // "HT"

  h_zb_httoppt = new TH1D("hHTTopPT"   , "Reco Top PT;p_{T} [GeV];Events" , 50 , 0  , 1000); 
  h_zb_httopeta = new TH1D("hHTTopEta"  , "Reco Top Eta;#eta;Events" ,       20 , -5 , 5);
  h_zb_httopphi = new TH1D("hHTTopPhi"  , "Reco Top Phi;#phi;Events" ,       20 , -5 , 5);
  h_zb_httopmass = new TH1D("hHTTopMass" , "Reco Top Mass;Mass;Events" ,      40 , 80 , 280);

  return ;
}

#define BCBin 6

class BasicCheckHistgram
{
 public:
  void BookHistgram(const char *);

  TFile *oFile;

  TH1D *h_b_met_MC[BCBin], *h_b_mt2_MC[BCBin], *h_b_ntopjets_MC[BCBin], *h_b_nbjets_MC[BCBin];
  TH1D *h_b_ht_MC[BCBin], *h_b_mht_MC[BCBin], *h_b_njets30_MC[BCBin], *h_b_njets50_MC[BCBin];

  TH1D *h_b_met_Data, *h_b_mt2_Data, *h_b_ntopjets_Data, *h_b_nbjets_Data;
  TH1D *h_b_ht_Data, *h_b_mht_Data, *h_b_njets30_Data, *h_b_njets50_Data;

  //TH1D *h_b_mt2_nbnt, *h_b_mt2_ybyt, *h_b_met_nbnt, *h_b_met_ybyt;
  //TH1D *h_b_dphi0_nbnt, *h_b_dphi0_ybyt, *h_b_dphi1_nbnt, *h_b_dphi1_ybyt, *h_b_dphi2_nbnt, *h_b_dphi2_ybyt;
  //TH1D *h_inverted_met, *h_inverted_njets, *h_inverted_mt2, *h_inverted_ht, *h_inverted_mht, *h_inverted_ntopjets, *h_inverted_nbjets;
};

void BasicCheckHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");

  for( Int_t i = 0 ; i < BCBin ; i++ )
  {
    std::string smalltag;

    if (i == 0) smalltag = "TTJets";
    else if (i == 1) smalltag = "SingleTop";
    else if (i == 2) smalltag = "WJets";
    else if (i == 3) smalltag = "ZJets";
    else if (i == 4) smalltag = "QCD";
    else smalltag = "TTZ";

    h_b_met_MC[i] = new TH1D( ("h_b_met_MC_" + smalltag).c_str(),"",20,150,550);
    h_b_njets30_MC[i] = new TH1D( ("h_b_njets30_MC_" + smalltag).c_str(),"",10,4,14);
    h_b_njets50_MC[i] = new TH1D( ("h_b_njets50_MC_" + smalltag).c_str(),"",15,2,17);
    h_b_mt2_MC[i] = new TH1D( ("h_b_mt2_MC_" + smalltag).c_str(),"",20,200,600);
    h_b_ht_MC[i] = new TH1D( ("h_b_ht_MC_" + smalltag).c_str(),"",50,500,3000);
    h_b_mht_MC[i] = new TH1D( ("h_b_mht_MC_" + smalltag).c_str(),"",50,0,1000);
    h_b_ntopjets_MC[i] = new TH1D( ("h_b_ntopjets_MC_" + smalltag).c_str(),"",5,1,6);
    h_b_nbjets_MC[i] = new TH1D( ("h_b_nbjets_MC_" + smalltag).c_str(),"",5,1,6);

    h_b_met_MC[i]->SetFillColor(i+2);
    h_b_mt2_MC[i]->SetFillColor(i+2);
    h_b_ntopjets_MC[i]->SetFillColor(i+2);
    h_b_nbjets_MC[i]->SetFillColor(i+2);
    h_b_ht_MC[i]->SetFillColor(i+2);
    h_b_mht_MC[i]->SetFillColor(i+2);
    h_b_njets30_MC[i]->SetFillColor(i+2);
    h_b_njets50_MC[i]->SetFillColor(i+2);

    h_b_met_MC[i]->SetLineColor(i+2);
    h_b_mt2_MC[i]->SetLineColor(i+2);
    h_b_ntopjets_MC[i]->SetLineColor(i+2);
    h_b_nbjets_MC[i]->SetLineColor(i+2);
    h_b_ht_MC[i]->SetLineColor(i+2);
    h_b_mht_MC[i]->SetLineColor(i+2);
    h_b_njets30_MC[i]->SetLineColor(i+2);
    h_b_njets50_MC[i]->SetLineColor(i+2);
  }

  h_b_met_Data = new TH1D("h_b_met_Data","",20,150,550);
  h_b_njets30_Data = new TH1D("h_b_njets30_Data","",10,4,14);
  h_b_njets50_Data = new TH1D("h_b_njets50_Data","",15,2,17);
  h_b_mt2_Data = new TH1D("h_b_mt2_Data","",20,200,600);
  h_b_ht_Data = new TH1D("h_b_ht_Data","",50,500,3000);
  h_b_mht_Data = new TH1D("h_b_mht_Data","",50,0,1000);
  h_b_ntopjets_Data = new TH1D("h_b_ntopjets_Data","",5,1,6);
  h_b_nbjets_Data = new TH1D("h_b_nbjets_Data","",5,1,6);

  return ;
}

class QCDFactors
{
 public:
  double nQCDNormal_MC[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}}, nQCDInverted_MC[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}};
  double nQCDNormal[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}}, nQCDInverted[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}};
  double nQCDNormal_all[MET_BINS][MT2_BINS] = {{0}}, nQCDInverted_all[MET_BINS][MT2_BINS] = {{0}};
  double nQCDNormal_all_err[MET_BINS][MT2_BINS] = {{0}}, nQCDInverted_all_err[MET_BINS][MT2_BINS] = {{0}};
  double QCDTFactor[MET_BINS][MT2_BINS] = {{0}}, QCDTFactor_err[MET_BINS][MT2_BINS] = {{0}};//Tfactors calculated from QCD MC
  double QCDTFactorFit[MET_BINS][MT2_BINS] = {{0}}, QCDTFactorFit_err[MET_BINS][MT2_BINS] = {{0}};//Tfactors smoothed by linear fit
  double QCDTFactorScaled[MET_BINS][MT2_BINS] = {{0}}, QCDTFactorScaled_err[MET_BINS][MT2_BINS] = {{0}};//Tfactors scaled by low MET bin Tfactor(from Data) and linear fit 
  double MET_sum[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}}, MET_sum_weight[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}};
  double MET_sum_all[MET_BINS][MT2_BINS] = {{0}}, MET_sum_weight_all[MET_BINS][MT2_BINS] = {{0}};
  double MET_mean[MET_BINS][MT2_BINS] = {{0}}, MET_mean_err[MET_BINS][MT2_BINS] = {{0}};

  double nQCDNormalData_all[MT2_BINS] = {0}, nQCDInvertedData_all[MT2_BINS] = {0};
  double nQCDNormalData_all_err[MT2_BINS] = {0}, nQCDInvertedData_all_err[MT2_BINS] = {0};
  double QCDTFactorData[MT2_BINS] = {0}, QCDTFactorData_err[MT2_BINS] = {0};

  double QCDWeights[QCD_BINS] = {0};
  double nQCD_exp_sb[NSEARCH_BINS] = {0}, nQCD_pred_sb[NSEARCH_BINS] = {0};
  double nQCD_exp_sb_MC[QCD_BINS][NSEARCH_BINS] = {{0}}, nQCD_pred_sb_MC[QCD_BINS][NSEARCH_BINS] = {{0}};
  double nQCD_exp_sb_err[NSEARCH_BINS] = {0}, nQCD_pred_sb_err[NSEARCH_BINS] = {0};

  void NumbertoTFactor();
  void TFactorFit();
  void TFactorScale();
  void printQCDFactorInfo(); 
  void printTFactorsfromDataHeader();
  void printTFactorsHeader();
  void printQCDClosureExp ( ClosureHistgram& myClosureHistgram );
  void printQCDClosurePred( ClosureHistgram& myClosureHistgram );
  void TFactorsPlotsGen();
  void CountingPlotsGen();
  void printSBInfo();

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
}

Double_t fitf(Double_t *v, Double_t *par)
{
  //Double_t arg = 0;
  //if (par[2] != 0) arg = (v[0] - par[1])/par[2];

  //Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
  //return fitval;
  Double_t arg = 0;
  arg = v[0];

  Double_t fitval = par[0] + par[1]*arg;
  return fitval;
}

void QCDFactors::TFactorFit()
{
  for(int i = 0; i < MT2_BINS; i++)
  {
    std::string pname = "TFactorfit_MT2BIN" + std::to_string(i);

    TCanvas *c = new TCanvas("c",pname.c_str(),200,10,700,500);

    c->SetFillColor(42);
    c->SetGrid();

    const Int_t n = MET_BINS;
    Double_t x[n], y[n], ex[n], ey[n];
    for (int j = 0 ; j < MET_BINS ; j++)
    {
      x[j] = MET_mean[j][i];
      y[j] = QCDTFactor[j][i];
      ex[j] = MET_mean_err[j][i];
      ey[j] = QCDTFactor_err[j][i];
    }
  
    TGraph *gr = new TGraphErrors(n,x,y,ex,ey);

    gr->SetLineColor(2);
    gr->SetLineWidth(4);
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    gr->SetTitle(pname.c_str());
    gr->GetXaxis()->SetTitle("mean MET[GeV]");
    gr->GetYaxis()->SetTitle("Translation Factor");

    //create a function with 2 parameters in the range [0,1000]
    TF1 *func = new TF1("fit",fitf,0,1000,2);
    func->SetParameters(0,0.01);
    func->SetParNames("Offset","Slope");
    gr->Fit("fit");

    //Create a TGraphErrors to hold the confidence intervals
    TGraphErrors *grint = new TGraphErrors(n);
    for (int j=0;j<n; j++){ grint->SetPoint(j, gr->GetX()[j], 0); }
    //Compute the confidence intervals at the x points of the created graph
    (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint);
    //Now the "grint" graph contains function values as its y-coordinates
    //and confidence intervals as the errors on these coordinates
    //Draw the graph, the function and the confidence intervals
    grint->SetLineColor(2);
    grint->SetFillColor(3);
    grint->SetFillStyle(3010);
    grint->SetTitle(pname.c_str());
    grint->GetXaxis()->SetTitle("mean MET[GeV]");
    grint->GetYaxis()->SetTitle("Translation Factor");
    grint->Draw("ap3");
    gr->Draw("psame");

    c->SaveAs( (dir_out + pname + ".png").c_str() );
    c->SaveAs( (dir_out + pname + ".pdf").c_str() );
    c->SaveAs( (dir_out + pname + ".C").c_str() );


    //Get value and uncertainty for Fit TFactor
    for (int j = 0 ; j < MET_BINS ; j++)
    {
      QCDTFactorFit[j][i] = func->Eval( MET_mean[j][i] );
      //temporary solution
      QCDTFactorFit_err[j][i] = grint->GetErrorY(j);
    }
  }
  return ;
}

void QCDFactors::TFactorScale()
{
  double TFactorsdiff[MT2_BINS] = {0};

  for(int i=0;i<MT2_BINS;i++)
  {
    TFactorsdiff[i] = head_QCDTFactorData[i] - QCDTFactorFit[0][i];
  }

  for(int i=0;i<MET_BINS;i++)
  {
    for(int j=0;j<MT2_BINS;j++)
    {
      QCDTFactorScaled[i][j] = QCDTFactorFit[i][j] + TFactorsdiff[j];
      if( QCDTFactorScaled[i][j] < 0 )
      { 
        std::cout << "METBIN,MT2BIN,TFactorScaled: " << i << "," << j << "," << QCDTFactorScaled[i][j] << std::endl;
        QCDTFactorScaled[i][j] = 0.000000000001;
      }
      //uncertainty of scaled tfactor have 3 parts: statistical, fit, and data MC difference
      QCDTFactorScaled_err[i][j] = std::sqrt( QCDTFactor_err[i][j]*QCDTFactor_err[i][j] + QCDTFactorFit_err[i][j]*QCDTFactorFit_err[i][j] + TFactorsdiff[j]*TFactorsdiff[j] );
    }
  }

  return ;
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
      std::cout << "PreFit, METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << QCDTFactor[i_cal][j_cal] << "(" << QCDTFactor_err[i_cal][j_cal] << ")"<< std::endl;
      std::cout << "PostFit, METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << QCDTFactorFit[i_cal][j_cal] << "(" << QCDTFactorFit_err[i_cal][j_cal] << ")"<< std::endl;
      std::cout << "Scaled, METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << QCDTFactorScaled[i_cal][j_cal] << "(" << QCDTFactorScaled_err[i_cal][j_cal] << ")"<< std::endl;
    }
  }
}

void QCDFactors::printTFactorsfromDataHeader()
{
  std::ofstream TFactorsfromDataHeader;
  TFactorsfromDataHeader.open ( (dir_out + "TFactorsfromDataHeader.h").c_str() );
  
  int i_cal = 0;

  TFactorsfromDataHeader << "  const double head_QCDTFactorData[" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MT2_BINS ; i_cal++ )
  {
    if( i_cal == 0 ) { TFactorsfromDataHeader << "{"; }

    TFactorsfromDataHeader << QCDTFactorData[i_cal];
    
    if( i_cal != MT2_BINS-1 ) { TFactorsfromDataHeader << ","; }
    else { TFactorsfromDataHeader << "};"; }
  }
  return ;
}

void QCDFactors::printTFactorsHeader()
{
  std::ofstream TFactorsHeader;
  TFactorsHeader.open ( (dir_out + "TFactorsHeader.h").c_str() );

  int i_cal = 0;
  int j_cal = 0;

  TFactorsHeader << "  const double QCDTFactor[" << MET_BINS << "][" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for( j_cal = 0 ; j_cal < MT2_BINS ; j_cal++ )
    {
      if( i_cal == 0 && j_cal == 0 ) { TFactorsHeader << "{{"; }
      if( i_cal != 0 && j_cal == 0 ) { TFactorsHeader << "{"; }

      TFactorsHeader << QCDTFactor[i_cal][j_cal];
      if( j_cal != MT2_BINS-1 ) { TFactorsHeader << ","; }

      if( i_cal != MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "},"; }
      if( i_cal == MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "}};" << std::endl; }
    }
  }

  TFactorsHeader << "  const double QCDTFactor_err[" << MET_BINS << "][" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for( j_cal = 0 ; j_cal < MT2_BINS ; j_cal++ )
    {
      if( i_cal == 0 && j_cal == 0 ) { TFactorsHeader << "{{"; }
      if( i_cal != 0 && j_cal == 0 ) { TFactorsHeader << "{"; }

      TFactorsHeader << QCDTFactor_err[i_cal][j_cal];
      if( j_cal != MT2_BINS-1 ) { TFactorsHeader << ","; }

      if( i_cal != MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "},"; }
      if( i_cal == MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "}};" << std::endl; }
    }
  }

  TFactorsHeader << "  const double QCDTFactorFit[" << MET_BINS << "][" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for( j_cal = 0 ; j_cal < MT2_BINS ; j_cal++ )
    {
      if( i_cal == 0 && j_cal == 0 ) { TFactorsHeader << "{{"; }
      if( i_cal != 0 && j_cal == 0 ) { TFactorsHeader << "{"; }

      TFactorsHeader << QCDTFactorFit[i_cal][j_cal];
      if( j_cal != MT2_BINS-1 ) { TFactorsHeader << ","; }

      if( i_cal != MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "},"; }
      if( i_cal == MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "}};" << std::endl; }
    }
  }

  TFactorsHeader << "  const double QCDTFactorFit_err[" << MET_BINS << "][" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for( j_cal = 0 ; j_cal < MT2_BINS ; j_cal++ )
    {
      if( i_cal == 0 && j_cal == 0 ) { TFactorsHeader << "{{"; }
      if( i_cal != 0 && j_cal == 0 ) { TFactorsHeader << "{"; }

      TFactorsHeader << QCDTFactorFit_err[i_cal][j_cal];
      if( j_cal != MT2_BINS-1 ) { TFactorsHeader << ","; }

      if( i_cal != MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "},"; }
      if( i_cal == MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "}};" << std::endl; }
    }
  }

  TFactorsHeader << "  const double QCDTFactorScaled[" << MET_BINS << "][" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for( j_cal = 0 ; j_cal < MT2_BINS ; j_cal++ )
    {
      if( i_cal == 0 && j_cal == 0 ) { TFactorsHeader << "{{"; }
      if( i_cal != 0 && j_cal == 0 ) { TFactorsHeader << "{"; }

      TFactorsHeader << QCDTFactorScaled[i_cal][j_cal];
      if( j_cal != MT2_BINS-1 ) { TFactorsHeader << ","; }

      if( i_cal != MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "},"; }
      if( i_cal == MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "}};" << std::endl; }
    }
  }

  TFactorsHeader << "  const double QCDTFactorScaled_err[" << MET_BINS << "][" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for( j_cal = 0 ; j_cal < MT2_BINS ; j_cal++ )
    {
      if( i_cal == 0 && j_cal == 0 ) { TFactorsHeader << "{{"; }
      if( i_cal != 0 && j_cal == 0 ) { TFactorsHeader << "{"; }

      TFactorsHeader << QCDTFactorScaled_err[i_cal][j_cal];
      if( j_cal != MT2_BINS-1 ) { TFactorsHeader << ","; }

      if( i_cal != MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "},"; }
      if( i_cal == MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "}};" << std::endl; }
    }
  }

  TFactorsHeader.close();
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
    myClosureHistgram.h_pred_sb->SetBinContent( i_cal+1 , nQCD_pred_sb[i_cal] );
    myClosureHistgram.h_pred_sb->SetBinError( i_cal+1 , nQCD_pred_sb_err[i_cal] );
  }
  return ;
}

void QCDFactors::TFactorsPlotsGen()
{
  const std::string titre="CMS Simulation 2015, #sqrt{s} = 13 TeV";
  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);

  TCanvas *c_prefit = new TCanvas("c_prefit", "",0,51,1920,1004);
  c_prefit->SetFillColor(0);
  c_prefit->cd();

  TH2D *tfactors2dPreFit = new TH2D("tfactors_prefit","TFactors PreFit",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);

  int i_cal;
  int j_cal;

  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      tfactors2dPreFit->SetBinContent( i_cal+1 , j_cal+1, QCDTFactor[i_cal][j_cal] );
      tfactors2dPreFit->SetBinError( i_cal+1 , j_cal+1, QCDTFactor_err[i_cal][j_cal] );
    }
  }

  tfactors2dPreFit->SetTitle("");
  tfactors2dPreFit->SetXTitle("MET [GeV]");
  tfactors2dPreFit->SetYTitle("MT2 [GeV]");
  //tfactors2dPreFit->SetYTitle("NbJets");
  tfactors2dPreFit->SetStats(0);

  gStyle->SetPaintTextFormat("1.2f");
  tfactors2dPreFit->Draw("colztexte");

  title->Draw("same");

  c_prefit->SaveAs( (dir_out + "_tfactors2dPreFit.png").c_str() );
  c_prefit->SaveAs( (dir_out + "_tfactors2dPreFit.pdf").c_str() );
  c_prefit->SaveAs( (dir_out + "_tfactors2dPreFit.C").c_str() );
  c_prefit->Close();


  //Post fit Tfactor plot
  TCanvas *c_postfit = new TCanvas("c_postfit", "",0,51,1920,1004);
  c_postfit->SetFillColor(0);
  c_postfit->cd();

  TH2D *tfactors2dPostFit = new TH2D("tfactors_postfit","TFactors PostFit",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
  
  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  { 
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    { 
      tfactors2dPostFit->SetBinContent( i_cal+1 , j_cal+1, QCDTFactorFit[i_cal][j_cal] );
      tfactors2dPostFit->SetBinError( i_cal+1 , j_cal+1, QCDTFactorFit_err[i_cal][j_cal] );
    }
  }

  tfactors2dPostFit->SetTitle("");
  tfactors2dPostFit->SetXTitle("MET [GeV]");
  tfactors2dPostFit->SetYTitle("MT2 [GeV]");
  tfactors2dPostFit->SetStats(0);

  gStyle->SetPaintTextFormat("1.2f");
  tfactors2dPostFit->Draw("colztexte");

  title->Draw("same");

  c_postfit->SaveAs( (dir_out + "_tfactors2dPostFit.png").c_str() );
  c_postfit->SaveAs( (dir_out + "_tfactors2dPostFit.pdf").c_str() );
  c_postfit->SaveAs( (dir_out + "_tfactors2dPostFit.C").c_str() );
  c_postfit->Close();

  //Scaled Tfactor plot
  TCanvas *c_scaled = new TCanvas("c_scaled", "",0,51,1920,1004);
  c_scaled->SetFillColor(0);
  c_scaled->cd();

  TH2D *tfactors2dScaled = new TH2D("tfactors_scaled","TFactors Scaled",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);

  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      tfactors2dScaled->SetBinContent( i_cal+1 , j_cal+1, QCDTFactorScaled[i_cal][j_cal] );
      tfactors2dScaled->SetBinError( i_cal+1 , j_cal+1, QCDTFactorScaled_err[i_cal][j_cal] );
    }
  }

  tfactors2dScaled->SetTitle("");
  tfactors2dScaled->SetXTitle("MET [GeV]");
  tfactors2dScaled->SetYTitle("MT2 [GeV]");
  tfactors2dScaled->SetStats(0);

  gStyle->SetPaintTextFormat("1.2f");
  tfactors2dScaled->Draw("colztexte");

  title->Draw("same");

  c_scaled->SaveAs( (dir_out + "_tfactors2dScaled.png").c_str() );
  c_scaled->SaveAs( (dir_out + "_tfactors2dScaled.pdf").c_str() );
  c_scaled->SaveAs( (dir_out + "_tfactors2dScaled.C").c_str() );
  c_scaled->Close();

  return ;
}

void QCDFactors::CountingPlotsGen()
{
  TH2D *countNormal_MC  = new TH2D("countNormal_MC","countNormal_MC",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
  TH2D *countNormal  = new TH2D("countNormal","countNormal",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
  TH2D *countInverted_MC  = new TH2D("countInverted_MC","countInverted_MC",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
  TH2D *countInverted  = new TH2D("countInverted","countInverted",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
      
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

  std::ostringstream strs;
  strs << (LUMI/1000);
  std::string lumi_str = strs.str();
  const std::string titre="CMS Preliminary 2015, "+ lumi_str + " fb^{-1}, #sqrt{s} = 13 TeV";
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

  c->SaveAs( (dir_out + "_Allcount2d.png").c_str() );
  c->SaveAs( (dir_out + "_Allcount2d.pdf").c_str() );
  c->SaveAs( (dir_out + "_Allcount2d.C").c_str() );
  c->Close();

  return ;
}

void QCDFactors::printSBInfo()
{
  std::cout << "#QCD in Search Bins: " << std::endl;
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    std::cout << "Search Bin Id:" << i_cal << "; Exp: " << nQCD_exp_sb[i_cal] << "(" << nQCD_exp_sb_err[i_cal] << "); Pred: " << nQCD_pred_sb[i_cal] << "(" << nQCD_pred_sb_err[i_cal] << "); (exp - pred)/pred: " << (nQCD_exp_sb[i_cal] - nQCD_pred_sb[i_cal])/nQCD_pred_sb[i_cal] << std::endl;
  }
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
