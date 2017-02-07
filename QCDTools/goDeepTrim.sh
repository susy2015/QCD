#!/bin/bash

export PATH=${PATH}:/cvmfs/cms.cern.ch/common
export CMS_PATH=/cvmfs/cms.cern.ch
#export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$1/src/QCD/QCDTools/obj:$1/src/TopTagger/TopTagger/test:$1/src/opencv/lib:$1/lib/slc6_amd64_gcc530

tar -xzf CMSSW_8_0_23.tar.gz
cd CMSSW_8_0_23
source /cvmfs/cms.cern.ch/cmsset_default.sh
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${_CONDOR_SCRATCH_DIR}/CMSSW_8_0_23/src/SusyAnaTools/Tools/obj:${_CONDOR_SCRATCH_DIR}/CMSSW_8_0_23/src/TopTagger/TopTagger/test:${_CONDOR_SCRATCH_DIR}/CMSSW_8_0_23/src/opencv/lib:${_CONDOR_SCRATCH_DIR}/CMSSW_8_0_23/lib/slc6_amd64_gcc530
# cmsenv
eval `scramv1 runtime -sh`

#cd $1/src
#eval `scramv1 runtime -sh`

cd ${_CONDOR_SCRATCH_DIR}
python NTuple_DeepTrim.py $2

#find . -name "*.root" -exec xrdcp {} "root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15/" \;
#find . -name "*.root" -exec rm {} \;
