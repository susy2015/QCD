import sys
import glob, os

def PrintCondorHeaderLine():
  print("universe = vanilla")
  print("request_disk   = 50 GB")
  print("request_memory = 1.5 GB")
  print("executable = $ENV(CMSSW_BASE)/src/QCD/QCDTools/goSignalStudy.sh")
  print("should_transfer_files = YES")
  print("#when_to_transfer_output = ON_EXIT")
  print ""

def PrintTransferFileLine(directory, sampletype, isfirst, islast):
  if(isfirst):
    sys.stdout.write('transfer_input_files = $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/$ENV(CMSSW_VERSION).tar.gz, $ENV(CMSSW_BASE)/src/QCD/QCDTools/SignalStudy, $ENV(CMSSW_BASE)/src/QCD/QCDTools/NTuple_SignalStudy.py, $ENV(CMSSW_BASE)/src/QCD/QCDTools/goSignalStudy.sh, $ENV(CMSSW_BASE)/src/QCD/QCDTools/allINone_ISRJets.root, $ENV(CMSSW_BASE)/src/QCD/QCDTools/ISRWeights.root, $ENV(CMSSW_BASE)/src/QCD/QCDTools/CSVv2_Moriond17_B_H.csv, $ENV(CMSSW_BASE)/src/QCD/QCDTools/allINone_bTagEff.root, $ENV(CMSSW_BASE)/src/QCD/QCDTools/allINone_leptonSF_Moriond17.root, $ENV(CMSSW_BASE)/src/QCD/QCDTools/PileupHistograms_0121_69p2mb_pm4p6.root, $ENV(CMSSW_BASE)/src/QCD/QCDTools/puppiCorr.root, $ENV(CMSSW_BASE)/src/QCD/QCDTools/TopTagger.cfg, $ENV(CMSSW_BASE)/src/QCD/QCDTools/TrainingOutput_dR20_pt30_depth12_500tree_2017_Feb16.model, $ENV(CMSSW_BASE)/src/QCD/QCDTools/Legacy_TopTagger.cfg, $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/2017MoriondTxt.tar.gz')
  #for dirname, dirnames, filenames in os.walk(directory):
  #  for filename in filenames:
  #    if ( sampletype in filename ):
  #      sys.stdout.write('$ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/2017MoriondTxt/' + filename + ', ')
  #    else:
  #      continue
  if(islast):
    print ""
    print ""

def PrintCondorLogLine(runtype):
  print ("Output = $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/res/SignalStudy_" + runtype + "_$(Process).stdout")
  print ("Error = $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/res/SignalStudy_" + runtype + "_$(Process).stderr")
  print ("Log = $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/res/SignalStudy_" + runtype + "_$(Process).log")
  print ("notify_user = hua.wei@cern.ch")
  print ""

def PrintCondorSubmitLine(directory, sampletype):
  print("#### "+ sampletype +" ####")
  print ""
  for dirname, dirnames, filenames in os.walk(directory):
    for filename in filenames:
      if ( sampletype in filename ):
        print ("arguments = $ENV(CMSSW_VERSION) $ENV(SCRAM_ARCH) 2017MoriondTxt/" + filename)
        print ("Queue")
        print ""
      else:
        continue

d = os.environ.get('CMSSW_BASE') + "/src/QCD/QCDTools/QCDStopFlattrees/2017MoriondTxt"
runtype = sys.argv[1]
print ("#The valid run types for SignalStudy are T5tttt, T5ttcc! While the current run type is : " + runtype)

if(runtype == "T5tttt"):
  PrintCondorHeaderLine()
  print("##transfer file list for " + runtype + " samples")
  PrintTransferFileLine(d, "T5tttt", True, True)
  PrintCondorLogLine(runtype)
  PrintCondorSubmitLine(d, "T5tttt")

else:
  print ("#Invalid run type for SignalStudy! What the fuck is going on ??!!")
