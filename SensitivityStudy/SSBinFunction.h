#define NTOPJETS_BINS 3
#define NBOTJETS_BINS 3
#define MET_BINS 4
#define MT2_BINS 3
//4 NTOP NBOT bins with all MET MT2 bins, 2 with only MET, 3 no MET and MT2: 4*12+2*4+3 
#define NSEARCH_BINS 59

const double ntopbins_edge[NTOPJETS_BINS+1] = {1,2,3,4};
const double nbotbins_edge[NBOTJETS_BINS+1] = {1,2,3,4};
const double metbins_edge[MET_BINS+1] = {200.0,300.0,400.0,500.0,600.0};
const double mt2bins_edge[MT2_BINS+1] = {200.0,300.0,400.0,500.0};

int Set_ntopjetsbin_number(
		                       int ntopjets
							  					)
{   
	int ntopjetsbin_num = -1;

	for(int i=0;i<NTOPJETS_BINS;i++)
  {
    if(i!=NTOPJETS_BINS-1)
    {
      if(ntopjets >= ntopbins_edge[i] && ntopjets < ntopbins_edge[i+1]){ ntopjetsbin_num = i; return ntopjetsbin_num; }
    }
    else
    {
      if(ntopjets >= ntopbins_edge[i]){ ntopjetsbin_num = i; return ntopjetsbin_num; }
    }
  }
  return ntopjetsbin_num;	
}

int Set_nbotjetsbin_number(
		                       int nbotjets
							  			    )
{
	int nbotjetsbin_num = -1;
 
  for(int i=0;i<NBOTJETS_BINS;i++)
  {
    if(i!=NBOTJETS_BINS-1)
    {
      if(nbotjets >= nbotbins_edge[i] && nbotjets < nbotbins_edge[i+1]){ nbotjetsbin_num = i; return nbotjetsbin_num; }
    }
    else
    {
      if(nbotjets >= nbotbins_edge[i]){ nbotjetsbin_num = i; return nbotjetsbin_num; }
    }
  }
  return nbotjetsbin_num;
}

int Set_metbin_number(
                       double met
                     )
{
  int metbin_num = -1;

  for(int i=0;i<MET_BINS;i++)
  {
    if(i!=MET_BINS-1)
    {
      if(met >= metbins_edge[i] && met < metbins_edge[i+1]){ metbin_num = i; return metbin_num; }
    }
    else
    {
      if(met >= metbins_edge[i]){ metbin_num = i; return metbin_num; }
    }
  }
  return metbin_num;
}

int Set_mt2bin_number(
                       double mt2
                     )
{
  int mt2bin_num = -1;

  for(int i=0;i<MT2_BINS;i++)
  {
    if(i!=MT2_BINS-1)
    {
      if(mt2 >= mt2bins_edge[i] && mt2 < mt2bins_edge[i+1]){ mt2bin_num = i; return mt2bin_num; }
    }
    else
    {
      if(mt2 >= mt2bins_edge[i]){ mt2bin_num = i; return mt2bin_num; }
    }
  }
  return mt2bin_num;
}

