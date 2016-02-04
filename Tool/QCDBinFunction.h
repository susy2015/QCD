#define MET_BINS 3
//#define NBJETS_BINS 2
#define MT2_BINS 2
#define QCD_BINS 5
#define NSEARCH_BINS 45

const double metbins_edge[MET_BINS+1] = {175.0,200.0,350.0,650.0};
const double mt2bins_edge[MT2_BINS+1] = {200.0,300,500.0};

int Set_metbin_number(
                       double met
                     )
{
  int metbin_num = -1;

  if(met >= 175 && met < 200)
  {
    metbin_num = 0;
  }
  else if(met >= 200 && met < 350)
  {
    metbin_num = 1;
  }
  //else if(met >= 300 && met < 400)
  //{
    //metbin_num = 2;
  //}
  else if(met >= 350)
  {
    metbin_num = 2;
  }

  return metbin_num;
}

int Set_nbjetsbin_number(
                          int nbjets
                        )
{
  int nbjetsbin_num;

  if( nbjets == 1 )
  {
    nbjetsbin_num = 0;
  }
  else if( nbjets >= 2 )
  {
    nbjetsbin_num = 1;
  }

  return nbjetsbin_num;
}


int Set_mt2bin_number(
                       double mt2
                     )
{
  int mt2bin_num = -1;

  //return 0;  

  if(mt2 >= 200 && mt2 < 300)
  {
    mt2bin_num = 0;
  }
  //else if(mt2 >= 300 && mt2 < 400) 
  //{
    //mt2bin_num = 1;
  //}
  else
  {
    mt2bin_num = 1;
  }

  return mt2bin_num;
}

