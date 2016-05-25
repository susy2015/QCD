#include <iostream>
#include <vector>

class SBGeometry
{
 public:
  const static int NTOPBINS = 3;
  const static int NBOTBINS = 3;
  const int NMT2BINS[NTOPBINS*NBOTBINS] = {3,3,2,//top 1
                                           3,3,2,//top 2
                                           2,2,1};//top >=3
  const int NMETBINS[NTOPBINS*NBOTBINS] = {6,6,4,//top 1
                                           6,6,4,//top 2
                                           3,3,3};//top >=3
  const double ntopbins_edge[NTOPBINS+1] = {1,2,3,4};
  const double nbotbins_edge[NBOTBINS+1] = {1,2,3,4};
  const std::vector< std::vector<double> > mt2bins_edge = {
                                                           {200.0,300.0,400.0,500.0},//top 1 bot 1
                                                           {200.0,300.0,400.0,500.0},//top 1 bot 2
                                                           {200.0,300.0,500.0},//top 1 bot >=3
                                                           {200.0,300.0,400.0,500.0},//top 2 bot 1
                                                           {200.0,300.0,400.0,500.0},//top 2 bot 2
                                                           {200.0,300.0,500.0},//top 2 bot >=3
                                                           {200.0,300.0,500.0},//top >=3 bot 1
                                                           {200.0,300.0,500.0},//top >=3 bot 2
                                                           {200.0,600.0} //top >=3 bot>=3
                                                          };  
  const std::vector< std::vector<double> > metbins_edge = {
                                                           {200.0,250.0,350.0,450.0,550.0,700.0,1000.0},//top 1 bot 1
                                                           {200.0,250.0,350.0,450.0,550.0,700.0,1000.0},//top 1 bot 2
                                                           {200.0,250.0,350.0,450.0,600.0},//top 1 bot >=3
                                                           {200.0,250.0,350.0,450.0,550.0,700.0,1000.0},//top 2 bot 1
																													 {200.0,250.0,350.0,450.0,550.0,700.0,1000.0},//top 2 bot 2
                                                           {200.0,250.0,350.0,450.0,600.0},//top 1 bot >=3
                                                           {200.0,250.0,400.0,600.0},//top >=3 bot 1
                                                           {200.0,250.0,400.0,600.0},//top >=3 bot 2
                                                           {200.0,250.0,400.0,600.0} //top >=3 bot>=3
                                                          };
  bool SBSelfTest();
  int GetSBID(int ntop, int nbot, double mt2, double met);//from 0 to last
 private:
  int GetTopID(int ntop);
  int GetBotID(int nbot);
  int GetMT2ID(int topbotid, double mt2);
  int GetMETID(int topbotid, double met);
};

int SBGeometry::GetTopID(int ntop)
{  
  int topid = -1;

  for(int i=0;i<NTOPBINS;i++)
  { 
    if(i!=NTOPBINS-1)
    { 
      if(ntop >= ntopbins_edge[i] && ntop < ntopbins_edge[i+1]){ topid = i; return topid; }
    }
    else
    { 
      if(ntop >= ntopbins_edge[i]){ topid = i; return topid; }
    }
  }
  return topid;
}

int SBGeometry::GetBotID(int nbot)
{ 
  int botid = -1;
  
  for(int i=0;i<NBOTBINS;i++)
  { 
    if(i!=NBOTBINS-1)
    { 
      if(nbot >= nbotbins_edge[i] && nbot < nbotbins_edge[i+1]){ botid = i; return botid; }
    }
    else
    { 
      if(nbot >= nbotbins_edge[i]){ botid = i; return botid; }
    }
  }
  return botid;
}

int SBGeometry::GetMT2ID(int topbotid, double mt2)
{
  if(topbotid<0 || topbotid>=NTOPBINS*NBOTBINS) return -2;
  int mt2bin_num = -1;
  
  for(int i=0;i<NMT2BINS[topbotid];i++)
  {
    if(i!=NMT2BINS[topbotid]-1)
    {
      if(mt2 >= (mt2bins_edge.at(topbotid)).at(i) && mt2 < (mt2bins_edge.at(topbotid)).at(i+1)){ mt2bin_num = i; return mt2bin_num; }
    }
    else
    {
      if(mt2 >= (mt2bins_edge.at(topbotid)).at(i)){ mt2bin_num = i; return mt2bin_num; }
    }
  }
  return mt2bin_num;
}

int SBGeometry::GetMETID(int topbotid, double met)
{ 
  if(topbotid<0 || topbotid>=NTOPBINS*NBOTBINS) return -2;
  int metbin_num = -1;
  
  for(int i=0;i<NMETBINS[topbotid];i++)
  { 
    if(i!=NMETBINS[topbotid]-1)
    { 
      if(met >= (metbins_edge.at(topbotid)).at(i) && met < (metbins_edge.at(topbotid)).at(i+1)){ metbin_num = i; return metbin_num; }
    }
    else
    { 
      if(met >= (metbins_edge.at(topbotid)).at(i)){ metbin_num = i; return metbin_num; }
    }
  }
  return metbin_num;
}

bool SBGeometry::SBSelfTest()
{
  int nsb=0;
  for(int i=0;i<NTOPBINS*NBOTBINS;i++){ nsb+=NMETBINS[i]*NMT2BINS[i]; }
  std::cout << "Total number of search bin: " << nsb << std::endl;

  bool isgoodSB=true;
  for(int i=0;i<NTOPBINS*NBOTBINS;i++)
  {
    if(NMT2BINS[i]!=(mt2bins_edge.at(i)).size()-1) {isgoodSB = false; std::cout << "Bad SB Def on MT2:" << i << std::endl; return isgoodSB;}
    if(NMETBINS[i]!=(metbins_edge.at(i)).size()-1) {isgoodSB = false; std::cout << "Bad SB Def on MET:" << i << std::endl; return isgoodSB;}
  }
  return isgoodSB;
}

int SBGeometry::GetSBID(int ntop, int nbot, double mt2, double met)
{
  int sbid = -1;
  int topid = -1, botid = -1, metid = -1, mt2id = -1;
  topid=GetTopID(ntop);
  botid=GetBotID(nbot);
  int topbotid = -1;
  (topid>=0 && botid >=0) ? topbotid = topid*NBOTBINS + botid : topbotid = -1; 
  if(topbotid<0 || topid<0 || botid<0) return -1;

  int sbbase = 0;
  if(topbotid!=0)
  {
    for(int i=0;i<topbotid;i++){ sbbase+=NMT2BINS[i]*NMETBINS[i]; }
  }

  mt2id=GetMT2ID(topbotid, mt2);
  metid=GetMETID(topbotid, met);
  if(mt2id<0 || metid<0) return -1;
  sbid = sbbase + mt2id*NMETBINS[topbotid] + metid;

  std::cout << topid << "," << botid <<"," << mt2id << ","<< metid << ",SBBase:" << sbbase << std::endl;
  return sbid;
}
