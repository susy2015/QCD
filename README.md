# AllHadronicSUSY
# QCD Background study

1.Set CMS Environment:

setenv SCRAM_ARCH slc6_amd64_gcc491(export SCRAM_ARCH = slc6_amd64_gcc491)

cmsrel CMSSW_7_4_15

cd CMSSW_7_4_15/src

cmsenv

2.Download source code from github and compile plugins:

git cms-merge-topic -u kpedro88:METfix7415

git clone -b TestMiniAOD git@github.com:susy2015/recipeAUX.git

git clone git@github.com:susy2015/SusyAnaTools.git

git clone https://github.com/susy2015/QCD.git

scram b -j 9

# QCD Translation Factor Method

1.Go to QCD directory and then compile the code

cd QCD/TFactorMethod

make

PS: We have Error like "cannot find libtbb.so.2", to solve this problem, we want to build a soft link to this lib for temporary solution. To do this:

Go to QCD/TFactorMethod

and then do:

ln -s /cvmfs/cms.cern.ch/slc6_amd64_gcc481/external/tbb/42_20131118oss/lib/libtbb.so.2

This will generate a soft link : libtbb.so.2

And it will be involved into make command automatically and we do not have error report anymore

2.Run the QCD code:

./QCD RunMode runList_QCD_HT_skimmed_MET175_v3.txt runList_QCD_DataMC_skimmed_MET175_v4.txt

The valid run modes are: CalOnly, ExpMCOnly, PredMCOnly, PredDataOnly, ExpMCPredMC, ExpMCPredData BasicCheckQCD BasicCheckLL QCDCombine

3.Making plots:

For closure and MCExp vs DataPred, reading PredQCD.root and ExpQCD.root:

./ClosurePlots QCDClosure20151204 or ./ClosurePlots QCDDataMC20151209

For Data/MC comparison in CS, reading BasicCheckQCD.root:

./BasicCheckPlots BasicCheckQCD20151209

# QCD Rebalance and Smear Method

Under construction

1.Jet Response function

2.Event Rebalance

3.Jet Smear

4.Final Prediction

# QCD Tools

1.Basic Skim:

cd QCD/QCDTools/QCDStopFlattrees

g++ stopNTuple_skim.cc \`root-config --libs --cflags\` -o PrivateSkim

PS: For QCD, MET > 175, while for all other samples, MET > 200 && HT > 500

python NTuple_Skim.py QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt

2.Deep Skim

cd QCD/QCDTools

make

python NTuple_DeepTrim.py QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt

3.Basic Slim:

Under construction

# Sensitivity Study
1.To study Signal/MC in designed search bin:

./SS SSAllMC runList_Sensitivity_MC_DeepSkimmed_v4_BG.txt runList_Sensitivity_MC_DeepSkimmed_v4_SG.txt runList_Sensitivity_MC_DeepSkimmed_v6_MuCS.txt

2.To study the CS in designed search bin:

./SS SSCS runList_Sensitivity_MC_DeepSkimmed_v4_BG.txt runList_Sensitivity_MC_DeepSkimmed_v4_SG.txt runList_Sensitivity_MC_DeepSkimmed_v6_MuCS.txt

3.To make 2D plots in designed search bin:

./SSPlots SSPlots20160504

./SSAUX1DPlots SSAUX1DPlots20160517

4.To test the SBGeometry.h

g++ -std=c++11 SSBinIDTest.cc

./a.out
