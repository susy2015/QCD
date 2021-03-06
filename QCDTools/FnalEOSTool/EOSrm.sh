#!/bin/bash
export PATH=${PATH}:/cvmfs/cms.cern.ch/common
export CMS_PATH=/cvmfs/cms.cern.ch

#cd $1/src
eval `scramv1 runtime -sh`

#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'DeepTrimmd_Spring16_80X_Jun_2016_Ntp_v5p0_TTJets_DiLeptstopFlatNtuples_.*root'` 
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15/QCD_Data_2017Moriondv11p3 | grep -E 'QCDTFTrimAndSlim_Spring16_80X_Nov_2016_Ntp_v11p0_new_IDs_QCD_HT.*root'` 
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'QCDTFTrimAndSlim_.*root'` 
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'SignalStudy_.*root'`
for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'Summer16_80X_Mar_2017_Ntp_v13p0_.*txt'`
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15/QCD_DataMC_2016ICHEPv7_CSV_fix | grep -E 'QCDTFTrimAndSlim_.*root'`
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'DeepTrimmd_.*root'` 
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'QCDTFTrimAndSlim_Summer16_80X_Jan_2017_Ntp_v12p0_MET-Run2016.*root'`
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'QCDTFTrimAndSlim_stopFlatNtuples_.*root'` 
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'DeepTrimmd_.*root'`
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15/LL_DataMC_2017Moriondv11p5c_ReRunData  | grep -E 'DeepTrimmd_.*root'`
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'TopTaggerTrimmed_.*root'`
#for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'SFCheckTrimmed_.*root'`
do 
  eos root://cmseos.fnal.gov/ rm $i .
done

