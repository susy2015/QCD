#ifndef _QCDTFTrimAndSlimCommon_H_
#define _QCDTFTrimAndSlimCommon_H_

#include <string>
#include <iostream>
#include <vector>

#include "SusyAnaTools/Tools/NTupleReader.h"
#include "SusyAnaTools/Tools/baselineDef.h"
#include "SusyAnaTools/Tools/ISRCorrector.h"
#include "SusyAnaTools/Tools/BTagCorrector.h"

const double trigger_turn_on_met = 200;
const double cut_mtwmu = 100;
const double cut_mtwel = 100;
const int nth_slash_nametag_MC = 10;
const int nth_slash_nametag_Data = 10;
//root://cmseos.fnal.gov//store/user/lpcsusyhad/Stop_production/Summer16_80X_Mar_2017_Ntp_v13X//MET/Summer16_80X_Mar_2017_Ntp_v13p0_MET-Run2016B-03Feb2017_ver2-v2/170303_234607/0000/stopFlatNtuples_102.root


bool useNewTagger = true;
bool useLegacycfg = false;

inline size_t find_Nth
(
  const std::string & str ,   // where to work
  unsigned            N ,     // N'th ocurrence
  const std::string & find    // what to 'find'
)
{
  if ( 0==N ) { return std::string::npos; }
  size_t pos,from=0;
  unsigned i=0;
  while ( i<N )
  {
    pos=str.find(find,from);
    if ( std::string::npos == pos ) { break; }
    from = pos + 1; // from = pos + find.size();
    ++i;
  }
  return pos;
}

std::string QCDOutputFileNameGenerator(std::string input_str,bool isData)
{
  //here is a little bit tricky when dealing with the slash... need to improve
  std::string tag = "";
  if(isData) tag = input_str.substr(find_Nth(input_str,nth_slash_nametag_Data,"/") + 1,find_Nth(input_str,nth_slash_nametag_Data+1,"/")-find_Nth(input_str,nth_slash_nametag_Data,"/")-1);
  else tag = input_str.substr(find_Nth(input_str,nth_slash_nametag_MC,"/") + 1,find_Nth(input_str,nth_slash_nametag_MC+1,"/")-find_Nth(input_str,nth_slash_nametag_MC,"/")-1);
  std::size_t idpos = input_str.find("stopFlatNtuples");
  std::string fileid = input_str.substr (idpos);
  std::string output_str = "QCDTFTrimAndSlim_" + tag + "_" + fileid;
  std::cout << "Output File Name: " << output_str << std::endl;
  return output_str;
}

