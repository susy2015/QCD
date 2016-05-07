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
#include "TF1.h"
#include "TFrame.h"
#include "TGraphErrors.h"
#include "TVirtualFitter.h"
#include "TMatrixDSym.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"

#include "Math/QuantFuncMathCore.h"
#include "TMath.h"

#include "SusyAnaTools/Tools/NTupleReader.h"
#include "SusyAnaTools/Tools/baselineDef.h"

#include "SSBinFunction.h"
#include "SSReWeighting.h"

std::string dir_out = "";

//############finish the definition of class AccRecoEffs######################
//baseline cut function definition
static BaselineVessel *myBaselineVessel;
void mypassBaselineFunc(NTupleReader& tr)
{
  (*myBaselineVessel)(tr);
}

class SSCSHistgram
{
 public:
  void BookHistgram(const char *);

  TFile *oFile;
  //NTop, NBot plots
  TH2D *h_ss_ntopnbot_MC_MuCS, *h_ss_ntopnbot_MC_ElCS;
  //MET MT2 plots after top bot
  TH2D *h_ss_metmt2_MC_MuCS[NTOPJETS_BINS][NBOTJETS_BINS], *h_ss_metmt2_MC_ElCS[NTOPJETS_BINS][NBOTJETS_BINS];
};

void SSCSHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");
  h_ss_ntopnbot_MC_MuCS = new TH2D("h_ss_ntopnbot_MC_MuCS","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);
  h_ss_ntopnbot_MC_ElCS = new TH2D("h_ss_ntopnbot_MC_ElCS","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);

  for(int i=0;i<NTOPJETS_BINS;i++)
  {
    for(int j=0;j<NBOTJETS_BINS;j++)
    { 
      std::string ntnbtag = "NT"+std::to_string(i+1)+"NB"+std::to_string(j+1);

      if(i==NTOPJETS_BINS-1)
      {
        h_ss_metmt2_MC_MuCS[i][j] = new TH2D(("h_ss_metmt2_MC_MuCS"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_ElCS[i][j] = new TH2D(("h_ss_metmt2_MC_ElCS"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
      }
      else if(i!=NTOPJETS_BINS-1 && j==NBOTJETS_BINS-1)
      {
        h_ss_metmt2_MC_MuCS[i][j] = new TH2D(("h_ss_metmt2_MC_MuCS"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_ElCS[i][j] = new TH2D(("h_ss_metmt2_MC_ElCS"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
      }
      else
      {
        h_ss_metmt2_MC_MuCS[i][j] = new TH2D(("h_ss_metmt2_MC_MuCS"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_ElCS[i][j] = new TH2D(("h_ss_metmt2_MC_ElCS"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
      }
    }
  }
  return ;
}

class SSHistgram
{
 public:
  void BookHistgram(const char *);

  TFile *oFile;
  //NTop, NBot plots
  TH2D *h_ss_ntopnbot_MC_AllBG;
  TH2D *h_ss_ntopnbot_MC_T1tttt_mGluino1200_mLSP800, *h_ss_ntopnbot_MC_T1tttt_mGluino1500_mLSP100;
  TH2D *h_ss_ntopnbot_MC_T2tt_mStop500_mLSP325, *h_ss_ntopnbot_MC_T2tt_mStop850_mLSP100; 
  //MET MT2 plots after top bot
  TH2D *h_ss_metmt2_MC_AllBG[NTOPJETS_BINS][NBOTJETS_BINS];
  TH2D *h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800[NTOPJETS_BINS][NBOTJETS_BINS], *h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100[NTOPJETS_BINS][NBOTJETS_BINS];
  TH2D *h_ss_metmt2_MC_T2tt_mStop500_mLSP325[NTOPJETS_BINS][NBOTJETS_BINS], *h_ss_metmt2_MC_T2tt_mStop850_mLSP100[NTOPJETS_BINS][NBOTJETS_BINS];
};

void SSHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");
  h_ss_ntopnbot_MC_AllBG = new TH2D("h_ss_ntopnbot_MC_AllBG","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);
  h_ss_ntopnbot_MC_T1tttt_mGluino1200_mLSP800 = new TH2D("h_ss_ntopnbot_MC_T1tttt_mGluino1200_mLSP800","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);
  h_ss_ntopnbot_MC_T1tttt_mGluino1500_mLSP100 = new TH2D("h_ss_ntopnbot_MC_T1tttt_mGluino1500_mLSP100","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);
  h_ss_ntopnbot_MC_T2tt_mStop500_mLSP325 = new TH2D("h_ss_ntopnbot_MC_T2tt_mStop500_mLSP325","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);
  h_ss_ntopnbot_MC_T2tt_mStop850_mLSP100 = new TH2D("h_ss_ntopnbot_MC_T2tt_mStop850_mLSP100","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);

  for(int i=0;i<NTOPJETS_BINS;i++)
  {
    for(int j=0;j<NBOTJETS_BINS;j++)
    {  
      std::string ntnbtag = "NT"+std::to_string(i+1)+"NB"+std::to_string(j+1);
			
      if(i==NTOPJETS_BINS-1)
      {
        h_ss_metmt2_MC_AllBG[i][j] = new TH2D(("h_ss_metmt2_MC_AllBG"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T2tt_mStop500_mLSP325[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop500_mLSP325"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T2tt_mStop850_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop850_mLSP100"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
      }
      else if(i!=NTOPJETS_BINS-1 && j==NBOTJETS_BINS-1)
      {
        h_ss_metmt2_MC_AllBG[i][j] = new TH2D(("h_ss_metmt2_MC_AllBG"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T2tt_mStop500_mLSP325[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop500_mLSP325"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T2tt_mStop850_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop850_mLSP100"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
      }
      else
      {
        h_ss_metmt2_MC_AllBG[i][j] = new TH2D(("h_ss_metmt2_MC_AllBG"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_T2tt_mStop500_mLSP325[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop500_mLSP325"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_T2tt_mStop850_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop850_mLSP100"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
      }
    }
  }
  return ;
}


/*
void QCDFactors::TFactorsPlotsGen()
{
  TCanvas *c_prefit = new TCanvas("c_prefit", "",50,50,1200,600);
  c_prefit->SetFillColor(0);
  c_prefit->cd();

  TH2D *tfactors2dPreFit = new TH2D("tfactors_prefit","TFactors PreFit",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
  tfactors2dPreFit->SetMarkerSize(1.6);

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
  tfactors2dPreFit->SetXTitle("#slash{E}_{T} [GeV]");
  tfactors2dPreFit->GetXaxis()->SetLabelSize(0.045);
  tfactors2dPreFit->GetXaxis()->SetTitleSize(0.045);
  tfactors2dPreFit->SetYTitle("M_{T2} [GeV]");
  tfactors2dPreFit->GetYaxis()->SetLabelSize(0.045);
  tfactors2dPreFit->GetYaxis()->SetTitleSize(0.045);
  tfactors2dPreFit->GetZaxis()->SetLabelSize(0.045);
  tfactors2dPreFit->GetZaxis()->SetTitleSize(0.045);
  tfactors2dPreFit->SetStats(0);

  gStyle->SetPaintTextFormat("1.2f");
  tfactors2dPreFit->Draw("colztexte");
  CMSStylePlot::CMS_lumi( c_prefit, 0, 0 );

  c_prefit->SaveAs( (dir_out + "_tfactors2dPreFit.png").c_str() );
  c_prefit->SaveAs( (dir_out + "_tfactors2dPreFit.pdf").c_str() );
  c_prefit->SaveAs( (dir_out + "_tfactors2dPreFit.C").c_str() );
  c_prefit->Close();

  //Post fit Tfactor plot
  TCanvas *c_postfit = new TCanvas("c_postfit", "",50,50,1200,600);
  c_postfit->SetFillColor(0);
  c_postfit->cd();

  TH2D *tfactors2dPostFit = new TH2D("tfactors_postfit","TFactors PostFit",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
  tfactors2dPostFit->SetMarkerSize(1.6);

  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  { 
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    { 
      tfactors2dPostFit->SetBinContent( i_cal+1 , j_cal+1, QCDTFactorFit[i_cal][j_cal] );
      tfactors2dPostFit->SetBinError( i_cal+1 , j_cal+1, QCDTFactorFit_err[i_cal][j_cal] );
    }
  }

  tfactors2dPostFit->SetTitle("");
  tfactors2dPostFit->SetXTitle("#slash{E}_{T} [GeV]");
  tfactors2dPostFit->GetXaxis()->SetLabelSize(0.045);
  tfactors2dPostFit->GetXaxis()->SetTitleSize(0.045);
  tfactors2dPostFit->SetYTitle("M_{T2} [GeV]");
  tfactors2dPostFit->GetYaxis()->SetLabelSize(0.045);
  tfactors2dPostFit->GetYaxis()->SetTitleSize(0.045);
  tfactors2dPostFit->GetZaxis()->SetLabelSize(0.045);
  tfactors2dPostFit->GetZaxis()->SetTitleSize(0.045);
  tfactors2dPostFit->SetStats(0);

  gStyle->SetPaintTextFormat("1.2f");
  tfactors2dPostFit->Draw("colztexte");
  CMSStylePlot::CMS_lumi( c_postfit, 0, 0 );

  c_postfit->SaveAs( (dir_out + "_tfactors2dPostFit.png").c_str() );
  c_postfit->SaveAs( (dir_out + "_tfactors2dPostFit.pdf").c_str() );
  c_postfit->SaveAs( (dir_out + "_tfactors2dPostFit.C").c_str() );
  c_postfit->Close();

  //Scaled Tfactor plot
  TCanvas *c_scaled = new TCanvas("c_scaled", "",50,50,1200,600);
  c_scaled->SetFillColor(0);
  c_scaled->cd();

  TH2D *tfactors2dScaled = new TH2D("tfactors_scaled","TFactors Scaled",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
  tfactors2dScaled->SetMarkerSize(1.6);

  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      tfactors2dScaled->SetBinContent( i_cal+1 , j_cal+1, QCDTFactorScaled[i_cal][j_cal] );
      tfactors2dScaled->SetBinError( i_cal+1 , j_cal+1, QCDTFactorScaled_err[i_cal][j_cal] );
    }
  }

  tfactors2dScaled->SetTitle("");
  tfactors2dScaled->SetXTitle("#slash{E}_{T} [GeV]");
  tfactors2dScaled->GetXaxis()->SetLabelSize(0.045);
  tfactors2dScaled->GetXaxis()->SetTitleSize(0.045);
  tfactors2dScaled->SetYTitle("M_{T2} [GeV]");
  tfactors2dScaled->GetYaxis()->SetLabelSize(0.045);
  tfactors2dScaled->GetYaxis()->SetTitleSize(0.045);
  tfactors2dScaled->GetZaxis()->SetLabelSize(0.045);
  tfactors2dScaled->GetZaxis()->SetTitleSize(0.045);
  tfactors2dScaled->SetStats(0);

  gStyle->SetPaintTextFormat("1.2f");
  tfactors2dScaled->Draw("colztexte");
  CMSStylePlot::CMS_lumi( c_scaled, 4, 0 );

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
  countNormal_MC->SetXTitle("#slash{E}_{T} [GeV]");
  countNormal_MC->SetYTitle("M_{T2} [GeV]");
  countNormal_MC->SetStats(0);
  countNormal->SetTitle("QCD Signal Normalized");
  countNormal->SetXTitle("#slash{E}_{T} [GeV]");
  countNormal->SetYTitle("M_{T2} [GeV]");
  countNormal->SetStats(0);
  countInverted_MC->SetTitle("QCD Inverted DeltaPhi MC");
  countInverted_MC->SetXTitle("#slash{E}_{T} [GeV]");
  countInverted_MC->SetYTitle("M_{T2} [GeV]");
  countInverted_MC->SetStats(0);
  countInverted->SetTitle("QCD Inverted DeltaPhi Normalized");
  countInverted->SetXTitle("#slash{E}_{T} [GeV]");
  countInverted->SetYTitle("M_{T2} [GeV]");
  countInverted->SetStats(0);

  //std::ostringstream strs;
  //strs << (LUMI/1000);
  //std::string lumi_str = strs.str();
  //const std::string titre="CMS Preliminary 2015, "+ lumi_str + " fb^{-1}, #sqrt{s} = 13 TeV";
  const std::string titre="CMS Preliminary 2015, 2.3 fb^{-1}, #sqrt{s} = 13 TeV";
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
*/
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
