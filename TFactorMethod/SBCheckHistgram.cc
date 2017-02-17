#include "SBCheckHistgram.h"

void SBCheckHistgram::BookHistgram(const char *outFileName)
{ 
  oFile = new TFile(outFileName, "recreate");
  
  for( Int_t i = 0 ; i < NSEARCH_BINS ; i++ )
  {
    std::string sb_index = std::to_string(i);
    for( Int_t j = 0 ; j < BCBin ; j++ )
    {
      std::string smalltag;

      if (j == 0) smalltag = "LL";
      else if (j == 1) smalltag = "HadTau";
      else if (j == 2) smalltag = "Zinv";
      else if (j == 3) smalltag = "QCD";
      else if (j == 4) smalltag = "TTZ";
      else { smalltag = "XXX"; std::cout << "what the fuck ??!!" << std::endl; }

      h_b_met_MC[i][j]     = new TH1D( ("h_b_met_MC_SB_"     + sb_index + "_" + smalltag).c_str(),"",20,150,550);
      h_b_mt2_MC[i][j]     = new TH1D( ("h_b_mt2_MC_SB_"     + sb_index + "_" + smalltag).c_str(),"",20,200,600);
      h_b_ht_MC[i][j]      = new TH1D( ("h_b_ht_MC_SB_"      + sb_index + "_" + smalltag).c_str(),"",50,500,3000);
      h_b_mht_MC[i][j]     = new TH1D( ("h_b_mht_MC_SB_"     + sb_index + "_" + smalltag).c_str(),"",50,0,1000);
      h_b_njets30_MC[i][j] = new TH1D( ("h_b_njets30_MC_SB_" + sb_index + "_" + smalltag).c_str(),"",10,4,14);
      h_b_njets50_MC[i][j] = new TH1D( ("h_b_njets50_MC_SB_" + sb_index + "_" + smalltag).c_str(),"",15,2,17);

      h_b_met_MC[i][j]->SetFillColor(i+2);
      h_b_mt2_MC[i][j]->SetFillColor(i+2);
      h_b_ht_MC[i][j]->SetFillColor(i+2);
      h_b_mht_MC[i][j]->SetFillColor(i+2);
      h_b_njets30_MC[i][j]->SetFillColor(i+2);
      h_b_njets50_MC[i][j]->SetFillColor(i+2);

      h_b_met_MC[i][j]->SetLineColor(i+2);
      h_b_mt2_MC[i][j]->SetLineColor(i+2);
      h_b_ht_MC[i][j]->SetLineColor(i+2);
      h_b_mht_MC[i][j]->SetLineColor(i+2);
      h_b_njets30_MC[i][j]->SetLineColor(i+2);
      h_b_njets50_MC[i][j]->SetLineColor(i+2);
    }

    h_b_met_Data[i]     = new TH1D(("h_b_met_Data_SB_"     + sb_index).c_str(),"",20,150,550);
    h_b_mt2_Data[i]     = new TH1D(("h_b_mt2_Data_SB_"     + sb_index).c_str(),"",20,200,600);
    h_b_ht_Data[i]      = new TH1D(("h_b_ht_Data_SB_"      + sb_index).c_str(),"",50,500,3000);
    h_b_mht_Data[i]     = new TH1D(("h_b_mht_Data_SB_"     + sb_index).c_str(),"",50,0,1000);
    h_b_njets30_Data[i] = new TH1D(("h_b_njets30_Data_SB_" + sb_index).c_str(),"",10,4,14);
    h_b_njets50_Data[i] = new TH1D(("h_b_njets50_Data_SB_" + sb_index).c_str(),"",15,2,17);

    h_b_pfcalometr_Data[i] = new TH1D(("h_b_pfcalometr_Data_SB_" + sb_index).c_str(),"",10,0,10);
  }

  h_Data_x_ht24_y_ht50 = new TH2D("h_Data_x_ht24_y_ht50","",60,0,3000,60,0,3000);

  return ;
}
