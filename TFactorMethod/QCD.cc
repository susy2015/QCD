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

#include "QCD.h"

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
      if(met < metbins_edge[0]) continue;

      //closure plots variables
      int njets30 = tr.getVar<int>("nJets30");
      int njets50 = tr.getVar<int>("nJets50");
      double ht = tr.getVar<double>("ht");
      double mht = tr.getVar<double>("mht");

      //checking plots for full QCD samples
      //filling HT variables for quick weight check
      //(myClosureHistgram.h_b_all_HT)->Fill(ht,thisweight);

      int metbin_number = myQCDBGModel.Set_metbin_number(met);
      int mt2bin_number = myQCDBGModel.Set_mt2bin_number(mt2);
      int njetsbin_number = myQCDBGModel.Set_njetsbin_number(ntopjets);

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto");
      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      double calomet = tr.getVar<double>("calomet");
      bool passPFCaloMETRatio = (met/calomet<3) && (calomet>80);
      //normal baseline without dPhis cut
      bool passBaselineQCD = passLeptVeto
                          && passTagger
                          && passBJets
                          && passNoiseEventFilter
                          //&& passQCDHighMETFilter
                          && passPFCaloMETRatio;
 
      //apply the met efficiencies
      //double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      //double metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( false, ht, met );
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
        if( met < metbins_edge[0] ) std::cout << "what the fuck is going on!!" << std::endl;
        
        if ( passdPhis )
        {
          if( ntopjets < 3 && nbotjets < 3 )
          {
            myQCDFactors.nQCDNormal_MC[i][metbin_number][mt2bin_number]++;
            myQCDFactors.nQCDNormal[i][metbin_number][mt2bin_number]+=(thisweight*metEff);
          }
          myQCDFactors.nQCDNormal_NJF_MC_all[njetsbin_number]++;
        }

        if ( !passdPhis )
        {
          if( ntopjets < 3 && nbotjets < 3 )
          {
            myQCDFactors.nQCDInverted_MC[i][metbin_number][mt2bin_number]++;
            myQCDFactors.nQCDInverted[i][metbin_number][mt2bin_number]+=(thisweight*metEff);
          }
          myQCDFactors.MET_sum[i][metbin_number][mt2bin_number] = myQCDFactors.MET_sum[i][metbin_number][mt2bin_number] + met * thisweight * metEff;
          myQCDFactors.MET_sum_weight[i][metbin_number][mt2bin_number] = myQCDFactors.MET_sum_weight[i][metbin_number][mt2bin_number] + thisweight * metEff;

          //(myCalHistgram.h_cal_met_MC[metbin_number][mt2bin_number])->Fill(met,thisweight*metEff);
          //int searchbin_id = mySearchBins.find_Binning_Index( nbotjets, ntopjets, mt2, met );
          //std::vector<int> searchbin_ids = mySearchBins.find_Binning_Indices( nbotjets, ntopjets, mt2, met );
          std::vector<int> searchbin_ids = mySearchBins.find_Binning_Indices( nbotjets, ntopjets, mt2, met, ht );
          for(auto i=0;i<searchbin_ids.size();i++)
          {
            int searchbin_id = searchbin_ids.at(i);
            if( searchbin_id >= 0)
            {
              myQCDFactors.MET_sum_all_exp_sb[searchbin_id] = myQCDFactors.MET_sum_all_exp_sb[searchbin_id] + met * thisweight * metEff;
              myQCDFactors.MET_sum_weight_all_exp_sb[searchbin_id] = myQCDFactors.MET_sum_weight_all_exp_sb[searchbin_id] + thisweight * metEff;
              myQCDFactors.MT2_sum_all_exp_sb[searchbin_id] = myQCDFactors.MT2_sum_all_exp_sb[searchbin_id] + mt2 * thisweight * metEff;
              myQCDFactors.MT2_sum_weight_all_exp_sb[searchbin_id] = myQCDFactors.MT2_sum_weight_all_exp_sb[searchbin_id] + thisweight * metEff;
            }
          }
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
      if(met < metbins_edge[0]) continue;

      //closure plots variables
      int njets30 = tr.getVar<int>("nJets30");
      int njets50 = tr.getVar<int>("nJets50");
      double ht = tr.getVar<double>("ht");
      double mht = tr.getVar<double>("mht");

      //checking plots for full QCD samples
      //filling HT variables for quick weight check
      //(myClosureHistgram.h_b_all_HT)->Fill(ht,thisweight);

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto");
      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      double calomet = tr.getVar<double>("calomet");
      bool passPFCaloMETRatio = (met/calomet<3) && (calomet>80);
      //normal baseline without dPhis cut
      bool passBaselineQCD = passLeptVeto
                          && passTagger
                          && passBJets
                          && passdPhis
                          && passNoiseEventFilter
                          //&& passQCDHighMETFilter
                          && passPFCaloMETRatio;

      //apply the met efficiencies
      //double metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( false, ht, met );
      double metEff = 1;
      if (
          passBaselineQCD
         )
      {
        if(ht<700){ std::cout << "HT: " << ht << "; QCD_HT : " << (*iter_QCDSampleInfos).QCDTag << std::endl; }
        (myClosureHistgram.h_exp_met)->Fill(met,thisweight*metEff);
        (myClosureHistgram.h_exp_njets30)->Fill(njets30,thisweight*metEff);
        (myClosureHistgram.h_exp_njets50)->Fill(njets50,thisweight*metEff);
        (myClosureHistgram.h_exp_mt2)->Fill(mt2,thisweight*metEff);
        (myClosureHistgram.h_exp_ht)->Fill(ht,thisweight*metEff);
        (myClosureHistgram.h_exp_mht)->Fill(mht,thisweight*metEff);
        (myClosureHistgram.h_exp_ntopjets)->Fill(ntopjets,thisweight*metEff);
        (myClosureHistgram.h_exp_nbjets)->Fill(nbotjets,thisweight*metEff);
          
        //int searchbin_id = mySearchBins.find_Binning_Index( nbotjets, ntopjets, mt2, met );
        //std::vector<int> searchbin_ids = mySearchBins.find_Binning_Indices( nbotjets, ntopjets, mt2, met );
        std::vector<int> searchbin_ids = mySearchBins.find_Binning_Indices( nbotjets, ntopjets, mt2, met, ht );
        for(auto i=0;i<searchbin_ids.size();i++)
        {
          int searchbin_id = searchbin_ids.at(i);
          if( searchbin_id >= 0 )
          {
            myQCDFactors.nQCD_exp_sb_MC[i][searchbin_id]++;
            myQCDFactors.nQCD_exp_sb[searchbin_id] += (thisweight*metEff);
            myQCDFactors.nQCD_exp_sb_err[searchbin_id] += (thisweight*metEff)*(thisweight*metEff);
          }
        }
      }  
    }//end of inner loop
  }//end of QCD Samples loop
  
  for( int i=0 ; i<NSEARCH_BINS ; i++ )
  {
    myQCDFactors.nQCD_exp_sb_err[i] = std::sqrt( myQCDFactors.nQCD_exp_sb_err[i] );
  }

  myClosureHistgram.printQCDClosureExp(myQCDFactors.nQCD_exp_sb, myQCDFactors.nQCD_exp_sb_err);
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
      if(met < metbins_edge[0]) continue;

      //closure plots variables
      int njets30 = tr.getVar<int>("nJets30");
      int njets50 = tr.getVar<int>("nJets50");
      double ht = tr.getVar<double>("ht");
      double mht = tr.getVar<double>("mht");

      //checking plots for full QCD samples
      //filling HT variables for quick weight check
      //(myClosureHistgram.h_b_all_HT)->Fill(ht,thisweight);

      int metbin_number = myQCDBGModel.Set_metbin_number(met);
      int mt2bin_number = myQCDBGModel.Set_mt2bin_number(mt2);
      int njetsbin_number = myQCDBGModel.Set_njetsbin_number(ntopjets);

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto");
      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      double calomet = tr.getVar<double>("calomet");
      bool passPFCaloMETRatio = (met/calomet<3) && (calomet>80);
      //normal baseline without dPhis cut
      bool passBaselineQCD = passLeptVeto
                          && passTagger
                          && passBJets
                          && passNoiseEventFilter
                          //&& passQCDHighMETFilter
                          && passPFCaloMETRatio;
      //apply trigger efficiencies
      //double metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( false, ht, met );
      double metEff = 1;
      if ( passBaselineQCD )
      {
        if( !passdPhis )
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
          //int searchbin_id = mySearchBins.find_Binning_Index( nbotjets, ntopjets, mt2, met );
          //std::vector<int> searchbin_ids = mySearchBins.find_Binning_Indices( nbotjets, ntopjets, mt2, met );
          std::vector<int> searchbin_ids = mySearchBins.find_Binning_Indices( nbotjets, ntopjets, mt2, met, ht );
          for(auto i=0;i<searchbin_ids.size();i++)
          {
            int searchbin_id = searchbin_ids.at(i);
            if( searchbin_id >= 0 )
            {
              myQCDFactors.nQCD_pred_sb[searchbin_id] += (predweight);
              myQCDFactors.nQCD_pred_sb_err[searchbin_id] += (predweight * predweight);
            }
          }
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop

  for( int i=0 ; i<NSEARCH_BINS ; i++ )
  {
    myQCDFactors.nQCD_pred_sb_err[i] = std::sqrt( myQCDFactors.nQCD_pred_sb_err[i] );
  }

  myClosureHistgram.printQCDClosurePred(myQCDFactors.nQCD_pred_sb, myQCDFactors.nQCD_pred_sb_err);
  (myClosureHistgram.oFile)->Write();
  (myClosureHistgram.oFile)->Close();
  return ;
}

