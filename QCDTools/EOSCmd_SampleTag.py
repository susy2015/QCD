import glob, os, sys

d_hadd_source = "/store/group/lpcsusyhad/hua/Skimmed_2015Nov15"
#d_final_target = "/store/group/lpcsusyhad/hua/Skimmed_2015Nov15/QCD_DataMC_2016ICHEPv7_CSV_fix"
d_final_target = "/store/group/lpcsusyhad/hua/Skimmed_2015Nov15/LL_DataMC_2016ICHEPv7_CSV_fix"
MGM = "root://cmseos.fnal.gov/"

sample_tag_list_Data = [
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_HTMHT-Run2016B-PromptReco-v2stopFlatNtuples_",
                       ]

sample_tag_list_LLHadTau = [
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_TTJets_SingleLeptFromTstopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_TTJets_SingleLeptFromT_ext1stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_TTJets_SingleLeptFromTbarstopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_TTJets_SingleLeptFromTbar_ext1stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_TTJets_DiLeptstopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_TTJets_DiLept_ext1stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-400To600stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-400To600_ext1stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-600To800stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-800To1200stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-800To1200_ext1stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-1200To2500stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-1200To2500_ext1stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-2500ToInfstopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_ST_tW_top_5f_inclusiveDecaysstopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_ST_tW_antitop_5f_inclusiveDecaysstopFlatNtuples_",
                           ]

sample_tag_list_Zinv = [
"QCDTFTrimAndSlim_Spring15_74X_Feb_2016_Ntp_v6p0_forMoriond_ZJetsToNuNu_HT-400To600stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring15_74X_Feb_2016_Ntp_v6p0_forMoriond_ZJetsToNuNu_HT-400To600_ext1stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_ZJetsToNuNu_HT-600To800stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_ZJetsToNuNu_HT-800To1200stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_ZJetsToNuNu_HT-1200To2500stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_ZJetsToNuNu_HT-2500ToInfstopFlatNtuples_",
                       ]

sample_tag_list_QCD = [
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_QCD_HT500to700stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_QCD_HT500to700_ext1stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_QCD_HT700to1000stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_QCD_HT700to1000_ext1stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_QCD_HT1000to1500stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_QCD_HT1000to1500_ext1stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_QCD_HT1500to2000stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_QCD_HT1500to2000_extstopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_QCD_HT2000toInfstopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_QCD_HT2000toInf_ext1stopFlatNtuples_",
                      ]

sample_tag_list_TTZ = [
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v6p0_fix_topProj_wt_data_topoff_TTWJetsToLNustopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v6p0_fix_topProj_wt_data_topoff_TTWJetsToQQstopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v6p0_fix_topProj_wt_data_topoff_TTZToLLNuNustopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v6p0_fix_topProj_wt_data_topoff_TTZToQQstopFlatNtuples_",
                      ]

sample_tag_list_DeepTrim = [
#"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_HTMHT-Run2016B-PromptReco-v2stopFlatNtuples_",
"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_TTJets_SingleLeptFromTstopFlatNtuples_",
"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_TTJets_SingleLeptFromT_ext1stopFlatNtuples_",
"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_TTJets_SingleLeptFromTbarstopFlatNtuples_",
"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_TTJets_SingleLeptFromTbar_ext1stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_TTJets_DiLeptstopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_TTJets_DiLept_ext1stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-400To600stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-400To600_ext1stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-600To800stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-800To1200stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-800To1200_ext1stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-1200To2500stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-1200To2500_ext1stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_WJetsToLNu_HT-2500ToInfstopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_ST_tW_top_5f_inclusiveDecaysstopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v7p0_new_JEC_new_filters_4ifb_ST_tW_antitop_5f_inclusiveDecaysstopFlatNtuples_",
                           ]

#example of sample tag: SSTrimmed_SMS-T2tt_mStop-850_mLSP-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8stopFlatNtuples_, always end with "_"
sample_tag = sys.argv[1]

sample_tag_list = []

if(sample_tag == 'Data') :
  sample_tag_list = sample_tag_list_Data
elif(sample_tag == 'LLHadTau') :
  sample_tag_list = sample_tag_list_LLHadTau
elif(sample_tag == 'Zinv') :
  sample_tag_list = sample_tag_list_Zinv
elif(sample_tag == 'QCD') :
  sample_tag_list = sample_tag_list_QCD
elif(sample_tag == 'TTZ') :
  sample_tag_list = sample_tag_list_TTZ
elif(sample_tag == 'DeepTrim') :
  sample_tag_list = sample_tag_list_DeepTrim
else:
  print "wrong run type!"

for tag in sample_tag_list :
  #hadd
  cmd = 'hadd ' + tag[:-1] + '.root `xrdfsls -u ' + d_hadd_source + ' | grep \'' + tag + '\'`'
  print(cmd)
  #os.system(cmd)
  cmd = 'xrdcp ' + tag[:-1] + '.root ' + MGM + d_final_target
  print(cmd)

  #xrdcp root://cmseos.fnal.gov//store/user/jjesus/EOSFile.txt \? root://cmseos.fnal.gov//store/user/jjesus/EOSFile1.txt
  #cmd = 'xrdcp ' + MGM + d_hadd_source + '/' + tag[:-1] + '.root ' + MGM + d_final_target + '/' + tag[:-1] + '.root' 
  #print(cmd)
  #cmd = 'eosrm ' + d_hadd_source + '/' + tag[:-1] + '.root'
  #print(cmd)

