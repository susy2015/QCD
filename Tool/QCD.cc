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
#include "QCDReWeighting.h"

void LoopQCDExpTfactor( QCDFactors& myQCDFactors, BaseHistgram& myBaseHistgram, QCDSampleWeight& myQCDSampleWeight )
{
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
    std::cout << "Weight " << thisweight << std::endl;

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
      double ht = tr.getVar<double>("ht");
      double mht = tr.getVar<double>("mht");

      std::vector<double> dPhiVec = tr.getVec<double>("dPhiVec"+spec);
      
      //checking plots for full QCD samples
      //filling HT variables for quick weight check
      (myBaseHistgram.h_b_all_HT)->Fill(ht,thisweight);

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
    
      if (
          passBaselineQCD
         )
      {
        if ( passBJets )
        {
          (myBaseHistgram.h_b_mt2_ybyt)->Fill(MT2,thisweight);
          (myBaseHistgram.h_b_met_ybyt)->Fill(met,thisweight);
          (myBaseHistgram.h_b_dphi0_ybyt)->Fill(dPhiVec.at(0),thisweight);
          (myBaseHistgram.h_b_dphi1_ybyt)->Fill(dPhiVec.at(1),thisweight);
          (myBaseHistgram.h_b_dphi2_ybyt)->Fill(dPhiVec.at(2),thisweight);
        }

        if ( (!passBJets) )
        {
          (myBaseHistgram.h_b_mt2_nbnt)->Fill(MT2,thisweight);
          (myBaseHistgram.h_b_met_nbnt)->Fill(met,thisweight);
          (myBaseHistgram.h_b_dphi0_nbnt)->Fill(dPhiVec.at(0),thisweight);
          (myBaseHistgram.h_b_dphi1_nbnt)->Fill(dPhiVec.at(1),thisweight);
          (myBaseHistgram.h_b_dphi2_nbnt)->Fill(dPhiVec.at(2),thisweight);
        }

        if ( passdPhis )
        {
          myQCDFactors.nQCDNormal_MC[i][metbin_number][mt2bin_number]++;
          myQCDFactors.nQCDNormal[i][metbin_number][mt2bin_number]+=thisweight;
 
          if ( passBJets )
          {
            (myBaseHistgram.h_exp_met)->Fill(met,thisweight);
            (myBaseHistgram.h_exp_njets)->Fill(njets30,thisweight);
            (myBaseHistgram.h_exp_mt2)->Fill(MT2,thisweight);
            (myBaseHistgram.h_exp_ht)->Fill(ht,thisweight);
            (myBaseHistgram.h_exp_mht)->Fill(mht,thisweight);
            (myBaseHistgram.h_exp_ntopjets)->Fill(ntopjets,thisweight);
            (myBaseHistgram.h_exp_nbjets)->Fill(nbottomjets,thisweight);
          
            int searchbin_id = find_Binning_Index( nbottomjets , ntopjets , MT2, met );
            if( searchbin_id >= 0 )
            {
              myQCDFactors.nQCD_exp_sb[searchbin_id] += thisweight;
              myQCDFactors.nQCD_exp_sb_MC[i][searchbin_id]++;
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
        myQCDFactors.nQCDInverted[i][metbin_number][mt2bin_number]+=thisweight;
        myQCDFactors.MET_sum[i][metbin_number][mt2bin_number] = myQCDFactors.MET_sum[i][metbin_number][mt2bin_number] + met * thisweight;
        myQCDFactors.MET_sum_weight[i][metbin_number][mt2bin_number] = myQCDFactors.MET_sum_weight[i][metbin_number][mt2bin_number] + thisweight;

        (myBaseHistgram.h_inverted_met)->Fill(met,thisweight);
        (myBaseHistgram.h_inverted_njets)->Fill(njets30,thisweight);
        (myBaseHistgram.h_inverted_mt2)->Fill(MT2,thisweight);
        (myBaseHistgram.h_inverted_ht)->Fill(ht,thisweight);
        (myBaseHistgram.h_inverted_mht)->Fill(mht,thisweight);
        (myBaseHistgram.h_inverted_ntopjets)->Fill(ntopjets,thisweight);
        (myBaseHistgram.h_inverted_nbjets)->Fill(nbottomjets,thisweight);
      }
    }//end of inner loop
    i++;
  }//end of QCD Samples loop

  myQCDFactors.NumbertoTFactor();
  myQCDFactors.printQCDFactorInfo();
  myQCDFactors.printQCDClosureExp(myBaseHistgram);
  myQCDFactors.TFactorsPlotsGen();
  myQCDFactors.CountingPlotsGen();

  return ;
}

void LoopQCDPred( QCDFactors& myQCDFactors, BaseHistgram& myBaseHistgram, QCDSampleWeight& myQCDSampleWeight )
{
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
    std::cout << "Weight " << thisweight << std::endl;

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
      double ht = tr.getVar<double>("ht");
      double mht = tr.getVar<double>("mht");

      //if( met < 175 ) continue;
      int metbin_number = Set_metbin_number(met);
      int njetsbin_number = Set_nbjetsbin_number(nbottomjets);
      int mt2bin_number = Set_mt2bin_number(MT2);

      bool passBaselineQCD = tr.getVar<bool>("passBaseline"+spec);
      bool passdPhis = tr.getVar<bool>("passdPhis"+spec);
      bool passBaseline_dPhisInverted = false;

      passBaseline_dPhisInverted = passBaselineQCD && (!passdPhis);

      if (passBaseline_dPhisInverted)
      {
        double predweight = thisweight * myQCDFactors.QCDTFactor[metbin_number][mt2bin_number];
        double predweight_err = thisweight * myQCDFactors.QCDTFactor_err[metbin_number][mt2bin_number];
        (myBaseHistgram.h_pred_met)->Fill(met,predweight);
        (myBaseHistgram.h_pred_njets)->Fill(njets30,predweight);
        (myBaseHistgram.h_pred_mt2)->Fill(MT2,predweight);
        (myBaseHistgram.h_pred_ht)->Fill(ht,predweight);
        (myBaseHistgram.h_pred_mht)->Fill(mht,predweight);
        (myBaseHistgram.h_pred_ntopjets)->Fill(ntopjets,predweight);
        (myBaseHistgram.h_pred_nbjets)->Fill(nbottomjets,predweight);

        int searchbin_id = find_Binning_Index( nbottomjets , ntopjets , MT2, met );
        if( searchbin_id >= 0 )
        {
          //std::cout << predweight << std::endl;
          myQCDFactors.nQCD_pred_sb[searchbin_id] += (predweight);
          //myQCDFactors.nQCD_pred_sb_err[searchbin_id] += (predweight_err);
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop

  myQCDFactors.printQCDClosureExp(myBaseHistgram);
  
  return ;
}

int main(int argc, char* argv[])
{

  if (argc < 2)
  {
    std::cerr <<"Please give 2 arguments " << "runList " << " " << "outputFileName" << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./QCD runlist_QCD.txt test.root" << std::endl;
    return -1;
  }
  const char *inputFileList_QCDMC = argv[1];
  const char *outFileName   = argv[2];

  //define my QCDFactors class to stroe counts and Translation factors
  QCDFactors myQCDFactors;
  //define my histgram class
  BaseHistgram myBaseHistgram;
  myBaseHistgram.BookHistgram(outFileName);

  QCDSampleWeight myQCDSampleWeight;
  myQCDSampleWeight.FillQCDSampleInfos(inputFileList_QCDMC);

  LoopQCDExpTfactor( myQCDFactors, myBaseHistgram, myQCDSampleWeight );
  LoopQCDPred      ( myQCDFactors, myBaseHistgram, myQCDSampleWeight );

  //write into histgram
  (myBaseHistgram.oFile)->Write();
  return 0;
}
