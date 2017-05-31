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
  std::string tag = input_str.substr(find_Nth(input_str,11,"/") + 1,find_Nth(input_str,12,"/")-find_Nth(input_str,11,"/")-1);
  std::size_t begin = input_str.find("stopFlatNtuples");
  std::size_t end = input_str.find(".root");
  std::string fileid = input_str.substr(begin,end);
  EventInfo myEventInfo;
  myEventInfo.OutTxtName = tag + "_" + fileid + ".txt";

  while(tr->getNextEvent())
  {
    int run   = tr->getVar<int>("run");
    int lumi  = tr->getVar<int>("lumi");
    int event = tr->getVar<int>("event");
 
    int ntopjets = tr->getVar<int>("nTopCandSortedCnt"+spec);
		std::vector<std::pair<int, std::vector<TLorentzVector>>> topjetmap = tr->getVec<std::pair<int, std::vector<TLorentzVector>>>("mTopJets"+spec);
    /*
    std::vector<TLorentzVector> *vTops;
    const TopTaggerResults& ttr = myBaselineVessel->ttPtr->getResults();
    std::vector<TopObject*> Ntop = ttr.getTops();  
    int ntopjets = Ntop.size();
    for(int it=0; it<ntopjets; it++)
    {
      vTops->push_back(Ntop.at(it)->P());
      std::vector<TLorentzVector> temp;
      for(auto j : Ntop.at(it)->getConstituents())
      {
        temp.push_back(j->P());
      }
      topjetmap->insert(std::make_pair(it, temp));
    }
    */
    std::cout << "NTops: " << ntopjets << std::endl;
    for(std::vector<std::pair<int, std::vector<TLorentzVector>>>::iterator it = topjetmap.begin(); it != topjetmap.end(); ++it) 
    {
      std::cout << "Top ID: " << it->first << " nSubJets: " << (it->second).size() << std::endl;
    }
    myEventInfo.run.push_back(run);
    myEventInfo.lumi.push_back(lumi);
    myEventInfo.event.push_back(event);

    /*
    double met = tr->getVar<double>("met");
    double ht = tr->getVar<double>("HT"+spec);
    int njetspt30 = tr->getVar<int>("cntNJetsPt30"+spec);
    int nmus = tr->getVar<int>("nMuons_CUT"+spec);
    int nels = tr->getVar<int>("nElectrons_CUT"+spec);

    bool passSFCheckTrim = false;
    passSFCheckTrim = ( met > 250 )
                   && ( ht > 250 )
                   && ( njetspt30 > 1 )
                   && ( (nmus==1 && nels == 0) || (nmus==0 && nels == 1) );
    */
  }

  if (originalTree) delete originalTree;
  myEventInfo.EventTxtProducer();
  return 0;
}
