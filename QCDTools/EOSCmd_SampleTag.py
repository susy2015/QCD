import glob, os, sys

d_hadd_source = "/store/group/lpcsusyhad/hua/Skimmed_2015Nov15"
#d_final_target = "/store/group/lpcsusyhad/hua/Skimmed_2015Nov15/QCD_Data_2016ICHEPv9"
#d_final_target = "/store/group/lpcsusyhad/hua/Skimmed_2015Nov15/LL_Data_2016ICHEPv9"
d_final_target = "/store/group/lpcsusyhad/hua/Skimmed_2015Nov15/SFCheckTrim_2016Sep"

MGM = "root://cmseos.fnal.gov/"

sample_tag_list_Data = [
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_FINAL_HTMHT-Run2016B-PromptReco-v2_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_FINAL_HTMHT-Run2016C-PromptReco-v2_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_FINAL_HTMHT-Run2016D-PromptReco-v2_stopFlatNtuples_",
                       ]

sample_tag_list_LLHadTau = [
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_SingleLeptFromT_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_SingleLeptFromT_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_SingleLeptFromTbar_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_SingleLeptFromTbar_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_DiLept_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_DiLept_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-400To600_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-400To600_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-600To800_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-800To1200_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-800To1200_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-1200To2500_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-1200To2500_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-2500ToInf_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_ST_tW_top_5f_inclusiveDecays_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_ST_tW_antitop_5f_inclusiveDecays_stopFlatNtuples_",
                           ]

sample_tag_list_Zinv = [
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_ZJetsToNuNu_HT-400To600_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_ZJetsToNuNu_HT-600To800_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_ZJetsToNuNu_HT-800To1200_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_ZJetsToNuNu_HT-1200To2500_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_ZJetsToNuNu_HT-1200To2500_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_ZJetsToNuNu_HT-2500ToInf_stopFlatNtuples_",
                       ]

sample_tag_list_QCD = [
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_QCD_HT500to700_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_QCD_HT500to700_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_QCD_HT700to1000_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_QCD_HT700to1000_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_QCD_HT1000to1500_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_QCD_HT1000to1500_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_QCD_HT1500to2000_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_QCD_HT1500to2000_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_QCD_HT2000toInf_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_QCD_HT2000toInf_ext1_stopFlatNtuples_",
                      ]

sample_tag_list_TTZ = [
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTWJetsToLNu_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTWJetsToQQ_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTZToLLNuNu_stopFlatNtuples_",
"QCDTFTrimAndSlim_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTZToQQ_stopFlatNtuples_",
                      ]

sample_tag_list_DeepTrim = [
"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_FINAL_HTMHT-Run2016B-PromptReco-v2_stopFlatNtuples_",
"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_FINAL_HTMHT-Run2016C-PromptReco-v2_stopFlatNtuples_",
"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_FINAL_HTMHT-Run2016D-PromptReco-v2_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_SingleLeptFromT_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_SingleLeptFromT_ext1_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_SingleLeptFromTbar_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_SingleLeptFromTbar_ext1_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_DiLept_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_DiLept_ext1_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-400To600_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-400To600_ext1_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-600To800_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-800To1200_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-800To1200_ext1_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-1200To2500_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-1200To2500_ext1_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-2500ToInf_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_ST_tW_top_5f_inclusiveDecays_stopFlatNtuples_",
#"DeepTrimmd_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_ST_tW_antitop_5f_inclusiveDecays_stopFlatNtuples_",
                           ]

sample_tag_list_SFCheckTrim = [
"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_FINAL_HTMHT-Run2016B-PromptReco-v2_stopFlatNtuples_",
"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_FINAL_HTMHT-Run2016C-PromptReco-v2_stopFlatNtuples_",
"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_FINAL_HTMHT-Run2016D-PromptReco-v2_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_SingleLeptFromT_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_SingleLeptFromT_ext1_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_SingleLeptFromTbar_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_SingleLeptFromTbar_ext1_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_DiLept_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_TTJets_DiLept_ext1_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-400To600_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-400To600_ext1_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-600To800_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-800To1200_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-800To1200_ext1_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-1200To2500_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-1200To2500_ext1_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_WJetsToLNu_HT-2500ToInf_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_ST_tW_top_5f_inclusiveDecays_stopFlatNtuples_",
#"SFCheckTrimmed_Spring16_80X_Jul_2016_Ntp_v8p0_new_JEC_new_muonID_top_up_ST_tW_antitop_5f_inclusiveDecays_stopFlatNtuples_",
                           ]

#example of sample tag: SSTrimmed_SMS-T2tt_mStop-850_mLSP-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_stopFlatNtuples_, always end with "_"
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
elif(sample_tag == 'SFCheckTrim') :
  sample_tag_list = sample_tag_list_SFCheckTrim
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

