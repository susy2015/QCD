#ifndef BASIC_HISTS_H
#define BASIC_HISTS_H

#include <sstream>
#include <iostream>
#include <fstream>

#include "TH1D.h"
#include "TH2D.h"
#include "TH2Poly.h"
#include "TString.h"

#include "SusyAnaTools/Tools/searchBins.h"

char names[200], dispt[200];

TH2D * h2_evtCnt_sumSM_nbJets_vs_nTops = 0;
std::vector<TString> keyWordVec;

std::vector<TH1D*> h1_cutFlowVec, h1_cutFlow_auxVec;
TH1D * h1_keyString =0;

std::vector<TH2D*> h2_evtCnt_nbJets_vs_nTopsVec;

std::vector<std::string> declaredSampleStrVec;
std::vector<std::vector<TH2Poly*> > h2_poly_MT2_vs_metVec;

std::vector<std::vector<TH1D*> > h1_nJetsVec, h1_metVec, h1_MT2Vec, h1_mTcombVec, h1_HTVec, h1_nJetsRsysVec;

std::vector<std::vector<TH1D*> > h1_minDphi_topmetVec;

std::vector<TH1D*> h1_nJets_baselineVec, h1_nTops_baselineVec, h1_nbJets_baselineVec;
std::vector<TH1D*> h1_met_baselineVec, h1_MT2_baselineVec, h1_HT_baselineVec, h1_metphi_baselineVec;
std::vector<TH1D*> h1_dphi1_baselineVec, h1_dphi2_baselineVec, h1_dphi3_baselineVec;
std::vector<TH1D*> h1_topMass_baselineVec;
std::vector<TH1D*> h1_vtxSize_baselineVec;
std::vector<TH1D*> h1_allJetPt_baselineVec, h1_allJetEta_baselineVec, h1_allJetPhi_baselineVec, h1_allJetM_baselineVec;
std::vector<TH1D*> h1_leadJetPt_baselineVec, h1_leadJetEta_baselineVec, h1_leadJetPhi_baselineVec, h1_leadJetM_baselineVec;
std::vector<TH1D*> h1_muPt_baselineVec, h1_muEta_baselineVec, h1_muPhi_baselineVec;
std::vector<TH1D*> h1_elePt_baselineVec, h1_eleEta_baselineVec, h1_elePhi_baselineVec;


