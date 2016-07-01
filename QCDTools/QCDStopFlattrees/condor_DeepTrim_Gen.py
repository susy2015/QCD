import sys
import glob, os
# Skimmed QCD samples location
# d = "/store/group/lpcsusyhad/hua/Skimmed_2015Nov15/TTJets_Nominal_MET200HT500_v3"

def PrintTransferFileLine(directory, sampletype):
  for dirname, dirnames, filenames in os.walk(directory):
    #if 'failed' in dirnames:
      # don't go into any failed root sample directories.
      #dirnames.remove('failed')
    # print path to all filenames.
    for filename in filenames:
      #if ( ('ST_' in filename) ):
      #if ( ('WJetsToLNu_HT' in filename) ): 
      #if ( ('TTJets_' in filename) ): 
      #if ( ('ZJetsToNuNu_HT-' in filename) ):
      if ( sampletype in filename ):
        sys.stdout.write('$ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/2016ICHEPMCTxt/' + filename + ', ')
      else:
        continue
  print ""
  print ""


def PrintCondorSubmitLine(directory, sampletype):
  for dirname, dirnames, filenames in os.walk(directory):
    for filename in filenames:
      #if ( ('ST_' in filename) ):
      #if ( ('WJetsToLNu_HT' in filename) ): 
      #if ( ('TTJets_' in filename) ): 
      #if ( ('ZJetsToNuNu_HT-' in filename) ):
      if ( sampletype in filename ):
        print ("arguments = $ENV(CMSSW_BASE) " + filename)
        print ("Queue")
        print ""
      else:
        continue


d = "/uscms_data/d3/hwei/stop/QCD/CMSSW_8_0_12/src/QCD/QCDTools/QCDStopFlattrees/2016ICHEPMCTxt"

#PrintTransferFileLine(d, "HTMHT")
#PrintCondorSubmitLine(d, "HTMHT")

#PrintTransferFileLine(d, "TTJets_")
#PrintCondorSubmitLine(d, "TTJets_")

#PrintTransferFileLine(d, "WJetsToLNu_HT-")
#PrintCondorSubmitLine(d, "WJetsToLNu_HT-")

PrintTransferFileLine(d, "ST_tW_")
PrintCondorSubmitLine(d, "ST_tW_")