void LoopQCDCalTFSideBand( QCDFactors& myQCDFactors, QCDSampleWeight& myQCDSampleWeight )
{
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  int i = 0;

  std::cout << "Calculating TFs in sideband: " << std::endl;
  
  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);

    double thisweight = (*iter_QCDSampleInfos).weight;
    //negative weight for other MC samples
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
      if(met < metbins_edge[0]) continue;

      //closure plots variables
      int njets30 = tr.getVar<int>("nJets30");
      int njets50 = tr.getVar<int>("nJets50");
      double ht = tr.getVar<double>("ht");
      double mht = tr.getVar<double>("mht");

      int metbin_number = myQCDBGModel.Set_metbin_number(met);
      int mt2bin_number = myQCDBGModel.Set_mt2bin_number(mt2);
      int sidebandbin_number = -1;
      if( metbin_number==0 && mt2bin_number==0){ sidebandbin_number=0; }
      if( metbin_number==0 && mt2bin_number==1){ sidebandbin_number=1; }

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto");
      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      //normal baseline without dPhis cut
      bool passBaselineQCD = passLeptVeto
                          && passTagger
                          && passBJets
                          && passNoiseEventFilter;

      //apply trigger efficiencies
      double metEff = 1;
      if ( passBaselineQCD )
      {
        if( (*iter_QCDSampleInfos).QCDTag == "MET" )
        {
          std::vector<std::string> TriggerNames = tr.getVec<std::string>("TriggerNames");
          std::vector<int> PassTrigger = tr.getVec<int>("PassTrigger");
          bool foundTrigger = false;

          for(unsigned it=0; it<TriggerNames.size(); it++)
          {
            if
            (
                TriggerNames[it].find("HLT_PFMET100_PFMHT100_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMET110_PFMHT110_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMET120_PFMHT120_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v") != std::string::npos
            )
            {
              if( PassTrigger[it] ) foundTrigger = true;
            }
          }

          if( !foundTrigger ) continue;
        }

        //Get normalized Tfactor in Inverted dPhi region in Real Data
        //metbin side band
        if( sidebandbin_number >= 0 )
        {
          if( passdPhis )
          {
            if( (*iter_QCDSampleInfos).QCDTag == "MET" )
            {
              metEff = 1;
              myQCDFactors.nQCDNormal_Data_all[sidebandbin_number] += std::abs(thisweight * metEff);
              myQCDFactors.nQCDNormal_Data_all_err[sidebandbin_number] += thisweight * thisweight * metEff * metEff;
            }
            if(   ((*iter_QCDSampleInfos).QCDTag).find("TTJets") != std::string::npos
               || ((*iter_QCDSampleInfos).QCDTag).find("ST_tW") != std::string::npos
               || ((*iter_QCDSampleInfos).QCDTag).find("WJetsToLNu_HT") != std::string::npos
              )
            { 
              //metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( true, ht, met );
              bool isLL = tr.getVar<bool>("isLL");
              double ttjetsFactor = singlemuCS_lowmet[sidebandbin_number];
              //double ttjetsFactor = 1;
              if(isLL)
              { 
                myQCDFactors.nQCDNormal_lostleptMC_all[sidebandbin_number] += std::abs(thisweight * metEff) * ttjetsFactor;
                myQCDFactors.nQCDNormal_lostleptMC_all_err[sidebandbin_number] += thisweight * thisweight * metEff * metEff * ttjetsFactor * ttjetsFactor;
              }
              else
              { 
                myQCDFactors.nQCDNormal_hadtauMC_all[sidebandbin_number] += std::abs(thisweight * metEff) * ttjetsFactor;
                myQCDFactors.nQCDNormal_hadtauMC_all_err[sidebandbin_number] += thisweight * thisweight * metEff * metEff * ttjetsFactor * ttjetsFactor;
              }
            }
            else if( ((*iter_QCDSampleInfos).QCDTag).find("ZJetsToNuNu_HT") != std::string::npos )
            { 
              //metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( true, ht, met );
              double njetRWF = 1;
              njets30<8 ? njetRWF = zinv_NJetRweightingFactor[njets30-1] : njetRWF = zinv_NJetRweightingFactor[7];

              myQCDFactors.nQCDNormal_zinvMC_all[sidebandbin_number] += std::abs(thisweight * metEff * njetRWF * zinv_RNorm);
              myQCDFactors.nQCDNormal_zinvMC_all_err[sidebandbin_number] += thisweight * metEff * njetRWF * zinv_RNorm * thisweight * metEff * njetRWF * zinv_RNorm;
            }
            else if(   
                       ((*iter_QCDSampleInfos).QCDTag).find("TTZTo") != std::string::npos
                    || ((*iter_QCDSampleInfos).QCDTag).find("TTWJets") != std::string::npos
                   )
            { 
              //metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( true, ht, met );
              bool isGenZLep = tr.getVar<bool>("isGenZLep");
              bool isGenWLep = tr.getVar<bool>("isGenWLep");
              if( isGenZLep || isGenWLep ) continue;
              
              bool isNegativeWeight = tr.getVar<bool>("isNegativeWeight");
              isNegativeWeight ? myQCDFactors.nQCDNormal_ttzMC_all[sidebandbin_number] -= std::abs(thisweight * metEff) : myQCDFactors.nQCDNormal_ttzMC_all[sidebandbin_number] += std::abs(thisweight * metEff);
              myQCDFactors.nQCDNormal_ttzMC_all_err[sidebandbin_number] += thisweight * thisweight * metEff * metEff;
            }
          }
          else 
          {
            if( (*iter_QCDSampleInfos).QCDTag == "MET" )
            {
              metEff = 1;
              myQCDFactors.nQCDInverted_Data_all[sidebandbin_number] += std::abs(thisweight * metEff);
              myQCDFactors.nQCDInverted_Data_all_err[sidebandbin_number] += thisweight * thisweight * metEff * metEff;
            }
            if(   ((*iter_QCDSampleInfos).QCDTag).find("TTJets") != std::string::npos
               || ((*iter_QCDSampleInfos).QCDTag).find("ST_tW") != std::string::npos
               || ((*iter_QCDSampleInfos).QCDTag).find("WJetsToLNu_HT") != std::string::npos
              )
            {
              //metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( true, ht, met ); 
              bool isLL = tr.getVar<bool>("isLL");
              double ttjetsFactor = singlemuCS_lowmet[sidebandbin_number];
              //double ttjetsFactor = 1;
              if(isLL)
              {
                myQCDFactors.nQCDInverted_lostleptMC_all[sidebandbin_number] += std::abs(thisweight * metEff) * ttjetsFactor;
                myQCDFactors.nQCDInverted_lostleptMC_all_err[sidebandbin_number] += thisweight * thisweight * metEff * metEff * ttjetsFactor * ttjetsFactor; 
              }
              else
              { 
                myQCDFactors.nQCDInverted_hadtauMC_all[sidebandbin_number] += std::abs(thisweight * metEff) * ttjetsFactor;
                myQCDFactors.nQCDInverted_hadtauMC_all_err[sidebandbin_number] += thisweight * thisweight * metEff * metEff * ttjetsFactor * ttjetsFactor;
              }
            }
            else if( ((*iter_QCDSampleInfos).QCDTag).find("ZJetsToNuNu_HT") != std::string::npos )
            { 
              //metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( true, ht, met );
              double njetRWF = 1;
              njets30<8 ? njetRWF = zinv_NJetRweightingFactor[njets30-1] : njetRWF = zinv_NJetRweightingFactor[7];
              myQCDFactors.nQCDInverted_zinvMC_all[sidebandbin_number] += std::abs(thisweight * metEff * njetRWF * zinv_RNorm);
              myQCDFactors.nQCDInverted_zinvMC_all_err[sidebandbin_number] += thisweight * metEff * njetRWF * zinv_RNorm * thisweight * metEff * njetRWF * zinv_RNorm;
            }
            else if(   
                       ((*iter_QCDSampleInfos).QCDTag).find("TTZTo") != std::string::npos
                    || ((*iter_QCDSampleInfos).QCDTag).find("TTWJets") != std::string::npos
                   )
            { 
              //metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( true, ht, met );
              bool isGenZLep = tr.getVar<bool>("isGenZLep");
              bool isGenWLep = tr.getVar<bool>("isGenWLep");
              if( isGenZLep || isGenWLep ) continue;
              
              bool isNegativeWeight = tr.getVar<bool>("isNegativeWeight");
              isNegativeWeight ? myQCDFactors.nQCDInverted_ttzMC_all[sidebandbin_number] -= std::abs(thisweight * metEff) : myQCDFactors.nQCDInverted_ttzMC_all[sidebandbin_number] += std::abs(thisweight * metEff);
              myQCDFactors.nQCDInverted_ttzMC_all_err[sidebandbin_number] += thisweight * thisweight * metEff * metEff;
            }
          }
        }
      }//event loop
    }//end of inner loop
  }//end of QCD Samples loop

  for( int i=0 ; i<MT2_BINS ; i++ )
  {
    myQCDFactors.nQCDNormal_hadtau_all[i] = dd_TQCD_hadtau[i];
    myQCDFactors.nQCDInverted_hadtau_all[i] = dd_TQCD_hadtauInv[i];
    myQCDFactors.nQCDNormal_lostlept_all[i] = dd_TQCD_lostlept[i];
    myQCDFactors.nQCDInverted_lostlept_all[i] = dd_TQCD_lostleptInv[i];

    myQCDFactors.nQCDNormal_hadtau_all_err[i] = dd_TQCD_hadtau_stat[i];
    myQCDFactors.nQCDInverted_hadtau_all_err[i] = dd_TQCD_hadtauInv_stat[i];
    myQCDFactors.nQCDNormal_lostlept_all_err[i] = dd_TQCD_lostlept_stat[i]; 
    myQCDFactors.nQCDInverted_lostlept_all_err[i] = dd_TQCD_lostleptInv_stat[i];

    myQCDFactors.nQCDNormal_Data_all_err[i] = std::sqrt( myQCDFactors.nQCDNormal_Data_all_err[i] ); 
    myQCDFactors.nQCDInverted_Data_all_err[i] = std::sqrt( myQCDFactors.nQCDInverted_Data_all_err[i] );
    myQCDFactors.nQCDNormal_hadtauMC_all_err[i] = std::sqrt( myQCDFactors.nQCDNormal_hadtauMC_all_err[i] ); 
    myQCDFactors.nQCDInverted_hadtauMC_all_err[i] = std::sqrt( myQCDFactors.nQCDInverted_hadtauMC_all_err[i] );
    myQCDFactors.nQCDNormal_lostleptMC_all_err[i] = std::sqrt( myQCDFactors.nQCDNormal_lostleptMC_all_err[i] ); 
    myQCDFactors.nQCDInverted_lostleptMC_all_err[i] = std::sqrt( myQCDFactors.nQCDInverted_lostleptMC_all_err[i] );
    myQCDFactors.nQCDNormal_zinvMC_all_err[i] = std::sqrt( myQCDFactors.nQCDNormal_zinvMC_all_err[i] ); 
    myQCDFactors.nQCDInverted_zinvMC_all_err[i] = std::sqrt( myQCDFactors.nQCDInverted_zinvMC_all_err[i] );
    myQCDFactors.nQCDNormal_ttzMC_all_err[i] = std::sqrt( myQCDFactors.nQCDNormal_ttzMC_all_err[i] ); 
    myQCDFactors.nQCDInverted_ttzMC_all_err[i] = std::sqrt( myQCDFactors.nQCDInverted_ttzMC_all_err[i] );
  }

  std::string pred_type;
  pred_type = "MCDriven";
  //pred_type = "DataDriven";
  //deal with the Tfactor from data.need to uncomment when you want to get low met side band tfactor from real data
  myQCDFactors.getAndprintTFactorsfromDataHeader("MCDriven"); 
  return ;
}

