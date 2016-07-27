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

#include "QCDBinFunction.h"

#include "QCDHardCodedInput/SysHeader.h"
//#include "SysHeader45.h"
//#include "SysHeader37.h"

#include "Math/QuantFuncMathCore.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"

#include "CMSStylePlot/CMS_lumi.h"
//#include "CMSStylePlot/tdrstyle.h"
//SearchBins mySearchBins("SB_37_2015");
//SearchBins mySearchBins("SB_45_2015");
SearchBins mySearchBins("SB_59_2016");

class SysUncs
{
 public:
  std::string sysunc_type;

  TFile * finPred;
  TList * listPred;

  TFile * finSysUnc;
  TList * listSysUnc;

  double final_pred[NSEARCH_BINS] = {0},final_pred_stat_up[NSEARCH_BINS] = {0}, final_pred_stat_dn[NSEARCH_BINS] = {0};
  double sysunc_tfactors[NSEARCH_BINS] = {0}, sysunc_nonclosure[NSEARCH_BINS] = {0};
  double sysunc_all_up[NSEARCH_BINS] = {0}, sysunc_all_dn[NSEARCH_BINS] = {0};

  void GetCentralPred();
  void GetTFactorsSysUnc();
  void GetNonClosureSysUnc();
  void combineSysUncs();
  void printSysUncs();
  
  void printLatexTable();
  void printFinalPred();
};

void SysUncs::GetCentralPred()
{
  for (int i = 0; i < NSEARCH_BINS ; i++)
  {
    final_pred[i] = (head_QCD_Data_CS[i] - head_QCD_otherBG_CS[i]) * head_QCD_TFactor[i];
    const double alpha = 1 - 0.6827;
    double N = head_QCD_Data_CS[i];
    final_pred_stat_dn[i] = (N==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,N,1.));
    final_pred_stat_dn[i] = (N-final_pred_stat_dn[i]) * head_QCD_TFactor[i];
    final_pred_stat_up[i] = ROOT::Math::gamma_quantile_c(alpha/2,N+1,1);
    final_pred_stat_up[i] = (final_pred_stat_up[i]-N) * head_QCD_TFactor[i];
  }

  std::cout << "Done with Cental Pred setting!" << std::endl;
  return ;
}

void SysUncs::GetTFactorsSysUnc()
{ 
  std::cout << "Setting TFactor Unc from SysHeader.h... " << std::endl;
  for (int i = 0; i < NSEARCH_BINS ; i++)
  { 
    sysunc_tfactors[i] = head_QCD_TFactor_relative_err[i];
  }
  return ;
}

void SysUncs::GetNonClosureSysUnc()
{
  std::cout << "Setting NonClosure Unc from SysHeader.h... " << std::endl;
  for (int i = 0; i < NSEARCH_BINS ; i++)
  {
    sysunc_nonclosure[i] = head_QCD_NonClosure_relative_err[i];
  }
  return ;
}

void SysUncs::combineSysUncs()
{
  for(int i=0;i<NSEARCH_BINS;i++)
  {
    sysunc_all_up[i] = head_QCD_TFactor[i]*head_QCD_otherBG_CS[i]*head_QCD_otherBG_sysup[i];
    sysunc_all_dn[i] = head_QCD_TFactor[i]*head_QCD_otherBG_CS[i]*head_QCD_otherBG_sysdn[i];

    if( final_pred[i] > 0 )
    {
      sysunc_all_up[i] += final_pred[i] * std::sqrt(sysunc_tfactors[i]*sysunc_tfactors[i] + sysunc_nonclosure[i]*sysunc_nonclosure[i]);
      sysunc_all_dn[i] += final_pred[i] * std::sqrt(sysunc_tfactors[i]*sysunc_tfactors[i] + sysunc_nonclosure[i]*sysunc_nonclosure[i]);
    }
  }
  return ;
}

void SysUncs::printSysUncs()
{
  for(int i=0;i<NSEARCH_BINS;i++)
  {
    std::cout << "SB: "<< i << ", SysUnc_All(up): " << sysunc_all_up[i] << ", SysUnc_All(dn): " << sysunc_all_dn[i] << ", SysUnc_TFactor: "<< sysunc_tfactors[i] << ", SysUnc_NonClosure: " << sysunc_nonclosure[i] << std::endl;
  }
  return ;
}

