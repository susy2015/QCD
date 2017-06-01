#!/bin/bash
export PATH=${PATH}:/cvmfs/cms.cern.ch/common
export CMS_PATH=/cvmfs/cms.cern.ch

eval `scramv1 runtime -sh`

for i in `xrdfs root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15 | grep -E 'Summer16_80X_Mar_2017_Ntp_v13p0_.*txt'` 
do 
  xrdcp root://cmseos.fnal.gov/$i .
done

