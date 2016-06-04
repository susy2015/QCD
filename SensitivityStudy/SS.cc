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
//                             NJets =      1        2       3        4        5        6       7      >=8
const double NJetRweightingFactor[8] = {0.926542,1.03995,0.919711,0.723581,0.869969,0.95682,0.584418,0.874059};

void LoopSSCS( SSSampleWeight& mySSSampleWeight )
{
  SSCSHistgram mySSCSHistgram;
  mySSCSHistgram.BookHistgram( (dir_out + "SSCS.root").c_str() );
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<SSSampleInfo>::iterator iter_SSSampleInfos;

  double mucs[NSB] = {0}, elcs[NSB]={0}, mucs_NMC[NSB] = {0}, elcs_NMC[NSB]={0};
  std::cout << "Let's do sensitivity study: " << std::endl;
  
  for(iter_SSSampleInfos = mySSSampleWeight.SSSampleInfos.begin(); iter_SSSampleInfos != mySSSampleWeight.SSSampleInfos.end(); iter_SSSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_SSSampleInfos).chain);

    double thisweight = (*iter_SSSampleInfos).weight;
    std::cout <<"Sample Type: "<< (*iter_SSSampleInfos).Tag << "; Weight: " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTop");
      int nbotjets = tr.getVar<int>("nBot");
      double mt2 = tr.getVar<double>("mt2");
      double met = tr.getVar<double>("met");

      int ntopjetsbin_number = mySBGeometry.GetTopID(ntopjets);
      int nbotjetsbin_number = mySBGeometry.GetBotID(nbotjets);
      //int metbin_number = Set_metbin_number(met);
      //int mt2bin_number = Set_mt2bin_number(mt2);

      int ij=ntopjetsbin_number*NBOTJETS_BINS+nbotjetsbin_number;
      int metsize = mySBGeometry.NMETBINS[ij], mt2size = mySBGeometry.NMT2BINS[ij];
      double metbins_edge[mySBGeometry.metbins_edge.at(ij).size()], mt2bins_edge[mySBGeometry.mt2bins_edge.at(ij).size()];
      std::copy ( mySBGeometry.metbins_edge.at(ij).begin(), mySBGeometry.metbins_edge.at(ij).end(), metbins_edge );
      std::copy ( mySBGeometry.mt2bins_edge.at(ij).begin(), mySBGeometry.mt2bins_edge.at(ij).end(), mt2bins_edge );

      double ntopjets_fold = -1, nbotjets_fold = -1, met_fold = -1, mt2_fold = -1;
      if(ntopjets>=mySBGeometry.ntopbins_edge[NTOPJETS_BINS]) ntopjets_fold = mySBGeometry.ntopbins_edge[NTOPJETS_BINS-1]; else ntopjets_fold = ntopjets;
      if(nbotjets>=mySBGeometry.nbotbins_edge[NBOTJETS_BINS]) nbotjets_fold = mySBGeometry.nbotbins_edge[NBOTJETS_BINS-1]; else nbotjets_fold = nbotjets;
      if(met>=metbins_edge[metsize]) met_fold = (metbins_edge[metsize-1]+metbins_edge[metsize])/2; else met_fold = met;
      if(mt2>=mt2bins_edge[mt2size]) mt2_fold = (mt2bins_edge[mt2size-1]+mt2bins_edge[mt2size])/2; else mt2_fold = mt2;

      //Get electron and muon for LL study
      int nElectrons = tr.getVar<int>("nElectrons");
      int nMuons = tr.getVar<int>("nMuons");
      //int searchbin_id = mySBGeometry.GetSBID(ntopjets,nbotjets,mt2,met);
      int searchbin_id = find_Binning_Index( nbotjets , ntopjets , mt2, met );

      if( ((*iter_SSSampleInfos).Tag).find("TTJets") != std::string::npos )
			{
        double TTJetsSF = 0.8;
        //Counting the muon control sample
        if (nElectrons == 0 && nMuons == 1)
        {
          (mySSCSHistgram.h_ss_ntopnbot_MC_MuCS)->Fill(ntopjets_fold,nbotjets_fold,thisweight*TTJetsSF);
          (mySSCSHistgram.h_ss_metmt2_MC_MuCS[ntopjetsbin_number][nbotjetsbin_number])->Fill(met_fold,mt2_fold,thisweight*TTJetsSF);
          if(searchbin_id>=0){ mucs[searchbin_id]+=(thisweight*TTJetsSF); mucs_NMC[searchbin_id]++; }
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
          (mySSCSHistgram.h_ss_ntopnbot_MC_ElCS)->Fill(ntopjets_fold,nbotjets_fold,thisweight*TTJetsSF);
          (mySSCSHistgram.h_ss_metmt2_MC_ElCS[ntopjetsbin_number][nbotjetsbin_number])->Fill(met_fold,mt2_fold,thisweight*TTJetsSF);
          if(searchbin_id>=0){ elcs[searchbin_id]+=(thisweight*TTJetsSF); elcs_NMC[searchbin_id]++; }
        }
      }
    }//end of inner loop
  }//end of Samples loop

  std::ofstream DC_sb_LL_Header;
  DC_sb_LL_Header.open ( "DC_sb_LL_Header.h" );
  DC_sb_LL_Header << "  const double head_DC_sb_MC_LL_cs[" << NSB << "] = ";
  for( int i_cal = 0 ; i_cal < NSB ; i_cal++ )
  {
    if( i_cal == 0 ) { DC_sb_LL_Header << "{"; }
    DC_sb_LL_Header << mucs[i_cal];
    if( i_cal != NSB-1 ) { DC_sb_LL_Header << ","; }
    else{ DC_sb_LL_Header << "};"; }
  }
  DC_sb_LL_Header << std::endl;
  DC_sb_LL_Header << "  const double head_DC_sb_NMC_LL_cs[" << NSB << "] = ";
  for( int i_cal = 0 ; i_cal < NSB ; i_cal++ )
  {
    if( i_cal == 0 ) { DC_sb_LL_Header << "{"; }
    DC_sb_LL_Header << mucs_NMC[i_cal];
    if( i_cal != NSB-1 ) { DC_sb_LL_Header << ","; }
    else{ DC_sb_LL_Header << "};"; }
  }

  DC_sb_LL_Header.close();

  (mySSCSHistgram.oFile)->Write();
  (mySSCSHistgram.oFile)->Close();
  return ;
}

