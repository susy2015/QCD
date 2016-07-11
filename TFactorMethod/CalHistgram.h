#include "TFile.h"
#include "TH1D.h"

#include "ConstantsSnippet.h"

class CalHistgram
{
 public:
  void BookHistgram(const char *);
  TFile *oFile;
  //closure plots on different variables and search bins
  TH1D *h_cal_met_MC[MET_BINS][MT2_BINS];
};
