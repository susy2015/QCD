# AllHadronicSUSY
# QCD Background study

1.Set CMS Environment:

```
cmsrel CMSSW_8_0_23
cd CMSSW_8_0_23/src
cmsenv
```

2.Download source code from github and compile plugins:

TopTagger:
```
## Checkout and build OpenCV library for Toptagger
cd $CMSSW_BASE/src
git clone git@github.com:susy2015/opencv.git
cd $CMSSW_BASE/src/opencv
git checkout 3.1.0_StopBugFix
cmake .
make -j 8
## Checkout Tagtagger
cd $CMSSW_BASE/src
git clone git@github.com:susy2015/TopTagger.git
cd $CMSSW_BASE/src/TopTagger
git fetch origin
git checkout HadStopAnaDevel_Moriond2017_Nov28_2016
```

SusyAnaTools:
```
git cms-init
git cms-merge-topic -u kpedro88:METfix8022
git cms-merge-topic -u cms-met:CMSSW_8_0_X-METFilterUpdate
git clone -b TestMiniAOD git@github.com:susy2015/recipeAUX.git
git clone git@github.com:cms-jet/JetToolbox.git JMEAnalysis/JetToolbox -b jetToolbox_80X_V2
git clone git@github.com:susy2015/SusyAnaTools.git
cd $CMSSW_BASE/src/SusyAnaTools
git fetch origin
git checkout Ana_BugFix1_Nov30_2016_Moriond_new_code_baseline_and_tagger
```

CMS Build application:
```
cd $CMSSW_BASE/src
scram b -j 10
```

Build SusyAnaTools and TopTagger library:
```
cd $CMSSW_BASE/src/TopTagger/TopTagger/test
make -j 8
cd $CMSSW_BASE/src/SusyAnaTools/Tools
make
```
Please make sure compile the TopTagger first then SusyAnaTools/Tools! Since baselineDef.cc is rely on the toptagger library!

QCD:
```
cd $CMSSW_BASE/src
git clone -b QCDBG2017Moriond git@github.com:susy2015/QCD.git
```
# QCD Tools

1.Basic Skim:
```
cd $CMSSW_BASE/src/QCD/QCDTools
make
source rmsetup.csh
source $CMSSW_BASE/src/SusyAnaTools/Tools/setup.csh
```

# QCD Translation Factor Method

1.QCD Translation Method
```
cd $CMSSW_BASE/src/QCD/TFactorMethod
make
./QCD RunMode runList_QCD_HT_skimmed_MET175_v3.txt runList_QCD_DataMC_skimmed_MET175_v4.txt
./QCD CalOnly ../QCDTools/QCDStopFlattrees/runList_QCD_HT_QCDTFTrimAndSlim_2016ICHEPv7_csv_fix.txt ../QCDTools/QCDStopFlattrees/runList_QCD_DataMC_QCDTFTrimAndSlim_2016ICHEPv7_csv_fix.txt
```
Specification of QCDHardCodedInput:

```
DataDriven.h : Contains all data driven inputs from HadTau and LL (inverted dphi for all search bin, low met sideband, etc), refreshed by hand
TFactorsfromDataHeader.h : Contains low met sideband Translation factors, refreshed after run in mode "CalTFSideBandOnly", source file of run mode "CalOnly"
TFactorsHeader.h : Contains all the Translation factors (prefit, postfit, scaled), refreshed after run in mode "CalOnly", source file of run mode "PredDataOnly" and "PredMCOnly"
SysHeader.h : Contains all information to make final prediction plot, comes from data card, refreshed after run in mode "PredDataOnly"
```
The valid run modes are: CalOnly, ExpMCOnly, PredMCOnly, CalTFSideBandOnly, PredDataOnly, BasicCheckQCD, BasicCheckLL, SBCheck

For closure and MCExp vs DataPred, reading PredQCD.root and ExpQCD.root:
```
./ClosurePlots QCDClosure20151204 or ./ClosurePlots QCDDataMC20151209
```
For Data/MC comparison in CS, reading BasicCheckQCD.root:
```
./BasicCheckPlots BasicCheckQCD20151209
```

# QCD Rebalance and Smear Method

Under construction

1.Jet Response function

2.Event Rebalance

3.Jet Smear

4.Final Prediction
