#include <string>
#include <iostream>
#include <vector>

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
