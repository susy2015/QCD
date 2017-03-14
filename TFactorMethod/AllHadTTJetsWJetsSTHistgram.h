#include <iostream>

#include "TFile.h"
#include "TH1D.h"

#include "ConstantsSnippet.h"

class AllHadTTJetsWJetsSTHistgram
{
 public:
  void BookHistgram(const char *);
  TFile *oFile;
  //closure plots on different variables and search bins
  TH1D *h_cr_lept_met, *h_cr_lept_njets30, *h_cr_lept_njets50, *h_cr_lept_mt2, *h_cr_lept_ht, *h_cr_lept_mht, *h_cr_lept_ntopjets, *h_cr_lept_nbjets, *h_cr_lept_sb;
  TH1D *h_cr_had_met, *h_cr_had_njets30, *h_cr_had_njets50, *h_cr_had_mt2, *h_cr_had_ht, *h_cr_had_mht, *h_cr_had_ntopjets, *h_cr_had_nbjets, *h_cr_had_sb;
  TH1D *h_cr_data_met, *h_cr_data_njets30, *h_cr_data_njets50, *h_cr_data_mt2, *h_cr_data_ht, *h_cr_data_mht, *h_cr_data_ntopjets, *h_cr_data_nbjets, *h_cr_data_sb;

  TH1D *h_sr_lept_met, *h_sr_lept_njets30, *h_sr_lept_njets50, *h_sr_lept_mt2, *h_sr_lept_ht, *h_sr_lept_mht, *h_sr_lept_ntopjets, *h_sr_lept_nbjets, *h_sr_lept_sb;
  TH1D *h_sr_had_met, *h_sr_had_njets30, *h_sr_had_njets50, *h_sr_had_mt2, *h_sr_had_ht, *h_sr_had_mht, *h_sr_had_ntopjets, *h_sr_had_nbjets, *h_sr_had_sb;
  TH1D *h_sr_data_met, *h_sr_data_njets30, *h_sr_data_njets50, *h_sr_data_mt2, *h_sr_data_ht, *h_sr_data_mht, *h_sr_data_ntopjets, *h_sr_data_nbjets, *h_sr_data_sb;

  //compare with QCD prediction! can not trust the xSec if we use ttjets and qcd together
  TH1D *h_sr_qcd_sb;
};
