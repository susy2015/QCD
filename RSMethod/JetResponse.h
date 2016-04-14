#include <string>
#include <iostream>
#include <vector>

#include "TH1D.h"
#include "TH2D.h"

#include "QCDReWeighting.h"

#include "SusyAnaTools/Tools/NTupleReader.h"
#include "SusyAnaTools/Tools/baselineDef.h"
#include "SusyAnaTools/Tools/samples.h"
#include "SusyAnaTools/Tools/searchBins.h"

#define JETPT_BINS 22
#define JETETA_BINS 11

namespace JetResponseConstant
{
  const double jetptbins_edge[JETPT_BINS+1] = {0, 20, 30, 50, 80, 120, 170, 230, 300, 380, 470, 570, 680, 800, 1000, 1300, 1700, 2200, 2800, 3500, 4300, 5200, 6500};
  const double jetetabins_edge[JETETA_BINS+1] = {0, 0.3, 0.5, 0.8, 1.1, 1.4, 1.7, 2.3, 2.8, 3.2, 4.1, 5.0};

  int Set_jetptbin_number( double jetpt );
  int Set_jetetabin_number( double jeteta );
}

int JetResponseConstant::Set_jetptbin_number( double jetpt )
{
  int jetptbin_num = -1;

  for(int i=0;i<JETPT_BINS;i++)
  {
    if(i!=JETPT_BINS-1)
    {
      if(jetpt >= jetptbins_edge[i] && jetpt < jetptbins_edge[i+1]){ jetptbin_num = i; return jetptbin_num; }
    }
    else
    {
      if(jetpt >= jetptbins_edge[i]){ jetptbin_num = i; return jetptbin_num; }
    }
  }

  return jetptbin_num;
}

int JetResponseConstant::Set_jetetabin_number( double jeteta )
{
  jeteta = std::abs( jeteta );//get only positive number

  int jetetabin_num = -1;

  for(int i=0;i<JETETA_BINS;i++)
  {
    if(i!=JETETA_BINS-1)
    {
      if(jeteta >= jetetabins_edge[i] && jeteta < jetetabins_edge[i+1]){ jetetabin_num = i; return jetetabin_num; }
    }
    else
    {
      if(jeteta >= jetetabins_edge[i]){ jetetabin_num = i; return jetetabin_num; }
    }
  }

  return jetetabin_num;
}

static BaselineVessel *myBaselineVessel;
void mypassBaselineFunc(NTupleReader& tr)
{
  (*myBaselineVessel)(tr);
}

class JetResponseHistgram
{
 public:
  void BookHistgram(const char *);
  TFile *oFile;
  
  TH2D *h_QCDMC_MET_MT2_Corr;
  TH1D *h_QCDMC_JetResponseFunction[JETPT_BINS][JETETA_BINS];
};

void JetResponseHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");

  h_QCDMC_MET_MT2_Corr = new TH2D("h_QCDMC_MET_MT2_Corr","",500,0,1000,50,0,1000);
  
  for( int i = 0 ; i < JETPT_BINS ; i++ )
  {
    for( int j = 0 ; j < JETETA_BINS ; j++ )
    {
      std::string jetpt_index = std::to_string(i);
      std::string jeteta_index = std::to_string(j);
			h_QCDMC_JetResponseFunction[i][j] = new TH1D( ("h_QCDMC_JetResponseFunction_" + jetpt_index + "_" + jeteta_index).c_str(),"",20, 0, 5);
 			//if( i!= MET_BINS-1) h_cal_met_MC[i][j] = new TH1D( ("h_cal_met_MC_" + met_index + mt2_index).c_str(),"",20, metbins_edge[i], metbins_edge[i+1]);
      //else h_cal_met_MC[i][j] = new TH1D( ("h_cal_met_MC_" + met_index + mt2_index).c_str(),"",20, metbins_edge[i],20000);
    }
  }
  
  return ;
}

