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
#include "TInterpreter.h"

#include "SusyAnaTools/Tools/samples.h"
#include "SusyAnaTools/Tools/searchBins.h"

#include "EventPick.h"

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cerr <<"Please give 1 argument " << "inputFileName " << std::endl;
    std::cerr <<"Valid configurations are: " << std::endl;
    std::cerr <<"./EventPick root://cmseos.fnal.gov//store/user/lpcsusyhad/Spring15_74X_Oct_2015_Ntp_v2X/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/QCD_HT500to700_Spring15DR74_Asympt25ns_Ntp_v2/150928_140039/0000/stopFlatNtuples_1.root" << std::endl;
    return -1;
  }
  std::string input_str(argv[1]);

  TChain *originalTree = new TChain("stopTreeMaker/AUX");
  originalTree->Add(input_str.c_str());
  originalTree->SetBranchStatus("*", 1);
   
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

  //here is a little bit tricky when dealing with the slash... need to improve
  //for all the MC samples
  //std::string tag = input_str.substr(find_Nth(input_str,10,"/") + 1,find_Nth(input_str,11,"/")-find_Nth(input_str,10,"/")-1);
  //for all the data samples
  std::string tag = input_str.substr(find_Nth(input_str,10,"/") + 1,find_Nth(input_str,11,"/")-find_Nth(input_str,10,"/")-1);
  std::size_t begin = input_str.find("stopFlatNtuples");
  std::size_t end = input_str.find(".root");
  std::string fileid = input_str.substr(begin,end);
  EventInfo myEventInfo_2t_1j2j;
  myEventInfo_2t_1j2j.EvtTxtName = tag + "_" + fileid + ".2t_1j2j.txt";
  EventInfo myEventInfo_2t_1j3j;
  myEventInfo_2t_1j3j.EvtTxtName = tag + "_" + fileid + ".2t_1j3j.txt";
  EventInfo myEventInfo_2t_2j3j;
  myEventInfo_2t_2j3j.EvtTxtName = tag + "_" + fileid + ".2t_2j3j.txt";
  EventInfo myEventInfo_2t_1j1j;
  myEventInfo_2t_1j1j.EvtTxtName = tag + "_" + fileid + ".2t_1j1j.txt";
  EventInfo myEventInfo_2t_2j2j;
  myEventInfo_2t_2j2j.EvtTxtName = tag + "_" + fileid + ".2t_2j2j.txt";
  EventInfo myEventInfo_2t_3j3j;
  myEventInfo_2t_3j3j.EvtTxtName = tag + "_" + fileid + ".2t_3j3j.txt";

  while(tr->getNextEvent())
  {
    unsigned int run             = tr->getVar<unsigned int>("run");
    unsigned int lumi            = tr->getVar<unsigned int>("lumi");
    unsigned long long int event = tr->getVar<unsigned long long int>("event");
 
    int ntopjets = tr->getVar<int>("nTopCandSortedCnt"+spec);
    const std::map<int, std::vector<TLorentzVector>> &mtopjets = tr->getMap<int, std::vector<TLorentzVector>>("mTopJets"+spec);
    bool passBaseline = (tr->getVar<bool>("passBaseline"+spec)) && (tr->getVar<bool>("passLeptVeto"+spec));
   
    bool dit_1j2j=false, dit_1j3j=false, dit_2j3j=false, dit_1j1j=false, dit_2j2j=false, dit_3j3j=false;

    if( passBaseline )
    {
      if(ntopjets==2)
      {
        std::cout << "NTops: " << ntopjets << std::endl;
        bool monojet=false, dijet=false, trijet=false;
        for(auto &topit  : mtopjets)
        {
          std::cout << "Top ID: " << topit.first << " nSubJets: " << (topit.second).size() << std::endl;
          int nsubjets=(topit.second).size();
          if     (nsubjets==1) monojet=true;
          else if(nsubjets==2) dijet=true;
          else if(nsubjets==3) trijet=true;
          else std::cout<<"Not monojet, dijet or trijet case!" << std::endl;
        }
        dit_1j2j = monojet && dijet && (!trijet);    dit_1j3j = monojet && (!dijet) && trijet;    dit_2j3j = (!monojet) && dijet && trijet;
        dit_1j1j = monojet && (!dijet) && (!trijet); dit_2j2j = (!monojet) && dijet && (!trijet); dit_3j3j = (!monojet) && (!dijet) && trijet;
      
        if(dit_1j2j){ myEventInfo_2t_1j2j.run.push_back(run); myEventInfo_2t_1j2j.lumi.push_back(lumi); myEventInfo_2t_1j2j.event.push_back(event); }
        if(dit_1j3j){ myEventInfo_2t_1j3j.run.push_back(run); myEventInfo_2t_1j3j.lumi.push_back(lumi); myEventInfo_2t_1j3j.event.push_back(event); }
        if(dit_2j3j){ myEventInfo_2t_2j3j.run.push_back(run); myEventInfo_2t_2j3j.lumi.push_back(lumi); myEventInfo_2t_2j3j.event.push_back(event); }
        if(dit_1j1j){ myEventInfo_2t_1j1j.run.push_back(run); myEventInfo_2t_1j1j.lumi.push_back(lumi); myEventInfo_2t_1j1j.event.push_back(event); }
        if(dit_2j2j){ myEventInfo_2t_2j2j.run.push_back(run); myEventInfo_2t_2j2j.lumi.push_back(lumi); myEventInfo_2t_2j2j.event.push_back(event); }
        if(dit_3j3j){ myEventInfo_2t_3j3j.run.push_back(run); myEventInfo_2t_3j3j.lumi.push_back(lumi); myEventInfo_2t_3j3j.event.push_back(event); }
      }
      else continue;
    }
  }

  if (originalTree) delete originalTree;
  
  std::string d = "root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15";

  myEventInfo_2t_1j2j.ZSxrdcp(d);
  myEventInfo_2t_1j3j.ZSxrdcp(d);
  myEventInfo_2t_2j3j.ZSxrdcp(d);
  myEventInfo_2t_1j1j.ZSxrdcp(d);
  myEventInfo_2t_2j2j.ZSxrdcp(d);
  myEventInfo_2t_3j3j.ZSxrdcp(d);

  return 0;
}