void LoopSSAllMC( SSSampleWeight& mySSSampleWeight )
{
  SSHistgram mySSHistgram;
  mySSHistgram.BookHistgram( (dir_out + "SSAllMC.root").c_str() );
  
  SSAUX1DHistgram mySSAUX1DHistgram;
  mySSAUX1DHistgram.BookHistgram( (dir_out + "SSAUX1DAllMC.root").c_str() );

  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<SSSampleInfo>::iterator iter_SSSampleInfos;
  //use class BaselineVessel in the SusyAnaTools/Tools/baselineDef.h file

  SSDataCard mySSDataCard;
  std::cout << "Let's do sensitivity study: " << std::endl;

  //begin to loop over all events
  for(iter_SSSampleInfos = mySSSampleWeight.SSSampleInfos.begin(); iter_SSSampleInfos != mySSSampleWeight.SSSampleInfos.end(); iter_SSSampleInfos++)
  {    
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_SSSampleInfos).chain);

    double thisweight = (*iter_SSSampleInfos).weight;
    std::cout <<"Sample Type: "<< (*iter_SSSampleInfos).Tag << "; Weight: " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTop");
      int nbotjets = tr.getVar<int>("nBot");
      double mt2 = tr.getVar<double>("mt2");
      double met = tr.getVar<double>("met");
      //closure plots variables
      //int njets30 = tr.getVar<int>("nJets30");
      //int njets50 = tr.getVar<int>("nJets50");
      //double ht = tr.getVar<double>("ht");

      int ntopjetsbin_number = mySBGeometry.GetTopID(ntopjets);
      int nbotjetsbin_number = mySBGeometry.GetBotID(nbotjets);
      //int metbin_number = Set_metbin_number(met);
      //int mt2bin_number = Set_mt2bin_number(mt2);

      bool passLeptVeto = tr.getVar<bool>("passLeptVeto");
      if(!passLeptVeto) continue;

      int ij=ntopjetsbin_number*NBOTJETS_BINS+nbotjetsbin_number;
      int metsize = mySBGeometry.NMETBINS[ij], mt2size = mySBGeometry.NMT2BINS[ij];
      double metbins_edge[mySBGeometry.metbins_edge.at(ij).size()], mt2bins_edge[mySBGeometry.mt2bins_edge.at(ij).size()];
      std::copy ( mySBGeometry.metbins_edge.at(ij).begin(), mySBGeometry.metbins_edge.at(ij).end(), metbins_edge );
      std::copy ( mySBGeometry.mt2bins_edge.at(ij).begin(), mySBGeometry.mt2bins_edge.at(ij).end(), mt2bins_edge );

      double ntopjets_fold = -1, nbotjets_fold = -1, met_fold = -1, mt2_fold = -1;
      if(ntopjets>=mySBGeometry.ntopbins_edge[NTOPJETS_BINS]) ntopjets_fold = mySBGeometry.ntopbins_edge[NTOPJETS_BINS-1]; else ntopjets_fold = ntopjets;
      if(nbotjets>=mySBGeometry.nbotbins_edge[NBOTJETS_BINS]) nbotjets_fold = mySBGeometry.nbotbins_edge[NBOTJETS_BINS-1]; else nbotjets_fold = nbotjets;
      if(met>=metbins_edge[metsize]) met_fold = (metbins_edge[metsize-1]+metbins_edge[metsize])/2; else met_fold = met;
      if(mt2>=mt2bins_edge[mt2size]) mt2_fold = (mt2bins_edge[mt2size-1]+mt2bins_edge[mt2size])/2; else mt2_fold = mt2;

      //int searchbin_id = mySBGeometry.GetSBID(ntopjets,nbotjets,mt2,met);
      int searchbin_id = find_Binning_Index( nbotjets , ntopjets , mt2, met );
      if(searchbin_id<0) { std::cout << "Search bin id problem! Please check!!" << std::endl; continue; }
      //To separate the LL and Hadtau

      if( ((*iter_SSSampleInfos).Tag).find("TTJets") != std::string::npos )
      { 
        bool isLL = tr.getVar<bool>("isLL");
        double TTJetsSF = 0.8;
        if(isLL) 
        {
          (mySSAUX1DHistgram.h_ss_aux_met_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][0])->Fill(met,thisweight*TTJetsSF);
          (mySSAUX1DHistgram.h_ss_aux_mt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][0])->Fill(mt2,thisweight*TTJetsSF);
          mySSDataCard.DC_sb_MC_LL[searchbin_id] += thisweight*TTJetsSF; 
        }
        else 
        { 
          (mySSAUX1DHistgram.h_ss_aux_met_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][1])->Fill(met,thisweight*TTJetsSF);
          (mySSAUX1DHistgram.h_ss_aux_mt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][1])->Fill(mt2,thisweight*TTJetsSF);
          mySSDataCard.DC_sb_MC_HadTau[searchbin_id] += thisweight*TTJetsSF;
          mySSDataCard.DC_sb_MC_HadTau_NMCforsystunc[searchbin_id]++;
          //std::cout << "NTop: " << ntopjets << ",NBoT: " << nbotjets << ",MT2: " << mt2 << ",MET: " << met << std::endl;
        }
      }
      if( ((*iter_SSSampleInfos).Tag).find("ST_tW") != std::string::npos )
      { 
        bool isLL = tr.getVar<bool>("isLL");
        if(isLL)
        { 
          (mySSAUX1DHistgram.h_ss_aux_met_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][0])->Fill(met,thisweight);
          (mySSAUX1DHistgram.h_ss_aux_mt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][0])->Fill(mt2,thisweight);
          mySSDataCard.DC_sb_MC_LL[searchbin_id] += thisweight;
        }
        else 
        {
          (mySSAUX1DHistgram.h_ss_aux_met_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][1])->Fill(met,thisweight);
          (mySSAUX1DHistgram.h_ss_aux_mt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][1])->Fill(mt2,thisweight);
          mySSDataCard.DC_sb_MC_HadTau[searchbin_id] += thisweight;
          mySSDataCard.DC_sb_MC_HadTau_NMCforsystunc[searchbin_id]++;
          //std::cout << "NTop: " << ntopjets << ",NBoT: " << nbotjets << ",MT2: " << mt2 << ",MET: " << met << std::endl;
        }
      }
      if( ((*iter_SSSampleInfos).Tag).find("WJetsToLNu_HT") != std::string::npos )
      {
        bool isLL = tr.getVar<bool>("isLL");
        if(isLL)
        {
          (mySSAUX1DHistgram.h_ss_aux_met_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][0])->Fill(met,thisweight);
          (mySSAUX1DHistgram.h_ss_aux_mt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][0])->Fill(mt2,thisweight);
          mySSDataCard.DC_sb_MC_LL[searchbin_id] += thisweight;
        }
        else 
        {
          (mySSAUX1DHistgram.h_ss_aux_met_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][1])->Fill(met,thisweight);
          (mySSAUX1DHistgram.h_ss_aux_mt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][1])->Fill(mt2,thisweight);  
          mySSDataCard.DC_sb_MC_HadTau[searchbin_id] += thisweight;
          mySSDataCard.DC_sb_MC_HadTau_NMCforsystunc[searchbin_id]++;
          //std::cout << "NTop: " << ntopjets << ",NBoT: " << nbotjets << ",MT2: " << mt2 << ",MET: " << met << std::endl;
        }
      }
      if( ((*iter_SSSampleInfos).Tag).find("ZJetsToNuNu_HT") != std::string::npos )
      {
        double RNorm = 0.783;  
        int nJets30 = tr.getVar<int>("nJets30"); double njetRWF = 1;
        nJets30<8 ? njetRWF = NJetRweightingFactor[nJets30-1] : njetRWF = NJetRweightingFactor[7];    
        (mySSAUX1DHistgram.h_ss_aux_met_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][2])->Fill(met,thisweight*njetRWF*RNorm);
        (mySSAUX1DHistgram.h_ss_aux_mt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][2])->Fill(mt2,thisweight*njetRWF*RNorm);
        mySSDataCard.DC_sb_MC_Zinv[searchbin_id] += thisweight*njetRWF*RNorm; 
        //effective number of event from Joe, we just have 2 type of weight, ZJetsToNuNu_HT-400To600 and ZJetsToNuNu_HT-600ToInf
        mySSDataCard.DC_sb_MC_Zinv_cs_up[searchbin_id]+=thisweight*njetRWF*RNorm; mySSDataCard.DC_sb_MC_Zinv_cs_dn[searchbin_id]+=thisweight*njetRWF*RNorm*thisweight*njetRWF*RNorm;
      }
      if( ((*iter_SSSampleInfos).Tag).find("QCD_HT") != std::string::npos )
      { 
        (mySSAUX1DHistgram.h_ss_aux_met_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][3])->Fill(met,thisweight);
        (mySSAUX1DHistgram.h_ss_aux_mt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][3])->Fill(mt2,thisweight);
        mySSDataCard.DC_sb_MC_QCD[searchbin_id] += thisweight; 
      }
      //TTZ, becareful to the negative prediction
      if( ((*iter_SSSampleInfos).Tag).find("TTZTo") != std::string::npos )
      { 
        bool isNegativeWeight = false; isNegativeWeight = tr.getVar<bool>("isNegativeWeight");
        bool isGenZLep = false; isGenZLep = tr.getVar<bool>("isGenZLep");
        bool isGenWLep = false; isGenWLep = tr.getVar<bool>("isGenWLep");
        if((!isGenZLep) && (!isGenWLep))
        {
          if(isNegativeWeight)
          {
            (mySSAUX1DHistgram.h_ss_aux_met_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][4])->Fill(met,-thisweight);
            (mySSAUX1DHistgram.h_ss_aux_mt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][4])->Fill(mt2,-thisweight);
          }
          else
          {
            (mySSAUX1DHistgram.h_ss_aux_met_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][4])->Fill(met,thisweight);
            (mySSAUX1DHistgram.h_ss_aux_mt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][4])->Fill(mt2,thisweight);
          }
          isNegativeWeight ? mySSDataCard.DC_sb_MC_TTZ[searchbin_id] -= thisweight : mySSDataCard.DC_sb_MC_TTZ[searchbin_id] += thisweight;
          isNegativeWeight ? mySSDataCard.DC_sb_MC_TTZ_cs[searchbin_id]-- : mySSDataCard.DC_sb_MC_TTZ_cs[searchbin_id]++;
        }
      }
      if( ((*iter_SSSampleInfos).Tag).find("TTWJetsTo") != std::string::npos )
      { 
        bool isNegativeWeight = false; isNegativeWeight = tr.getVar<bool>("isNegativeWeight");
        bool isGenZLep = false; isGenZLep = tr.getVar<bool>("isGenZLep");
        bool isGenWLep = false; isGenWLep = tr.getVar<bool>("isGenWLep");
        if((!isGenZLep) && (!isGenWLep))
        {
          if(isNegativeWeight)
          {
            (mySSAUX1DHistgram.h_ss_aux_met_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][4])->Fill(met,-thisweight);
            (mySSAUX1DHistgram.h_ss_aux_mt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][4])->Fill(mt2,-thisweight);
          }
          else
          {
            (mySSAUX1DHistgram.h_ss_aux_met_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][4])->Fill(met,thisweight);
            (mySSAUX1DHistgram.h_ss_aux_mt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number][4])->Fill(mt2,thisweight);
          }
          isNegativeWeight ? mySSDataCard.DC_sb_MC_TTZ[searchbin_id] -= thisweight : mySSDataCard.DC_sb_MC_TTZ[searchbin_id] += thisweight;
          isNegativeWeight ? mySSDataCard.DC_sb_MC_TTZ_cs[searchbin_id]-- : mySSDataCard.DC_sb_MC_TTZ_cs[searchbin_id]++;
        }
      }

      if( ((*iter_SSSampleInfos).Tag).find("T1tttt_mGluino-1200_mLSP-800") != std::string::npos )
      {
        (mySSAUX1DHistgram.h_ss_aux_met_MC_T1tttt_mGluino1200_mLSP800[ntopjetsbin_number][nbotjetsbin_number])->Fill(met,thisweight);
        (mySSAUX1DHistgram.h_ss_aux_mt2_MC_T1tttt_mGluino1200_mLSP800[ntopjetsbin_number][nbotjetsbin_number])->Fill(mt2,thisweight);
        (mySSHistgram.h_ss_ntopnbot_MC_T1tttt_mGluino1200_mLSP800)->Fill(ntopjets_fold,nbotjets_fold,thisweight);
        (mySSHistgram.h_ss_metmt2_MC_T1tttt_mGluino1200_mLSP800[ntopjetsbin_number][nbotjetsbin_number])->Fill(met_fold,mt2_fold,thisweight);
      }
      else if( ((*iter_SSSampleInfos).Tag).find("T1tttt_mGluino-1500_mLSP-100") != std::string::npos )
      {
        (mySSAUX1DHistgram.h_ss_aux_met_MC_T1tttt_mGluino1500_mLSP100[ntopjetsbin_number][nbotjetsbin_number])->Fill(met,thisweight);
        (mySSAUX1DHistgram.h_ss_aux_mt2_MC_T1tttt_mGluino1500_mLSP100[ntopjetsbin_number][nbotjetsbin_number])->Fill(mt2,thisweight);
        (mySSHistgram.h_ss_ntopnbot_MC_T1tttt_mGluino1500_mLSP100)->Fill(ntopjets_fold,nbotjets_fold,thisweight);
        (mySSHistgram.h_ss_metmt2_MC_T1tttt_mGluino1500_mLSP100[ntopjetsbin_number][nbotjetsbin_number])->Fill(met_fold,mt2_fold,thisweight);
      }
      else if( ((*iter_SSSampleInfos).Tag).find("T2tt_mStop-500_mLSP-325") != std::string::npos )
      {
        (mySSAUX1DHistgram.h_ss_aux_met_MC_T2tt_mStop500_mLSP325[ntopjetsbin_number][nbotjetsbin_number])->Fill(met,thisweight);
        (mySSAUX1DHistgram.h_ss_aux_mt2_MC_T2tt_mStop500_mLSP325[ntopjetsbin_number][nbotjetsbin_number])->Fill(mt2,thisweight);
        (mySSHistgram.h_ss_ntopnbot_MC_T2tt_mStop500_mLSP325)->Fill(ntopjets_fold,nbotjets_fold,thisweight);
        (mySSHistgram.h_ss_metmt2_MC_T2tt_mStop500_mLSP325[ntopjetsbin_number][nbotjetsbin_number])->Fill(met_fold,mt2_fold,thisweight);
      }
      else if( ((*iter_SSSampleInfos).Tag).find("T2tt_mStop-850_mLSP-100") != std::string::npos )
      {
        (mySSAUX1DHistgram.h_ss_aux_met_MC_T2tt_mStop850_mLSP100[ntopjetsbin_number][nbotjetsbin_number])->Fill(met,thisweight);
        (mySSAUX1DHistgram.h_ss_aux_mt2_MC_T2tt_mStop850_mLSP100[ntopjetsbin_number][nbotjetsbin_number])->Fill(mt2,thisweight);
        (mySSHistgram.h_ss_ntopnbot_MC_T2tt_mStop850_mLSP100)->Fill(ntopjets_fold,nbotjets_fold,thisweight);
        (mySSHistgram.h_ss_metmt2_MC_T2tt_mStop850_mLSP100[ntopjetsbin_number][nbotjetsbin_number])->Fill(met_fold,mt2_fold,thisweight);
      }
      else
      {
        (mySSHistgram.h_ss_ntopnbot_MC_AllBG)->Fill(ntopjets_fold,nbotjets_fold,thisweight);
        (mySSHistgram.h_ss_metmt2_MC_AllBG[ntopjetsbin_number][nbotjetsbin_number])->Fill(met_fold,mt2_fold,thisweight);
      } 
    }//end of inner loop
  }//end of Samples loop

  //mySSDataCard.printDC_AllFiles("_45BinsRefLUMI2015");
  mySSDataCard.printDC_AllFiles("_45BinsRefLUMI2015");
  (mySSHistgram.oFile)->Write();
  (mySSHistgram.oFile)->Close();
  (mySSAUX1DHistgram.oFile)->Write();
  (mySSAUX1DHistgram.oFile)->Close();
  return ;
}

