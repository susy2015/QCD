import sys
import glob, os
# Skimmed QCD samples location
# d = "/store/group/lpcsusyhad/hua/Skimmed_2015Nov15/TTJets_Nominal_MET200HT500_v3"
d = "/uscms_data/d3/hwei/stop/QCD/CMSSW_8_0_12/src/QCD/QCDTools/QCDStopFlattrees/2016ICHEPMCTxt"
# Full QCD samples location
# d = "/eos/uscms/store/group/lpcsusyhad/Spring15_74X_Oct_2015_Ntp_v2X/"
for dirname, dirnames, filenames in os.walk(d):
  # print path to all subdirectories first.
  # for subdirname in dirnames:
  #    print(os.path.join(dirname, subdirname))

  # if "TTJets_DiLept" not in dirname: 
  # if "QCD_Pt" not in dirname:
    #continue
  if 'failed' in dirnames:
    # don't go into any failed root sample directories.
    dirnames.remove('failed')
  
  # if 'QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8' in dirnames:
    #dirnames.remove('QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8')
  # if 'QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8' in dirnames:
    #dirnames.remove('QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8')
  # if 'QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8' in dirnames:
    #dirnames.remove('QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8')

  # print path to all filenames.
  for filename in filenames:
    #if ( ('ST_' in filename) ):
    #if ( ('WJetsToLNu_HT' in filename) ): 
    #if ( ('TTJets_' in filename) ): 
    #if ( ('ZJetsToNuNu_HT-' in filename) ):
    if ( ('HTMHT' in filename) ):
      #sys.stdout.write('$ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/2016ICHEPMCTxt/' + filename + ', ')
      #print ("$ENV(CMSSW_BASE)/src/QCD/QCDTools/QCDStopFlattrees/2016ICHEPMCTxt/" + filename + ", ")
      print ("arguments = $ENV(CMSSW_BASE) Data " + filename)
      print ("Queue")
      print ""
      #print(os.path.join(dirname, filename))
    else:
      continue

#for file in glob.glob("*QCD_HT_*.root"):
#    print( d + file )
