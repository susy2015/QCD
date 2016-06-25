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
SearchBins mySearchBins("SB_59_2016");

void LoopQCDCal( QCDFactors& myQCDFactors, QCDSampleWeight& myQCDSampleWeight )
{
  CalHistgram myCalHistgram;
  myCalHistgram.BookHistgram( (dir_out + "CalQCD.root").c_str() );
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  int i = 0;

  std::cout << "Calculation: " << std::endl;

  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {  
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);
 
    double thisweight = (*iter_QCDSampleInfos).weight;
    myQCDFactors.QCDWeights[i] = thisweight;
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

      //checking plots for full QCD samples
      //filling HT variables for quick weight check
      //(myClosureHistgram.h_b_all_HT)->Fill(ht,thisweight);

      int metbin_number = Set_metbin_number(met);
      int mt2bin_number = Set_mt2bin_number(mt2);
      int njetsbin_number = Set_njetsbin_number(njets30);

      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");

      double calomet = tr.getVar<double>("calomet");
      bool passPFCaloMETRatio = (met/calomet<3);
      //normal baseline without dPhis cut
      bool passBaselineQCD = passTagger
                          && passPFCaloMETRatio
                          && passBJets
                          && passQCDHighMETFilter;
 
      //apply the met efficiencies
      //double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      double metEff = 1;
      if (
          passBaselineQCD
         )
      {
        if( met > 1000 )
        { 
          std::cout << "bad QCD event with crazy MET!! " << (*iter_QCDSampleInfos).QCDTag << "; MET: " << met << " MT2: " << mt2 << " NB: " << nbotjets << " NT: " << ntopjets << std::endl;
          std::cout << "HT: " << ht << " MHT: " << mht << std::endl;
        }
        if( met < 175 ) std::cout << "what the fuck is going on!!" << std::endl;
        
        if ( passdPhis )
        {
          //if( njetsbin_number == 0)
          //{
            myQCDFactors.nQCDNormal_MC[i][metbin_number][mt2bin_number]++;
            myQCDFactors.nQCDNormal[i][metbin_number][mt2bin_number]+=(thisweight*metEff);
          //}
          myQCDFactors.nQCDNormal_NJF_MC_all[njetsbin_number]++;
        }

        if ( !passdPhis )
        {
          //if( njetsbin_number == 0)
          //{
            myQCDFactors.nQCDInverted_MC[i][metbin_number][mt2bin_number]++;
            myQCDFactors.nQCDInverted[i][metbin_number][mt2bin_number]+=(thisweight*metEff);
            myQCDFactors.MET_sum[i][metbin_number][mt2bin_number] = myQCDFactors.MET_sum[i][metbin_number][mt2bin_number] + met * thisweight * metEff;
            myQCDFactors.MET_sum_weight[i][metbin_number][mt2bin_number] = myQCDFactors.MET_sum_weight[i][metbin_number][mt2bin_number] + thisweight * metEff;

            //(myCalHistgram.h_cal_met_MC[metbin_number][mt2bin_number])->Fill(met,thisweight*metEff);

            int searchbin_id = mySearchBins.find_Binning_Index( nbotjets , ntopjets , mt2, met );
            if( searchbin_id >= 0)
            {
              myQCDFactors.MET_sum_all_exp_sb[searchbin_id] = myQCDFactors.MET_sum_all_exp_sb[searchbin_id] + met * thisweight * metEff;
              myQCDFactors.MET_sum_weight_all_exp_sb[searchbin_id] = myQCDFactors.MET_sum_weight_all_exp_sb[searchbin_id] + thisweight * metEff;
              myQCDFactors.MT2_sum_all_exp_sb[searchbin_id] = myQCDFactors.MT2_sum_all_exp_sb[searchbin_id] + mt2 * thisweight * metEff;
              myQCDFactors.MT2_sum_weight_all_exp_sb[searchbin_id] = myQCDFactors.MT2_sum_weight_all_exp_sb[searchbin_id] + thisweight * metEff;
            }
          //}
          myQCDFactors.nQCDInverted_NJF_MC_all[njetsbin_number]++;
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

  (myCalHistgram.oFile)->Write();
  (myCalHistgram.oFile)->Close();
  return ;
}

void LoopQCDExpMC( QCDFactors& myQCDFactors, QCDSampleWeight& myQCDSampleWeight )
{
  ClosureHistgram myClosureHistgram;
  myClosureHistgram.BookHistgram( (dir_out + "ExpQCD.root").c_str() );

  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  int i = 0;

  std::cout << "Expectation(QCD_HT MC): " << std::endl;

  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {  
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);
 
    double thisweight = (*iter_QCDSampleInfos).weight;
    myQCDFactors.QCDWeights[i] = thisweight;
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

      //checking plots for full QCD samples
      //filling HT variables for quick weight check
      //(myClosureHistgram.h_b_all_HT)->Fill(ht,thisweight);

      int metbin_number = Set_metbin_number(met);
      int mt2bin_number = Set_mt2bin_number(mt2);
      int njetsbin_number = Set_njetsbin_number(njets30);

      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");

      double calomet = tr.getVar<double>("calomet");
      bool passPFCaloMETRatio = (met/calomet<3);

      bool passBaselineQCD = passTagger
                          && passBJets
                          && passPFCaloMETRatio
                          && passQCDHighMETFilter
                          && passdPhis;

      //apply the met efficiencies
      //double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      double metEff = 1;
      if (
          passBaselineQCD
         )
      {
        (myClosureHistgram.h_exp_met)->Fill(met,thisweight*metEff);
        (myClosureHistgram.h_exp_njets30)->Fill(njets30,thisweight*metEff);
        (myClosureHistgram.h_exp_njets50)->Fill(njets50,thisweight*metEff);
        (myClosureHistgram.h_exp_mt2)->Fill(mt2,thisweight*metEff);
        (myClosureHistgram.h_exp_ht)->Fill(ht,thisweight*metEff);
        (myClosureHistgram.h_exp_mht)->Fill(mht,thisweight*metEff);
        (myClosureHistgram.h_exp_ntopjets)->Fill(ntopjets,thisweight*metEff);
        (myClosureHistgram.h_exp_nbjets)->Fill(nbotjets,thisweight*metEff);
          
        int searchbin_id = mySearchBins.find_Binning_Index( nbotjets , ntopjets , mt2, met );
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

void LoopQCDPredMC( QCDFactors& myQCDFactors, QCDSampleWeight& myQCDSampleWeight )
{
  double QCDTFactorPred[MET_BINS][MT2_BINS] = {{0}}, QCDTFactorPred_err[MET_BINS][MT2_BINS] = {{0}};
  double QCDTNJFPred[NJETS_BINS] = {0}, QCDTNJFPred_err[NJETS_BINS] = {0};
  ClosureHistgram myClosureHistgram;
  //use Post fit tfactor for MC non closure
  myClosureHistgram.BookHistgram( (dir_out + "PredQCDMC.root").c_str() ); 
  for(int i=0;i<MET_BINS;i++)
  {
    for(int j=0;j<MT2_BINS;j++)
    {
      QCDTFactorPred[i][j] = head_QCDTFactor[i][j];
      QCDTFactorPred_err[i][j] = head_QCDTFactor_err[i][j];
    }
  }

  for(int i=0;i<MET_BINS;i++)
  {
    //QCDTNJFPred[i] = head_QCDTNJF[i];
    //QCDTNJFPred_err[i] = head_QCDTNJF_err[i];
    QCDTNJFPred[i] = 1;
    QCDTNJFPred_err[i] = 0;
  }

  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  int i = 0;

  std::cout << "Prediction(QCD_HT MC): " << std::endl;
  
  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);

    double thisweight = (*iter_QCDSampleInfos).weight;
    //negative weight for other MC samples
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

      //checking plots for full QCD samples
      //filling HT variables for quick weight check
      //(myClosureHistgram.h_b_all_HT)->Fill(ht,thisweight);

      int metbin_number = Set_metbin_number(met);
      int mt2bin_number = Set_mt2bin_number(mt2);
      int njetsbin_number = Set_njetsbin_number(njets30);

      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");
      double calomet = tr.getVar<double>("calomet");
      bool passPFCaloMETRatio = (met/calomet<3);

      bool passBaselineQCD = passTagger
                          && passBJets
                          && passPFCaloMETRatio
                          && passQCDHighMETFilter
                          && (!passdPhis);

      //apply trigger efficiencies
      //double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      double metEff = 1;
      if ( passBaselineQCD )
      {
        double predweight = thisweight * metEff * QCDTFactorPred[metbin_number][mt2bin_number] * QCDTNJFPred[njetsbin_number];
        (myClosureHistgram.h_pred_met)->Fill(met,predweight);
        (myClosureHistgram.h_pred_njets30)->Fill(njets30,predweight);
        (myClosureHistgram.h_pred_njets50)->Fill(njets50,predweight);
        (myClosureHistgram.h_pred_mt2)->Fill(mt2,predweight);
        (myClosureHistgram.h_pred_ht)->Fill(ht,predweight);
        (myClosureHistgram.h_pred_mht)->Fill(mht,predweight);
        (myClosureHistgram.h_pred_ntopjets)->Fill(ntopjets,predweight);
        (myClosureHistgram.h_pred_nbjets)->Fill(nbotjets,predweight);

        //if( ht < 500) std::cout << ht << " small ht, what the fuck!!" << std::endl;

        int searchbin_id = mySearchBins.find_Binning_Index( nbotjets , ntopjets , mt2, met );
        if( searchbin_id >= 0 )
        {
          myQCDFactors.nQCD_pred_sb[searchbin_id] += (predweight);
          myQCDFactors.nQCD_pred_sb_err[searchbin_id] += (predweight * predweight);
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop

  for( int i=0 ; i<NSEARCH_BINS ; i++ )
  {
    myQCDFactors.nQCD_pred_sb_err[i] = std::sqrt( myQCDFactors.nQCD_pred_sb_err[i] );
  }

  myQCDFactors.printQCDClosurePred(myClosureHistgram);
  (myClosureHistgram.oFile)->Write();
  (myClosureHistgram.oFile)->Close();
  return ;
}

void LoopQCDPredData( QCDFactors& myQCDFactors, QCDSampleWeight& myQCDSampleWeight )
{
  double QCDTFactorPred[MET_BINS][MT2_BINS] = {{0}}, QCDTFactorPred_err[MET_BINS][MT2_BINS] = {{0}};
  double QCDTNJFPred[NJETS_BINS] = {0}, QCDTNJFPred_err[NJETS_BINS] = {0};
  ClosureHistgram myClosureHistgram;
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

  for(int i=0;i<MET_BINS;i++)
  {
    //QCDTNJFPred[i] = head_QCDTNJF[i];
    //QCDTNJFPred_err[i] = head_QCDTNJF_err[i];
    QCDTNJFPred[i] = 1;
    QCDTNJFPred_err[i] = 0;
  }

  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  int i = 0;

  std::cout << "Prediction(HTMHT): " << std::endl;
  
  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);

    double thisweight = (*iter_QCDSampleInfos).weight;
    //negative weight for other MC samples
    if( ( (*iter_QCDSampleInfos).QCDTag ).find("HTMHT") != std::string::npos ) thisweight = 1 * Scale;
    else thisweight = -thisweight;
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
      //double mht = tr.getVar<double>("mht");

      //checking plots for full QCD samples
      //filling HT variables for quick weight check
      //(myClosureHistgram.h_b_all_HT)->Fill(ht,thisweight);

      int metbin_number = Set_metbin_number(met);
      int mt2bin_number = Set_mt2bin_number(mt2);
      int njetsbin_number = Set_njetsbin_number(njets30);

      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      //bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");

      //normal baseline without dPhis cut, and without passQCDHighMETFilter
      bool passBaselineQCD = false;
      passBaselineQCD = passTagger
                     && passBJets;
                     //&& passQCDHighMETFilter

      //apply trigger efficiencies
      //double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      double metEff = 1;
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
            ( TriggerNames[it].find("HLT_PFHT300_PFMET100_v") != std::string::npos )
            {
              if( PassTrigger[it] ) foundTrigger = true;
            }
          }

          if( !foundTrigger ) continue;
        }

        if( (!passdPhis) )
        {
          //if( ht < 500) std::cout << ht << " small ht, what the fuck!!" << std::endl;
          int searchbin_id = mySearchBins.find_Binning_Index( nbotjets , ntopjets , mt2, met );
          if( searchbin_id >= 0 )
          {
            if( (*iter_QCDSampleInfos).QCDTag == "HTMHT" )
            { 
              myQCDFactors.MET_sb_sum[searchbin_id] = myQCDFactors.MET_sb_sum[searchbin_id] + met * thisweight * metEff;
              myQCDFactors.MET_sb_sum_weight[searchbin_id] = myQCDFactors.MET_sb_sum_weight[searchbin_id] + thisweight * metEff;
              myQCDFactors.MT2_sb_sum[searchbin_id] = myQCDFactors.MT2_sb_sum[searchbin_id] + mt2 * thisweight * metEff;
              myQCDFactors.MT2_sb_sum_weight[searchbin_id] = myQCDFactors.MT2_sb_sum_weight[searchbin_id] + thisweight * metEff;

              myQCDFactors.DC_sb_Data[searchbin_id] += thisweight * metEff;
              myQCDFactors.DC_sb_Data_err[searchbin_id] += thisweight * metEff * thisweight * metEff; 
            }
            if(   ((*iter_QCDSampleInfos).QCDTag).find("TTJets") != std::string::npos
               || ((*iter_QCDSampleInfos).QCDTag).find("ST_tW") != std::string::npos
               || ((*iter_QCDSampleInfos).QCDTag).find("WJetsToLNu_HT") != std::string::npos
              )
            {
              bool isLL = tr.getVar<bool>("isLL");
              if(isLL)
              {
                myQCDFactors.DC_sb_lostleptMC[searchbin_id] += std::abs(thisweight * metEff);
              }
              else
              {
                myQCDFactors.DC_sb_hadtauMC[searchbin_id] += std::abs(thisweight * metEff); 
              }
            }
            else if( ((*iter_QCDSampleInfos).QCDTag).find("ZJetsToNuNu_HT") != std::string::npos )
            {
              myQCDFactors.DC_sb_zinvMC[searchbin_id] += std::abs(thisweight * metEff);
            }
            else if(
                       ((*iter_QCDSampleInfos).QCDTag).find("TTZTo") != std::string::npos
                    || ((*iter_QCDSampleInfos).QCDTag).find("TTWJets") != std::string::npos
                   )
            {
              bool isGenZLep = tr.getVar<bool>("isGenZLep");
              bool isGenWLep = tr.getVar<bool>("isGenWLep");
              if( isGenZLep || isGenWLep ) continue;

              bool isNegativeWeight = tr.getVar<bool>("isNegativeWeight");
              if( isNegativeWeight ) thisweight = -thisweight;
              isNegativeWeight ? myQCDFactors.DC_sb_ttzMC[searchbin_id] -= std::abs(thisweight * metEff) : myQCDFactors.DC_sb_ttzMC[searchbin_id] += std::abs(thisweight * metEff);
            }
          }

          double predweight = thisweight * metEff * QCDTFactorPred[metbin_number][mt2bin_number] * QCDTNJFPred[njetsbin_number];

          (myClosureHistgram.h_pred_met)->Fill(met,predweight);
          (myClosureHistgram.h_pred_njets30)->Fill(njets30,predweight);
          (myClosureHistgram.h_pred_njets50)->Fill(njets50,predweight);
          (myClosureHistgram.h_pred_mt2)->Fill(mt2,predweight);
          (myClosureHistgram.h_pred_ht)->Fill(ht,predweight);
          //(myClosureHistgram.h_pred_mht)->Fill(mht,predweight);
          (myClosureHistgram.h_pred_ntopjets)->Fill(ntopjets,predweight);
          (myClosureHistgram.h_pred_nbjets)->Fill(nbotjets,predweight);
        }

        //Get normalized Tfactor in Inverted dPhi region in Real Data
        //metbin side band
        if( metbin_number == 0 )
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
      }//event loop
    }//end of inner loop
  }//end of QCD Samples loop

  //print data card for limit setting
  //Data driven yield from other bg
  for( int i=0 ; i<NSEARCH_BINS ; i++ )
  {
    // determine the mt2 met id from mt2 met mean value
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
    
    //set stat unc from DC central value
    myQCDFactors.DC_sb_Data_err[i] = std::sqrt(myQCDFactors.DC_sb_Data_err[i]);
    myQCDFactors.DC_sb_zinvMC_err[i] = std::sqrt(myQCDFactors.DC_sb_zinvMC_err[i]);
    myQCDFactors.DC_sb_ttzMC_err[i] = std::sqrt(myQCDFactors.DC_sb_ttzMC_err[i]);
  
    /*
    //set up data card from data driven input
    //myQCDFactors.DC_sb_hadtau[i] = pred_sb_hadtau[i];
    //myQCDFactors.DC_sb_lostlept[i] = pred_sb_lostlept[i];
    //myQCDFactors.DC_sb_hadtau_errup[i] = std::sqrt( pred_sb_hadtau_stat[i]*pred_sb_hadtau_stat[i] + pred_sb_hadtau_sysUp[i]*pred_sb_hadtau_sysUp[i] );
    //myQCDFactors.DC_sb_hadtau_errdown[i] = std::sqrt( pred_sb_hadtau_stat[i]*pred_sb_hadtau_stat[i] + pred_sb_hadtau_sysDown[i]*pred_sb_hadtau_sysDown[i] );
    //myQCDFactors.DC_sb_lostlept_errup[i] = std::sqrt( pred_sb_lostlept_stat[i]*pred_sb_lostlept_stat[i] + pred_sb_lostlept_sysUp[i]*pred_sb_lostlept_sysUp[i] );
    //myQCDFactors.DC_sb_lostlept_errdown[i] = std::sqrt( pred_sb_lostlept_stat[i]*pred_sb_lostlept_stat[i] + pred_sb_lostlept_sysDown[i]*pred_sb_lostlept_sysDown[i] );

    //deal with had tau, data driven
    myQCDFactors.nQCD_pred_sb[i] -= pred_sb_hadtau[i] * QCDTFactorPred[met_id][mt2_id];
    //myQCDFactors.nQCD_pred_sb_err[i] += pred_sb_hadtau_stat[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];
    myQCDFactors.nQCD_pred_sb_sysuncup[i] += pred_sb_hadtau_stat[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];
    myQCDFactors.nQCD_pred_sb_sysuncdown[i] += pred_sb_hadtau_stat[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];
    myQCDFactors.nQCD_pred_sb_sysuncup[i] += pred_sb_hadtau_sysUp[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];
    myQCDFactors.nQCD_pred_sb_sysuncdown[i] += pred_sb_hadtau_sysDown[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];

    //deal with ll, data driven
    myQCDFactors.nQCD_pred_sb[i] -= pred_sb_lostlept[i] * QCDTFactorPred[met_id][mt2_id];
    //myQCDFactors.nQCD_pred_sb_err[i] += pred_sb_lostlept_stat[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];
    myQCDFactors.nQCD_pred_sb_sysuncup[i] += pred_sb_lostlept_stat[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];
    myQCDFactors.nQCD_pred_sb_sysuncdown[i] += pred_sb_lostlept_stat[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];
    myQCDFactors.nQCD_pred_sb_sysuncup[i] += pred_sb_lostlept_sysUp[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];
    myQCDFactors.nQCD_pred_sb_sysuncdown[i] += pred_sb_lostlept_sysDown[i] * QCDTFactorPred[met_id][mt2_id] * QCDTFactorPred[met_id][mt2_id];
    */

    //deal with zinv
    myQCDFactors.nQCD_pred_sb_sysuncup[i] += myQCDFactors.DC_sb_zinvMC_err[i] * myQCDFactors.DC_sb_zinvMC_err[i];
    myQCDFactors.nQCD_pred_sb_sysuncdown[i] += myQCDFactors.DC_sb_zinvMC_err[i] * myQCDFactors.DC_sb_zinvMC_err[i];
    //deal with ttz
    myQCDFactors.nQCD_pred_sb_sysuncup[i] += myQCDFactors.DC_sb_ttzMC_err[i] * myQCDFactors.DC_sb_ttzMC_err[i];
    myQCDFactors.nQCD_pred_sb_sysuncdown[i] += myQCDFactors.DC_sb_ttzMC_err[i] * myQCDFactors.DC_sb_ttzMC_err[i];
  }

  for( int i=0 ; i<NSEARCH_BINS ; i++ )
  {
    myQCDFactors.nQCD_pred_sb_sysuncup[i] = std::sqrt( myQCDFactors.nQCD_pred_sb_sysuncup[i] );
    myQCDFactors.nQCD_pred_sb_sysuncdown[i] = std::sqrt( myQCDFactors.nQCD_pred_sb_sysuncdown[i] );
  }
  /*
  for( int i=0 ; i<MT2_BINS ; i++ )
  {
    myQCDFactors.nQCDNormalData_all[i] -= TQCD_hadtau[i];
    myQCDFactors.nQCDNormalData_all_err[i] += (TQCD_hadtau_stat[i]*TQCD_hadtau_stat[i]);
    myQCDFactors.nQCDInvertedData_all[i] -= TQCD_hadtauInv[i];
    myQCDFactors.nQCDInvertedData_all_err[i] += (TQCD_hadtauInv_stat[i]*TQCD_hadtauInv_stat[i]);

    myQCDFactors.nQCDNormalData_all[i] -= TQCD_lostlept[i];
    myQCDFactors.nQCDNormalData_all_err[i] += (TQCD_lostlept_stat[i]*TQCD_lostlept_stat[i]);
    myQCDFactors.nQCDInvertedData_all[i] -= TQCD_lostleptInv[i];
    myQCDFactors.nQCDInvertedData_all_err[i] += (TQCD_lostleptInv_stat[i]*TQCD_lostleptInv_stat[i]);
  }
  */
  //deal with the Tfactor from data.need to uncomment when you want to get low met side band tfactor from real data
  //myQCDFactors.getAndprintTFactorsfromDataHeader(); 
  myQCDFactors.printSysHeader();
  myQCDFactors.printDataCard();

  myQCDFactors.printQCDClosurePred(myClosureHistgram);
  (myClosureHistgram.oFile)->Write();
  (myClosureHistgram.oFile)->Close();
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

    double thisweight = (*iter_QCDSampleInfos).weight;
    if( ( (*iter_QCDSampleInfos).QCDTag ).find("HTMHT") != std::string::npos ) thisweight = 1 * Scale;
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
      //double mht = tr.getVar<double>("mht");

      //checking plots for full QCD samples
      //filling HT variables for quick weight check
      //(myClosureHistgram.h_b_all_HT)->Fill(ht,thisweight);

      int metbin_number = Set_metbin_number(met);
      int mt2bin_number = Set_mt2bin_number(mt2);
      int njetsbin_number = Set_njetsbin_number(njets30);

      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      //bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");

      //normal baseline without dPhis cut, and without passQCDHighMETFilter
      bool passBaselineQCD = false;
      passBaselineQCD = passTagger
                     && passBJets
                     && passQCDHighMETFilter;
                     //&& passNoiseEventFilter;

      bool passBaseline_dPhisInverted = false;
      passBaseline_dPhisInverted = passBaselineQCD && (!passdPhis);
      //apply trigger efficiencies
      //double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      double metEff = 1;

      if (passBaseline_dPhisInverted)
      {
        int searchbin_id = mySearchBins.find_Binning_Index( nbotjets , ntopjets , mt2, met );

        if( (*iter_QCDSampleInfos).QCDTag == "HTMHT" )
        {
          std::vector<std::string> TriggerNames = tr.getVec<std::string>("TriggerNames");
          std::vector<int> PassTrigger = tr.getVec<int>("PassTrigger");
          bool foundTrigger = false;

          for(unsigned it=0; it<TriggerNames.size(); it++)
          {
            if
            ( 
             TriggerNames[it].find("HLT_PFHT300_PFMET100_v") != std::string::npos
            )

            {
              if( PassTrigger[it] ) foundTrigger = true;
            }
          }

          if( !foundTrigger ) continue;

          (myBasicCheckHistgram.h_b_met_Data)->Fill(met,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mt2_Data)->Fill(mt2,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ntopjets_Data)->Fill(ntopjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_nbjets_Data)->Fill(nbotjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ht_Data)->Fill(ht,thisweight*metEff);
          //(myBasicCheckHistgram.h_b_mht_Data)->Fill(mht,thisweight*metEff);
          (myBasicCheckHistgram.h_b_njets30_Data)->Fill(njets30,thisweight*metEff);
          (myBasicCheckHistgram.h_b_njets50_Data)->Fill(njets50,thisweight*metEff);

          (myBasicCheckHistgram.h_b_sb_Data)->Fill(searchbin_id,thisweight*metEff);
        }
        else
        {
          Int_t ih = -1;

          if(   ((*iter_QCDSampleInfos).QCDTag).find("TTJets") != std::string::npos
             || ((*iter_QCDSampleInfos).QCDTag).find("ST_tW") != std::string::npos
             || ((*iter_QCDSampleInfos).QCDTag).find("WJetsToLNu_HT") != std::string::npos 
            ) 
          { 
            bool isLL = tr.getVar<bool>("isLL");
            isLL ? ih = 0 : ih = 1;
          }
          else if( ((*iter_QCDSampleInfos).QCDTag).find("ZJetsToNuNu_HT") != std::string::npos ) ih = 2;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("QCD_HT") != std::string::npos )
          {
            double calomet = tr.getVar<double>("calomet");
            bool passPFCaloMETRatio = (met/calomet<3); 
            if( !passPFCaloMETRatio ) continue;
            ih = 3;
          }
          else if( 
                     ((*iter_QCDSampleInfos).QCDTag).find("TTZTo") != std::string::npos 
                  || ((*iter_QCDSampleInfos).QCDTag).find("TTWJets") != std::string::npos 
                 ) 
          { 
            ih = 4;
            bool isNegativeWeight = tr.getVar<bool>("isNegativeWeight");
            if( isNegativeWeight ) thisweight = -thisweight;
          }
          else std::cout << "Invalid tag! what the fuck is going on ?!" << std::endl;

          (myBasicCheckHistgram.h_b_met_MC[ih])->Fill(met,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mt2_MC[ih])->Fill(mt2,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ntopjets_MC[ih])->Fill(ntopjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_nbjets_MC[ih])->Fill(nbotjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ht_MC[ih])->Fill(ht,thisweight*metEff);
          //(myBasicCheckHistgram.h_b_mht_MC[ih])->Fill(mht,thisweight*metEff);
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
      //int njetsbin_number = Set_njetsbin_number(nbotjets);
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

        int searchbin_id = mySearchBins.find_Binning_Index( nbottomjets , ntopjets , MT2, met );
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
  myQCDSampleWeight.QCDSampleInfo_push_back( "_QCD_HT500to700"  , 29370   , 62819508, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "_QCD_HT700to1000" , 6524    , 45453945, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "_QCD_HT1000to1500", 1064    , 15217446, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "_QCD_HT1500to2000", 121.5   , 11705926, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "_QCD_HT2000toInf" , 25.42   ,  6040004, LUMI, 1, inputFileList_QCDMC.c_str() );
  if( myQCDSampleWeight.QCDSampleInfos.size() != QCD_BINS)
  {
    std::cout << "QCD_BINS in QCDBinFunction.h and the entries of QCD samples in QCDReWeighting.h are not equal! Please check on that!" << std::endl; 
    return 0;
  }

  double TTbar_SingleLept_BR = 0.43930872; // 2*W_Lept_BR*(1-W_Lept_BR)
  double TTbar_DiLept_BR = 0.10614564; // W_Lept_BR^2
  //sample needed in the prediction loop
  QCDSampleWeight myDataSampleWeight;
  myDataSampleWeight.QCDSampleInfo_push_back( "HTMHT"                      ,                              1,        1, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTJets_DiLept"             ,         831.76*TTbar_DiLept_BR, 30587326, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromTbar_", 831.76*0.5*TTbar_SingleLept_BR, 51873969, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromT_"   , 831.76*0.5*TTbar_SingleLept_BR, 59654914, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ST_tW_top"                 ,                           35.6,   998400, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ST_tW_antitop"             ,                           35.6,   967600, LUMI, 1, inputFileList_Data.c_str() );
  //be careful!! WJets and ZJets samples have some tricky part, need to understand!
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-400To600"   ,   48.91,       7299788, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-600To800"   ,   12.05,       3723054, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-800To1200"  ,   5.501,       7480017, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-1200To2500" ,   1.329,       7042924, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-2500ToInf"  , 0.03216,        252809, LUMI, 1.21, inputFileList_Data.c_str() );

  myDataSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-400To600"  ,    10.73,       9591908, LUMI, 1.23, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-600To800"  ,  0.853*3,       5650700, LUMI, 1.23, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-800To1200" ,  0.394*3,       2156175, LUMI, 1.23, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-1200To2500", 0.0974*3,        365216, LUMI, 1.23, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-2500ToInf" ,0.00230*3,        405752, LUMI, 1.23, inputFileList_Data.c_str() );
  //be careful! TTZ has negative weight issue!!
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTZToLLNuNu"            , 0.2529, 398600, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTZToQQ"                , 0.5297, 749400, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTWJetsToLNu"           , 0.2043, 252673, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTWJetsToQQ"            , 0.4062, 738148, LUMI, 1, inputFileList_Data.c_str() );


  //sample needed in the basic check loop
  QCDSampleWeight myBasicCheckSampleWeight;
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "HTMHT"                      ,                              1,        1, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTJets_DiLept"             ,         831.76*TTbar_DiLept_BR, 30587326, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromTbar_", 831.76*0.5*TTbar_SingleLept_BR, 51873969, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromT_"   , 831.76*0.5*TTbar_SingleLept_BR, 59654914, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ST_tW_top"                 ,                           35.6,   998400, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ST_tW_antitop"             ,                           35.6,   967600, LUMI, 1, inputFileList_Data.c_str() );
  //be careful!! WJets and ZJets samples have some tricky part, need to understand!
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-400To600"   ,   48.91,       7299788, LUMI, 1.21, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-600To800"   ,   12.05,       3723054, LUMI, 1.21, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-800To1200"  ,   5.501,       7480017, LUMI, 1.21, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-1200To2500" ,   1.329,       7042924, LUMI, 1.21, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-2500ToInf"  , 0.03216,        252809, LUMI, 1.21, inputFileList_Data.c_str() );

  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-400To600"  ,    10.73,       9591908, LUMI, 1.23, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-600To800"  ,  0.853*3,       5650700, LUMI, 1.23, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-800To1200" ,  0.394*3,       2156175, LUMI, 1.23, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-1200To2500", 0.0974*3,        365216, LUMI, 1.23, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-2500ToInf" ,0.00230*3,        405752, LUMI, 1.23, inputFileList_Data.c_str() );
  //be careful! TTZ has negative weight issue!!
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTZToLLNuNu"            , 0.2529, 398600, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTZToQQ"                , 0.5297, 749400, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTWJetsToLNu"           , 0.2043, 252673, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTWJetsToQQ"            , 0.4062, 738148, LUMI, 1, inputFileList_Data.c_str() );

  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_QCD_HT500to700"  , 29370   , 62819508, LUMI, 1, inputFileList_QCDMC.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_QCD_HT700to1000" , 6524    , 45453945, LUMI, 1, inputFileList_QCDMC.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_QCD_HT1000to1500", 1064    , 15217446, LUMI, 1, inputFileList_QCDMC.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_QCD_HT1500to2000", 121.5   , 11705926, LUMI, 1, inputFileList_QCDMC.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_QCD_HT2000toInf" , 25.42   ,  6040004, LUMI, 1, inputFileList_QCDMC.c_str() );


  if( RunMode == "CalOnly" )
  {
    LoopQCDCal( myQCDFactors, myQCDSampleWeight );
    return 0;
  }
  else if( RunMode == "ExpMCOnly" )
  {
    LoopQCDExpMC( myQCDFactors, myQCDSampleWeight );
    return 0;
  }
  else if( RunMode == "PredMCOnly" )
  {
    LoopQCDPredMC( myQCDFactors, myQCDSampleWeight );
    return 0;
  }
  else if( RunMode == "PredDataOnly" )
  {
    LoopQCDPredData( myQCDFactors, myDataSampleWeight );
    return 0;
  }
  else if( RunMode == "ExpMCPredMC" )
  {
    LoopQCDExpMC ( myQCDFactors, myQCDSampleWeight );
    LoopQCDPredMC( myQCDFactors, myQCDSampleWeight );
    myQCDFactors.printSBInfo();
    return 0;
  }
  else if( RunMode == "ExpMCPredData" )
  {
    LoopQCDExpMC   ( myQCDFactors, myQCDSampleWeight );
    LoopQCDPredData( myQCDFactors, myDataSampleWeight );
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
  else
  {
    std::cout << "Invalide RunMode!!" << std::endl;
    return 0;
  }

  return 0;
}
