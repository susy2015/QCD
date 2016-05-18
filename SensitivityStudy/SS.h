#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stdlib.h>

#include "TH1D.h"
#include "TH2D.h"
#include "THStack.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TChain.h"
#include "TList.h"
#include "TF1.h"
#include "TFrame.h"
#include "TGraphErrors.h"
#include "TVirtualFitter.h"
#include "TMatrixDSym.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"

#include "Math/QuantFuncMathCore.h"
#include "TMath.h"

#include "SusyAnaTools/Tools/NTupleReader.h"
#include "SusyAnaTools/Tools/baselineDef.h"

#include "SSBinFunction.h"
#include "SSReWeighting.h"

std::string dir_out = "";

//############finish the definition of class AccRecoEffs######################
//baseline cut function definition
static BaselineVessel *myBaselineVessel;
void mypassBaselineFunc(NTupleReader& tr)
{
  (*myBaselineVessel)(tr);
}

class SSDataCard
{
 public:
  double DC_sb_MC_Data[NSEARCH_BINS] = {0};
  double DC_sb_MC_Data_statunc[NSEARCH_BINS] = {0};
  double DC_sb_MC_LL[NSEARCH_BINS] = {0}, DC_sb_MC_HadTau[NSEARCH_BINS] = {0}, DC_sb_MC_Zinv[NSEARCH_BINS] = {0}, DC_sb_MC_QCD[NSEARCH_BINS] = {0}, DC_sb_MC_TTZ[NSEARCH_BINS] = {0}, DC_sb_MC_Rare[NSEARCH_BINS] = {0}; 
  double DC_sb_MC_LL_sysunc[NSEARCH_BINS] = {0}, DC_sb_MC_HadTau_sysunc[NSEARCH_BINS] = {0}, DC_sb_MC_Zinv_sysunc[NSEARCH_BINS] = {0}, DC_sb_MC_QCD_sysunc[NSEARCH_BINS] = {0}, DC_sb_MC_TTZ_sysunc[NSEARCH_BINS] = {0}, DC_sb_MC_Rare_sysunc[NSEARCH_BINS] = {0};
  void printDC_AllFiles();
 private:
  void fake_uncs();
};
void SSDataCard::fake_uncs()
{
  std::cout << "Faking syst uncs in Data card!" << std::endl;
  for(int i=0;i<NSEARCH_BINS;i++)
  {
    //LL and hadTau: 40 % of prediction
    DC_sb_MC_LL_sysunc[i] = 0.4;
    DC_sb_MC_HadTau_sysunc[i] = 0.4;
    //Zinv
		DC_sb_MC_Zinv_sysunc[i] = std::sqrt(DC_sb_MC_Zinv[i])/DC_sb_MC_Zinv[i];
    if(DC_sb_MC_Zinv[i]<0.000000000001) DC_sb_MC_Zinv_sysunc[i] = 0;
    if(DC_sb_MC_Zinv_sysunc[i]>1) DC_sb_MC_Zinv_sysunc[i] = 1;
    //QCD, 150% of prediction
    DC_sb_MC_QCD_sysunc[i] = 1.5;
  }
  return ;
}

