import glob, os, sys

#here we define a function to find the nth occurance of substring, work for ttjets
def find_nth(haystack, needle, n):
  start = haystack.find(needle)
  while start >= 0 and n > 1:
    start = haystack.find(needle, start+len(needle))
    n -= 1
  return start

def find_between( s, first, last ):
  try:
    start = s.index( first ) + len( first )
    end = s.index( last, start )
    return s[start:end]
  except ValueError:
    return ""
#d = "/eos/uscms/store/group/lpcsusyhad/Spring15_74X_Nov_2015_Ntp_v3X/"
#d = "/eos/uscms/store/group/lpcsusyhad/Spring15_74X_Dec_2015_Ntp_v4X/"
#d= "root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15"

file_name = sys.argv[1]
#rootfile_tag = file_name[:-4]
#print(rootfile_tag) 
sampletag_list = []
missing_list = []

with open(file_name) as f:
  for line in f:
    if "0 hwei     us_cms" in line:
      #print(line) 
      sampletag_str = find_between(line,"_data_topoff_","root")
      sampletag_list.append(sampletag_str)
      missing_str = find_between(line,"QCDTFTrimAndSlim_","root")
      missing_str = "QCDTFTrimAndSlim_"+missing_str+"root"
      print missing_str
      missing_list.append(missing_str)
      #cmd = "eos root://cmseos.fnal.gov/ ls /store/group/lpcsusyhad/hua/Skimmed_2015Nov15/"+missing_str
      cmd = "eos root://cmseos.fnal.gov/ rm /store/group/lpcsusyhad/hua/Skimmed_2015Nov15/"+missing_str
      os.system(cmd)

      #print(sampletag_str)
    #cmd = 'xrdcp *'+ rootfile_tag +'*.root ' + d
    #cmd = 'xrdcp *.root ' + d
    #os.system(cmd)
    #cmd = 'rm *'+ rootfile_tag +'*.root'
    #cmd = 'rm *.root'
    #os.system(cmd)

#for p in sampletag_list : print p

file_list = [
              "QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt",
              "QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt",
              "QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt",
              "QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt",
              "QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt"
            ]

source_list = []

for p in sampletag_list:
  #QCD_HT700to1000stopFlatNtuples_99.
  isext = False
  taga_=""
  tagb_=""
  if( "ext" not in p):
    isext = False
    taga_ = find_between(p,"QCD_","stopFlatNtuples")
    tagb_ = find_between(p,"stopFlatNtuples_",".")
  else:
    isext = True
    taga_ = find_between(p,"QCD_","_ext")
    tagb_ = find_between(p,"stopFlatNtuples_",".")

  #print filetag
  for onef_str in file_list : 
    if taga_ in onef_str : 
      onef = open(onef_str)
      for onefline in onef:
        #root://cmseos.fnal.gov//store/user/lpcsusyhad/Spring16_80X_Jun_2016_Ntp_v6X/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Spring16_80X_Jun_2016_Ntp_v6p0_fix_topProj_wt_data_topoff_QCD_HT500to700/160617_093756/0000/stopFlatNtuples_1.root
        taga = find_between(onefline,"/QCD_","_TuneCUETP8M1")
        tagb = find_between(onefline,"stopFlatNtuples_",".root")
        if(isext):
          if ((taga == taga_) and (tagb == tagb_) and ("ext" in onefline)) :
            source_list.append(onefline)
            #print onefline
            break
          else : 
            continue
        else:
          if ((taga == taga_) and (tagb == tagb_) and ("ext" not in onefline)) :
            source_list.append(onefline)
            #print onefline
            break
          else :
            continue

    else:
      continue

if len(missing_list) == len(source_list):
  print "Good! fail file equal to source file!!"
else:
  print "what the fuck! source and bug file not equal!!!"

f_source = open('FailQCDList.txt','w')
for ll in source_list:
  f_source.write(ll) # python will convert \n to os.linesep

f_source.close() # you can omit in most cases as the destructor will call it
