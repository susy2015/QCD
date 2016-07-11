#include "CalHistgram.h"

void CalHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");
  //closure plots on different variables
  for( int i = 0 ; i < MET_BINS ; i++ )
  {
    for( int j = 0 ; j < MT2_BINS ; j++ )
    {
      std::string met_index = std::to_string(i);
      std::string mt2_index = std::to_string(j);
      if( i!= MET_BINS-1) h_cal_met_MC[i][j] = new TH1D( ("h_cal_met_MC_" + met_index + mt2_index).c_str(),"",20,metbins_edge[i],metbins_edge[i+1]);
      else h_cal_met_MC[i][j] = new TH1D( ("h_cal_met_MC_" + met_index + mt2_index).c_str(),"",20,metbins_edge[i],20000);
    }
  }
  return ;
}
