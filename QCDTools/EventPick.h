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
  void EventTxtProducer(bool ExtInfo);
 public:
  std::vector<unsigned int> run;
  std::vector<unsigned int> lumi;
  std::vector<unsigned long long int> event;
  std::vector<std::array<double, 6>> eta, phi, pt;
  
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

void EventInfo::EventTxtProducer(bool ExtInfo)
{
  std::cout << "Output File Name: " << EvtTxtName << std::endl;
  std::ofstream outfile;
  outfile.open (EvtTxtName.c_str());
  for (int i=0;i<run.size();i++)
  {
    outfile << run.at(i) << ":" << lumi.at(i) << ":" << event.at(i) << "\n";
    if(ExtInfo)
    { 
      for(int j=0;j<6;j++)
      {
        outfile << j << "th jet eta: " << eta.at(i)[j] << ", phi: " << phi.at(i)[j] << ", pt: " << pt.at(i)[j] << "\n";
      }
    }
  }
  outfile.close();
  return ;
}

void EventInfo::ZSxrdcp(std::string d)
{
  if( ZeroContent() ){ return ; }
  else
  {
    //EventTxtProducer(false);
    EventTxtProducer(true);
    std::system(("xrdcp " + EvtTxtName + " " + d).c_str());
    std::system(("rm " + EvtTxtName).c_str());
    return ;
  }
  return ;
}
