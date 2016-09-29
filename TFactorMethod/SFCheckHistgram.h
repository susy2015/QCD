#include <iostream>

#include "TFile.h"
#include "TH1D.h"

#include "ConstantsSnippet.h"

class SFCheckHistgram
{
 public:
  void BookHistgram(const char *);

  TFile *oFile;

  TH1D *h_b_met_MC[SFMCBin], *h_b_mt2_MC[SFMCBin], *h_b_ntopjets_MC[SFMCBin], *h_b_nbjets_MC[SFMCBin];
  TH1D *h_b_ht_MC[SFMCBin], *h_b_mht_MC[SFMCBin], *h_b_njets30_MC[SFMCBin], *h_b_njets50_MC[SFMCBin];
  TH1D *h_b_sb_MC[SFMCBin];

  TH1D *h_b_met_Data, *h_b_mt2_Data, *h_b_ntopjets_Data, *h_b_nbjets_Data;
  TH1D *h_b_ht_Data, *h_b_mht_Data, *h_b_njets30_Data, *h_b_njets50_Data;
  TH1D *h_b_sb_Data;
  //TH1D *h_b_mt2_nbnt, *h_b_mt2_ybyt, *h_b_met_nbnt, *h_b_met_ybyt;
  //TH1D *h_b_dphi0_nbnt, *h_b_dphi0_ybyt, *h_b_dphi1_nbnt, *h_b_dphi1_ybyt, *h_b_dphi2_nbnt, *h_b_dphi2_ybyt;
  //TH1D *h_inverted_met, *h_inverted_njets, *h_inverted_mt2, *h_inverted_ht, *h_inverted_mht, *h_inverted_ntopjets, *h_inverted_nbjets;
};

