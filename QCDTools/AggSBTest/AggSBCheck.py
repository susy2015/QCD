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
      subsum = sum(norSB[pair[0]:(pair[1]+1)])
      thisnum=thisnum+subsum
      #print subsum
    num.append(thisnum)
    #print thisnum
  return num

def CompareDraw(title,jmap_bin,aggSBsplTG,aggSBnorTG,norSBsplTG,norSBnorTG):
  c = TCanvas("c","",50,50,800,600)
  c.SetLogy()
  ROOT.gStyle.SetOptStat(0);
  
  h_aggSBsplTG = TH1D("h_aggSBsplTG","",30,0,30)
  h_aggSBnorTG = TH1D("h_aggSBnorTG","",30,0,30)
  h_norSBsplTG = TH1D("h_norSBsplTG","",30,0,30)
  h_norSBnorTG = TH1D("h_norSBnorTG","",30,0,30)

  h_aggSBsplTG.SetMarkerStyle(21)
  h_aggSBsplTG.SetMarkerSize(1.5)
  h_aggSBsplTG.SetMarkerColor(5)
  h_aggSBsplTG.SetLineColor(5)
  h_aggSBsplTG.SetLineWidth(3)
  h_aggSBsplTG.GetXaxis().SetTitle("Search Bins")
  h_aggSBsplTG.GetYaxis().SetTitle("Events")

  h_aggSBnorTG.SetMarkerStyle(21)
  h_aggSBnorTG.SetMarkerSize(1.5)
  h_aggSBnorTG.SetMarkerColor(4)
  h_aggSBnorTG.SetLineColor(4)
  h_aggSBnorTG.SetLineWidth(3)
  h_aggSBnorTG.GetXaxis().SetTitle("Search Bins")
  h_aggSBnorTG.GetYaxis().SetTitle("Events")

  h_norSBsplTG.SetMarkerStyle(20)
  h_norSBsplTG.SetMarkerColor(3)
  h_norSBsplTG.SetLineColor(3)
  h_norSBsplTG.SetLineWidth(3)
  h_norSBsplTG.GetXaxis().SetTitle("Search Bins")
  h_norSBsplTG.GetYaxis().SetTitle("Events")

  h_norSBnorTG.SetMarkerStyle(20)
  h_norSBnorTG.SetMarkerColor(2)
  h_norSBnorTG.SetLineColor(2)
  h_norSBnorTG.SetLineWidth(3)
  h_norSBnorTG.GetXaxis().SetTitle("Search Bins")
  h_norSBnorTG.GetYaxis().SetTitle("Events")

  for i in range(len(jmap_bin)):
    h_aggSBsplTG.SetBinContent(jmap_bin[i]+1,aggSBsplTG[i])
    h_aggSBnorTG.SetBinContent(jmap_bin[i]+1,aggSBnorTG[i])
    h_norSBsplTG.SetBinContent(jmap_bin[i]+1,norSBsplTG[i])
    h_norSBnorTG.SetBinContent(jmap_bin[i]+1,norSBnorTG[i])

  h_aggSBsplTG.Draw("P")
  h_aggSBnorTG.Draw("same P")
  h_norSBsplTG.Draw("same")
  h_norSBnorTG.Draw("same")

  leg = TLegend(0.15,0.70,0.70,0.90)
  leg.SetBorderSize(1)
  leg.SetLineColor(1)
  leg.SetLineWidth(2)
  leg.SetFillColor(0)
  leg.SetTextFont(42)
  leg.SetTextSize(0.03)
  leg.SetHeader("QCD background "+title)
  leg.AddEntry(h_aggSBsplTG,"Direct from Agg SB, Simple Tagger")
  leg.AddEntry(h_aggSBnorTG,"Direct from Agg SB, Normal Tagger")
  leg.AddEntry(h_norSBsplTG,"Sum Nor SB to fake Agg SB, Simple Tagger")
  leg.AddEntry(h_norSBnorTG,"Sum Nor SB to fake Agg SB, Normal Tagger")
  leg.Draw("same")
  c.SaveAs(title+"_AggSBCheck.png")
  return

qcd_cs_aggSBsplTG = GetNum("qcd_v13_aggsb_spltg.txt","QCD_Data_CS = ")
qcd_cs_aggSBnorTG = GetNum("qcd_v13_aggsb_nortg.txt","QCD_Data_CS = ")
qcd_cs_norSBsplTG = GetNum("qcd_v13_norsb_spltg.txt","QCD_Data_CS = ")
qcd_cs_norSBnorTG = GetNum("qcd_v13_norsb_nortg.txt","QCD_Data_CS = ")

qcd_jmap_bin = GetIDSBJSON()
qcd_cs_aggSBsplTG_jmap = GetAggSBJSON(qcd_cs_aggSBsplTG)
qcd_cs_aggSBnorTG_jmap = GetAggSBJSON(qcd_cs_aggSBnorTG)
qcd_cs_norSBsplTG_jmap = SumNorSBJSON(qcd_cs_norSBsplTG)
qcd_cs_norSBnorTG_jmap = SumNorSBJSON(qcd_cs_norSBnorTG)

CompareDraw("QCD_ControlRegion_Data",qcd_jmap_bin,qcd_cs_aggSBsplTG_jmap,qcd_cs_aggSBnorTG_jmap,qcd_cs_norSBsplTG_jmap,qcd_cs_norSBnorTG_jmap)
print qcd_jmap_bin
print qcd_cs_aggSBsplTG_jmap
print qcd_cs_aggSBnorTG_jmap
print qcd_cs_norSBsplTG_jmap
print qcd_cs_norSBnorTG_jmap

qcd_otherBG_aggSBsplTG = GetNum("qcd_v13_aggsb_spltg.txt","QCD_otherBG_eff_CS = ")
qcd_otherBG_aggSBnorTG = GetNum("qcd_v13_aggsb_nortg.txt","QCD_otherBG_eff_CS = ")
qcd_otherBG_norSBsplTG = GetNum("qcd_v13_norsb_spltg.txt","QCD_otherBG_CS = ")
qcd_otherBG_norSBnorTG = GetNum("qcd_v13_norsb_nortg.txt","QCD_otherBG_CS = ")

qcd_otherBG_aggSBsplTG_jmap = GetAggSBJSON(qcd_otherBG_aggSBsplTG)
qcd_otherBG_aggSBnorTG_jmap = GetAggSBJSON(qcd_otherBG_aggSBnorTG)
qcd_otherBG_norSBsplTG_jmap = SumNorSBJSON(qcd_otherBG_norSBsplTG)
qcd_otherBG_norSBnorTG_jmap = SumNorSBJSON(qcd_otherBG_norSBnorTG)

CompareDraw("QCD_ControlRegion_otherBG",qcd_jmap_bin,qcd_otherBG_aggSBsplTG_jmap,qcd_otherBG_aggSBnorTG_jmap,qcd_otherBG_norSBsplTG_jmap,qcd_otherBG_norSBnorTG_jmap)
print qcd_jmap_bin
print qcd_otherBG_aggSBsplTG_jmap
print qcd_otherBG_aggSBnorTG_jmap
print qcd_otherBG_norSBsplTG_jmap
print qcd_otherBG_norSBnorTG_jmap
