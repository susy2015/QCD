# AllHadronicSUSY
# QCD Background study

1.Set CMS Environment:

setenv SCRAM_ARCH slc6_amd64_gcc491(export SCRAM_ARCH = slc6_amd64_gcc491)

cmsrel CMSSW_7_4_6_patch6

cd CMSSW_7_4_6_patch6/src

cmsenv

2.Download source code from github and compile plugins:

git cms-merge-topic -u cms-met:METCorUnc74X

git clone -b TestMiniAOD git@github.com:susy2015/recipeAUX.git

git clone git@github.com:susy2015/SusyAnaTools.git

git clone https://github.com/susy2015/QCD.git

scram b -j9

3.Go to QCD directory and then compile the code

cd QCD/Tool

mkdir obj

make

PS: We have Error like "cannot find libtbb.so.2", to solve this problem, we want to build a soft link to this lib for temporary solution. To do this:

Go to QCD/Tool

and then do:

ln -s /cvmfs/cms.cern.ch/slc6_amd64_gcc481/external/tbb/42_20131118oss/lib/libtbb.so.2

This will generate a soft link : libtbb.so.2

And it will be involved into make command automatically and we do not have error report anymore

4.Run the QCD code:

./QCD runList_inputfile.txt outputfile.root

5.Some useful tools:

cd QCD/Tool/QCDStopFlattrees

g++ stopNTuple_skim.cc `root-config --libs --cflags` -o PrivateSkim

PS: For QCD, MET > 175 while for all ttbar samples, MET > 200

python NTuple_Skim.py