int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cerr <<"Please give at least 3 arguments " << "RunMode " << " " << "runListMCBG " << " " << "runListMCSG" << "" << "runListMCCS" << std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./QCD RunMode runlist_QCDMC.txt runlist_Data.txt" << std::endl;
    return -1;
  }

  std::string RunMode = argv[1];
  std::string inputFileList_MC_BG = argv[2];
  std::string inputFileList_MC_SG = argv[3];
  std::string inputFileList_CS = argv[4];

  std::cout << "The valid run modes are: SS" << std::endl;
  std::cout << "The run mode we have right now is: " << RunMode << std::endl;

  if( RunMode == "SSCS" )
  {
    double TTbar_SingleLept_BR = 0.43930872; // 2*W_Lept_BR*(1-W_Lept_BR)
    double TTbar_DiLept_BR = 0.10614564; // W_Lept_BR^2

    SSSampleWeight mySSSampleWeightCS;
    mySSSampleWeightCS.SSSampleInfo_push_back( "TTJets_SingleLept", 831.76*0.5*TTbar_SingleLept_BR, 59816364+60144642, LUMI, 1, inputFileList_CS.c_str() );
    mySSSampleWeightCS.SSSampleInfo_push_back( "TTJets_DiLept"    , 831.76*TTbar_DiLept_BR        , 30498962         , LUMI, 1, inputFileList_CS.c_str() );
    
    LoopSSCS( mySSSampleWeightCS );
    return 0;
  }
  else if( RunMode == "SSAllMC" )
  {
    double TTbar_SingleLept_BR = 0.43930872; // 2*W_Lept_BR*(1-W_Lept_BR)
    double TTbar_DiLept_BR = 0.10614564; // W_Lept_BR^2

    //sample needed in the basic check loop
    SSSampleWeight mySSSampleWeightAllMC;
    mySSSampleWeightAllMC.SSSampleInfo_push_back( "TTJets_SingleLept"       , 831.76*0.5*TTbar_SingleLept_BR, 59816364+60144642, LUMI, 1, inputFileList_MC_BG.c_str() );
    mySSSampleWeightAllMC.SSSampleInfo_push_back( "TTJets_DiLept"           , 831.76*TTbar_DiLept_BR        , 30498962         , LUMI, 1, inputFileList_MC_BG.c_str() );
    mySSSampleWeightAllMC.SSSampleInfo_push_back( "ST_tW_top"               ,   35.6,        995600, LUMI, 1, inputFileList_MC_BG.c_str() );
    mySSSampleWeightAllMC.SSSampleInfo_push_back( "ST_tW_antitop"           ,   35.6,        988500, LUMI, 1, inputFileList_MC_BG.c_str() );
    //be careful!! WJets and ZJets samples have some tricky part, need to understand!
    mySSSampleWeightAllMC.SSSampleInfo_push_back( "WJetsToLNu_HT-400To600"  ,  48.91,       1745914, LUMI, 1.21, inputFileList_MC_BG.c_str() );
    mySSSampleWeightAllMC.SSSampleInfo_push_back( "WJetsToLNu_HT-600ToInf"  ,  18.77,       1039152, LUMI, 1.21, inputFileList_MC_BG.c_str() );

    mySSSampleWeightAllMC.SSSampleInfo_push_back( "ZJetsToNuNu_HT-400To600" ,  10.73,       9591098, LUMI, 1.23, inputFileList_MC_BG.c_str() );
    mySSSampleWeightAllMC.SSSampleInfo_push_back( "ZJetsToNuNu_HT-600ToInf" ,  4.116,      10202299, LUMI, 1.23, inputFileList_MC_BG.c_str() );
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
