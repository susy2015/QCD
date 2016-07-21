#include "TriggerEff.h"

double TriggerEff::GetTriggerEff_HLT_HT300_MET100(bool isRealMET, double ht, double met)
{
  int id = Get_met_id( met );

  if(ht>500 && ht<1000)
  {
    if( id>=0 && id < trgeff_realandfake_met_ht500to1000.size() ) return trgeff_realandfake_met_ht500to1000.at(id);
    else if( id>=trgeff_realandfake_met_ht500to1000.size() ) return 1;
    else{ std::cout << "Invalid MET, please check!!" << std::endl; return 0; }
  }
  else if(ht>1000)
  {
    if(isRealMET)
    {
      if( id>=0 && id < trgeff_real_met_ht1000toInf.size() ) return trgeff_real_met_ht1000toInf.at(id);
      else if( id>=trgeff_real_met_ht1000toInf.size() ) return 1;
      else{ std::cout << "Invalid MET, please check!!" << std::endl; return 0; }
    }
    else
    {
      if( id>=0 && id < trgeff_fake_met_ht1000toInf.size() ) return trgeff_fake_met_ht1000toInf.at(id);
      else if( id>=trgeff_fake_met_ht1000toInf.size() ) return 1;
      else{ std::cout << "Invalid MET, please check!!" << std::endl; return 0; }
    }
  }
  else
  {
    std::cout << "HT lower than 500 GeV ??!! Please Check!! " << std::endl;
    return 0;
  }
}

double TriggerEff::GetTriggerEff_HLT_Mu45_eta2p1(double eta)
{
  int id = Get_eta_id( eta );
  if( id>=0 && id < trgeff_mu_eta.size() ) return trgeff_mu_eta.at(id);
  else{ std::cout << "Invalid Mu Eta, please check!!" << std::endl; return 0; }
}

void TriggerEff::SelfTest()
{
  std::cout << "Testing HLT_HT300_MET100 Effs ..." << std::endl;
  for(auto i=0;i<trgeff_met_bin_edge.size();i++)
  {
    double thismet = trgeff_met_bin_edge.at(i)+5;
    double realandfakemeteff_lowht = GetTriggerEff_HLT_HT300_MET100(  true,  600, thismet );
    double realmeteff_highht       = GetTriggerEff_HLT_HT300_MET100(  true, 1200, thismet );
    double fakemeteff_highht       = GetTriggerEff_HLT_HT300_MET100( false, 1200, thismet );
    std::cout << "Test MET value: " << thismet << ", RealAndFakeMETEff_LowHT: " << realandfakemeteff_lowht << ", RealMETEff_HighHT: " << realmeteff_highht << ", FakeMETEff_HighHT: " << fakemeteff_highht << std::endl;
  }

  std::cout << "Testing HLT_Mu45_eta2p1 Effs ..." << std::endl;
  for(auto i=0;i<trgeff_eta_bin_edge.size();i++)
  { 
    double thiseta = trgeff_eta_bin_edge.at(i)+0.2;
    double thisetaeff = GetTriggerEff_HLT_Mu45_eta2p1( thiseta );
    std::cout << "Test ETA value: " << thiseta << ", Trigger Eff HLT_Mu45_eta2p1: " << thisetaeff << std::endl;
  }

  return;
}

int TriggerEff::Get_met_id(double met)
{
  if(met<trgeff_met_bin_edge.at(0)) return -1;
  for(auto i=0;i<trgeff_met_bin_edge.size();i++)
  {
    if(i!=trgeff_met_bin_edge.size()-1)
    {
      if(met > trgeff_met_bin_edge.at(i) && met < trgeff_met_bin_edge.at(i+1)) return i;
      else continue;
    }
    else
    {
      return (trgeff_met_bin_edge.size()+1);
    }
  }
  return -1;
}

int TriggerEff::Get_eta_id(double eta)
{
  if(eta<trgeff_eta_bin_edge.at(0) || eta > trgeff_eta_bin_edge.at(trgeff_eta_bin_edge.size()-1) ) return -1;
  for(auto i=0;i<trgeff_eta_bin_edge.size();i++)
  {
    if(i!=trgeff_eta_bin_edge.size()-1)
    {
      if(eta > trgeff_eta_bin_edge.at(i) && eta < trgeff_eta_bin_edge.at(i+1)) return i;
      else continue;
    }
    else
    {
      return -1;
    }
  }
  return -1;
}
