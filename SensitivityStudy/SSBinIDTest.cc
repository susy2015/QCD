#include <iostream>
//#include "SSBinFunction.h"
#include "SBGeometry.h"

int main()
{
  std::cout << "Testing Search bin ID algorithm..." << std::endl;
  SBGeometry mySBGeometry;
  if(mySBGeometry.SBSelfTest()){ std::cout << "Good SB Def! Continue testing..." << std::endl; }
  else return -1;
  
  for(int i=0;i<5;i++)
  {
    for(int j=0;j<5;j++)
    {
      for(int k=0;k<20;k++)
      {
        for(int l=0;l<30;l++)
        {
          int ntop = i, nbot = j;
          double mt2 = k*20+200, met = l*20+200;
          int sbid = mySBGeometry.GetSBID(ntop,nbot,mt2,met);
          if(sbid<0) continue;
          std::cout << "(" << ntop << "," << nbot << "," << mt2 << "," << met << "):" << sbid << std::endl; 
        }
      }
    }
  }
  /*
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
  */
  return 1;
}
