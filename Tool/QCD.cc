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

#include "SusyAnaTools/Tools/samples.h"
#include "SusyAnaTools/Tools/searchBins.h"

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
//#include "TROOT.h"
//#include "TInterpreter.h"
#include "QCD.h"
//#include "QCDReWeighting.h"
#include "TFactorsHeader.h"
#include "DataDriven.h"
#include "TriggerEff.h"

const double Scale = 1;
//const double Scale = 591.5/2153.736;

void LoopQCDCal( QCDFactors& myQCDFactors, QCDSampleWeight& myQCDSampleWeight )
{
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  int i = 0;
  //use class BaselineVessel in the SusyAnaTools/Tools/baselineDef.h file
  const std::string spec = "QCD";
  myBaselineVessel = new BaselineVessel(spec);

  std::cout << "Calculation: " << std::endl;

  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {  
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);
    //initialize the type3Ptr defined in the customize.h
    AnaFunctions::prepareTopTagger();
    //The passBaseline is registered here
    tr.registerFunction(&mypassBaselineFunc);    
 
    double thisweight = (*iter_QCDSampleInfos).weight;
    myQCDFactors.QCDWeights[i] = thisweight;
    std::cout <<"Sample Type: "<< (*iter_QCDSampleInfos).QCDTag << "; Weight: " << thisweight << std::endl;
    
    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      int nbottomjets = tr.getVar<int>("cntCSVS"+spec);
      double MT2 = tr.getVar<double>("best_had_brJet_MT2"+spec);      
      double met = tr.getVar<double>("met");
      //closure plots variables
      int njets30 = tr.getVar<int>("cntNJetsPt30Eta24"+spec);
      int njets50 = tr.getVar<int>("cntNJetsPt50Eta24"+spec);
      double ht = tr.getVar<double>("HT"+spec);
      double mht = tr.getVar<double>("mht");

      std::vector<double> dPhiVec = tr.getVec<double>("dPhiVec"+spec);
      
      //checking plots for full QCD samples
      //filling HT variables for quick weight check
      //(myClosureHistgram.h_b_all_HT)->Fill(ht,thisweight);

      int metbin_number = Set_metbin_number(met);
      int njetsbin_number = Set_nbjetsbin_number(nbottomjets);
      int mt2bin_number = Set_mt2bin_number(MT2);

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto"+spec);
      bool passnJets = tr.getVar<bool>("passnJets"+spec);
      //bool passMET = tr.getVar<bool>("passMET"+spec);
      bool passHT = tr.getVar<bool>("passHT"+spec);
      bool passMT2 = tr.getVar<bool>("passMT2"+spec);
      bool passTagger = tr.getVar<bool>("passTagger"+spec);
      bool passBJets = tr.getVar<bool>("passBJets"+spec);
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter"+spec);
      bool passdPhis = tr.getVar<bool>("passdPhis"+spec);
      
      //normal baseline without dPhis cut
      bool passBaselineQCD = passLeptVeto
                          && passnJets
                          && passHT
                          && passMT2
                          && passTagger
                          //&& passBJets
                          && passNoiseEventFilter;
 
      //apply the met efficiencies
      double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      if (
          passBaselineQCD
         )
      {
        if ( passdPhis )
        {
          myQCDFactors.nQCDNormal_MC[i][metbin_number][mt2bin_number]++;
          myQCDFactors.nQCDNormal[i][metbin_number][mt2bin_number]+=(thisweight*metEff);
        }
      }  

      bool passBaseline_dPhisInverted = false;
      passBaseline_dPhisInverted = passBaselineQCD 
                                   && (!passdPhis);

      if (
          passBaseline_dPhisInverted
         )
      {
        myQCDFactors.nQCDInverted_MC[i][metbin_number][mt2bin_number]++;
        myQCDFactors.nQCDInverted[i][metbin_number][mt2bin_number]+=(thisweight*metEff);
        myQCDFactors.MET_sum[i][metbin_number][mt2bin_number] = myQCDFactors.MET_sum[i][metbin_number][mt2bin_number] + met * thisweight * metEff;
        myQCDFactors.MET_sum_weight[i][metbin_number][mt2bin_number] = myQCDFactors.MET_sum_weight[i][metbin_number][mt2bin_number] + thisweight * metEff;

        int searchbin_id = find_Binning_Index( nbottomjets , ntopjets , MT2, met );
        if( searchbin_id >= 0)
        {
          myQCDFactors.MET_sum_all_exp_sb[searchbin_id] = myQCDFactors.MET_sum_all_exp_sb[searchbin_id] + met * thisweight * metEff;
          myQCDFactors.MET_sum_weight_all_exp_sb[searchbin_id] = myQCDFactors.MET_sum_weight_all_exp_sb[searchbin_id] + thisweight * metEff;
          myQCDFactors.MT2_sum_all_exp_sb[searchbin_id] = myQCDFactors.MT2_sum_all_exp_sb[searchbin_id] + MT2 * thisweight * metEff;
          myQCDFactors.MT2_sum_weight_all_exp_sb[searchbin_id] = myQCDFactors.MT2_sum_weight_all_exp_sb[searchbin_id] + thisweight * metEff;
        }
      }
    }//end of inner loop
    i++;
  }//end of QCD Samples loop

  myQCDFactors.NumbertoTFactor();
  myQCDFactors.TFactorFit();
  myQCDFactors.TFactorScale();
  myQCDFactors.printQCDFactorInfo();
  myQCDFactors.printTFactorsHeader();
  
  myQCDFactors.TFactorsPlotsGen();
  myQCDFactors.CountingPlotsGen();
  return ;
}

