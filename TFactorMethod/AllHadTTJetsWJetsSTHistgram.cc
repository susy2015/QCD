#include "AllHadTTJetsWJetsSTHistgram.h"

void AllHadTTJetsWJetsSTHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");
  //closure plots on different variables
  h_cr_lept_met = new TH1D("h_cr_lept_met","",40,0,2000);
  h_cr_lept_njets30 = new TH1D("h_cr_lept_njets30","",20,0,20);
  h_cr_lept_njets50 = new TH1D("h_cr_lept_njets50","",20,0,20);
  h_cr_lept_mt2 = new TH1D("h_cr_lept_mt2","",40,0,2000);
  h_cr_lept_ht = new TH1D("h_cr_lept_ht","",60,0,3000);
  h_cr_lept_mht = new TH1D("h_cr_lept_mht","",20,0,1000);
  h_cr_lept_ntopjets = new TH1D("h_cr_lept_ntopjets","",20,0,20);
  h_cr_lept_nbjets = new TH1D("h_cr_lept_nbjets","",20,0,20);
  h_cr_lept_sb = new TH1D("h_cr_lept_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  h_cr_had_met = new TH1D("h_cr_had_met","",40,0,2000);
  h_cr_had_njets30 = new TH1D("h_cr_had_njets30","",20,0,20);
  h_cr_had_njets50 = new TH1D("h_cr_had_njets50","",20,0,20);
  h_cr_had_mt2 = new TH1D("h_cr_had_mt2","",40,0,2000);
  h_cr_had_ht = new TH1D("h_cr_had_ht","",60,0,3000);
  h_cr_had_mht = new TH1D("h_cr_had_mht","",20,0,1000);
  h_cr_had_ntopjets = new TH1D("h_cr_had_ntopjets","",20,0,20);
  h_cr_had_nbjets = new TH1D("h_cr_had_nbjets","",20,0,20);
  h_cr_had_sb = new TH1D("h_cr_had_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  h_cr_data_met = new TH1D("h_cr_data_met","",40,0,2000);
  h_cr_data_njets30 = new TH1D("h_cr_data_njets30","",20,0,20);
  h_cr_data_njets50 = new TH1D("h_cr_data_njets50","",20,0,20);
  h_cr_data_mt2 = new TH1D("h_cr_data_mt2","",40,0,2000);
  h_cr_data_ht = new TH1D("h_cr_data_ht","",60,0,3000);
  h_cr_data_mht = new TH1D("h_cr_data_mht","",20,0,1000);
  h_cr_data_ntopjets = new TH1D("h_cr_data_ntopjets","",20,0,20);
  h_cr_data_nbjets = new TH1D("h_cr_data_nbjets","",20,0,20);
  h_cr_data_sb = new TH1D("h_cr_data_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  h_sr_lept_met = new TH1D("h_sr_lept_met","",40,0,2000);
  h_sr_lept_njets30 = new TH1D("h_sr_lept_njets30","",20,0,20);
  h_sr_lept_njets50 = new TH1D("h_sr_lept_njets50","",20,0,20);
  h_sr_lept_mt2 = new TH1D("h_sr_lept_mt2","",40,0,2000);
  h_sr_lept_ht = new TH1D("h_sr_lept_ht","",60,0,3000);
  h_sr_lept_mht = new TH1D("h_sr_lept_mht","",20,0,1000);
  h_sr_lept_ntopjets = new TH1D("h_sr_lept_ntopjets","",20,0,20);
  h_sr_lept_nbjets = new TH1D("h_sr_lept_nbjets","",20,0,20);
  h_sr_lept_sb = new TH1D("h_sr_lept_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  h_sr_had_met = new TH1D("h_sr_had_met","",40,0,2000);
  h_sr_had_njets30 = new TH1D("h_sr_had_njets30","",20,0,20);
  h_sr_had_njets50 = new TH1D("h_sr_had_njets50","",20,0,20);
  h_sr_had_mt2 = new TH1D("h_sr_had_mt2","",40,0,2000);
  h_sr_had_ht = new TH1D("h_sr_had_ht","",60,0,3000);
  h_sr_had_mht = new TH1D("h_sr_had_mht","",20,0,1000);
  h_sr_had_ntopjets = new TH1D("h_sr_had_ntopjets","",20,0,20);
  h_sr_had_nbjets = new TH1D("h_sr_had_nbjets","",20,0,20);
  h_sr_had_sb = new TH1D("h_sr_had_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  h_sr_data_met = new TH1D("h_sr_data_met","",40,0,2000);
  h_sr_data_njets30 = new TH1D("h_sr_data_njets30","",20,0,20);
  h_sr_data_njets50 = new TH1D("h_sr_data_njets50","",20,0,20);
  h_sr_data_mt2 = new TH1D("h_sr_data_mt2","",40,0,2000);
  h_sr_data_ht = new TH1D("h_sr_data_ht","",60,0,3000);
  h_sr_data_mht = new TH1D("h_sr_data_mht","",20,0,1000);
  h_sr_data_ntopjets = new TH1D("h_sr_data_ntopjets","",20,0,20);
  h_sr_data_nbjets = new TH1D("h_sr_data_nbjets","",20,0,20);
  h_sr_data_sb = new TH1D("h_sr_data_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  h_sr_qcd_sb = new TH1D("h_sr_qcd_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);

  return ;
}
