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
 private:
  bool ZeroContent();
  void EventTxtProducer();
 public:
  std::vector<unsigned int> run;
  std::vector<unsigned int> lumi;
  std::vector<unsigned long long int> event;
  
  bool isData;
  std::string EvtTxtName="";
  std::string AUXTxtName="";
  void ZSxrdcp(std::string d);
};

bool EventInfo::ZeroContent()
{
  bool zerocontent = false;
  if(run.size()==0){ zerocontent = true; }
  return zerocontent;
}

void EventInfo::EventTxtProducer()
{
  std::cout << "Output File Name: " << EvtTxtName << std::endl;
  std::ofstream outfile;
  outfile.open (EvtTxtName.c_str());
  for (int i=0;i<run.size();i++)
  {
    outfile << run.at(i) << ":" << lumi.at(i) << ":" << event.at(i) << "\n";
  }
  outfile.close();
  return ;
}

void EventInfo::ZSxrdcp(std::string d)
{
  if( ZeroContent() ){ return ; }
  else
  {
    EventTxtProducer();
    std::system(("xrdcp " + EvtTxtName + " " + d).c_str());
    std::system(("rm " + EvtTxtName).c_str());
    return ;
  }
  return ;
}
