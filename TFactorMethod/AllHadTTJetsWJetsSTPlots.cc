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
    //comparison plots
    {"cr_had_met"     , "cr_data_met"     , "MET [GeV]"             ,200 , 800  },
    {"cr_had_njets30" , "cr_data_njets30" , "Number of 30 GeV jets" ,2   , 15   }, 
    {"cr_had_njets50" , "cr_data_njets50" , "Number of 50 GeV jets" ,2   , 15   },  
    {"cr_had_mt2"     , "cr_data_mt2"     , "MT2 [GeV]"             ,200 , 600  },                                               
    {"cr_had_ht"      , "cr_data_ht"      , "HT [GeV]"              ,300 , 1800 },
    {"cr_had_mht"     , "cr_data_mht"     , "MHT [GeV]"             ,100 , 500  },
    {"cr_had_ntopjets", "cr_data_ntopjets", "Number of Top jets"    ,0   , 5    },
    {"cr_had_nbjets"  , "cr_data_nbjets"  , "Number of B Jets"      ,0   , 5    },

    {"cr_lept_met"     , "cr_data_met"     , "MET [GeV]"             ,200 , 800  },
    {"cr_lept_njets30" , "cr_data_njets30" , "Number of 30 GeV jets" ,2   , 15   },
    {"cr_lept_njets50" , "cr_data_njets50" , "Number of 50 GeV jets" ,2   , 15   },
    {"cr_lept_mt2"     , "cr_data_mt2"     , "MT2 [GeV]"             ,200 , 600  },
    {"cr_lept_ht"      , "cr_data_ht"      , "HT [GeV]"              ,300 , 1800 },
    {"cr_lept_mht"     , "cr_data_mht"     , "MHT [GeV]"             ,100 , 500  },
    {"cr_lept_ntopjets", "cr_data_ntopjets", "Number of Top jets"    ,0   , 5    },
    {"cr_lept_nbjets"  , "cr_data_nbjets"  , "Number of B Jets"      ,0   , 5    },

    {"cr_had_met"     , "cr_lept_met"     , "MET [GeV]"             ,200 , 800  },
    {"cr_had_njets30" , "cr_lept_njets30" , "Number of 30 GeV jets" ,2   , 15   },
    {"cr_had_njets50" , "cr_lept_njets50" , "Number of 50 GeV jets" ,2   , 15   },
    {"cr_had_mt2"     , "cr_lept_mt2"     , "MT2 [GeV]"             ,200 , 600  },
    {"cr_had_ht"      , "cr_lept_ht"      , "HT [GeV]"              ,300 , 1800 },
    {"cr_had_mht"     , "cr_lept_mht"     , "MHT [GeV]"             ,100 , 500  },
    {"cr_had_ntopjets", "cr_lept_ntopjets", "Number of Top jets"    ,0   , 5    },
    {"cr_had_nbjets"  , "cr_lept_nbjets"  , "Number of B Jets"      ,0   , 5    },

    {"sr_had_met"     , "sr_data_met"     , "MET [GeV]"             ,200 , 800  },
    {"sr_had_njets30" , "sr_data_njets30" , "Number of 30 GeV jets" ,2   , 15   },
    {"sr_had_njets50" , "sr_data_njets50" , "Number of 50 GeV jets" ,2   , 15   },
    {"sr_had_mt2"     , "sr_data_mt2"     , "MT2 [GeV]"             ,200 , 600  },
    {"sr_had_ht"      , "sr_data_ht"      , "HT [GeV]"              ,300 , 1800 },
    {"sr_had_mht"     , "sr_data_mht"     , "MHT [GeV]"             ,100 , 500  },
    {"sr_had_ntopjets", "sr_data_ntopjets", "Number of Top jets"    ,0   , 5    },
    {"sr_had_nbjets"  , "sr_data_nbjets"  , "Number of B Jets"      ,0   , 5    },

    {"sr_lept_met"     , "sr_data_met"     , "MET [GeV]"             ,200 , 800  },
    {"sr_lept_njets30" , "sr_data_njets30" , "Number of 30 GeV jets" ,2   , 15   },
    {"sr_lept_njets50" , "sr_data_njets50" , "Number of 50 GeV jets" ,2   , 15   },
    {"sr_lept_mt2"     , "sr_data_mt2"     , "MT2 [GeV]"             ,200 , 600  },
    {"sr_lept_ht"      , "sr_data_ht"      , "HT [GeV]"              ,300 , 1800 },
    {"sr_lept_mht"     , "sr_data_mht"     , "MHT [GeV]"             ,100 , 500  },
    {"sr_lept_ntopjets", "sr_data_ntopjets", "Number of Top jets"    ,0   , 5    },
    {"sr_lept_nbjets"  , "sr_data_nbjets"  , "Number of B Jets"      ,0   , 5    },

    {"sr_had_met"     , "sr_lept_met"     , "MET [GeV]"             ,200 , 800  },
    {"sr_had_njets30" , "sr_lept_njets30" , "Number of 30 GeV jets" ,2   , 15   },
    {"sr_had_njets50" , "sr_lept_njets50" , "Number of 50 GeV jets" ,2   , 15   },
    {"sr_had_mt2"     , "sr_lept_mt2"     , "MT2 [GeV]"             ,200 , 600  },
    {"sr_had_ht"      , "sr_lept_ht"      , "HT [GeV]"              ,300 , 1800 },
    {"sr_had_mht"     , "sr_lept_mht"     , "MHT [GeV]"             ,100 , 500  },
    {"sr_had_ntopjets", "sr_lept_ntopjets", "Number of Top jets"    ,0   , 5    },
    {"sr_had_nbjets"  , "sr_lept_nbjets"  , "Number of B Jets"      ,0   , 5    },
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
  myAllHadTTJetsWJetsSTPlots.CompareTemplate("cr_had_sb" , "cr_data_sb", "Search Bins", 0, NSEARCH_BINS);
  myAllHadTTJetsWJetsSTPlots.CompareTemplate("cr_lept_sb", "cr_data_sb", "Search Bins", 0, NSEARCH_BINS);
  myAllHadTTJetsWJetsSTPlots.CompareTemplate("cr_had_sb" , "cr_lept_sb", "Search Bins", 0, NSEARCH_BINS);
  myAllHadTTJetsWJetsSTPlots.CompareTemplate("sr_had_sb" , "sr_data_sb", "Search Bins", 0, NSEARCH_BINS);
  myAllHadTTJetsWJetsSTPlots.CompareTemplate("sr_lept_sb", "sr_data_sb", "Search Bins", 0, NSEARCH_BINS);
  myAllHadTTJetsWJetsSTPlots.CompareTemplate("sr_had_sb" , "sr_lept_sb", "Search Bins", 0, NSEARCH_BINS);

  myAllHadTTJetsWJetsSTPlots.CompareTemplate("sr_had_sb" , "sr_qcd_sb", "Search Bins", 0, NSEARCH_BINS);

  return 0;
}

