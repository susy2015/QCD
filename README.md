# AllHadronicSUSY
# QCD Background study

1.Set CMS Environment:

```
cmsrel CMSSW_8_0_25
cd CMSSW_8_0_25/src
cmsenv
```
2.Download source code from github and compile plugins:

SusyAnaTools:
```
git cms-init
git cms-merge-topic -u kpedro88:METfix8022
git cms-merge-topic -u cms-met:fromCMSSW_8_0_20_postICHEPfilter
git clone -b TestMiniAOD git@github.com:susy2015/recipeAUX.git
git clone git@github.com:susy2015/JetToolbox.git JMEAnalysis/JetToolbox -b fix_NoLep_jetToolbox_80X_V3
git cms-merge-topic gpetruc:badMuonFilters_80X_v2
git clone -b ana_v3_Summer16_MC_23Sep2016_Data_Feb21_2017 git@github.com:susy2015/SusyAnaTools.git
```

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
git clone -b HadStopAnaDevel_v7_Moriond2017_Feb20_2017 git@github.com:susy2015/TopTagger.git
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

```
cd $CMSSW_BASE/src/QCD/QCDTools
make
source reset.csh
source $CMSSW_BASE/src/SusyAnaTools/Tools/setup.csh
```
OR customized TaggerCfg setting : 
```
$CMSSW_BASE/src/TopTagger/Tools/getTaggerCfg.sh -t MVAAK8_Tight_v1.1.1 -d /uscms_data/d3/hwei/stop
$CMSSW_BASE/src/TopTagger/Tools/getTaggerCfg.sh -t Legacy_AK4Only_v0.1.0 -f Legacy_TopTagger.cfg -d /uscms_data/d3/hwei/stop
```

Tarball CMSSW release and Txt file : 
```
cd $CMSSW_BASE/src/QCD/QCDTools/QCDStopFlattrees
sh cache_all.sh
tar --exclude-caches-all -zcf ${CMSSW_VERSION}.tar.gz -C ${CMSSW_BASE}/.. ${CMSSW_VERSION}
tar -zcf 2017MoriondTxt.tar.gz 2017MoriondTxt
```

1.Deep skim for lost lepton background estimation:

2.QCD skim and slim for QCD background estimation:

# QCD Translation Factor Method

1.QCD Translation Method
```
cd $CMSSW_BASE/src/QCD/TFactorMethod
make
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
