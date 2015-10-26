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
#include "TH1F.h"
#include "TH1D.h"
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

using namespace std;

int main(int argc, char* argv[])
{

  if (argc < 2)
  {
    std::cerr <<"Please give 2 arguments " << "runList " << " " << "outputFileName" << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./QCD runlist_QCD.txt test.root" << std::endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName   = argv[2];

  //clock to monitor the run time
  size_t t0 = clock();
  //define my QCDFactors class to stroe counts and Translation factors
  QCDFactors myQCDFactors;
  //define my histgram class
  BaseHistgram myBaseHistgram;
  myBaseHistgram.BookHistgram(outFileName);

  QCDSampleWeight myQCDSampleWeight;
  myQCDSampleWeight.FillQCDSampleInfos(inputFileList);

  //use class BaselineVessel in the SusyAnaTools/Tools/baselineDef.h file
  const std::string spec = "QCD";
  myBaselineVessel = new BaselineVessel(spec);

  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  int i = 0;  

  double pybjets, pnbjets, pydphis, pndphis;

  std::cout << "First Loop start(Factorization and Expectation): " << std::endl;

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

      bool passTagger = tr.getVar<bool>("passTagger"+spec);
      bool passBJets = tr.getVar<bool>("passBJets"+spec);

      std::vector<double> dPhiVec = tr.getVec<double>("dPhiVec"+spec);
      
      //checking plots for full QCD samples
      //filling HT variables for quick weight check
      (myBaseHistgram.h_b_all_HT)->Fill(ht,thisweight);

      int metbin_number = Set_metbin_number(met);
      int njetsbin_number = Set_nbjetsbin_number(nbottomjets);
      int mt2bin_number = Set_mt2bin_number(MT2);

      bool passBaselineQCD = tr.getVar<bool>("passBaseline"+spec);
      bool passdPhis = tr.getVar<bool>("passdPhis"+spec);
      bool passnJets = tr.getVar<bool>("passnJets"+spec);
      
      if( passnJets )
      { 
        if( passBJets && passTagger ) pybjets+=thisweight;
        else pnbjets+=thisweight;
        if( passdPhis )  pydphis+=thisweight;
        else pndphis+=thisweight; 
      }
      //if( passBaselineQCD ) { std::cout << passBaselineQCD << std::endl; }
      
      //normal baseline
      bool passBaseline = false;
      passBaseline = passBaselineQCD; 
                     //&& passdPhis; 
                     //&& passTagger
                     //&& passBJets;
    
      if (
          passBaseline
         )
      {
        if ( passTagger && passBJets )
        {
          (myBaseHistgram.h_b_mt2_ybyt)->Fill(MT2,thisweight);
          (myBaseHistgram.h_b_met_ybyt)->Fill(met,thisweight);
          (myBaseHistgram.h_b_dphi0_ybyt)->Fill(dPhiVec.at(0),thisweight);
          (myBaseHistgram.h_b_dphi1_ybyt)->Fill(dPhiVec.at(1),thisweight);
          (myBaseHistgram.h_b_dphi2_ybyt)->Fill(dPhiVec.at(2),thisweight);
        }

        if ( (!passTagger) && (!passBJets) )
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
 
          if ( passTagger && passBJets )
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
                                   //&& passTagger
                                   //&& passBJets;

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

  std::cout << pybjets << ", " << pnbjets << ", "<< pydphis << ", "<< pndphis << std::endl;
  myQCDFactors.NumbertoTFactor();
  //myQCDFactors.TFactorFit();

  std::cout << "Second Loop start(Prediction): " << std::endl;
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
      bool passBJets = tr.getVar<bool>("passBJets"+spec);
      bool passTagger = tr.getVar<bool>("passTagger"+spec);
      bool passBaseline_dPhisInverted = false;

      passBaseline_dPhisInverted = passBaselineQCD && passBJets && passTagger && (!passdPhis);

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

  myQCDFactors.printQCDFactorInfo();
  myQCDFactors.printQCDClosure(myBaseHistgram);
  myQCDFactors.TFactorsPlotsGen();
  myQCDFactors.CountingPlotsGen();

  //write into histgram
  (myBaseHistgram.oFile)->Write();
  return 0;
}

void QCDFactors::NumbertoTFactor()
{
  //value calculation
  for(int i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(int j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      for(int k_cal = 0 ; k_cal < QCD_BINS ; k_cal++)
      {
         nQCDNormal_all[i_cal][j_cal] += nQCDNormal[k_cal][i_cal][j_cal];
         nQCDInverted_all[i_cal][j_cal] += nQCDInverted[k_cal][i_cal][j_cal];
         MET_sum_all[i_cal][j_cal] += MET_sum[k_cal][i_cal][j_cal];
         MET_sum_weight_all[i_cal][j_cal] += MET_sum_weight[k_cal][i_cal][j_cal];
      }
      QCDTFactor[i_cal][j_cal] = nQCDNormal_all[i_cal][j_cal]/nQCDInverted_all[i_cal][j_cal];
      MET_mean[i_cal][j_cal] = MET_sum_all[i_cal][j_cal]/MET_sum_weight_all[i_cal][j_cal];
    }
  }

  //TFactor uncertainty calculation
  for(int i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(int j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      for(int k_cal = 0 ; k_cal < QCD_BINS ; k_cal++)
      {
        nQCDNormal_all_err[i_cal][j_cal] += nQCDNormal_MC[k_cal][i_cal][j_cal] * QCDWeights[k_cal] * QCDWeights[k_cal] ;
        nQCDInverted_all_err[i_cal][j_cal] += nQCDInverted_MC[k_cal][i_cal][j_cal] * QCDWeights[k_cal] * QCDWeights[k_cal];
      }
      nQCDNormal_all_err[i_cal][j_cal] = std::sqrt( nQCDNormal_all_err[i_cal][j_cal] );
      nQCDInverted_all_err[i_cal][j_cal] = std::sqrt( nQCDInverted_all_err[i_cal][j_cal] );
      QCDTFactor_err[i_cal][j_cal] = QCDTFactor[i_cal][j_cal] * std::sqrt( nQCDNormal_all_err[i_cal][j_cal]*nQCDNormal_all_err[i_cal][j_cal]/nQCDNormal_all[i_cal][j_cal]/nQCDNormal_all[i_cal][j_cal] + nQCDInverted_all_err[i_cal][j_cal]*nQCDInverted_all_err[i_cal][j_cal]/nQCDInverted_all[i_cal][j_cal]/nQCDInverted_all[i_cal][j_cal] );
    }
  }

  //Expected QCD uncertainty calculation
  for(int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++)
  {
    for(int j_cal = 0 ; j_cal < QCD_BINS ; j_cal++)
    {
      nQCD_exp_sb_err[i_cal] += nQCD_exp_sb_MC[j_cal][i_cal] * QCDWeights[j_cal] * QCDWeights[j_cal];
    }
    nQCD_exp_sb_err[i_cal] = std::sqrt( nQCD_exp_sb_err[i_cal] );
  }
}

void QCDFactors::printQCDFactorInfo()
{
  int i_cal,j_cal,k_cal;

  std::cout << "Counting Normal MC: " << std::endl;
  for( i_cal=0 ; i_cal < QCD_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MET_BINS ; j_cal++)
    {
      for(k_cal = 0 ; k_cal < MT2_BINS ; k_cal++)
      {
        std::cout << "QCD Files:" << i_cal << ", METBin:" << j_cal << ",MT2Bin:" << k_cal << "; :" << nQCDNormal_MC[i_cal][j_cal][k_cal] << std::endl;
      }
    }
  }

  std::cout << "Counting Normal: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      std::cout << "METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << nQCDNormal_all[i_cal][j_cal] << "(" << nQCDNormal_all_err[i_cal][j_cal] << ")"<< std::endl;
    }
  }

  std::cout << "Counting Inverted MC: " << std::endl;
  for( i_cal=0 ; i_cal < QCD_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MET_BINS ; j_cal++)
    {
      for(k_cal = 0 ; k_cal < MT2_BINS ; k_cal++)
      {
        std::cout << "QCD Files:" << i_cal << ", METBin:" << j_cal << ",MT2Bin:" << k_cal << "; :" << nQCDInverted_MC[i_cal][j_cal][k_cal] << std::endl;
      }
    }
  }

  std::cout << "Counting Inverted: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      std::cout << "METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << nQCDInverted_all[i_cal][j_cal] << "(" << nQCDInverted_all_err[i_cal][j_cal] << ")"<< std::endl;
    }
  }

  std::cout << "Translation Factors: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      std::cout << "METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << QCDTFactor[i_cal][j_cal] << "(" << QCDTFactor_err[i_cal][j_cal] << ")"<< std::endl;
    }
  }

  /*
  std::cout << "Mean MET: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    std::cout << MET_mean[i_cal][j_cal] <<"(" << MET_mean_err[i_cal][j_cal] << ")" << " , ";
    if( i_cal == MET_BINS-1 )
    {
      std::cout << std::endl;
    }
  }
  */
  std::cout << "#QCD in Search Bins: " << std::endl;
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    std::cout << "Search Bin Id:" << i_cal << "; Exp: " << nQCD_exp_sb[i_cal] << "(" << nQCD_exp_sb_err[i_cal] << "); Pred: " << nQCD_pred_sb[i_cal] << "(" << nQCD_pred_sb_err[i_cal] << "); (exp - pred)/pred: " << (nQCD_exp_sb[i_cal] - nQCD_pred_sb[i_cal])/nQCD_pred_sb[i_cal] << std::endl;
  }
}

