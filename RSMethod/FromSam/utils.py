from ROOT import *
import sys
from array import array
import numpy as np
import random

tl = TLatex()
cmsTextFont = 61
extraTextFont = 52
lumiTextSize = 0.6
lumiTextOffset = 0.2
cmsTextSize = 0.75
cmsTextOffset = 0.1
regularfont = 42
originalfont = tl.GetTextFont()



def histoStyler(h,color):
    h.SetLineWidth(2)
    h.SetLineColor(color)
    size = 0.065
    font = 132
    h.GetXaxis().SetLabelFont(font)
    h.GetYaxis().SetLabelFont(font)
    h.GetXaxis().SetTitleFont(font)
    h.GetYaxis().SetTitleFont(font)
    h.GetYaxis().SetTitleSize(size)
    h.GetXaxis().SetTitleSize(size)
    h.GetXaxis().SetLabelSize(size)   
    h.GetYaxis().SetLabelSize(size)
    h.GetXaxis().SetTitleOffset(1.0)
    h.GetYaxis().SetTitleOffset(0.9)
    h.Sumw2()


def histoStyler2d(h): 
    h.GetYaxis().SetTitleOffset(1.2)
    h.GetXaxis().SetTitleOffset(1.0)
    size = 0.065
    font = 132
    h.GetXaxis().SetLabelFont(font)
    h.GetYaxis().SetLabelFont(font)
    h.GetXaxis().SetTitleFont(font)
    h.GetYaxis().SetTitleFont(font)
    h.GetYaxis().SetTitleSize(size)
    h.GetXaxis().SetTitleSize(size)
    h.GetXaxis().SetLabelSize(size)   
    h.GetYaxis().SetLabelSize(size)
    h.GetXaxis().SetTitleOffset(1.0)
    h.GetYaxis().SetTitleOffset(1.12)
    h.Sumw2()
    return h


binning = {}
binning['Mht']=[0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,250,300,400,500,600]
binning['Met']=binning['Mht']
binning['Ht']=[0,25,50,75,100,125,150,175,200,225,250,275,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500,1600,1800,2000,2200,2400,2600,2800,3000]
#binning['Ht']=[50,0,2500]
binning['NJets']=[14,0,14]
binning['BTags']=[0,1,2,3,4,5,6,7]
binning['Jet1Pt']=[50,0,800]
binning['Jet1Eta']=[30,-3,3]
binning['Jet2Pt']=[50,0,800]
binning['Jet2Eta']=[30,-3,3]
binning['Jet3Pt']=[50,0,800]
binning['Jet3Eta']=[30,-3,3]
binning['Jet4Pt']=[50,0,800]
binning['Jet4Eta']=[30,-3,3]
binning['MhtPhi']=[32,-3.2,3.2]
binning['DPhiJet1Mht']=[32,-3.2,3.2]
binning['DPhiJet2Mht']=[32,-3.2,3.2]
binning['DPhiJet3Mht']=[32,-3.2,3.2]
binning['DPhiJet4Mht']=[32,-3.2,3.2]


binningUser = {}#
binningUser['Mht']=[20,0,600]#
binningUser['Met']=binningUser['Mht']#
binningUser['Ht']=[10,200,2000]#
binningUser['NJets']=[6,2,14]#
binningUser['BTags']=[5,0,6]#
binningUser['Jet1Pt']=[20,0,800]#
binningUser['Jet1Eta']=[20,-3,3]#
binningUser['Jet2Pt']=[20,0,800]#
binningUser['Jet2Eta']=[20,-3,3]#
binningUser['Jet3Pt']=[20,0,800]#
binningUser['Jet3Eta']=[20,-3,3]#
binningUser['Jet4Pt']=[20,0,800]#
binningUser['Jet4Eta']=[20,-3,3]#
binningUser['MhtPhi']=[32,-3.2,3.2]
binningUser['DPhiJet1Mht']=[32,-3.2,3.2]
binningUser['DPhiJet2Mht']=[32,-3.2,3.2]
binningUser['DPhiJet3Mht']=[32,-3.2,3.2]
binningUser['DPhiJet4Mht']=[32,-3.2,3.2]

binning2d = {}
binning2d['Mht']=[0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,220,240,260,280,300,320,340,360,380,400,425,450,475,500,525,550,575,600]
binning2d['Met']=binning2d['Mht']
binning2d['Ht']=[0,25,50,75,100,125,150,175,200,225,250,275,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400,1450,1500,1600,1800,2000,2200,2400,2600,2800,3000]
binning2d['NJets']=[6,2,14]
binning2d['BTags']=[6,0,6]
binning2d['Jet1Pt']=[60,0,2000]
binning2d['Jet1Eta']=[40,-3,3]
binning2d['Jet2Pt']=[40,0,800]
binning2d['Jet2Eta']=[40,-3,3]
binning2d['Jet3Pt']=[40,0,800]
binning2d['Jet3Eta']=[40,-3,3]
binning2d['Jet4Pt']=[40,0,800]
binning2d['Jet4Eta']=[40,-3,3]
binning2d['MhtPhi']=[32,-3.2,3.2]
binning2d['DPhiJet1Mht']=[32,-3.2,3.2]
binning2d['DPhiJet2Mht']=[32,-3.2,3.2]
binning2d['DPhiJet3Mht']=[32,-3.2,3.2]
binning2d['DPhiJet4Mht']=[32,-3.2,3.2]

binningTemplate = {}
binningTemplate['Mht']=[300,0,600]
binningTemplate['Mht']=[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,150,155,160,165,170,175,180,185,190,195,200,220,240,260,280,300,400,500,800]
binningTemplate['Met']=binningTemplate['Mht']
binningTemplate['Ht']=[0,300,500,700,1000,1500,2000,5000]
binningTemplate['NJets']=[10,0,10]
binningTemplate['BTags']=[0,1,2,5]
binningTemplate['Jet1Pt']=[20,0,800]
binningTemplate['Jet1Eta']=[20,-3,3]
binningTemplate['Jet2Pt']=[20,0,800]
binningTemplate['Jet2Eta']=[20,-3,3]
binningTemplate['Jet3Pt']=[20,0,800]
binningTemplate['Jet3Eta']=[20,-3,3]
binningTemplate['Jet4Pt']=[20,0,800]
binningTemplate['Jet4Eta']=[20,-3,3]
binningTemplate['DPhiJet1Mht']=[126,-3.15,3.15]
binningTemplate['DPhiJet2Mht']=binningTemplate['DPhiJet1Mht']
binningTemplate['DPhiJet3Mht']=binningTemplate['DPhiJet1Mht']
binningTemplate['DPhiJet4Mht']=binningTemplate['DPhiJet1Mht']

