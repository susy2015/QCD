import glob, os, sys

#here we define a function to find the nth occurance of substring, work for ttjets
def find_nth(haystack, needle, n):
  start = haystack.find(needle)
  while start >= 0 and n > 1:
    start = haystack.find(needle, start+len(needle))
    n -= 1
  return start

d = "/eos/uscms/store/group/lpcsusyhad/Spring15_74X_Nov_2015_Ntp_v3X/"
#d = "/eos/uscms/store/group/lpcsusyhad/hua/"
#os.chdir(d)
sample_tag = sys.argv[1]

for dirname, dirnames, filenames in os.walk(d):
  # print path to all subdirectories first.
  # for subdirname in dirnames:
  #    print(os.path.join(dirname, subdirname))

  #if "QCD_HT" not in dirname:
  #if "ZJetsToNuNu_" not in dirname: 
  if sample_tag not in dirname:
    continue

  if 'failed' in dirnames:
    # don't go into any failed root sample directories.
    dirnames.remove('failed')
  if 'addJetsForZinv' in dirnames:
    # don't go into any special Zinv root sample directories.
    dirnames.remove('addJetsForZinv')

  # print path to all filenames.
  for filename in filenames:
    input_tmp = os.path.join(dirname, filename)
    cmd = './PrivateSkim ' + input_tmp
    print(cmd) 
    os.system(cmd)

#for file in glob.glob("*QCD_HT_*.root"):
#    print( d + file )
