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

#include "Math/QuantFuncMathCore.h"
#include "TMath.h"

#include "SusyAnaTools/Tools/NTupleReader.h"
#include "SusyAnaTools/Tools/baselineDef.h"
#include "SusyAnaTools/Tools/BTagCorrector.h"

//#include "CMSStylePlot/CMS_lumi.h"

#include "QCDReWeighting.h"
#include "SFCheckHistgram.h"

//Scale Tfactors with the Tfactor from Real Data
#include "ConstantsSnippet.h"
//#include "CMSStylePlot/tdrstyle.h"

//all the root file for plotting will go to this directory
std::string dir_out = "RootForPlotting/";

//baseline cut function definition, no need since move to QCD style root file
static BaselineVessel *myBaselineVessel;
void mypassBaselineFunc(NTupleReader& tr)
{
  (*myBaselineVessel)(tr);
}

//overall scale for all plots, will be set to be 1 if no special need
const double Scale = 1;
//const double Scale = 591.5/2153.736;

double ElMuDataMCScaleFactor(
                             std::vector<TLorentzVector> elesLVec,
                             std::vector<int> elesFlagVeto,
                             std::vector<double> elesMiniIso,
	                           std::vector<TLorentzVector> muonsLVec,
                             std::vector<int> muonsFlagMedium,
                             std::vector<double> muonsMiniIso,
                             TH2F *hel_1st,
                             TH2F *hel_2nd,
                             TH2F *hmu_1st
                            )
{
  //muonsLVec, elesLVec
  bool isElCS=false, isMuCS=false;

  double reco_els_pt = -1, reco_els_eta = -20;
  for(unsigned int ie = 0 ; ie < elesLVec.size() ; ie++)
  {
    if(elesFlagVeto[ie] && elesLVec[ie].Pt()>(AnaConsts::elesMiniIsoArr).minPt && fabs(elesLVec[ie].Eta()) < (AnaConsts::elesMiniIsoArr).maxAbsEta && elesMiniIso[ie] < (AnaConsts::elesMiniIsoArr).maxIsoEB )
    { 
      reco_els_pt  = ( elesLVec.at(ie) ).Pt();
      reco_els_eta = ( elesLVec.at(ie) ).Eta();
    }
  }
  if(reco_els_pt>0) isElCS=true;

  double reco_mus_pt = -1, reco_mus_eta = -20;
  for(unsigned int im = 0 ; im < muonsLVec.size() ; im++)
  {
    if(muonsFlagMedium[im] && muonsLVec[im].Pt()>(AnaConsts::muonsMiniIsoArr).minPt && fabs(muonsLVec[im].Eta()) < (AnaConsts::muonsMiniIsoArr).maxAbsEta && muonsMiniIso[im] < (AnaConsts::muonsMiniIsoArr).maxIso )
	  {
      reco_mus_pt  = ( muonsLVec.at(im) ).Pt();
      reco_mus_eta = ( muonsLVec.at(im) ).Eta();
    }
  }
  if(reco_mus_pt>0) isMuCS=true;

  if(isElCS && !isMuCS)
  {
    double elsf = 1;
    int etabin1st = hel_1st->GetXaxis()->FindBin(reco_els_eta);
    int ptbin1st = hel_1st->GetYaxis()->FindBin(reco_els_pt);
    if(reco_els_pt > 200) ptbin1st = hel_1st->GetYaxis()->FindBin(200-1);
    if(reco_els_pt < 20 ) ptbin1st = hel_1st->GetYaxis()->FindBin(20 +1);
    elsf *= hel_1st->GetBinContent(etabin1st,ptbin1st);
    //if(elsf<0.1) std::cout << "El Pt : " << reco_els_pt << " El Eta : "<< reco_els_eta << std::endl;

    int ptbin2nd = hel_2nd->GetXaxis()->FindBin(reco_els_pt);
    if(reco_els_pt > hel_2nd->GetXaxis()->GetXmax()) ptbin2nd = hel_2nd->GetXaxis()->FindBin(hel_2nd->GetXaxis()->GetXmax()-1);
    if(reco_els_pt < hel_2nd->GetXaxis()->GetXmin()) ptbin2nd = hel_2nd->GetXaxis()->FindBin(hel_2nd->GetXaxis()->GetXmin()+1);
    int etabin2nd = hel_2nd->GetYaxis()->FindBin(std::abs(reco_els_eta));
    elsf *= hel_2nd->GetBinContent(ptbin2nd,etabin2nd);
    //if(elsf<0.1) std::cout << "El Pt : " << reco_els_pt << " El Eta : "<< reco_els_eta << std::endl;
    return elsf;
  }
  else if(!isElCS && isMuCS)
  {
    double musf = 1;
    int ptbin1st = hmu_1st->GetXaxis()->FindBin(reco_mus_pt);
    if(reco_mus_pt > hmu_1st->GetXaxis()->GetXmax()) ptbin1st = hmu_1st->GetXaxis()->FindBin(hmu_1st->GetXaxis()->GetXmax()-1);
    int etabin1st = hmu_1st->GetYaxis()->FindBin(std::abs(reco_mus_eta));
    musf *= hmu_1st->GetBinContent(ptbin1st,etabin1st);
    //if(musf<0.1) std::cout << "Mu Pt : " << reco_mus_pt << " Mu Eta : "<< reco_mus_eta << std::endl;
    return musf;
  }
  else
  {
    std::cout << "the event is neither single electron CS nor single muon CS! Please check!" << std::endl;
    return 1;
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
