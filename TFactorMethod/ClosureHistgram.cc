#include "ClosureHistgram.h"

void ClosureHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");
  //closure plots on different variables
  h_pred_met = new TH1D("h_pred_met","",50,0,1000);
  h_pred_njets30 = new TH1D("h_pred_njets30","",20,0,20);
  h_pred_njets50 = new TH1D("h_pred_njets50","",20,0,20);
  h_pred_mt2 = new TH1D("h_pred_mt2","",50,0,1000);
  h_pred_ht = new TH1D("h_pred_ht","",60,0,3000);
  h_pred_mht = new TH1D("h_pred_mht","",50,0,1000);
  h_pred_ntopjets = new TH1D("h_pred_ntopjets","",20,0,20);
  h_pred_nbjets = new TH1D("h_pred_nbjets","",20,0,20);

  h_exp_met = new TH1D("h_exp_met","",50,0,1000);
  h_exp_njets30 = new TH1D("h_exp_njets30","",20,0,20);
  h_exp_njets50 = new TH1D("h_exp_njets50","",20,0,20);
  h_exp_mt2 = new TH1D("h_exp_mt2","",50,0,1000);
  h_exp_ht = new TH1D("h_exp_ht","",60,0,3000);
  h_exp_mht = new TH1D("h_exp_mht","",50,0,1000);
  h_exp_ntopjets = new TH1D("h_exp_ntopjets","",20,0,20);
  h_exp_nbjets = new TH1D("h_exp_nbjets","",20,0,20);

  h_exp_sb = new TH1D("h_exp_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_pred_sb = new TH1D("h_pred_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  return ;
}

void ClosureHistgram::printQCDClosureExp( double (&nQCD_exp_sb)[NSEARCH_BINS], double (&nQCD_exp_sb_err)[NSEARCH_BINS] )
{
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    std::cout << nQCD_exp_sb[i_cal] << "," << std::endl;
    h_exp_sb->SetBinContent( i_cal+1 , nQCD_exp_sb[i_cal] );
    h_exp_sb->SetBinError( i_cal+1 , nQCD_exp_sb_err[i_cal] );
  }
  return ;
}

void ClosureHistgram::printQCDClosurePred( double (&nQCD_pred_sb)[NSEARCH_BINS], double (&nQCD_pred_sb_err)[NSEARCH_BINS] )
{
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    std::cout << nQCD_pred_sb[i_cal] << "," << std::endl;
    h_pred_sb->SetBinContent( i_cal+1 , nQCD_pred_sb[i_cal] );
    h_pred_sb->SetBinError( i_cal+1 , nQCD_pred_sb_err[i_cal] );
  }
  return ;
}

