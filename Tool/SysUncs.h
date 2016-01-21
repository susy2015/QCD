#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <iomanip>

#include "TFile.h"
#include "TList.h"
#include "TString.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"

#include "SusyAnaTools/Tools/searchBins.h"

#include "QCDReWeighting.h"
#include "QCDBinFunction.h"

class SysUncs
{
 public:
  std::string sysunc_type;

  TFile * finPred;
  TList * listPred;

  TFile * finSysUnc;
  TList * listSysUnc;

  double final_pred[NSEARCH_BINS] = {0},final_pred_stat[NSEARCH_BINS] = {0};
  double sysunc_tfactors[NSEARCH_BINS] = {0}, sysunc_nonclosure[NSEARCH_BINS] = {0};
  double sysunc_all[NSEARCH_BINS] = {0};

  void Initialization(std::string type); 
  void Reset();

  void GetTFactorsSysUnc();
  void GetNonClosureSysUnc();

  void combineSysUncs();
  void printSysUncs();
  void printLatexTable();
  void printFinalPred();
};

void SysUncs::Initialization(std::string type)
{
  sysunc_type = type;

  finPred = TFile::Open("PredQCDData.root");
  listPred = finPred->GetListOfKeys();
  if( type == "TFactorsUnc" )
  {
    finPred = TFile::Open("PredQCDData.root");
    listPred = finPred->GetListOfKeys();

    finSysUnc = TFile::Open("TFactorsUnc.root");
    listSysUnc = finSysUnc->GetListOfKeys();
  }
  else if( type == "NonClosureUnc" )
  {
    finPred = TFile::Open("PredQCDMC.root");
    listPred = finPred->GetListOfKeys();

    finSysUnc = TFile::Open("ExpQCD.root");
    listSysUnc = finSysUnc->GetListOfKeys();
  }
  else{ std::cout << "Unc type not included! Think carefully!" << std::endl; return ; }
  //convert lumi from double pb-1 to string, fb-1
  //std::ostringstream strs;
  //strs << (LUMI/1000);
  //lumi_str = strs.str();
  return ;
}

void SysUncs::Reset()
{
  finPred->Close();
  listPred->Clear();
  finSysUnc->Close();
  listSysUnc->Clear();
  std::cout << "Done with " << sysunc_type << ". Resetting the file and list object!" << std::endl;
  sysunc_type.clear();
  return ;
}

void SysUncs::GetTFactorsSysUnc()
{ 
  TH1D * h_pred;
  TH1D * h_sysunc;

  int NPredHist, NSysUncHist;
  NPredHist = listPred->GetSize();
  NSysUncHist = listSysUnc->GetSize();

  for(int i  = 0 ; i < NPredHist ; i++)
  {
    if( TString(listPred->At(i)->GetName()).Contains( "_pred_sb" ) )
    {
      h_pred = (TH1D*)finPred->Get(listPred->At(i)->GetName())->Clone();
    }
    else 
      continue;
  }

  for (int j = 1; j < NSEARCH_BINS+1 ; j++)
  {
    final_pred[j-1] = h_pred->GetBinContent(j);
    final_pred_stat[j-1] = h_pred->GetBinError(j);
  }

  for(int i  = 0 ; i < NSysUncHist ; i++)
  {
    if( TString(listPred->At(i)->GetName()).Contains( "_TFactorsUnc_0" ) ) continue;
    else
    {
      h_sysunc = (TH1D*)finSysUnc->Get(listSysUnc->At(i)->GetName())->Clone();

      for (int j = 1; j < NSEARCH_BINS+1 ; j++)
      {
        double pred = h_pred->GetBinContent(j);
        double sysunc = h_sysunc->GetBinContent(j);
        double pred_err = h_pred->GetBinError(j);
        double sysunc_err = h_sysunc->GetBinError(j);
        double d = 1000;

        if ( (pred >= 0) )
        {
          d = std::abs( sysunc-pred );
        }
        else if( pred < 0 && sysunc >= 0)
          d = sysunc;
        else
        { 
          d=0; 
          //std::cout << i << "Zero Sys Unc from Tfactors" <<std::endl; 
        }
        sysunc_tfactors[j-1] += d*d;
      }
      h_sysunc->Reset();
    }
  }

  for (int i = 0; i < NSEARCH_BINS ; i++)
  { 
    sysunc_tfactors[i] = std::sqrt( sysunc_tfactors[i] );
  }
  return ;
}