void QCDFactors::printQCDClosure(BaseHistgram& myBaseHistgram)
{
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    myBaseHistgram.h_pred_sb->SetBinContent( i_cal+1 , nQCD_pred_sb[i_cal] );
    myBaseHistgram.h_pred_sb->SetBinError( i_cal+1 , nQCD_pred_sb_err[i_cal] );
    myBaseHistgram.h_exp_sb->SetBinContent( i_cal+1 , nQCD_exp_sb[i_cal] );
    myBaseHistgram.h_exp_sb->SetBinError( i_cal+1 , nQCD_exp_sb_err[i_cal] );
  }
  return ;
}

void QCDFactors::TFactorsPlotsGen()
{
  const std::string titre="CMS Simulation 2015, #sqrt{s} = 13 TeV";

  TCanvas *c = new TCanvas("c", "c",0,51,1920,1004);
  c->SetFillColor(0);
  c->cd();

  double metbins[MET_BINS+1] = {175.0,200.0,350.0,650.0};
  //double ybins[MT2_BINS+1] = {1.0,2.0,5.0};
  double mt2bins[MT2_BINS+1] = {200.0,300.0,400.0,500.0};

  TH2D *tfactors2d  = new TH2D("tfactors","TFactors",MET_BINS,metbins,MT2_BINS,mt2bins);

  int i_cal;
  int j_cal;

  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      tfactors2d->SetBinContent( i_cal+1 , j_cal+1, QCDTFactor[i_cal][j_cal] );
      tfactors2d->SetBinError( i_cal+1 , j_cal+1, QCDTFactor_err[i_cal][j_cal] );
    }
  }

  tfactors2d->SetTitle("");
  tfactors2d->SetXTitle("MET [GeV]");
  tfactors2d->SetYTitle("MT2 [GeV]");
  //tfactors2d->SetYTitle("NbJets");
  tfactors2d->SetStats(0);

  gStyle->SetPaintTextFormat("1.2f");
  tfactors2d->Draw("colztexte");

  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);
  title->Draw("same");

  c->SaveAs( "_tfactors2d.png" );
  c->SaveAs( "_tfactors2d.pdf" );
  c->SaveAs( "_tfactors2d.C" );
  
  return ;
}

