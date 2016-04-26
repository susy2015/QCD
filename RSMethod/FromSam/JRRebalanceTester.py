import os,sys
from ROOT import *
from utils import *
from array import array
from glob import glob


gROOT.SetBatch(1)

def selection(Ht,Mht,NJets,BTags,nminus1var = ''):
	#if not t.BTags==0: return False
	#nminus1var = ''###################these are not n-1 sels!!!
	if not 'NJets' in nminus1var:
		if not NJets>baseline['NJets']: return False
	if not 'Ht' in nminus1var:
		if not Ht>baseline['Ht']: return False
	if not 'Mht' in nminus1var:
		if not Mht>baseline['Mht']: return False
	return True

ntries = 1
pwd = '/uscms_data/d3/sbein/Ra2slashB2015/Official/Jan18/CMSSW_7_4_15/src/HomeQCD'#os.getcwd()
try: datamc = sys.argv[1]
except: datamc = 'MC'
try: htedge = sys.argv[2]
except: htedge = '700'
try: quickrun = bool(sys.argv[3])
except: quickrun = False

temlname = pwd+'/Templates/megatemplateUltraIsoPureNob0JetID_Ht500.root'
temlname = pwd+'/Templates/megatemplateUltraIsoPureCosJetID.root'
temlname = pwd+'/Templates/megatemplateUltraIsoPureNob0JetID.root'

print 'temlname=',temlname
ftemplate = TFile(temlname)
print 'using templates from',temlname
hPtTemplate = ftemplate.Get('hPtTemplate')
templatePtAxis = hPtTemplate.GetXaxis()
hEtaTemplate = ftemplate.Get('hEtaTemplate')
templateEtaAxis = hEtaTemplate.GetXaxis()
fGenMhtTemplateB0 = ftemplate.Get('splines/hGenMhtPtB0_spline')
fGenDPhiTemplateB0 = ftemplate.Get('splines/hGenDPhiJet1_spline')
fGenMhtTemplateB1 = ftemplate.Get('splines/hGenMhtPtB1_spline')
fGenDPhiTemplateB1 = ftemplate.Get('splines/hGenDPhiBJet1_spline')
fGenMhtTemplates = [fGenMhtTemplateB0,fGenMhtTemplateB1]
fGenDPhiTemplates = [fGenDPhiTemplateB0, fGenDPhiTemplateB1]
newfilename = ('TruthAndMethodHT'+htedge+temlname.replace(pwd+'/Templates/megatemplate','')+'.root')
newfilename = newfilename.replace('.root.root','.root')
fNew = TFile(newfilename.replace('.root','.root'),'recreate')
print 'creating new file:',newfilename


hHt = TH1F('hHt','hHt',120,0,2500)
hHt.Sumw2()
hHtWeighted = TH1F('hHtWeighted','hHtWeighted',120,0,2500)
hHtWeighted.Sumw2()


fRTemplates = ['']
hRTemplates = ['']
for ieta in range(1,templateEtaAxis.GetNbins()+2):
	fRTemplates.append([''])
	hRTemplates.append([''])
	etarange = str(templateEtaAxis.GetBinLowEdge(ieta))+'-'+str(templateEtaAxis.GetBinUpEdge(ieta))
	for ipt in range(1,templatePtAxis.GetNbins()+2):
		lowedge = templatePtAxis.GetBinLowEdge(ipt)
		upedge = templatePtAxis.GetBinUpEdge(ipt)
		ptrange = str(lowedge)+'-'+str(upedge)
		f = ftemplate.Get('splines/hRTemplate(rPt'+ptrange+', rEta'+etarange+')_spline')
		fRTemplates[-1].append(f)
		h = ftemplate.Get('hRTemplate(gPt'+ptrange+', gEta'+etarange+')')
		hRTemplates[-1].append(h)


histoStructDict = {}
for var in varlist: histoStructDict[var] = mkHistoStruct(var)

