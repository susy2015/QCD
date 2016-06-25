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
#include "THStack.h"

#include "BasicCheckPlots.h"

int main(int argc, char* argv[])
{

  if (argc < 1)
  {
    std::cerr <<"Please give at least 1 argument " << "TargetDirName" << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./BasicCheckPlots BasicCheckQCD20151209 or ./BasicCheckPlots BasicCheckLL20151211" << std::endl;
    return -1;
  }

  std::string DirName = argv[1];

  BasicCheckPlots myBasicCheckPlots;
  myBasicCheckPlots.Initialization(DirName);
  //initialize the closure plots parameter we want to investigate
  std::vector<Plotting_Parameter> myPlotting_Paramete = 
  { 
    //QCD basic check plots
    {"_met"     , "MET [GeV]"             ,150 , 550  },
    {"_njets30" , "Number of 30 GeV jets" ,4   , 14   }, 
    {"_njets50" , "Number of 50 GeV jets" ,2   , 17   },  
    {"_mt2"     , "MT2 [GeV]"             ,200 , 600  },                                               
    {"_ht"      , "HT [GeV]"              ,500 , 3000 },
    //{"_mht"     , "MHT [GeV]"             ,0   , 1000 },
    {"_ntopjets", "Number of Top jets"    ,1   , 6    },
    {"_nbjets"  , "Number of B Jets"      ,1   , 6    },
    //search bin closure plots
    {"_sb"   , "Search Bins"           ,0   , 60 },
  };

  std::vector<Plotting_Parameter>::iterator iter_p;

  for( iter_p = myPlotting_Paramete.begin() ; iter_p != myPlotting_Paramete.end() ; iter_p ++)
  {
    myBasicCheckPlots.BasicCheckTemplate(
                                         (*iter_p).hist_tag,
                                         (*iter_p).XTitle,
                                         (*iter_p).min,
                                         (*iter_p).max 
                                        );
  }

  myPlotting_Paramete.clear();
  
  return 0;
}