void QCDFactors::CountingPlotsGen()
{
  const std::string titre="CMS Simulation 2015, 3fb-1, #sqrt{s} = 13 TeV";
  double metbins[MET_BINS+1] = {175.0,200.0,350.0,650.0};
  //double ybins[MT2_BINS+1] = {1.0,2.0,5.0};  
  double mt2bins[MT2_BINS+1] = {200.0,300.0,400.0,500.0};

  TH2D *countNormal_MC  = new TH2D("countNormal_MC","countNormal_MC",MET_BINS,metbins,MT2_BINS,mt2bins);
  TH2D *countNormal  = new TH2D("countNormal","countNormal",MET_BINS,metbins,MT2_BINS,mt2bins);
  TH2D *countInverted_MC  = new TH2D("countInverted_MC","countInverted_MC",MET_BINS,metbins,MT2_BINS,mt2bins);
  TH2D *countInverted  = new TH2D("countInverted","countInverted",MET_BINS,metbins,MT2_BINS,mt2bins);
      
  double nQCDNormal_MC_all[MET_BINS][MT2_BINS] = {{0}}, nQCDInverted_MC_all[MET_BINS][MT2_BINS] = {{0}};

  int i_cal;
  int j_cal;

  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      for(int tmp = 0 ; tmp < QCD_BINS ; tmp++)
      {
        nQCDNormal_MC_all[i_cal][j_cal] +=nQCDNormal_MC[tmp][i_cal][j_cal];
        nQCDInverted_MC_all[i_cal][j_cal] +=nQCDInverted_MC[tmp][i_cal][j_cal];
      }

      countNormal_MC->SetBinContent( i_cal+1 , j_cal+1, nQCDNormal_MC_all[i_cal][j_cal] );
      countNormal->SetBinContent( i_cal+1 , j_cal+1, nQCDNormal_all[i_cal][j_cal] );
      countNormal->SetBinError( i_cal+1 , j_cal+1, nQCDNormal_all_err[i_cal][j_cal] );

      countInverted_MC->SetBinContent( i_cal+1 , j_cal+1, nQCDInverted_MC_all[i_cal][j_cal] );
      countInverted->SetBinContent( i_cal+1 , j_cal+1, nQCDInverted_all[i_cal][j_cal] );
      countInverted->SetBinError( i_cal+1 , j_cal+1, nQCDInverted_all_err[i_cal][j_cal] );
    }
  }

  countNormal_MC->SetTitle("QCD Signal MC");
  countNormal_MC->SetXTitle("MET [GeV]");
  countNormal_MC->SetYTitle("MT2 [GeV]");
  countNormal_MC->SetStats(0);
  countNormal->SetTitle("QCD Signal Normalized");
  countNormal->SetXTitle("MET [GeV]");
  countNormal->SetYTitle("MT2 [GeV]");
  countNormal->SetStats(0);
  countInverted_MC->SetTitle("QCD Inverted DeltaPhi MC");
  countInverted_MC->SetXTitle("MET [GeV]");
  countInverted_MC->SetYTitle("MT2 [GeV]");
  countInverted_MC->SetStats(0);
  countInverted->SetTitle("QCD Inverted DeltaPhi Normalized");
  countInverted->SetXTitle("MET [GeV]");
  countInverted->SetYTitle("MT2 [GeV]");
  countInverted->SetStats(0);

  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);

  TCanvas *c = new TCanvas("c", "c",0,51,1920,1004);
  c->Divide(2,2);
  c->SetFillColor(0);
  gStyle->SetPaintTextFormat("1.2f");
  
  c->cd(1);
  countNormal_MC->Draw("colztexte");
  title->Draw("same");

  c->cd(2);
  countNormal->Draw("colztexte");
  title->Draw("same");

  c->cd(3);
  countInverted_MC->Draw("colztexte");
  title->Draw("same");

  c->cd(4);
  countInverted->Draw("colztexte");
  title->Draw("same");

  c->SaveAs( "_Allcount2d.png" );
  c->SaveAs( "_Allcount2d.pdf" );
  c->SaveAs( "_Allcount2d.C" );

  return ;
}
