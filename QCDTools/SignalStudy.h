#include <string>
#include <iostream>
#include <vector>

#include "TLorentzVector.h"

#include "SusyAnaTools/Tools/NTupleReader.h"
#include "SusyAnaTools/Tools/baselineDef.h"

bool useNewTagger = true;
bool useLegacycfg = false;

size_t find_Nth
(
  const std::string & str ,   // where to work
  unsigned            N ,     // N'th ocurrence
  const std::string & find    // what to 'find'
)
{
  if ( 0==N ) { return std::string::npos; }
  size_t pos,from=0;
  unsigned i=0;
  while ( i<N )
  {
    pos=str.find(find,from);
    if ( std::string::npos == pos ) { break; }
    from = pos + 1; // from = pos + find.size();
    ++i;
  }
  return pos;
}

double GetPartonGenMET(std::vector<TLorentzVector> LVec)
{
  double genmet=0;
  if(LVec.size()==0) return 0;
  else
  {
    TLorentzVector thisLVec;
    for(int i=0; i<LVec.size(); i++)
    {
      thisLVec+=LVec.at(i);
    }
    genmet=thisLVec.Pt();
  }

  return genmet;
}