std::string ISRAndBTagStringConverter(std::string QCDoutputFileName)
{
  std::string histTag = "";
  if     ( QCDoutputFileName.find("_TTJets_SingleLeptFromT_"   ) != std::string::npos ) histTag = "TTbarSingleLepT"   ;
  else if( QCDoutputFileName.find("_TTJets_SingleLeptFromTbar_") != std::string::npos ) histTag = "TTbarSingleLepTbar";
  else if( QCDoutputFileName.find("_TTJets_DiLept_"            ) != std::string::npos ) histTag = "TTbarDiLep"        ;
  else if( QCDoutputFileName.find("_TTJets_HT-600to800_"       ) != std::string::npos ) histTag = "TTbar_HT-600to800"  ;
  else if( QCDoutputFileName.find("_TTJets_HT-800to1200_"      ) != std::string::npos ) histTag = "TTbar_HT-800to1200" ;
  else if( QCDoutputFileName.find("_TTJets_HT-1200to2500_"     ) != std::string::npos ) histTag = "TTbar_HT-1200to2500";
  else if( QCDoutputFileName.find("_TTJets_HT-2500toInf_"      ) != std::string::npos ) histTag = "TTbar_HT-2500toInf" ;
  else if( QCDoutputFileName.find("_WJetsToLNu_HT-70To100_"    ) != std::string::npos ) histTag = "WJetsToLNu_HT_70to100"   ;
  else if( QCDoutputFileName.find("_WJetsToLNu_HT-100To200_"   ) != std::string::npos ) histTag = "WJetsToLNu_HT_100to200"  ;
  else if( QCDoutputFileName.find("_WJetsToLNu_HT-200To400_"   ) != std::string::npos ) histTag = "WJetsToLNu_HT_200to400"  ;
  else if( QCDoutputFileName.find("_WJetsToLNu_HT-400To600_"   ) != std::string::npos ) histTag = "WJetsToLNu_HT_400to600"  ;
  else if( QCDoutputFileName.find("_WJetsToLNu_HT-600To800_"   ) != std::string::npos ) histTag = "WJetsToLNu_HT_600to800"  ;
  else if( QCDoutputFileName.find("_WJetsToLNu_HT-800To1200_"  ) != std::string::npos ) histTag = "WJetsToLNu_HT_800to1200" ;
  else if( QCDoutputFileName.find("_WJetsToLNu_HT-1200To2500_" ) != std::string::npos ) histTag = "WJetsToLNu_HT_1200to2500";
  else if( QCDoutputFileName.find("_WJetsToLNu_HT-2500ToInf_"  ) != std::string::npos ) histTag = "WJetsToLNu_HT_2500toInf" ;
  else if( QCDoutputFileName.find("_ST_tW_top_5f_inclusiveDecays_"          ) != std::string::npos ) histTag = "tW_top_incl";
  else if( QCDoutputFileName.find("_ST_tW_antitop_5f_inclusiveDecays_"      ) != std::string::npos ) histTag = "tW_antitop_incl";
  else if( QCDoutputFileName.find("_ST_tW_top_5f_NoFullyHadronicDecays_"    ) != std::string::npos ) histTag = "tW_top_NoHad";
  else if( QCDoutputFileName.find("_ST_tW_antitop_5f_NoFullyHadronicDecays_") != std::string::npos ) histTag = "tW_antitop_NoHad";
  else if( QCDoutputFileName.find("_ZJetsToNuNu_HT-100To200_"  ) != std::string::npos ) histTag = "ZJetsToNuNu_HT_100to200"  ;
  else if( QCDoutputFileName.find("_ZJetsToNuNu_HT-200To400_"  ) != std::string::npos ) histTag = "ZJetsToNuNu_HT_200to400"  ;
  else if( QCDoutputFileName.find("_ZJetsToNuNu_HT-400To600_"  ) != std::string::npos ) histTag = "ZJetsToNuNu_HT_400to600"  ;
  else if( QCDoutputFileName.find("_ZJetsToNuNu_HT-600To800_"  ) != std::string::npos ) histTag = "ZJetsToNuNu_HT_600to800"  ;
  else if( QCDoutputFileName.find("_ZJetsToNuNu_HT-800To1200_" ) != std::string::npos ) histTag = "ZJetsToNuNu_HT_800to1200" ;
  else if( QCDoutputFileName.find("_ZJetsToNuNu_HT-1200To2500_") != std::string::npos ) histTag = "ZJetsToNuNu_HT_1200to2500";
  else if( QCDoutputFileName.find("_ZJetsToNuNu_HT-2500ToInf_" ) != std::string::npos ) histTag = "ZJetsToNuNu_HT_2500toInf" ;
  else if( QCDoutputFileName.find("_QCD_HT100to200_"           ) != std::string::npos && !(QCDoutputFileName.find("BFilter") != std::string::npos) ) histTag = "QCD_HT100to200"  ;
  else if( QCDoutputFileName.find("_QCD_HT200to300_"           ) != std::string::npos && !(QCDoutputFileName.find("BFilter") != std::string::npos) ) histTag = "QCD_HT200to300"  ;
  else if( QCDoutputFileName.find("_QCD_HT300to500_"           ) != std::string::npos && !(QCDoutputFileName.find("BFilter") != std::string::npos) ) histTag = "QCD_HT300to500"  ;
  else if( QCDoutputFileName.find("_QCD_HT500to700_"           ) != std::string::npos && !(QCDoutputFileName.find("BFilter") != std::string::npos) ) histTag = "QCD_HT500to700"  ;
  else if( QCDoutputFileName.find("_QCD_HT700to1000_"          ) != std::string::npos && !(QCDoutputFileName.find("BFilter") != std::string::npos) ) histTag = "QCD_HT700to1000" ;
  else if( QCDoutputFileName.find("_QCD_HT1000to1500_"         ) != std::string::npos && !(QCDoutputFileName.find("BFilter") != std::string::npos) ) histTag = "QCD_HT1000to1500";
  else if( QCDoutputFileName.find("_QCD_HT1500to2000_"         ) != std::string::npos && !(QCDoutputFileName.find("BFilter") != std::string::npos) ) histTag = "QCD_HT1500to2000";
  else if( QCDoutputFileName.find("_QCD_HT2000toInf_"          ) != std::string::npos && !(QCDoutputFileName.find("BFilter") != std::string::npos) ) histTag = "QCD_HT2000toInf" ;
  else if( QCDoutputFileName.find("_QCD_HT200to300_BFilter_"   ) != std::string::npos ) histTag = "QCD_HT200to300_BGenFilter"  ;
  else if( QCDoutputFileName.find("_QCD_HT300to500_BFilter_"   ) != std::string::npos ) histTag = "QCD_HT300to500_BGenFilter"  ;
  else if( QCDoutputFileName.find("_QCD_HT500to700_BFilter_"   ) != std::string::npos ) histTag = "QCD_HT500to700_BGenFilter"  ;
  else if( QCDoutputFileName.find("_QCD_HT700to1000_BFilter_"  ) != std::string::npos ) histTag = "QCD_HT700to1000_BGenFilter" ;
  else if( QCDoutputFileName.find("_QCD_HT1000to1500_BFilter_" ) != std::string::npos ) histTag = "QCD_HT1000to1500_BGenFilter";
  else if( QCDoutputFileName.find("_QCD_HT1500to2000_BFilter_" ) != std::string::npos ) histTag = "QCD_HT1500to2000_BGenFilter";
  else if( QCDoutputFileName.find("_QCD_HT2000toInf_BFilter_"  ) != std::string::npos ) histTag = "QCD_HT2000toInf_BGenFilter" ;
  else if( QCDoutputFileName.find("_TTWJetsToLNu_"             ) != std::string::npos ) histTag = "TTWJetsToLNu";
  else if( QCDoutputFileName.find("_TTWJetsToQQ_"              ) != std::string::npos ) histTag = "TTWJetsToQQ" ;
  else if( QCDoutputFileName.find("_TTZToLLNuNu_"              ) != std::string::npos ) histTag = "TTZToLLNuNu" ;
  else if( QCDoutputFileName.find("_TTZToQQ_"                  ) != std::string::npos ) histTag = "TTZToQQ"     ;
  else if( QCDoutputFileName.find("_WWTo2L2Nu_"                ) != std::string::npos ) histTag = "WWTo2L2Nu";
  else if( QCDoutputFileName.find("_WWTo4Q_"                   ) != std::string::npos ) histTag = "WWTo4Q"   ;
  else if( QCDoutputFileName.find("_WWToLNuQQ_"                ) != std::string::npos ) histTag = "WWToLNuQQ";
  else if( QCDoutputFileName.find("_WZ_"                       ) != std::string::npos ) histTag = "WZ";
  else if( QCDoutputFileName.find("_ZZTo2L2Nu_"                ) != std::string::npos ) histTag = "ZZTo2L2Nu";
  else if( QCDoutputFileName.find("_ZZTo2L2Q_"                 ) != std::string::npos ) histTag = "ZZTo2L2Q" ;
  else if( QCDoutputFileName.find("_ZZTo2Q2Nu_"                ) != std::string::npos ) histTag = "ZZTo2Q2Nu";
  else if( QCDoutputFileName.find("_ZZTo4L_"                   ) != std::string::npos ) histTag = "ZZTo4L"   ;
  else if( QCDoutputFileName.find("_ZZTo4Q_"                   ) != std::string::npos ) histTag = "ZZTo4Q"   ;
  else if( QCDoutputFileName.find("_WWW_"                      ) != std::string::npos ) histTag = "WWW";
  else if( QCDoutputFileName.find("_WWZ_"                      ) != std::string::npos ) histTag = "WWZ";
  else if( QCDoutputFileName.find("_WWG_"                      ) != std::string::npos ) histTag = "WWG";
  else if( QCDoutputFileName.find("_WZG_"                      ) != std::string::npos ) histTag = "WZG";
  else if( QCDoutputFileName.find("_WZZ_"                      ) != std::string::npos ) histTag = "WZZ";
  else if( QCDoutputFileName.find("_ZZZ_"                      ) != std::string::npos ) histTag = "ZZZ";
  else histTag = "histTagNotFound";
  //else if( QCDoutputFileName.find("") != std::string::npos ) histTag = "";
  return histTag;
}

void ISRReWeightingSet(NTupleReader &mytr, std::string outputFileName)
{
  ISRCorrector *isrcorr = new ISRCorrector("allINone_ISRJets.root","","");
  std::string histTag = ISRAndBTagStringConverter(outputFileName);
  isrcorr->resetSample(histTag);
  mytr.registerFunction((*isrcorr));
  return ;
}

void BTagReWeightingSet(NTupleReader &mytr, std::string outputFileName)
{
  BTagCorrector *btagcorr = new BTagCorrector("allINone_bTagEff.root");
  std::string histTag = ISRAndBTagStringConverter(outputFileName);
  btagcorr->resetEffs(histTag);
  mytr.registerFunction((*btagcorr));
  return ;
}

#endif
