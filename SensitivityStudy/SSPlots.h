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
#include "TH2D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TExec.h"

#include "SusyAnaTools/Tools/searchBins.h"

#include "SSReWeighting.h"
#include "SSBinFunction.h"

class SSPlots
{
 public:
  std::string target_DIR;

  TFile * fin;
  TList * list;

  std::string lumi_str;  

  double scale = 1;

  void Initialization(std::string dir); 
  void PrintPlotsName();
  void SSPlotsLoop();
};

void SSPlots::Initialization(std::string dir)
{
  target_DIR = dir;
  system( ("mkdir " + dir).c_str() );

  fin = TFile::Open("SS.root");
  list = fin->GetListOfKeys();
  //convert lumi from double pb-1 to string, fb-1
  std::ostringstream strs;
  strs << (LUMI/1000);
  lumi_str = strs.str();
}

void SSPlots::PrintPlotsName()
{
  for(int i  = 0 ; i < list->GetSize() ; i++)
  {
    std::cout<<"Name: "<< list->At(i)->GetName() << "("<< i <<")"<<std::endl;
  }
  return ;
}

void SSPlots::SSPlotsLoop()
{ 
  TH2D * h;

  int NHist = list->GetSize();

	//Get plots from root file
  for(int i  = 0 ; i < NHist ; i++)
  {
    h = (TH2D*)fin->Get(list->At(i)->GetName())->Clone();

    if( TString(list->At(i)->GetName()).Contains( "_metmt2_MC_" ) )
    {
      h->GetXaxis()->SetTitle("MET[GeV]");
      h->GetYaxis()->SetTitle("MT2[GeV]");
    }
    else if( TString(list->At(i)->GetName()).Contains( "_ntopnbot_MC_" ) )
    {
      h->GetXaxis()->SetTitle("NTops");
      h->GetYaxis()->SetTitle("NBottoms");
    }
    else
    {
      std::cout << "Unknow plot name??!!" << std::endl;
    }

    //Create LUMI stamp
    const std::string titre="CMS Preliminary 2016, "+ lumi_str + " fb^{-1}, #sqrt{s} = 13 TeV";

    TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
    title->SetNDC();
    title->SetTextSize(0.045);

	  //Draw plots on Canvas
    TCanvas *c = new TCanvas("c","",50,50,800,600); 
	  //HistStyle::init();
	  gStyle->SetOptStat(0);
		gStyle->SetPaintTextFormat("1.2f");
    h->Draw("colztexte");
    title->Draw("same");

    c->SaveAs( target_DIR + TString("/_") + TString(list->At(i)->GetName()) + TString(".png") );
    c->SaveAs( target_DIR + TString("/_") + TString(list->At(i)->GetName()) + TString(".pdf") );
    c->SaveAs( target_DIR + TString("/_") + TString(list->At(i)->GetName()) + TString(".C") );
	}
}
