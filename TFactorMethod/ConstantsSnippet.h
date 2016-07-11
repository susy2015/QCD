#ifndef _QCDConstants_H_
#define _QCDConstants_H_

//define lumi in pb-1
//2016 Moriond
//#define LUMI 2262.946
//2016 ICHEP
//#define LUMI 8000
#define LUMI 4004.345

#define MET_BINS 4
#define MT2_BINS 2
#define NJETS_BINS 3
#define QCD_BINS 5
//#define NSEARCH_BINS 45
//#define NSEARCH_BINS 37
#define NSEARCH_BINS 59

const double metbins_edge[MET_BINS+1] = {175.0,200.0,350.0,500.0,650.0};
const double mt2bins_edge[MT2_BINS+1] = {200.0,350,500.0};
//const double njetsbins_edge[NJETS_BINS+1] = {1,2,3,4};


//                                  NJets =      1        2       3        4        5        6       7      >=8
//const double zinv_NJetRweightingFactor[8] = {0.926542,1.03995,0.919711,0.723581,0.869969,0.95682,0.584418,0.874059};
const double zinv_NJetRweightingFactor[8] = {1.09758 ,0.92655,0.911107,0.728836,0.607093,0.88641,0.588388,0.851549};
const double zinv_RNorm = 0.828;

#define BCBin 5

#endif