void SysUncs::GetNonClosureSysUnc()
{
  TH1D * h_pred;
  TH1D * h_sysunc;

  int NHist;
  if( listPred->GetSize() == listSysUnc->GetSize() ) NHist = listSysUnc->GetSize();
  else { NHist = -1; std::cout << "We do not have equal number of hist in Exp and Pred, what the fuck is going on??" << std::endl; return ; }

  for(int i  = 0 ; i < NHist ; i++)
  {
    if( TString(listPred->At(i)->GetName()).Contains( "_pred_sb" ) )
    {
      h_pred = (TH1D*)finPred->Get(listPred->At(i)->GetName())->Clone();
    }
    if( TString(listSysUnc->At(i)->GetName()).Contains( "_exp_sb" ) )
    {
      h_sysunc = (TH1D*)finSysUnc->Get(listSysUnc->At(i)->GetName())->Clone();
    }
    else
      continue;
  }

  for (int j = 1; j < NSEARCH_BINS+1 ; j++)
  {
    double pred = h_pred->GetBinContent(j);
    double sysunc = h_sysunc->GetBinContent(j);
    double pred_err = h_pred->GetBinError(j);
    double sysunc_err = h_sysunc->GetBinError(j);
    //std::cout << "i: " << i << " pred_err: " << pred_err << " sysunc_err: " << sysunc_err << std::endl;
    double e = 5;
    if ( (pred > 0) && (sysunc > 0) )
    {
      double r = pred/sysunc;
      e = std::sqrt( pred_err*pred_err + sysunc_err*sysunc_err*r*r ) / sysunc;
      sysunc_nonclosure[j-1] = std::max( std::abs(e*sysunc) , std::abs(sysunc-pred) );
      std::cout << "j: " << j << " Pred: "<< pred << " Exp: "<< sysunc << " Error: " << e << std::endl;
    }
    else if( j!=1 && ((pred <= 0) || (sysunc <= 0)) ){ sysunc_nonclosure[j-1] = std::abs(sysunc-pred); }
    else { std::cout << "First Bin have werid behavior, too bad, WTF??!!" << std::endl; return ;}
  }

  return ;
}

void SysUncs::combineSysUncs()
{
  for(int i=0;i<NSEARCH_BINS;i++)
  {
    sysunc_all[i] = std::sqrt(sysunc_tfactors[i]*sysunc_tfactors[i] + sysunc_nonclosure[i]*sysunc_nonclosure[i] );
  }
  return ;
}

void SysUncs::printSysUncs()
{
  for(int i=0;i<NSEARCH_BINS;i++)
  {
    std::cout << "SB: "<< i << ", SysUnc_All: " << sysunc_all[i] << ", SysUnc_TFactor: "<< sysunc_tfactors[i] << ", SysUnc_NonClosure: " << sysunc_nonclosure[i] << std::endl;
  }
  return ;
}

void SysUncs::printLatexTable()
{
  std::vector<std::vector<std::vector<double> > > out_MT2_met_Binning;
  build_MT2_met_Binning(out_MT2_met_Binning);
  print_searchBins_headerstr("& QCD Prediction\\\\");
  for(int ib=0; ib<nTotBins; ib++)
  {
    double tmp_pred = final_pred[ib];
    if( tmp_pred < 0) tmp_pred = 0;
    double tmp_stat = final_pred_stat[ib];
    double tmp_sys = sysunc_all[ib];

    std::string addstr ="& " + (std::to_string(tmp_pred)).substr(0,5) + " $\\pm$ " + (std::to_string(tmp_stat)).substr(0,5) + " $\\pm$ " + (std::to_string(tmp_sys)).substr(0,5) + " \\\\";

    std::string outstr = get_searchBins_defstr(ib,addstr);
    //printf("%s", outstr.c_str());
    std::cout<<outstr; 
  }
  std::cout<<std::endl<<std::endl;
  return ;
}

void SysUncs::printFinalPred()
{
  TCanvas *c = new TCanvas("c","",200,10,700,500);
  gStyle->SetOptStat(0);

  TH1D *h_pred_sb = new TH1D("h_pred_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    double e = std::sqrt(sysunc_all[i_cal]*sysunc_all[i_cal] + final_pred_stat[i_cal]*final_pred_stat[i_cal]);
    h_pred_sb->SetBinContent( i_cal+1 , final_pred[i_cal] );
    h_pred_sb->SetBinError( i_cal+1 , e );
  }
  h_pred_sb->GetXaxis()->SetTitle("Search Bins");
  h_pred_sb->Draw("e0");

  const std::string titre="CMS Preliminary 2015, 2.2 fb^{-1}, #sqrt{s} = 13 TeV";

  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);
  title->Draw("same");
 
  c->SaveAs( "_sb_Data.png" );
  c->SaveAs( "_sb_Data.pdf" );
  c->SaveAs( "_sb_Data.C" );
  return ;
}
