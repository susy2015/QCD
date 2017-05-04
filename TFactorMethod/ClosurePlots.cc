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
    //{"_met"     , "MET [GeV]"             ,200 , 800  },
    {"_met"     , "E_{T}^{miss} [GeV]"    ,200 , 800  },
    {"_njets30" , "Number of 30 GeV jets" ,2   , 15   }, 
    {"_njets50" , "Number of 50 GeV jets" ,2   , 15   },  
    {"_mt2"     , "M_{T2} [GeV]"          ,200 , 600  },                                               
    {"_ht"      , "H_{T} [GeV]"           ,300 , 1800 },
    {"_mht"     , "H_{T}^{miss} [GeV]"    ,100 , 500  },
    {"_ntopjets", "N_{t}"                 ,0   , 5    },
    {"_nbjets"  , "N_{b}"                 ,0   , 5    },
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
  myClosurePlots.ClosureTemplate(
                                 "_sb",
                                 "Search Bins",
                                 0,
                                 NSEARCH_BINS
                                );  
  
  return 0;
}