TwoDHistos = [['Mht','Ht'],['Mht','BTags'],['Mht','NJets'],['Mht','Jet1Pt'],['Mht','Jet2Pt'],['Jet1Pt','Jet2Pt'],['Jet1Pt','Jet3Pt'],['Jet1Pt','Jet4Pt'],['Jet1Eta','Jet2Eta'],['Jet1Eta','Jet3Eta'],['Jet1Eta','Jet4Eta']]
histo2dStructDict = {}
for histo in TwoDHistos:
	histo2dStructDict[histo[0]+'Vs'+histo[1]] = mk2dHistoStruct(histo[0],histo[1])

t = TChain('TreeMaker2/PreSelection')
filefile = open(pwd+'/filelists/filelistQCD.txt')
rawfiles = filefile.readlines()
filelist = []
for rawfile in rawfiles: 
	if not 'HT'+htedge+'to' in rawfile: continue
	filelist.append(rawfile.strip())

if quickrun: 
	for f in filelist[:1]: t.Add('root://cmseos.fnal.gov//store/user/sbein/Ra2slashB/myProduction/'+f)
	nevents = 1200
	verbosity = 1
else: 
	for flong in filelist: t.Add('root://cmseos.fnal.gov//store/user/sbein/Ra2slashB/myProduction/'+flong)
	nevents = t.GetEntries() #nevents = 2000
	verbosity = 1000

