import json
import ROOT
from ROOT import TCanvas
from ROOT import TH1D
from ROOT import TLegend
from ROOT import TStyle
from pprint import pprint

def GetNum(fname,tag):
  with open(fname) as f:
    for line in f:
      if(tag in line):
        num_str = (line.split(tag,1)[1]).split()
  num = []
  for i in num_str:
    num.append(float(i))
  #print num
  return num

def GetIDSBJSON():
  binid = []
  with open('201730AggSB201784SBMap.json') as map_file:
    thismap = json.load(map_file)
  for i in thismap:
    binid.append(int(i))
  return binid

def GetAggSBJSON(aggSB):
  num = []
  with open('201730AggSB201784SBMap.json') as map_file:
    thismap = json.load(map_file)
  #pprint(thismap)
  for i in thismap:
    num.append(aggSB[int(i)])
    #print thismap[i]
  return num

def SumNorSBJSON(norSB):
  num = []
  with open('201730AggSB201784SBMap.json') as map_file:
    thismap = json.load(map_file)
  for i in thismap:
    thisnum=0
    edges = thismap[i]
    for pair in edges:
      subsum = sum(norSB[pair[0]:pair[1]])
      thisnum=thisnum+subsum
      #print subsum
    num.append(thisnum)
    #print thisnum
  return num

def CompareDraw(title,jmap_bin,aggSB,norSB):
  c = TCanvas("c","",50,50,800,600)
  c.SetLogy()
  ROOT.gStyle.SetOptStat(0);
  
  h_agg = TH1D("h_agg","",30,0,30)
  h_nor = TH1D("h_nor","",30,0,30)
  h_agg.SetMarkerStyle(20)
  h_agg.SetMarkerColor(4)
  h_agg.SetMarkerSize(0)
  h_agg.SetLineColor(4)
  h_agg.SetLineWidth(3)
  h_agg.GetXaxis().SetTitle("Search Bins")
  h_agg.GetYaxis().SetTitle("Events")

  h_nor.SetMarkerStyle(20)
  h_nor.SetMarkerColor(2)
  h_nor.SetMarkerSize(0.9)
  h_nor.SetLineColor(2)
  h_nor.SetLineWidth(3)
  h_nor.GetXaxis().SetTitle("Search Bins")
  h_nor.GetYaxis().SetTitle("Events")

  for i in range(len(jmap_bin)):
    h_agg.SetBinContent(jmap_bin[i],aggSB[i])
    h_nor.SetBinContent(jmap_bin[i],norSB[i])
  h_agg.Draw()
  h_nor.Draw("same")

  leg = TLegend(0.15,0.70,0.70,0.90)
  leg.SetBorderSize(1)
  leg.SetLineColor(1)
  leg.SetLineWidth(2)
  leg.SetFillColor(0)
  leg.SetTextFont(42)
  leg.SetTextSize(0.03)
  leg.SetHeader("QCD background "+title)
  leg.AddEntry(h_agg,"Direct from Aggregate SB")
  leg.AddEntry(h_nor,"Sum Normal SB to fake Aggregate SB")
  leg.Draw("same")
  c.SaveAs(title+"_AggSBCheck.png")
  return

qcd_cs_aggSB = GetNum("qcd_v13_aggSB_0.0.txt","QCD_Data_CS = ")
qcd_cs_norSB = GetNum("qcd_v13.2.1.txt","QCD_Data_CS = ")

qcd_jmap_bin = GetIDSBJSON()
qcd_cs_aggjmap = GetAggSBJSON(qcd_cs_aggSB)
qcd_cs_norjmap = SumNorSBJSON(qcd_cs_norSB)

CompareDraw("QCD_ControlRegion_Data",qcd_jmap_bin,qcd_cs_aggjmap,qcd_cs_norjmap)
print qcd_jmap_bin
print qcd_cs_aggjmap
print qcd_cs_norjmap

qcd_otherBG_aggSB = GetNum("qcd_v13_aggSB_0.0.txt","QCD_otherBG_eff_CS = ")
qcd_otherBG_norSB = GetNum("qcd_v13.2.1.txt","QCD_otherBG_CS = ")

qcd_otherBG_aggjmap = GetAggSBJSON(qcd_otherBG_aggSB)
qcd_otherBG_norjmap = SumNorSBJSON(qcd_otherBG_norSB)

CompareDraw("QCD_ControlRegion_otherBG",qcd_jmap_bin,qcd_otherBG_aggjmap,qcd_otherBG_norjmap)
print qcd_jmap_bin
print qcd_otherBG_aggjmap
print qcd_otherBG_norjmap

