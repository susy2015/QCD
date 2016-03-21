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
//#include "SusyAnaTools/Tools/CMS_lumi.h"

#include "QCDReWeighting.h"
#include "QCDBinFunction.h"
#include "SysHeader.h"

#include "CMSStylePlot/CMS_lumi.h"
//#include "CMSStylePlot/tdrstyle.h"

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
  double sysunc_all_up[NSEARCH_BINS] = {0}, sysunc_all_down[NSEARCH_BINS] = {0};

  void Initialization(std::string type); 
  void Reset();

  void GetCentralPred();
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

  if( type == "TFactorsUnc" )
  {
    //finPred = TFile::Open("PredQCDData.root");
    //listPred = finPred->GetListOfKeys();

    //finSysUnc = TFile::Open("TFactorsUnc.root");
    //listSysUnc = finSysUnc->GetListOfKeys();
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

void SysUncs::GetCentralPred()
{
  finPred = TFile::Open("PredQCDData.root");
  listPred = finPred->GetListOfKeys();

  TH1D * h_pred;

  int NPredHist;
  NPredHist = listPred->GetSize();

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

  finPred->Close();
  listPred->Clear();
  std::cout << "Done with Cental Pred setting! Resetting the file and list object!" << std::endl;
  return ;
}

void SysUncs::GetTFactorsSysUnc()
{ 
  /*
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
    if( TString(listPred->At(i)->GetName()).Contains( "_TFactorsUnc_up_0" ) ) continue;
    if( TString(listPred->At(i)->GetName()).Contains( "_TFactorsUnc_down_" ) ) continue;

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
          d = 0; 
          //std::cout << i << "Zero Sys Unc from Tfactors" <<std::endl; 
        }
        sysunc_tfactors[j-1] += d*d;
      }
      h_sysunc->Reset();
    }
  }
  */
  for (int i = 0; i < NSEARCH_BINS ; i++)
  { 
    sysunc_tfactors[i] = head_QCD_TFactor_relative_err[i];
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
      double r = sysunc/pred;
      e = std::sqrt( sysunc_err*sysunc_err + pred_err*pred_err*r*r ) / pred;
      sysunc_nonclosure[j-1] = std::max( std::abs(e) , std::abs((sysunc-pred)/pred) );
      std::cout << "j: " << j << " Pred: "<< pred << " Exp: "<< sysunc << " Error: " << e << std::endl;
    }
    else if( j!=1 && ((pred <= 0) || (sysunc <= 0)) ){ sysunc_nonclosure[j-1] = std::abs(sysunc-pred); }
    else { std::cout << "First Bin have werid behavior, too bad, WTF??!!" << std::endl; return ;}
  }

  std::cout << "QCD_NonClosure_relative_err = ";
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    std::cout << sysunc_nonclosure[i_cal] << " ";
    if(i_cal == NSEARCH_BINS -1 ) std::cout << std::endl;
  }

  return ;
}

void SysUncs::combineSysUncs()
{
  for(int i=0;i<NSEARCH_BINS;i++)
  {
    sysunc_all_up[i] = head_QCD_otherBG_sysup[i];
    sysunc_all_down[i] = head_QCD_otherBG_sysdown[i];

    if( final_pred[i] > 0 )
    {
      sysunc_all_up[i] += final_pred[i] * std::sqrt(sysunc_tfactors[i]*sysunc_tfactors[i] + sysunc_nonclosure[i]*sysunc_nonclosure[i]);
      sysunc_all_down[i] += final_pred[i] * std::sqrt(sysunc_tfactors[i]*sysunc_tfactors[i] + sysunc_nonclosure[i]*sysunc_nonclosure[i]);
    }
  }
  return ;
}

void SysUncs::printSysUncs()
{
  for(int i=0;i<NSEARCH_BINS;i++)
  {
    std::cout << "SB: "<< i << ", SysUnc_All(up): " << sysunc_all_up[i] << ", SysUnc_All(down): " << sysunc_all_down[i] << ", SysUnc_TFactor: "<< sysunc_tfactors[i] << ", SysUnc_NonClosure: " << sysunc_nonclosure[i] << std::endl;
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
    double tmp_sys_up = sysunc_all_up[ib];
    double tmp_sys_down = sysunc_all_down[ib];

    std::string addstr ="& " + (std::to_string(tmp_pred)).substr(0,5) + " $\\pm$ " + (std::to_string(tmp_stat)).substr(0,5) + " $^{+" + (std::to_string(tmp_sys_up)).substr(0,5) + "}_{-" + (std::to_string(tmp_sys_down)).substr(0,5) + "}$ " + " \\\\";

    std::string outstr = get_searchBins_defstr(ib,addstr);
    //printf("%s", outstr.c_str());
    std::cout<<outstr; 
  }
  std::cout<<std::endl<<std::endl;
  return ;
}

void SysUncs::printFinalPred()
{
  TCanvas *c = new TCanvas("c","",50,50,800,600);

  gStyle->SetOptStat(0);

  TH1D *h_pred_sb = new TH1D("h_pred_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  h_pred_sb->SetMarkerStyle(20);
  h_pred_sb->SetMarkerColor(kBlue);
  h_pred_sb->SetLineColor(h_pred_sb->GetMarkerColor());
  h_pred_sb->SetMarkerSize(0.9);

  h_pred_sb->GetYaxis()->SetTitleOffset(0.9);
  h_pred_sb->GetYaxis()->SetTitleFont(42);
  h_pred_sb->GetYaxis()->SetTitleSize(0.045);
  h_pred_sb->GetYaxis()->SetLabelSize(0.04);
  h_pred_sb->GetYaxis()->SetLabelFont(42);
  h_pred_sb->GetYaxis()->SetTitle("Events");
  h_pred_sb->GetXaxis()->SetTitleOffset(0.9);
  h_pred_sb->GetXaxis()->SetTitleFont(42);
  h_pred_sb->GetXaxis()->SetTitleSize(0.045);
  h_pred_sb->GetXaxis()->SetLabelSize(0.04);
  h_pred_sb->GetXaxis()->SetLabelFont(42);
  h_pred_sb->GetXaxis()->SetTitle("Search region bin number");

  h_pred_sb->GetYaxis()->SetRangeUser(0,18);

  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    double e = std::sqrt(sysunc_all_down[i_cal]*sysunc_all_down[i_cal] + final_pred_stat[i_cal]*final_pred_stat[i_cal]);
    final_pred[i_cal] > 0 ? h_pred_sb->SetBinContent( i_cal+1 , final_pred[i_cal] ) : h_pred_sb->SetBinContent( i_cal+1 , 0 ) ;
    h_pred_sb->SetBinError( i_cal+1 , e );
  }
  
  h_pred_sb->Draw("e0");

  drawSBregionDef(0.0, 18.0, false);
  CMSStylePlot::CMS_lumi( c, 4, 0 );

  c->SaveAs( "_sb_Data.png" );
  c->SaveAs( "_sb_Data.pdf" );
  c->SaveAs( "_sb_Data.C" );
  return ;
}
