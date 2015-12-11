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
#include "TriggerEff.h"

const double Scale = 0.5/2.1;

void LoopQCDExpTfactor( QCDFactors& myQCDFactors, QCDSampleWeight& myQCDSampleWeight )
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

  std::cout << "TFactor calculation and Expectation plots: " << std::endl;

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
      bool passNoiseEventFilter = tr.getVar<bool>("passNoiseEventFilter"+spec);

      bool passBJets = tr.getVar<bool>("passBJets"+spec);
      bool passdPhis = tr.getVar<bool>("passdPhis"+spec);
      
      //normal baseline
      bool passBaselineQCD = false;
      passBaselineQCD = passLeptVeto
                     && passnJets
                     && passHT
                     && passMT2
                     && passTagger
                     && passNoiseEventFilter;
      //apply the met efficiencies
      double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      if (
          passBaselineQCD
         )
      {
        if ( passBJets )
        {
          //(myClosureHistgram.h_b_mt2_ybyt)->Fill(MT2,thisweight);
          //(myClosureHistgram.h_b_met_ybyt)->Fill(met,thisweight);
          //(myClosureHistgram.h_b_dphi0_ybyt)->Fill(dPhiVec.at(0),thisweight);
          //(myClosureHistgram.h_b_dphi1_ybyt)->Fill(dPhiVec.at(1),thisweight);
          //(myClosureHistgram.h_b_dphi2_ybyt)->Fill(dPhiVec.at(2),thisweight);
        }

        if ( (!passBJets) )
        {
          //(myClosureHistgram.h_b_mt2_nbnt)->Fill(MT2,thisweight);
          //(myClosureHistgram.h_b_met_nbnt)->Fill(met,thisweight);
          //(myClosureHistgram.h_b_dphi0_nbnt)->Fill(dPhiVec.at(0),thisweight);
          //(myClosureHistgram.h_b_dphi1_nbnt)->Fill(dPhiVec.at(1),thisweight);
          //(myClosureHistgram.h_b_dphi2_nbnt)->Fill(dPhiVec.at(2),thisweight);
        }

        if ( passdPhis )
        {
          myQCDFactors.nQCDNormal_MC[i][metbin_number][mt2bin_number]++;
          myQCDFactors.nQCDNormal[i][metbin_number][mt2bin_number]+=(thisweight*metEff);
 
          if ( passBJets )
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
            }
          }
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

        //(myClosureHistgram.h_inverted_met)->Fill(met,thisweight);
        //(myClosureHistgram.h_inverted_njets)->Fill(njets30,thisweight);
        //(myClosureHistgram.h_inverted_mt2)->Fill(MT2,thisweight);
        //(myClosureHistgram.h_inverted_ht)->Fill(ht,thisweight);
        //(myClosureHistgram.h_inverted_mht)->Fill(mht,thisweight);
        //(myClosureHistgram.h_inverted_ntopjets)->Fill(ntopjets,thisweight);
        //(myClosureHistgram.h_inverted_nbjets)->Fill(nbottomjets,thisweight);
      }
    }//end of inner loop
    i++;
  }//end of QCD Samples loop
  //be careful!! NumbertoTFactor must be in front of sb plot generation! otherwise we may get all 0 in expectation error!!
  myQCDFactors.NumbertoTFactor();
  myQCDFactors.printQCDClosureExp(myClosureHistgram);
  (myClosureHistgram.oFile)->Write();
  (myClosureHistgram.oFile)->Close();
  myQCDFactors.printQCDFactorInfo();
  myQCDFactors.printTFactorsHeader();

  return ;
}