void SSDataCard::printDC_AllFiles()
{
  fake_uncs();

  std::ofstream Datafile ("_Data.txt");
  if (Datafile.is_open())
  {
    Datafile << "luminosity = " << LUMI << "\n";
    Datafile << "channels = " << NSEARCH_BINS << "\n";
    Datafile << "sample = signal \n";

    Datafile << "rate = ";
    for(int i=0;i<NSEARCH_BINS;i++)
    {
      Datafile << DC_sb_MC_Data[i] << " ";
    }
    Datafile << "\n";
    //std::cout << "stat_unc_all = ";
    //for(int i=0;i<NSEARCH_BINS;i++)
    //{
    //  Datafile << DC_sb_MC_Data_statunc[i] << " ";
    //}
    //Datafile << "\n";
    Datafile.close();
  }
  else std::cout << "Unable to open Datafile";

  std::ofstream LLfile ("_LL.txt");
  if (LLfile.is_open())
  {
    LLfile << "rate = ";
    for(int i=0;i<NSEARCH_BINS;i++)
    {
      LLfile << DC_sb_MC_LL[i] << " ";
    }
    LLfile << "\n";
    LLfile << "syst_unc_all = ";
    for(int i=0;i<NSEARCH_BINS;i++)
    {
      LLfile << DC_sb_MC_LL_sysunc[i] << " ";
    }
    LLfile << "\n";
    LLfile.close();
  }
  else std::cout << "Unable to open LLfile";

  std::ofstream HadTaufile ("_HadTau.txt");
  if (HadTaufile.is_open())
  {
    HadTaufile << "rate = ";
    for(int i=0;i<NSEARCH_BINS;i++)
    {
      HadTaufile << DC_sb_MC_HadTau[i] << " ";
    }
    HadTaufile << "\n";
    HadTaufile << "syst_unc_all = ";
    for(int i=0;i<NSEARCH_BINS;i++)
    {
      HadTaufile << DC_sb_MC_HadTau_sysunc[i] << " ";
    }
    HadTaufile << "\n";
    HadTaufile.close();
  }
  else std::cout << "Unable to open HadTaufile";

  std::ofstream Zinvfile ("_Zinv.txt");
  if (Zinvfile.is_open())
  {
    Zinvfile << "rate = ";
    for(int i=0;i<NSEARCH_BINS;i++)
    {
      Zinvfile << DC_sb_MC_Zinv[i] << " ";
    }
    Zinvfile << "\n";
    Zinvfile << "syst_unc_all = ";
    for(int i=0;i<NSEARCH_BINS;i++)
    {
      Zinvfile << DC_sb_MC_Zinv_sysunc[i] << " ";
    }
    Zinvfile << "\n";
    Zinvfile.close();
  }
  else std::cout << "Unable to open Zinvfile";

  std::ofstream QCDfile ("_QCD.txt");
  if (QCDfile.is_open())
  {
    QCDfile << "rate = ";
    for(int i=0;i<NSEARCH_BINS;i++)
    {
      QCDfile << DC_sb_MC_QCD[i] << " ";
    }
    QCDfile << "\n";
    QCDfile << "syst_unc_all = ";
    for(int i=0;i<NSEARCH_BINS;i++)
    {
      QCDfile << DC_sb_MC_QCD_sysunc[i] << " ";
    }
    QCDfile << "\n";
    QCDfile.close();
  }
  else std::cout << "Unable to open QCDfile";

  std::ofstream TTZfile ("_TTZ.txt");
  if (TTZfile.is_open())
  {
    TTZfile << "rate = ";
    for(int i=0;i<NSEARCH_BINS;i++)
    {
      TTZfile << DC_sb_MC_TTZ[i] << " ";
    }
    TTZfile << "\n";
    TTZfile << "syst_unc_all = ";
    for(int i=0;i<NSEARCH_BINS;i++)
    {
      TTZfile << DC_sb_MC_TTZ_sysunc[i] << " ";
    }
    TTZfile << "\n";
    TTZfile.close();
  }
  else std::cout << "Unable to open TTZfile";
 
  std::ofstream Rarefile ("_Rare.txt");
  if (Rarefile.is_open())
  {
    Rarefile << "rate = ";
    for(int i=0;i<NSEARCH_BINS;i++)
    {
      Rarefile << DC_sb_MC_Rare[i] << " ";
    }
    Rarefile << "\n";
    Rarefile << "syst_unc_all = ";
    for(int i=0;i<NSEARCH_BINS;i++)
    {
      Rarefile << DC_sb_MC_Rare_sysunc[i] << " ";
    }
    Rarefile << "\n";
    Rarefile.close();
  }
  else std::cout << "Unable to open Rarefile";

  return ;
}

class SSCSHistgram
{
 public:
  void BookHistgram(const char *);

  TFile *oFile;
  //NTop, NBot plots
  TH2D *h_ss_ntopnbot_MC_MuCS, *h_ss_ntopnbot_MC_ElCS;
  //MET MT2 plots after top bot
  TH2D *h_ss_metmt2_MC_MuCS[NTOPJETS_BINS][NBOTJETS_BINS], *h_ss_metmt2_MC_ElCS[NTOPJETS_BINS][NBOTJETS_BINS];
};

void SSCSHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");
  h_ss_ntopnbot_MC_MuCS = new TH2D("h_ss_ntopnbot_MC_MuCS","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);
  h_ss_ntopnbot_MC_ElCS = new TH2D("h_ss_ntopnbot_MC_ElCS","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);

  for(int i=0;i<NTOPJETS_BINS;i++)
  {
    for(int j=0;j<NBOTJETS_BINS;j++)
    { 
      std::string ntnbtag = "NT"+std::to_string(i+1)+"NB"+std::to_string(j+1);
      /*
      if(i==NTOPJETS_BINS-1)
      {
        h_ss_metmt2_MC_MuCS[i][j] = new TH2D(("h_ss_metmt2_MC_MuCS"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_ElCS[i][j] = new TH2D(("h_ss_metmt2_MC_ElCS"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
      }
      else if(i!=NTOPJETS_BINS-1 && j==NBOTJETS_BINS-1)
      {
        h_ss_metmt2_MC_MuCS[i][j] = new TH2D(("h_ss_metmt2_MC_MuCS"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_ElCS[i][j] = new TH2D(("h_ss_metmt2_MC_ElCS"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
      }
      else
      {
        h_ss_metmt2_MC_MuCS[i][j] = new TH2D(("h_ss_metmt2_MC_MuCS"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_ElCS[i][j] = new TH2D(("h_ss_metmt2_MC_ElCS"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
      }
      */
      if(i==NTOPJETS_BINS-1 || j==NBOTJETS_BINS-1)
      {
        h_ss_metmt2_MC_MuCS[i][j] = new TH2D(("h_ss_metmt2_MC_MuCS"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_ElCS[i][j] = new TH2D(("h_ss_metmt2_MC_ElCS"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
      }
      else
      {
        h_ss_metmt2_MC_MuCS[i][j] = new TH2D(("h_ss_metmt2_MC_MuCS"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_ElCS[i][j] = new TH2D(("h_ss_metmt2_MC_ElCS"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
      }
    }
  }
  return ;
}

class SSHistgram
{
 public:
  void BookHistgram(const char *);

  TFile *oFile;
  //NTop, NBot plots
  TH2D *h_ss_ntopnbot_MC_AllBG;
  TH2D *h_ss_ntopnbot_MC_T1tttt_mGluino1200_mLSP800, *h_ss_ntopnbot_MC_T1tttt_mGluino1500_mLSP100;
  TH2D *h_ss_ntopnbot_MC_T2tt_mStop500_mLSP325, *h_ss_ntopnbot_MC_T2tt_mStop850_mLSP100; 
  //MET MT2 plots after top bot
  TH2D *h_ss_metmt2_MC_AllBG[NTOPJETS_BINS][NBOTJETS_BINS];
  TH2D *h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800[NTOPJETS_BINS][NBOTJETS_BINS], *h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100[NTOPJETS_BINS][NBOTJETS_BINS];
  TH2D *h_ss_metmt2_MC_T2tt_mStop500_mLSP325[NTOPJETS_BINS][NBOTJETS_BINS], *h_ss_metmt2_MC_T2tt_mStop850_mLSP100[NTOPJETS_BINS][NBOTJETS_BINS];
};

void SSHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");
  h_ss_ntopnbot_MC_AllBG = new TH2D("h_ss_ntopnbot_MC_AllBG","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);
  h_ss_ntopnbot_MC_T1tttt_mGluino1200_mLSP800 = new TH2D("h_ss_ntopnbot_MC_T1tttt_mGluino1200_mLSP800","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);
  h_ss_ntopnbot_MC_T1tttt_mGluino1500_mLSP100 = new TH2D("h_ss_ntopnbot_MC_T1tttt_mGluino1500_mLSP100","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);
  h_ss_ntopnbot_MC_T2tt_mStop500_mLSP325 = new TH2D("h_ss_ntopnbot_MC_T2tt_mStop500_mLSP325","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);
  h_ss_ntopnbot_MC_T2tt_mStop850_mLSP100 = new TH2D("h_ss_ntopnbot_MC_T2tt_mStop850_mLSP100","",NTOPJETS_BINS,ntopbins_edge,NBOTJETS_BINS,nbotbins_edge);

  for(int i=0;i<NTOPJETS_BINS;i++)
  {
    for(int j=0;j<NBOTJETS_BINS;j++)
    {  
      std::string ntnbtag = "NT"+std::to_string(i+1)+"NB"+std::to_string(j+1);
      /*
      if(i==NTOPJETS_BINS-1)
      {
        h_ss_metmt2_MC_AllBG[i][j] = new TH2D(("h_ss_metmt2_MC_AllBG"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T2tt_mStop500_mLSP325[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop500_mLSP325"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T2tt_mStop850_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop850_mLSP100"+ntnbtag).c_str(),"",1,metbins_edge[0],metbins_edge[MET_BINS],1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
      }
      else if(i!=NTOPJETS_BINS-1 && j==NBOTJETS_BINS-1)
      {
        h_ss_metmt2_MC_AllBG[i][j] = new TH2D(("h_ss_metmt2_MC_AllBG"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T2tt_mStop500_mLSP325[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop500_mLSP325"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T2tt_mStop850_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop850_mLSP100"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
      }
      else
      {
        h_ss_metmt2_MC_AllBG[i][j] = new TH2D(("h_ss_metmt2_MC_AllBG"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_T2tt_mStop500_mLSP325[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop500_mLSP325"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_T2tt_mStop850_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop850_mLSP100"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
      }
      */
      if(i==NTOPJETS_BINS-1 || j==NBOTJETS_BINS-1)
      {
        h_ss_metmt2_MC_AllBG[i][j] = new TH2D(("h_ss_metmt2_MC_AllBG"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T2tt_mStop500_mLSP325[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop500_mLSP325"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
        h_ss_metmt2_MC_T2tt_mStop850_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop850_mLSP100"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,1,mt2bins_edge[0],mt2bins_edge[MT2_BINS]);
      }
      else
      {
        h_ss_metmt2_MC_AllBG[i][j] = new TH2D(("h_ss_metmt2_MC_AllBG"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_T2tt_mStop500_mLSP325[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop500_mLSP325"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
        h_ss_metmt2_MC_T2tt_mStop850_mLSP100[i][j] = new TH2D(("h_ss_metmt2_MC_T2tt_mStop850_mLSP100"+ntnbtag).c_str(),"",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
      } 
    }
  }
  return ;
}

#define SSAUXBGBin 5

class SSAUX1DHistgram
{
 public:
  void BookHistgram(const char *);
  
  TFile *oFile;
  //MET MT2 plots after top bot
  TH1D *h_ss_aux_met_MC_AllBG[NTOPJETS_BINS][NBOTJETS_BINS][SSAUXBGBin];
  TH1D *h_ss_aux_met_MC_T1tttt_mGluino1200_mLSP800[NTOPJETS_BINS][NBOTJETS_BINS], *h_ss_aux_met_MC_T1tttt_mGluino1500_mLSP100[NTOPJETS_BINS][NBOTJETS_BINS];
  TH1D *h_ss_aux_met_MC_T2tt_mStop500_mLSP325[NTOPJETS_BINS][NBOTJETS_BINS], *h_ss_aux_met_MC_T2tt_mStop850_mLSP100[NTOPJETS_BINS][NBOTJETS_BINS];

  TH1D *h_ss_aux_mt2_MC_AllBG[NTOPJETS_BINS][NBOTJETS_BINS][SSAUXBGBin];
  TH1D *h_ss_aux_mt2_MC_T1tttt_mGluino1200_mLSP800[NTOPJETS_BINS][NBOTJETS_BINS], *h_ss_aux_mt2_MC_T1tttt_mGluino1500_mLSP100[NTOPJETS_BINS][NBOTJETS_BINS];
  TH1D *h_ss_aux_mt2_MC_T2tt_mStop500_mLSP325[NTOPJETS_BINS][NBOTJETS_BINS], *h_ss_aux_mt2_MC_T2tt_mStop850_mLSP100[NTOPJETS_BINS][NBOTJETS_BINS];
};

void SSAUX1DHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");

  for(int i=0;i<NTOPJETS_BINS;i++)
  {
    for(int j=0;j<NBOTJETS_BINS;j++)
    {
      std::string ntnbtag = "NT"+std::to_string(i+1)+"NB"+std::to_string(j+1);
      for(int k=0;k<SSAUXBGBin;k++)
      { 
        std::string smalltag;

        if (k == 0) smalltag = "LL";
        else if (k == 1) smalltag = "HadTau";
        else if (k == 2) smalltag = "Zinv";
        else if (k == 3) smalltag = "QCD";
        else smalltag = "TTZ";
        
				h_ss_aux_met_MC_AllBG[i][j][k] = new TH1D(("h_ss_aux_met_MC_AllBG"+ntnbtag+"_"+smalltag).c_str(),"",(metbins_edge[MET_BINS]+500-metbins_edge[0])/50,metbins_edge[0],metbins_edge[MET_BINS]+500);
        h_ss_aux_mt2_MC_AllBG[i][j][k] = new TH1D(("h_ss_aux_mt2_MC_AllBG"+ntnbtag+"_"+smalltag).c_str(),"",(mt2bins_edge[MT2_BINS]+500-mt2bins_edge[0])/50,mt2bins_edge[0],mt2bins_edge[MT2_BINS]+500);

        h_ss_aux_met_MC_AllBG[i][j][k]->SetFillColor(k+2);
        h_ss_aux_mt2_MC_AllBG[i][j][k]->SetFillColor(k+2);
        h_ss_aux_met_MC_AllBG[i][j][k]->SetLineColor(k+2);
        h_ss_aux_mt2_MC_AllBG[i][j][k]->SetLineColor(k+2);
      }

      h_ss_aux_met_MC_T1tttt_mGluino1200_mLSP800[i][j] = new TH1D(("h_ss_aux_met_MC_T1tttt_mGluino1200_mLSP800"+ntnbtag).c_str(),"",(metbins_edge[MET_BINS]+500-metbins_edge[0])/50,metbins_edge[0],metbins_edge[MET_BINS]+500);
      h_ss_aux_met_MC_T1tttt_mGluino1500_mLSP100[i][j] = new TH1D(("h_ss_aux_met_MC_T1tttt_mGluino1500_mLSP100"+ntnbtag).c_str(),"",(metbins_edge[MET_BINS]+500-metbins_edge[0])/50,metbins_edge[0],metbins_edge[MET_BINS]+500);
      h_ss_aux_met_MC_T2tt_mStop500_mLSP325[i][j] = new TH1D(("h_ss_aux_met_MC_T2tt_mStop500_mLSP325"+ntnbtag).c_str(),"",(metbins_edge[MET_BINS]+500-metbins_edge[0])/50,metbins_edge[0],metbins_edge[MET_BINS]+500);
      h_ss_aux_met_MC_T2tt_mStop850_mLSP100[i][j] = new TH1D(("h_ss_aux_met_MC_T2tt_mStop850_mLSP100"+ntnbtag).c_str(),"",(metbins_edge[MET_BINS]+500-metbins_edge[0])/50,metbins_edge[0],metbins_edge[MET_BINS]+500);

      h_ss_aux_mt2_MC_T1tttt_mGluino1200_mLSP800[i][j] = new TH1D(("h_ss_aux_mt2_MC_T1tttt_mGluino1200_mLSP800"+ntnbtag).c_str(),"",(mt2bins_edge[MT2_BINS]+500-mt2bins_edge[0])/50,mt2bins_edge[0],mt2bins_edge[MT2_BINS]+500);
      h_ss_aux_mt2_MC_T1tttt_mGluino1500_mLSP100[i][j] = new TH1D(("h_ss_aux_mt2_MC_T1tttt_mGluino1500_mLSP100"+ntnbtag).c_str(),"",(mt2bins_edge[MT2_BINS]+500-mt2bins_edge[0])/50,mt2bins_edge[0],mt2bins_edge[MT2_BINS]+500);
      h_ss_aux_mt2_MC_T2tt_mStop500_mLSP325[i][j] = new TH1D(("h_ss_aux_mt2_MC_T2tt_mStop500_mLSP325"+ntnbtag).c_str(),"",(mt2bins_edge[MT2_BINS]+500-mt2bins_edge[0])/50,mt2bins_edge[0],mt2bins_edge[MT2_BINS]+500);
      h_ss_aux_mt2_MC_T2tt_mStop850_mLSP100[i][j] = new TH1D(("h_ss_aux_mt2_MC_T2tt_mStop850_mLSP100"+ntnbtag).c_str(),"",(mt2bins_edge[MT2_BINS]+500-mt2bins_edge[0])/50,mt2bins_edge[0],mt2bins_edge[MT2_BINS]+500);
    }
  }
}

//##########functions to calculate Delta_R and Delta Phi###############
double DeltaPhi(double phi1, double phi2) 
{
  double result = phi1 - phi2;
  while (result > M_PI)    result -= 2 * M_PI;
  while (result <= -M_PI)  result += 2 * M_PI;
  return result;
}

double DeltaR(double eta1, double phi1, double eta2, double phi2) 
{
  double deta = eta1 - eta2;
  double dphi = DeltaPhi(phi1, phi2);
  return std::sqrt(deta*deta + dphi*dphi);
}