void LoopQCDPredData( QCDFactors& myQCDFactors, QCDSampleWeight& myQCDSampleWeight )
{
  double QCDTFactorPred[MET_BINS][MT2_BINS] = {{0}}, QCDTFactorPred_err[MET_BINS][MT2_BINS] = {{0}};
  double QCDTNJFPred[NJETS_BINS] = {0}, QCDTNJFPred_err[NJETS_BINS] = {0};
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

  std::cout << "Prediction(MET): " << std::endl;
  
  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);

    double thisweight = (*iter_QCDSampleInfos).weight;
    //negative weight for other MC samples
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
      if(met < metbins_edge[0]) continue;

      //closure plots variables
      int njets30 = tr.getVar<int>("nJets30");
      int njets50 = tr.getVar<int>("nJets50");
      double ht = tr.getVar<double>("ht");
      //double mht = tr.getVar<double>("mht");

      int metbin_number = myQCDBGModel.Set_metbin_number(met);
      int mt2bin_number = myQCDBGModel.Set_mt2bin_number(mt2);
      int njetsbin_number = myQCDBGModel.Set_njetsbin_number(ntopjets);

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto");
      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      //normal baseline without dPhis cut
      bool passBaselineQCD = passLeptVeto
                          && passTagger
                          && passBJets
                          && passNoiseEventFilter;

      //apply trigger efficiencies
      double metEff = 1;
      if ( passBaselineQCD )
      {
        if( (*iter_QCDSampleInfos).QCDTag == "MET" )
        {
          std::vector<std::string> TriggerNames = tr.getVec<std::string>("TriggerNames");
          std::vector<int> PassTrigger = tr.getVec<int>("PassTrigger");
          bool foundTrigger = false;

          for(unsigned it=0; it<TriggerNames.size(); it++)
          {
            if
            (
                TriggerNames[it].find("HLT_PFMET100_PFMHT100_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMET110_PFMHT110_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMET120_PFMHT120_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v") != std::string::npos
            )
            {
              if( PassTrigger[it] ) foundTrigger = true;
            }
          }

          if( !foundTrigger ) continue;
        }

        if( (!passdPhis) )
        {
          //if( ht < 500) std::cout << ht << " small ht, what the fuck!!" << std::endl;
          //int searchbin_id = mySearchBins.find_Binning_Index( nbotjets, ntopjets, mt2, met );
          //std::vector<int> searchbin_ids = mySearchBins.find_Binning_Indices( nbotjets, ntopjets, mt2, met );
          std::vector<int> searchbin_ids = mySearchBins.find_Binning_Indices( nbotjets, ntopjets, mt2, met, ht );
          for(auto i=0;i<searchbin_ids.size();i++)
          { 
            int searchbin_id = searchbin_ids.at(i);
            if( searchbin_id >= 0 )
            {
              if( (*iter_QCDSampleInfos).QCDTag == "MET" )
              { 
                metEff = 1;
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
                //metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( true, ht, met );
                bool isLL = tr.getVar<bool>("isLL");
                double ttjetsFactor = singlemuCS_invdphi;
                //double ttjetsFactor = 1;
                if(isLL)
                {
                  myQCDFactors.DC_sb_lostleptMC[searchbin_id] += std::abs(thisweight * metEff) * ttjetsFactor;
                  myQCDFactors.DC_sb_lostleptMC_err[searchbin_id] += thisweight * metEff * thisweight * metEff * ttjetsFactor * ttjetsFactor;
                }
                else
                {
                  myQCDFactors.DC_sb_hadtauMC[searchbin_id] += std::abs(thisweight * metEff) * ttjetsFactor; 
                  myQCDFactors.DC_sb_hadtauMC_err[searchbin_id] += thisweight * metEff * thisweight * metEff * ttjetsFactor * ttjetsFactor;
                }
              }
              else if( ((*iter_QCDSampleInfos).QCDTag).find("ZJetsToNuNu_HT") != std::string::npos )
              {
                //metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( true, ht, met );
                double njetRWF = 1;
                njets30<8 ? njetRWF = zinv_NJetRweightingFactor[njets30-1] : njetRWF = zinv_NJetRweightingFactor[7];   
                myQCDFactors.DC_sb_zinvMC[searchbin_id] += std::abs(thisweight * metEff * njetRWF * zinv_RNorm);
                myQCDFactors.DC_sb_zinvMC_err[searchbin_id] += thisweight * metEff * njetRWF * zinv_RNorm * thisweight * metEff * njetRWF * zinv_RNorm;
              }
              else if(
                         ((*iter_QCDSampleInfos).QCDTag).find("TTZTo") != std::string::npos
                      || ((*iter_QCDSampleInfos).QCDTag).find("TTWJets") != std::string::npos
                     )
              {
                //metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( true, ht, met );
                bool isGenZLep = tr.getVar<bool>("isGenZLep");
                bool isGenWLep = tr.getVar<bool>("isGenWLep");
                if( isGenZLep || isGenWLep ) continue;

                bool isNegativeWeight = tr.getVar<bool>("isNegativeWeight");
                if( isNegativeWeight ) thisweight = -thisweight;
                isNegativeWeight ? myQCDFactors.DC_sb_ttzMC[searchbin_id] -= std::abs(thisweight * metEff) : myQCDFactors.DC_sb_ttzMC[searchbin_id] += std::abs(thisweight * metEff);
                //isNegativeWeight ? myQCDFactors.DC_sb_ttzMC_err[searchbin_id] -= thisweight * metEff * thisweight * metEff : myQCDFactors.DC_sb_ttzMC_err[searchbin_id] += thisweight * metEff * thisweight * metEff;
                myQCDFactors.DC_sb_ttzMC_err[searchbin_id] += thisweight * metEff * thisweight * metEff;
              }
            }//if valid search bin id >=0
          }//event search region loop
        }//if inverted dphi
      }//event loop
    }//end of inner loop
  }//end of QCD Samples loop

  //get non closure unc from root file, need to be correcto in the following loop
  myQCDFactors.getNonClosureUnc();
  for( int i=0 ; i<NSEARCH_BINS ; i++ )
  {
    // determine the mt2 met id from mt2 met mean value
    myQCDFactors.MET_sb_mean[i] = myQCDFactors.MET_sb_sum[i]/myQCDFactors.MET_sb_sum_weight[i];
    myQCDFactors.MT2_sb_mean[i] = myQCDFactors.MT2_sb_sum[i]/myQCDFactors.MT2_sb_sum_weight[i];
    int met_id = -1, mt2_id = -1;
    met_id = myQCDBGModel.Set_metbin_number( myQCDFactors.MET_sb_mean[i] );
    mt2_id = myQCDBGModel.Set_mt2bin_number( myQCDFactors.MT2_sb_mean[i] );
    //std::cout << met_id << "," << mt2_id << std::endl;
    //set up data card from Tfactors
    if( met_id < 0 || mt2_id < 0 )
    {
      //reset the met and mt2 id with average value from MC
      met_id = myQCDBGModel.Set_metbin_number( head_QCD_meanMET_exp_sb[i] );
      mt2_id = myQCDBGModel.Set_mt2bin_number( head_QCD_meanMT2_exp_sb[i] );
      if( head_QCD_meanMET_exp_sb[i] < 100 ) met_id = myQCDBGModel.Set_metbin_number( head_QCD_meanMET_exp_sb[i-1] );
      if( head_QCD_meanMT2_exp_sb[i] < 100 ) mt2_id = myQCDBGModel.Set_mt2bin_number( head_QCD_meanMT2_exp_sb[i-1] );
    }
    myQCDFactors.DC_sb_TFactor[i] = QCDTFactorPred[met_id][mt2_id];
    double tmptfsysunc1 = head_QCDTFactor_err[met_id][mt2_id]/head_QCDTFactor[met_id][mt2_id];
    double tmptfsysunc2 = head_QCDTFactorScaled_err[met_id][mt2_id]/head_QCDTFactorScaled[met_id][mt2_id];
    myQCDFactors.DC_sb_TFactor_err[i] = std::sqrt( tmptfsysunc1*tmptfsysunc1 + tmptfsysunc2*tmptfsysunc2);
   
    //DataDriven from header file
    myQCDFactors.DC_sb_hadtau[i] = dd_pred_sb_hadtau[i];
    myQCDFactors.DC_sb_lostlept[i] = dd_pred_sb_lostlept[i];
    myQCDFactors.DC_sb_hadtau_errup[i] = std::sqrt( dd_pred_sb_hadtau_stat[i]*dd_pred_sb_hadtau_stat[i] + dd_pred_sb_hadtau_sysUp[i]*dd_pred_sb_hadtau_sysUp[i] );
    myQCDFactors.DC_sb_hadtau_errdown[i] = std::sqrt( dd_pred_sb_hadtau_stat[i]*dd_pred_sb_hadtau_stat[i] + dd_pred_sb_hadtau_sysDown[i]*dd_pred_sb_hadtau_sysDown[i] );
    myQCDFactors.DC_sb_lostlept_errup[i] = std::sqrt( dd_pred_sb_lostlept_stat[i]*dd_pred_sb_lostlept_stat[i] + dd_pred_sb_lostlept_sysUp[i]*dd_pred_sb_lostlept_sysUp[i] );
    myQCDFactors.DC_sb_lostlept_errdown[i] = std::sqrt( dd_pred_sb_lostlept_stat[i]*dd_pred_sb_lostlept_stat[i] + dd_pred_sb_lostlept_sysDown[i]*dd_pred_sb_lostlept_sysDown[i] );    
    //MC driven err
    myQCDFactors.DC_sb_Data_err[i] = std::sqrt(myQCDFactors.DC_sb_Data_err[i]);
    myQCDFactors.DC_sb_hadtauMC_err[i] = std::sqrt(myQCDFactors.DC_sb_hadtauMC_err[i]);
    myQCDFactors.DC_sb_lostleptMC_err[i] = std::sqrt(myQCDFactors.DC_sb_lostleptMC_err[i]);
    myQCDFactors.DC_sb_zinvMC_err[i] = std::sqrt(myQCDFactors.DC_sb_zinvMC_err[i]);
    myQCDFactors.DC_sb_ttzMC_err[i] = std::sqrt(myQCDFactors.DC_sb_ttzMC_err[i]);
    
    //deal with NTop jets correction factors related issue
    SearchBins::searchBinDef outBinDef; mySearchBins.find_BinBoundaries( i, outBinDef );
    int ntopbinid = outBinDef.top_lo_ - 1;//0,1,2 for ntop =1,2,and >=3
    myQCDFactors.QCD_NTopFactor[i] = head_QCDTNJF[ntopbinid];
    myQCDFactors.QCD_NTopFactor_relative_err[i] = head_QCDTNJF_err[ntopbinid]/head_QCDTNJF[ntopbinid];
    //myQCDFactors.QCD_NonClosure_relative_err[i] += (head_QCDTNJF[ntopbinid]-1);
  }
  
  std::string pred_type;
  pred_type = "MCDriven";
  //pred_type = "DataDriven";
  //deal with the Tfactor from data.need to uncomment when you want to get low met side band tfactor from real data
  //myQCDFactors.printSysHeader("DataDriven");
  myQCDFactors.printSysHeader("MCDriven");
  //myQCDFactors.printDataCard("DataDriven");
  myQCDFactors.printDataCard("MCDriven");
  return ;
}

