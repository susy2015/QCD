#include "ConstantsSnippet.h"

const double metbins_edge[MET_BINS+1] = {175.0,200.0,350.0,500.0,650.0};
const double mt2bins_edge[MT2_BINS+1] = {200.0,350,500.0};
//const double njetsbins_edge[NJETS_BINS+1] = {1,2,3,4};

class QCDBGModel
{
 public:
  int Set_metbin_number( double met );
  int Set_njetsbin_number( int njets );
  int Set_mt2bin_number( double mt2 );
};
