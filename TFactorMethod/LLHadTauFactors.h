#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLatex.h"
//#include ".h"
//#include ".h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TFrame.h"
#include "TGraphErrors.h"
#include "TVirtualFitter.h"
#include "TMatrixDSym.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"

#include "ConstantsSnippet.h"

class LLHadTauFactors
{
 public:
  std::string header_out = "QCDHardCodedInput/";
  std::string plot_out = "";
  //MC in single mu and single el
  double CR_dphi_singleMu_MC_sb[NSEARCH_BINS] = {0}, CR_dphi_singleEl_MC_sb[NSEARCH_BINS] = {0};
  double CR_invdphi_singleMu_MC_sb[NSEARCH_BINS] = {0}, CR_invdphi_singleEl_MC_sb[NSEARCH_BINS] = {0};

  double SR_dphi_ll_MC_sb[NSEARCH_BINS] = {0};
  double SR_invdphi_ll_MC_sb[NSEARCH_BINS] = {0};
  double SR_dphi_hadtau_MC_sb[NSEARCH_BINS] = {0};
  double SR_invdphi_hadtau_MC_sb[NSEARCH_BINS] = {0};

  //scale factors per search bin
  double dphi_ll_singleMu_Eff_sb[NSEARCH_BINS] = {0}, dphi_ll_singleEl_Eff_sb[NSEARCH_BINS] = {0};
  double invdphi_ll_singleMu_Eff_sb[NSEARCH_BINS] = {0}, invdphi_ll_singleEl_Eff_sb[NSEARCH_BINS] = {0};
  double dphi_hadtau_singleMu_Eff_sb[NSEARCH_BINS] = {0}, dphi_hadtau_singleEl_Eff_sb[NSEARCH_BINS] = {0};
  double invdphi_hadtau_singleMu_Eff_sb[NSEARCH_BINS] = {0}, invdphi_hadtau_singleEl_Eff_sb[NSEARCH_BINS] = {0};


  void NumbertoTFactor();
  void printInfo();

 private:
  double get_aoverb_Error(
                          double a,
                          double b,
                          double ea,
                          double eb
                         );
};
