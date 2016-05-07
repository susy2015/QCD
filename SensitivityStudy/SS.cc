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
#include "SS.h"

//const double Scale = 591.5/2153.736;

void LoopSSMuCS( SSSampleWeight& mySSSampleWeight )
{
  SSCSHistgram mySSCSHistgram;
  mySSCSHistgram.BookHistgram( (dir_out + "SSMuCS.root").c_str() );
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<SSSampleInfo>::iterator iter_SSSampleInfos;
  //use class BaselineVessel in the SusyAnaTools/Tools/baselineDef.h file
  const std::string spec = "lostlept";
  myBaselineVessel = new BaselineVessel(spec);

  std::cout << "Let's do sensitivity study: " << std::endl;
  
  for(iter_SSSampleInfos = mySSSampleWeight.SSSampleInfos.begin(); iter_SSSampleInfos != mySSSampleWeight.SSSampleInfos.end(); iter_SSSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_SSSampleInfos).chain);
    //initialize the type3Ptr defined in the customize.h
    AnaFunctions::prepareTopTagger();
    //The passBaseline is registered here
    tr.registerFunction(&mypassBaselineFunc);

    double thisweight = (*iter_SSSampleInfos).weight;
    std::cout <<"Sample Type: "<< (*iter_SSSampleInfos).Tag << "; Weight: " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      int nbotjets = tr.getVar<int>("cntCSVS"+spec);
      double mt2 = tr.getVar<double>("best_had_brJet_MT2"+spec);
      double met = tr.getVar<double>("met");

			int ntopjetsbin_number = Set_ntopjetsbin_number(ntopjets);
      int nbotjetsbin_number = Set_nbotjetsbin_number(nbotjets);
      int metbin_number = Set_metbin_number(met);
      int mt2bin_number = Set_mt2bin_number(mt2);

      bool passBaselineLL = tr.getVar<bool>("passBaseline"+spec);

      if (passBaselineLL)
      {
        if(ntopjets>=ntopbins_edge[NTOPJETS_BINS]) ntopjets = ntopbins_edge[NTOPJETS_BINS-1];
        if(nbotjets>=nbotbins_edge[NBOTJETS_BINS]) nbotjets = nbotbins_edge[NBOTJETS_BINS-1];
        if(met>=metbins_edge[MET_BINS]) met = (metbins_edge[MET_BINS-1]+metbins_edge[MET_BINS])/2;
        if(mt2>=mt2bins_edge[MT2_BINS]) mt2 = (mt2bins_edge[MT2_BINS-1]+mt2bins_edge[MT2_BINS])/2;

				//int searchbin_id = find_Binning_Index( nbotjets, ntopjets, mt2, met );
        //Get electron and muon for LL study
        int nElectrons = tr.getVar<int>("nElectrons_CUT"+spec);
        int nMuons = tr.getVar<int>("nMuons_CUT"+spec);
 				
        if( ((*iter_SSSampleInfos).Tag).find("TTJets") != std::string::npos )
			  {
          //Counting the muon control sample
					if (nElectrons == 0 && nMuons == 1)
          {
            (mySSCSHistgram.h_ss_ntopnbot_MC_MuCS)->Fill(ntopjets,nbotjets,thisweight);
            (mySSCSHistgram.h_ss_metmt2_MC_MuCS[ntopjetsbin_number][nbotjetsbin_number])->Fill(met,mt2,thisweight);
            /*
            if( ntopjets >= 3 && nbotjets>=3 )
            {
              std::cout << "NT ,NB :" << ntopjets << "," << nbotjets << std::endl;
              std::cout << "MET,MT2:" << met << "," << mt2 << std::endl;
            }
            */
          }
          if (nElectrons == 1 && nMuons == 0)
          {
            (mySSCSHistgram.h_ss_ntopnbot_MC_ElCS)->Fill(ntopjets,nbotjets,thisweight);
            (mySSCSHistgram.h_ss_metmt2_MC_ElCS[ntopjetsbin_number][nbotjetsbin_number])->Fill(met,mt2,thisweight);
          }
				}
      }
    }//end of inner loop
  }//end of Samples loop

  (mySSCSHistgram.oFile)->Write();
  (mySSCSHistgram.oFile)->Close();
  return ;
}

