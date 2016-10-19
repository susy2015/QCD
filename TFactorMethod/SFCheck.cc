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

#include "SFCheck.h"

//std::string dir_out = "RootForPlotting/";
std::string dir_out = "";

void LoopSFCheck( QCDSampleWeight& myQCDSampleWeight, int lower_nb, int higher_nb, bool isCondor )
{
  SFCheckHistgram mySFCheckHistgram;
  mySFCheckHistgram.BookHistgram( (dir_out + "SFCheck_nb" + std::to_string(lower_nb) + "_" + std::to_string(higher_nb) + ".root").c_str() );
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  //use class BaselineVessel in the SusyAnaTools/Tools/baselineDef.h file
  const std::string spec = "QCD";
  myBaselineVessel = new BaselineVessel(spec);
  
	std::string LeptF_dir = "LeptFactors/";
  if(isCondor) {LeptF_dir.clear(); LeptF_dir = "";}
  TFile *flept_sf_all = TFile::Open( ( LeptF_dir + "allINone_leptonSF.root").c_str() );
  TH2F *ele_VetoID_SF = (TH2F*) flept_sf_all->Get("GsfElectronToVeto");
  TH2F *ele_miniISO_SF = (TH2F*) flept_sf_all->Get("MVAVLooseElectronToMini");
  TH2F *ele_trkpt_SF = (TH2F*) flept_sf_all->Get("EGamma_SF2D");
  TH2F *mu_mediumID_SF = (TH2F*) flept_sf_all->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0");
  TH2F *mu_miniISO_SF = (TH2F*) flept_sf_all->Get("pt_abseta_PLOT_pair_probeMultiplicity_bin0_&_Medium2016_pass");
  TH1D *mu_trkptGT10_SF = (TH1D*) flept_sf_all->Get("mutrksfptg10");
  TH1D *mu_trkptLT10_SF = (TH1D*) flept_sf_all->Get("mutrksfptl10");

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
    
    if( ! ( ( (*iter_QCDSampleInfos).QCDTag ).find("HTMHT") != std::string::npos ) ) 
    {
      BTagCorrector *btagcorr;
      btagcorr = nullptr;
      if( ( (*iter_QCDSampleInfos).QCDTag ).find("WJetsToLNu_HT") != std::string::npos )
      { 
        if  (isCondor){btagcorr = new BTagCorrector("WJetsToLNu_HT_bTagEff_forHua.root", "", false);}
        else          {btagcorr = new BTagCorrector("BSFactors/WJetsToLNu_HT_bTagEff_forHua.root", "BSFactors", false);}
      }
      else
      { 
        if  (isCondor){btagcorr = new BTagCorrector("TTbarNoHad_bTagEff.root", "", false);}
        else          {btagcorr = new BTagCorrector("BSFactors/TTbarNoHad_bTagEff.root", "BSFactors", false);}
      }
      tr.registerFunction(*btagcorr);
    }
    
    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      int nbotjets = tr.getVar<int>("cntCSVS"+spec);
      double mt2 = tr.getVar<double>("best_had_brJet_MT2"+spec);
      double met = tr.getVar<double>("met");
      //aux varibales
      int njets30 = tr.getVar<int>("cntNJetsPt30Eta24"+spec);
      int njets50 = tr.getVar<int>("cntNJetsPt50Eta24"+spec);
      double ht = tr.getVar<double>("HT"+spec);
  
      double bSF = 1;
      if( ! ( ( (*iter_QCDSampleInfos).QCDTag ).find("HTMHT") != std::string::npos ) )  
      {
        bSF = tr.getVar<double>("bTagSF_EventWeightSimple_Central");
        //std::cout << "b tag scale factor : " << bSF << std::endl;
      }
   
      //apply trigger efficiencies
      //double bSF = QCDGetTriggerEff( (*iter_QCDSampleInfos).QCDTag, met );
      double leptSF = 1;
      if( ! ( ( (*iter_QCDSampleInfos).QCDTag ).find("HTMHT") != std::string::npos ) )  
      {
        leptSF = ElMuDataMCScaleFactor(
                                       tr.getVec<TLorentzVector>("elesLVec"),
                                       tr.getVec<int>("elesFlagVeto"),
                                       tr.getVec<double>("elesMiniIso"),
                                       tr.getVec<TLorentzVector>("muonsLVec"),
                                       tr.getVec<int>("muonsFlagMedium"),
                                       tr.getVec<double>("muonsMiniIso"),
                                       ele_VetoID_SF,
                                       ele_miniISO_SF,
                                       ele_trkpt_SF,
                                       mu_mediumID_SF,
                                       mu_miniISO_SF,
                                       mu_trkptGT10_SF,
                                       mu_trkptLT10_SF
                                      );
      }
      //std::cout << "Lept SF : " << leptSF << std::endl;
      
      if ( nbotjets >= lower_nb && nbotjets < higher_nb )
      {
        if( (*iter_QCDSampleInfos).QCDTag == "HTMHT" )
        {
          std::vector<std::string> TriggerNames = tr.getVec<std::string>("TriggerNames");
          std::vector<int> PassTrigger = tr.getVec<int>("PassTrigger");
          bool foundTrigger = false;
          for(unsigned it=0; it<TriggerNames.size(); it++)
          {
            if
            ( 
             TriggerNames[it].find("HLT_PFMET100_PFMHT100_IDTight") != std::string::npos || 
             TriggerNames[it].find("HLT_PFMETNoMu100_PFMHTNoMu100_IDTight") != std::string::npos
            )
            {
              if( PassTrigger[it] ) foundTrigger = true;
            }
          }

          if( !foundTrigger ) continue;

          (mySFCheckHistgram.h_b_met_Data)->Fill(met,thisweight);
          (mySFCheckHistgram.h_b_mt2_Data)->Fill(mt2,thisweight);
          (mySFCheckHistgram.h_b_ntopjets_Data)->Fill(ntopjets,thisweight);
          (mySFCheckHistgram.h_b_nbjets_Data)->Fill(nbotjets,thisweight);
          (mySFCheckHistgram.h_b_ht_Data)->Fill(ht,thisweight);
          //(mySFCheckHistgram.h_b_mht_Data)->Fill(mht,thisweight);
          (mySFCheckHistgram.h_b_njets30_Data)->Fill(njets30,thisweight);
          (mySFCheckHistgram.h_b_njets50_Data)->Fill(njets50,thisweight);

        }
        else
        {
          Int_t ih = -1;

          if( ((*iter_QCDSampleInfos).QCDTag).find("TTJets") != std::string::npos ) ih = 0;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("ST_tW") != std::string::npos ) ih = 1;
          else if( ((*iter_QCDSampleInfos).QCDTag).find("WJetsToLNu_HT") ) ih = 2;
          else std::cout << "Invalid tag! what the fuck is going on ?!" << std::endl;
      
          //Top pt reweighting
          //Get gen top TLVec
          double topptSF = 1;
          if( ((*iter_QCDSampleInfos).QCDTag).find("TTJets") != std::string::npos )
          {
            const std::vector<TLorentzVector> &genDecayLVec = tr.getVec<TLorentzVector>("genDecayLVec");
            const std::vector<int> &genDecayIdxVec = tr.getVec<int>("genDecayIdxVec");
            const std::vector<int> &genDecayPdgIdVec = tr.getVec<int>("genDecayPdgIdVec");
            const std::vector<int> &genDecayMomIdxVec = tr.getVec<int>("genDecayMomIdxVec");
            std::vector<TLorentzVector> GenTop = GetGenTopLVec(genDecayLVec, genDecayPdgIdVec, genDecayIdxVec, genDecayMomIdxVec);
            if(GenTop.size()!=2){ std::cout << "Can not find 2 Gen top in TTJets sample?? what the fuck is going on!" << std::endl; }
            for(auto& i:GenTop)
            {
              double toppt = i.Pt();
              //https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting, l+jets, 8TeV
              topptSF = topptSF*std::exp(0.159-0.00141*toppt);
            }
            topptSF = std::sqrt(topptSF);
            //std::cout << topptSF << std::endl;
          }

          (mySFCheckHistgram.h_b_met_MC[ih])->Fill(met,thisweight*bSF*leptSF*topptSF);
          (mySFCheckHistgram.h_b_mt2_MC[ih])->Fill(mt2,thisweight*bSF*leptSF*topptSF);
          (mySFCheckHistgram.h_b_ntopjets_MC[ih])->Fill(ntopjets,thisweight*bSF*leptSF*topptSF);
          (mySFCheckHistgram.h_b_nbjets_MC[ih])->Fill(nbotjets,thisweight*bSF*leptSF*topptSF);
          (mySFCheckHistgram.h_b_ht_MC[ih])->Fill(ht,thisweight*bSF*leptSF*topptSF);
          //(mySFCheckHistgram.h_b_mht_MC[ih])->Fill(mht,thisweight*bSF*leptSF*topptSF);
          (mySFCheckHistgram.h_b_njets30_MC)[ih]->Fill(njets30,thisweight*bSF*leptSF*topptSF);
          (mySFCheckHistgram.h_b_njets50_MC)[ih]->Fill(njets50,thisweight*bSF*leptSF*topptSF);
        }
      }
    }//end of inner loop
  }//end of QCD Samples loop

  flept_sf_all->Close();

  (mySFCheckHistgram.oFile)->Write();
  (mySFCheckHistgram.oFile)->Close();
  return ;
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr <<"Please give at least 2 arguments " << "RunMode " << " " << "runListMC " << " " << "runListData"<< std::endl;
    std::cerr <<" Valid configurations are " << std::endl;
    std::cerr <<" ./QCD RunMode runlist_Data.txt" << std::endl;
    return -1;
  }

  std::string RunMode = argv[1];
  std::string inputFileList_Data = argv[2];
  
  std::cout << "The valid run modes are: SFCheck" << std::endl;
  std::cout << "The run mode we have right now is: " << RunMode << std::endl;
  
  double TTbar_SingleLept_BR = 0.43930872; // 2*W_Lept_BR*(1-W_Lept_BR)
  double TTbar_DiLept_BR = 0.10614564; // W_Lept_BR^2
  //sample needed in the prediction loop
  QCDSampleWeight myDataSampleWeight;
  myDataSampleWeight.QCDSampleInfo_push_back( "HTMHT"                      ,                              1,        1, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTJets_DiLept"             ,         831.76*TTbar_DiLept_BR, 30682233, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromT_"   , 831.76*0.5*TTbar_SingleLept_BR, 49576803, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_TTJets_SingleLeptFromTbar_", 831.76*0.5*TTbar_SingleLept_BR, 60494823, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ST_tW_top"                 ,                           35.6,   998400, LUMI, 1, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_ST_tW_antitop"             ,                           35.6,   985000, LUMI, 1, inputFileList_Data.c_str() );
  //be careful!! WJets and ZJets samples have some tricky part, need to understand!
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-400To600"   ,   48.91,       7432746, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-600To800"   ,   12.05,       3722395, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-800To1200"  ,   5.501,       7854734, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-1200To2500" ,   1.329,       7063909, LUMI, 1.21, inputFileList_Data.c_str() );
  myDataSampleWeight.QCDSampleInfo_push_back( "_WJetsToLNu_HT-2500ToInf"  , 0.03216,        253561, LUMI, 1.21, inputFileList_Data.c_str() );

  if( RunMode == "SFCheckTTJets" )
  {
    //LoopSFCheck( myDataSampleWeight, 1, 9, false );
    LoopSFCheck( myDataSampleWeight, 1, 9, true );
    return 0;
  }
  else if( RunMode == "SFCheckWJets" )
  {
    //LoopSFCheck( myDataSampleWeight, 0, 1, false );
    LoopSFCheck( myDataSampleWeight, 0, 1, true );
    return 0;
  }
  else
  {
    std::cout << "Invalide RunMode!!" << std::endl;
    return 0;
  }

  return 0;
}
