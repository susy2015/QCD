import glob, os
# Skimmed QCD samples location
d = "/eos/uscms/store/group/lpcsusyhad/hua/"
# Full QCD samples location
# d = "/eos/uscms/store/group/lpcsusyhad/Spring15_74X_Oct_2015_Ntp_v2X/"
for dirname, dirnames, filenames in os.walk(d):
  # print path to all subdirectories first.
  # for subdirname in dirnames:
  #    print(os.path.join(dirname, subdirname))

  if "QCD_HT" not in dirname: 
  # if "QCD_Pt" not in dirname:
    continue
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
    print(os.path.join(dirname, filename))

#for file in glob.glob("*QCD_HT_*.root"):
#    print( d + file )
