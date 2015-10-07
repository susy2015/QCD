#!/bin/bash

export PATH=${PATH}:/cvmfs/cms.cern.ch/common
export CMS_PATH=/cvmfs/cms.cern.ch

cd $1/src
eval `scramv1 runtime -sh`

cd $1/src/QCD/Tool

#xrdcp root://cmsxrootd-site.fnal.gov//store/user/lpcsusyhad/PHYS14_720_Mar14_2014_v2/rootlist_$1.txt .

./QCD $2 $3

#rm rootlist_$1.txt
