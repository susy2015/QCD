#include "TFile.h"
#include "TH1D.h"

#include "ConstantsSnippet.h"

class ClosureHistgram
{
 public:
  void BookHistgram(const char *);
  TFile *oFile;
  //closure plots on different variables and search bins
  TH1D *h_pred_met, *h_pred_njets30, *h_pred_njets50, *h_pred_mt2, *h_pred_ht, *h_pred_mht, *h_pred_ntopjets, *h_pred_nbjets;
  TH1D *h_exp_met, *h_exp_njets30, *h_exp_njets50, *h_exp_mt2, *h_exp_ht, *h_exp_mht, *h_exp_ntopjets, *h_exp_nbjets;
  TH1D *h_exp_sb, *h_pred_sb;
};
