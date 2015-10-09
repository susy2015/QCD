import glob, os
#d = "/uscms/home/hwei/work/stop/CMSSW_7_4_5/src/flattrees/"
d = "/eos/uscms/store/group/lpcsusyhad/Spring15_74X_Oct_2015_Ntp_v2X/"
#os.chdir(d)

for dirname, dirnames, filenames in os.walk(d):
  # print path to all subdirectories first.
  # for subdirname in dirnames:
  #    print(os.path.join(dirname, subdirname))

  if "QCD_HT" not in dirname: 
    continue
  if 'failed' in dirnames:
    # don't go into any failed root sample directories.
    dirnames.remove('failed')
  
  begin = dirname.find('QCD')
  end = dirname.find('TuneCUETP8M1', begin)
  tag = dirname[begin:end] + 'skimmed_'
  #if 'QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8' in dirnames:
    #dirnames.remove('QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8')
  #if 'QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8' in dirnames:
    #dirnames.remove('QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8')
  #if 'QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8' in dirnames:
    #dirnames.remove('QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8')

  # print path to all filenames.
  for filename in filenames:
    input_tmp = os.path.join(dirname, filename)
    output_tmp = tag + filename
    cmd = './NTupleSkim ' + input_tmp + ' ' + output_tmp
    print(cmd) 
    os.system(cmd)

#for file in glob.glob("*QCD_HT_*.root"):
#    print( d + file )
