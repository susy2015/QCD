import glob, os, sys

#here we define a function to find the nth occurance of substring, work for ttjets
def find_nth(haystack, needle, n):
  start = haystack.find(needle)
  while start >= 0 and n > 1:
    start = haystack.find(needle, start+len(needle))
    n -= 1
  return start

file_name = sys.argv[1]

with open(file_name) as f:
  for line in f:
    cmd = './SignalStudy ' + line
    print(cmd) 
    os.system(cmd)
