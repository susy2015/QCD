#include <fstream>
#include <map>
#include <iomanip>
#include <locale>
#include <sstream>
#include <stdlib.h>

#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TString.h"
#include "TLorentzVector.h"

#include "JetResponse.h"

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"Please give 1 argument " << "inputFileName " << std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./JetResponse runList_QCDMC_MET30.txt" << std::endl;
    return -1;
  }

  std::string inputFileList_QCDMC = argv[1];

  JetResponseHistgram myJetResponseHistgram;
  myJetResponseHistgram.BookHistgram("JetResponseQCD.root");
  //clock to monitor the run time
  size_t t0 = clock();
  std::vector<QCDSampleInfo>::iterator iter_QCDSampleInfos;
  int i = 0;
  //use class BaselineVessel in the SusyAnaTools/Tools/baselineDef.h file
  const std::string spec = "QCD";
  myBaselineVessel = new BaselineVessel(spec);

  QCDSampleWeight myQCDSampleWeight;
  myQCDSampleWeight.QCDSampleInfo_push_back( "QCD_HT300to500"  , 367000  , 20086103, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "QCD_HT500to700"  , 29370   , 19664159, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "QCD_HT700to1000" , 6524    , 15356448, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "QCD_HT1000to1500", 1064    ,  4963895, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "QCD_HT1500to2000", 121.5   ,  3868886, LUMI, 1, inputFileList_QCDMC.c_str() );
  myQCDSampleWeight.QCDSampleInfo_push_back( "QCD_HT2000toInf" , 25.42   ,  1683349, LUMI, 1, inputFileList_QCDMC.c_str() );

  std::cout << "QCD Jet Response: " << std::endl;

  for(iter_QCDSampleInfos = myQCDSampleWeight.QCDSampleInfos.begin(); iter_QCDSampleInfos != myQCDSampleWeight.QCDSampleInfos.end(); iter_QCDSampleInfos++)
  {
    //use class NTupleReader in the SusyAnaTools/Tools/NTupleReader.h file
    NTupleReader tr((*iter_QCDSampleInfos).chain);
    //initialize the type3Ptr defined in the customize.h
    AnaFunctions::prepareTopTagger();
    //The passBaseline is registered here
    tr.registerFunction(&mypassBaselineFunc);

    double thisweight = (*iter_QCDSampleInfos).weight;
    std::cout <<"Sample Type: "<< (*iter_QCDSampleInfos).QCDTag << "; Weight: " << thisweight << std::endl;

    while(tr.getNextEvent())
    {
      if(tr.getEvtNum()%20000 == 0) std::cout << tr.getEvtNum() << "\t" << ((clock() - t0)/1000000.0) << std::endl;

      //searchbin variables
      //int ntopjets = tr.getVar<int>("nTopCandSortedCnt"+spec);
      //int nbottomjets = tr.getVar<int>("cntCSVS"+spec);
      double MT2 = tr.getVar<double>("best_had_brJet_MT2"+spec);
      double met = tr.getVar<double>("met");

      (myJetResponseHistgram.h_QCDMC_MET_MT2_Corr)->Fill(met,MT2,thisweight);
      /*
      //reco Jet
      std::vector<TLorentzVector> jetsLVec = tr.getVec<TLorentzVector>("jetsLVec");
      //Gen Jet information
      std::vector<TLorentzVector> GenjetsLVec = tr.getVec<TLorentzVector>("GenjetsLVec");

      for(int i=0;i<GenjetsLVec.size();i++)
      {
        double Genjetpt = GenjetsLVec.at(i).Pt();
        double Genjeteta = GenjetsLVec.at(i).Eta();

        int jetptbin_number = JetResponseConstant::Set_jetptbin_number( Genjetpt );
        int jetetabin_number = JetResponseConstant::Set_jetetabin_number( Genjeteta );
      }
      */
    }
  }

  (myJetResponseHistgram.oFile)->Write();
  (myJetResponseHistgram.oFile)->Close();
  return 0;
}
