import glob, os

#here we define a function to find the nth occurance of substring, work for ttjets
def find_nth(haystack, needle, n):
  start = haystack.find(needle)
  while start >= 0 and n > 1:
    start = haystack.find(needle, start+len(needle))
    n -= 1
  return start

d = "/eos/uscms/store/group/lpcsusyhad/Spring15_74X_Oct_2015_Ntp_v2X/"
#d = "/eos/uscms/store/group/lpcsusyhad/hua/"
#os.chdir(d)

for dirname, dirnames, filenames in os.walk(d):
  # print path to all subdirectories first.
  # for subdirname in dirnames:
  #    print(os.path.join(dirname, subdirname))

  #if "QCD_HT" not in dirname:
  if "TTJets_DiLept" not in dirname: 
    continue
  if 'failed' in dirnames:
    # don't go into any failed root sample directories.
    dirnames.remove('failed')
  
  #begin = dirname.find('QCD')
  #begin = find_nth( dirname, "TTJets", 2)
  #end = dirname.find('Asympt25ns', begin)
  #tag = dirname[begin:end] + 'skimmed_'
  #if 'QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8' in dirnames:
    #dirnames.remove('QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8')
  #if 'QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8' in dirnames:
    #dirnames.remove('QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8')
  #if 'QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8' in dirnames:
    #dirnames.remove('QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8')

  # print path to all filenames.
  for filename in filenames:
    input_tmp = os.path.join(dirname, filename)
    cmd = './PrivateSkim ' + input_tmp
    print(cmd) 
    os.system(cmd)

#for file in glob.glob("*QCD_HT_*.root"):
#    print( d + file )
