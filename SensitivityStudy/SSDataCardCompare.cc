#include <vector>
#include <iostream>
#include <set>

#include "SSDataCardCompare.h"

int main(int argc, char* argv[])
{
  std::vector<DC_Compare_Parameter> myDC_Compare_Parameter = 
  { 
    //LL
    { "LL","rate" },
    { "LL","cs_event" },
    { "LL","syst_unc_closure_up" },
    //HadTau
    { "HadTau","rate" },
    { "HadTau","syst_unc_closure_up" },
    //Zinv
    { "Zinv","rate" },
    { "Zinv","cs_event" },
    //{ "Zinv","syst ?" },
    //TTZ
    { "TTZ","rate" },
    { "TTZ","cs_event" },
  };

  DCComparePlots myDCComparePlots;
  std::vector<DC_Compare_Parameter>::iterator iter_p;

  for( iter_p = myDC_Compare_Parameter.begin() ; iter_p != myDC_Compare_Parameter.end() ; iter_p ++)
  {
    myDCComparePlots.DCComparePlotsLoop(
                                        (*iter_p).sample_type,
                                        (*iter_p).var_type
                                       );
  }
  myDC_Compare_Parameter.clear();
  return 0;
}
