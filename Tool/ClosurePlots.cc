#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <set>

#include "TFile.h"
#include "TList.h"
#include "TString.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"

#include "ClosurePlots.h"

int main(int argc, char* argv[])
{

  if (argc < 1)
  {
    std::cerr <<"Please give at least 1 argument " << "TargetDirName" << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./ClosurePlots QCDClosure20151204 or ./ClosurePlots QCDDataMC20151209" << std::endl;
    return -1;
  }

  std::string DirName = argv[1];

  ClosurePlots myClosurePlots;
  myClosurePlots.Initialization(DirName);
  //initialize the closure plots parameter we want to investigate
  std::vector<Plotting_Parameter> myPlotting_Paramete = 
  { 
    //QCD closure plots
    {"_met"     , "MET [GeV]"             ,150 , 600  },
    {"_njets30" , "Number of 30 GeV jets" ,2   , 17   }, 
    {"_njets50" , "Number of 50 GeV jets" ,2   , 17   },  
    {"_mt2"     , "MT2 [GeV]"             ,100 , 600  },                                               
    {"_ht"      , "HT [GeV]"              ,400 , 1400 },
    {"_mht"     , "MHT [GeV]"             ,100 , 500  },
    {"_ntopjets", "Number of Top jets"    ,0   , 5    },
    {"_nbjets"  , "Number of B Jets"      ,0   , 10   },
    //search bin closure plots
    //{"_sb"   , "Search Bins"           ,0   , 65  },
  };

  
  std::vector<Plotting_Parameter>::iterator iter_p;

  for( iter_p = myPlotting_Paramete.begin() ; iter_p != myPlotting_Paramete.end() ; iter_p ++)
  {
    myClosurePlots.ClosureTemplate(
                                   (*iter_p).hist_tag,
                                   (*iter_p).XTitle,
                                   (*iter_p).min,
                                   (*iter_p).max 
                                  );
    //myClosurePlots.CompareTemplate(
    //                               (*iter_p).hist_tag,
    //                               (*iter_p).XTitle,
    //                               (*iter_p).min,
    //                               (*iter_p).max
    //                              );
  }

  myPlotting_Paramete.clear();
  /*
  myPlotting_Paramete =
  {
    //QCD closure plots
    {"_b_met"     , "MET [GeV]"             ,150 , 600  },
    {"_b_mt2"     , "MT2 [GeV]"             ,100 , 600  },
    {"_b_dphi0"   , "Delta Phi(MET,Jet1)"   ,0   , 4    },
    {"_b_dphi1"   , "Delta Phi(MET,Jet2)"   ,0   , 4    },
    {"_b_dphi2"   , "Delta Phi(MET,Jet3)"   ,0   , 4    },
    //search bin closure plots
    //{"_sb"   , "Search Bins"           ,0   , 65  },
  };


  for( iter_p = myPlotting_Paramete.begin() ; iter_p != myPlotting_Paramete.end() ; iter_p ++)
  {
    myClosurePlots.BTStudyTemplate(
                                   (*iter_p).hist_tag,
                                   (*iter_p).XTitle,
                                   (*iter_p).min,
                                   (*iter_p).max
                                  );
  }
  
  */
  myClosurePlots.ClosureTemplate(
                                 "_sb",
                                 "Search Bins",
                                 0,
                                 50
                                );  
  
  return 0;
}