void SysUncs::printLatexTable()
{
  std::vector<std::vector<std::vector<double> > > out_MT2_met_Binning;
  mySearchBins.build_MT2_met_Binning(out_MT2_met_Binning);
  mySearchBins.print_searchBins_headerstr("& QCD Prediction\\\\");
  int nTotBins = mySearchBins.nSearchBins();
  for(int ib=0; ib<nTotBins; ib++)
  {
    double tmp_pred = final_pred[ib];
    if( tmp_pred < 0) tmp_pred = 0;
    double tmp_stat_up = final_pred_stat_up[ib];
    double tmp_stat_dn = final_pred_stat_dn[ib];
    double tmp_sys_up = sysunc_all_up[ib];
    double tmp_sys_dn = sysunc_all_dn[ib];

    std::string addstr ="& " + (std::to_string(tmp_pred)).substr(0,5) + " $^{+" + (std::to_string(tmp_stat_up)).substr(0,5) + "}_{-" + (std::to_string(tmp_stat_dn)).substr(0,5) + "}$ " + " $^{+" + (std::to_string(tmp_sys_up)).substr(0,5) + "}_{-" + (std::to_string(tmp_sys_dn)).substr(0,5) + "}$ " + " \\\\";
    //std::string addstr ="& " + (std::to_string(tmp_pred)).substr(0,5) + " $\\pm$ " + (std::to_string(tmp_stat)).substr(0,5) + " $^{+" + (std::to_string(tmp_sys_up)).substr(0,5) + "}_{-" + (std::to_string(tmp_sys_dn)).substr(0,5) + "}$ " + " \\\\";

    std::string outstr = mySearchBins.get_searchBins_defstr(ib,addstr);
    //printf("%s", outstr.c_str());
    std::cout<< outstr; 
  }
  std::cout<<std::endl<<std::endl;
  return ;
}

void SysUncs::printFinalPred()
{
  TCanvas *c = new TCanvas("c","",50,50,800,600);

  gStyle->SetOptStat(0);

  TH1D *h_pred_sb_data = new TH1D("h_pred_sb_data","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  //h->SetBinErrorOption(TH1::kPoisson);

  /*
  h_pred_sb_data->SetMarkerStyle(20);
  h_pred_sb_data->SetMarkerColor(kBlue);
  h_pred_sb_data->SetLineColor(h_pred_sb_data->GetMarkerColor());
  h_pred_sb_data->SetMarkerSize(0.9);

  h_pred_sb_data->GetYaxis()->SetTitleOffset(0.9);
  h_pred_sb_data->GetYaxis()->SetTitleFont(42);
  h_pred_sb_data->GetYaxis()->SetTitleSize(0.045);
  h_pred_sb_data->GetYaxis()->SetLabelSize(0.04);
  h_pred_sb_data->GetYaxis()->SetLabelFont(42);
  h_pred_sb_data->GetYaxis()->SetTitle("Events");
  h_pred_sb_data->GetXaxis()->SetTitleOffset(0.9);
  h_pred_sb_data->GetXaxis()->SetTitleFont(42);
  h_pred_sb_data->GetXaxis()->SetTitleSize(0.045);
  h_pred_sb_data->GetXaxis()->SetLabelSize(0.04);
  h_pred_sb_data->GetXaxis()->SetLabelFont(42);
  h_pred_sb_data->GetXaxis()->SetTitle("Search region bin number");

  h_pred_sb_data->GetYaxis()->SetRangeUser(0,18);
  */

  h_pred_sb_data->GetYaxis()->SetRangeUser(0,20);
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    final_pred[i_cal] > 0 ? h_pred_sb_data->SetBinContent( i_cal+1 , final_pred[i_cal] ) : h_pred_sb_data->SetBinContent( i_cal+1 , 0 ) ;
  }
 
  //h_pred_sb_data->Draw("e0");
  TGraphAsymmErrors * g = new TGraphAsymmErrors(h_pred_sb_data);
  g->SetMarkerSize(0.5);
  g->SetMarkerStyle (20);

  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    double N = h_pred_sb_data->GetBinContent( i_cal+1 ); 
    double e_up = std::sqrt( sysunc_all_up[i_cal]*sysunc_all_up[i_cal] + final_pred_stat_up[i_cal]*final_pred_stat_up[i_cal] );
    double e_dn = std::sqrt( sysunc_all_dn[i_cal]*sysunc_all_dn[i_cal] + final_pred_stat_dn[i_cal]*final_pred_stat_dn[i_cal] );

    //std::cout << "test on e_dn" << e_dn << std::endl;
    g->SetPointEYlow(i_cal, e_dn);
    g->SetPointEYhigh(i_cal, e_up);
  }
  g->GetXaxis()->SetRangeUser(0,NSEARCH_BINS+1);
  g->GetYaxis()->SetRangeUser(0,100);
  g->Draw("AP");

  mySearchBins.drawSBregionDef(0.0,100.0,false);
  CMSStylePlot::CMS_lumi( c, 4, 0 );

  c->SaveAs( "_sb_Data.png" );
  c->SaveAs( "_sb_Data.pdf" );
  c->SaveAs( "_sb_Data.C" );
  return ;
}