void LoopSSAllMC( SSSampleWeight& mySSSampleWeight )
{
  SSHistgram mySSHistgram;
  mySSHistgram.BookHistgram( (dir_out + "SSAllMC.root").c_str() );
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<SSSampleInfo>::iterator iter_SSSampleInfos;
  //use class BaselineVessel in the SusyAnaTools/Tools/baselineDef.h file
  const std::string spec = "";
  myBaselineVessel = new BaselineVessel(spec);

  std::cout << "Let's do sensitivity study: " << std::endl;
  
  for(iter_SSSampleInfos = mySSSampleWeight.SSSampleInfos.begin(); iter_SSSampleInfos != mySSSampleWeight.SSSampleInfos.end(); iter_SSSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_SSSampleInfos).chain);
    //initialize the type3Ptr defined in the customize.h
    AnaFunctions::prepareTopTagger();
    //The passBaseline is registered here
    tr.registerFunction(&mypassBaselineFunc);

    double thisweight = (*iter_SSSampleInfos).weight;
    std::cout <<"Sample Type: "<< (*iter_SSSampleInfos).Tag << "; Weight: " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      int nbotjets = tr.getVar<int>("cntCSVS"+spec);
      double mt2 = tr.getVar<double>("best_had_brJet_MT2"+spec);
      double met = tr.getVar<double>("met");
      //closure plots variables
      //int njets30 = tr.getVar<int>("cntNJetsPt30Eta24"+spec);
      //int njets50 = tr.getVar<int>("cntNJetsPt50Eta24"+spec);
      //double ht = tr.getVar<double>("HT"+spec);

			int ntopjetsbin_number = Set_ntopjetsbin_number(ntopjets);
      int nbotjetsbin_number = Set_nbotjetsbin_number(nbotjets);
      int metbin_number = Set_metbin_number(met);
      int mt2bin_number = Set_mt2bin_number(mt2);

      bool passBaseline = tr.getVar<bool>("passBaseline"+spec);

      if (passBaseline)
      {
        if(ntopjets>=ntopbins_edge[NTOPJETS_BINS]) ntopjets = ntopbins_edge[NTOPJETS_BINS-1];
        if(nbotjets>=nbotbins_edge[NBOTJETS_BINS]) nbotjets = nbotbins_edge[NBOTJETS_BINS-1];
        if(met>=metbins_edge[MET_BINS]) met = (metbins_edge[MET_BINS-1]+metbins_edge[MET_BINS])/2;
        if(mt2>=mt2bins_edge[MT2_BINS]) mt2 = (mt2bins_edge[MT2_BINS-1]+mt2bins_edge[MT2_BINS])/2;

				//int searchbin_id = find_Binning_Index( nbotjets, ntopjets, mt2, met );
        //Get electron and muon for LL study
        if( ((*iter_SSSampleInfos).Tag).find("T1tttt_mGluino-1200_mLSP-800") != std::string::npos )
        {
          (mySSHistgram.h_ss_ntopnbot_MC_T1tttt_mGluino1200_mLSP800)->Fill(ntopjets,nbotjets,thisweight);
          (mySSHistgram.h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800[ntopjetsbin_number][nbotjetsbin_number])->Fill(met,mt2,thisweight);
        }
				else if( ((*iter_SSSampleInfos).Tag).find("T1tttt_mGluino-1500_mLSP-100") != std::string::npos )
        {
          (mySSHistgram.h_ss_ntopnbot_MC_T1tttt_mGluino1500_mLSP100)->Fill(ntopjets,nbotjets,thisweight);
          (mySSHistgram.h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100[ntopjetsbin_number][nbotjetsbin_number])->Fill(met,mt2,thisweight);
        }
				else if( ((*iter_SSSampleInfos).Tag).find("T2tt_mStop-500_mLSP-325") != std::string::npos )
        {
          (mySSHistgram.h_ss_ntopnbot_MC_T2tt_mStop500_mLSP325)->Fill(ntopjets,nbotjets,thisweight);
          (mySSHistgram.h_ss_metmt2_MC_T2tt_mStop500_mLSP325[ntopjetsbin_number][nbotjetsbin_number])->Fill(met,mt2,thisweight);
        }
				else if( ((*iter_SSSampleInfos).Tag).find("T2tt_mStop-850_mLSP-100") != std::string::npos )
        {
          (mySSHistgram.h_ss_ntopnbot_MC_T2tt_mStop850_mLSP100)->Fill(ntopjets,nbotjets,thisweight);
          (mySSHistgram.h_ss_metmt2_MC_T2tt_mStop850_mLSP100[ntopjetsbin_number][nbotjetsbin_number])->Fill(met,mt2,thisweight);
        }
        else
        {
          (mySSHistgram.h_ss_ntopnbot_MC_AllBG)->Fill(ntopjets,nbotjets,thisweight);
          (mySSHistgram.h_ss_metmt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number])->Fill(met,mt2,thisweight);
        } 
      }
    }//end of inner loop
  }//end of Samples loop

  (mySSHistgram.oFile)->Write();
  (mySSHistgram.oFile)->Close();
  return ;
}

