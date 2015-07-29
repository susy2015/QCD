import glob, os
d = "/uscms/home/hwei/work/stop/CMSSW_7_4_5/src/flattrees/"
os.chdir(d)
for file in glob.glob("*QCD_HT_*.root"):
    print( d + file )
