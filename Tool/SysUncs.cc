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

#include "SysUncs.h"

int main()
{
  SysUncs mySysUncs;
 
  mySysUncs.Initialization("TFactorsUnc");
  mySysUncs.GetTFactorsSysUnc();
  mySysUncs.Reset();

  mySysUncs.Initialization("NonClosureUnc");
  mySysUncs.GetNonClosureSysUnc();
  mySysUncs.Reset();

  mySysUncs.combineSysUncs();
  mySysUncs.printSysUncs();
  
  mySysUncs.printLatexTable();
  mySysUncs.printFinalPred();
  return 0;
}