int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cerr <<"Please give at least 3 arguments " << "RunMode " << " " << "runListMCBG " << " " << "runListMCSG" << "" << "runListMCMuCS" << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./QCD RunMode runlist_QCDMC.txt runlist_Data.txt" << std::endl;
    return -1;
  }

  std::string RunMode = argv[1];
  std::string inputFileList_MC_BG = argv[2];
  std::string inputFileList_MC_SG = argv[3];
  std::string inputFileList_MuCS = argv[4];

  std::cout << "The valid run modes are: SS" << std::endl;
  std::cout << "The run mode we have right now is: " << RunMode << std::endl;

  //sample needed in the basic check loop
  SSSampleWeight mySSSampleWeightAllMC;
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "TTJets"                  , 831.76,      11339232, LUMI, 1, inputFileList_MC_BG.c_str() );
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "ST_tW_top"               ,   35.6,        995600, LUMI, 1, inputFileList_MC_BG.c_str() );
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "ST_tW_antitop"           ,   35.6,        988500, LUMI, 1, inputFileList_MC_BG.c_str() );
  //be careful!! WJets and ZJets samples have some tricky part, need to understand!
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "WJetsToLNu_HT-400To600"  ,  48.91,       1745914, LUMI, 1.21, inputFileList_MC_BG.c_str() );
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "WJetsToLNu_HT-600ToInf"  ,  18.77,       1039152, LUMI, 1.21, inputFileList_MC_BG.c_str() );
  
	mySSSampleWeightAllMC.SSSampleInfo_push_back( "ZJetsToNuNu_HT-400To600" ,  10.73,       1018882, LUMI, 1.23, inputFileList_MC_BG.c_str() );
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "ZJetsToNuNu_HT-600ToInf" ,  4.116,       1008333, LUMI, 1.23, inputFileList_MC_BG.c_str() );
  //Be careful! TTZ has negative weight issue!!
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "TTZToLLNuNu"             , 0.2529, 291495-106505, LUMI, 1, inputFileList_MC_BG.c_str() );
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "TTZToQQ"                 , 0.5297, 550599-199201, LUMI, 1, inputFileList_MC_BG.c_str() );  
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "TTWJetsToLNu"            , 0.2043, 191379-61529 , LUMI, 1, inputFileList_MC_BG.c_str() );
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "TTWJetsToQQ"             , 0.4062, 632147-201817, LUMI, 1, inputFileList_MC_BG.c_str() );

  mySSSampleWeightAllMC.SSSampleInfo_push_back( "QCD_HT500to700"  , 29370   , 19664159, LUMI, 1, inputFileList_MC_BG.c_str() );
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "QCD_HT700to1000" , 6524    , 15356448, LUMI, 1, inputFileList_MC_BG.c_str() );
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "QCD_HT1000to1500", 1064    ,  4963895, LUMI, 1, inputFileList_MC_BG.c_str() );
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "QCD_HT1500to2000", 121.5   ,  3868886, LUMI, 1, inputFileList_MC_BG.c_str() );
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "QCD_HT2000toInf" , 25.42   ,  1683349, LUMI, 1, inputFileList_MC_BG.c_str() );

  mySSSampleWeightAllMC.SSSampleInfo_push_back( "SMS-T1tttt_mGluino-1200_mLSP-800",  0.0856418,  147194, LUMI, 1, inputFileList_MC_SG.c_str() );
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "SMS-T1tttt_mGluino-1500_mLSP-100",  0.0141903,  103140, LUMI, 1, inputFileList_MC_SG.c_str() );
  mySSSampleWeightAllMC.SSSampleInfo_push_back( "SMS-T2tt_mStop-500_mLSP-325"     ,  0.51848  ,  388207, LUMI, 1, inputFileList_MC_SG.c_str() );
	mySSSampleWeightAllMC.SSSampleInfo_push_back( "SMS-T2tt_mStop-850_mLSP-100"     ,  0.0189612,  240685, LUMI, 1, inputFileList_MC_SG.c_str() );

  double TTbar_SingleLept_BR = 0.43930872; // 2*W_Lept_BR*(1-W_Lept_BR)
  double TTbar_DiLept_BR = 0.10614564; // W_Lept_BR^2
  SSSampleWeight mySSSampleWeightMuCS;
  mySSSampleWeightMuCS.SSSampleInfo_push_back( "TTJets_SingleLept", 831.76*0.5*TTbar_SingleLept_BR, 59816364+60144642, LUMI, 1, inputFileList_MuCS.c_str() );
  mySSSampleWeightMuCS.SSSampleInfo_push_back( "TTJets_DiLept"    , 831.76*TTbar_DiLept_BR        , 30498962         , LUMI, 1, inputFileList_MuCS.c_str() );

  if( RunMode == "SSMuCS" )
  {
    LoopSSMuCS( mySSSampleWeightMuCS );
    return 0;
  }
  else if( RunMode == "SSAllMC" )
  {
    LoopSSAllMC( mySSSampleWeightAllMC );
    return 0;
  }
  else
  {
    std::cout << "Invalide RunMode!!" << std::endl;
    return 0;
  }

  return 0;
}
