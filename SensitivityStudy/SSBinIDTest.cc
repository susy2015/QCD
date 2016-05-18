#include <iostream>
#include "SSBinFunction.h"

int main()
{
  std::cout << "Testing Search bin ID algorithm..." << std::endl;
  for(int i=-1;i<NTOPJETS_BINS+1;i++)
  {
    for(int j=-1;j<NBOTJETS_BINS+1;j++)
    {
      for(int k=-1;k<MT2_BINS+1;k++)
      {
        for(int l=-1;l<MET_BINS+1;l++)
        {
          int sbid = Set_SearchBinID(i,j,k,l);
          if(sbid<0) continue;
          std::cout << "(" << i << "," << j << "," << k << "," << l << "):" << sbid << std::endl; 
        }
      }
    }
  }
  return 1;
}
