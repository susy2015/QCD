#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h>

#include "TFile.h"
#include "TList.h"
#include "TString.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TExec.h"

#include "SusyAnaTools/Tools/searchBins.h"

#include "QCDBinFunction.h"

#include "CMSStylePlot/CMS_lumi.h"

SearchBins mySearchBins("SB_59_2016");

class ClosurePlots
{
 public:
  std::string target_DIR;

  TFile * finExp;
  TList * listExp;

  TFile * finPred;
  TList * listPred;

  std::string lumi_str;  

  double scale = 1;

  void Initialization(std::string dir); 
  void PrintPlotsName();
  void ClosureTemplate(
                       TString hist_tag,
                       TString XTitle,
                       double min,
                       double max
                       );
  void CompareTemplate(
                       TString hist_tag,
                       TString XTitle,
                       double min,
                       double max
                       );
  void BTStudyTemplate(
                       TString hist_tag,
                       TString XTitle,
                       double min,
                       double max
                      );
};

void ClosurePlots::Initialization(std::string dir)
{
  target_DIR = dir;
  system( ("mkdir " + dir).c_str() );

  finExp = TFile::Open("RootForPlotting/ExpQCD.root");
  listExp = finExp->GetListOfKeys();
  finPred = TFile::Open("RootForPlotting/PredQCDMC.root");
  listPred = finPred->GetListOfKeys();

  //convert lumi from double pb-1 to string, fb-1
  std::ostringstream strs;
  strs << (4000/1000);
  lumi_str = strs.str();
}

void ClosurePlots::PrintPlotsName()
{
  for(int i  = 0 ; i < listExp->GetSize() ; i++)
  {
    std::cout<<"Name: "<< listExp->At(i)->GetName() << "("<< i <<")"<<std::endl;
  }
  
  return ;
}