void LoopQCDExp( QCDFactors& myQCDFactors, QCDSampleWeight& myQCDSampleWeight )
{
  ClosureHistgram myClosureHistgram;
  myClosureHistgram.BookHistgram( (dir_out + "ExpQCD.root").c_str() );

  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  int i = 0;
  //use class BaselineVessel in the SusyAnaTools/Tools/baselineDef.h file
  const std::string spec = "QCD";
  myBaselineVessel = new BaselineVessel(spec);

  std::cout << "Expectation: " << std::endl;

  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {  
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);
    //initialize the type3Ptr defined in the customize.h
    AnaFunctions::prepareTopTagger();
    //The passBaseline is registered here
    tr.registerFunction(&mypassBaselineFunc);    
 
    double thisweight = (*iter_QCDSampleInfos).weight;
    myQCDFactors.QCDWeights[i] = thisweight;
    std::cout <<"Sample Type: "<< (*iter_QCDSampleInfos).QCDTag << "; Weight: " << thisweight << std::endl;
    
    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      int nbottomjets = tr.getVar<int>("cntCSVS"+spec);
      double MT2 = tr.getVar<double>("best_had_brJet_MT2"+spec);      
      double met = tr.getVar<double>("met");
      //closure plots variables
      int njets30 = tr.getVar<int>("cntNJetsPt30Eta24"+spec);
      int njets50 = tr.getVar<int>("cntNJetsPt50Eta24"+spec);
      double ht = tr.getVar<double>("HT"+spec);
      double mht = tr.getVar<double>("mht");

      std::vector<double> dPhiVec = tr.getVec<double>("dPhiVec"+spec);
      
      //checking plots for full QCD samples
      //filling HT variables for quick weight check
      //(myClosureHistgram.h_b_all_HT)->Fill(ht,thisweight);

      int metbin_number = Set_metbin_number(met);
      int njetsbin_number = Set_nbjetsbin_number(nbottomjets);
      int mt2bin_number = Set_mt2bin_number(MT2);

      //normal baseline
      bool passBaselineQCD = tr.getVar<bool>("passBaseline"+spec);
      bool passdPhis = tr.getVar<bool>("passdPhis"+spec);
      passBaselineQCD = passBaselineQCD
                     && passdPhis;
      //apply the met efficiencies
      double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      if (
          passBaselineQCD
         )
      {
        (myClosureHistgram.h_exp_met)->Fill(met,thisweight*metEff);
        (myClosureHistgram.h_exp_njets30)->Fill(njets30,thisweight*metEff);
        (myClosureHistgram.h_exp_njets50)->Fill(njets50,thisweight*metEff);
        (myClosureHistgram.h_exp_mt2)->Fill(MT2,thisweight*metEff);
        (myClosureHistgram.h_exp_ht)->Fill(ht,thisweight*metEff);
        (myClosureHistgram.h_exp_mht)->Fill(mht,thisweight*metEff);
        (myClosureHistgram.h_exp_ntopjets)->Fill(ntopjets,thisweight*metEff);
        (myClosureHistgram.h_exp_nbjets)->Fill(nbottomjets,thisweight*metEff);
          
        int searchbin_id = find_Binning_Index( nbottomjets , ntopjets , MT2, met );
        if( searchbin_id >= 0 )
        {
          myQCDFactors.nQCD_exp_sb_MC[i][searchbin_id]++;
          myQCDFactors.nQCD_exp_sb[searchbin_id] += (thisweight*metEff);
          myQCDFactors.nQCD_exp_sb_err[searchbin_id] += (thisweight*metEff)*(thisweight*metEff);
        }
      }  
    }//end of inner loop
  }//end of QCD Samples loop
  
  for( int i=0 ; i<NSEARCH_BINS ; i++ )
  {
    myQCDFactors.nQCD_exp_sb_err[i] = std::sqrt( myQCDFactors.nQCD_exp_sb_err[i] );
  }

  myQCDFactors.printQCDClosureExp(myClosureHistgram);
  (myClosureHistgram.oFile)->Write();
  (myClosureHistgram.oFile)->Close();

  return ;
}