baseline = {}
baseline['Mht'] = 100
baseline['Ht'] = 500
baseline['NJets'] = 3
baseline['BTags'] = 0

baselineStr = {}
baselineStr['Mht']='H_{T}^{miss} > '+str(baseline['Mht'])+' GeV'
baselineStr['Ht']='H_{T} > '+str(baseline['Ht'])+' GeV'
baselineStr['NJets']='N_{jets} > '+str(baseline['NJets'])
baselineStr['BTags']=''


def Struct(*args, **kwargs):
    def init(self, *iargs, **ikwargs):
        for k,v in kwargs.items():
            setattr(self, k, v)
        for i in range(len(iargs)):
            setattr(self, args[i], iargs[i])
        for k,v in ikwargs.items():
            setattr(self, k, v)

    name = kwargs.pop("name", "MyStruct")
    kwargs.update(dict((k, None) for k in args))
    return type(name, (object,), {'__init__': init, '__slots__': kwargs.keys()})

def mkHistoStruct(var):
    histoStruct = Struct('Branch','Truth','GenSmeared','Gen','Rebalanced','RplusS')
    if len(binning[var])==3:
        nbins = binning[var][0]
        low = binning[var][1]
        high = binning[var][2]
        histoStruct.Branch = TH1F('h'+var+'Branch',var+'Branch',nbins,low,high)
        histoStruct.Truth = TH1F('h'+var+'Truth',var+'Truth',nbins,low,high)
        histoStruct.GenSmeared = TH1F('h'+var+'GenSmeared',var+'GenSmeared',nbins,low,high)
        histoStruct.Gen = TH1F('h'+var+'Gen',var+'Gen',nbins,low,high)
        histoStruct.Rebalanced = TH1F('h'+var+'Rebalanced',var+'Rebalanced',nbins,low,high)
        histoStruct.RplusS = TH1F('h'+var+'RplusS',var+'RplusS',nbins,low,high)
    else:
        nBin = len(binning[var])-1
        binArr = array('d',binning[var])
        histoStruct.Branch = TH1F('h'+var+'Branch',var+'Branch',nBin,binArr)
        histoStruct.Truth = TH1F('h'+var+'Truth',var+'Truth',nBin,binArr)
        histoStruct.GenSmeared = TH1F('h'+var+'GenSmeared',var+'GenSmeared',nBin,binArr)
        histoStruct.Gen = TH1F('h'+var+'Gen',var+'Gen',nBin,binArr)
        histoStruct.Rebalanced = TH1F('h'+var+'Rebalanced',var+'Rebalanced',nBin,binArr)
        histoStruct.RplusS = TH1F('h'+var+'RplusS',var+'RplusS',nBin,binArr)
    histoStyler(histoStruct.Branch,19)
    histoStyler(histoStruct.Truth,kRed)
    histoStyler(histoStruct.GenSmeared,kBlack)
    histoStyler(histoStruct.Gen,kGreen)
    histoStyler(histoStruct.Rebalanced,kBlue)
    histoStyler(histoStruct.RplusS,kBlack)
    return histoStruct


def mkQuadStruct(var, tree):
    quad = Struct('Branch','Truth','GenSmeared','Gen')
    quad.Branch = np.zeros(1,dtype=float)
    quad.Truth = np.zeros(1,dtype=float)
    quad.GenSmeared = np.zeros(1,dtype=float)
    quad.Gen = np.zeros(1,dtype=float)
    tree.Branch(var+'Branch',quad.Branch,var+'Branch/D')
    tree.Branch(var+'Truth',quad.Truth,var+'Truth/D')
    tree.Branch(var+'GenSmeared',quad.GenSmeared,var+'GenSmeared/D')
    tree.Branch(var+'Gen',quad.Gen,var+'Gen/D')
    tree.Branch(var+'Rebalanced',quad.Rebalanced,var+'Rebalanced/D')
    tree.Branch(var+'RplusS',quad.RplusS,var+'RplusS/D')
    return quad

def initializeQuads(quadDict):
    for key in quadDict:
        #print 'key', key
        quadDict[key].Branch[0] = -11.0
        quadDict[key].Truth[0] = -11.0
        quadDict[key].GenSmeared[0] = -11.0
        quadDict[key].Gen[0] = -11.0
        quadDict[key].Rebalanced[0] = -11.0
        quadDict[key].RplusS[0] = -11.0
                
def writeHistoStruct(hStructDict):
    for key in hStructDict:
        print 'writing histogram structure:', key
        hStructDict[key].Branch.Write()
        hStructDict[key].Truth.Write()
        hStructDict[key].GenSmeared.Write()
        hStructDict[key].Gen.Write()
        hStructDict[key].Rebalanced.Write()
        hStructDict[key].RplusS.Write()


def mkTag(lo2):
    if lo2[0]==lo2[1]:
        str_ = ' = '+str(lo2[0])
    else:
        str_ = '~['+str(lo2[0])+','+str(lo2[1])+']'
    return str_

def countJets(tlvvec,thresh):
    count = 0
    for j in range(len(tlvvec)):
        if tlvvec[j].Pt()>thresh and abs(tlvvec[j].Eta())<2.4: count+=1
    return count


def countBJets(tlvvec, csvvec,thresh):
    count = 0
    for j in range(len(tlvvec)):
        if tlvvec[j].Pt()>thresh and abs(tlvvec[j].Eta())<2.4 and csvvec[j]>0.89: count+=1
    return count


def passesSelectionWithMatching(t, leptype='ele'):
    if not bool(ord(t.JetID)): return False
    if t.NJets<4: return False
    if leptype=='ele': 
        if (t.MuonsNum>0): return False
        if (t.Electrons.size()==0): return False
        matched = False
        for e in range(len(t.Electrons)):
            if not abs(t.genParticles_PDGid[e])==11: continue
            for g in range(len(t.genParticles)):
                if t.Electrons[e].DeltaR(t.genParticles[g])<0.5:
                    matched = True
                    break