void LoopBasicCheckQCD( QCDSampleWeight& myQCDSampleWeight )
{
  BasicCheckHistgram myBasicCheckHistgram;
  myBasicCheckHistgram.BookHistgram( (dir_out + "BasicCheckQCD.root").c_str() );
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;

  std::cout << "Let's check inverted Delta Phi region for QCD: " << std::endl;
  
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

      //checking plots for full QCD samples
      //filling HT variables for quick weight check
      //(myClosureHistgram.h_b_all_HT)->Fill(ht,thisweight);

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto");
      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      //normal baseline without dPhis cut
      bool passBaselineQCD = passLeptVeto
                          && passTagger
                          && passBJets
                          && passNoiseEventFilter;

      bool passBaseline_dPhisInverted = false;
      passBaseline_dPhisInverted = passBaselineQCD && (!passdPhis);
      //apply trigger efficiencies
      //double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      double metEff = 1;

      if (passBaseline_dPhisInverted)
      {
        //int searchbin_id = mySearchBins.find_Binning_Index( nbotjets, ntopjets, mt2, met );
        int searchbin_id = mySearchBins.find_Binning_Index( nbotjets, ntopjets, mt2, met, ht );

        if( (*iter_QCDSampleInfos).QCDTag == "MET" )
        {
          std::vector<std::string> TriggerNames = tr.getVec<std::string>("TriggerNames");
          std::vector<int> PassTrigger = tr.getVec<int>("PassTrigger");
          bool foundTrigger = false;

          for(unsigned it=0; it<TriggerNames.size(); it++)
          {
            if
            ( 
                TriggerNames[it].find("HLT_PFMET100_PFMHT100_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMET110_PFMHT110_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMET120_PFMHT120_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v") != std::string::npos
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
          (myBasicCheckHistgram.h_b_mht_Data)->Fill(mht,thisweight*metEff);
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
            bool passPFCaloMETRatio = (met/calomet<3) && (calomet>80); 
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

  double nDataLL[MT2_BINS] = {0}, nMCLL[MT2_BINS] = {0};
  double nDataLL_test = 0, nMCLL_test = 0;
  std::cout << "Let's check single Muon region for LL: " << std::endl;
  
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
      int mt2bin_number = myQCDBGModel.Set_mt2bin_number(mt2);
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
      //normal baseline without dPhis cut
      bool passBaselineLL = passTagger
                         && passBJets
                         //&& passdPhis
                         && passNoiseEventFilter;

      //apply trigger efficiencies
      //double metEff = myTriggerEff.GetTriggerEff_HLT_HT300_MET100( true, ht, met );
      double metEff = 1;
      if ( 
           passBaselineLL && (nElectrons==0) && (nMuons == 1) 
         //&& (!passdPhis)
         //&& passdPhis
         )
      {
        //int searchbin_id = mySearchBins.find_Binning_Index( nbotjets, ntopjets, mt2, met );
        int searchbin_id = mySearchBins.find_Binning_Index( nbotjets, ntopjets, mt2, met, ht );

        if( (*iter_QCDSampleInfos).QCDTag == "MET" )
        {
          //be careful! reset trigger eff to be 1 for real data
          metEff = 1;
          std::vector<std::string> TriggerNames = tr.getVec<std::string>("TriggerNames");
          std::vector<int> PassTrigger = tr.getVec<int>("PassTrigger");
          bool foundTrigger = false;

          for(unsigned it=0; it<TriggerNames.size(); it++)
          {
            if
            ( 
                TriggerNames[it].find("HLT_PFMET100_PFMHT100_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMET110_PFMHT110_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMET120_PFMHT120_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v") != std::string::npos
             || TriggerNames[it].find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v") != std::string::npos
            )
            {
              if( PassTrigger[it] ) foundTrigger = true;
            }
          }

          if( !foundTrigger ) continue;

          if(met<metbins_edge[1] && met>metbins_edge[0]){ nDataLL[mt2bin_number]+=thisweight*metEff; }
          if(met>metbins_edge[1] && (!passdPhis)){ nDataLL_test+=thisweight*metEff; }
          (myBasicCheckHistgram.h_b_met_Data)->Fill(met,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mt2_Data)->Fill(mt2,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ntopjets_Data)->Fill(ntopjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_nbjets_Data)->Fill(nbotjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ht_Data)->Fill(ht,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mht_Data)->Fill(mht,thisweight*metEff);
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
            if(isLL) std::cout << "isLL" << std::endl;
            isLL ? ih = 0 : ih = 1;
          }
          else if( ((*iter_QCDSampleInfos).QCDTag).find("ZJetsToNuNu_HT") != std::string::npos ) ih = 2;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("QCD_HT") != std::string::npos )
          {
            double calomet = tr.getVar<double>("calomet");
            bool passPFCaloMETRatio = (met/calomet<3) && (calomet>80); 
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

          if(met<metbins_edge[1] && met>metbins_edge[0]){ nMCLL[mt2bin_number]+=thisweight*metEff; }
          if(met>metbins_edge[1] && (!passdPhis)){ nMCLL_test+=thisweight*metEff; }
          (myBasicCheckHistgram.h_b_met_MC[ih])->Fill(met,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mt2_MC[ih])->Fill(mt2,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ntopjets_MC[ih])->Fill(ntopjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_nbjets_MC[ih])->Fill(nbotjets,thisweight*metEff);
          (myBasicCheckHistgram.h_b_ht_MC[ih])->Fill(ht,thisweight*metEff);
          (myBasicCheckHistgram.h_b_mht_MC[ih])->Fill(mht,thisweight*metEff);
          (myBasicCheckHistgram.h_b_njets30_MC)[ih]->Fill(njets30,thisweight*metEff);
          (myBasicCheckHistgram.h_b_njets50_MC)[ih]->Fill(njets50,thisweight*metEff);

          (myBasicCheckHistgram.h_b_sb_MC)[ih]->Fill(searchbin_id,thisweight*metEff);
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop
  for(int i=0;i<MT2_BINS;i++)
  {
    std::cout << "Counting(MT2Bin" << i <<"), nData : " << nDataLL[i] << "; nMC : "<< nMCLL[i] << std::endl;
    std::cout << "Single Mu Data/MC Factor(MT2Bin" << i <<"): " << nDataLL[i]/nMCLL[i] << std::endl;
  }
  std::cout << "Counting Test, nData : " << nDataLL_test << "; nMC : "<< nMCLL_test << std::endl;
  std::cout << "Single Mu Data/MC Factor Test: " << nDataLL_test/nMCLL_test << std::endl;
  (myBasicCheckHistgram.oFile)->Write();
  (myBasicCheckHistgram.oFile)->Close();
  return ;
}

void LoopSBCheck( QCDSampleWeight& myQCDSampleWeight )
{
  SBCheckHistgram mySBCheckHistgram;
  mySBCheckHistgram.BookHistgram( (dir_out + "SBCheckHistgram.root").c_str() );
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;

  std::cout << "Let's check inverted Delta Phi region for QCD: " << std::endl;
  
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

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto");
      bool passTagger = tr.getVar<bool>("passTagger");
      bool passBJets = tr.getVar<bool>("passBJets");
      bool passdPhis = tr.getVar<bool>("passdPhis");
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter");
      bool passQCDHighMETFilter = tr.getVar<bool>("passQCDHighMETFilter");
      //normal baseline without dPhis cut
      bool passBaseline = (met>200)
                       && passLeptVeto
                       && passTagger
                       && passBJets
                       && passdPhis
                       && passNoiseEventFilter;

      //apply trigger efficiencies
      //double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      double metEff = 1;

      if (passBaseline)
      {
        //int searchbin_id = mySearchBins.find_Binning_Index( nbotjets, ntopjets, mt2, met );
        int searchbin_id = mySearchBins.find_Binning_Index( nbotjets, ntopjets, mt2, met, ht );
        if(searchbin_id < 0) continue;

        if( (*iter_QCDSampleInfos).QCDTag == "MET" )
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
        
          (mySBCheckHistgram.h_b_met_Data[searchbin_id])->Fill(met,thisweight*metEff);
          (mySBCheckHistgram.h_b_mt2_Data[searchbin_id])->Fill(mt2,thisweight*metEff);
          (mySBCheckHistgram.h_b_ht_Data[searchbin_id])->Fill(ht,thisweight*metEff);
          (mySBCheckHistgram.h_b_mht_Data[searchbin_id])->Fill(mht,thisweight*metEff);
          (mySBCheckHistgram.h_b_njets30_Data[searchbin_id])->Fill(njets30,thisweight*metEff);
          (mySBCheckHistgram.h_b_njets50_Data[searchbin_id])->Fill(njets50,thisweight*metEff);

          double calomet = tr.getVar<double>("calomet");
          double r = met/calomet;
          (mySBCheckHistgram.h_b_pfcalometr_Data[searchbin_id])->Fill(r,thisweight*metEff);
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
            bool passPFCaloMETRatio = (met/calomet<3) && (calomet>80); 
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

          (mySBCheckHistgram.h_b_met_MC[searchbin_id][ih])->Fill(met,thisweight*metEff);
          (mySBCheckHistgram.h_b_mt2_MC[searchbin_id][ih])->Fill(mt2,thisweight*metEff);
          (mySBCheckHistgram.h_b_ht_MC[searchbin_id][ih])->Fill(ht,thisweight*metEff);
          (mySBCheckHistgram.h_b_mht_MC[searchbin_id][ih])->Fill(mht,thisweight*metEff);
          (mySBCheckHistgram.h_b_njets30_MC)[searchbin_id][ih]->Fill(njets30,thisweight*metEff);
          (mySBCheckHistgram.h_b_njets50_MC)[searchbin_id][ih]->Fill(njets50,thisweight*metEff);
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop

  (mySBCheckHistgram.oFile)->Write();
  (mySBCheckHistgram.oFile)->Close();
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
  
  std::cout << "The valid run modes are: CalOnly, ExpMCOnly, PredMCOnly, CalTFSideBandOnly, PredDataOnly, BasicCheckQCD, BasicCheckLL, SBCheck" << std::endl;
  std::cout << "The run mode we have right now is: " << RunMode << std::endl;
  //define my QCDFactors class to stroe counts and Translation factors
  QCDFactors myQCDFactors;
  //myTriggerEff.SelfTest();
  //Sample needed in the calculation and expectation loop
  QCDSampleWeight myQCDSampleWeight;
  myQCDSampleWeight.QCDSampleInfo_push_back( "_QCD_HT300to500"  , 366800  , 54706298, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "_QCD_HT500to700"  , 29370   , 63337753, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "_QCD_HT700to1000" , 6524    , 45453945, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "_QCD_HT1000to1500", 1064    , 15316362, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "_QCD_HT1500to2000", 121.5   , 11650581, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "_QCD_HT2000toInf" , 25.42   ,  6007777, LUMI, 1, inputFileList_QCDMC.c_str() );
  if( myQCDSampleWeight.QCDSampleInfos.size() != QCD_BINS)
  {
    std::cout << "QCD_BINS in QCDBinFunction.h and the entries of QCD samples in QCDReWeighting.h are not equal! Please check on that!" << std::endl; 
    return 0;
  }

  double TTbar_SingleLept_BR = 0.43930872; // 2*W_Lept_BR*(1-W_Lept_BR)
  double TTbar_DiLept_BR = 0.10614564; // W_Lept_BR^2
  //sample needed in the prediction loop
  QCDSampleWeight myDataSampleWeight;
  myDataSampleWeight.QCDSampleInfo_push_back( "MET"                        ,                              1,        1, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTJets_DiLept"             ,         831.76*TTbar_DiLept_BR, 30682233, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromT_"   , 831.76*0.5*TTbar_SingleLept_BR, 53057043, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromTbar_", 831.76*0.5*TTbar_SingleLept_BR, 60494823, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ST_tW_top"                 ,                           35.6,   998400, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ST_tW_antitop"             ,                           35.6,   985000, LUMI, 1, inputFileList_Data.c_str() );
  //be careful!! WJets and ZJets samples have some tricky part, need to understand!
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-200To400"   ,   359.7,      19591498, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-400To600"   ,   48.91,       7432746, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-600To800"   ,   12.05,      18088165, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-800To1200"  ,   5.501,       7854734, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-1200To2500" ,   1.329,       7023857, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-2500ToInf"  , 0.03216,       2507809, LUMI, 1.21, inputFileList_Data.c_str() );

  myDataSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-200To400"  ,    77.67,      25035015, LUMI, 1.23, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-400To600"  ,    10.73,       9290017, LUMI, 1.23, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-600To800"  ,  0.853*3,       5712221, LUMI, 1.23, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-800To1200" ,  0.394*3,       1944423, LUMI, 1.23, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-1200To2500", 0.0974*3,        513471, LUMI, 1.23, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-2500ToInf" ,0.00230*3,        405752, LUMI, 1.23, inputFileList_Data.c_str() );
  //be careful! TTZ has negative weight issue!!
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTZToLLNuNu"            , 0.2529, 1744167 - 635909, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTZToQQ"                , 0.5297,  550282 - 199118, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTWJetsToLNu"           , 0.2043, 1821666 - 582855, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTWJetsToQQ"            , 0.4062,  631804 - 201494, LUMI, 1, inputFileList_Data.c_str() );


  //sample needed in the basic check loop
  QCDSampleWeight myBasicCheckSampleWeight;
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "MET"                        ,                              1,        1, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTJets_DiLept"             ,         831.76*TTbar_DiLept_BR, 30682233, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromT_"   , 831.76*0.5*TTbar_SingleLept_BR, 53057043, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromTbar_", 831.76*0.5*TTbar_SingleLept_BR, 60494823, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ST_tW_top"                 ,                           35.6,   998400, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ST_tW_antitop"             ,                           35.6,   985000, LUMI, 1, inputFileList_Data.c_str() );
  //be careful!! WJets and ZJets samples have some tricky part, need to understand!
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-200To400"   ,   359.7,      19591498, LUMI, 1.21, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-400To600"   ,   48.91,       7432746, LUMI, 1.21, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-600To800"   ,   12.05,      18088165, LUMI, 1.21, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-800To1200"  ,   5.501,       7854734, LUMI, 1.21, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-1200To2500" ,   1.329,       7023857, LUMI, 1.21, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-2500ToInf"  , 0.03216,       2507809, LUMI, 1.21, inputFileList_Data.c_str() );

  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-200To400"  ,    77.67,      25035015, LUMI, 1.23, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-400To600"  ,    10.73,       9290017, LUMI, 1.23, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-600To800"  ,  0.853*3,       5712221, LUMI, 1.23, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-800To1200" ,  0.394*3,       1944423, LUMI, 1.23, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-1200To2500", 0.0974*3,        513471, LUMI, 1.23, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_ZJetsToNuNu_HT-2500ToInf" ,0.00230*3,        405752, LUMI, 1.23, inputFileList_Data.c_str() );
  //be careful! TTZ has negative weight issue!!
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTZToLLNuNu"            , 0.2529, 1744167 - 635909, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTZToQQ"                , 0.5297,  550282 - 199118, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTWJetsToLNu"           , 0.2043, 1821666 - 582855, LUMI, 1, inputFileList_Data.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_TTWJetsToQQ"            , 0.4062,  631804 - 201494, LUMI, 1, inputFileList_Data.c_str() );

  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_QCD_HT300to500"  , 366800  , 54706298, LUMI, 1, inputFileList_QCDMC.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_QCD_HT500to700"  , 29370   , 63337753, LUMI, 1, inputFileList_QCDMC.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_QCD_HT700to1000" , 6524    , 45453945, LUMI, 1, inputFileList_QCDMC.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_QCD_HT1000to1500", 1064    , 15316362, LUMI, 1, inputFileList_QCDMC.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_QCD_HT1500to2000", 121.5   , 11650581, LUMI, 1, inputFileList_QCDMC.c_str() );
  myBasicCheckSampleWeight.QCDSampleInfo_push_back( "_QCD_HT2000toInf" , 25.42   ,  6007777, LUMI, 1, inputFileList_QCDMC.c_str() );

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
  else if( RunMode == "CalTFSideBandOnly" )
  {
    LoopQCDCalTFSideBand( myQCDFactors, myDataSampleWeight );
    return 0;
  }
  else if( RunMode == "PredDataOnly" )
  {
    LoopQCDPredData( myQCDFactors, myDataSampleWeight );
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
  else if( RunMode == "SBCheck" )
  {
    LoopSBCheck( myBasicCheckSampleWeight );
    return 0;
  }
  else
  {
    std::cout << "Invalide RunMode!!" << std::endl;
    return 0;
  }

  return 0;
}
