import json
import ROOT
from ROOT import TCanvas, TH1
from ROOT import TH1D
from ROOT import TLegend
from ROOT import TStyle
from ROOT import TColor, TGaxis, TH1F, TPad, TNamed 
from ROOT import kBlack, kBlue, kRed
from pprint import pprint
import numpy as np

def createCanvasPads():
  c = TCanvas("c", "canvas", 800, 800)
  # Upper histogram plot is pad1
  pad1 = TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
  pad1.SetBottomMargin(0)  # joins upper and lower plot
  pad1.SetGridx()
  pad1.Draw()
  # Lower ratio plot is pad2
  c.cd()  # returns to main canvas before defining pad2
  pad2 = TPad("pad2", "pad2", 0, 0.05, 1, 0.3)
  pad2.SetTopMargin(0)  # joins upper and lower plot
  pad2.SetBottomMargin(0.2)
  pad2.SetGridx()
  pad2.Draw()
  return c, pad1, pad2

def CompareDraw(islogy,title,mSUSYMother,mLSP):
  h_met1 = ROOT.TH1D("h_met1","",20,0,1000)
  h_met2 = ROOT.TH1D("h_met2","",20,0,1000)
  h_met3 = ROOT.TH1D("h_met3","",20,0,1000)
  h_met4 = ROOT.TH1D("h_met4","",20,0,1000)
  h_met5 = ROOT.TH1D("h_met5","",20,0,1000)
  h_met6 = ROOT.TH1D("h_met6","",20,0,1000)
  h_met7 = ROOT.TH1D("h_met7","",20,0,1000)

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

  h_metdiff1 = ROOT.TH1D("h_metdiff1","",20,-500,500)
  h_metdiff2 = ROOT.TH1D("h_metdiff2","",20,-500,500)
  h_metdiff3 = ROOT.TH1D("h_metdiff3","",20,-500,500)
  h_metdiff4 = ROOT.TH1D("h_metdiff4","",20,-500,500)
  h_metdiff5 = ROOT.TH1D("h_metdiff5","",20,-500,500)

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

  c1 = ROOT.TCanvas("c","",50,50,800,600)
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

  leg1 = ROOT.TLegend(0.35,0.70,0.90,0.90)
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

  c2 = ROOT.TCanvas("c","",50,50,800,600)
  ROOT.gStyle.SetOptStat(0);

  h_metdiff1.Draw()
  h_metdiff2.Draw("same")
  h_metdiff3.Draw("same")
  h_metdiff4.Draw("same")
  h_metdiff5.Draw("same")

  leg2 = ROOT.TLegend(0.35,0.70,0.90,0.90)
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
  f.Close()

  return

def SignalScan():
  f = ROOT.TFile.Open("root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15/SMSStudy/SignalStudy_Summer16_80X_Mar_2017_Ntp_v13p0_SMS-T5tttt_dM175_FastSim_scan_stopFlatNtuples.root", "read")
  t = f.Get("stopTreeMaker/QCDTFTree")
  SUSYMotherSUSYLSPList=[]
  i = 0  
  for event in t:
    if((event.SusyMotherMass,event.SusyLSPMass) not in SUSYMotherSUSYLSPList):
      #if(event.SusyLSPMass==1):
      if(event.SusyMotherMass==1000):
        SUSYMotherSUSYLSPList.append((event.SusyMotherMass,event.SusyLSPMass))
        print("mSUSYMother: %d, mLSP: %d" % (event.SusyMotherMass,event.SusyLSPMass))
    i = i+1
    if((i%10000) == 0):
      print("%i Events Filled!" % (i))
  f.Close()

  SUSYMotherSUSYLSPList.sort()
  print SUSYMotherSUSYLSPList
  return SUSYMotherSUSYLSPList

