import json
import ROOT
from ROOT import TCanvas
from ROOT import TH1D
from ROOT import TLegend
from ROOT import TStyle
from pprint import pprint
import numpy as np

def CompareDraw(islogy,title,mSUSYMother,mLSP):
  h_met1 = TH1D("h_met1","",20,0,1000)
  h_met2 = TH1D("h_met2","",20,0,1000)
  h_met3 = TH1D("h_met3","",20,0,1000)
  h_met4 = TH1D("h_met4","",20,0,1000)
  h_met5 = TH1D("h_met5","",20,0,1000)
  h_met6 = TH1D("h_met6","",20,0,1000)
  h_met7 = TH1D("h_met7","",20,0,1000)

  h_met1.SetMarkerStyle(21)
  h_met1.SetMarkerSize(1.5)
  h_met1.SetMarkerColor(1)
  h_met1.SetLineColor(1)
  h_met1.SetLineWidth(3)
  h_met1.GetXaxis().SetTitle("MET")
  h_met1.GetYaxis().SetTitle("Events")

  h_met2.SetMarkerStyle(21)
  h_met2.SetMarkerSize(1.5)
  h_met2.SetMarkerColor(2)
  h_met2.SetLineColor(2)
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
  h_met4.SetMarkerColor(4)
  h_met4.SetLineColor(4)
  h_met4.SetLineWidth(3)
  h_met4.GetXaxis().SetTitle("MET")
  h_met4.GetYaxis().SetTitle("Events")

  h_met5.SetMarkerStyle(20)
  h_met5.SetMarkerColor(5)
  h_met5.SetLineColor(5)
  h_met5.SetLineWidth(3)
  h_met5.GetXaxis().SetTitle("MET")
  h_met5.GetYaxis().SetTitle("Events")

  h_met6.SetMarkerStyle(20)
  h_met6.SetMarkerColor(6)
  h_met6.SetLineColor(6)
  h_met6.SetLineWidth(3)
  h_met6.GetXaxis().SetTitle("MET")
  h_met6.GetYaxis().SetTitle("Events")

  h_met7.SetMarkerStyle(20)
  h_met7.SetMarkerColor(7)
  h_met7.SetLineColor(7)
  h_met7.SetLineWidth(3)
  h_met7.GetXaxis().SetTitle("MET")
  h_met7.GetYaxis().SetTitle("Events")

  h_metdiff1 = TH1D("h_metdiff1","",20,-500,500)
  h_metdiff2 = TH1D("h_metdiff2","",20,-500,500)
  h_metdiff3 = TH1D("h_metdiff3","",20,-500,500)
  h_metdiff4 = TH1D("h_metdiff4","",20,-500,500)
  h_metdiff5 = TH1D("h_metdiff5","",20,-500,500)

  h_metdiff1.SetMarkerStyle(20)
  h_metdiff1.SetMarkerColor(1)
  h_metdiff1.SetLineColor(1)
  h_metdiff1.SetLineWidth(3)
  h_metdiff1.GetXaxis().SetTitle("Diff MET")
  h_metdiff1.GetYaxis().SetTitle("Events")

  h_metdiff2.SetMarkerStyle(20)
  h_metdiff2.SetMarkerColor(2)
  h_metdiff2.SetLineColor(2)
  h_metdiff2.SetLineWidth(3)  
  h_metdiff2.GetXaxis().SetTitle("Diff MET")
  h_metdiff2.GetYaxis().SetTitle("Events")

  h_metdiff3.SetMarkerStyle(20)
  h_metdiff3.SetMarkerColor(3)
  h_metdiff3.SetLineColor(3)
  h_metdiff3.SetLineWidth(3)
  h_metdiff3.GetXaxis().SetTitle("Diff MET")
  h_metdiff3.GetYaxis().SetTitle("Events")

  h_metdiff4.SetMarkerStyle(20)
  h_metdiff4.SetMarkerColor(4)
  h_metdiff4.SetLineColor(4)
  h_metdiff4.SetLineWidth(3)  
  h_metdiff4.GetXaxis().SetTitle("Diff MET")
  h_metdiff4.GetYaxis().SetTitle("Events")

  h_metdiff5.SetMarkerStyle(20)
  h_metdiff5.SetMarkerColor(5)
  h_metdiff5.SetLineColor(5)
  h_metdiff5.SetLineWidth(3)  
  h_metdiff5.GetXaxis().SetTitle("Diff MET")
  h_metdiff5.GetYaxis().SetTitle("Events")

  #f = ROOT.TFile.Open("FnalEOSTool/SignalStudy_Summer16_80X_Mar_2017_Ntp_v13p0_SMS-T5tttt_dM175_FastSim_scan_stopFlatNtuples.root", "read")
  f = ROOT.TFile.Open("root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15/SMSStudy/SignalStudy_Summer16_80X_Mar_2017_Ntp_v13p0_SMS-T5tttt_dM175_FastSim_scan_stopFlatNtuples.root", "read")
  #f = ROOT.TFile.Open("root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15/SignalStudy_Summer16_80X_Mar_2017_Ntp_v13p0_SMS-T5tttt_dM175_FastSim_scan_stopFlatNtuples_33.root", "read")
  t = f.Get("stopTreeMaker/QCDTFTree")
  i = 0  
  for event in t:
    if(mLSP>event.SusyLSPMass-0.5 and mLSP<event.SusyLSPMass+0.5 and mSUSYMother>event.SusyMotherMass-0.5 and mSUSYMother<event.SusyMotherMass+0.5 and event.ifAllHadTop):
      #if(event.ifAllHadTop):
      #  print 1
      #else:
      #  print 0
      print("mSUSYMother: %d, mLSP: %d" % (event.SusyMotherMass,event.SusyLSPMass))
      h_met1.Fill(event.met)
      h_met2.Fill(event.genmet)
      h_met3.Fill(event.allgenmet)
      h_met4.Fill(event.sNugenmet)
      h_met5.Fill(event.sNuNufromTopWgenmet)
      h_met6.Fill(event.sNuNufromTopBgenmet)
      h_met7.Fill(event.sNuNuOthergenmet)
      h_metdiff1.Fill(event.allgenmet-event.genmet)
      h_metdiff2.Fill(event.sNugenmet-event.genmet)
      h_metdiff3.Fill(event.sNuNufromTopWgenmet-event.genmet)
      h_metdiff4.Fill(event.sNuNufromTopBgenmet-event.genmet)
      h_metdiff5.Fill(event.sNuNuOthergenmet-event.genmet)
    i = i+1
    if((i%10000) == 0):
      print("%i Events Filled!" % (i))

  c1 = TCanvas("c","",50,50,800,600)
  if islogy:
    c1.SetLogy()
  ROOT.gStyle.SetOptStat(0);
  
  #h_met1.Draw()
  h_met2.Draw()
  h_met2.Draw("same")
  #h_met3.Draw("same")
  h_met4.Draw("same")
  #h_met5.Draw("same")
  #h_met6.Draw("same")
  h_met7.Draw("same")

  leg1 = TLegend(0.35,0.70,0.90,0.90)
  leg1.SetBorderSize(1)
  leg1.SetLineColor(1)
  leg1.SetLineWidth(2)
  leg1.SetFillColor(0)
  leg1.SetTextFont(42)
  leg1.SetTextSize(0.03)
  leg1.SetHeader(title)
  leg1.AddEntry(h_met1,"Reco MET")
  leg1.AddEntry(h_met2,"Gen MET")
  leg1.AddEntry(h_met3,"MET from Gen LSP and all Nu")
  leg1.AddEntry(h_met4,"MET from Gen LSP Only")
  leg1.AddEntry(h_met5,"MET from Gen LSP and Gen TopW Nu")
  leg1.AddEntry(h_met6,"MET from Gen LSP and Gen TopB Nu")
  leg1.AddEntry(h_met7,"MET from Gen LSP and Other Nu")
  leg1.Draw("same")
  c1.SaveAs(title+"_3met.png")
  c1.Close()

  c2 = TCanvas("c","",50,50,800,600)
  ROOT.gStyle.SetOptStat(0);

  h_metdiff1.Draw()
  h_metdiff2.Draw("same")
  h_metdiff3.Draw("same")
  h_metdiff4.Draw("same")
  h_metdiff5.Draw("same")

  leg2 = TLegend(0.35,0.70,0.90,0.90)
  leg2.SetBorderSize(1)
  leg2.SetLineColor(1)
  leg2.SetLineWidth(2)
  leg2.SetFillColor(0)
  leg2.SetTextFont(42)
  leg2.SetTextSize(0.03)
  leg2.SetHeader(title)
  leg2.AddEntry(h_metdiff1,"MET_LSP_allNu - GenMET")
  leg2.AddEntry(h_metdiff2,"MET_LSP - GenMET")
  leg2.AddEntry(h_metdiff3,"MET_LSP_TopWNu - GenMET")
  leg2.AddEntry(h_metdiff4,"MET_LSP_TopBNu - GenMET")
  leg2.AddEntry(h_metdiff5,"MET_LSP_OtherNu - GenMET")
  leg2.Draw("same")
  c2.SaveAs(title+"_diffmet.png")
  c2.Close()
  return

CompareDraw(True,"T5tttt_dM175_2000_1",2000,1)
CompareDraw(True,"T5tttt_dM175_1700_1",1700,1)
CompareDraw(True,"T5tttt_dM175_1000_1",1000,1)