void LoopQCDPred( QCDFactors& myQCDFactors, QCDSampleWeight& myQCDSampleWeight, std::string RunMode )
{
  double QCDTFactorPred[MET_BINS][MT2_BINS] = {{0}}, QCDTFactorPred_err[MET_BINS][MT2_BINS] = {{0}};
  ClosureHistgram myClosureHistgram;
  if( RunMode.find("PredMC") != std::string::npos ) 
  { 
    //use Post fit tfactor for MC non closure
    myClosureHistgram.BookHistgram( (dir_out + "PredQCDMC.root").c_str() ); 
    for(int i=0;i<MET_BINS;i++)
    {
      for(int j=0;j<MT2_BINS;j++)
      {
        QCDTFactorPred[i][j] = head_QCDTFactorFit[i][j];
        QCDTFactorPred_err[i][j] = head_QCDTFactorFit_err[i][j];
      }
    }
  }
  else if( RunMode.find("PredData") != std::string::npos ) 
  {
    //use Real Data scaled tfactor for Prediction 
    myClosureHistgram.BookHistgram( (dir_out + "PredQCDData.root").c_str() ); 
    for(int i=0;i<MET_BINS;i++)
    {
      for(int j=0;j<MT2_BINS;j++)
      {
        QCDTFactorPred[i][j] = head_QCDTFactorScaled[i][j];
        QCDTFactorPred_err[i][j] = head_QCDTFactorScaled_err[i][j];
      }
    }
  }
  else{ std::cout << "Call Pred function but Not in the correct Pred Mode!! Please Check!!" << std::endl; return ; }

  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  int i = 0;
  //use class BaselineVessel in the SusyAnaTools/Tools/baselineDef.h file
  const std::string spec = "QCD";
  myBaselineVessel = new BaselineVessel(spec);

  std::cout << "Prediction: " << std::endl;
  
  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);
    //initialize the type3Ptr defined in the customize.h
    AnaFunctions::prepareTopTagger();
    //The passBaseline is registered here
    tr.registerFunction(&mypassBaselineFunc);

    double thisweight = (*iter_QCDSampleInfos).weight;
    //negative weight for other MC samples
    if( !( ( (*iter_QCDSampleInfos).QCDTag ).find("QCD") != std::string::npos) ) thisweight = -thisweight;
    if( ( (*iter_QCDSampleInfos).QCDTag ).find("HTMHT") != std::string::npos ) thisweight = 1 * Scale;

    std::cout <<"Sample Type: "<< (*iter_QCDSampleInfos).QCDTag << "; Weight: " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      int nbottomjets = tr.getVar<int>("cntCSVS"+spec);
      double MT2 = tr.getVar<double>("best_had_brJet_MT2"+spec);
      double met = tr.getVar<double>("met");
      //closure plots variables
      int njets30 = tr.getVar<int>("cntNJetsPt30Eta24"+spec);
      int njets50 = tr.getVar<int>("cntNJetsPt50Eta24"+spec);
      double ht = tr.getVar<double>("HT"+spec);
      double mht = tr.getVar<double>("mht");

      //if( met < 175 ) continue;
      int metbin_number = Set_metbin_number(met);
      int mt2bin_number = Set_mt2bin_number(MT2);

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto"+spec);
      bool passnJets = tr.getVar<bool>("passnJets"+spec);
      //bool passMET = tr.getVar<bool>("passMET"+spec);
      bool passHT = tr.getVar<bool>("passHT"+spec);
      bool passMT2 = tr.getVar<bool>("passMT2"+spec);
      bool passTagger = tr.getVar<bool>("passTagger"+spec);
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter"+spec);
      bool passBJets = tr.getVar<bool>("passBJets"+spec);
      bool passdPhis = tr.getVar<bool>("passdPhis"+spec);

      //normal baseline without dPhis cut
      bool passBaselineQCD = false;
      passBaselineQCD = passLeptVeto
                     && passnJets
                     && passHT
                     && passMT2
                     && passTagger
                     //&& passBJets
                     && passNoiseEventFilter;

      //apply trigger efficiencies
      double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      
      if ( passBaselineQCD )
      {
        if( (*iter_QCDSampleInfos).QCDTag == "HTMHT" )
        {
          std::vector<std::string> TriggerNames = tr.getVec<std::string>("TriggerNames");
          std::vector<int> PassTrigger = tr.getVec<int>("PassTrigger");
          bool foundTrigger = false;

          for(unsigned it=0; it<TriggerNames.size(); it++)
          {
            if
            (   TriggerNames[it].find("HLT_PFHT350_PFMET100_JetIdCleaned_v") != std::string::npos 
             || TriggerNames[it].find("HLT_PFHT350_PFMET100_NoiseCleaned_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFHT350_PFMET100_v") != std::string::npos
            )
            {
              if( PassTrigger[it] ) foundTrigger = true;
            }
          }

          if( !foundTrigger ) continue;
        }

        if( passBJets && (!passdPhis) )
        {
          double predweight = thisweight * metEff * QCDTFactorPred[metbin_number][mt2bin_number];
          (myClosureHistgram.h_pred_met)->Fill(met,predweight);
          (myClosureHistgram.h_pred_njets30)->Fill(njets30,predweight);
          (myClosureHistgram.h_pred_njets50)->Fill(njets50,predweight);
          (myClosureHistgram.h_pred_mt2)->Fill(MT2,predweight);
          (myClosureHistgram.h_pred_ht)->Fill(ht,predweight);
          (myClosureHistgram.h_pred_mht)->Fill(mht,predweight);
          (myClosureHistgram.h_pred_ntopjets)->Fill(ntopjets,predweight);
          (myClosureHistgram.h_pred_nbjets)->Fill(nbottomjets,predweight);

          //if( ht < 500) std::cout << ht << " small ht, what the fuck!!" << std::endl;

          int searchbin_id = find_Binning_Index( nbottomjets , ntopjets , MT2, met );
          if( searchbin_id >= 0 )
          {
            //std::cout << predweight << std::endl;
            if( (*iter_QCDSampleInfos).QCDTag == "HTMHT" )
            { 
              myQCDFactors.MET_sb_sum[searchbin_id] = myQCDFactors.MET_sb_sum[searchbin_id] + met * thisweight * metEff;
              myQCDFactors.MET_sb_sum_weight[searchbin_id] = myQCDFactors.MET_sb_sum_weight[searchbin_id] + thisweight * metEff;
              myQCDFactors.MT2_sb_sum[searchbin_id] = myQCDFactors.MT2_sb_sum[searchbin_id] + MT2 * thisweight * metEff;
              myQCDFactors.MT2_sb_sum_weight[searchbin_id] = myQCDFactors.MT2_sb_sum_weight[searchbin_id] + thisweight * metEff;

              myQCDFactors.DC_sb_Data[searchbin_id] += thisweight * metEff;
              myQCDFactors.DC_sb_Data_err[searchbin_id] += thisweight * metEff * thisweight * metEff; 
            }
            if( ((*iter_QCDSampleInfos).QCDTag).find("ZJetsToNuNu_HT") != std::string::npos )
            { 
              myQCDFactors.DC_sb_zinvMC[searchbin_id] += std::abs(thisweight * metEff);
              myQCDFactors.DC_sb_zinvMC_err[searchbin_id] += thisweight * metEff * thisweight * metEff;
            }
            if( ((*iter_QCDSampleInfos).QCDTag).find("TTZTo") != std::string::npos )
            { 
              myQCDFactors.DC_sb_ttzMC[searchbin_id] += std::abs(thisweight * metEff);
              myQCDFactors.DC_sb_ttzMC_err[searchbin_id] += thisweight * metEff * thisweight * metEff;
            }

            myQCDFactors.nQCD_pred_sb[searchbin_id] += (predweight);
            myQCDFactors.nQCD_pred_sb_err[searchbin_id] += (predweight * predweight);
          }
        }

        //Get normalized Tfactor in Inverted dPhi region in Real Data
        if( RunMode.find("PredData") != std::string::npos )
        {
          if( metbin_number == 0 )
          {
            if( passBJets )
            {
              if( passdPhis )
              {
                myQCDFactors.nQCDNormalData_all[mt2bin_number] += thisweight * metEff;
                myQCDFactors.nQCDNormalData_all_err[mt2bin_number] += thisweight * thisweight * metEff * metEff;
              }
              else 
              {
                myQCDFactors.nQCDInvertedData_all[mt2bin_number] += thisweight * metEff;
                myQCDFactors.nQCDInvertedData_all_err[mt2bin_number] += thisweight * thisweight * metEff * metEff;
              }
            }
          }
        }
      }//event loop
    }//end of inner loop
  }//end of QCD Samples loop

  if( RunMode.find("PredData") != std::string::npos )
  {
    //Data driven yield from other bg
    for( int i=0 ; i<NSEARCH_BINS ; i++ )
    {
      myQCDFactors.DC_sb_Data_err[i] = std::sqrt(myQCDFactors.DC_sb_Data_err[i]);
      myQCDFactors.DC_sb_zinvMC_err[i] = std::sqrt(myQCDFactors.DC_sb_zinvMC_err[i]);
      myQCDFactors.DC_sb_ttzMC_err[i] = std::sqrt(myQCDFactors.DC_sb_ttzMC_err[i]);

      myQCDFactors.MET_sb_mean[i] = myQCDFactors.MET_sb_sum[i]/myQCDFactors.MET_sb_sum_weight[i];
      myQCDFactors.MT2_sb_mean[i] = myQCDFactors.MT2_sb_sum[i]/myQCDFactors.MT2_sb_sum_weight[i];

      int met_id = -1, mt2_id = -1;
      met_id = Set_metbin_number( myQCDFactors.MET_sb_mean[i] );
      mt2_id = Set_mt2bin_number( myQCDFactors.MT2_sb_mean[i] );
      //std::cout << met_id << "," << mt2_id << std::endl;

      //set up data card from Tfactors
      if( met_id < 0 || mt2_id < 0 )
      {
        //reset the met and mt2 id with average value from MC
        met_id = Set_metbin_number( head_QCD_meanMET_exp_sb[i] );
        mt2_id = Set_mt2bin_number( head_QCD_meanMT2_exp_sb[i] );
      }
        
      myQCDFactors.DC_sb_TFactor[i] = QCDTFactorPred[met_id][mt2_id];
      myQCDFactors.DC_sb_TFactor_err[i] = QCDTFactorPred_err[met_id][mt2_id];
      //set up data card from data driven input
      myQCDFactors.DC_sb_hadtau[i] = pred_sb_hadtau[i];
      myQCDFactors.DC_sb_lostlept[i] = pred_sb_lostlept[i];
      myQCDFactors.DC_sb_hadtau_errup[i] = std::sqrt( pred_sb_hadtau_stat[i]*pred_sb_hadtau_stat[i] + pred_sb_hadtau_sysUp[i]*pred_sb_hadtau_sysUp[i] );
      myQCDFactors.DC_sb_hadtau_errdown[i] = std::sqrt( pred_sb_hadtau_stat[i]*pred_sb_hadtau_stat[i] + pred_sb_hadtau_sysDown[i]*pred_sb_hadtau_sysDown[i] );
      myQCDFactors.DC_sb_lostlept_errup[i] = pred_sb_lostlept_stat[i];
      myQCDFactors.DC_sb_lostlept_errdown[i] = pred_sb_lostlept_stat[i];

      myQCDFactors.nQCD_pred_sb[i] -= pred_sb_hadtau[i] * QCDTFactorPred[met_id][mt2_id];
      //myQCDFactors.nQCD_pred_sb_err[i] += pred_sb_hadtau_stat[i] * pred_sb_hadtau_stat[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];
      myQCDFactors.nQCD_pred_sb[i] -= pred_sb_lostlept[i] * QCDTFactorPred[met_id][mt2_id];
      //myQCDFactors.nQCD_pred_sb_err[i] += pred_sb_lostlept_stat[i] * pred_sb_lostlept_stat[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];
    }
    //deal with the Tfactor from data
    myQCDFactors.getAndprintTFactorsfromDataHeader(); 
    myQCDFactors.printDataCard();
  }

  for( int i=0 ; i<NSEARCH_BINS ; i++ )
  {
    myQCDFactors.nQCD_pred_sb_err[i] = std::sqrt( myQCDFactors.nQCD_pred_sb_err[i] );
  }

  myQCDFactors.printQCDClosurePred(myClosureHistgram);
  (myClosureHistgram.oFile)->Write();
  (myClosureHistgram.oFile)->Close();
  return ;
}

