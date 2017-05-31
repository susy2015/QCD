#include <string>
#include <iostream>
#include <vector>
#include <fstream>

// Top Tagger
#include "TopTagger/TopTagger/include/TopTagger.h"
#include "TopTagger/TopTagger/include/TopTaggerResults.h"
#include "TopTagger/TopTagger/include/TopTaggerUtilities.h"

#include "SusyAnaTools/TopTagger/interface/Type3TopTagger.h"
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

class EventInfo
{
 public:
  std::vector<int> run;
  std::vector<int> lumi;
  std::vector<int> event;
  
  bool isData;
  std::string OutTxtName="";
  void EventTxtProducer();
};

void EventInfo::EventTxtProducer()
{
  std::cout << "Output File Name: " << OutTxtName << std::endl;
  std::ofstream outfile;
  outfile.open (OutTxtName.c_str());
  for (int i=0;i<run.size();i++)
  {
    outfile << run.at(i) << ":" << lumi.at(i) << ":" << event.at(i) << "\n";
  }
  outfile.close();
  return ;
}
