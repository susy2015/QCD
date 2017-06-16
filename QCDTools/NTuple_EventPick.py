import glob, os, sys

def find_nth(haystack, needle, n):
  start = haystack.find(needle)
  while start >= 0 and n > 1:
    start = haystack.find(needle, start+len(needle))
    n -= 1
  return start

file_name = sys.argv[1]

with open(file_name) as f:
  for line in f:
    cmd = './EventPick ' + line
    print(cmd) 
    os.system(cmd)