void LoopQCDTFactorsUnc( QCDSampleWeight& myQCDSampleWeight, std::string RunMode )
{
  double QCDTFactorPred[MET_BINS][MT2_BINS] = {{0}}, QCDTFactorPred_err[MET_BINS][MT2_BINS] = {{0}};
  double nQCD_pred_sb_TFactorUnc_up[MET_BINS][MT2_BINS][NSEARCH_BINS] = {{{0}}}, nQCD_pred_sb_TFactorUnc_up_err[MET_BINS][MT2_BINS][NSEARCH_BINS] = {{{0}}};
  double nQCD_pred_sb_TFactorUnc_down[MET_BINS][MT2_BINS][NSEARCH_BINS] = {{{0}}}, nQCD_pred_sb_TFactorUnc_down_err[MET_BINS][MT2_BINS][NSEARCH_BINS] = {{{0}}};

  double MET_sb_sum[NSEARCH_BINS] = {0}, MET_sb_sum_weight[NSEARCH_BINS] = {0};
  double MET_sb_mean[NSEARCH_BINS] = {0};
  double MT2_sb_sum[NSEARCH_BINS] = {0}, MT2_sb_sum_weight[NSEARCH_BINS] = {0};
  double MT2_sb_mean[NSEARCH_BINS] = {0};

  TFactorsUncHistgram myTFactorsUncHistgram;
  myTFactorsUncHistgram.BookHistgram( (dir_out  + RunMode + ".root").c_str() );

  if( RunMode.find("TFactorsUnc") != std::string::npos )
  {
    //int met_index = std::stoi (RunMode.substr(0,1));
    //int mt2_index = std::stoi (RunMode.substr(1,1));
    //10,11.20,21
    //if( met_index < 1 || met_index > MET_BINS-1 || mt2_index < 0 || mt2_index > MT2_BINS-1 ){ std::cout << "Invalid Tfactor index! WTF?" << std::endl; return ; }
    for(int i=0;i<MET_BINS;i++)
    {
      for(int j=0;j<MT2_BINS;j++)
      {
        QCDTFactorPred[i][j] = head_QCDTFactorScaled[i][j];
        QCDTFactorPred_err[i][j] = head_QCDTFactorScaled_err[i][j];
      }
    }
  }
  else{ std::cout << "Call Tfactor Unc function but Not in the correct Mode!! Please Check!!" << std::endl; return ; }

  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  //use class BaselineVessel in the SusyAnaTools/Tools/baselineDef.h file
  const std::string spec = "QCD";
  myBaselineVessel = new BaselineVessel(spec);

  std::cout << "TFactor Unc Calculation: " << std::endl;
  
  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);
    //initialize the type3Ptr defined in the customize.h
    AnaFunctions::prepareTopTagger();
    //The passBaseline is registered here
    tr.registerFunction(&mypassBaselineFunc);

    double thisweight = (*iter_QCDSampleInfos).weight;
    //negative weight for other MC samples
    if( !( ( (*iter_QCDSampleInfos).QCDTag ).find("QCD") != std::string::npos) ) thisweight = -thisweight;
    if( ( (*iter_QCDSampleInfos).QCDTag ).find("HTMHT") != std::string::npos ) thisweight = 1;

    std::cout <<"Sample Type: "<< (*iter_QCDSampleInfos).QCDTag << "; Weight: " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      int nbottomjets = tr.getVar<int>("cntCSVS"+spec);
      double MT2 = tr.getVar<double>("best_had_brJet_MT2"+spec);
      double met = tr.getVar<double>("met");

      //if( met < 175 ) continue;
      int metbin_number = Set_metbin_number(met);
      int mt2bin_number = Set_mt2bin_number(MT2);

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto"+spec);
      bool passnJets = tr.getVar<bool>("passnJets"+spec);
      //bool passMET = tr.getVar<bool>("passMET"+spec);
      bool passHT = tr.getVar<bool>("passHT"+spec);
      bool passMT2 = tr.getVar<bool>("passMT2"+spec);
      bool passTagger = tr.getVar<bool>("passTagger"+spec);
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter"+spec);
      bool passBJets = tr.getVar<bool>("passBJets"+spec);
      bool passdPhis = tr.getVar<bool>("passdPhis"+spec);

      //normal baseline without dPhis cut
      bool passBaselineQCD = false;
      passBaselineQCD = passLeptVeto
                     && passnJets
                     && passHT
                     && passMT2
                     && passTagger
                     //&& passBJets
                     && passNoiseEventFilter;

      //apply trigger efficiencies
      double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      
      if( passBaselineQCD )
      {
        if( (*iter_QCDSampleInfos).QCDTag == "HTMHT" )
        {
          std::vector<std::string> TriggerNames = tr.getVec<std::string>("TriggerNames");
          std::vector<int> PassTrigger = tr.getVec<int>("PassTrigger");
          bool foundTrigger = false;

          for(unsigned it=0; it<TriggerNames.size(); it++)
          {
            if
            (   TriggerNames[it].find("HLT_PFHT350_PFMET100_JetIdCleaned_v") != std::string::npos 
             || TriggerNames[it].find("HLT_PFHT350_PFMET100_NoiseCleaned_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFHT350_PFMET100_v") != std::string::npos
            )
            {
              if( PassTrigger[it] ) foundTrigger = true;
            }
          }

          if( !foundTrigger ) continue;
        }

        if( passBJets && (!passdPhis) )
        {
          for(int i=0;i<MET_BINS;i++)
          { 
            for(int j=0;j<MT2_BINS;j++)
            { 
              double predweight = thisweight * metEff * QCDTFactorPred[metbin_number][mt2bin_number];
              double prede = 0;
              if( metbin_number == i && mt2bin_number == j )
              {
                prede = thisweight * metEff * QCDTFactorPred_err[metbin_number][mt2bin_number];
              }
              double predweight_up = predweight + prede;
              double predweight_down = predweight - prede;
              if( predweight_down < 0 ) predweight_down = 0;

              int searchbin_id = find_Binning_Index( nbottomjets , ntopjets , MT2, met );
              if( searchbin_id >= 0 )
              {
                //std::cout << predweight << std::endl;
                if( (*iter_QCDSampleInfos).QCDTag == "HTMHT" )
                {
                  MET_sb_sum[searchbin_id] = MET_sb_sum[searchbin_id] + met * thisweight * metEff;
                  MET_sb_sum_weight[searchbin_id] = MET_sb_sum_weight[searchbin_id] + thisweight * metEff;
                  MT2_sb_sum[searchbin_id] = MT2_sb_sum[searchbin_id] + MT2 * thisweight * metEff;
                  MT2_sb_sum_weight[searchbin_id] = MT2_sb_sum_weight[searchbin_id] + thisweight * metEff;
                }

                nQCD_pred_sb_TFactorUnc_up[i][j][searchbin_id] += (predweight_up);
                nQCD_pred_sb_TFactorUnc_up_err[i][j][searchbin_id] += (predweight_up * predweight_up);
                nQCD_pred_sb_TFactorUnc_down[i][j][searchbin_id] += (predweight_down);
                nQCD_pred_sb_TFactorUnc_down_err[i][j][searchbin_id] += (predweight_down * predweight_down);
              }
            }
          }
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop

  for(int i=0;i<MET_BINS;i++)
  {
    for(int j=0;j<MT2_BINS;j++)
    {
      for(int k=0;k<NSEARCH_BINS;k++)
      {
        MET_sb_mean[k] = MET_sb_sum[k]/MET_sb_sum_weight[k];
        MT2_sb_mean[k] = MT2_sb_sum[k]/MT2_sb_sum_weight[k];
      
        int met_id = -1, mt2_id = -1;
        met_id = Set_metbin_number( MET_sb_mean[i] );
        mt2_id = Set_mt2bin_number( MT2_sb_mean[i] );
      
        if( met_id >= 0 && mt2_id >= 0 )
        { 
          nQCD_pred_sb_TFactorUnc_up[i][j][k] -= pred_sb_hadtau[k] * QCDTFactorPred[met_id][mt2_id]; 
          nQCD_pred_sb_TFactorUnc_down[i][j][k] -= pred_sb_hadtau[k] * QCDTFactorPred[met_id][mt2_id];
          //nQCD_pred_sb_err[i] += pred_sb_hadtau_stat[i] * pred_sb_hadtau_stat[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];
          nQCD_pred_sb_TFactorUnc_up[i][j][k] -= pred_sb_lostlept[k] * QCDTFactorPred[met_id][mt2_id];
          nQCD_pred_sb_TFactorUnc_down[i][j][k] -= pred_sb_lostlept[k] * QCDTFactorPred[met_id][mt2_id];
          //myQCDFactors.nQCD_pred_sb_err[i] += pred_sb_lostlept_stat[i] * pred_sb_lostlept_stat[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];
        }

        if( met_id == i && mt2_id == j ) 
        {
          nQCD_pred_sb_TFactorUnc_up[i][j][k] += ( pred_sb_hadtau[k] + pred_sb_lostlept[k] ) * QCDTFactorPred_err[met_id][mt2_id];
          nQCD_pred_sb_TFactorUnc_down[i][j][k] -= ( pred_sb_hadtau[k] + pred_sb_lostlept[k] ) * QCDTFactorPred_err[met_id][mt2_id];
        }
        nQCD_pred_sb_TFactorUnc_up_err[i][j][k] = std::sqrt( nQCD_pred_sb_TFactorUnc_up_err[i][j][k] );
        nQCD_pred_sb_TFactorUnc_down_err[i][j][k] = std::sqrt( nQCD_pred_sb_TFactorUnc_down_err[i][j][k] );

        (myTFactorsUncHistgram.h_pred_sb_TFactorsUnc_up[i][j])->SetBinContent( k+1 , nQCD_pred_sb_TFactorUnc_up[i][j][k] );
        (myTFactorsUncHistgram.h_pred_sb_TFactorsUnc_up[i][j])->SetBinError( k+1 , nQCD_pred_sb_TFactorUnc_up_err[i][j][k] );
        (myTFactorsUncHistgram.h_pred_sb_TFactorsUnc_down[i][j])->SetBinContent( k+1 , nQCD_pred_sb_TFactorUnc_down[i][j][k] );
        (myTFactorsUncHistgram.h_pred_sb_TFactorsUnc_down[i][j])->SetBinError( k+1 , nQCD_pred_sb_TFactorUnc_down_err[i][j][k] );
      }
    }
  }

  (myTFactorsUncHistgram.oFile)->Write();
  (myTFactorsUncHistgram.oFile)->Close();

  return ;
}

void LoopBasicCheckQCD( QCDSampleWeight& myQCDSampleWeight )
{
  BasicCheckHistgram myBasicCheckHistgram;
  myBasicCheckHistgram.BookHistgram( (dir_out + "BasicCheckQCD.root").c_str() );
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  //use class BaselineVessel in the SusyAnaTools/Tools/baselineDef.h file
  const std::string spec = "QCD";
  myBaselineVessel = new BaselineVessel(spec);

  std::cout << "Let's check inverted Delta Phi region for QCD: " << std::endl;
  
  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);
    //initialize the type3Ptr defined in the customize.h
    AnaFunctions::prepareTopTagger();
    //The passBaseline is registered here
    tr.registerFunction(&mypassBaselineFunc);

    double thisweight = (*iter_QCDSampleInfos).weight;
    if( ( (*iter_QCDSampleInfos).QCDTag ).find("HTMHT") != std::string::npos ) thisweight = 1 * Scale;
    std::cout <<"Sample Type: "<< (*iter_QCDSampleInfos).QCDTag << "; Weight: " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      int nbottomjets = tr.getVar<int>("cntCSVS"+spec);
      double MT2 = tr.getVar<double>("best_had_brJet_MT2"+spec);
      double met = tr.getVar<double>("met");
      //closure plots variables
      int njets30 = tr.getVar<int>("cntNJetsPt30Eta24"+spec);
      int njets50 = tr.getVar<int>("cntNJetsPt50Eta24"+spec);
      double ht = tr.getVar<double>("HT"+spec);
      double mht = tr.getVar<double>("mht");

      //if( met < 175 ) continue;
      int metbin_number = Set_metbin_number(met);
      int njetsbin_number = Set_nbjetsbin_number(nbottomjets);
      int mt2bin_number = Set_mt2bin_number(MT2);

      bool passBaselineQCD = tr.getVar<bool>("passBaseline"+spec);
      bool passdPhis = tr.getVar<bool>("passdPhis"+spec);
      bool passBaseline_dPhisInverted = false;
      //bool passBaseline_dPhis = false;

      std::vector<double> dPhiVec = tr.getVec<double>("dPhiVec"+spec);
      bool passMydPhis = (dPhiVec.at(0) >= 0.4 && dPhiVec.at(1) >= 0.4 && dPhiVec.at(2) >= 0.3);
      passBaseline_dPhisInverted = passBaselineQCD && (!passMydPhis);
      //passBaseline_dPhis = passBaselineQCD && passdPhis;
      //apply trigger efficiencies
      double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );

      if (passBaseline_dPhisInverted)
      {
        int searchbin_id = find_Binning_Index( nbottomjets , ntopjets , MT2, met );

        if( (*iter_QCDSampleInfos).QCDTag == "HTMHT" )
        {
          std::vector<std::string> TriggerNames = tr.getVec<std::string>("TriggerNames");
          std::vector<int> PassTrigger = tr.getVec<int>("PassTrigger");
          bool foundTrigger = false;

          for(unsigned it=0; it<TriggerNames.size(); it++)
          {
            if
            (   TriggerNames[it].find("HLT_PFHT350_PFMET100_JetIdCleaned_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFHT350_PFMET100_NoiseCleaned_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFHT350_PFMET100_v") != std::string::npos
            )

            {
              if( PassTrigger[it] ) foundTrigger = true;
            }
          }

          if( !foundTrigger ) continue;

          (myBasicCheckHistgram.h_b_met_Data)->Fill(met,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mt2_Data)->Fill(MT2,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ntopjets_Data)->Fill(ntopjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_nbjets_Data)->Fill(nbottomjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ht_Data)->Fill(ht,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mht_Data)->Fill(mht,thisweight*metEff);
          (myBasicCheckHistgram.h_b_njets30_Data)->Fill(njets30,thisweight*metEff);
          (myBasicCheckHistgram.h_b_njets50_Data)->Fill(njets50,thisweight*metEff);

          (myBasicCheckHistgram.h_b_sb_Data)->Fill(searchbin_id,thisweight*metEff);
        }
        else
        {
          Int_t ih = -1;

          if( ((*iter_QCDSampleInfos).QCDTag).find("TTJets") != std::string::npos ) ih = 0;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("ST_tW") != std::string::npos ) ih = 1;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("WJetsToLNu_HT") != std::string::npos ) ih = 2;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("ZJetsToNuNu_HT") != std::string::npos ) ih = 3;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("QCD_HT") != std::string::npos ) ih = 4;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("TTZTo") != std::string::npos ) ih = 5;
          else std::cout << "Invalid tag! what the fuck is going on ?!" << std::endl;

          (myBasicCheckHistgram.h_b_met_MC[ih])->Fill(met,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mt2_MC[ih])->Fill(MT2,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ntopjets_MC[ih])->Fill(ntopjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_nbjets_MC[ih])->Fill(nbottomjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ht_MC[ih])->Fill(ht,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mht_MC[ih])->Fill(mht,thisweight*metEff);
          (myBasicCheckHistgram.h_b_njets30_MC)[ih]->Fill(njets30,thisweight*metEff);
          (myBasicCheckHistgram.h_b_njets50_MC)[ih]->Fill(njets50,thisweight*metEff);

          (myBasicCheckHistgram.h_b_sb_MC)[ih]->Fill(searchbin_id,thisweight*metEff);
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop

  (myBasicCheckHistgram.oFile)->Write();
  (myBasicCheckHistgram.oFile)->Close();
  return ;
}