void ClosurePlots::ClosureTemplate(
                                   TString hist_tag,
                                   TString XTitle,
                                   double min,
                                   double max
                                  )
{ 
  TH1D * h_pred;
  TH1D * h_exp;

  int NHist;
  std::cout << listExp->GetSize() << "," << listPred->GetSize() << std::endl;
  if( listPred->GetSize() == listExp->GetSize() ) NHist = listExp->GetSize();
  else { NHist = -1; std::cout << "We do not have equal number of hist in Exp and Pred, what the fuck is going on??" << std::endl; return ; }  

  //Get Exp and Pred from root file
  for(int i  = 0 ; i < NHist ; i++)
  {
    if( TString(listPred->At(i)->GetName()).Contains( hist_tag ) )
    {
      if( TString(listPred->At(i)->GetName()).Contains( "_pred_" ) )
      {
        h_pred = (TH1D*)finPred->Get(listPred->At(i)->GetName())->Clone();
      }
    }
    if( TString(listExp->At(i)->GetName()).Contains( hist_tag ) )
    {
      if( TString(listExp->At(i)->GetName()).Contains( "_exp_" ) )
      {
        h_exp = (TH1D*)finExp->Get(listExp->At(i)->GetName())->Clone();
      }
    }
    else
      continue;
  }

  //Set Style for h_exp and h_pred
  h_pred->SetMarkerStyle(20);
  h_pred->SetMarkerColor(kBlue);
  h_pred->SetMarkerSize(0);
  h_pred->SetLineColor(h_pred->GetMarkerColor());
  h_pred->SetLineWidth(3);
  h_pred->GetXaxis()->SetRangeUser(min,max);
  h_pred->GetXaxis()->SetTitle(XTitle);
  h_pred->GetYaxis()->SetTitleOffset(0.6);
  h_pred->GetYaxis()->SetTitleFont(42);
  h_pred->GetYaxis()->SetTitleSize(0.065);
  h_pred->GetYaxis()->SetLabelSize(0.04);
  h_pred->GetYaxis()->SetLabelFont(42);
  h_pred->GetYaxis()->SetTitle("Events");
  //h_pred->Sumw2();
  //h_pred->Scale(scale);

  h_exp->SetMarkerStyle(20);
  h_exp->SetMarkerColor(kRed);
  h_exp->SetMarkerSize(0.9);
  h_exp->SetLineColor(h_exp->GetMarkerColor());
  h_exp->SetLineWidth(3);
  h_exp->GetXaxis()->SetRangeUser(min,max);
  h_exp->GetXaxis()->SetTitle(XTitle);
  h_exp->GetYaxis()->SetTitleOffset(0.6);
  h_exp->GetYaxis()->SetTitleFont(42);
  h_exp->GetYaxis()->SetTitleSize(0.065);
  h_exp->GetYaxis()->SetLabelSize(0.04);
  h_exp->GetYaxis()->SetLabelFont(42);
  h_exp->GetYaxis()->SetTitle("Events");
  //h_exp->Sumw2();
  //h_exp->Scale(scale);

  // Ratio plots
  TH1* h_ratioFrame;
  TH1* h_ratio;
    
  h_ratio = static_cast<TH1*>(h_exp->Clone("Ratio"));
  h_ratio->Divide(h_pred);
  h_ratio->SetMarkerSize(1);
  h_ratio->GetYaxis()->SetTitle("#frac{Direct}{Prediction}");
  //h_ratio->GetYaxis()->SetRangeUser(0.0,5.1);
  h_ratio->SetTitle("");
  h_ratio->SetStats(0);
  h_ratio->SetLineWidth(1);
  h_ratio->GetYaxis()->SetTitleSize(0.15);
  h_ratio->GetYaxis()->SetTitleOffset(0.3);
  h_ratio->GetYaxis()->SetTitleFont(42);
  h_ratio->GetYaxis()->SetLabelSize(0.1);
  h_ratio->GetYaxis()->SetLabelFont(42);
  h_ratio->GetXaxis()->SetLabelOffset(0.01);
  h_ratio->GetXaxis()->SetLabelFont(42);
  h_ratio->GetXaxis()->SetLabelSize(0.08);
  h_ratio->GetXaxis()->SetTitleSize(0.16);
  h_ratio->GetXaxis()->SetTitleFont(42);
  h_ratio->GetXaxis()->SetTitleOffset(0.6);
  if (hist_tag == "_sb")
  {
    h_ratio->GetXaxis()->SetTitle("Search region bin number");
  }

  //Create LUMI stamp
  //const std::string titre="CMS Preliminary 2015, "+ lumi_str + " fb^{-1}, #sqrt{s} = 13 TeV";
  //const std::string titre="CMS Preliminary 2016, 2.3 fb^{-1}, #sqrt{s} = 13 TeV";
  const std::string titre="CMS Preliminary 2016                                                       12.9 fb^{-1}(13 TeV)";

  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);

  //Create Legend
  TLegend* leg = new TLegend(0.55,0.75,0.90,0.90);
  leg->SetBorderSize(1);
  leg->SetLineColor(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  //leg->SetFillStyle();
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  leg->SetHeader("QCD background");
  leg->AddEntry(h_exp,"Direct from simulation","P");
  //leg->AddEntry(hPred[0],"Treat simulation like data","L");
  leg->AddEntry(h_pred,"Treat simulation like data");

  //Draw plots on Canvas
  TCanvas *c = new TCanvas("c","",50,50,800,600); 
  //HistStyle::init();
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
  pad1->SetBottomMargin(0);
  pad1->SetBorderMode(0);
  
  TExec *setex = new TExec("setex", "gStyle->SetErrorX(0.0)");

  if( hist_tag == "_sb" )
  { 
    pad1->SetLogy(); 
    h_exp->GetXaxis()->SetRangeUser(0.,NSEARCH_BINS);
  
    Double_t pred,exp,pred_err,exp_err;
    double non_closure_unc[NSEARCH_BINS] ={-10};
    for (Int_t i = 1; i < h_pred->GetNbinsX(); i++)
    {
      pred = h_pred->GetBinContent(i);
      exp = h_exp->GetBinContent(i);
      pred_err = h_pred->GetBinError(i);
      exp_err = h_exp->GetBinError(i);
      //std::cout << "i: " << i << " pred_err: " << pred_err << " exp_err: " << exp_err << std::endl;
      double r = 100;
      double e = 5;
      if ( (pred > 0) && (exp > 0) ) 
      { 
        r = exp/pred;
        e = std::sqrt( exp_err*exp_err + pred_err*pred_err*r*r ) / pred;
        non_closure_unc[i-1] = e;
        //double percent = (exp-pred)/pred * 100;
        std::cout << "i: " << i << " Pred: "<< pred << " Pred_Err: "<< pred_err << std::endl;
        //std::cout << "i: " << i << " Pred: "<< pred << " Exp: "<< exp << " Ratio: " << r-1 << " Error: " << e << std::endl;
      }
    }
  }
    
  setex->Draw();
  h_exp->Draw("PE1");
  h_pred->DrawCopy("hist same");
  h_pred->SetFillColor(kBlue-4);
  h_pred->SetFillStyle(3001);
  h_pred->Draw("E2 same");

  if( hist_tag == "_sb" ){ mySearchBins.drawSBregionDef(0.0, 75.0, true); }
  CMSStylePlot::CMS_lumi( c, 4, 0 );
  //title->Draw("same");
  leg->Draw("same");

  c->Update(); 
  
  pad->cd(2);
  TPad *pad2 = (TPad*) pad->GetPad(2);
  pad2->SetPad("ratio", "", 0, 0, 1.0, divRatio, kWhite);
  pad2->SetBottomMargin(0.3);
  pad2->SetTopMargin(small);
  pad2->SetBorderMode(0);

  h_ratio->SetMaximum(5);
  h_ratio->SetMinimum(-2);
  if( hist_tag == "_sb" )
  {
    h_ratio->GetXaxis()->SetLabelSize(0.1);
    h_ratio->GetXaxis()->SetTitleOffset(0.8);
    h_ratio->GetXaxis()->SetRangeUser(0.,NSEARCH_BINS);
  }

  TLine *tl_one = new TLine();
  tl_one->SetLineStyle(2);
  tl_one->SetLineColor(1);
  tl_one->SetLineWidth(2);
  
  h_ratio->Draw("PE1");
  tl_one->DrawLine(min,1.,max,1.);

  c->SaveAs( target_DIR + TString("/") + hist_tag + TString(".png") );
  c->SaveAs( target_DIR + TString("/") + hist_tag + TString(".pdf") );
  c->SaveAs( target_DIR + TString("/") + hist_tag + TString(".C") );
}

