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
        bool isLL = tr.getVar<bool>("isLL");

        if( passLeptVeto && ( passdPhis) ){ myLLHadTauFactors.SR_dphi_ll_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
        if( passLeptVeto && (!passdPhis) ){ myLLHadTauFactors.SR_invdphi_ll_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
        if( (nElectrons==0) && (nMuons == 1) && ( passdPhis) ){ myLLHadTauFactors.CR_dphi_ll_singleMu_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
        if( (nElectrons==0) && (nMuons == 1) && (!passdPhis) ){ myLLHadTauFactors.CR_invdphi_ll_singleMu_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
        if( (nElectrons==1) && (nMuons == 0) && ( passdPhis) ){ myLLHadTauFactors.CR_dphi_ll_singleEl_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
        if( (nElectrons==1) && (nMuons == 0) && (!passdPhis) ){ myLLHadTauFactors.CR_invdphi_ll_singleEl_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
        if( passLeptVeto && ( passdPhis) ){ myLLHadTauFactors.SR_dphi_hadtau_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
        if( passLeptVeto && (!passdPhis) ){ myLLHadTauFactors.SR_invdphi_hadtau_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
        if( (nElectrons==0) && (nMuons == 1) && ( passdPhis) ){ myLLHadTauFactors.CR_dphi_hadtau_singleMu_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
        if( (nElectrons==0) && (nMuons == 1) && (!passdPhis) ){ myLLHadTauFactors.CR_invdphi_hadtau_singleMu_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
        if( (nElectrons==1) && (nMuons == 0) && ( passdPhis) ){ myLLHadTauFactors.CR_dphi_hadtau_singleEl_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
        if( (nElectrons==1) && (nMuons == 0) && (!passdPhis) ){ myLLHadTauFactors.CR_invdphi_hadtau_singleEl_MC_sb[searchbin_id]+=thisweight*ISRCorr*BTagCorr; }
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


        }
        else
        {
          double ISRCorr = tr.getVar<double>("ISRCorr");
          double BTagCorr = tr.getVar<double>("BTagCorr");
        }



      }
    }//end of inner loop
  }//end of QCD Samples loop

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
  std::string inputFileList_LLHadTauMC = argv[2];
  std::string inputFileList_Data = argv[3];
 
  std::cout << "The valid run modes are: CalLLHadTau, PredDataLLHadTau" << std::endl;
  std::cout << "The run mode we have right now is: " << RunMode << std::endl;
  //myTriggerEff.SelfTest();
  LLHadTauFactors myLLHadTauFactors;

  double TTbar_SingleLept_BR = 0.43930872; // 2*W_Lept_BR*(1-W_Lept_BR)
  double TTbar_DiLept_BR = 0.10614564; // W_Lept_BR^2
  //sample needed in the prediction loop
  QCDSampleWeight myLLHadTauMCSampleWeight;
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_TTJets_DiLept"             ,         831.76*TTbar_DiLept_BR, 30444678, LUMI, 1, inputFileList_LLHadTauMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromT_"   , 831.76*0.5*TTbar_SingleLept_BR, 61901450, LUMI, 1, inputFileList_LLHadTauMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromTbar_", 831.76*0.5*TTbar_SingleLept_BR, 59860282, LUMI, 1, inputFileList_LLHadTauMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_ST_tW_top"                 ,                           35.6,  6774350, LUMI, 1, inputFileList_LLHadTauMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_ST_tW_antitop"             ,                           35.6,  6933094, LUMI, 1, inputFileList_LLHadTauMC.c_str() );
  //be careful!! WJets and ZJets samples have some tricky part, need to understand!
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-200To400"   ,   359.7,      38867206, LUMI, 1.21, inputFileList_LLHadTauMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-400To600"   ,   48.91,       7759701, LUMI, 1.21, inputFileList_LLHadTauMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-600To800"   ,   12.05,      17494743, LUMI, 1.21, inputFileList_LLHadTauMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-800To1200"  ,   5.501,       7745467, LUMI, 1.21, inputFileList_LLHadTauMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-1200To2500" ,   1.329,       6801534, LUMI, 1.21, inputFileList_LLHadTauMC.c_str() );
  myLLHadTauMCSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-2500ToInf"  , 0.03216,       2637821, LUMI, 1.21, inputFileList_LLHadTauMC.c_str() );

  //sample needed in the basic check loop
  QCDSampleWeight myLLHadTauDataSampleWeight;
  myLLHadTauDataSampleWeight.QCDSampleInfo_push_back( "MET", 1, 1, LUMI, 1, inputFileList_Data.c_str() );

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
  else
  {
    std::cout << "Invalide RunMode!!" << std::endl;
    return 0;
  }

  return 0;
}