def mSUSYMotherTrend():
  f = ROOT.TFile.Open("root://cmseos.fnal.gov//store/group/lpcsusyhad/hua/Skimmed_2015Nov15/SMSStudy/SignalStudy_Summer16_80X_Mar_2017_Ntp_v13p0_SMS-T5tttt_dM175_FastSim_scan_stopFlatNtuples.root", "read")
  t = f.Get("stopTreeMaker/QCDTFTree")
  #SUSYMotherSUSYLSPList=[(800.0, 1.0), (900.0, 1.0), (1000.0, 1.0), (1100.0, 1.0), (1200.0, 1.0), (1250.0, 1.0), (1300.0, 1.0), (1350.0, 1.0), (1400.0, 1.0), (1450.0, 1.0), (1500.0, 1.0), (1550.0, 1.0), (1600.0, 1.0), (1650.0, 1.0), (1700.0, 1.0), (1750.0, 1.0), (1800.0, 1.0), (1850.0, 1.0), (1900.0, 1.0), (1950.0, 1.0), (2000.0, 1.0), (2050.0, 1.0), (2100.0, 1.0), (2150.0, 1.0), (2200.0, 1.0), (2250.0, 1.0), (2300.0, 1.0)]
  SUSYMotherSUSYLSPList=[(1000.0, 1.0), (1000.0, 100.0), (1000.0, 200.0), (1000.0, 300.0), (1000.0, 400.0), (1000.0, 500.0), (1000.0, 600.0), (1000.0, 650.0), (1000.0, 700.0), (1000.0, 735.0)]
  SUSYMotherSUSYLSPList=[(1100.0, 1.0), (1100.0, 100.0), (1100.0, 200.0), (1100.0, 300.0), (1100.0, 400.0), (1100.0, 500.0), (1100.0, 600.0), (1100.0, 650.0), (1100.0, 700.0), (1100.0, 750.0), (1100.0, 800.0), (1100.0, 835.0)]
  #SUSYMotherSUSYLSPList=[(2000.0, 1.0), (2000.0, 50.0), (2000.0, 100.0), (2000.0, 150.0), (2000.0, 200.0), (2000.0, 300.0), (2000.0, 400.0), (2000.0, 500.0), (2000.0, 600.0), (2000.0, 700.0), (2000.0, 800.0), (2000.0, 900.0), (2000.0, 1000.0), (2000.0, 1050.0), (2000.0, 1100.0), (2000.0, 1150.0), (2000.0, 1200.0), (2000.0, 1250.0), (2000.0, 1300.0), (2000.0, 1350.0), (2000.0, 1400.0), (2000.0, 1450.0), (2000.0, 1500.0), (2000.0, 1550.0), (2000.0, 1600.0)]
  GenLeptVetoEvt = [0]*len(SUSYMotherSUSYLSPList)
  AllPassBaselineEvt = [0]*len(SUSYMotherSUSYLSPList)
  #h_allbsl = ROOT.TH1D("h_allbsl","",40,800,2800)
  h_allbsl = ROOT.TH1D("h_allbsl","",40,0,2000)
  h_allbsl.SetLineColor(kBlue)
  #h_lepvto = ROOT.TH1D("h_lepvto","",40,800,2800)
  h_lepvto = ROOT.TH1D("h_lepvto","",40,0,2000)
  h_lepvto.SetLineColor(kRed)
  i = 0
  for event in t:
    #if(event.SusyLSPMass==1):
    if(event.SusyMotherMass==2000):
      idx=SUSYMotherSUSYLSPList.index((event.SusyMotherMass,event.SusyLSPMass))
      AllPassBaselineEvt[idx] = AllPassBaselineEvt[idx]+1
      #h_allbsl.Fill(event.SusyMotherMass,1)
      h_allbsl.Fill(event.SusyLSPMass,1)
      if(event.ifAllHadTop):
        GenLeptVetoEvt[idx] = GenLeptVetoEvt[idx]+1
        #h_lepvto.Fill(event.SusyMotherMass,1)
        h_lepvto.Fill(event.SusyLSPMass,1)
    i = i+1
    if((i%10000) == 0):
      print("%i Events Filled!" % (i))

  h_ratio = h_lepvto.Clone()
  h_ratio.Divide(h_lepvto,h_allbsl,1.0,1.0,"B")
  h_ratio.SetLineColor(kBlack)
  h_ratio.SetMarkerStyle(21)
  h_ratio.SetMarkerSize(1.5)
  #h_ratio.GetXaxis().SetTitle("mSUSYMother")
  h_ratio.GetXaxis().SetTitle("mSUSYLSP")
  h_ratio.GetYaxis().SetTitle("#frac{GenLeptVeto}{All}")

  c1, pad11, pad12 = createCanvasPads()
  #c1 = ROOT.TCanvas("c","",50,50,800,600)
  #c1.SetLogy()
  ROOT.gStyle.SetOptStat(0)
  pad11.cd()
  pad11.SetLogy()
  h_allbsl.GetYaxis().SetRangeUser(2,5000)
  h_lepvto.GetYaxis().SetRangeUser(2,5000)
  h_allbsl.Draw()
  h_lepvto.Draw("same")
  #h1.GetYaxis().SetLabelSize(0.0)
  #axis = TGaxis(-5, 20, -5, 220, 20, 220, 510, "")
  #axis.SetLabelFont(43)
  #axis.SetLabelSize(15)
  #axis.Draw()
  leg1 = ROOT.TLegend(0.35,0.70,0.90,0.90)
  leg1.SetBorderSize(1)
  leg1.SetLineColor(1)
  leg1.SetLineWidth(2)
  leg1.SetFillColor(0)
  leg1.SetTextFont(42)
  leg1.SetTextSize(0.03)
  leg1.SetHeader("T5tttt_dM175")
  leg1.AddEntry(h_allbsl,"Baseline")
  leg1.AddEntry(h_lepvto,"Baseline+GenLeptVeto")
  leg1.Draw("same")
  pad12.cd()
  h_ratio.GetYaxis().SetRangeUser(0,0.75)
  h_ratio.Draw("p")

  c1.SaveAs("_test1.png")
  c1.Close()
  f.Close()

  print GenLeptVetoEvt
  print AllPassBaselineEvt


SignalScan()
#mSUSYMotherTrend()
#CompareDraw(True,"T5tttt_dM175_2000_1",2000,1)
#CompareDraw(True,"T5tttt_dM175_1700_1",1700,1)
#CompareDraw(True,"T5tttt_dM175_1000_1",1000,1)