void declHistPerSample(const std::string &sampleKeyString){

  const TString sampleKeyStringT = sampleKeyString;

  TH1D * h1_cutFlow = new TH1D(sampleKeyStringT+"_h1_cutFlow", sampleKeyStringT+": cut flow table", 20, 0, 20); h1_cutFlow->SetBit(TH1::kCanRebin); h1_cutFlow->Sumw2(); h1_cutFlowVec.push_back((TH1D*)h1_cutFlow->Clone());
  TH1D * h1_cutFlow_aux = new TH1D(sampleKeyStringT+"_h1_cutFlow_aux", sampleKeyStringT+": more cut flow table", 20, 0, 20); h1_cutFlow_aux->SetBit(TH1::kCanRebin); h1_cutFlow_aux->Sumw2(); h1_cutFlow_auxVec.push_back((TH1D*)h1_cutFlow_aux->Clone());


  TH1D * h1_nJets_baseline = new TH1D(sampleKeyStringT+"_h1_nJets_baseline", sampleKeyStringT+": nJets after baseline; nJets", 14, 0, 14); h1_nJets_baseline->Sumw2(); h1_nJets_baselineVec.push_back((TH1D*)h1_nJets_baseline->Clone());
  TH1D * h1_nbJets_baseline = new TH1D(sampleKeyStringT+"_h1_nbJets_baseline", sampleKeyStringT+": nbJets after baseline; nbJets", 5, 0, 5); h1_nbJets_baseline->Sumw2(); h1_nbJets_baselineVec.push_back((TH1D*)h1_nbJets_baseline->Clone());
  TH1D * h1_nTops_baseline = new TH1D(sampleKeyStringT+"_h1_nTops_baseline", sampleKeyStringT+": nTops after baseline; nTops", 4, 0, 4); h1_nTops_baseline->Sumw2(); h1_nTops_baselineVec.push_back((TH1D*)h1_nTops_baseline->Clone());

  TH1D * h1_met_baseline = new TH1D(sampleKeyStringT+"_h1_met_baseline", sampleKeyStringT+": met after baseline; met (GeV)", 100, 0, 1000); h1_met_baseline->Sumw2(); h1_met_baselineVec.push_back((TH1D*)h1_met_baseline->Clone());
  TH1D * h1_MT2_baseline = new TH1D(sampleKeyStringT+"_h1_MT2_baseline", sampleKeyStringT+": MT2 after baseline; MT2 (GeV)", 100, 0, 1000); h1_MT2_baseline->Sumw2(); h1_MT2_baselineVec.push_back((TH1D*)h1_MT2_baseline->Clone());
  TH1D * h1_HT_baseline = new TH1D(sampleKeyStringT+"_h1_HT_baseline", sampleKeyStringT+": HT after baseline; HT (GeV)", 100, 0, 1000); h1_HT_baseline->Sumw2(); h1_HT_baselineVec.push_back((TH1D*)h1_HT_baseline->Clone());
  TH1D * h1_metphi_baseline = new TH1D(sampleKeyStringT+"_h1_metphi_baseline", sampleKeyStringT+": metphi after baseline; metphi", 100, -3.2, 3.2); h1_metphi_baseline->Sumw2(); h1_metphi_baselineVec.push_back((TH1D*)h1_metphi_baseline->Clone());

  TH1D * h1_dphi1_baseline = new TH1D(sampleKeyStringT+"_h1_dphi1_baseline", sampleKeyStringT+": dphi1 after baseline; dphi1", 100, 0.0, 3.2); h1_dphi1_baseline->Sumw2(); h1_dphi1_baselineVec.push_back((TH1D*)h1_dphi1_baseline->Clone());
  TH1D * h1_dphi2_baseline = new TH1D(sampleKeyStringT+"_h1_dphi2_baseline", sampleKeyStringT+": dphi2 after baseline; dphi2", 100, 0.0, 3.2); h1_dphi2_baseline->Sumw2(); h1_dphi2_baselineVec.push_back((TH1D*)h1_dphi2_baseline->Clone());
  TH1D * h1_dphi3_baseline = new TH1D(sampleKeyStringT+"_h1_dphi3_baseline", sampleKeyStringT+": dphi3 after baseline; dphi3", 100, 0.0, 3.2); h1_dphi3_baseline->Sumw2(); h1_dphi3_baselineVec.push_back((TH1D*)h1_dphi3_baseline->Clone());

  TH1D * h1_topMass_baseline = new TH1D(sampleKeyStringT+"_h1_topMass_baseline", sampleKeyStringT+": top mass after baseline; topM (GeV)", 100, 0, 300); h1_topMass_baseline->Sumw2(); h1_topMass_baselineVec.push_back((TH1D*)h1_topMass_baseline->Clone()); 

  TH1D * h1_vtxSize_baseline = new TH1D(sampleKeyStringT+"_h1_vtxSize_baseline", sampleKeyStringT+": vtxSize after baseline; vtxSize", 50, 0, 50); h1_vtxSize_baseline->Sumw2(); h1_vtxSize_baselineVec.push_back((TH1D*)h1_vtxSize_baseline->Clone());

  TH1D * h1_allJetPt_baseline = new TH1D(sampleKeyStringT+"_h1_allJetPt_baseline", sampleKeyStringT+": allJetPt after baseline; allJetPt (GeV)", 100, 0, 1000); h1_allJetPt_baseline->Sumw2(); h1_allJetPt_baselineVec.push_back((TH1D*)h1_allJetPt_baseline->Clone());
  TH1D * h1_allJetEta_baseline = new TH1D(sampleKeyStringT+"_h1_allJetEta_baseline", sampleKeyStringT+": allJetEta after baseline; allJetEta", 100, -5, 5); h1_allJetEta_baseline->Sumw2(); h1_allJetEta_baselineVec.push_back((TH1D*)h1_allJetEta_baseline->Clone());
  TH1D * h1_allJetPhi_baseline = new TH1D(sampleKeyStringT+"_h1_allJetPhi_baseline", sampleKeyStringT+": allJetPhi after baseline; allJetPhi", 100, -3.2, 3.2); h1_allJetPhi_baseline->Sumw2(); h1_allJetPhi_baselineVec.push_back((TH1D*)h1_allJetPhi_baseline->Clone());
  TH1D * h1_allJetM_baseline = new TH1D(sampleKeyStringT+"_h1_allJetM_baseline", sampleKeyStringT+": allJetM after baseline; allJetM (GeV)", 100, 0, 250); h1_allJetM_baseline->Sumw2(); h1_allJetM_baselineVec.push_back((TH1D*)h1_allJetM_baseline->Clone());

  TH1D * h1_leadJetPt_baseline = new TH1D(sampleKeyStringT+"_h1_leadJetPt_baseline", sampleKeyStringT+": leadJetPt after baseline; leadJetPt (GeV)", 100, 0, 1000); h1_leadJetPt_baseline->Sumw2(); h1_leadJetPt_baselineVec.push_back((TH1D*)h1_leadJetPt_baseline->Clone());
  TH1D * h1_leadJetEta_baseline = new TH1D(sampleKeyStringT+"_h1_leadJetEta_baseline", sampleKeyStringT+": leadJetEta after baseline; leadJetEta", 100, -5, 5); h1_leadJetEta_baseline->Sumw2(); h1_leadJetEta_baselineVec.push_back((TH1D*)h1_leadJetEta_baseline->Clone());
  TH1D * h1_leadJetPhi_baseline = new TH1D(sampleKeyStringT+"_h1_leadJetPhi_baseline", sampleKeyStringT+": leadJetPhi after baseline; leadJetPhi", 100, -3.2, 3.2); h1_leadJetPhi_baseline->Sumw2(); h1_leadJetPhi_baselineVec.push_back((TH1D*)h1_leadJetPhi_baseline->Clone());
  TH1D * h1_leadJetM_baseline = new TH1D(sampleKeyStringT+"_h1_leadJetM_baseline", sampleKeyStringT+": leadJetM after baseline; leadJetM (GeV)", 100, 0, 250); h1_leadJetM_baseline->Sumw2(); h1_leadJetM_baselineVec.push_back((TH1D*)h1_leadJetM_baseline->Clone());

  TH1D * h1_muPt_baseline = new TH1D(sampleKeyStringT+"_h1_muPt_baseline", sampleKeyStringT+": muPt after baseline; muPt (GeV)", 100, 0, 300); h1_muPt_baseline->Sumw2(); h1_muPt_baselineVec.push_back((TH1D*)h1_muPt_baseline->Clone());
  TH1D * h1_muEta_baseline = new TH1D(sampleKeyStringT+"_h1_muEta_baseline", sampleKeyStringT+": muEta after baseline; muEta", 100, -5, 5); h1_muEta_baseline->Sumw2(); h1_muEta_baselineVec.push_back((TH1D*)h1_muEta_baseline->Clone());
  TH1D * h1_muPhi_baseline = new TH1D(sampleKeyStringT+"_h1_muPhi_baseline", sampleKeyStringT+": muPhi after baseline; muPhi", 100, -3.2, 3.2); h1_muPhi_baseline->Sumw2(); h1_muPhi_baselineVec.push_back((TH1D*)h1_muPhi_baseline->Clone());

  TH1D * h1_elePt_baseline = new TH1D(sampleKeyStringT+"_h1_elePt_baseline", sampleKeyStringT+": elePt after baseline; elePt (GeV)", 100, 0, 300); h1_elePt_baseline->Sumw2(); h1_elePt_baselineVec.push_back((TH1D*)h1_elePt_baseline->Clone());
  TH1D * h1_eleEta_baseline = new TH1D(sampleKeyStringT+"_h1_eleEta_baseline", sampleKeyStringT+": eleEta after baseline; eleEta", 100, -5, 5); h1_eleEta_baseline->Sumw2(); h1_eleEta_baselineVec.push_back((TH1D*)h1_eleEta_baseline->Clone());
  TH1D * h1_elePhi_baseline = new TH1D(sampleKeyStringT+"_h1_elePhi_baseline", sampleKeyStringT+": elePhi after baseline; elePhi", 100, -3.2, 3.2); h1_elePhi_baseline->Sumw2(); h1_elePhi_baselineVec.push_back((TH1D*)h1_elePhi_baseline->Clone());

  TH2D * h2_evtCnt_nbJets_vs_nTops = new TH2D(sampleKeyStringT+"_h2_evtCnt_nbJets_vs_nTops", sampleKeyStringT+": event counts nbJets versus nTops; nTops; nbJets", 4, 0, 4, 3, 1, 4); h2_evtCnt_nbJets_vs_nTops->Sumw2(); h2_evtCnt_nbJets_vs_nTopsVec.push_back((TH2D*) h2_evtCnt_nbJets_vs_nTops->Clone());

  bool isDeclared = false;
  if( std::find(declaredSampleStrVec.begin(), declaredSampleStrVec.end(), sampleKeyStringT.Data()) != declaredSampleStrVec.end() ) isDeclared = true;
  else{ declaredSampleStrVec.push_back(sampleKeyString); }

  for(unsigned int iSR=0; iSR<nSR && !isDeclared; iSR++){
     std::vector<TH2Poly*> h2_PS_poly_MT2_vs_metVec;
     sprintf(names, "%s_h2_poly_MT2_vs_met_nbJets%s_nTops%s", sampleKeyStringT.Data(), keyStr_nbJets_SR[iSR].c_str(), keyStr_nTops_SR[iSR].c_str());
     sprintf(dispt, "%s: MT2 versus met for nbJets%s and nTops%s; met (GeV); MT2 (GeV)", sampleKeyStringT.Data(), disStr_nbJets_SR[iSR].c_str(), disStr_nTops_SR[iSR].c_str());
     TH2Poly * h2_poly_MT2_vs_met = new TH2Poly(names, dispt, 200, pseudoMax_met_for_hist, 200, pseudoMax_MT2_for_hist);
     h2_poly_MT2_vs_met->SetName(names); h2_poly_MT2_vs_met->SetTitle(dispt);
     for(unsigned int ib=0; ib<out_MT2_met_Binning_forTH2Poly[iSR].size(); ib++){ h2_poly_MT2_vs_met->AddBin(out_MT2_met_Binning_forTH2Poly[iSR][ib][0], out_MT2_met_Binning_forTH2Poly[iSR][ib][1], out_MT2_met_Binning_forTH2Poly[iSR][ib][2], out_MT2_met_Binning_forTH2Poly[iSR][ib][3]); }
     h2_poly_MT2_vs_met->Sumw2();
     if( h2_poly_MT2_vs_metVec.size() < iSR+1 ) { h2_PS_poly_MT2_vs_metVec.push_back((TH2Poly*)h2_poly_MT2_vs_met->Clone()); h2_poly_MT2_vs_metVec.push_back(h2_PS_poly_MT2_vs_metVec); }
     else{ h2_poly_MT2_vs_metVec[iSR].push_back((TH2Poly*)h2_poly_MT2_vs_met->Clone());}
  }

}

void declHistGlobal(){

   h2_evtCnt_sumSM_nbJets_vs_nTops = new TH2D("h2_evtCnt_sumSM_nbJets_vs_nTops", "SumSM: event counts nbJets versus nTops; nTops; nbJets", 4, 0, 4, 3, 1, 4); h2_evtCnt_sumSM_nbJets_vs_nTops->Sumw2();
   h1_keyString = new TH1D("h1_keyString", "key string", 5, 0, 5); h1_keyString->SetBit(TH1::kCanRebin);

}

#endif
