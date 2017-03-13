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
  TH1D *h_lept_met, *h_lept_njets30, *h_lept_njets50, *h_lept_mt2, *h_lept_ht, *h_lept_mht, *h_lept_ntopjets, *h_lept_nbjets, *h_lept_sb;
  TH1D *h_had_met, *h_had_njets30, *h_had_njets50, *h_had_mt2, *h_had_ht, *h_had_mht, *h_had_ntopjets, *h_had_nbjets, *h_had_sb;
  TH1D *h_data_met, *h_data_njets30, *h_data_njets50, *h_data_mt2, *h_data_ht, *h_data_mht, *h_data_ntopjets, *h_data_nbjets, *h_data_sb;
};