def getMatchedCsv(GenJets, RecoJets, CsvVec):
    CsvVec_ = []
    for gjet in GenJets:
        dR = 9
        csv_ = 0
        for ireco in range(len(RecoJets)):
            rjet = RecoJets[ireco]
            dR_ = gjet.DeltaR(rjet)
            if dR_<dR:
                dR=dR_
                csv_ = CsvVec[ireco]
                if dR_<0.25: break
        CsvVec_.append(csv_)
    return CsvVec_

def smearJets(tlvVec, csvVec, histvec, hEtaTemplate, hPtTemplate):
    tlvVec_ = []
    csvVec_ = []
    #print 'before smearing:'
    #for i in range(len(tlvVec)): print tlvVec[i].Pt(), tlvVec[i].Eta(), csvVec[i]
    for j in range(len(tlvVec)):   
        tlv = tlvVec[j]
        tlvVec_.append(tlv.Clone())
        csvVec_.append(csvVec[j])        
        if not (tlv.Pt()>2):
            continue                 
        ieta = hEtaTemplate.GetXaxis().FindBin(abs(tlv.Eta()))
        ipt = hPtTemplate.GetXaxis().FindBin(tlv.Pt()) # change when you redo templates
        rando = histvec[ieta][ipt].GetRandom()
        if rando==float('inf'): 
            rando = 1      
        tlvVec_[-1]*=rando
        #print 'helpin out a brother', histvec[ieta][ipt].GetName()
        #histvec[ieta][ipt].Draw()
        #c1.Update()
        #pause()
    tlv_csv = [list(x) for x in zip(*sorted(zip(tlvVec_, csvVec_), key=lambda pair: -pair[0].Pt()))]
    #print 'after smearing:'
    #for i in range(len(tlv_csv[0])):print tlv_csv[0][i].Pt(), tlv_csv[0][i].Eta(), tlv_csv[1][i],'n'
    return tlv_csv


import time
beginning = time.time()
counters = [0 for i in xrange(1000)]
prevTime = time.time()
def uc(i):
    global prevTime
    now = time.time()
    counters[i] += now - prevTime
    prevTime = now
def printResults():
    global prevTime
    for i, x in enumerate(counters):
        print i, x
if time.time()-beginning>10:
    print "it's big!"
    print printResults()
    #exit(0)
    
def rebalanceJets(tlvVec, csvVec, fRTemplates, hEtaTemplate, hPtTemplate, fGenMhtTemplates, fGenDPhiTemplates,hHtTemplate):#modify to make smart start for one of the jets to put the MHT below 200.
    tlvVec_ = []
    csvVec_ = []
    tlvUntouched = []
    csvUntouched = []
    ptaxis = hPtTemplate.GetXaxis()
    for j in range(len(tlvVec)):
        tlv = tlvVec[j] 
        csv = csvVec[j]    
        if tlv.Pt()<30 or j>3:
            tlvUntouched.append(tlv.Clone())
            csvUntouched.append(csv)
            continue           
        tlvVec_.append(tlv.Clone())
        csvVec_.append(csv)   
    nparams = len(tlvVec_)
    def fcn( npar, gin, f, par, iflag ):
        prevTime = time.time()
        rTlvVec_ = []
        rCsvVec_ = []
        prod = 1
        uc(0)
        for i in range(nparams):
            rCsvVec_.append(csvVec_[i])
            rTlvVec_.append(tlvVec_[i].Clone())
            rTlvVec_[i]*=1.0/par[i]
            ptNew = rTlvVec_[i].Pt()
            ietaNew = abs(hEtaTemplate.GetXaxis().FindBin(abs(rTlvVec_[i].Eta())))# this should never change.
            iptNew = ptaxis.FindBin(ptNew)
            ptBinC = ptaxis.GetBinCenter(iptNew)
            #if i==0: print 'templates=', ietaNew, iptNew
            if ptNew-ptBinC>0: otherbin = 1
            else: otherbin = -1
            PtBinOther = ptaxis.GetBinCenter(iptNew+otherbin)
            a = (PtBinOther-ptNew)/(PtBinOther-ptBinC)
            b = (ptNew-ptBinC)/(PtBinOther-ptBinC)
            interpolatedFactor = 0.5*(a*fRTemplates[ietaNew][iptNew].Eval(par[i]) + b*fRTemplates[ietaNew][iptNew+otherbin].Eval(par[i]))
            prod*=interpolatedFactor
            #prod*=fRTemplates[ietaNew][iptNew].Eval(par[i])#i think this is right.

        rht = getHT(rTlvVec_,30)
        iht = hHtTemplate.GetXaxis().FindBin(rht)
        
        ibjet, bjet = getLeadingBJet(rTlvVec_, rCsvVec_) #perhaps try to do this only when a clever flag flips.
        if ibjet==-1:
            leadjet = max(rTlvVec_, key=lambda p: p.Pt())
            fGenMhtTemplate = fGenMhtTemplates[0][iht]
            fGenDPhiTemplate = fGenDPhiTemplates[0][iht]
        else: 
            leadjet = bjet
            fGenMhtTemplate = fGenMhtTemplates[1][iht]
            fGenDPhiTemplate = fGenDPhiTemplates[1][iht]
        rTlvVec_+=tlvUntouched
        rmht, rphi = getMHT(rTlvVec_,30)#delta phi, fixed
        rMhtVec = TLorentzVector() #change to return tlv?
        rMhtVec.SetPtEtaPhiE(rmht,0,rphi,rmht) #change to return tlv?
        rdphi = rMhtVec.DeltaPhi(leadjet)
        prod*=fGenDPhiTemplate.Eval(rmht)
        prod*=fGenDPhiTemplate.Eval(rdphi)#try commenting this line. does MHT always go down?
        f[0] = -prod
        #print 'f[0] = -TMath.Log(prod)=', f[0]
        
    gMinuit = TMinuit(nparams)
    gMinuit.SetPrintLevel(-1)
    gMinuit.SetFCN( fcn )
    arglist = array( 'd', nparams*[1.0] )
    arglist[0]=0
    ierflg = Long(1982)#Long(0)#
    gMinuit.mnexcm( "SET ERR", arglist, 1, ierflg )##can we do without this?  
    for i in range(nparams):#0.95+(0.1*i%1)
        gMinuit.mnparm(i,'c'+str(i),1.0,0.03,0.3,3.5,ierflg) #try much larger step size; with MIGRAD too
    gMinuit.SetMaxIterations(20000)
    arglist[0] = 20000
    try:
        arglist[1] = 1
    except: pass
    test = gMinuit.mnexcm( "MINIMIZE", arglist, 2, ierflg )
    amin, edm, errdef = Double(0.18), Double(0.19), Double(0.05)
    nvpar, nparx, icstat = Long(1983), Long(1984), Long(1985)
    gMinuit.mnstat( amin, edm, errdef, nvpar, nparx, icstat )
    gMinuit.mnprin( 3, amin )
    #if not (ierflg==0): return [[],[]]
    currentValue = np.zeros(1,dtype=float)
    currentError = np.zeros(1,dtype=float)
    for i in range(nparams):
        gMinuit.GetParameter (i, currentValue, currentError)
        tlvVec_[i]*=1.0/currentValue[0]#don't forget to change this back for harrison
        #tlvVec_[i]*=currentValue[0]
        
    tlvVec_+=tlvUntouched
    csvVec_+=csvUntouched
        
    omht, odphi = getMHT(tlvVec,30)
    #for j in range(len(tlvVec)): print 'jet',j,tlvVec[j].Pt(), csvVec[j]
    print 'oldmht = ', omht, odphi
    rmht, rdphi = getMHT(tlvVec_,30)
    #for j in range(len(tlvVec_)): print 'jet',j,tlvVec_[j].Pt(), csvVec_[j]
    print 'newmht = ', rmht, rdphi
    print 'eierflg = ', ierflg
    tlv_csv = [list(x) for x in zip(*sorted(zip(tlvVec_, csvVec_), key=lambda pair: -pair[0].Pt()))]
    #quicktlv, quickcsv = tlv_csv
    #for j in range(len(quicktlv)): print 'jetEND',j,quicktlv[j].Pt(), quickcsv[j]
    return tlv_csv





