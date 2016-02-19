import glob, os, sys

#here we define a function to find the nth occurance of substring, work for ttjets
def find_nth(haystack, needle, n):
  start = haystack.find(needle)
  while start >= 0 and n > 1:
    start = haystack.find(needle, start+len(needle))
    n -= 1
  return start

#d = "/eos/uscms/store/group/lpcsusyhad/Spring15_74X_Nov_2015_Ntp_v3X/"
#d = "/eos/uscms/store/group/lpcsusyhad/Spring15_74X_Dec_2015_Ntp_v4X/"
d= "root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15"
file_name = sys.argv[1]

with open(file_name) as f:
  for line in f:
  #print path to all filenames
    cmd = './PrivateSkim ' + line
    print(cmd) 
    os.system(cmd)
    cmd = 'xrdcp *.root ' + d
    os.system(cmd)
    cmd = 'rm *.root'
    os.system(cmd)

#for file in glob.glob("*QCD_HT_*.root"):
#    print( d + file )
