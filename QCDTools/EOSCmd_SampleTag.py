import glob, os, sys

d_hadd_source = "/store/group/lpcsusyhad/hua/Skimmed_2015Nov15"
d_final_target = "/store/group/lpcsusyhad/hua/Skimmed_2015Nov15/QCD_Data_2017Moriondv12p5c"
#d_final_target = "/store/group/lpcsusyhad/hua/Skimmed_2015Nov15/LL_DataMC_2017Moriondv12p5c"
#d_final_target = "/store/group/lpcsusyhad/hua/Skimmed_2015Nov15/SFCheckTrim_2016Sep"

MGM = "root://cmseos.fnal.gov/"

sample_tag_list_Data = [
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016B-23Sep2016-v3_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016C-23Sep2016-v1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016D-23Sep2016-v1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016E-23Sep2016-v1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016F-23Sep2016-v1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016G-23Sep2016-v1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016H-PromptReco-v2_stopFlatNtuples_",
                       ]

sample_tag_list_LLHadTau = [
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_SingleLeptFromT_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_SingleLeptFromT_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_SingleLeptFromTbar_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_SingleLeptFromTbar_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_DiLept_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_DiLept_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_HT-600to800_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_HT-800to1200_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_HT-1200to2500_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_HT-2500toInf_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-200To400_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-200To400_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-200To400_ext2_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-400To600_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-400To600_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-600To800_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-600To800_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-800To1200_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-800To1200_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-1200To2500_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-1200To2500_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-2500ToInf_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-2500ToInf_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_top_5f_inclusiveDecays_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_top_5f_NoFullyHadronicDecays_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_top_5f_NoFullyHadronicDecays_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_top_5f_NoFullyHadronicDecays_ext2_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_antitop_5f_inclusiveDecays_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_antitop_5f_NoFullyHadronicDecays_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_antitop_5f_NoFullyHadronicDecays_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_antitop_5f_NoFullyHadronicDecays_ext2_stopFlatNtuples_",
                           ]

sample_tag_list_Zinv = [
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZJetsToNuNu_HT-200To400_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZJetsToNuNu_HT-200To400_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZJetsToNuNu_HT-400To600_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZJetsToNuNu_HT-400To600_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZJetsToNuNu_HT-600To800_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZJetsToNuNu_HT-800To1200_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZJetsToNuNu_HT-1200To2500_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZJetsToNuNu_HT-1200To2500_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZJetsToNuNu_HT-2500ToInf_stopFlatNtuples_",
                       ]

sample_tag_list_QCD = [
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT200to300_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT200to300_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT200to300_BFilter_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT300to500_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT300to500_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT300to500_BFilter_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT500to700_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT500to700_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT500to700_BFilter_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT700to1000_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT700to1000_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT700to1000_BFilter_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT1000to1500_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT1000to1500_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT1000to1500_BFilter_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT1500to2000_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT1500to2000_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT1500to2000_BFilter_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT2000toInf_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT2000toInf_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_QCD_HT2000toInf_BFilter_stopFlatNtuples_",
                      ]

sample_tag_list_TTZ = [
#"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTWJetsToLNu_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTWJetsToLNu_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTWJetsToLNu_ext2_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTWJetsToQQ_stopFlatNtuples_",
#"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTZToLLNuNu_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTZToLLNuNu_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_TTZToQQ_stopFlatNtuples_",
##Di-boson
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZZTo4Q_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZZTo4L_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZZTo2Q2Nu_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZZTo2L2Q_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZZTo2L2Nu_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WZ_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WZ_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WWToLNuQQ_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WWToLNuQQ_ext1_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WWTo4Q_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WWTo2L2Nu_stopFlatNtuples_",
##Tri-boson
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WWW_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WWZ_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WZZ_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_ZZZ_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WZG_stopFlatNtuples_",
"QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_WWG_stopFlatNtuples_",
                      ]

sample_tag_list_DeepTrim = [
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016B-23Sep2016-v3_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016C-23Sep2016-v1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016D-23Sep2016-v1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016E-23Sep2016-v1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016F-23Sep2016-v1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016G-23Sep2016-v1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016H-PromptReco-v2_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_SingleLeptFromT_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_SingleLeptFromT_ext1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_SingleLeptFromTbar_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_SingleLeptFromTbar_ext1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_DiLept_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_DiLept_ext1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_HT-600to800_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_HT-800to1200_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_HT-1200to2500_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_HT-2500toInf_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-200To400_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-200To400_ext1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-200To400_ext2_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-400To600_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-400To600_ext1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-600To800_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-600To800_ext1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-800To1200_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-800To1200_ext1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-1200To2500_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-1200To2500_ext1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-2500ToInf_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-2500ToInf_ext1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_top_5f_inclusiveDecays_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_top_5f_NoFullyHadronicDecays_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_top_5f_NoFullyHadronicDecays_ext1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_top_5f_NoFullyHadronicDecays_ext2_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_antitop_5f_inclusiveDecays_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_antitop_5f_NoFullyHadronicDecays_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_antitop_5f_NoFullyHadronicDecays_ext1_stopFlatNtuples_",
"DeepTrimmd_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_antitop_5f_NoFullyHadronicDecays_ext2_stopFlatNtuples_",
                           ]

sample_tag_list_SFCheckTrim = [
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_FINAL_HTMHT-Run2016B-PromptReco-v2_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_FINAL_HTMHT-Run2016C-PromptReco-v2_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_FINAL_HTMHT-Run2016D-PromptReco-v2_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_SingleLeptFromT_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_SingleLeptFromT_ext1_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_SingleLeptFromTbar_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_SingleLeptFromTbar_ext1_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_DiLept_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_TTJets_DiLept_ext1_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-400To600_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-400To600_ext1_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-600To800_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-800To1200_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-800To1200_ext1_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-1200To2500_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-1200To2500_ext1_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_WJetsToLNu_HT-2500ToInf_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_top_5f_inclusiveDecays_stopFlatNtuples_",
#"SFCheckTrimmed_Summer16_80X_Jan_2017_Ntp_v12p0_ST_tW_antitop_5f_inclusiveDecays_stopFlatNtuples_",
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

