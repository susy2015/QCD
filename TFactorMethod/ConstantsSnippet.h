#ifndef _QCDConstants_H_
#define _QCDConstants_H_

//define lumi in pb-1
//2016 Moriond
//#define LUMI 2262.946
//2016 ICHEP
//#define LUMI 8000 //test tag
//#define LUMI 4004.345 //preapp, NTuple v7 fix b working point
//#define LUMI 7647.637518921 //app, NTuple v8
#define LUMI 12918.140703927 //final 2016 ICHEP data set

#define MET_BINS 4
#define MT2_BINS 2
#define NJETS_BINS 3
#define QCD_BINS 5
//#define NSEARCH_BINS 45
//#define NSEARCH_BINS 37
#define NSEARCH_BINS 59
//#define NSEARCH_BINS 8
//const double metbins_edge[MET_BINS+1] = {175.0,200.0,350.0,500.0,650.0};
const double metbins_edge[MET_BINS+1] = {150.0,200.0,350.0,500.0,650.0};
const double mt2bins_edge[MT2_BINS+1] = {200.0,350,500.0};
//const double njetsbins_edge[NJETS_BINS+1] = {1,2,3,4};

//Constants from Zinv background
//                                  NJets =      1        2       3        4        5        6       7      >=8
//const double zinv_NJetRweightingFactor[8] = {0.926542,1.03995,0.919711,0.723581,0.869969,0.95682,0.584418,0.874059};//full status, 4.0fb-1
//const double zinv_NJetRweightingFactor[8] = {1.09758 ,0.92655,0.911107,0.728836,0.607093,0.88641,0.588388,0.851549};//preapp after csv fix,4.0fb-1
//const double zinv_NJetRweightingFactor[8] = {0.974553,1.03047,0.957998,0.806491,0.719326,0.86521,0.844148,0.599463};//v8, 7.6fb-1
const double zinv_NJetRweightingFactor[8] = {1.02845,1.08559,1.06879,0.922173,0.871796,0.99674,0.993756,0.539612};//v8 MC and v9 data, 12.9 fb-1
//const double zinv_RNorm = 0.828;//4.0fb-1, v6 and v7
//const double zinv_RNorm = 0.868;//7.6fb-1, v8
const double zinv_RNorm = 0.783;//v8 MC and v9 data, 12.9 fb-1

//const double singlemuCS_InvertedDPhi = 0.556143;
//const double singlemuCS_NormalDPhi = 0.606167;
//const double singlemuCS_InvertedDPhi = 0.579223;
//const double singlemuCS_NormalDPhi = 0.606808;
//const double singlemuCS_InvertedDPhi = 0.745792;
//const double singlemuCS_NormalDPhi = 0.762781;
const double singlemuCS_lowmet[MT2_BINS] = {0.727846,0.334243};
const double singlemuCS_invdphi = 0.669007;
#define BCBin 5

#endif