void LoopBasicCheckLL( QCDSampleWeight& myQCDSampleWeight )
{
  BasicCheckHistgram myBasicCheckHistgram;
  myBasicCheckHistgram.BookHistgram( (dir_out + "BasicCheckLL.root").c_str() );
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  //use class BaselineVessel in the SusyAnaTools/Tools/baselineDef.h file
  const std::string spec = "lostlept";
  myBaselineVessel = new BaselineVessel(spec);

  std::cout << "Let's check single Muon region for LL: " << std::endl;
  
  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);
    //initialize the type3Ptr defined in the customize.h
    AnaFunctions::prepareTopTagger();
    //The passBaseline is registered here
    tr.registerFunction(&mypassBaselineFunc);

    double thisweight = (*iter_QCDSampleInfos).weight;
    if( ( (*iter_QCDSampleInfos).QCDTag ).find("HTMHT") != std::string::npos ) thisweight = 1 * Scale;
    std::cout <<"Sample Type: "<< (*iter_QCDSampleInfos).QCDTag << "; Weight: " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      int nbottomjets = tr.getVar<int>("cntCSVS"+spec);
      double MT2 = tr.getVar<double>("best_had_brJet_MT2"+spec);
      double met = tr.getVar<double>("met");
      //closure plots variables
      int njets30 = tr.getVar<int>("cntNJetsPt30Eta24"+spec);
      int njets50 = tr.getVar<int>("cntNJetsPt50Eta24"+spec);
      double ht = tr.getVar<double>("HT"+spec);
      double mht = tr.getVar<double>("mht");
      //single muon CS
      int nMuons = tr.getVar<int>("nMuons_CUT" + spec);

      //if( met < 175 ) continue;
      int metbin_number = Set_metbin_number(met);
      int njetsbin_number = Set_nbjetsbin_number(nbottomjets);
      int mt2bin_number = Set_mt2bin_number(MT2);

      //bool passLeptVeto = tr.getVar<bool>("passLeptVeto"+spec);
      bool passnJets = tr.getVar<bool>("passnJets"+spec);
      bool passMET = tr.getVar<bool>("passMET"+spec);
      bool passHT = tr.getVar<bool>("passHT"+spec);
      bool passMT2 = tr.getVar<bool>("passMT2"+spec);
      bool passTagger = tr.getVar<bool>("passTagger"+spec);
      bool passBJets = tr.getVar<bool>("passBJets"+spec);
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter"+spec);
      bool passdPhis = tr.getVar<bool>("passdPhis"+spec);

      //normal baseline without dPhis cut
      bool passBaselineLL = passnJets
                         && passMET
                         && passHT
                         && passMT2
                         && passTagger
                         && passBJets
                         && passdPhis
                         && passNoiseEventFilter;

      bool passEleVeto = tr.getVar<bool>("passEleVeto"+spec);

      //apply trigger efficiencies
      double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );

      if ( 
           passBaselineLL && passEleVeto && (nMuons == 1) 
        //&& (!passdPhis)
         )
      {
        if( (*iter_QCDSampleInfos).QCDTag == "HTMHT" )
        {
          std::vector<std::string> TriggerNames = tr.getVec<std::string>("TriggerNames");
          std::vector<int> PassTrigger = tr.getVec<int>("PassTrigger");
          bool foundTrigger = false;

          for(unsigned it=0; it<TriggerNames.size(); it++)
          {
            if
            (   TriggerNames[it].find("HLT_PFHT350_PFMET100_JetIdCleaned_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFHT350_PFMET100_NoiseCleaned_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFHT350_PFMET100_v") != std::string::npos
            )
            {
              if( PassTrigger[it] ) foundTrigger = true;
            }
          }

          if( !foundTrigger ) continue;

          (myBasicCheckHistgram.h_b_met_Data)->Fill(met,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mt2_Data)->Fill(MT2,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ntopjets_Data)->Fill(ntopjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_nbjets_Data)->Fill(nbottomjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ht_Data)->Fill(ht,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mht_Data)->Fill(mht,thisweight*metEff);
          (myBasicCheckHistgram.h_b_njets30_Data)->Fill(njets30,thisweight*metEff);
          (myBasicCheckHistgram.h_b_njets50_Data)->Fill(njets50,thisweight*metEff);
        }
        else
        {
          Int_t ih = -1;

          if( ((*iter_QCDSampleInfos).QCDTag).find("TTJets") != std::string::npos ) ih = 0;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("ST_tW") != std::string::npos ) ih = 1;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("WJetsToLNu_HT") != std::string::npos ) ih = 2;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("ZJetsToNuNu_HT") != std::string::npos ) ih = 3;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("QCD_HT") != std::string::npos ) ih = 4;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("TTZTo") != std::string::npos ) ih = 5;
          else std::cout << "Invalid tag! what the fuck is going on ?!" << std::endl;

          (myBasicCheckHistgram.h_b_met_MC[ih])->Fill(met,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mt2_MC[ih])->Fill(MT2,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ntopjets_MC[ih])->Fill(ntopjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_nbjets_MC[ih])->Fill(nbottomjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ht_MC[ih])->Fill(ht,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mht_MC[ih])->Fill(mht,thisweight*metEff);
          (myBasicCheckHistgram.h_b_njets30_MC)[ih]->Fill(njets30,thisweight*metEff);
          (myBasicCheckHistgram.h_b_njets50_MC)[ih]->Fill(njets50,thisweight*metEff);
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop

  (myBasicCheckHistgram.oFile)->Write();
  (myBasicCheckHistgram.oFile)->Close();
  return ;
}

