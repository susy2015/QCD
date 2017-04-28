#include <iostream>

#include "TFile.h"
#include "TH1D.h"

class PredDataHistgram
{
 public:
  void BookHistgram(const char *);
  TFile *oFile;
  //closure plots on different variables and search bins
  TH1D *h_pred_data_met, *h_pred_data_njets30, *h_pred_data_njets50, *h_pred_data_mt2, *h_pred_data_ht, *h_pred_data_mht, *h_pred_data_ntopjets, *h_pred_data_nbjets;
  TH1D *h_pred_otherbg_met, *h_pred_otherbg_njets30, *h_pred_otherbg_njets50, *h_pred_otherbg_mt2, *h_pred_otherbg_ht, *h_pred_otherbg_mht, *h_pred_otherbg_ntopjets, *h_pred_otherbg_nbjets;
};
