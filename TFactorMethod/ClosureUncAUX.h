#include <iostream>

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include "ConstantsSnippet.h"

class ClosureUncAUX
{
 public:
  void BookHistgram(const char *);
  TFile *oFile;
  //closure plots on different variables and search bins
  TH1D *h_nMC_exp_sb, *h_nMC_pred_sb;
  TH2D *h_nMC_exp_x_met_y_mt2, *h_nMC_exp_x_met_y_ht, *h_nMC_pred_x_met_y_mt2, *h_nMC_pred_x_met_y_ht;
  TH2D *h_exp_x_met_y_mt2, *h_exp_x_met_y_ht, *h_pred_x_met_y_mt2, *h_pred_x_met_y_ht;
};
