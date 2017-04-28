#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <cmath>
#include <set>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <fstream>
#include <vector>

#include "TStopwatch.h"
#include "TString.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TPad.h"
#include "TStyle.h"

#include "Math/QuantFuncMathCore.h"
#include "TMath.h"
#include "TLorentzVector.h"

#include "LLHadTau.h"

void LoopLLHadTauCal( LLHadTauFactors& myLLHadTauFactors, QCDSampleWeight& myQCDSampleWeight )
{
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;

  std::cout << "Let's calculate the LL and HadTau translation factor: " << std::endl;  
  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);

    double thisweight = (*iter_QCDSampleInfos).weight;
    if( ( (*iter_QCDSampleInfos).QCDTag ).find("MET") != std::string::npos ) thisweight = 1 * Scale;
    std::cout <<"Sample Type: "<< (*iter_QCDSampleInfos).QCDTag << "; Weight: " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTop");
      int nbotjets = tr.getVar<int>("nBot");
      double mt2 = tr.getVar<double>("mt2");
      double met = tr.getVar<double>("met");
      //closure plots variables
      int njets30 = tr.getVar<int>("nJets30");
      int njets50 = tr.getVar<int>("nJets50");
      double ht = tr.getVar<double>("ht");
      double mht = tr.getVar<double>("mht");

      int nMuons     = tr.getVar<int>("nMuons");
      int nElectrons = tr.getVar<int>("nElectrons");

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto");
      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      //normal baseline without dPhis and Lepton veto cut
      bool passBaselineLL = passTagger
                         && passBJets
                         && passQCDHighMETFilter
                         && passNoiseEventFilter;

      //apply trigger efficiencies
      //double metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( true, ht, met );
      double metEff = 1;
      if ( passBaselineLL )
      {
        int searchbin_id = mySearchBins.find_Binning_Index( nbotjets, ntopjets, mt2, met, ht );
        if( met<250 ) continue;

        double ISRCorr = tr.getVar<double>("ISRCorr");
        double BTagCorr = tr.getVar<double>("BTagCorr");
        
        bool isAllHad = tr.getVar<bool>("isAllHad");
        bool isLL = tr.getVar<bool>("isLL");
        bool isHadTau = tr.getVar<bool>("isHadTau");
        if(isAllHad)
        {
          if( ( (*iter_QCDSampleInfos).QCDTag ).find("Lept") != std::string::npos ) std::cout << "Get All Had events in the TTJets Leptonic channel??!!" << std::endl;
        }
        else
        {
          if(isLL)
          {
            if( passLeptVeto && ( passdPhis) ){ myLLHadTauFactors.SR_dphi_ll_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
            if( passLeptVeto && (!passdPhis) ){ myLLHadTauFactors.SR_invdphi_ll_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
          }
          if(isHadTau)
          {
            if( passLeptVeto && ( passdPhis) ){ myLLHadTauFactors.SR_dphi_hadtau_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
            if( passLeptVeto && (!passdPhis) ){ myLLHadTauFactors.SR_invdphi_hadtau_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
          }
          if( (nElectrons==0) && (nMuons == 1) && ( passdPhis) ){ myLLHadTauFactors.CR_dphi_singleMu_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
          if( (nElectrons==0) && (nMuons == 1) && (!passdPhis) ){ myLLHadTauFactors.CR_invdphi_singleMu_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
          if( (nElectrons==1) && (nMuons == 0) && ( passdPhis) ){ myLLHadTauFactors.CR_dphi_singleEl_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
          if( (nElectrons==1) && (nMuons == 0) && (!passdPhis) ){ myLLHadTauFactors.CR_invdphi_singleEl_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
          if( ((!isLL) && (!isHadTau)) || (isLL && isHadTau) ) std::cout << "Not All Had and also not LL not HadTau??!!" << std::endl;
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop

  myLLHadTauFactors.NumbertoTFactor();
  myLLHadTauFactors.printInfo();
  return ;
}

void LoopLLHadTauPredData( LLHadTauFactors& myLLHadTauFactors, QCDSampleWeight& myQCDSampleWeight )
{
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;

  double nData_dphi_CR_Mu=0, nMC_dphi_CR_Mu=0, nData_dphi_CR_El=0, nMC_dphi_CR_El=0;
  double nData_invdphi_CR_Mu=0, nMC_invdphi_CR_Mu=0, nData_invdphi_CR_El=0, nMC_invdphi_CR_El=0;

  std::cout << "Let's predict the LL and HadTau yield: " << std::endl;  
  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);

    double thisweight = (*iter_QCDSampleInfos).weight;
    if( ( (*iter_QCDSampleInfos).QCDTag ).find("MET") != std::string::npos ) thisweight = 1 * Scale;
    std::cout <<"Sample Type: "<< (*iter_QCDSampleInfos).QCDTag << "; Weight: " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTop");
      int nbotjets = tr.getVar<int>("nBot");
      double mt2 = tr.getVar<double>("mt2");
      double met = tr.getVar<double>("met");
      //closure plots variables
      int njets30 = tr.getVar<int>("nJets30");
      int njets50 = tr.getVar<int>("nJets50");
      double ht = tr.getVar<double>("ht");
      double mht = tr.getVar<double>("mht");

      int nMuons     = tr.getVar<int>("nMuons");
      int nElectrons = tr.getVar<int>("nElectrons");

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto");
      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      //normal baseline without dPhis and Lepton veto cut
      bool passBaselineLL = passTagger
                         && passBJets
                         && passQCDHighMETFilter
                         && passNoiseEventFilter;

      //apply trigger efficiencies
      //double metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( true, ht, met );
      double metEff = 1;
      if ( passBaselineLL )
      {
        int searchbin_id = mySearchBins.find_Binning_Index( nbotjets, ntopjets, mt2, met, ht );
        if( met<250 ) continue;

        if( ( (*iter_QCDSampleInfos).QCDTag ).find("MET") != std::string::npos )
        {
          if( (nElectrons==0) && (nMuons == 1) && ( passdPhis) ){ nData_dphi_CR_Mu+=thisweight; }
          if( (nElectrons==0) && (nMuons == 1) && (!passdPhis) ){ nData_invdphi_CR_Mu+=thisweight; }
          if( (nElectrons==1) && (nMuons == 0) && ( passdPhis) ){ nData_dphi_CR_El+=thisweight; }
          if( (nElectrons==1) && (nMuons == 0) && (!passdPhis) ){ nData_invdphi_CR_El+=thisweight; }
        }
        else
        {
          double ISRCorr = tr.getVar<double>("ISRCorr");
          double BTagCorr = tr.getVar<double>("BTagCorr");
          if( (nElectrons==0) && (nMuons == 1) && ( passdPhis) ){ nMC_dphi_CR_Mu+=thisweight*ISRCorr*BTagCorr; }
          if( (nElectrons==0) && (nMuons == 1) && (!passdPhis) ){ nMC_invdphi_CR_Mu+=thisweight*ISRCorr*BTagCorr; }
          if( (nElectrons==1) && (nMuons == 0) && ( passdPhis) ){ nMC_dphi_CR_El+=thisweight*ISRCorr*BTagCorr; }
          if( (nElectrons==1) && (nMuons == 0) && (!passdPhis) ){ nMC_invdphi_CR_El+=thisweight*ISRCorr*BTagCorr; }
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop
  std::cout << "dphi CR Mu overall Data/MC: " << nData_dphi_CR_Mu/nMC_dphi_CR_Mu << std::endl;
  std::cout << "invdphi CR Mu overall Data/MC: " << nData_invdphi_CR_Mu/nMC_invdphi_CR_Mu << std::endl;
  std::cout << "dphi CR El overall Data/MC: " << nData_dphi_CR_El/nMC_dphi_CR_El << std::endl;
  std::cout << "invdphi CR El overall Data/MC: " << nData_invdphi_CR_El/nMC_invdphi_CR_El << std::endl;
  return ;
}

void LoopLLHadTauAllHadStudy( LLHadTauFactors& myLLHadTauFactors, QCDSampleWeight& myQCDSampleWeight )
{
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  
  AllHadTTJetsWJetsSTHistgram myAllHadTTJetsWJetsSTHistgram;
  myAllHadTTJetsWJetsSTHistgram.BookHistgram( (dir_out + "AllHadTTJetsWJetsST.root").c_str() );
  
  double cr_had_sb[NSEARCH_BINS]={0}, cr_lept_sb[NSEARCH_BINS]={0}, cr_data_sb[NSEARCH_BINS]={0};
  double sr_had_sb[NSEARCH_BINS]={0}, sr_lept_sb[NSEARCH_BINS]={0}, sr_data_sb[NSEARCH_BINS]={0};
  double sr_qcd_sb[NSEARCH_BINS]={0};
  double sr_qcd_sb_err[NSEARCH_BINS]={0};
  //double sr_qcd_sb[NSEARCH_BINS]={170.179,7.75616,0.409068,0.192625,0.207445,43.251,1.83173,0.135019,0.277662,1.45875,0.525724,-0.0134822,0.00363832,0.0408321,0.2706,0.012484,0.0183167,0.00217602,0.0162454,0.000727278,0.0276462,43.5861,2.07933,-0.0692409,-0.0439108,0.145861,13.4119,0.256205,0.00705771,-0.00190889,0.241339,0.00630619,0.0125806,0.00361789,0.00323214,0.00293654,-0.00416238,0.874504,0.278113,0.0878673,-0.00983544,1.20302,0.724805,0.0512047,-0.115385,1.97962,0.594732,-0.075413,9.47035,0.924586,0.102283,-0.0188991,2.64092,0.18531,0.140479,0.144155,0.0221826,0.0155773,3.11106,0.430332,0.0498012,-0.0375358,0.0861389,0.235395,0.0131118,0.091604,-0.00175622,-0.00181063,0.00238067,0.00214157,0.382677,-0.0205641,0.102778,-0.07262,0.0650063,0.566029,0.0870332,0.0681539,0.0833899,-0.0201172,0.180428,-0.0134398,0.188605,0};
  //double sr_qcd_sb_err[NSEARCH_BINS]={75.853,8.18952,1.62421,0.783143,0.831271,32.5658,2.71335,0.894765,1.09675,1.68775,0.626474,0.0138361,0.0167123,0.0661538,0.378356,0.0310712,0.0342968,0.014061,0.0862839,0.0144539,0.145555,26.0467,3.1065,0.130207,0.100474,0.588059,37.2569,0.515968,0.0188754,0.010889,0.311843,0.065784,0.0268137,0.0148089,0.0222456,0.0212849,0.0110091,1.09757,0.503573,0.30293,0.197015,1.21194,0.886071,0.293166,0.199293,1.84914,1.53979,0.249632,9.50831,1.52178,0.441023,0.0786937,2.01889,0.465731,0.614343,0.242239,0.0438386,0.0316546,2.6771,0.855666,0.239512,0.0629168,0.685686,0.549709,0.0988645,0.157119,0.0108771,0.010884,0.026356,0.0145441,0.646833,0.197293,0.282624,0.285344,0.309669,0.854659,0.316846,0.268924,0.261669,0.197167,0.341827,0.197197,0.34695,0.196875};
  
  std::cout << "Let's study the all had part of TTJets, WJets and single top: " << std::endl;  
  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);

    double thisweight = (*iter_QCDSampleInfos).weight;
    if( ( (*iter_QCDSampleInfos).QCDTag ).find("MET") != std::string::npos ) thisweight = 1 * Scale;
    std::cout <<"Sample Type: "<< (*iter_QCDSampleInfos).QCDTag << "; Weight: " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTop");
      int nbotjets = tr.getVar<int>("nBot");
      double mt2 = tr.getVar<double>("mt2");
      double met = tr.getVar<double>("met");
      //closure plots variables
      int njets30 = tr.getVar<int>("nJets30");
      int njets50 = tr.getVar<int>("nJets50");
      double ht = tr.getVar<double>("ht");
      double mht = tr.getVar<double>("mht");

      int nMuons     = tr.getVar<int>("nMuons");
      int nElectrons = tr.getVar<int>("nElectrons");

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto");
      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      //normal baseline without dPhis and Lepton veto cut
      bool passBaselineQCD = passLeptVeto 
                          && passTagger
                          && passBJets
                          && passQCDHighMETFilter
                          && passNoiseEventFilter;

      //apply trigger efficiencies
      //double metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( true, ht, met );
      double metEff = 1;
      if ( passBaselineQCD )
      {
        int searchbin_id = mySearchBins.find_Binning_Index( nbotjets, ntopjets, mt2, met, ht );
        if( met<250 ) continue;
        if( ( (*iter_QCDSampleInfos).QCDTag ).find("TTJets_Inc") != std::string::npos )
        {
          double genht = tr.getVar<double>("genht");
          if( genht>=600 ) continue;
        }

        if(   ((*iter_QCDSampleInfos).QCDTag).find("TTJets") != std::string::npos
           || ((*iter_QCDSampleInfos).QCDTag).find("ST_tW") != std::string::npos
           || ((*iter_QCDSampleInfos).QCDTag).find("WJetsToLNu_HT") != std::string::npos
          )
        {
          double ISRCorr = tr.getVar<double>("ISRCorr");
          double BTagCorr = tr.getVar<double>("BTagCorr");
        
          bool isAllHad = tr.getVar<bool>("isAllHad");
          bool isLL = tr.getVar<bool>("isLL");
          bool isHadTau = tr.getVar<bool>("isHadTau");
          double ttjetsFactor = 0.84;
          if(isAllHad)
          {
            if(!passdPhis)
            { 
              (myAllHadTTJetsWJetsSTHistgram.h_cr_had_met)->Fill(met,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_had_njets30)->Fill(njets30,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_had_njets50)->Fill(njets50,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_had_mt2)->Fill(mt2,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_had_ht)->Fill(ht,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_had_mht)->Fill(mht,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_had_ntopjets)->Fill(ntopjets,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_had_nbjets)->Fill(nbotjets,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_had_sb)->Fill(searchbin_id,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              cr_had_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr*ttjetsFactor; 
            }
            else
            {
              (myAllHadTTJetsWJetsSTHistgram.h_sr_had_met)->Fill(met,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_had_njets30)->Fill(njets30,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_had_njets50)->Fill(njets50,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_had_mt2)->Fill(mt2,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_had_ht)->Fill(ht,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_had_mht)->Fill(mht,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_had_ntopjets)->Fill(ntopjets,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_had_nbjets)->Fill(nbotjets,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_had_sb)->Fill(searchbin_id,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              sr_had_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr*ttjetsFactor;
            }
          }
          else
          {
            if(!passdPhis)
            { 
              (myAllHadTTJetsWJetsSTHistgram.h_cr_lept_met)->Fill(met,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_lept_njets30)->Fill(njets30,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_lept_njets50)->Fill(njets50,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_lept_mt2)->Fill(mt2,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_lept_ht)->Fill(ht,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_lept_mht)->Fill(mht,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_lept_ntopjets)->Fill(ntopjets,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_lept_nbjets)->Fill(nbotjets,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_cr_lept_sb)->Fill(searchbin_id,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              cr_lept_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr*ttjetsFactor; 
            }
            else
            {
              (myAllHadTTJetsWJetsSTHistgram.h_sr_lept_met)->Fill(met,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_lept_njets30)->Fill(njets30,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_lept_njets50)->Fill(njets50,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_lept_mt2)->Fill(mt2,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_lept_ht)->Fill(ht,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_lept_mht)->Fill(mht,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_lept_ntopjets)->Fill(ntopjets,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_lept_nbjets)->Fill(nbotjets,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              (myAllHadTTJetsWJetsSTHistgram.h_sr_lept_sb)->Fill(searchbin_id,thisweight*ISRCorr*BTagCorr*ttjetsFactor);
              sr_lept_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr*ttjetsFactor;
            }
          }
        }//end of TTJets, WJets STMC sample
        if( ((*iter_QCDSampleInfos).QCDTag).find("MET") != std::string::npos )
        {
          if(!passdPhis)
          {
            (myAllHadTTJetsWJetsSTHistgram.h_cr_data_met)->Fill(met,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_cr_data_njets30)->Fill(njets30,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_cr_data_njets50)->Fill(njets50,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_cr_data_mt2)->Fill(mt2,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_cr_data_ht)->Fill(ht,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_cr_data_mht)->Fill(mht,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_cr_data_ntopjets)->Fill(ntopjets,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_cr_data_nbjets)->Fill(nbotjets,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_cr_data_sb)->Fill(searchbin_id,thisweight);
            cr_data_sb[searchbin_id]+=thisweight;
          }
          else
          {
            (myAllHadTTJetsWJetsSTHistgram.h_sr_data_met)->Fill(met,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_sr_data_njets30)->Fill(njets30,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_sr_data_njets50)->Fill(njets50,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_sr_data_mt2)->Fill(mt2,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_sr_data_ht)->Fill(ht,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_sr_data_mht)->Fill(mht,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_sr_data_ntopjets)->Fill(ntopjets,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_sr_data_nbjets)->Fill(nbotjets,thisweight);
            (myAllHadTTJetsWJetsSTHistgram.h_sr_data_sb)->Fill(searchbin_id,thisweight);
            sr_data_sb[searchbin_id]+=thisweight;
          }
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop

  for(int i=0;i<NSEARCH_BINS;i++)
  {
    //std::cout << "SB id: " << i << "; Had/Data: " << cr_had_sb[i]/cr_data_sb[i] << std::endl;
    (myAllHadTTJetsWJetsSTHistgram.h_sr_qcd_sb)->SetBinContent(i+1,sr_qcd_sb[i]);
    (myAllHadTTJetsWJetsSTHistgram.h_sr_qcd_sb)->SetBinError(i+1,sr_qcd_sb_err[i]);
    std::cout << sr_had_sb[i] << " ";
  }

  (myAllHadTTJetsWJetsSTHistgram.oFile)->Write();
  (myAllHadTTJetsWJetsSTHistgram.oFile)->Close();

  return ;
}

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cerr <<"Please give at least 3 arguments " << "RunMode " << " " << "runListMC " << " " << "runListData " << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./LLHadTau RunMode runlist_LLHadTauMC runlist_Data.txt" << std::endl;
    return -1;
  }

  std::string RunMode = argv[1];
  std::string inputFileList_LLHadTauDataMC = argv[2];
  std::string inputFileList_AllHadTTJetsSTWJets = argv[3];
 
  std::cout << "The valid run modes are: CalLLHadTau, PredDataLLHadTau" << std::endl;
  std::cout << "The run mode we have right now is: " << RunMode << std::endl;
  //myTriggerEff.SelfTest();
  LLHadTauFactors myLLHadTauFactors;

  double TTbar_SingleLept_BR = 0.43930872; // 2*W_Lept_BR*(1-W_Lept_BR)
  double TTbar_DiLept_BR = 0.10614564; // W_Lept_BR^2
  //sample needed in the LL TF calculation loop
  QCDSampleWeight myLLHadTauMCSampleWeight;
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_TTJets_DiLept"             ,         831.76*TTbar_DiLept_BR, 30444678, LUMI, 1, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromT_"   , 831.76*0.5*TTbar_SingleLept_BR, 61901450, LUMI, 1, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromTbar_", 831.76*0.5*TTbar_SingleLept_BR, 59860282, LUMI, 1, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_ST_tW_top"                 ,                           35.6,  6774350, LUMI, 1, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_ST_tW_antitop"             ,                           35.6,  6933094, LUMI, 1, inputFileList_LLHadTauDataMC.c_str() );
  //be careful!! WJets and ZJets samples have some tricky part, need to understand!
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-200To400"   ,   359.7,      38867206, LUMI, 1.21, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-400To600"   ,   48.91,       7759701, LUMI, 1.21, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-600To800"   ,   12.05,      17494743, LUMI, 1.21, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-800To1200"  ,   5.501,       7745467, LUMI, 1.21, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-1200To2500" ,   1.329,       6801534, LUMI, 1.21, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-2500ToInf"  , 0.03216,       2637821, LUMI, 1.21, inputFileList_LLHadTauDataMC.c_str() );

  //sample needed in the ll pred loop
  QCDSampleWeight myLLHadTauDataSampleWeight;
  myLLHadTauDataSampleWeight.QCDSampleInfo_push_back( "MET", 1, 1, LUMI, 1, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauDataSampleWeight.QCDSampleInfo_push_back( "_TTJets_DiLept"             ,         831.76*TTbar_DiLept_BR, 30444678, LUMI, 1, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauDataSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromT_"   , 831.76*0.5*TTbar_SingleLept_BR, 61901450, LUMI, 1, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauDataSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromTbar_", 831.76*0.5*TTbar_SingleLept_BR, 59860282, LUMI, 1, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauDataSampleWeight.QCDSampleInfo_push_back( "_ST_tW_top"                 ,                           35.6,  6774350, LUMI, 1, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauDataSampleWeight.QCDSampleInfo_push_back( "_ST_tW_antitop"             ,                           35.6,  6933094, LUMI, 1, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-200To400"   ,   359.7,      38867206, LUMI, 1.21, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-400To600"   ,   48.91,       7759701, LUMI, 1.21, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-600To800"   ,   12.05,      17494743, LUMI, 1.21, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-800To1200"  ,   5.501,       7745467, LUMI, 1.21, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-1200To2500" ,   1.329,       6801534, LUMI, 1.21, inputFileList_LLHadTauDataMC.c_str() );
  myLLHadTauDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-2500ToInf"  , 0.03216,       2637821, LUMI, 1.21, inputFileList_LLHadTauDataMC.c_str() );


  QCDSampleWeight myLLHadTauAllHadSampleWeight;
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "_TTJets_Inc_"          ,      831.76, 10139950, LUMI,    1, inputFileList_AllHadTTJetsSTWJets.c_str() );
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "_TTJets_HT-600to800_"  ,    2.666535, 14210872, LUMI,    1, inputFileList_AllHadTTJetsSTWJets.c_str() );
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "_TTJets_HT-800to1200_" ,    1.098082,  9982765, LUMI,    1, inputFileList_AllHadTTJetsSTWJets.c_str() );
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "_TTJets_HT-1200to2500_",    0.198748,  2932983, LUMI,    1, inputFileList_AllHadTTJetsSTWJets.c_str() );
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "_TTJets_HT-2500toInf_" , 0.002368413,  1519815, LUMI,    1, inputFileList_AllHadTTJetsSTWJets.c_str() );
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "_ST_tW_top"            ,        35.6,  6774350, LUMI,    1, inputFileList_AllHadTTJetsSTWJets.c_str() );
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "_ST_tW_antitop"        ,        35.6,  6933094, LUMI,    1, inputFileList_AllHadTTJetsSTWJets.c_str() );
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-200To400"   ,   359.7, 38867206, LUMI, 1.21, inputFileList_AllHadTTJetsSTWJets.c_str() );
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-400To600"   ,   48.91,  7759701, LUMI, 1.21, inputFileList_AllHadTTJetsSTWJets.c_str() );
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-600To800"   ,   12.05, 17494743, LUMI, 1.21, inputFileList_AllHadTTJetsSTWJets.c_str() );
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-800To1200"  ,   5.501,  7745467, LUMI, 1.21, inputFileList_AllHadTTJetsSTWJets.c_str() );
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-1200To2500" ,   1.329,  6801534, LUMI, 1.21, inputFileList_AllHadTTJetsSTWJets.c_str() );
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-2500ToInf"  , 0.03216,  2637821, LUMI, 1.21, inputFileList_AllHadTTJetsSTWJets.c_str() );
  myLLHadTauAllHadSampleWeight.QCDSampleInfo_push_back( "MET", 1, 1, LUMI, 1, inputFileList_LLHadTauDataMC.c_str() );

  if( RunMode == "CalLLHadTau" )
  {
    LoopLLHadTauCal( myLLHadTauFactors, myLLHadTauMCSampleWeight );
    return 0;
  }
  else if( RunMode == "PredDataLLHadTau" )
  {
    LoopLLHadTauPredData( myLLHadTauFactors, myLLHadTauDataSampleWeight );
    return 0;
  }
  else if( RunMode == "AllHadStudyLLHadTau" )
  {
    LoopLLHadTauAllHadStudy( myLLHadTauFactors, myLLHadTauAllHadSampleWeight );
    return 0;
  }
  else
  {
    std::cout << "Invalide RunMode!!" << std::endl;
    return 0;
  }

  return 0;
}