#def rebalanceJets(tlvVec, csvVec, fRTemplates, hEtaTemplate, hPtTemplate, fGenMhtTemplates, fGenDPhiTemplates):
def rebalanceJetsOld(tlvVec, csvVec, fRTemplates, hEtaTemplate, hPtTemplate, fGenMhtTemplates, fGenDPhiTemplates):
    tlvVec_ = []
    csvVec_ = []
    flist_ = []#
    tlvUntouched = []
    csvUntouched = []
    for j in range(len(tlvVec)):
        tlv = tlvVec[j] 
        csv = csvVec[j]    
        if tlv.Pt()<15:
            tlvUntouched.append(tlv.Clone())
            csvUntouched.append(csv)
            continue           
        tlvVec_.append(tlv.Clone())
        csvVec_.append(csvVec[j])   
        ieta = hEtaTemplate.GetXaxis().FindBin(abs(tlv.Eta()))
        ipt = hPtTemplate.GetXaxis().FindBin(tlv.Pt())
        flist_.append(fRTemplates[ieta][ipt])
        
    nparams = len(flist_)
    print 'len(flist)=', len(flist_)

    ibjet, bjet = getLeadingBJet(tlvVec, csvVec)
    if ibjet==-1: 
        print 'b=0'
        fGenMhtTemplate = fGenMhtTemplates[0]
        fGenDPhiTemplate = fGenDPhiTemplates[0]
        i_axis = 0
    else: 
        print 'b=1'
        i_axis = ibjet
        fGenMhtTemplate = fGenMhtTemplates[1]
        fGenDPhiTemplate = fGenDPhiTemplates[1]

    def fcn( npar, gin, f, par, iflag ):#this all needs a lot of work for b-tags
        rTlvVec_ = []
        prod = 1
        for i in range(nparams):
            prod*=flist_[i].Eval(par[i])
            rTlvVec_.append(tlvVec_[i].Clone())
            rTlvVec_[i]*=par[i]
        rTlvVec_+=tlvUntouched
        #rTlvVec_=sorted(rTlvVec_, key=lambda thing: -thing.Pt())
        rmht, rphi = getMHT(rTlvVec_,30)#delta phi, fixed
        rMhtVec = TLorentzVector()
        rMhtVec.SetPtEtaPhiE(rmht,0,rphi,rmht)
        rdphi = rMhtVec.DeltaPhi(rTlvVec_[i_axis])
        #rmht = min(100,rmht)
        prod*=fGenMhtTemplate.Eval(rmht)
        prod*=fGenDPhiTemplate.Eval(rdphi)
        f[0] = -prod
        
    gMinuit = TMinuit(nparams)
    gMinuit.SetPrintLevel(-1)
    gMinuit.SetFCN( fcn )
    arglist = array( 'd', nparams*[1.0] )
    arglist[0]=0
    ierflg = Long(0)#Long(1982)
    gMinuit.mnexcm( "SET ERR", arglist, 1, ierflg )##can we do without this?  
    for i in range(nparams):
        gMinuit.mnparm(i,'c'+str(i),0.98+(0.2*i%1),0.002,0.3,3.5,ierflg)
    gMinuit.SetMaxIterations(50000)
    arglist[0] = 50000
    try:
        arglist[1] = 1
    except: pass
    test = gMinuit.mnexcm( "MINIMIZE", arglist, 2, ierflg )
    amin, edm, errdef = Double(0.18), Double(0.19), Double(0.05)
    nvpar, nparx, icstat = Long(1983), Long(1984), Long(1985)
    gMinuit.mnstat( amin, edm, errdef, nvpar, nparx, icstat )
    gMinuit.mnprin( 3, amin )
    
    clist_ = []
    elist_ = []
    for i in range(nparams):
        currentValue = np.zeros(1,dtype=float)
        currentError = np.zeros(1,dtype=float)
        gMinuit.GetParameter (i, currentValue, currentError)
        clist_.append(currentValue)
        elist_.append(currentError)
        tlvVec_[i]*=clist_[i]
        
    tlvVec_+=tlvUntouched
    csvVec_+=csvUntouched
        
    omht, odphi = getMHT(tlvVec,30)
    #for j in range(len(tlvVec)): print 'jet',j,tlvVec[j].Pt(), csvVec[j]
    print 'oldmht = ', omht, odphi
    rmht, rdphi = getMHT(tlvVec_,30)
    #for j in range(len(tlvVec_)): print 'jet',j,tlvVec_[j].Pt(), csvVec_[j]
    print 'newmht = ', rmht, rdphi
    tlv_csv = [list(x) for x in zip(*sorted(zip(tlvVec_, csvVec_), key=lambda pair: -pair[0].Pt()))]
    #quicktlv, quickcsv = tlv_csv
    #for j in range(len(quicktlv)): print 'jetEND',j,quicktlv[j].Pt(), quickcsv[j]
    return tlv_csv



