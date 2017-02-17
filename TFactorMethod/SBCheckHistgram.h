#include <iostream>

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include "ConstantsSnippet.h"

class SBCheckHistgram
{
 public:
  void BookHistgram(const char *);
  TFile *oFile;

  TH1D *h_b_met_MC[NSEARCH_BINS][BCBin], *h_b_mt2_MC[NSEARCH_BINS][BCBin];
  TH1D *h_b_ht_MC[NSEARCH_BINS][BCBin], *h_b_mht_MC[NSEARCH_BINS][BCBin], *h_b_njets30_MC[NSEARCH_BINS][BCBin], *h_b_njets50_MC[NSEARCH_BINS][BCBin];

  TH1D *h_b_met_Data[NSEARCH_BINS], *h_b_mt2_Data[NSEARCH_BINS], *h_b_ntopjets_Data[NSEARCH_BINS], *h_b_nbjets_Data[NSEARCH_BINS];
  TH1D *h_b_ht_Data[NSEARCH_BINS], *h_b_mht_Data[NSEARCH_BINS], *h_b_njets30_Data[NSEARCH_BINS], *h_b_njets50_Data[NSEARCH_BINS];

  TH1D *h_b_pfcalometr_Data[NSEARCH_BINS];

  TH2D *h_Data_x_ht24_y_ht50;

};

