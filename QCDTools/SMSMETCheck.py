import json
import ROOT
from ROOT import TCanvas
from ROOT import TH1D
from ROOT import TLegend
from ROOT import TStyle
from pprint import pprint
import numpy as np

def CompareDraw(islogy,title,mSUSYMother,mLSP):
  c = TCanvas("c","",50,50,800,600)
  if islogy:
    c.SetLogy()
  ROOT.gStyle.SetOptStat(0);
  
  h_met1 = TH1D("h_met1","",100,0,2000)
  h_met2 = TH1D("h_met2","",100,0,2000)
  h_met3 = TH1D("h_met3","",100,0,2000)
  h_met4 = TH1D("h_met4","",100,0,2000)
  h_met5 = TH1D("h_met5","",100,0,2000)

  h_met1.SetMarkerStyle(21)
  h_met1.SetMarkerSize(1.5)
  h_met1.SetMarkerColor(5)
  h_met1.SetLineColor(5)
  h_met1.SetLineWidth(3)
  h_met1.GetXaxis().SetTitle("MET")
  h_met1.GetYaxis().SetTitle("Events")

  h_met2.SetMarkerStyle(21)
  h_met2.SetMarkerSize(1.5)
  h_met2.SetMarkerColor(4)
  h_met2.SetLineColor(4)
  h_met2.SetLineWidth(3)
  h_met2.GetXaxis().SetTitle("MET")
  h_met2.GetYaxis().SetTitle("Events")

  h_met3.SetMarkerStyle(20)
  h_met3.SetMarkerColor(3)
  h_met3.SetLineColor(3)
  h_met3.SetLineWidth(3)
  h_met3.GetXaxis().SetTitle("MET")
  h_met3.GetYaxis().SetTitle("Events")

  h_met4.SetMarkerStyle(20)
  h_met4.SetMarkerColor(2)
  h_met4.SetLineColor(2)
  h_met4.SetLineWidth(3)
  h_met4.GetXaxis().SetTitle("MET")
  h_met4.GetYaxis().SetTitle("Events")

  h_met5.SetMarkerStyle(20)
  h_met5.SetMarkerColor(1)
  h_met5.SetLineColor(1)
  h_met5.SetLineWidth(3)
  h_met5.GetXaxis().SetTitle("MET")
  h_met5.GetYaxis().SetTitle("Events")

  f = ROOT.TFile.Open("SignalStudy_Test.root", "read")
  t = f.Get("stopTreeMaker/QCDTFTree")
  i = 0  
  for event in t:
    #if(mLSP>event.SusyLSPMass-0.5 and mLSP<event.SusyLSPMass+0.5 and mSUSYMother>event.SusyMotherMass-0.5 and mSUSYMother<event.SusyMotherMass+0.5):
    if(True):
      h_met1.Fill(event.met)
      h_met2.Fill(event.genmet)
      h_met3.Fill(event.allgenmet)
      h_met4.Fill(event.sNugenmet)
      h_met5.Fill(event.sNuNufromTopWgenmet)
    i = i+1
    if((i%10000) == 0):
      print("%i Events Filled!" % (i))
  
  h_met1.Draw()
  h_met2.Draw("same")
  h_met3.Draw("same")
  h_met4.Draw("same")
  h_met5.Draw("same")

  leg = TLegend(0.35,0.70,0.90,0.90)
  leg.SetBorderSize(1)
  leg.SetLineColor(1)
  leg.SetLineWidth(2)
  leg.SetFillColor(0)
  leg.SetTextFont(42)
  leg.SetTextSize(0.03)
  leg.SetHeader(title)
  leg.AddEntry(h_met1,"Reco MET")
  leg.AddEntry(h_met2,"Gen MET")
  leg.AddEntry(h_met3,"MET from Gen Neutrino and LSP")
  leg.AddEntry(h_met4,"MET from Gen LSP Only")
  leg.AddEntry(h_met5,"MET from Gen LSP and Gen TopW Neutrino")
  leg.Draw("same")
  c.SaveAs(title+"_met.png")
  return

CompareDraw(True,"T5tttt_dM175_2000_1",2000,1)