void LoopQCDCombine( QCDSampleWeight& myQCDSampleWeight )
{
  CombineHistgram myCombineHistgram;
  myCombineHistgram.BookHistgram( (dir_out + "QCDCombine.root").c_str() );

  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  int i = 0;
  //use class BaselineVessel in the SusyAnaTools/Tools/baselineDef.h file
  const std::string spec = "QCD";
  myBaselineVessel = new BaselineVessel(spec);

  std::cout << "Combination: QCD Prediction plots and TTJets Inc cutflow" << std::endl;
  
  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);
    //initialize the type3Ptr defined in the customize.h
    AnaFunctions::prepareTopTagger();
    //The passBaseline is registered here
    tr.registerFunction(&mypassBaselineFunc);

    double thisweight = (*iter_QCDSampleInfos).weight;
    //negative weight for other MC samples
    if( !( ( (*iter_QCDSampleInfos).QCDTag ).find("QCD") != std::string::npos) ) thisweight = -thisweight;
    if( ( (*iter_QCDSampleInfos).QCDTag ).find("HTMHT") != std::string::npos ) thisweight = 1 * Scale;

    std::cout <<"Sample Type: "<< (*iter_QCDSampleInfos).QCDTag << "; Weight: " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      int nbottomjets = tr.getVar<int>("cntCSVS"+spec);
      double MT2 = tr.getVar<double>("best_had_brJet_MT2"+spec);
      double met = tr.getVar<double>("met");
      //closure plots variables
      int njets30 = tr.getVar<int>("cntNJetsPt30Eta24"+spec);
      int njets50 = tr.getVar<int>("cntNJetsPt50Eta24"+spec);
      double ht = tr.getVar<double>("HT"+spec);

      //if( met < 175 ) continue;
      int metbin_number = Set_metbin_number(met);
      int mt2bin_number = Set_mt2bin_number(MT2);

      bool passdPhis = tr.getVar<bool>("passdPhis"+spec);
      bool passBaselineQCD = tr.getVar<bool>("passBaseline"+spec);
      bool passBaseline_dPhisInverted = false;

      passBaseline_dPhisInverted = passBaselineQCD && (!passdPhis);
      //apply trigger efficiencies
      double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      /*
      //top tagger study for zhenbin
      if(
         tr->getVar<bool>("passNoiseEventFilter") &&
         tr->getVar<bool>("passnJets") &&
         tr->getVar<bool>("passMuonVeto") &&
         tr->getVar<bool>("passEleVeto") &&
         tr->getVar<bool>("passIsoTrkVeto") &&
         !(tr->getVar<bool>("passdPhis")) &&
         tr->getVar<bool>("passBJets") &&
         tr->getVar<bool>("passMET") &&
         tr->getVar<bool>("passHT") &&
        )
      {
        double predweight = thisweight * metEff * QCDTFactor[metbin_number][mt2bin_number];

      }
      */
      if (passBaseline_dPhisInverted)
      {
        if( met < 200 ) continue;

        if( (*iter_QCDSampleInfos).QCDTag == "HTMHT" )
        {
          std::vector<std::string> TriggerNames = tr.getVec<std::string>("TriggerNames");
          std::vector<int> PassTrigger = tr.getVec<int>("PassTrigger");
          bool foundTrigger = false;

          for(unsigned it=0; it<TriggerNames.size(); it++)
          {
            if
            (   TriggerNames[it].find("HLT_PFHT350_PFMET100_JetIdCleaned_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFHT350_PFMET100_NoiseCleaned_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFHT350_PFMET100_v") != std::string::npos
            )
            {
              if( PassTrigger[it] ) foundTrigger = true;
            }
          }

          if( !foundTrigger ) continue;
        }

        double predweight = thisweight * metEff * head_QCDTFactorScaled[metbin_number][mt2bin_number];
        //double predweight_err = thisweight * metEff * QCDTFactor_err[metbin_number][mt2bin_number];
        (myCombineHistgram.h_zb_met)->Fill(met,predweight);
        (myCombineHistgram.h_zb_njets30)->Fill(njets30,predweight);
        (myCombineHistgram.h_zb_njets50)->Fill(njets50,predweight);
        (myCombineHistgram.h_zb_mt2)->Fill(MT2,predweight);
        (myCombineHistgram.h_zb_ht)->Fill(ht,predweight);
        (myCombineHistgram.h_zb_ntopjets)->Fill(ntopjets,predweight);
        (myCombineHistgram.h_zb_nbjets)->Fill(nbottomjets,predweight);

        int searchbin_id = find_Binning_Index( nbottomjets , ntopjets , MT2, met );
        if( searchbin_id >= 0 )
        {
          //std::cout << predweight << std::endl;
          (myCombineHistgram.h_zb_sb)->Fill(searchbin_id,predweight);
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop

  (myCombineHistgram.oFile)->Write();
  (myCombineHistgram.oFile)->Close();
  return ;
}

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cerr <<"Please give at least 3 arguments " << "RunMode " << " " << "runListMC " << " " << "runListData"<< std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./QCD RunMode runlist_QCDMC.txt runlist_Data.txt" << std::endl;
    return -1;
  }

  std::string RunMode = argv[1];
  std::string inputFileList_QCDMC = argv[2];
  std::string inputFileList_Data = argv[3];
  
  std::cout << "The valid run modes are: CalOnly, ExpMCOnly, PredMCOnly, PredDataOnly, ExpMCPredMC, ExpMCPredData, BasicCheckQCD, BasicCheckLL QCDCombine TFactorsUnc" << std::endl;
  std::cout << "The run mode we have right now is: " << RunMode << std::endl;
  //define my QCDFactors class to stroe counts and Translation factors
  QCDFactors myQCDFactors;

  //Sample needed in the calculation and expectation loop
  QCDSampleWeight myQCDSampleWeight;
  myQCDSampleWeight.QCDSampleInfo_push_back( "QCD_HT500to700_"  , 29370   , 19664159, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "QCD_HT700to1000_" , 6524    , 15356448, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "QCD_HT1000to1500_", 1064    ,  4963895, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "QCD_HT1500to2000_", 121.5   ,  3868886, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "QCD_HT2000toInf_" , 25.42   ,  1683349, LUMI, 1, inputFileList_QCDMC.c_str() );
  if( myQCDSampleWeight.QCDSampleInfos.size() != QCD_BINS)
  {
    std::cout << "QCD_BINS in QCDBinFunction.h and the entries of QCD samples in QCDReWeighting.h are not equal! Please check on that!" << std::endl; 
    return 0;
  }
  //sample needed in the prediction loop
  QCDSampleWeight myDataSampleWeight;
  myDataSampleWeight.QCDSampleInfo_push_back( "HTMHT"                   ,      1,             1, LUMI, 1, inputFileList_Data.c_str() );
  //myDataSampleWeight.QCDSampleInfo_push_back( "TTJets_"                 , 831.76,      11339232, LUMI, 1, inputFileList_Data.c_str() );
  //myDataSampleWeight.QCDSampleInfo_push_back( "ST_tW_top"               ,   35.6,        995600, LUMI, 1, inputFileList_Data.c_str() );
  //myDataSampleWeight.QCDSampleInfo_push_back( "ST_tW_antitop"           ,   35.6,        988500, LUMI, 1, inputFileList_Data.c_str() );
  //be careful!! WJets and ZJets samples have some tricky part, need to understand!
  //myDataSampleWeight.QCDSampleInfo_push_back( "WJetsToLNu_HT-400To600_" ,  48.91,       1745914, LUMI, 1.21, inputFileList_Data.c_str() );
  //myDataSampleWeight.QCDSampleInfo_push_back( "WJetsToLNu_HT-600ToInf_" ,  18.77,       1039152, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "ZJetsToNuNu_HT-400To600_",  10.73,       1018882, LUMI, 1.23, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "ZJetsToNuNu_HT-600ToInf_",  4.116,       1008333, LUMI, 1.23, inputFileList_Data.c_str() );
  //be careful! TTZ has negative weight issue!!
  myDataSampleWeight.QCDSampleInfo_push_back( "TTZToLLNuNu_"            , 0.2529, 291495-106505, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "TTZToQQ_"                , 0.5297, 550599-199201, LUMI, 1, inputFileList_Data.c_str() );

  //sample needed in the basic check loop
  QCDSampleWeight myBasicCheckSampleWeight;
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "HTMHT"                   ,      1,             1, LUMI, 1, inputFileList_Data.c_str() );
  //myBasicCheckSampleWeight.QCDSampleInfo_push_back( "SingleMuon"              ,      1,             1, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "TTJets_"                 , 831.76,      11339232, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "ST_tW_top"               ,   35.6,        995600, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "ST_tW_antitop"           ,   35.6,        988500, LUMI, 1, inputFileList_Data.c_str() );
  //be careful!! WJets and ZJets samples have some tricky part, need to understand!
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "WJetsToLNu_HT-400To600_" ,  48.91,       1745914, LUMI, 1.21, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "WJetsToLNu_HT-600ToInf_" ,  18.77,       1039152, LUMI, 1.21, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "ZJetsToNuNu_HT-400To600_",  10.73,       1018882, LUMI, 1.23, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "ZJetsToNuNu_HT-600ToInf_",  4.116,       1008333, LUMI, 1.23, inputFileList_Data.c_str() );
  //be careful! TTZ has negative weight issue!!
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "TTZToLLNuNu_"            , 0.2529, 291495-106505, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "TTZToQQ_"                , 0.5297, 550599-199201, LUMI, 1, inputFileList_Data.c_str() );  

  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "QCD_HT500to700_"  , 29370   , 19664159, LUMI, 1, inputFileList_QCDMC.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "QCD_HT700to1000_" , 6524    , 15356448, LUMI, 1, inputFileList_QCDMC.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "QCD_HT1000to1500_", 1064    ,  4963895, LUMI, 1, inputFileList_QCDMC.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "QCD_HT1500to2000_", 121.5   ,  3868886, LUMI, 1, inputFileList_QCDMC.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "QCD_HT2000toInf_" , 25.42   ,  1683349, LUMI, 1, inputFileList_QCDMC.c_str() );


  if( RunMode == "CalOnly" )
  {
    LoopQCDCal( myQCDFactors, myQCDSampleWeight );
    return 0;
  }
  else if( RunMode == "ExpMCOnly" )
  {
    LoopQCDExp( myQCDFactors, myQCDSampleWeight );
    return 0;
  }
  else if( RunMode == "PredMCOnly" )
  {
    LoopQCDPred( myQCDFactors, myQCDSampleWeight, RunMode );
    return 0;
  }
  else if( RunMode == "PredDataOnly" )
  {
    LoopQCDPred( myQCDFactors, myDataSampleWeight, RunMode );
    return 0;
  }
  else if( RunMode == "ExpMCPredMC" )
  {
    LoopQCDExp ( myQCDFactors, myQCDSampleWeight );
    LoopQCDPred( myQCDFactors, myQCDSampleWeight, RunMode );
    myQCDFactors.printSBInfo();
    return 0;
  }
  else if( RunMode == "ExpMCPredData" )
  {
    LoopQCDExp ( myQCDFactors, myQCDSampleWeight );
    LoopQCDPred( myQCDFactors, myDataSampleWeight, RunMode );
    myQCDFactors.printSBInfo();
    return 0;
  }
  else if( RunMode == "BasicCheckQCD" )
  {
    LoopBasicCheckQCD( myBasicCheckSampleWeight );
    return 0;
  }
  else if( RunMode == "BasicCheckLL" )
  {
    LoopBasicCheckLL( myBasicCheckSampleWeight );
    return 0;
  }
  else if( RunMode == "QCDCombine" )
  {
    LoopQCDCombine( myDataSampleWeight );
  }
  else if( RunMode == "TFactorsUnc" )
  {
    LoopQCDTFactorsUnc( myDataSampleWeight, RunMode );
    return 0;
  }
  else
  {
    std::cout << "Invalide RunMode!!" << std::endl;
    return 0;
  }

  return 0;
}
