#include "ClosureUncAUX.h"

void ClosureUncAUX::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");

  h_nMC_exp_sb = new TH1D("h_nMC_exp_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_nMC_pred_sb = new TH1D("h_nMC_pred_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  h_nMC_exp_x_met_y_mt2 = new TH2D("h_nMC_exp_x_met_y_mt2","",40,0,2000,40,0,2000);
  h_nMC_exp_x_met_y_ht = new TH2D("h_nMC_exp_x_met_y_ht","",40,0,2000,60,0,3000);

  h_nMC_pred_x_met_y_mt2 = new TH2D("h_nMC_pred_x_met_y_mt2","",40,0,2000,40,0,2000);
  h_nMC_pred_x_met_y_ht = new TH2D("h_nMC_pred_x_met_y_ht","",40,0,2000,60,0,3000);

  h_exp_x_met_y_mt2 = new TH2D("h_exp_x_met_y_mt2","",40,0,2000,40,0,2000);
  h_exp_x_met_y_ht = new TH2D("h_exp_x_met_y_ht","",40,0,2000,60,0,3000);

  h_pred_x_met_y_mt2 = new TH2D("h_pred_x_met_y_mt2","",40,0,2000,40,0,2000);
  h_pred_x_met_y_ht = new TH2D("h_pred_x_met_y_ht","",40,0,2000,60,0,3000);

  return ;
}
