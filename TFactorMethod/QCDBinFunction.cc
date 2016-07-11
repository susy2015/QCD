#include "QCDBinFunction.h"

int QCDBGModel::Set_metbin_number( double met )
{
  int metbin_num = -1;

  for(int i=0;i<MET_BINS;i++)
  {
    if(i!=MET_BINS-1)
    {
      if(met >= metbins_edge[i] && met < metbins_edge[i+1]){ metbin_num = i; return metbin_num; }
    }
    else
    {
      if(met >= metbins_edge[i]){ metbin_num = i; return metbin_num; }
    }
  }

  return metbin_num;
}

int QCDBGModel::Set_njetsbin_number( int njets )
{
  int njetsbin_num;

  //if( njets == 1 )
  if( njets >= 4 && njets <= 6 )
  {
    njetsbin_num = 0;
  }
  //else if( njets == 2 )
  else if( njets >= 7 && njets <= 8 )
  {
    njetsbin_num = 1;
  }
  //else if( njets >= 3 )
  else if( njets >= 9 )
  {
    njetsbin_num = 2;
  }
  else
  {
    njetsbin_num = -1;
  } 
  return njetsbin_num;
}

int QCDBGModel::Set_mt2bin_number( double mt2 )
{
  int mt2bin_num = -1;

  for(int i=0;i<MT2_BINS;i++)
  {
    if(i!=MT2_BINS-1)
    {
      if(mt2 >= mt2bins_edge[i] && mt2 < mt2bins_edge[i+1]){ mt2bin_num = i; return mt2bin_num; }
    }
    else
    {
      if(mt2 >= mt2bins_edge[i]){ mt2bin_num = i; return mt2bin_num; }
    }
  }
  return mt2bin_num;
}

