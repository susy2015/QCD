#!/bin/bash
export PATH=${PATH}:/cvmfs/cms.cern.ch/common
export CMS_PATH=/cvmfs/cms.cern.ch

#cd $1/src
eval `scramv1 runtime -sh`

#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v5p0_TTJets_DiLeptstopFlatNtuples_.*root'` 
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15/QCD_DataMC_2016ICHEPv5 | grep -E 'QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v5p0_QCD_.*root'` 
for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'QCDTFTrimAndSlim_.*root'` 
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v6p0_fix_topProj_wt_data_topoff_WJetsToLNu_HT-.*root'` 
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v6p0_fix_topProj_wt_data_topoff_ST_tW_.*root'`
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'QCDTFTrimAndSlim_Spring16_80X_Jun_2016_Ntp_v7p0_.*root'`
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'QCDTFTrimAndSlim_stopFlatNtuples_.*root'` 
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'DeepTrimmd_.*root'`
do 
  eos root://cmseos.fnal.gov/ rm $i .
done

