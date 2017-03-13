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

#include "AllHadTTJetsWJetsSTPlots.h"

int main(int argc, char* argv[])
{

  if (argc < 1)
  {
    std::cerr <<"Please give at least 1 argument " << "TargetDirName" << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./AllHadTTJetsWJetsSTPlots QCDClosure20151204 or ./AllHadTTJetsWJetsSTPlots QCDDataMC20151209" << std::endl;
    return -1;
  }

  std::string DirName = argv[1];

  AllHadTTJetsWJetsSTPlots myAllHadTTJetsWJetsSTPlots;
  myAllHadTTJetsWJetsSTPlots.Initialization(DirName);
  //initialize the closure plots parameter we want to investigate
  std::vector<Plotting_Parameter> myPlotting_Paramete = 
  { 
    //QCD closure plots
    {"had_met"     , "data_met"     , "MET [GeV]"             ,200 , 800  },
    {"had_njets30" , "data_njets30" , "Number of 30 GeV jets" ,2   , 15   }, 
    {"had_njets50" , "data_njets50" , "Number of 50 GeV jets" ,2   , 15   },  
    {"had_mt2"     , "data_mt2"     , "MT2 [GeV]"             ,200 , 600  },                                               
    {"had_ht"      , "data_ht"      , "HT [GeV]"              ,300 , 1800 },
    {"had_mht"     , "data_mht"     , "MHT [GeV]"             ,100 , 500  },
    {"had_ntopjets", "data_ntopjets", "Number of Top jets"    ,0   , 5    },
    {"had_nbjets"  , "data_nbjets"  , "Number of B Jets"      ,0   , 5    },

    {"lept_met"     , "data_met"     , "MET [GeV]"             ,200 , 800  },
    {"lept_njets30" , "data_njets30" , "Number of 30 GeV jets" ,2   , 15   },
    {"lept_njets50" , "data_njets50" , "Number of 50 GeV jets" ,2   , 15   },
    {"lept_mt2"     , "data_mt2"     , "MT2 [GeV]"             ,200 , 600  },
    {"lept_ht"      , "data_ht"      , "HT [GeV]"              ,300 , 1800 },
    {"lept_mht"     , "data_mht"     , "MHT [GeV]"             ,100 , 500  },
    {"lept_ntopjets", "data_ntopjets", "Number of Top jets"    ,0   , 5    },
    {"lept_nbjets"  , "data_nbjets"  , "Number of B Jets"      ,0   , 5    },

    {"had_met"     , "lept_met"     , "MET [GeV]"             ,200 , 800  },
    {"had_njets30" , "lept_njets30" , "Number of 30 GeV jets" ,2   , 15   },
    {"had_njets50" , "lept_njets50" , "Number of 50 GeV jets" ,2   , 15   },
    {"had_mt2"     , "lept_mt2"     , "MT2 [GeV]"             ,200 , 600  },
    {"had_ht"      , "lept_ht"      , "HT [GeV]"              ,300 , 1800 },
    {"had_mht"     , "lept_mht"     , "MHT [GeV]"             ,100 , 500  },
    {"had_ntopjets", "lept_ntopjets", "Number of Top jets"    ,0   , 5    },
    {"had_nbjets"  , "lept_nbjets"  , "Number of B Jets"      ,0   , 5    },
  };

  
  std::vector<Plotting_Parameter>::iterator iter_p;

  for( iter_p = myPlotting_Paramete.begin() ; iter_p != myPlotting_Paramete.end() ; iter_p ++)
  {
    myAllHadTTJetsWJetsSTPlots.CompareTemplate(
                                               (*iter_p).hist_n_tag,
                                               (*iter_p).hist_d_tag,
                                               (*iter_p).XTitle,
                                               (*iter_p).min,
                                               (*iter_p).max 
                                              );
  }

  myPlotting_Paramete.clear();
  myAllHadTTJetsWJetsSTPlots.CompareTemplate("had_sb" , "data_sb", "Search Bins", 0, NSEARCH_BINS);
  myAllHadTTJetsWJetsSTPlots.CompareTemplate("lept_sb", "data_sb", "Search Bins", 0, NSEARCH_BINS);
  myAllHadTTJetsWJetsSTPlots.CompareTemplate("had_sb" , "lept_sb", "Search Bins", 0, NSEARCH_BINS);

  return 0;
}