/*
void ClosurePlots::CompareTemplate(
                                   TString hist_tag,
                                   TString XTitle,
                                   double min,
                                   double max
                                  )
{ 
  TH1D * h_inverted;
  TH1D * h_normal;

  for(int i  = 0 ; i < list->GetSize() ; i++)
  {
    if( TString(list->At(i)->GetName()).Contains( hist_tag ) )
    {
      if( TString(list->At(i)->GetName()).Contains( "_inverted_" ) )
      {
        h_inverted = (TH1D*)fin->Get(list->At(i)->GetName())->Clone();
      }
      if( TString(list->At(i)->GetName()).Contains( "_exp_" ) )
      {
        h_normal = (TH1D*)fin->Get(list->At(i)->GetName())->Clone();
      }
    }
    else
      continue;
  }

  TCanvas *c = new TCanvas("c","A Simple Graph Example",200,10,700,500); 
  gStyle->SetOptStat(0);

  h_inverted->GetXaxis()->SetRangeUser(min,max);
  h_inverted->GetXaxis()->SetTitle(XTitle);
  h_inverted->SetLineColor(1);
  h_inverted->SetLineWidth(3);
  h_inverted->Sumw2();

  h_normal->GetXaxis()->SetRangeUser(min,max);
  h_normal->GetXaxis()->SetTitle(XTitle);
  h_normal->SetLineColor(2);
  h_normal->SetLineWidth(3);
  h_normal->Sumw2();

  h_inverted->Draw(); 
  h_normal->Draw("same");

  const std::string titre="CMS Preliminary 2015, 3 fb^{-1}, #sqrt{s} = 13 TeV";
  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);
  title->Draw("same");

  TLegend* leg = new TLegend(0.6,0.75,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  leg->AddEntry(h_normal,"Normal","l");
  leg->AddEntry(h_inverted,"Inverted Delat Phi","l");
  leg->Draw("same");

  c->SaveAs( hist_tag + TString("_normal_inverted.png") );
  c->SaveAs( hist_tag + TString("_normal_inverted.pdf") );
  c->SaveAs( hist_tag + TString("_normal_inverted.C") );
}

void ClosurePlots::BTStudyTemplate(
                                   TString hist_tag,
                                   TString XTitle,
                                   double min,
                                   double max
                                  )
{ 
  TH1D * h_nbnt;
  TH1D * h_ybyt;

  for(int i  = 0 ; i < list->GetSize() ; i++)
  {
    if( TString(list->At(i)->GetName()).Contains( hist_tag ) )
    {
      if( TString(list->At(i)->GetName()).Contains( "_nbnt" ) )
      {
        h_nbnt = (TH1D*)fin->Get(list->At(i)->GetName())->Clone();
      }
      if( TString(list->At(i)->GetName()).Contains( "_ybyt" ) )
      {
        h_ybyt = (TH1D*)fin->Get(list->At(i)->GetName())->Clone();
      }
    }
    else
      continue;
  }

  double scaletmp;
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

  h_nbnt->GetXaxis()->SetRangeUser(min,max);
  h_nbnt->GetXaxis()->SetTitle(XTitle);
  h_nbnt->SetLineColor(1);
  h_nbnt->SetLineWidth(3);
  h_nbnt->Sumw2();
  scaletmp = 1/(h_nbnt->Integral());
  h_nbnt->Scale(scaletmp);

  h_ybyt->GetXaxis()->SetRangeUser(min,max);
  h_ybyt->GetXaxis()->SetTitle(XTitle);
  h_ybyt->SetLineColor(2);
  h_ybyt->SetLineWidth(3);
  h_ybyt->Sumw2();
  scaletmp = 1/(h_ybyt->Integral());
  h_ybyt->Scale(scaletmp);

  h_nbnt->Draw(); 
  h_ybyt->Draw("same");

  const std::string titre="CMS Preliminary 2015, #sqrt{s} = 13 TeV";
  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);
  title->Draw("same");

  TLegend* leg = new TLegend(0.6,0.75,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  leg->AddEntry(h_nbnt,"No Bottom cut","l");
  leg->AddEntry(h_ybyt,"Bottom cut","l");
  leg->Draw("same");

  pad->cd(2); 
  TPad *pad2 = (TPad*) pad->GetPad(2);
  pad2->SetPad("ratio", "", 0, 0, 1.0, divRatio, kWhite);
  pad2->SetBottomMargin(0.3);
  pad2->SetTopMargin(small);
  pad2->SetBorderMode(0);

  TH1D *ratio = (TH1D*) h_nbnt->Clone();
  TH1D *allmc = (TH1D*) h_ybyt->Clone();

  ratio->Add(allmc, -1);
  ratio->Divide(allmc);
  ratio->GetYaxis()->SetTitle( "(NB - YB)/YB" );

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
  //ratio->Sumw2();
  ratio->DrawCopy();

  TH1D *zero = (TH1D*)ratio->Clone(); 
  zero->Reset();
  for(int ib=0; ib<ratio->GetNbinsX(); ib++){ zero->SetBinContent(ib+1, 0); }
  zero->SetLineColor(kRed); zero->SetLineWidth(1);
  zero->DrawCopy("same");

  c->SaveAs( hist_tag + TString("_nbnt_ybyt.png") );
  c->SaveAs( hist_tag + TString("_nbnt_ybyt.pdf") );
  c->SaveAs( hist_tag + TString("_nbnt_ybyt.C") );
}
*/

struct Plotting_Parameter
{
  TString hist_tag;
  TString XTitle;
  double min;
  double max;
};