def rebalanceJets2(tlvVec, csvVec, fRTemplates, hEtaTemplate, hPtTemplate, fGenMhtTemplates, fGenDPhiTemplates):

    tlvVec_ = []#jets to be stretched
    csvVec_ = []#corresponding csv's
    flist_ = []
    tlvUntouched = []#remaindor
    csvUntouched = []#
    startMht, startMhtPhi = getMHT(tlvVec,30)
    startMhtVec = TLorentzVector()
    startMhtVec.SetPtEtaPhiE(startMht,0,startMhtPhi,startMht)

    
    for j in range(len(tlvVec)):
        tlv = tlvVec[j] 
        csv = csvVec[j]    
        if tlv.Pt()<12:
            tlvUntouched.append(tlv.Clone())
            csvUntouched.append(csv)
            continue           
        tlvVec_.append(tlv.Clone())
        csvVec_.append(csvVec[j])   
        ieta = hEtaTemplate.GetXaxis().FindBin(abs(tlv.Eta()))
        ipt = hPtTemplate.GetXaxis().FindBin(tlv.Pt())
        flist_.append(fRTemplates[ieta][ipt])
    n2stretch = len(tlvVec_)
    nparams = n2stretch-2
    print ''
    print 'len(flist)=', len(flist_)

    ibjet, bjet = getLeadingBJet(tlvVec, csvVec)
    i1 = -1
    i2 = -1
    attempts = 10
    iAttempt = 0
    while i1==-1 and i2==-1:
        if ibjet==-1:
            print 'doin b0'
            luckyMht = fGenMhtTemplates[0].GetRandom()
            luckyDMhtPhi = fGenDPhiTemplates[0].GetRandom()
            luckyMhtPhi = tlvVec_[0].Phi()+luckyDMhtPhi
        else:
            print 'doing b1'
            luckyMht = fGenMhtTemplates[1].GetRandom()
            luckyDMhtPhi = fGenDPhiTemplates[1].GetRandom()
            luckyMhtPhi = bjet.Phi()+luckyDMhtPhi
            
        luckyMhtVec = TLorentzVector()
        luckyMhtVec.SetPtEtaPhiE(luckyMht,0,luckyMhtPhi,luckyMht)
        luckyMhtPx = luckyMhtVec.Px()
        luckyMhtPy = luckyMhtVec.Py()

        print 'starting mht, phi=', startMhtVec.Pt(), startMhtVec.Phi()
        print 'lucky mht, phi=', luckyMhtVec.Pt(), luckyMhtVec.Phi()

        dMhtX = array('d',[luckyMhtPx - startMhtVec.Px()])
        dMhtY = array('d',[luckyMhtPy - startMhtVec.Py()])
        constrainedC1 = array('d',[1.0])
        constrainedC2 = array('d',[1.0])

        figMerit = 999
        stop = False
        quickrange = range(0,n2stretch)
        random.shuffle(quickrange)
        #for itool2 in range(1,n2stretch):
        for itool2 in quickrange:
            if stop: break
            #for itool1 in range(itool2):
            for itool1 in quickrange:
                if itool1==itool2:continue
                constrainedC1[0] = -(dMhtY[0]*tlvVec_[itool2].Px()-tlvVec_[itool1].Py()*tlvVec_[itool2].Px()-dMhtX[0]*tlvVec_[itool2].Py()+tlvVec_[itool1].Px()*tlvVec_[itool2].Py())
                constrainedC1[0]/=(tlvVec_[itool1].Py()*tlvVec_[itool2].Px()-tlvVec_[itool1].Px()*tlvVec_[itool2].Py())
                constrainedC2[0] = -(dMhtY[0]*tlvVec_[itool1].Px()-dMhtX[0]*tlvVec_[itool1].Py()+tlvVec_[itool1].Py()*tlvVec_[itool2].Px()-tlvVec_[itool1].Px()*tlvVec_[itool2].Py())
                constrainedC2[0]/=(-tlvVec_[itool1].Py()*tlvVec_[itool2].Px()+tlvVec_[itool1].Px()*tlvVec_[itool2].Py())
                if constrainedC1[0]>0.1 and constrainedC2[0]>0.1 and constrainedC1[0] < 3.5 and constrainedC2[0] < 3.5: 
                    figMerit_ = pow(pow(constrainedC1[0]-1,2)+pow(constrainedC2[0]-1,2),0.5)
                    if figMerit_ < figMerit: 
                        figMerit = figMerit_
                        i1 = itool1
                        i2 = itool2
                        print 'found i1, i2', i1, i2, 'to make c1c2=', constrainedC1[0],constrainedC2[0]
                        if figMerit<0.8: 
                            stop = True
                            break
        if i1==-1 or i2==-1: 
            print "no solutions possible!, starting over"
            iAttempt+=1
            if iAttempt>attempts:
                return [[],[]]

    #checked that basically C1 and C2 are perfect

    def fcn( npar, gin, f, par, iflag ):
        rTlvVec_ = []
        prod = 1.0
        ipar = 0
        for i in range(n2stretch):
            if i==i1 or i==i2: 
                rTlvVec_.append(tlvVec_[i].Clone())
                continue
            #ipar+=1#was here
            prod*=flist_[i].Eval(par[ipar])
            rTlvVec_.append(tlvVec_[i].Clone())
            rTlvVec_[i]*=par[ipar]
            ipar+=1
        rTlvVec_+=tlvUntouched ##could consider skipping this when all originalPt>30 jets are treated as bendy
        #rTlvVec_=sorted(rTlvVec_, key=lambda thing: -thing.Pt())
        rmht, rphi = getMHT(rTlvVec_,30)#delta phi, fixed
        rMhtVec = TLorentzVector()
        rMhtVec.SetPtEtaPhiE(rmht,0,rphi,rmht)
        dMhtX[0] = luckyMhtPx - rMhtVec.Px()
        dMhtY[0] = luckyMhtPy - rMhtVec.Py()
        constrainedC1[0] = -(dMhtY[0]*tlvVec_[i2].Px()-tlvVec_[i1].Py()*tlvVec_[i2].Px()-dMhtX[0]*tlvVec_[i2].Py()+tlvVec_[i1].Px()*tlvVec_[i2].Py())
        constrainedC1[0]/=(tlvVec_[i1].Py()*tlvVec_[i2].Px()-tlvVec_[i1].Px()*tlvVec_[i2].Py())
        constrainedC2[0] = -(dMhtY[0]*tlvVec_[i1].Px()-dMhtX[0]*tlvVec_[i1].Py()+tlvVec_[i1].Py()*tlvVec_[i2].Px()-tlvVec_[i1].Px()*tlvVec_[i2].Py())
        constrainedC2[0]/=(-tlvVec_[i1].Py()*tlvVec_[i2].Px()+tlvVec_[i1].Px()*tlvVec_[i2].Py())
        rTlvVec_[i1]*=constrainedC1[0]
        rTlvVec_[i2]*=constrainedC2[0]
        #print 'intermediateMht=', getMHT(rTlvVec_,30)
        #print 'with c1, c2=', constrainedC1[0], constrainedC2[0]
        largenumber = 99999999999
        prod*=((flist_[i1].Eval(constrainedC1[0])))#addedthat)*(1+(constrainedC1[0]<0.1)*largenumber*(constrainedC1[0]-0.1))+(constrainedC1[0]<0.1)*largenumber*(constrainedC1[0]-0.1))
        prod*=((flist_[i2].Eval(constrainedC2[0])))#addedthat)*(1+(constrainedC2[0]<0.1)*largenumber*(constrainedC2[0]-0.1))+(constrainedC1[0]<0.1)*largenumber*(constrainedC1[0]-0.1))
        f[0] = -prod
        
    gMinuit = TMinuit(nparams)
    gMinuit.SetPrintLevel(-1)
    gMinuit.SetFCN( fcn )
    arglist = array( 'd', max(1,nparams)*[1.0] )
    arglist[0]=0
    ierflg = Long(0)#Long(1982)
    gMinuit.mnexcm( "SET ERR", arglist, 1, ierflg )##can we do without this?  
    ipar = 0
    for i in range(n2stretch):
        if i==i1 or i==i2: continue
        gMinuit.mnparm(ipar,'c'+str(i+1),0.985+0*(0.02*i%1),0.01,0.3,3.5,ierflg)
        ipar+=1
    gMinuit.SetMaxIterations(50000)
    arglist[0] = 50000
    try:
        arglist[1] = 1
    except: pass
    test = gMinuit.mnexcm( "SIMPLEX", arglist, 2, ierflg )
    amin, edm, errdef = Double(0.18), Double(0.19), Double(0.05)
    nvpar, nparx, icstat = Long(1983), Long(1984), Long(1985)
    gMinuit.mnstat( amin, edm, errdef, nvpar, nparx, icstat )
    gMinuit.mnprin( 3, amin )
    
    clist_ = []
    elist_ = []
    ipar = 0
    for i in range(n2stretch):
        if i==i1 or i==i2:
            currentValue = 1.0
            currentError = 0.01
        else:
            currentValue = np.zeros(1,dtype=float)
            currentError = np.zeros(1,dtype=float)
            gMinuit.GetParameter (ipar, currentValue, currentError)
            ipar+=1
        clist_.append(currentValue)
        elist_.append(currentError)
        tlvVec_[i]*=clist_[i]
        
    tlvVec_+=tlvUntouched
    csvVec_+=csvUntouched

    rmht, rphi = getMHT(tlvVec_,30)#delta phi, fixed
    rMhtVec = TLorentzVector()
    rMhtVec.SetPtEtaPhiE(rmht,0,rphi,rmht)
    dMhtX[0] = luckyMhtPx - rMhtVec.Px()
    dMhtY[0] = luckyMhtPy - rMhtVec.Py()
    constrainedC1[0] = -(dMhtY[0]*tlvVec_[i2].Px()-tlvVec_[i1].Py()*tlvVec_[i2].Px()-dMhtX[0]*tlvVec_[i2].Py()+tlvVec_[i1].Px()*tlvVec_[i2].Py())
    constrainedC1[0]/=(tlvVec_[i1].Py()*tlvVec_[i2].Px()-tlvVec_[i1].Px()*tlvVec_[i2].Py())
    constrainedC2[0] = -(dMhtY[0]*tlvVec_[i1].Px()-dMhtX[0]*tlvVec_[i1].Py()+tlvVec_[i1].Py()*tlvVec_[i2].Px()-tlvVec_[i1].Px()*tlvVec_[i2].Py())
    constrainedC2[0]/=(-tlvVec_[i1].Py()*tlvVec_[i2].Px()+tlvVec_[i1].Px()*tlvVec_[i2].Py())
    tlvVec_[i1]*=constrainedC1[0]
    tlvVec_[i2]*=constrainedC2[0]
    newMht, newPhi = getMHT(tlvVec_,30)
        
    omht, odphi = getMHT(tlvVec,30)
    #for j in range(len(tlvVec)): print 'jet',j,tlvVec[j].Pt(), csvVec[j]
    print 'oldmht = ', omht, odphi
    #for j in range(len(tlvVec_)): print 'jet',j,tlvVec_[j].Pt(), csvVec_[j]
    print 'newmht = ', newMht, newPhi
    print 'C['+str(i1)+'], C['+str(i2)+']=', constrainedC1, constrainedC2
    tlv_csv = [list(x) for x in zip(*sorted(zip(tlvVec_, csvVec_), key=lambda pair: -pair[0].Pt()))]
    #quicktlv, quickcsv = tlv_csv
    #for j in range(len(quicktlv)): print 'jetEND',j,quicktlv[j].Pt(), quickcsv[j]
    if constrainedC1[0]<0 or constrainedC2[0] < 0:
        print 'redoing the whole thing'
        tlv_csv = rebalanceJets2(tlvVec, csvVec, fRTemplates, hEtaTemplate, hPtTemplate, fGenMhtTemplates, fGenDPhiTemplates)
        print 'this was the redo'
    return tlv_csv


