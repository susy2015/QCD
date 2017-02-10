import sys
import glob, os

def PrintCondorHeaderLine():
  print("universe = vanilla")
  print("request_disk   = 50 GB")
  print("request_memory = 1.5 GB")
  print("executable = $ENV(CMSSW_BASE)/src/QCD/QCDTools/goQCDTFTrimAndSlim.sh")
  print("should_transfer_files = YES")
  print("#when_to_transfer_output = ON_EXIT")
  print ""

def PrintTransferFileLine(directory, sampletype, isfirst, islast):
  if(isfirst):
    sys.stdout.write('transfer_input_files = $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/CMSSW_8_0_25.tar.gz, $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDTFTrimAndSlim_LLHadTau, $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDTFTrimAndSlim_Zinv, $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDTFTrimAndSlim_QCD, $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDTFTrimAndSlim_TTZ, $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDTFTrimAndSlim_Data, $ENV(CMSSW_BASE)/src/QCD/QCDTools/NTuple_QCDTFTrimAndSlim.py, $ENV(CMSSW_BASE)/src/QCD/QCDTools/goQCDTFTrimAndSlim.sh, $ENV(CMSSW_BASE)/src/QCD/QCDTools/CSVv2_Moriond17_B_H.csv, $ENV(CMSSW_BASE)/src/QCD/QCDTools/TTbarNoHad_bTagEff.root, $ENV(CMSSW_BASE)/src/QCD/QCDTools/PileupHistograms_Nov17.root, $ENV(CMSSW_BASE)/src/QCD/QCDTools/puppiSoftdropResol.root, $ENV(CMSSW_BASE)/src/QCD/QCDTools/Legacy_TopTagger.cfg, $ENV(CMSSW_BASE)/src/QCD/QCDTools/TopTagger.cfg, $ENV(CMSSW_BASE)/src/QCD/QCDTools/TrainingOutput_dR20_pt30_depth14_2016_Dec2.model, ')
  for dirname, dirnames, filenames in os.walk(directory):
    for filename in filenames:
      if ( sampletype in filename ):
        sys.stdout.write('$ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/2017MoriondTxt/' + filename + ', ')
      else:
        continue
  if(islast):
    print ""
    print ""

def PrintCondorLogLine(runtype):
  print ("Output = $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/res/QCDTFTrimAndSlim_" + runtype + "_$(Process).stdout")
  print ("Error = $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/res/QCDTFTrimAndSlim_" + runtype + "_$(Process).stderr")
  print ("Log = $ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/res/QCDTFTrimAndSlim_" + runtype + "_$(Process).log")
  print ("notify_user = hua.wei@cern.ch")
  print ""

def PrintCondorSubmitLine(directory, sampletype, command):
  print("#### "+ sampletype +" ####")
  print ""
  for dirname, dirnames, filenames in os.walk(directory):
    for filename in filenames:
      if ( sampletype in filename ):
        print ("arguments = $ENV(CMSSW_VERSION) $ENV(SCRAM_ARCH) " + command + " " + filename)
        print ("Queue")
        print ""
      else:
        continue

d = "/uscms_data/d3/hwei/stop/QCD/CMSSW_8_0_25/src/QCD/QCDTools/QCDStopFlattrees/2017MoriondTxt"
runtype = sys.argv[1]
print ("#The valid run types for QCDTFTrimAndSlim are Data, LLHadTau, Zinv, QCD, and TTZ! While the current run type is : " + runtype)

if(runtype == "Data"):
  PrintCondorHeaderLine()
  print("##transfer file list for " + runtype + " samples")
  PrintTransferFileLine(d, "MET", True, True)
  PrintCondorLogLine(runtype)
  PrintCondorSubmitLine(d, "MET", runtype)
elif(runtype == "LLHadTau"):
  PrintCondorHeaderLine()
  print("##transfer file list for " + runtype + " samples")
  PrintTransferFileLine(d, "TTJets_", True, False)
  PrintTransferFileLine(d, "WJetsToLNu_HT-", False, False)
  PrintTransferFileLine(d, "ST_tW_", False, True)
  PrintCondorLogLine(runtype)
  PrintCondorSubmitLine(d, "TTJets_", runtype)
  PrintCondorSubmitLine(d, "WJetsToLNu_HT-", runtype)
  PrintCondorSubmitLine(d, "ST_tW_", runtype)
elif(runtype == "Zinv"):
  PrintCondorHeaderLine()
  print("##transfer file list for " + runtype + " samples")
  PrintTransferFileLine(d, "ZJetsToNuNu_HT-", True, True)
  PrintCondorLogLine(runtype)
  PrintCondorSubmitLine(d, "ZJetsToNuNu_HT-", runtype)
elif(runtype == "QCD"):
  PrintCondorHeaderLine()
  print("##transfer file list for " + runtype + " samples")
  PrintTransferFileLine(d, "QCD_HT", True, True)
  PrintCondorLogLine(runtype)
  PrintCondorSubmitLine(d, "QCD_HT", runtype)
elif(runtype == "TTZ"):
  PrintCondorHeaderLine()
  print("##transfer file list for " + runtype + " samples")
  PrintTransferFileLine(d, "TTZTo", True, False)
  PrintTransferFileLine(d, "TTWJetsTo", False, False)
  PrintTransferFileLine(d, "WW", False, False)
  PrintTransferFileLine(d, "WZ", False, False)
  PrintTransferFileLine(d, "ZZ", False, True)
  PrintCondorLogLine(runtype)
  PrintCondorSubmitLine(d, "TTZTo", runtype)
  PrintCondorSubmitLine(d, "TTWJetsTo", runtype)
  PrintCondorSubmitLine(d, "WW", runtype)
  PrintCondorSubmitLine(d, "WZ", runtype)
  PrintCondorSubmitLine(d, "ZZ", runtype)
else:
  print ("#Invalid run type for QCDTFTrimAndSlim! What the fuck is going on ??!!")
