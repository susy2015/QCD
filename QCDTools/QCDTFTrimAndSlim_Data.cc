#include <fstream>
#include <map>
#include <iomanip>
#include <locale>
#include <sstream>
#include <stdlib.h>
#include <cmath>

#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TInterpreter.h"

#include "SusyAnaTools/Tools/samples.h"
#include "SusyAnaTools/Tools/searchBins.h"

#include "QCDTFTrimAndSlimCommon.h"

double DeltaPhi(double phi1, double phi2) 
{
  double result = phi1 - phi2;
  while (result > M_PI)    result -= 2 * M_PI;
  while (result <= -M_PI)  result += 2 * M_PI;
  return result;
}

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"Please give 1 argument " << "inputFileName " << std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./QCDTFTrimAndSlim_QCD root://cmseos.fnal.gov//store/user/lpcsusyhad/Spring16_80X_Jun_2016_Ntp_v5X/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Spring16_80X_Jun_2016_Ntp_v5p0_QCD_HT2000toInf_ext1/160609_112453/0000/stopFlatNtuples_105.root" << std::endl;
    return -1;
  }
  std::string input_str(argv[1]);
  std::string output_str = QCDOutputFileNameGenerator(input_str,true);

  TChain *originalTree = new TChain("stopTreeMaker/AUX");
  originalTree->Add(input_str.c_str());
   
  TFile* output = new TFile((output_str).c_str(), "RECREATE");
  TDirectory *mydict = output->mkdir("stopTreeMaker"); mydict->cd();
  TTree* selectedTree = new TTree("QCDTFTree","QCDTFTree");
  
  //search bin variables
  Double_t met,mt2,ht; Int_t ntopjets,nbotjets;
  selectedTree->Branch("met",&met,"met/D");
  selectedTree->Branch("mt2",&mt2,"mt2/D");
  selectedTree->Branch("ht",&ht,"ht/D");
  selectedTree->Branch("nTop",&ntopjets,"nTop/I");
  selectedTree->Branch("nBot",&nbotjets,"nBot/I");
  //AUX variables maybe useful for research
  Int_t njets30,njets50; Double_t mht;
  selectedTree->Branch("nJets30",&njets30,"nJets30/I");
  selectedTree->Branch("nJets50",&njets50,"nJets50/I");
  selectedTree->Branch("mht",&mht,"mht/D");
  Double_t metphi, mhtphi;
  selectedTree->Branch("metphi",&metphi,"metphi/D");
  selectedTree->Branch("mhtphi",&mhtphi,"mhtphi/D");
  Int_t nmus,nels;
  selectedTree->Branch("nMuons"    ,&nmus,"nMuons/I"    );
  selectedTree->Branch("nElectrons",&nels,"nElectrons/I");
  //Boolean related to the baseline
  Bool_t passLeptVeto,passTagger,passBJets,passQCDHighMETFilter,passdPhis,passNoiseEventFilter;
  selectedTree->Branch("passLeptVeto"        ,&passLeptVeto        ,"passLeptVeto/O");
  selectedTree->Branch("passTagger"          ,&passTagger          ,"passTagger/O");
  selectedTree->Branch("passBJets"           ,&passBJets           ,"passBJets/O");
  selectedTree->Branch("passQCDHighMETFilter",&passQCDHighMETFilter,"passQCDHighMETFilter/O");
  selectedTree->Branch("passdPhis"           ,&passdPhis           ,"passdPhis/O");
  selectedTree->Branch("passNoiseEventFilter",&passNoiseEventFilter,"passNoiseEventFilter/O");
  //calo MET and calo MET phi to get rid of trash in QCD
  Double_t calomet, calometphi;
  selectedTree->Branch("calomet"   ,&calomet   ,"calomet/D");
  selectedTree->Branch("calometphi",&calometphi,"calometphi/D");
  //HT with Eta<5.0, study on High pt HF jet issue
  Double_t ht50;
  selectedTree->Branch("ht50",&ht50,"ht50/D");
  //Trigger information, for Data only
  Bool_t passSearchTrigger;  
  selectedTree->Branch("passSearchTrigger",&passSearchTrigger,"passSearchTrigger/O");
  //Boolean helper on single mu single el CS
  Bool_t pass1mu0elmtwmu,pass0mu1elmtwel;
  selectedTree->Branch("pass1mu0elmtwmu",&pass1mu0elmtwmu,"pass1mu0elmtwmu/O");
  selectedTree->Branch("pass0mu1elmtwel",&pass0mu1elmtwel,"pass0mu1elmtwel/O");

  std::shared_ptr<topTagger::type3TopTagger>type3Ptr(nullptr);
  NTupleReader *tr=0;
  //initialize the type3Ptr defined in the customize.h
  AnaFunctions::prepareForNtupleReader();
  tr = new NTupleReader(originalTree, AnaConsts::activatedBranchNames);
  const std::string spec = "lostlept";
  BaselineVessel *myBaselineVessel = 0;
  myBaselineVessel = new BaselineVessel(*tr, spec);
  if( !useNewTagger ){ myBaselineVessel->SetupTopTagger(false, "Legacy_TopTagger.cfg" ); }
  else
  {
    if( useLegacycfg ){ myBaselineVessel->SetupTopTagger(true, "Legacy_TopTagger.cfg" ); }
    else{ myBaselineVessel->SetupTopTagger(true, "TopTagger.cfg" ); }
  }
  //The passBaseline is registered here
  tr->registerFunction(*myBaselineVessel);

  while(tr->getNextEvent())
  {
    met = tr->getVar<double>("met");
    bool passnJets = tr->getVar<bool>("passnJets"+spec);
    bool passHT = tr->getVar<bool>("passHT"+spec);
    bool passMT2 = tr->getVar<bool>("passMT2"+spec);
    bool passQCDTFTrimAndSlim = ( met > trigger_turn_on_met)
                             && passnJets
                             && passHT
                             && passMT2;

    if(passQCDTFTrimAndSlim)
    {
      //searchbin variables
      mt2 = tr->getVar<double>("best_had_brJet_MT2"+spec);       
      ht = tr->getVar<double>("HT"+spec);
      ntopjets = tr->getVar<int>("nTopCandSortedCnt"+spec);
      nbotjets = tr->getVar<int>("cntCSVS"+spec);
      //AUX variables
      njets30 = tr->getVar<int>("cntNJetsPt30Eta24"+spec);
      njets50 = tr->getVar<int>("cntNJetsPt50Eta24"+spec);
      TLorentzVector mht_TLV = AnaFunctions::calcMHT(tr->getVec<TLorentzVector>("jetsLVec"), AnaConsts::pt30Eta24Arr);
      mht = mht_TLV.Pt(); 
      metphi = tr->getVar<double>("metphi");
      mhtphi = mht_TLV.Phi();
      nmus = tr->getVar<int>("nMuons_CUT"+spec);
      nels = tr->getVar<int>("nElectrons_CUT"+spec);
      //Baseline Boolean
      passLeptVeto = tr->getVar<bool>("passLeptVeto"+spec);
      passTagger = tr->getVar<bool>("passTagger"+spec);
      passBJets = tr->getVar<bool>("passBJets"+spec);
      passQCDHighMETFilter = tr->getVar<bool>("passQCDHighMETFilter"+spec);
      passdPhis = tr->getVar<bool>("passdPhis"+spec);
      passNoiseEventFilter = tr->getVar<bool>("passNoiseEventFilter"+spec);
      //QCD filter related
      calomet = tr->getVar<double>("calomet");
      calometphi = tr->getVar<double>("calometphi");
      //HT50
      ht50 = tr->getVar<double>("HT50"+spec);
      //Trigger information
      std::vector<std::string> TriggerNames = tr->getVec<std::string>("TriggerNames");
      std::vector<int> PassTrigger = tr->getVec<int>("PassTrigger");
      passSearchTrigger = false;
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
          if( PassTrigger[it] ) passSearchTrigger = true;
        }
      }

      //Single Mu Single El CS boolean helper
      //Single Mu
      pass1mu0elmtwmu = false;
      if(nmus==1 && nels==0)
      {
        double this_mus_pt = -1, this_mus_eta = 0, this_mus_phi = -1;
        std::vector<TLorentzVector> muonsLVec = tr->getVec<TLorentzVector>("muonsLVec");
        std::vector<double> muonsMiniIso = tr->getVec<double>("muonsMiniIso");
        std::vector<int> muonsFlagMedium = tr->getVec<int>("muonsFlagMedium");
        for(unsigned int im = 0 ; im < muonsLVec.size() ; im++)
        {
          if(muonsFlagMedium[im] && muonsLVec[im].Pt()>(AnaConsts::muonsMiniIsoArr).minPt && fabs(muonsLVec[im].Eta()) < (AnaConsts::muonsMiniIsoArr).maxAbsEta && muonsMiniIso[im] < (AnaConsts::muonsMiniIsoArr).maxIso )
          {
            this_mus_pt  = ( muonsLVec.at(im) ).Pt();
            this_mus_eta = ( muonsLVec.at(im) ).Eta();
            this_mus_phi = ( muonsLVec.at(im) ).Phi();
          }
        }
        if(this_mus_pt>0)
        {
          double deltaphi_mus = DeltaPhi( this_mus_phi , metphi );
          double thismtwmu = std::sqrt( 2.0 * this_mus_pt * met * ( 1.0 - cos(deltaphi_mus) ) );
          if(thismtwmu<cut_mtwmu) pass1mu0elmtwmu = true;
        }
      }

      //Single El
      pass0mu1elmtwel = false;
      if(nmus==0 && nels==1)
      {
        double this_els_pt = -1, this_els_eta = 0, this_els_phi = -1;
        std::vector<TLorentzVector> elesLVec = tr->getVec<TLorentzVector>("elesLVec");
        std::vector<int> elesFlagVeto = tr->getVec<int>("elesFlagVeto");
        std::vector<double> elesMiniIso = tr->getVec<double>("elesMiniIso");

        for(unsigned int im = 0 ; im < elesLVec.size() ; im++)
        {
          if(elesFlagVeto[im] && elesLVec[im].Pt()>(AnaConsts::elesMiniIsoArr).minPt && fabs(elesLVec[im].Eta()) < (AnaConsts::elesMiniIsoArr).maxAbsEta && elesMiniIso[im] < (AnaConsts::elesMiniIsoArr).maxIsoEB )
          {
            this_els_pt  = ( elesLVec.at(im) ).Pt();
            this_els_eta = ( elesLVec.at(im) ).Eta();
            this_els_phi = ( elesLVec.at(im) ).Phi();
          }
        }
        if(this_els_pt>0)
        {
          double deltaphi_els = DeltaPhi( this_els_phi , metphi );
          double thismtwel = std::sqrt( 2.0 * this_els_pt * met * ( 1.0 - cos(deltaphi_els) ) );
          if(thismtwel<cut_mtwel) pass0mu1elmtwel = true;
        }
      }

      selectedTree->Fill();
    }
    else continue;
  }
  selectedTree->Write();
  output->Write(); 
  output->Close();

  if (originalTree) delete originalTree;

  std::string d = "root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15";
  std::system(("xrdcp " + output_str + " " + d).c_str());
  std::system(("rm " + output_str).c_str());

  return 0;
}