def getLeadingGenBJet(GenJets, RecoJets, CsvVec):
    for gjet in GenJets:
        for ireco in range(len(RecoJets)):
            rjet = RecoJets[ireco]
            dR_ = gjet.DeltaR(rjet)
            if dR_<0.4 and CsvVec[ireco]>0.89:
                return gjet
    emptyvec = TLorentzVector()
    return emptyvec

def getLeadingBJet(RecoJets, CsvVec):
    for ireco in range(len(RecoJets)):
        if not RecoJets[ireco].Pt()>30: continue
        if CsvVec[ireco]>0.89: return [ireco,RecoJets[ireco]]
    emptyvec = TLorentzVector()
    return [-1,emptyvec]

def getLeadingBJet2(RecoJets, CsvVec):
    jlistCopy = list(RecoJets)
    clistCopy = list(CsvVec)
    jlistCopy, clistCopy = [list(x) for x in zip(*sorted(zip(jlistCopy, clistCopy), key=lambda pair: -pair[0].Pt()))]
    for ireco in range(len(jlistCopy)):
        if not jlistCopy[ireco].Pt()>30: break
        if clistCopy[ireco]>0.89: return [ireco,jlistCopy[ireco]]
    emptyvec = TLorentzVector()
    return [-1,emptyvec]


