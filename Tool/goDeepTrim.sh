#!/bin/bash

export PATH=${PATH}:/cvmfs/cms.cern.ch/common
export CMS_PATH=/cvmfs/cms.cern.ch

cd $1/src
eval `scramv1 runtime -sh`

#cd $1/src/QCD/Tool/QCDStopFlattrees
cd ${_CONDOR_SCRATCH_DIR}
#cd .

python NTuple_DeepTrim.py $2

#find . -name "*.root" -exec xrdcp {} "root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15/" \;
#find . -name "*.root" -exec rm {} \;
