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

//baseline cut function definition, no need since move to QCD style root file
static BaselineVessel *myBaselineVessel;
void mypassBaselineFunc(NTupleReader& tr)
{
  (*myBaselineVessel)(tr);
}

//overall scale for all plots, will be set to be 1 if no special need
const double Scale = 1;
//const double Scale = 591.5/2153.736;

bool ElPtEtaCut(
                std::vector<TLorentzVector> elesLVec,
                std::vector<int> elesFlagVeto,
                std::vector<double> elesMiniIso
               )
{
  bool isElPass=false;

  double reco_els_pt = -1, reco_els_eta = -20;
  for(unsigned int ie = 0 ; ie < elesLVec.size() ; ie++)
  {
    if(elesFlagVeto[ie] && elesLVec[ie].Pt()>(AnaConsts::elesMiniIsoArr).minPt && fabs(elesLVec[ie].Eta()) < (AnaConsts::elesMiniIsoArr).maxAbsEta && elesMiniIso[ie] < (AnaConsts::elesMiniIsoArr).maxIsoEB )
    {
      reco_els_pt  = ( elesLVec.at(ie) ).Pt();
      reco_els_eta = ( elesLVec.at(ie) ).Eta();
    }
  }
  if(reco_els_pt>25 && std::abs(reco_els_eta) < 2.5) isElPass=true;

  return isElPass;
}

bool MuPtEtaCut(
                std::vector<TLorentzVector> muonsLVec,
                std::vector<int> muonsFlagMedium,
                std::vector<double> muonsMiniIso
               )
{ 
  bool isMuPass=false;
  
  double reco_mus_pt = -1, reco_mus_eta = -20;
  for(unsigned int im = 0 ; im < muonsLVec.size() ; im++)
  { 
    if(muonsFlagMedium[im] && muonsLVec[im].Pt()>(AnaConsts::muonsMiniIsoArr).minPt && fabs(muonsLVec[im].Eta()) < (AnaConsts::muonsMiniIsoArr).maxAbsEta && muonsMiniIso[im] < (AnaConsts::muonsMiniIsoArr).maxIso )
    { 
      reco_mus_pt  = ( muonsLVec.at(im) ).Pt();
      reco_mus_eta = ( muonsLVec.at(im) ).Eta();
    }
  }
  if(reco_mus_pt>25  && std::abs(reco_mus_eta) < 2.4) isMuPass=true;
  
  return isMuPass;
}