print 'nevents=', nevents
for ientry in range(nevents):
	if ientry%verbosity==0:
		print "processing event",ientry
	t.GetEntry(ientry)
	hHt.Fill(t.HT,1)
	hHtWeighted.Fill(t.genHT,t.Weight)
	if not (bool(t.JetID)): continue
	#if not t.BTags==0: continue
	thresh = 30
	MetVec = mkmet(t.METPt, t.METPhi)
	genMetVec = mkmet(t.GenMETPt, t.GenMETPhi)
	
	bMhtVec = TLorentzVector()
	bMhtVec.SetPtEtaPhiE(t.MHT,0,t.MHT_Phi,t.MHT)
	bMetPt = t.METPt
	if selection(t.HT,t.MHT,t.NJets,t.BTags,'MhtVsHt'): histo2dStructDict['MhtVsHt'].Branch.Fill(t.HT,t.MHT,t.Weight)
	if selection(t.HT,t.MHT,t.NJets,t.BTags,'MhtVsBTags'):histo2dStructDict['MhtVsBTags'].Branch.Fill(t.BTags,t.MHT,t.Weight)
	if selection(t.HT,t.MHT,t.NJets,t.BTags,'MhtVsNJets'): histo2dStructDict['MhtVsNJets'].Branch.Fill(t.NJets,t.MHT,t.Weight)
	if selection(t.HT,t.MHT,t.NJets,t.BTags,'Mht'): histoStructDict['Mht'].Branch.Fill(t.MHT,t.Weight)
	if selection(t.HT,t.MHT,t.NJets,t.BTags,'Mht'): histoStructDict['MhtPhi'].Branch.Fill(bMhtVec.Phi(),t.Weight)
	if selection(t.HT,t.MHT,t.NJets,t.BTags,'Mht'): histoStructDict['Met'].Branch.Fill(bMetPt,t.Weight)
	if selection(t.HT,t.MHT,t.NJets,t.BTags,'Ht'): histoStructDict['Ht'].Branch.Fill(t.HT,t.Weight)
	if selection(t.HT,t.MHT,t.NJets,t.BTags,'NJets'): histoStructDict['NJets'].Branch.Fill(t.NJets,t.Weight)
	if selection(t.HT,t.MHT,t.NJets,t.BTags,'BTags'): histoStructDict['BTags'].Branch.Fill(t.BTags,t.Weight)
	if selection(t.HT,t.MHT,t.NJets,t.BTags,'Mht'):
		try:#
			histoStructDict['DPhiJet1Mht'].Branch.Fill(t.Jets[0].DeltaPhi(bMhtVec),t.Weight)
			histoStructDict['Jet1Pt'].Branch.Fill(t.Jets[0].Pt(),t.Weight)
			histoStructDict['Jet1Eta'].Branch.Fill(t.Jets[0].Eta(),t.Weight)
			histo2dStructDict['MhtVsJet1Pt'].Branch.Fill(t.Jets[0].Pt(),t.MHT,t.Weight)
			histoStructDict['Jet2Pt'].Branch.Fill(t.Jets[1].Pt(),t.Weight)
			histoStructDict['Jet2Eta'].Branch.Fill(t.Jets[1].Eta(),t.Weight)
			histo2dStructDict['MhtVsJet2Pt'].Branch.Fill(t.Jets[1].Pt(),t.MHT,t.Weight)
			histo2dStructDict['Jet1EtaVsJet2Eta'].Branch.Fill(t.Jets[1].Eta(),t.Jets[0].Eta(),t.Weight)
			histoStructDict['Jet3Pt'].Branch.Fill(t.Jets[2].Pt(),t.Weight)
			histoStructDict['Jet3Eta'].Branch.Fill(t.Jets[2].Eta(),t.Weight)
			histo2dStructDict['MhtVsJet3Pt'].Branch.Fill(t.Jets[2].Pt(),t.MHT,t.Weight)
			histo2dStructDict['Jet1PtVsJet3Pt'].Branch.Fill(t.Jets[2].Pt(),t.Jets[0].Pt(),t.Weight)
			histo2dStructDict['Jet1EtaVsJet3Eta'].Branch.Fill(t.Jets[2].Eta(),t.Jets[0].Eta(),t.Weight)
			histoStructDict['Jet4Pt'].Branch.Fill(t.Jets[3].Pt(),t.Weight)
			histoStructDict['Jet4Eta'].Branch.Fill(t.Jets[3].Eta(),t.Weight)
			histo2dStructDict['MhtVsJet4Pt'].Branch.Fill(t.Jets[3].Pt(),t.MHT,t.Weight)
			histo2dStructDict['Jet1PtVsJet4Pt'].Branch.Fill(t.Jets[3].Pt(),t.Jets[0].Pt(),t.Weight)
			histo2dStructDict['Jet1EtaVsJet4Eta'].Branch.Fill(t.Jets[3].Eta(),t.Jets[0].Eta(),t.Weight)
		except:
			pass

	tHt = getHT(t.JetSlim,thresh)
	tMht, tMhtPhi = getMHT(t.JetSlim,thresh)
	tNJets = countJets(t.JetSlim,thresh)
	tBTags = countBJets(t.JetSlim,t.JetsSlim_bDiscriminatorCSV,thresh)
	tMhtVec = TLorentzVector()
	tMetPt = getMET(MetVec, t.JetSlim, t.JetSlim)[0]
	if not tBTags==t.BTags: print 'mismatch'
	if selection(tHt,tMht,tNJets,tBTags,'MhtVsHt'): histo2dStructDict['MhtVsHt'].Truth.Fill(tHt,tMht,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'MhtVsNJets'): histo2dStructDict['MhtVsNJets'].Truth.Fill(tNJets,tMht,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'MhtVsBTags'): histo2dStructDict['MhtVsBTags'].Truth.Fill(tBTags,tMht,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'Mht'): histoStructDict['Mht'].Truth.Fill(tMht,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'Mht'): histoStructDict['MhtPhi'].Truth.Fill(tMhtPhi,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'Mht'): histoStructDict['Met'].Truth.Fill(tMetPt,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'Ht'): histoStructDict['Ht'].Truth.Fill(tHt,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'NJets'): histoStructDict['NJets'].Truth.Fill(tNJets,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'BTags'): histoStructDict['BTags'].Truth.Fill(tBTags,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'Mht'):
		try:
			histoStructDict['DPhiJet1Mht'].Truth.Fill(t.JetSlim[0].DeltaPhi(tMhtVec),t.Weight)
			histoStructDict['Jet1Pt'].Truth.Fill(t.JetSlim[0].Pt(),t.Weight)
			histoStructDict['Jet1Eta'].Truth.Fill(t.JetSlim[0].Eta(),t.Weight)
			histo2dStructDict['MhtVsJet1Pt'].Truth.Fill(t.JetSlim[0].Pt(),tMht,t.Weight)
			histoStructDict['Jet2Pt'].Truth.Fill(t.JetSlim[1].Pt(),t.Weight)
			histoStructDict['Jet2Eta'].Truth.Fill(t.JetSlim[1].Eta(),t.Weight)
			histo2dStructDict['MhtVsJet2Pt'].Truth.Fill(t.JetSlim[1].Pt(),tMht,t.Weight)
			histo2dStructDict['Jet1PtVsJet2Pt'].Truth.Fill(t.JetSlim[1].Pt(),t.JetSlim[0].Pt(),t.Weight)
			histo2dStructDict['Jet1EtaVsJet2Eta'].Truth.Fill(t.JetSlim[1].Eta(),t.JetSlim[0].Eta(),t.Weight)
			histoStructDict['Jet3Pt'].Truth.Fill(t.JetSlim[2].Pt(),t.Weight)
			histoStructDict['Jet3Eta'].Truth.Fill(t.JetSlim[2].Eta(),t.Weight)
			histo2dStructDict['Jet1PtVsJet3Pt'].Truth.Fill(t.JetSlim[2].Pt(),t.JetSlim[0].Pt(),t.Weight)
			histo2dStructDict['Jet1EtaVsJet3Eta'].Truth.Fill(t.JetSlim[2].Eta(),t.JetSlim[0].Eta(),t.Weight)
			histoStructDict['Jet4Pt'].Truth.Fill(t.JetSlim[3].Pt(),t.Weight)
			histoStructDict['Jet4Eta'].Truth.Fill(t.JetSlim[3].Eta(),t.Weight)
			histo2dStructDict['Jet1PtVsJet4Pt'].Truth.Fill(t.JetSlim[3].Pt(),t.JetSlim[0].Pt(),t.Weight)
			histo2dStructDict['Jet1EtaVsJet4Eta'].Truth.Fill(t.JetSlim[3].Eta(),t.JetSlim[0].Eta(),t.Weight)
		except:
			pass

	ntries = 1
	for i in range(ntries):
		rebalancedJets,csvRebalancedJets = rebalanceJets2(t.JetSlim,t.JetsSlim_bDiscriminatorCSV,fRTemplates,\
														 hEtaTemplate,hPtTemplate, fGenMhtTemplates, fGenDPhiTemplates)
		mHt = getHT(rebalancedJets,thresh)
		mMht, mMhtPhi = getMHT(rebalancedJets,thresh)
		mNJets = countJets(rebalancedJets,thresh)
		mBTags = countBJets(rebalancedJets,csvRebalancedJets,thresh)
		mMhtVec = TLorentzVector()
		mMhtVec.SetPtEtaPhiE(mMht,0,mMhtPhi,mMht)
		mMetPt = getMET(MetVec, t.JetSlim, rebalancedJets)[0]
		if selection(tHt,tMht,tNJets,tBTags,'MhtVsHt'): histo2dStructDict['MhtVsHt'].Rebalanced.Fill(mHt,mMht,t.Weight/ntries)
		if selection(tHt,tMht,tNJets,tBTags,'MhtVsNJets'):histo2dStructDict['MhtVsNJets'].Rebalanced.Fill(mNJets,mMht,t.Weight/ntries)
		if selection(tHt,tMht,tNJets,tBTags,'MhtVsBTags'):histo2dStructDict['MhtVsBTags'].Rebalanced.Fill(mBTags,mMht,t.Weight/ntries)
		if selection(tHt,tMht,tNJets,tBTags,'Mht'): histoStructDict['Mht'].Rebalanced.Fill(mMht,t.Weight/ntries)
		if selection(tHt,tMht,tNJets,tBTags,'Mht'): histoStructDict['MhtPhi'].Rebalanced.Fill(mMhtPhi,t.Weight)
		if selection(tHt,tMht,tNJets,tBTags,'Mht'): histoStructDict['Met'].Rebalanced.Fill(mMetPt,t.Weight/ntries)
		if selection(tHt,tMht,tNJets,tBTags,'Ht'): histoStructDict['Ht'].Rebalanced.Fill(mHt,t.Weight/ntries)
		if selection(tHt,tMht,tNJets,tBTags,'NJets'): histoStructDict['NJets'].Rebalanced.Fill(mNJets,t.Weight/ntries)
		if selection(tHt,tMht,tNJets,tBTags,'BTags'): histoStructDict['BTags'].Rebalanced.Fill(mBTags,t.Weight/ntries)
		if selection(tHt,tMht,tNJets,tBTags,'Mht'):
			try:
				histoStructDict['DPhiJet1Mht'].Rebalanced.Fill(rebalancedJets[0].DeltaPhi(mMhtVec),t.Weight)
				histoStructDict['Jet1Pt'].Rebalanced.Fill(rebalancedJets[0].Pt(),t.Weight/ntries)
				histoStructDict['Jet1Eta'].Rebalanced.Fill(rebalancedJets[0].Eta(),t.Weight/ntries)
				histo2dStructDict['MhtVsJet1Pt'].Rebalanced.Fill(rebalancedJets[0].Pt(),mMht,t.Weight/ntries)
				histoStructDict['Jet2Pt'].Rebalanced.Fill(rebalancedJets[1].Pt(),t.Weight/ntries)
				histoStructDict['Jet2Eta'].Rebalanced.Fill(rebalancedJets[1].Eta(),t.Weight/ntries)
				histo2dStructDict['MhtVsJet2Pt'].Rebalanced.Fill(rebalancedJets[1].Pt(),mMht,t.Weight/ntries)
				histo2dStructDict['Jet1PtVsJet2Pt'].Rebalanced.Fill(rebalancedJets[1].Pt(),rebalancedJets[0].Pt(),t.Weight/ntries)
				histo2dStructDict['Jet1EtaVsJet2Eta'].Rebalanced.Fill(rebalancedJets[1].Eta(),rebalancedJets[0].Eta(),t.Weight/ntries)
				histoStructDict['Jet3Pt'].Rebalanced.Fill(rebalancedJets[2].Pt(),t.Weight/ntries)
				histoStructDict['Jet3Eta'].Rebalanced.Fill(rebalancedJets[2].Eta(),t.Weight/ntries)
				histo2dStructDict['Jet1PtVsJet3Pt'].Rebalanced.Fill(rebalancedJets[2].Pt(),rebalancedJets[0].Pt(),t.Weight/ntries)
				histo2dStructDict['Jet1EtaVsJet3Eta'].Rebalanced.Fill(rebalancedJets[2].Eta(),rebalancedJets[0].Eta(),t.Weight/ntries)
				histoStructDict['Jet4Pt'].Rebalanced.Fill(rebalancedJets[3].Pt(),t.Weight/ntries)
				histoStructDict['Jet4Eta'].Rebalanced.Fill(rebalancedJets[3].Eta(),t.Weight/ntries)
				histo2dStructDict['Jet1PtVsJet4Pt'].Rebalanced.Fill(rebalancedJets[3].Pt(),rebalancedJets[0].Pt(),t.Weight/ntries)
				histo2dStructDict['Jet1EtaVsJet4Eta'].Rebalanced.Fill(rebalancedJets[3].Eta(),rebalancedJets[0].Eta(),t.Weight/ntries)
			except:
				pass


	ntries = 1
	matchedCsvVec = getMatchedCsv(t.GenJets,t.JetSlim,t.JetsSlim_bDiscriminatorCSV)
	for i in range(ntries):
		smearedJets,csvSmearedJets = smearJets(t.GenJets,matchedCsvVec,hRTemplates,hEtaTemplate,hPtTemplate)
		mHt = getHT(smearedJets,thresh)
		mMht, mMhtPhi = getMHT(smearedJets,thresh)
		mNJets = countJets(smearedJets,thresh)
		mBTags = countBJets(smearedJets,csvSmearedJets,thresh)
		mMhtVec = TLorentzVector()
		mMhtVec.SetPtEtaPhiE(mMht,0,mMhtPhi,mMht)
		mMetPt = getMET(genMetVec, t.GenJets, smearedJets)[0]
		if selection(mHt,mMht,mNJets,mBTags,'MhtVsHt'): histo2dStructDict['MhtVsHt'].GenSmeared.Fill(mHt,mMht,t.Weight/ntries)
		if selection(mHt,mMht,mNJets,mBTags,'MhtVsNJets'):histo2dStructDict['MhtVsNJets'].GenSmeared.Fill(mNJets,mMht,t.Weight/ntries)
		if selection(mHt,mMht,mNJets,mBTags,'MhtVsBTags'):histo2dStructDict['MhtVsBTags'].GenSmeared.Fill(mBTags,mMht,t.Weight/ntries)
		if selection(mHt,mMht,mNJets,mBTags,'Mht'): histoStructDict['Mht'].GenSmeared.Fill(mMht,t.Weight/ntries)
		if selection(mHt,mMht,mNJets,mBTags,'Mht'): histoStructDict['MhtPhi'].GenSmeared.Fill(mMhtPhi,t.Weight)
		if selection(mHt,mMht,mNJets,mBTags,'Mht'): histoStructDict['Met'].GenSmeared.Fill(mMetPt,t.Weight/ntries)
		if selection(mHt,mMht,mNJets,mBTags,'Ht'): histoStructDict['Ht'].GenSmeared.Fill(mHt,t.Weight/ntries)
		if selection(mHt,mMht,mNJets,mBTags,'NJets'): histoStructDict['NJets'].GenSmeared.Fill(mNJets,t.Weight/ntries)
		if selection(mHt,mMht,mNJets,mBTags,'BTags'): histoStructDict['BTags'].GenSmeared.Fill(mBTags,t.Weight/ntries)
		if selection(mHt,mMht,mNJets,mBTags,'Mht'):
			try:
				histoStructDict['DPhiJet1Mht'].GenSmeared.Fill(smearedJets[0].DeltaPhi(mMhtVec),t.Weight)
				histoStructDict['Jet1Pt'].GenSmeared.Fill(smearedJets[0].Pt(),t.Weight/ntries)
				histoStructDict['Jet1Eta'].GenSmeared.Fill(smearedJets[0].Eta(),t.Weight/ntries)
				histo2dStructDict['MhtVsJet1Pt'].GenSmeared.Fill(smearedJets[0].Pt(),mMht,t.Weight/ntries)
				histoStructDict['Jet2Pt'].GenSmeared.Fill(smearedJets[1].Pt(),t.Weight/ntries)
				histoStructDict['Jet2Eta'].GenSmeared.Fill(smearedJets[1].Eta(),t.Weight/ntries)
				histo2dStructDict['MhtVsJet2Pt'].GenSmeared.Fill(smearedJets[1].Pt(),mMht,t.Weight/ntries)
				histo2dStructDict['Jet1PtVsJet2Pt'].GenSmeared.Fill(smearedJets[1].Pt(),smearedJets[0].Pt(),t.Weight/ntries)
				histo2dStructDict['Jet1EtaVsJet2Eta'].GenSmeared.Fill(smearedJets[1].Eta(),smearedJets[0].Eta(),t.Weight/ntries)
				histoStructDict['Jet3Pt'].GenSmeared.Fill(smearedJets[2].Pt(),t.Weight/ntries)
				histoStructDict['Jet3Eta'].GenSmeared.Fill(smearedJets[2].Eta(),t.Weight/ntries)
				histo2dStructDict['Jet1PtVsJet3Pt'].GenSmeared.Fill(smearedJets[2].Pt(),smearedJets[0].Pt(),t.Weight/ntries)
				histo2dStructDict['Jet1EtaVsJet3Eta'].GenSmeared.Fill(smearedJets[2].Eta(),smearedJets[0].Eta(),t.Weight/ntries)
				histoStructDict['Jet4Pt'].GenSmeared.Fill(smearedJets[3].Pt(),t.Weight/ntries)
				histoStructDict['Jet4Eta'].GenSmeared.Fill(smearedJets[3].Eta(),t.Weight/ntries)
				histo2dStructDict['Jet1PtVsJet4Pt'].GenSmeared.Fill(smearedJets[3].Pt(),smearedJets[0].Pt(),t.Weight/ntries)
				histo2dStructDict['Jet1EtaVsJet4Eta'].GenSmeared.Fill(smearedJets[3].Eta(),smearedJets[0].Eta(),t.Weight/ntries)
			except:
				pass


	gHt = getHT(t.GenJets,thresh)
	gMht, gMhtPhi = getMHT(t.GenJets,thresh)
	gNJets = countJets(t.GenJets,thresh)
	gBTags = countBJets(t.GenJets,matchedCsvVec,thresh)
	gMhtVec = TLorentzVector()
	gMhtVec.SetPtEtaPhiE(gMht,0,gMhtPhi,gMht)
	gMetPt = genMetVec.Pt()  
	if selection(tHt,tMht,tNJets,tBTags,'MhtVsHt'): histo2dStructDict['MhtVsHt'].Gen.Fill(gHt,gMht,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'MhtVsNJets'):histo2dStructDict['MhtVsNJets'].Gen.Fill(gNJets,gMht,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'MhtVsBTags'):histo2dStructDict['MhtVsBTags'].Gen.Fill(gBTags,gMht,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'Mht'):histoStructDict['Mht'].Gen.Fill(gMht,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'Mht'): histoStructDict['MhtPhi'].Gen.Fill(gMhtPhi,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'Mht'):histoStructDict['Met'].Gen.Fill(gMetPt,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'Ht'):histoStructDict['Ht'].Gen.Fill(gHt,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'NJets'):histoStructDict['NJets'].Gen.Fill(gNJets,t.Weight)
	if selection(tHt,tMht,tNJets,tBTags,'BTags'): histoStructDict['BTags'].Gen.Fill(gBTags,t.Weight)  
	if selection(tHt,tMht,tNJets,tBTags,'Mht'):
		try:
			histoStructDict['DPhiJet1Mht'].Gen.Fill(t.GenJets[0].DeltaPhi(gMhtVec),t.Weight)
			histoStructDict['Jet1Pt'].Gen.Fill(t.GenJets[0].Pt(),t.Weight)
			histoStructDict['Jet1Eta'].Gen.Fill(t.GenJets[0].Eta(),t.Weight)
			histo2dStructDict['MhtVsJet1Pt'].Gen.Fill(t.GenJets[0].Pt(),gMht,t.Weight)
			histoStructDict['Jet2Pt'].Gen.Fill(t.GenJets[1].Pt(),t.Weight)
			histoStructDict['Jet2Eta'].Gen.Fill(t.GenJets[1].Eta(),t.Weight)
			histo2dStructDict['MhtVsJet2Pt'].Gen.Fill(t.GenJets[1].Pt(),gMht,t.Weight)
			histo2dStructDict['Jet1PtVsJet2Pt'].Gen.Fill(t.GenJets[1].Pt(),t.GenJets[0].Pt(),t.Weight)
			histo2dStructDict['Jet1EtaVsJet2Eta'].Gen.Fill(t.GenJets[1].Eta(),t.GenJets[0].Eta(),t.Weight)
			histoStructDict['Jet3Pt'].Gen.Fill(t.GenJets[2].Pt(),t.Weight)
			histoStructDict['Jet3Eta'].Gen.Fill(t.GenJets[2].Eta(),t.Weight)
			histo2dStructDict['Jet1PtVsJet3Pt'].Gen.Fill(t.GenJets[3].Pt(),t.GenJets[0].Pt(),t.Weight)
			histo2dStructDict['Jet1EtaVsJet3Eta'].Gen.Fill(t.GenJets[3].Eta(),t.GenJets[0].Eta(),t.Weight)
			histoStructDict['Jet4Pt'].Gen.Fill(t.GenJets[3].Pt(),t.Weight)
			histoStructDict['Jet4Eta'].Gen.Fill(t.GenJets[3].Eta(),t.Weight)
			histo2dStructDict['Jet1PtVsJet4Pt'].Gen.Fill(t.GenJets[4].Pt(),t.GenJets[0].Pt(),t.Weight)
			histo2dStructDict['Jet1EtaVsJet4Eta'].Gen.Fill(t.GenJets[4].Eta(),t.GenJets[0].Eta(),t.Weight)
		except:
			pass


fNew.cd()
writeHistoStruct(histoStructDict)
writeHistoStruct(histo2dStructDict)
hHt.Write()
hHtWeighted.Write()
fNew.Close()
