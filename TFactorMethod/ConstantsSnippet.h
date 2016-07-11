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

#define BCBin 5

#endif
