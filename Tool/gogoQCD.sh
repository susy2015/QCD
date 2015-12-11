#!/bin/bash

export PATH=${PATH}:/cvmfs/cms.cern.ch/common
export CMS_PATH=/cvmfs/cms.cern.ch

cd $4/src
eval `scramv1 runtime -sh`

cd $4/src/QCD/Tool

#xrdcp root://cmsxrootd-site.fnal.gov//store/user/lpcsusyhad/PHYS14_720_Mar14_2014_v2/rootlist_$1.txt .
./QCD $1 $2 $3

