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

SearchBins mySearchBins("SB_v1_2017");

class AllHadTTJetsWJetsSTPlots
{
 public:
  std::string target_DIR;

  TFile * fin;
  TList * list;

  std::string lumi_str;  

  double scale = 1;

  void Initialization(std::string dir); 
  void PrintPlotsName();
  void CompareTemplate(
                       TString hist_n_tag,
                       TString hist_d_tag,
                       TString XTitle,
                       double min,
                       double max
                       );
};

void AllHadTTJetsWJetsSTPlots::Initialization(std::string dir)
{
  target_DIR = dir;
  system( ("mkdir " + dir).c_str() );

  fin = TFile::Open("RootForPlotting/AllHadTTJetsWJetsST.root");
  list = fin->GetListOfKeys();

  //convert lumi from double pb-1 to string, fb-1
  std::ostringstream strs;
  strs << (4000/1000);
  lumi_str = strs.str();
}

void AllHadTTJetsWJetsSTPlots::PrintPlotsName()
{
  for(int i  = 0 ; i < list->GetSize() ; i++)
  {
    std::cout<<"Name: "<< list->At(i)->GetName() << "("<< i <<")"<<std::endl;
  }
  
  return ;
}

void AllHadTTJetsWJetsSTPlots::CompareTemplate(
                                               TString hist_n_tag,
                                               TString hist_d_tag,
                                               TString XTitle,
                                               double min,
                                               double max
                                              )
{ 
  TH1D * h_n;
  TH1D * h_d;

  int NHist = list->GetSize();
  //Get Exp and Pred from root file
  for(int i  = 0 ; i < NHist ; i++)
  {
    if( TString(list->At(i)->GetName()).Contains( hist_n_tag ) )
    {
      h_n = (TH1D*)fin->Get(list->At(i)->GetName())->Clone();
    }
    if( TString(list->At(i)->GetName()).Contains( hist_d_tag ) )
    {
      h_d = (TH1D*)fin->Get(list->At(i)->GetName())->Clone();
    }
    else
      continue;
  }

  //Set Style for h_d and h_n
  h_n->SetMarkerStyle(20);
  h_n->SetMarkerColor(kBlue);
  h_n->SetMarkerSize(0);
  h_n->SetLineColor(h_n->GetMarkerColor());
  h_n->SetLineWidth(3);
  h_n->GetXaxis()->SetRangeUser(min,max);
  h_n->GetXaxis()->SetTitle(XTitle);
  h_n->GetYaxis()->SetTitleOffset(0.6);
  h_n->GetYaxis()->SetTitleFont(42);
  h_n->GetYaxis()->SetTitleSize(0.065);
  h_n->GetYaxis()->SetLabelSize(0.05);
  h_n->GetYaxis()->SetLabelFont(42);
  h_n->GetYaxis()->SetTitle("Events");
  h_n->SetMinimum(0.001);
  //h_n->Sumw2();
  //h_n->Scale(scale);

  h_d->SetMarkerStyle(20);
  h_d->SetMarkerColor(kRed);
  h_d->SetMarkerSize(0.9);
  h_d->SetLineColor(h_d->GetMarkerColor());
  h_d->SetLineWidth(3);
  h_d->GetXaxis()->SetRangeUser(min,max);
  h_d->GetXaxis()->SetTitle(XTitle);
  h_d->GetYaxis()->SetTitleOffset(0.6);
  h_d->GetYaxis()->SetTitleFont(42);
  h_d->GetYaxis()->SetTitleSize(0.065);
  h_d->GetYaxis()->SetLabelSize(0.05);
  h_d->GetYaxis()->SetLabelFont(42);
  h_d->GetYaxis()->SetTitle("Events");
  h_d->SetMinimum(0.001);
  //h_d->Sumw2();
  //h_d->Scale(scale);

  // Ratio plots
  TH1* h_ratioFrame;
  TH1* h_ratio;
    
  h_ratio = static_cast<TH1*>(h_n->Clone("Ratio"));
  h_ratio->Divide(h_d);
  h_ratio->SetMarkerSize(1);
  h_ratio->SetTitle("");
  h_ratio->SetStats(0);
  h_ratio->SetLineWidth(1);
  h_ratio->GetYaxis()->SetTitleSize(0.15);
  h_ratio->GetYaxis()->SetTitleOffset(0.6);
  h_ratio->GetYaxis()->SetTitleFont(42);
  h_ratio->GetYaxis()->SetLabelSize(0.1);
  h_ratio->GetYaxis()->SetLabelFont(42);
  h_ratio->GetXaxis()->SetLabelOffset(0.01);
  h_ratio->GetXaxis()->SetLabelFont(42);
  h_ratio->GetXaxis()->SetLabelSize(0.15);
  h_ratio->GetXaxis()->SetTitleSize(0.16);
  h_ratio->GetXaxis()->SetTitleFont(42);
  h_ratio->GetXaxis()->SetTitleOffset(1.0);

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
  leg->SetHeader("All Had TTJetsWJetsSTop QCD CR");
  leg->AddEntry(h_n, hist_n_tag);
  leg->AddEntry(h_d, hist_d_tag, "P");

  //Draw plots on Canvas
  TCanvas *c = new TCanvas("c","",50,50,800,600); 
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
  if( hist_n_tag.Contains("sb") )
  {
    pad1->SetLogy();
  }
  setex->Draw();
  h_d->Draw("PE1");
  h_n->DrawCopy("hist same");
  h_n->SetFillColor(kBlue-4);
  h_n->SetFillStyle(3001);
  h_n->Draw("E2 same");

  CMSStylePlot::CMS_lumi( c, 4, 0 );
  leg->Draw("same");

  c->Update(); 
  
  pad->cd(2);
  TPad *pad2 = (TPad*) pad->GetPad(2);
  pad2->SetPad("ratio", "", 0, 0, 1.0, divRatio, kWhite);
  pad2->SetBottomMargin(0.3);
  pad2->SetTopMargin(small);
  pad2->SetBorderMode(0);

  h_ratio->SetMaximum(0.9);
  h_ratio->SetMinimum(-0.1);

  TLine *tl_one = new TLine();
  tl_one->SetLineStyle(2);
  tl_one->SetLineColor(1);
  tl_one->SetLineWidth(2);
  
  h_ratio->Draw("PE1");
  tl_one->DrawLine(min,0.,max,0.);

  c->SaveAs( target_DIR + TString("/_n_") + hist_n_tag + TString("_d_") + hist_d_tag + TString(".png") );
  c->SaveAs( target_DIR + TString("/_n_") + hist_n_tag + TString("_d_") + hist_d_tag + TString(".pdf") );
  c->SaveAs( target_DIR + TString("/_n_") + hist_n_tag + TString("_d_") + hist_d_tag + TString(".C") );
}

struct Plotting_Parameter
{
  TString hist_n_tag;
  TString hist_d_tag;
  TString XTitle;
  double min;
  double max;
};