def getZleptons(leptons, zlow=70, zhigh=110):
    tlvVec_ = []
    for ilep in range(leptons):
        for jlep in range(ilep):
            matched = False
            m = (leptons[ilep]+leptons[jlep]).M()
            if not (m>zlow and m<zhigh):continue
            tlvVec_.append(leptons(ilep))
            tlvVec.append(leptons(jlep))
    return tlvVec_


def cleanJets(tlvVec, zleptons, zlow=70, zhigh=110):
    tlvVec_ = []
    for tlv in tlvVec:
        matched = False
        for zleptons in zleptons:
            dr = tlv.DeltaR(zleptons)
            if dr<0.4:
                matched = True
                break
        if matched: continue
        tlvVec_.append(tlv)  
    return tlvVec_


def getMHT(tlvVec,thresh):
    mhtvec = TLorentzVector()
    for tlv in tlvVec:
        if not (tlv.Pt()>thresh): continue
        if not (abs(tlv.Eta())<5.0): continue
        mhtvec-=tlv
    return [mhtvec.Pt(), mhtvec.Phi()]

def getMET(originalMet,originalJets,newJets):
    if not len(originalJets)==len(newJets):
        print 'mismatch'; exit()
    newMET = originalMet.Clone()
    for jet in originalJets:
        newMET+=jet
    for jet in newJets:
        newMET-=jet
    return [newMET.Pt(), newMET.Phi()]

def getHT(tlvVec,thresh):
    ht = 0
    for tlv in tlvVec:
        if not (abs(tlv.Eta())<2.4): continue
        if not (tlv.Pt()>thresh): continue
        ht+=tlv.Pt()
    return ht

def mklegend(x1=.1105, y1=.53, x2=.3805, y2=.8, color=kWhite):
    lg = TLegend(x1, y1, x2, y2)
    lg.SetFillColor(color)
    lg.SetTextFont(42)
    lg.SetBorderSize(0)
    lg.SetShadowColor(kWhite)
    lg.SetFillStyle(0)
    return lg

'''
def mk2dHistoStruct(var1, var2):
    histoStruct = Struct('Branch','Truth','GenSmeared','Gen')
    nbins1 = binning2d[var1][0]
    low1 = binning2d[var1][1]
    high1 = binning2d[var1][2]
    nbins2 = binning2d[var2][0]
    low2 = binning2d[var2][1]
    high2 = binning2d[var2][2]
    histoStruct.Branch = TH2F('h'+var1+'Vs'+var2+'Branch',var1+'Vs'+var2+'Branch',nbins2,low2,high2,nbins1,low1,high1)
    histoStruct.Truth = TH2F('h'+var1+'Vs'+var2+'Truth',var1+'Vs'+var2+'Truth',nbins2,low2,high2,nbins1,low1,high1)
    histoStruct.GenSmeared = TH2F('h'+var1+'Vs'+var2+'GenSmeared',var1+'Vs'+var2+'GenSmeared',nbins2,low2,high2,nbins1,low1,high1)
    histoStruct.Gen = TH2F('h'+var1+'Vs'+var2+'Gen',var1+'Vs'+var2+'Gen',nbins2,low2,high2,nbins1,low1,high1)
    histoStyler(histoStruct.Branch,19)
    histoStyler(histoStruct.Truth,kRed)
    histoStyler(histoStruct.GenSmeared,kBlack)
    histoStyler(histoStruct.Gen,kGreen)
    return histoStruct
'''

