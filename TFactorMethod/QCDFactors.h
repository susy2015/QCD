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

#include "QCDHardCodedInput/TFactorsfromDataHeader.h"
//#include "CMSStylePlot/CMS_lumi.h"

class QCDFactors
{
 public:
  std::string header_out = "QCDHardCodedInput/";
  std::string plot_out = "";
  //LoopQCDCal, variables for TFactor calculation in QCD HT MC, none Ext for nb,nt 1,2, ext for nb or nt ge 3
  double nQCDNormal_MC[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}}, nQCDInverted_MC[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}};
  double nQCDNormal[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}}, nQCDInverted[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}};
  double nQCDNormal_Ext_MC[QCD_BINS][MET_Ext_BINS][HT_Ext_BINS] = {{{0}}}, nQCDInverted_Ext_MC[QCD_BINS][MET_Ext_BINS][HT_Ext_BINS] = {{{0}}};
  double nQCDNormal_Ext[QCD_BINS][MET_Ext_BINS][HT_Ext_BINS] = {{{0}}}, nQCDInverted_Ext[QCD_BINS][MET_Ext_BINS][HT_Ext_BINS] = {{{0}}};

  double nQCDNormal_all[MET_BINS][MT2_BINS] = {{0}}, nQCDInverted_all[MET_BINS][MT2_BINS] = {{0}};
  double nQCDNormal_all_err[MET_BINS][MT2_BINS] = {{0}}, nQCDInverted_all_err[MET_BINS][MT2_BINS] = {{0}};
  double nQCDNormal_Ext_all[MET_Ext_BINS][HT_Ext_BINS] = {{0}}, nQCDInverted_Ext_all[MET_Ext_BINS][HT_Ext_BINS] = {{0}};
  double nQCDNormal_Ext_all_err[MET_Ext_BINS][HT_Ext_BINS] = {{0}}, nQCDInverted_Ext_all_err[MET_Ext_BINS][HT_Ext_BINS] = {{0}};

  double nOtherNormal_all[MET_BINS][MT2_BINS] = {{0}}, nOtherInverted_all[MET_BINS][MT2_BINS] = {{0}};
  double nOtherNormal_all_err[MET_BINS][MT2_BINS] = {{0}}, nOtherInverted_all_err[MET_BINS][MT2_BINS] = {{0}};
  double nOtherNormal_Ext_all[MET_Ext_BINS][HT_Ext_BINS] = {{0}}, nOtherInverted_Ext_all[MET_Ext_BINS][HT_Ext_BINS] = {{0}};
  double nOtherNormal_Ext_all_err[MET_Ext_BINS][HT_Ext_BINS] = {{0}}, nOtherInverted_Ext_all_err[MET_Ext_BINS][HT_Ext_BINS] = {{0}};

  double QCDTFactor[MET_BINS][MT2_BINS] = {{0}}, QCDTFactor_err[MET_BINS][MT2_BINS] = {{0}};//Tfactors calculated from QCD MC
  double QCDTFactorFit[MET_BINS][MT2_BINS] = {{0}}, QCDTFactorFit_err[MET_BINS][MT2_BINS] = {{0}};//Tfactors smoothed by linear fit,FIXME
  double QCDTFactorScaled[MET_BINS][MT2_BINS] = {{0}}, QCDTFactorScaled_err[MET_BINS][MT2_BINS] = {{0}};//Tfactors scaled by low MET bin Tfactor(from Data) and linear fit 
  double MET_sum[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}}, MET_sum_weight[QCD_BINS][MET_BINS][MT2_BINS] = {{{0}}};//FIXME
  double MET_sum_all[MET_BINS][MT2_BINS] = {{0}}, MET_sum_weight_all[MET_BINS][MT2_BINS] = {{0}};//FIXME
  double MET_mean[MET_BINS][MT2_BINS] = {{0}}, MET_mean_err[MET_BINS][MT2_BINS] = {{0}};//FIXME

  double QCDTFactor_Ext[MET_Ext_BINS][HT_Ext_BINS] = {{0}}, QCDTFactor_Ext_err[MET_Ext_BINS][HT_Ext_BINS] = {{0}};//Tfactors calculated from QCD MC
  double QCDTFactorFit_Ext[MET_Ext_BINS][HT_Ext_BINS] = {{0}}, QCDTFactorFit_Ext_err[MET_Ext_BINS][HT_Ext_BINS] = {{0}};//Tfactors smoothed by linear fit,FIXME
  double QCDTFactorScaled_Ext[MET_Ext_BINS][HT_Ext_BINS] = {{0}}, QCDTFactorScaled_Ext_err[MET_Ext_BINS][HT_Ext_BINS] = {{0}};//Tfactors scaled by low MET bin Tfactor(from Data) and linear fit 
  //NJet correction factor, not used for now
  double nQCDNormal_NJF_MC_all[NJETS_BINS] = {0}, nQCDInverted_NJF_MC_all[NJETS_BINS] = {0};
  double QCDTNJF[NJETS_BINS] = {0}, QCDTNJF_err[NJETS_BINS] = {0};//Tfactors calculated from QCD MC
  //determine the tfactor value in the MC inverted dphi region in case of no inverted dphis in some search in real data
  double MET_sum_all_exp_sb[NSEARCH_BINS] = {0}, MET_sum_weight_all_exp_sb[NSEARCH_BINS] = {0};
  double MT2_sum_all_exp_sb[NSEARCH_BINS] = {0}, MT2_sum_weight_all_exp_sb[NSEARCH_BINS] = {0}; 
  double HT_sum_all_exp_sb[NSEARCH_BINS] = {0}, HT_sum_weight_all_exp_sb[NSEARCH_BINS] = {0};
  double MET_mean_exp_sb[NSEARCH_BINS] = {0}, MT2_mean_exp_sb[NSEARCH_BINS] = {0}, HT_mean_exp_sb[NSEARCH_BINS] = {0};
  //determine the tfactor value in the Data inverted dphi region in case of no inverted dphis in some search in real data  
  double MET_sb_sum[NSEARCH_BINS] = {0}, MET_sb_sum_weight[NSEARCH_BINS] = {0};
  double MET_sb_mean[NSEARCH_BINS] = {0};
  double MT2_sb_sum[NSEARCH_BINS] = {0}, MT2_sb_sum_weight[NSEARCH_BINS] = {0};
  double MT2_sb_mean[NSEARCH_BINS] = {0}; 
  double HT_sb_sum[NSEARCH_BINS] = {0}, HT_sb_sum_weight[NSEARCH_BINS] = {0};
  double HT_sb_mean[NSEARCH_BINS] = {0};

  void NumbertoTFactor();
  void TFactorFit();//FIXME
  void TFactorScale();
  void printQCDFactorInfo();
  void printTFactorsHeader();
  void TFactorsPlotsGen();
  void CountingPlotsGen();

  //LoopQCDPredData, variables for data card
  double DC_sb_Data[NSEARCH_BINS] = {0}; 
  double DC_sb_Data_err[NSEARCH_BINS] = {0};
  //MC driven variables
  double DC_sb_hadtauMC[NSEARCH_BINS] = {0}, DC_sb_lostleptMC[NSEARCH_BINS] = {0};
  double DC_sb_zinvMC[NSEARCH_BINS] = {0}, DC_sb_ttzMC[NSEARCH_BINS] = {0}, DC_sb_allhadMC[NSEARCH_BINS] = {0};
  double DC_sb_hadtauMC_err[NSEARCH_BINS] = {0}, DC_sb_lostleptMC_err[NSEARCH_BINS] = {0}; 
  double DC_sb_zinvMC_err[NSEARCH_BINS] = {0}, DC_sb_ttzMC_err[NSEARCH_BINS] = {0}, DC_sb_allhadMC_err[NSEARCH_BINS] = {0};
  //Data driven variables
  double DC_sb_hadtau[NSEARCH_BINS] = {0}, DC_sb_lostlept[NSEARCH_BINS] = {0};
  double DC_sb_hadtau_errup[NSEARCH_BINS] = {0}, DC_sb_lostlept_errup[NSEARCH_BINS] = {0}, DC_sb_hadtau_errdown[NSEARCH_BINS] = {0}, DC_sb_lostlept_errdown[NSEARCH_BINS] = {0};
  double DC_sb_TFactor[NSEARCH_BINS] = {0};
  double DC_sb_TFactor_err[NSEARCH_BINS] = {0};
  //variables for aggregate search bins 
  double DC_sb_TFactor_ave[NSEARCH_BINS] = {0};
  double DC_sb_TFactor_ave_err[NSEARCH_BINS] = {0};
  double DC_sb_TFactor_sum_weight[NSEARCH_BINS] = {0}, DC_sb_TFactor_sum[NSEARCH_BINS] = {0};
  double DC_sb_TFactor_sum_weight_err[NSEARCH_BINS] = {0}, DC_sb_TFactor_sum_err[NSEARCH_BINS] = {0};
  double DC_sb_otherBG_eff[NSEARCH_BINS] = {0};
  double DC_sb_otherBG_sum_weight[NSEARCH_BINS] = {0}, DC_sb_otherBG_sum[NSEARCH_BINS] = {0};
  //too diffcult to calculter the err for eff other bg... use approximation to replace
  //variables for Data Card and Syst header
  double QCD_Data_CS[NSEARCH_BINS] = {0}, QCD_Data_CS_relative_err[NSEARCH_BINS] = {0};
  double QCD_otherBG_CS[NSEARCH_BINS] = {0}, QCD_otherBG_CS_relative_errup[NSEARCH_BINS] = {0}, QCD_otherBG_CS_relative_errdown[NSEARCH_BINS] = {0};
  double QCD_TFactor[NSEARCH_BINS] = {0}, QCD_TFactor_relative_err[NSEARCH_BINS] = {0};
  double QCD_NTopFactor[NSEARCH_BINS] = {0}, QCD_NTopFactor_relative_err[NSEARCH_BINS] = {0};
  double QCD_NonClosure_relative_err[NSEARCH_BINS] = {0};
  //variables for aggregate search bins
  double QCD_otherBG_eff_CS[NSEARCH_BINS] = {0};
  double QCD_TFactor_ave[NSEARCH_BINS] = {0}, QCD_TFactor_ave_relative_err[NSEARCH_BINS] = {0};

  void printDataCard(std::string pred_type);
  void printSysHeader(std::string pred_type);

  //LoopQCDCalTFSideBand, to calculate the Tfactor from data in low met side band
  double nQCDNormal_Data_all[MT2_BINS] = {0}, nQCDInverted_Data_all[MT2_BINS] = {0};
  double nQCDNormal_Data_all_err[MT2_BINS] = {0}, nQCDInverted_Data_all_err[MT2_BINS] = {0};
  double nQCDNormal_Ext_Data_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_Data_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  double nQCDNormal_Ext_Data_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_Data_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  //MC driven variables
  double nQCDNormal_hadtauMC_all[MT2_BINS] = {0}, nQCDInverted_hadtauMC_all[MT2_BINS] = {0};
  double nQCDNormal_hadtauMC_all_err[MT2_BINS] = {0}, nQCDInverted_hadtauMC_all_err[MT2_BINS] = {0};
  double nQCDNormal_lostleptMC_all[MT2_BINS] = {0}, nQCDInverted_lostleptMC_all[MT2_BINS] = {0};
  double nQCDNormal_lostleptMC_all_err[MT2_BINS] = {0}, nQCDInverted_lostleptMC_all_err[MT2_BINS] = {0};
  double nQCDNormal_zinvMC_all[MT2_BINS] = {0}, nQCDInverted_zinvMC_all[MT2_BINS] = {0};
  double nQCDNormal_zinvMC_all_err[MT2_BINS] = {0}, nQCDInverted_zinvMC_all_err[MT2_BINS] = {0};
  double nQCDNormal_ttzMC_all[MT2_BINS] = {0}, nQCDInverted_ttzMC_all[MT2_BINS] = {0};
  double nQCDNormal_ttzMC_all_err[MT2_BINS] = {0}, nQCDInverted_ttzMC_all_err[MT2_BINS] = {0};
  double nQCDNormal_allhadMC_all[MT2_BINS] = {0}, nQCDInverted_allhadMC_all[MT2_BINS] = {0};
  double nQCDNormal_allhadMC_all_err[MT2_BINS] = {0}, nQCDInverted_allhadMC_all_err[MT2_BINS] = {0};
  double nQCDNormal_Ext_hadtauMC_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_hadtauMC_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  double nQCDNormal_Ext_hadtauMC_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_hadtauMC_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  double nQCDNormal_Ext_lostleptMC_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_lostleptMC_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  double nQCDNormal_Ext_lostleptMC_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_lostleptMC_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  double nQCDNormal_Ext_zinvMC_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_zinvMC_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  double nQCDNormal_Ext_zinvMC_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_zinvMC_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  double nQCDNormal_Ext_ttzMC_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_ttzMC_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  double nQCDNormal_Ext_ttzMC_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_ttzMC_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  double nQCDNormal_Ext_allhadMC_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_allhadMC_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  double nQCDNormal_Ext_allhadMC_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_allhadMC_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  //Data driven variables
  double nQCDNormal_hadtau_all[MT2_BINS] = {0}, nQCDInverted_hadtau_all[MT2_BINS] = {0};
  double nQCDNormal_hadtau_all_err[MT2_BINS] = {0}, nQCDInverted_hadtau_all_err[MT2_BINS] = {0};
  double nQCDNormal_lostlept_all[MT2_BINS] = {0}, nQCDInverted_lostlept_all[MT2_BINS] = {0};
  double nQCDNormal_lostlept_all_err[MT2_BINS] = {0}, nQCDInverted_lostlept_all_err[MT2_BINS] = {0};
  double nQCDNormal_Ext_hadtau_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_hadtau_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  double nQCDNormal_Ext_hadtau_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_hadtau_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  double nQCDNormal_Ext_lostlept_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_lostlept_all[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  double nQCDNormal_Ext_lostlept_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, nQCDInverted_Ext_lostlept_all_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  //2 set of TFactors involoved in the QCDHardCodedInput
  double QCDTFactorData[MT2_BINS] = {0}, QCDTFactorData_err[MT2_BINS] = {0};
  double QCDTFactorData_Ext[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0}, QCDTFactorData_Ext_err[MET_Ext_SideBand_BINS*HT_Ext_BINS] = {0};
  void getAndprintTFactorsfromDataHeader(std::string pred_type);

  //LoopQCDPredMC and LoopQCDExpMC
  double QCDWeights[QCD_BINS] = {0};
  double nQCD_exp_sb_MC[QCD_BINS][NSEARCH_BINS] = {{0}}, nQCD_pred_sb_MC[QCD_BINS][NSEARCH_BINS] = {{0}};
  double nQCD_exp_sb[NSEARCH_BINS] = {0}, nQCD_pred_sb[NSEARCH_BINS] = {0};
  double nQCD_exp_sb_err[NSEARCH_BINS] = {0}, nQCD_pred_sb_err[NSEARCH_BINS] = {0};
  void printSBInfo();

 private:
  double get_aoverb_Error(
                          double a,
                          double b,
                          double ea,
                          double eb
                         );
  std::string printDataCardLine(std::string name,double (&nums)[NSEARCH_BINS]);
  std::string printSysHeaderLine(std::string name,double (&nums)[NSEARCH_BINS]);
};
