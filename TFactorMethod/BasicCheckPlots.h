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

#include "QCDReWeighting.h"

TH1D* merge_hist_list(const TList& hists)
{
  TIter next(hists.MakeIterator());
  TH1D* hist = NULL;
  TH1D* res = NULL;
  int icount = 0;
  while ((hist = (TH1D*) next()))
  {
    if(icount == 0)
    {
      res = (TH1D*) hist->Clone("my_all");
      icount++;
    }
    else
    {
      res->Add(hist);
    }
  }
  return res;
}

TH1D* merge_stack(const THStack& stack)
{
  TList* hists = stack.GetHists();
  return merge_hist_list(*hists);
}

class BasicCheckPlots
{
 public:
  std::string target_DIR;

  TFile * fin;
  TList * list;

  std::string lumi_str;  

  double scale = 1;

  void Initialization(std::string dir); 
  void PrintPlotsName();
  void BasicCheckTemplate(
                          TString hist_tag,
                          TString XTitle,
                          double min,
                          double max
                         );
};

void BasicCheckPlots::Initialization(std::string dir)
{
  target_DIR = dir;
  system( ("mkdir " + dir).c_str() );

  fin = TFile::Open("BasicCheckQCD.root");
  //fin = TFile::Open("BasicCheckLL.root");
  list = fin->GetListOfKeys();

  //convert lumi from double pb-1 to string, fb-1
  std::ostringstream strs;
  strs << (LUMI/1000);
  lumi_str = strs.str();
}

void BasicCheckPlots::PrintPlotsName()
{
  for(int i  = 0 ; i < list->GetSize() ; i++)
  {
    std::cout<<"Name: "<< list->At(i)->GetName() << "("<< i <<")"<<std::endl;
  }
  
  return ;
}

void BasicCheckPlots::BasicCheckTemplate(
                                         TString hist_tag,
                                         TString XTitle,
                                         double min,
                                         double max
                                        )
{ 
  TH1D * h_Data;
  THStack * hs_MC = new THStack("hs_MC","");
  
  TLegend* leg = new TLegend(0.6,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);

  std::string smalltag;
  int NHist = list->GetSize();

  for(int i  = 0 ; i < NHist ; i++)
  {
    if( TString(list->At(i)->GetName()).Contains( hist_tag ) )
    {
      if( TString(list->At(i)->GetName()).Contains( "_Data" ) )
      {
        h_Data = (TH1D*)fin->Get(list->At(i)->GetName())->Clone();
        smalltag = "Data"; 
        leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "l");
      }
    }
    if( TString(list->At(i)->GetName()).Contains( hist_tag ) )
    {
      if( TString(list->At(i)->GetName()).Contains( "_MC" ) )
      {
        hs_MC->Add( (TH1D*)fin->Get(list->At(i)->GetName()) );
        
        if( TString(list->At(i)->GetName()).Contains( "LL" ) ) { smalltag = "LL"; leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "f"); }
        if( TString(list->At(i)->GetName()).Contains( "HadTau" ) ) { smalltag = "HadTau"; leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "f"); }
        if( TString(list->At(i)->GetName()).Contains( "Zinv" ) ) { smalltag = "Zinv"; leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "f"); }
        if( TString(list->At(i)->GetName()).Contains( "QCD" ) ) { smalltag = "QCD"; leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "f"); }
        if( TString(list->At(i)->GetName()).Contains( "TTZ" ) ) { smalltag = "TTZ"; leg->AddEntry( (TH1D*)fin->Get(list->At(i)->GetName()), smalltag.c_str(), "f"); }
      }
    }
    else
      continue;
  }

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

  h_Data->GetXaxis()->SetRangeUser(min,max);
  h_Data->GetXaxis()->SetTitle(XTitle);
  h_Data->SetLineColor(1);
  h_Data->SetLineWidth(3);
  h_Data->Sumw2();
  h_Data->Scale(scale);

  //hs_MC->GetXaxis()->SetLimits(min, max);
  //hs_MC->GetXaxis()->SetRangeUser(min,max);
  //hs_MC->GetXaxis()->SetTitle(XTitle);
  //hs_MC->SetLineColor(2);
  //hs_MC->SetLineWidth(3);
  //hs_MC->Sumw2();
  //hs_MC->Scale(scale);
  
  hs_MC->Draw("hist");
  h_Data->Draw("same e0");

  //const std::string titre="CMS Preliminary 2015, "+ lumi_str + " fb^{-1}, #sqrt{s} = 13 TeV";
  const std::string titre="CMS Preliminary 2016, 8.0 fb^{-1}, #sqrt{s} = 13 TeV";
  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);
  title->Draw("same");
  
  leg->Draw("same");

  c->Update(); 
 
  pad->cd(2); 
  TPad *pad2 = (TPad*) pad->GetPad(2);
  pad2->SetPad("ratio", "", 0, 0, 1.0, divRatio, kWhite);
  pad2->SetBottomMargin(0.3);
  pad2->SetTopMargin(small);
  pad2->SetBorderMode(0);

  TH1D *h_MC_all = merge_stack( *hs_MC );
  TH1D *ratio = (TH1D*) h_Data->Clone();
  TH1D *allmc = (TH1D*) h_MC_all->Clone();

  ratio->Add(allmc, -1);
  ratio->Divide(allmc);
  ratio->GetYaxis()->SetTitle( "(Data-MC)/MC" );

  TAxis* xHT = ratio->GetXaxis();

  xHT->SetTickLength(xHT->GetTickLength()*labelRatio);
  xHT->SetLabelSize(xHT->GetLabelSize()*labelRatio);
  xHT->SetLabelOffset(xHT->GetLabelOffset()*labelRatio);
  ratio->SetMinimum(-2.0);
  ratio->SetMaximum(2.0);

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

  c->SaveAs( target_DIR + TString("/") + hist_tag + TString("_BasicCheck.png") );
  c->SaveAs( target_DIR + TString("/") + hist_tag + TString("_BasicCheck.pdf") );
  c->SaveAs( target_DIR + TString("/") + hist_tag + TString("_BasicCheck.C") );
}

struct Plotting_Parameter
{
  TString hist_tag;
  TString XTitle;
  double min;
  double max;
};