void LoopQCDPred( QCDFactors& myQCDFactors, QCDSampleWeight& myQCDSampleWeight, std::string RunMode )
{
  ClosureHistgram myClosureHistgram;
  if( RunMode.find("PredMC") != std::string::npos ) { myClosureHistgram.BookHistgram( (dir_out + "PredQCDMC.root").c_str() ); }
  else if( RunMode.find("PredData") != std::string::npos ) { myClosureHistgram.BookHistgram( (dir_out + "PredQCDData.root").c_str() ); }
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
      int njetsbin_number = Set_nbjetsbin_number(nbottomjets);
      int mt2bin_number = Set_mt2bin_number(MT2);

      bool passBaselineQCD = tr.getVar<bool>("passBaseline"+spec);
      bool passdPhis = tr.getVar<bool>("passdPhis"+spec);
      bool passBaseline_dPhisInverted = false;

      passBaseline_dPhisInverted = passBaselineQCD && (!passdPhis);
      //apply trigger efficiencies
      double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      
      if (passBaseline_dPhisInverted)
      {
        double predweight = thisweight * metEff * QCDTFactor[metbin_number][mt2bin_number];
        //double predweight_err = thisweight * metEff * QCDTFactor_err[metbin_number][mt2bin_number];
        (myClosureHistgram.h_pred_met)->Fill(met,predweight);
        (myClosureHistgram.h_pred_njets30)->Fill(njets30,predweight);
        (myClosureHistgram.h_pred_njets50)->Fill(njets50,predweight);
        (myClosureHistgram.h_pred_mt2)->Fill(MT2,predweight);
        (myClosureHistgram.h_pred_ht)->Fill(ht,predweight);
        (myClosureHistgram.h_pred_mht)->Fill(mht,predweight);
        (myClosureHistgram.h_pred_ntopjets)->Fill(ntopjets,predweight);
        (myClosureHistgram.h_pred_nbjets)->Fill(nbottomjets,predweight);

        if( ht < 500) std::cout << ht << " small ht, what the fuck!!" << std::endl;

        int searchbin_id = find_Binning_Index( nbottomjets , ntopjets , MT2, met );
        if( searchbin_id >= 0 )
        {
          //std::cout << predweight << std::endl;
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

      passBaseline_dPhisInverted = passBaselineQCD && (!passdPhis);
      //apply trigger efficiencies
      double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );

      if (passBaseline_dPhisInverted)
      {
        if( (*iter_QCDSampleInfos).QCDTag == "HTMHT" )
        {
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

          if( 
              ((*iter_QCDSampleInfos).QCDTag).find("TTJets") != std::string::npos 
           || ((*iter_QCDSampleInfos).QCDTag).find("ST_tW") != std::string::npos
           || ((*iter_QCDSampleInfos).QCDTag).find("WJetsToLNu_HT") != std::string::npos
            ) ih = 0;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("ZJetsToNuNu_HT") != std::string::npos ) ih = 1;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("QCD_HT") != std::string::npos ) ih = 2;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("TTZTo") != std::string::npos ) ih = 3;
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
    if( ( (*iter_QCDSampleInfos).QCDTag ).find("SingleMuon") != std::string::npos ) thisweight = 1 * Scale;
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

      bool passBaselineLL = tr.getVar<bool>("passBaseline"+spec);

      //apply trigger efficiencies
      double metEff = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );

      if ( passBaselineLL && (nMuons == 1) )
      {
        if( (*iter_QCDSampleInfos).QCDTag == "SingleMuon" )
        {
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

          if( 
              ((*iter_QCDSampleInfos).QCDTag).find("TTJets") != std::string::npos 
           || ((*iter_QCDSampleInfos).QCDTag).find("ST_tW") != std::string::npos
           || ((*iter_QCDSampleInfos).QCDTag).find("WJetsToLNu_HT") != std::string::npos
            ) ih = 0;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("ZJetsToNuNu_HT") != std::string::npos ) ih = 1;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("QCD_HT") != std::string::npos ) ih = 2;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("TTZTo") != std::string::npos ) ih = 3;
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
  
  std::cout << "The valid run modes are: ExpMCOnly, PredMCOnly, PredDataOnly, ExpMCPredMC, ExpMCPredData, BasicCheckQCD, BasicCheckLL" << std::endl;
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
  myDataSampleWeight.QCDSampleInfo_push_back( "TTJets_"                 , 831.76,      11339232, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "ST_tW_top"               ,   35.6,        995600, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "ST_tW_antitop"           ,   35.6,        988500, LUMI, 1, inputFileList_Data.c_str() );
  //be careful!! WJets and ZJets samples have some tricky part, need to understand!
  myDataSampleWeight.QCDSampleInfo_push_back( "WJetsToLNu_HT-400To600_" ,  48.91,       1745914, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "WJetsToLNu_HT-600ToInf_" ,  18.77,       1039152, LUMI, 1.21, inputFileList_Data.c_str() );
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


  if( RunMode == "ExpMCOnly" )
  {
    LoopQCDExpTfactor( myQCDFactors, myQCDSampleWeight );
    myQCDFactors.TFactorsPlotsGen();
    myQCDFactors.CountingPlotsGen();
    return 0;
  }
  else if( RunMode == "PredMCOnly" )
  {
    LoopQCDPred      ( myQCDFactors, myQCDSampleWeight, RunMode );
    return 0;
  }
  else if( RunMode == "PredDataOnly" )
  {
    LoopQCDPred      ( myQCDFactors, myDataSampleWeight, RunMode );
    return 0;
  }
  else if( RunMode == "ExpMCPredMC" )
  {
    LoopQCDExpTfactor( myQCDFactors, myQCDSampleWeight );
    LoopQCDPred      ( myQCDFactors, myQCDSampleWeight, RunMode );
    myQCDFactors.TFactorsPlotsGen();
    myQCDFactors.CountingPlotsGen();
    myQCDFactors.printSBInfo();
    return 0;
  }
  else if( RunMode == "ExpMCPredData" )
  {
    LoopQCDExpTfactor( myQCDFactors, myQCDSampleWeight );
    LoopQCDPred      ( myQCDFactors, myDataSampleWeight, RunMode );
    myQCDFactors.TFactorsPlotsGen();
    myQCDFactors.CountingPlotsGen();
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
  else
  {
    std::cout << "Invalide RunMode!!" << std::endl;
    return 0;
  }

  return 0;
}
