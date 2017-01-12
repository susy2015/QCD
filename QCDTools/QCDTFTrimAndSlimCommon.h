#ifndef _QCDTFTrimAndSlimCommon_H_
#define _QCDTFTrimAndSlimCommon_H_

#include <string>
#include <iostream>
#include <vector>

#include "SusyAnaTools/Tools/NTupleReader.h"
#include "SusyAnaTools/Tools/baselineDef.h"

const double trigger_turn_on_met = 200;
const double cut_mtwmu = 100;
const double cut_mtwel = 100;
const int nth_slash_nametag_MC = 10;
const int nth_slash_nametag_Data = 10;

bool useNewTagger = true;
bool useLegacycfg = false;

inline size_t find_Nth
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
#endif
