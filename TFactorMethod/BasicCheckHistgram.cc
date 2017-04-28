#include "BasicCheckHistgram.h"

void BasicCheckHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");

  for( Int_t i = 0 ; i < BCBin ; i++ )
  {
    std::string smalltag;

    if (i == 0) smalltag = "LL";
    else if (i == 1) smalltag = "HadTau";
    else if (i == 2) smalltag = "Zinv";
    else if (i == 3) smalltag = "QCD";
    else if (i == 4) smalltag = "TTZRare";
    else if (i == 5) smalltag = "AllHadTTJetsWJetsST";

    h_b_met_MC[i] = new TH1D( ("h_b_met_MC_" + smalltag).c_str(),"",20,200,600);
    h_b_njets30_MC[i] = new TH1D( ("h_b_njets30_MC_" + smalltag).c_str(),"",10,4,14);
    h_b_njets50_MC[i] = new TH1D( ("h_b_njets50_MC_" + smalltag).c_str(),"",15,2,17);
    h_b_mt2_MC[i] = new TH1D( ("h_b_mt2_MC_" + smalltag).c_str(),"",20,200,600);
    h_b_ht_MC[i] = new TH1D( ("h_b_ht_MC_" + smalltag).c_str(),"",50,300,2800);
    h_b_mht_MC[i] = new TH1D( ("h_b_mht_MC_" + smalltag).c_str(),"",50,0,1000);
    h_b_ntopjets_MC[i] = new TH1D( ("h_b_ntopjets_MC_" + smalltag).c_str(),"",5,1,6);
    h_b_nbjets_MC[i] = new TH1D( ("h_b_nbjets_MC_" + smalltag).c_str(),"",5,1,6);

    h_b_sb_MC[i] = new TH1D( ("h_b_sb_MC_" + smalltag).c_str(),"",60,0,60);

    h_b_met_MC[i]->SetFillColor(i+2);
    h_b_mt2_MC[i]->SetFillColor(i+2);
    h_b_ntopjets_MC[i]->SetFillColor(i+2);
    h_b_nbjets_MC[i]->SetFillColor(i+2);
    h_b_ht_MC[i]->SetFillColor(i+2);
    h_b_mht_MC[i]->SetFillColor(i+2);
    h_b_njets30_MC[i]->SetFillColor(i+2);
    h_b_njets50_MC[i]->SetFillColor(i+2);

    h_b_sb_MC[i]->SetFillColor(i+2);

    h_b_met_MC[i]->SetLineColor(i+2);
    h_b_mt2_MC[i]->SetLineColor(i+2);
    h_b_ntopjets_MC[i]->SetLineColor(i+2);
    h_b_nbjets_MC[i]->SetLineColor(i+2);
    h_b_ht_MC[i]->SetLineColor(i+2);
    h_b_mht_MC[i]->SetLineColor(i+2);
    h_b_njets30_MC[i]->SetLineColor(i+2);
    h_b_njets50_MC[i]->SetLineColor(i+2);

    h_b_sb_MC[i]->SetLineColor(i+2);
  }

  h_b_met_Data = new TH1D("h_b_met_Data","",20,200,600);
  h_b_njets30_Data = new TH1D("h_b_njets30_Data","",10,4,14);
  h_b_njets50_Data = new TH1D("h_b_njets50_Data","",15,2,17);
  h_b_mt2_Data = new TH1D("h_b_mt2_Data","",20,200,600);
  h_b_ht_Data = new TH1D("h_b_ht_Data","",50,300,2800);
  h_b_mht_Data = new TH1D("h_b_mht_Data","",50,0,1000);
  h_b_ntopjets_Data = new TH1D("h_b_ntopjets_Data","",5,1,6);
  h_b_nbjets_Data = new TH1D("h_b_nbjets_Data","",5,1,6);

  h_b_sb_Data = new TH1D("h_b_sb_Data","",60,0,60);

  return ;
}