double ElMuDataMCScaleFactor(
                             std::vector<TLorentzVector> elesLVec,
                             std::vector<int> elesFlagVeto,
                             std::vector<double> elesMiniIso,
	                           std::vector<TLorentzVector> muonsLVec,
                             std::vector<int> muonsFlagMedium,
                             std::vector<double> muonsMiniIso,
                             TH2F *el_ID_SF,
                             TH2F *el_ISO_SF,
                             TH2F *el_trk_SF,
                             TH2F *mu_ID_SF,
                             TH2F *mu_ISO_SF,
                             TH1D *mu_trkptGT10_SF,
                             TH1D *mu_trkptLT10_SF
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
    int ptbinid = el_ID_SF->GetXaxis()->FindBin(reco_els_pt);
    if(reco_els_pt > el_ID_SF->GetXaxis()->GetXmax()) ptbinid = el_ID_SF->GetXaxis()->FindBin(el_ID_SF->GetXaxis()->GetXmax()-1);
    if(reco_els_pt < el_ID_SF->GetXaxis()->GetXmin()) ptbinid = el_ID_SF->GetXaxis()->FindBin(el_ID_SF->GetXaxis()->GetXmin()+1);
    int etabinid = el_ID_SF->GetYaxis()->FindBin(std::abs(reco_els_eta));
    elsf *= el_ID_SF->GetBinContent(ptbinid,etabinid);

    int ptbiniso = el_ISO_SF->GetXaxis()->FindBin(reco_els_pt);
    if(reco_els_pt > el_ISO_SF->GetXaxis()->GetXmax()) ptbiniso = el_ISO_SF->GetXaxis()->FindBin(el_ISO_SF->GetXaxis()->GetXmax()-1);
    if(reco_els_pt < el_ISO_SF->GetXaxis()->GetXmin()) ptbiniso = el_ISO_SF->GetXaxis()->FindBin(el_ISO_SF->GetXaxis()->GetXmin()+1);
    int etabiniso = el_ISO_SF->GetYaxis()->FindBin(std::abs(reco_els_eta));
    elsf *= el_ISO_SF->GetBinContent(ptbiniso,etabiniso);

    int etabintrk = el_trk_SF->GetXaxis()->FindBin(reco_els_eta);
    int ptbintrk = el_trk_SF->GetYaxis()->FindBin(reco_els_pt);
    if(reco_els_pt > 200) ptbintrk = el_trk_SF->GetYaxis()->FindBin(200-1);
    if(reco_els_pt < 20 ) ptbintrk = el_trk_SF->GetYaxis()->FindBin(20 +1);
    elsf *= el_trk_SF->GetBinContent(etabintrk,ptbintrk);
    
    if(elsf<0.1) std::cout << "El Pt : " << reco_els_pt << " El Eta : "<< reco_els_eta << std::endl;

    return elsf;
  }
  else if(!isElCS && isMuCS)
  {
    double musf = 1;
    int ptbinid = mu_ID_SF->GetXaxis()->FindBin(reco_mus_pt);
    if(reco_mus_pt > mu_ID_SF->GetXaxis()->GetXmax()) ptbinid = mu_ID_SF->GetXaxis()->FindBin(mu_ID_SF->GetXaxis()->GetXmax()-1);
    if(reco_mus_pt < mu_ID_SF->GetXaxis()->GetXmin()) ptbinid = mu_ID_SF->GetXaxis()->FindBin(mu_ID_SF->GetXaxis()->GetXmin()+1);
    int etabinid = mu_ID_SF->GetYaxis()->FindBin(std::abs(reco_mus_eta));
    musf *= mu_ID_SF->GetBinContent(ptbinid,etabinid);

    int ptbiniso = mu_ISO_SF->GetXaxis()->FindBin(reco_mus_pt);
    if(reco_mus_pt > mu_ISO_SF->GetXaxis()->GetXmax()) ptbiniso = mu_ISO_SF->GetXaxis()->FindBin(mu_ISO_SF->GetXaxis()->GetXmax()-1);
    if(reco_mus_pt < mu_ISO_SF->GetXaxis()->GetXmin()) ptbiniso = mu_ISO_SF->GetXaxis()->FindBin(mu_ISO_SF->GetXaxis()->GetXmin()+1);
    int etabiniso = mu_ISO_SF->GetYaxis()->FindBin(std::abs(reco_mus_eta));
    musf *= mu_ISO_SF->GetBinContent(ptbiniso,etabiniso);

    if(reco_mus_pt > 10)
    {
      int etabintrk = mu_trkptGT10_SF->GetXaxis()->FindBin(reco_mus_eta);
      musf *= mu_trkptGT10_SF->GetBinContent(etabintrk);
    }
    else
    {
      int etabintrk = mu_trkptLT10_SF->GetXaxis()->FindBin(reco_mus_eta);
      musf *= mu_trkptLT10_SF->GetBinContent(etabintrk);
    }

    if(musf<0.1) std::cout << "Mu Pt : " << reco_mus_pt << " Mu Eta : "<< reco_mus_eta << std::endl;

    return musf;
  }
  else
  {
    std::cout << "the event is neither single electron CS nor single muon CS! Please check!" << std::endl;
    return 1;
  }
}

//Get Gen top information for top pt reweighting
std::vector<TLorentzVector> GetGenTopLVec(
                                          std::vector<TLorentzVector> genDecayLVec,
                                          std::vector<int> genDecayPdgIdVec,
                                          std::vector<int> genDecayIdxVec,
                                          std::vector<int> genDecayMomIdxVec
                                         )
{
  std::vector<TLorentzVector> tLVec;
  for(unsigned it=0; it<genDecayLVec.size(); it++)
  {
    int pdgId = genDecayPdgIdVec.at(it);
    if( std::abs(pdgId)==6 )
    {
      /*
      for(unsigned ig=0; ig<genDecayLVec.size(); ig++)
      {
        if( genDecayMomIdxVec.at(ig) == genDecayIdxVec.at(it) )
        {
          int pdgId = genDecayPdgIdVec.at(ig);
          if( std::abs(pdgId)==24 )
          {
            int flag = 0;
            for(unsigned iq=0; iq<genDecayLVec.size(); iq++)
            {
              if( genDecayMomIdxVec.at(iq) == genDecayIdxVec.at(ig) )
              {
                int pdgid = genDecayPdgIdVec.at(iq);
                if( std::abs(pdgid)==11 || std::abs(pdgid)==13 || std::abs(pdgid)==15 ) flag++;
              }
            }
            if(!flag) tLVec.push_back(genDecayLVec.at(it));
          }
        }
      }//dau. loop
      */
      tLVec.push_back(genDecayLVec.at(it));
    }//top cond
  }//genloop
  return tLVec;
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
