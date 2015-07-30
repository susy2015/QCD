#define MET_BINS 3
#define NBJETS_BINS 2
#define MT2_BINS 2
#define QCD_BINS 7
#define NSEARCH_BINS 64

int Set_metbin_number(
                       double met
                     )
{
  int metbin_num;

  if(met >= 175 && met < 200)
  {
    metbin_num = 0;
  }
  else if(met >= 200 && met < 300)
  {
    metbin_num = 1;
  }
  //else if(met >= 250 && met < 350)
  //{
  //  metbin_num = 2;
  //}
  else if(met >= 300)
  {
    metbin_num = 2;
  }

  return metbin_num;
}

int Set_nbjetsbin_number(
                          int nbjets
                        )
{
  int nbjetsbin_num = 0;

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
  int mt2bin_num;

  if(mt2 < 200)
  {
    mt2bin_num = 0;
  }
  else if(mt2 >= 200)
  {
    mt2bin_num = 1;
  }

  return mt2bin_num;
}

