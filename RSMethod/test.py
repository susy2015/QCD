#import os,sys
#from ROOT import *
#from utils import *
#from array import array
#from glob import glob

def test(u):
  u=u+2
  return u

a=1
b=2

for i in range(3):
  a = test(i)
  print a,b


