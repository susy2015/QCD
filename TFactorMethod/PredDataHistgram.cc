#include "PredDataHistgram.h"

void PredDataHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");
  //closure plots on different variables
  h_pred_data_met = new TH1D("h_pred_data_met","",40,0,2000);
  h_pred_data_njets30 = new TH1D("h_pred_data_njets30","",20,0,20);
  h_pred_data_njets50 = new TH1D("h_pred_data_njets50","",20,0,20);
  h_pred_data_mt2 = new TH1D("h_pred_data_mt2","",40,0,2000);
  h_pred_data_ht = new TH1D("h_pred_data_ht","",60,0,3000);
  h_pred_data_mht = new TH1D("h_pred_data_mht","",20,0,1000);
  h_pred_data_ntopjets = new TH1D("h_pred_data_ntopjets","",20,0,20);
  h_pred_data_nbjets = new TH1D("h_pred_data_nbjets","",20,0,20);

  h_pred_otherbg_met = new TH1D("h_pred_otherbg_met","",40,0,2000);
  h_pred_otherbg_njets30 = new TH1D("h_pred_otherbg_njets30","",20,0,20);
  h_pred_otherbg_njets50 = new TH1D("h_pred_otherbg_njets50","",20,0,20);
  h_pred_otherbg_mt2 = new TH1D("h_pred_otherbg_mt2","",40,0,2000);
  h_pred_otherbg_ht = new TH1D("h_pred_otherbg_ht","",60,0,3000);
  h_pred_otherbg_mht = new TH1D("h_pred_otherbg_mht","",20,0,1000);
  h_pred_otherbg_ntopjets = new TH1D("h_pred_otherbg_ntopjets","",20,0,20);
  h_pred_otherbg_nbjets = new TH1D("h_pred_otherbg_nbjets","",20,0,20);

  return ;
}
