#ifndef _QCDConstants_H_
#define _QCDConstants_H_

//define lumi in pb-1
//2016 Moriond
//#define LUMI 2262.946
//2016 ICHEP
//#define LUMI 8000 //test tag
//#define LUMI 4004.345 //preapp, NTuple v7 fix b working point
//#define LUMI 7647.637518921 //app, NTuple v8
//#define LUMI 12918.140703927 //final 2016 ICHEP data set
#define LUMI 35866.210733056 //final 2017 Moriond data set, after re miniAOD

//#define QCD_BINS 2*6//6 QCD HT sample and 2 flavor, bfilter or no bfilter
#define QCD_BINS 6//6 QCD HT sample
#define MET_BINS 4
#define MT2_BINS 2
#define MET_Ext_BINS 2
#define MET_Ext_SideBand_BINS 1
#define HT_Ext_BINS 1
#define NJETS_BINS 3
//#define NSEARCH_BINS 45
//#define NSEARCH_BINS 37
//#define NSEARCH_BINS 59
//#define NSEARCH_BINS 8
#define NSEARCH_BINS 84
//#define NSEARCH_BINS 33
//const double metbins_edge[MET_BINS+1] = {175.0,200.0,350.0,500.0,650.0};
//const double metbins_edge[MET_BINS+1] = {150.0,200.0,350.0,500.0,650.0};
const double metbins_edge[MET_BINS+1] = {200.0,250.0,350.0,450.0,600.0};
const double mt2bins_edge[MT2_BINS+1] = {200.0,400.0,800.0};
const double metbins_ext_edge[MET_Ext_BINS+1] = {200.0,250.0,600.0};
const double htbins_ext_edge[HT_Ext_BINS+1] = {300.0,2000.0};
//const double njetsbins_edge[NJETS_BINS+1] = {1,2,3,4};

#define ZINVNJETS_BINS 7
//Constants from Zinv background
//                                  NJets =      1        2       3        4        5        6       7      >=8
//const double zinv_NJetRweightingFactor[8] = {0.926542,1.03995,0.919711,0.723581,0.869969,0.95682,0.584418,0.874059};//full status, 4.0fb-1
//const double zinv_NJetRweightingFactor[8] = {1.09758 ,0.92655,0.911107,0.728836,0.607093,0.88641,0.588388,0.851549};//preapp after csv fix,4.0fb-1
//const double zinv_NJetRweightingFactor[8] = {0.974553,1.03047,0.957998,0.806491,0.719326,0.86521,0.844148,0.599463};//v8, 7.6fb-1
//const double zinv_NJetRweightingFactor[8] = {1.02845,1.08559,1.06879,0.922173,0.871796,0.99674,0.993756,0.539612};//v8 MC and v9 data, 12.9 fb-1
//const double zinv_NJetRweightingFactor[8] = {      0,      0,      0,0.715566,0.630464,0.59214,0.523173,0.406519};//v11 MC Data, 36.4 fb-1, all 2016 runs
//                                               NJets =      1        2       3        4        5       6     >=7
const double zinv_NJetRweightingFactor[ZINVNJETS_BINS] = {    0,       0,      0,0.506690,0.864817,0.84834,0.453468};//v13 Data, 35.87 fb-1, all 2016 runs
//const double zinv_RNorm = 0.828;//4.0fb-1, v6 and v7
//const double zinv_RNorm = 0.868;//7.6fb-1, v8
//const double zinv_RNorm = 0.783;//v8 MC and v9 data, 12.9 fb-1
//const double zinv_RNorm = 0.963;//v11 MC Data, 36.4 fb-1
const double zinv_RNorm = 1.146;//v13 Data, 35.87 fb-1

//Constants from single muon CS correction factor for MCDriven method
//2016 ICHEP v9 final result
//const double singlemuCS_lowmet[MT2_BINS] = {0.727846,0.334243};
//const double singlemuCS_invdphi = 0.669007;

//const double singlemuCS_lowmet[MT2_BINS] = {0.791615,0.704817};
//const double singlemuCS_invdphi = 0.775379;

//ntop and nbot 1,2, v11
//const double singlemuCS_lowmet[MT2_BINS] = {0.813645,0.521239};
//const double singlemuCS_dphi = 0.7974; //not using
//const double singlemuCS_invdphi = 0.790159;

//ntop and nbot 1,2, v12
const double singlemuCS_lowmet[MT2_BINS] = {0.725746,0.422914};
const double singlemuCS_invdphi =  0.705635;

//ntop or nbot >= 3, v11
//const double singlemuCS_ext_lowmet[MT2_BINS] = {0.686758,0.340552};
//const double singlemuCS_ext_dphi = 0.67888663; //not using
//const double singlemuCS_ext_invdphi = 0.776688;

//ntop or nbot >= 3, v12
const double singlemuCS_ext_lowmet[MT2_BINS] = {0.709523,1.20265};
const double singlemuCS_ext_invdphi = 0.737436;

#define BCBin 6
#define SFMCBin 3

#endif
