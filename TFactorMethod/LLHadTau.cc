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
  //double sr_qcd_sb[NSEARCH_BINS]={0};
  //double sr_qcd_sb_err[NSEARCH_BINS]={0};
  double sr_qcd_sb[NSEARCH_BINS]={204.729,6.50093,0.644066,0.300452,0.277241,53.0254,1.9418,0.212278,0.442387,2.37098,0.489912,0,0.00713334,0.0628432,0.239347,0.0242831,0.0364366,0.00429246,0.0312614,0.00127961,0.0558778,51.196,2.03097,0,0,0.19748,11.7698,0.167349,0.0381034,0,0.400529,0.0267274,0.025227,0.00722828,0.0055037,0.00573477,0,2.0249,0.668971,0.212707,0,2.71837,1.72609,0.118228,0,4.77023,1.42676,0,11.7541,1.00829,0.161495,0,1.88785,0,0.193209,0.151932,0.0447189,0.0314959,3.69755,0.459406,0.0771614,0,0.0595213,0.258214,0.0206266,0.138755,0,0,0.0013987,0.00420669,0.929288,0,0.251532,0,0.147951,1.34809,0.203445,0.164162,0.198193,0,0.430525,0,0.458259,0};
  double sr_qcd_sb_err[NSEARCH_BINS]={85.3285,11.014,3.91893,1.84966,0.935647,38.6186,3.06496,1.15707,1.50976,1.40318,0.475381,0.0280265,0.0339169,0.0867644,0.291086,0.0597018,0.0644301,0.0282852,0.0492162,0.0277504,0.0748305,33.2215,3.98434,0.209169,0.161415,0.671346,17.2343,0.304589,0.148592,0.0234301,0.348334,0.08347,0.0529013,0.0297823,0.0286998,0.0288874,0.0223213,2.03808,1.10773,0.717262,0.574942,2.00007,1.5522,0.706179,0.487419,3.70421,3.72905,0.610591,10.1081,1.77536,0.604408,0.12593,1.47293,0.150724,0.713589,0.206317,0.0820019,0.0586484,3.82466,0.975644,0.334422,0.101047,0.851863,0.626505,0.151229,0.183361,0.0220407,0.0220553,0.0395807,0.0289777,1.34893,0.575527,0.660312,0.698646,0.729218,1.75278,0.749443,0.639834,0.650698,0.575275,0.874694,0.575343,0.885111,0.574652};

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


  double sum_sr_had_sb = 0, sum_sr_qcd_sb = 0;
  for(int i=0;i<NSEARCH_BINS;i++)
  {
    //std::cout << "SB id: " << i << "; Had/Data: " << cr_had_sb[i]/cr_data_sb[i] << std::endl;
    (myAllHadTTJetsWJetsSTHistgram.h_sr_qcd_sb)->SetBinContent(i+1,sr_qcd_sb[i]);
    (myAllHadTTJetsWJetsSTHistgram.h_sr_qcd_sb)->SetBinError(i+1,sr_qcd_sb_err[i]);
    //std::cout << sr_had_sb[i] << " ";
    sum_sr_had_sb+=sr_had_sb[i];
    sum_sr_qcd_sb+=sr_qcd_sb[i];
  }
  std::cout << "HadTTJets/QCDPred: " << sum_sr_had_sb/sum_sr_qcd_sb << std::endl;;

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