def mk2dHistoStruct(var1, var2):
    histoStruct = Struct('Branch','Truth','GenSmeared','Gen')
    if len(binning[var1])==3 and len(binning[var2])==3:
        nbins1 = binning[var1][0]
        low1 = binning[var1][1]
        high1 = binning[var1][2]
        nbins2 = binning[var2][0]
        low2 = binning[var2][1]
        high2 = binning[var2][2]
        histoStruct.Branch = TH2F('h'+var1+'Vs'+var2+'Branch',var1+'Vs'+var2+'Branch',nbins2,low2,high2,nbins1,low1,high1)
        histoStruct.Truth = TH2F('h'+var1+'Vs'+var2+'Truth',var1+'Vs'+var2+'Truth',nbins2,low2,high2,nbins1,low1,high1)
        histoStruct.GenSmeared = TH2F('h'+var1+'Vs'+var2+'GenSmeared',var1+'Vs'+var2+'GenSmeared',nbins2,low2,high2,nbins1,low1,high1)
        histoStruct.Gen = TH2F('h'+var1+'Vs'+var2+'Gen',var1+'Vs'+var2+'Gen',nbins2,low2,high2,nbins1,low1,high1)
        histoStruct.Rebalanced = TH2F('h'+var1+'Vs'+var2+'Rebalanced',var1+'Vs'+var2+'Rebalanced',nbins2,low2,high2,nbins1,low1,high1)
        histoStruct.RplusS = TH2F('h'+var1+'Vs'+var2+'RplusS',var1+'Vs'+var2+'RplusS',nbins2,low2,high2,nbins1,low1,high1)
    elif len(binning[var1])==3 and len(binning[var2])!=3:
        nbins1 = binning[var1][0]
        low1 = binning[var1][1]
        high1 = binning[var1][2]
        nBin2 = len(binning[var2])-1
        binArr2 = array('d',binning[var2])
        histoStruct.Branch = TH2F('h'+var1+'Vs'+var2+'Branch',var1+'Vs'+var2+'Branch',nBin2,binArr2,nbins1,low1,high1)
        histoStruct.Truth = TH2F('h'+var1+'Vs'+var2+'Truth',var1+'Vs'+var2+'Truth',nBin2,binArr2,nbins1,low1,high1)
        histoStruct.GenSmeared = TH2F('h'+var1+'Vs'+var2+'GenSmeared',var1+'Vs'+var2+'GenSmeared',nBin2,binArr2,nbins1,low1,high1)
        histoStruct.Gen = TH2F('h'+var1+'Vs'+var2+'Gen',var1+'Vs'+var2+'Gen',nBin2,binArr2,nbins1,low1,high1)
        histoStruct.Rebalanced = TH2F('h'+var1+'Vs'+var2+'Rebalanced',var1+'Vs'+var2+'Rebalanced',nBin2,binArr2,nbins1,low1,high1)
        histoStruct.RplusS = TH2F('h'+var1+'Vs'+var2+'RplusS',var1+'Vs'+var2+'RplusS',nBin2,binArr2,nbins1,low1,high1)
    elif len(binning[var1])!=3 and len(binning[var2])==3:
        nBin1 = len(binning[var1])-1
        binArr1 = array('d',binning[var1])
        nbins2 = binning[var2][0]
        low2 = binning[var2][1]
        high2 = binning[var2][2]
        histoStruct.Branch = TH2F('h'+var1+'Vs'+var2+'Branch',var1+'Vs'+var2+'Branch',nbins2,low2,high2,nBin1,binArr1)
        histoStruct.Truth = TH2F('h'+var1+'Vs'+var2+'Truth',var1+'Vs'+var2+'Truth',nbins2,low2,high2,nBin1,binArr1)
        histoStruct.GenSmeared = TH2F('h'+var1+'Vs'+var2+'GenSmeared',var1+'Vs'+var2+'GenSmeared',nbins2,low2,high2,nBin1,binArr1)
        histoStruct.Gen = TH2F('h'+var1+'Vs'+var2+'Gen',var1+'Vs'+var2+'Gen',nbins2,low2,high2,nBin1,binArr1)
        histoStruct.Rebalanced = TH2F('h'+var1+'Vs'+var2+'Rebalanced',var1+'Vs'+var2+'Rebalanced',nbins2,low2,high2,nBin1,binArr1)
        histoStruct.RplusS = TH2F('h'+var1+'Vs'+var2+'RplusS',var1+'Vs'+var2+'RplusS',nbins2,low2,high2,nBin1,binArr1)
    else:
        nBin1 = len(binning[var1])-1
        binArr1 = array('d',binning[var1])
        nBin2 = len(binning[var2])-1
        binArr2 = array('d',binning[var2])
        histoStruct.Branch = TH2F('h'+var1+'Vs'+var2+'Branch',var1+'Vs'+var2+'Branch',nBin2,binArr2,nBin1,binArr1)
        histoStruct.Truth = TH2F('h'+var1+'Vs'+var2+'Truth',var1+'Vs'+var2+'Truth',nBin2,binArr2,nBin1,binArr1)
        histoStruct.GenSmeared = TH2F('h'+var1+'Vs'+var2+'GenSmeared',var1+'Vs'+var2+'GenSmeared',nBin2,binArr2,nBin1,binArr1)
        histoStruct.Gen = TH2F('h'+var1+'Vs'+var2+'Gen',var1+'Vs'+var2+'Gen',nBin2,binArr2,nBin1,binArr1)
        histoStruct.Rebalanced = TH2F('h'+var1+'Vs'+var2+'Rebalanced',var1+'Vs'+var2+'Rebalanced',nBin2,binArr2,nBin1,binArr1)
        histoStruct.RplusS = TH2F('h'+var1+'Vs'+var2+'RplusS',var1+'Vs'+var2+'RplusS',nBin2,binArr2,nBin1,binArr1)
    histoStyler(histoStruct.Branch,6)
    histoStyler(histoStruct.Truth,kRed)
    histoStyler(histoStruct.GenSmeared,kBlack)
    histoStyler(histoStruct.Gen,kGreen)
    histoStyler(histoStruct.Rebalanced,kBlue)
    histoStyler(histoStruct.RplusS,kBlack)
    return histoStruct

def selFromJets(tlvvec,thresh,nminus1var = ''):
    #if not t.BTags==0: return False
    nminus1var = ''###################these are not n-1 sels!!!
    if not 'NJets' in nminus1var:
        if not countJets(tlvvec,thresh)>2: return False
    if not 'Ht' in nminus1var:
        if not getHT(tlvvec,thresh)>300: return False
    if not 'Mht' in nminus1var:
        if not getMHT(tlvvec,thresh)>100: return False
    return True

def pause(thingy='please push enter'):
    import sys
    print thingy
    sys.stdout.flush()
    raw_input('')

def mkmet(metPt, metPhi):
    met = TLorentzVector()
    met.SetPtEtaPhiE(metPt, 0, metPhi, metPt)
    return met
    
