#include "TriggerEff.h"

double TriggerEff::GetTriggerEff_HLT_HT300_MET100_2016ICHEP(bool isRealMET, double ht, double met)
{
  int id = Get_met_id_2016ICHEP( met );

  if(ht>500 && ht<1000)
  {
    if( id>=0 && id < trgeff_realandfake_met_ht500to1000_2016ICHEP.size() ) return trgeff_realandfake_met_ht500to1000_2016ICHEP.at(id);
    else if( id>=trgeff_realandfake_met_ht500to1000_2016ICHEP.size() ) return 1;
    else{ std::cout << "Invalid MET, please check!!" << std::endl; return 0; }
  }
  else if(ht>1000)
  {
    if(isRealMET)
    {
      if( id>=0 && id < trgeff_real_met_ht1000toInf_2016ICHEP.size() ) return trgeff_real_met_ht1000toInf_2016ICHEP.at(id);
      else if( id>=trgeff_real_met_ht1000toInf_2016ICHEP.size() ) return 1;
      else{ std::cout << "Invalid MET, please check!!" << std::endl; return 0; }
    }
    else
    {
      if( id>=0 && id < trgeff_fake_met_ht1000toInf_2016ICHEP.size() ) return trgeff_fake_met_ht1000toInf_2016ICHEP.at(id);
      else if( id>=trgeff_fake_met_ht1000toInf_2016ICHEP.size() ) return 1;
      else{ std::cout << "Invalid MET, please check!!" << std::endl; return 0; }
    }
  }
  else
  {
    std::cout << "HT lower than 500 GeV ??!! Please Check!! " << std::endl;
    return 0;
  }
}

double TriggerEff::GetTriggerEff_HLT_Mu45_eta2p1_2016ICHEP(double eta)
{
  int id = Get_eta_id_2016ICHEP( eta );
  if( id>=0 && id < trgeff_mu_eta_2016ICHEP.size() ) return trgeff_mu_eta_2016ICHEP.at(id);
  else{ std::cout << "Invalid Mu Eta, please check!!" << std::endl; return 0; }
}

double TriggerEff::GetTriggerEff_HLT_PFMET100_PFMHT100_2017Moriond(bool isRealMET, double ht, double met)
{
  int id = Get_met_id_2017Moriond( met );

  if(ht>=300 && ht<1000)
  {
    if(isRealMET)
    {
      if( id>=0 && id < trgeff_real_met_ht300to1000_2017Moriond.size() ) return trgeff_real_met_ht300to1000_2017Moriond.at(id);
      else if( id>=trgeff_real_met_ht300to1000_2017Moriond.size() ) return 1;
      else{ std::cout << "Invalid MET, please check!!" << std::endl; return 0; }
    }
    else
    {
      if( id>=0 && id < trgeff_fake_met_ht300to1000_2017Moriond.size() ) return trgeff_fake_met_ht300to1000_2017Moriond.at(id);
      else if( id>=trgeff_fake_met_ht300to1000_2017Moriond.size() ) return 1;
      else{ std::cout << "Invalid MET, please check!!" << std::endl; return 0; }
    }
  }
  else if(ht>=1000)
  {
    if(isRealMET)
    {
      if( id>=0 && id < trgeff_real_met_ht1000toInf_2017Moriond.size() ) return trgeff_real_met_ht1000toInf_2017Moriond.at(id);
      else if( id>=trgeff_real_met_ht1000toInf_2017Moriond.size() ) return 1;
      else{ std::cout << "Invalid MET, please check!!" << std::endl; return 0; }
    }
    else
    {
      if( id>=0 && id < trgeff_fake_met_ht1000toInf_2017Moriond.size() ) return trgeff_fake_met_ht1000toInf_2017Moriond.at(id);
      else if( id>=trgeff_fake_met_ht1000toInf_2017Moriond.size() ) return 1;
      else{ std::cout << "Invalid MET, please check!!" << std::endl; return 0; }
    }
  }
  else
  {
    std::cout << "HT lower than 300 GeV ??!! Please Check!! " << std::endl;
    return 0;
  }
}

void TriggerEff::SelfTest()
{
  std::cout << "Testing HLT_HT300_MET100_2016ICHEP Effs ..." << std::endl;
  for(auto i=0;i<trgeff_met_bin_edge_2016ICHEP.size();i++)
  {
    double thismet = trgeff_met_bin_edge_2016ICHEP.at(i)+5;
    double realandfakemeteff_lowht = GetTriggerEff_HLT_HT300_MET100_2016ICHEP(  true,  600, thismet );
    double realmeteff_highht       = GetTriggerEff_HLT_HT300_MET100_2016ICHEP(  true, 1200, thismet );
    double fakemeteff_highht       = GetTriggerEff_HLT_HT300_MET100_2016ICHEP( false, 1200, thismet );
    std::cout << "Test MET value: " << thismet << ", RealAndFakeMETEff_LowHT: " << realandfakemeteff_lowht << ", RealMETEff_HighHT: " << realmeteff_highht << ", FakeMETEff_HighHT: " << fakemeteff_highht << std::endl;
  }

  std::cout << "Testing HLT_Mu45_eta2p1_2016ICHEP Effs ..." << std::endl;
  for(auto i=0;i<trgeff_eta_bin_edge_2016ICHEP.size();i++)
  { 
    double thiseta = trgeff_eta_bin_edge_2016ICHEP.at(i)+0.2;
    double thisetaeff = GetTriggerEff_HLT_Mu45_eta2p1_2016ICHEP( thiseta );
    std::cout << "Test ETA value: " << thiseta << ", Trigger Eff HLT_Mu45_eta2p1: " << thisetaeff << std::endl;
  }

  std::cout << "Testing HLT_PFMET100_PFMHT100_2017Moriond Effs ..." << std::endl;
  for(auto i=0;i<trgeff_met_bin_edge_2017Moriond.size();i++)
  {
    double thismet = trgeff_met_bin_edge_2017Moriond.at(i)+5;
    double realmeteff_lowht  = GetTriggerEff_HLT_PFMET100_PFMHT100_2017Moriond(  true,  400, thismet );
    double fakemeteff_lowht  = GetTriggerEff_HLT_PFMET100_PFMHT100_2017Moriond( false,  400, thismet );
    double realmeteff_highht = GetTriggerEff_HLT_PFMET100_PFMHT100_2017Moriond(  true, 1200, thismet );
    double fakemeteff_highht = GetTriggerEff_HLT_PFMET100_PFMHT100_2017Moriond( false, 1200, thismet );
    std::cout << "Test MET value: " << thismet << ", RealMETEff_LowHT: " << realmeteff_lowht << ", FakeMETEff_LowHT: " << fakemeteff_lowht << ", RealMETEff_HighHT: " << realmeteff_highht << ", FakeMETEff_HighHT: " << fakemeteff_highht << std::endl;
  }
  return;
}

int TriggerEff::Get_met_id_2016ICHEP(double met)
{
  if(met<trgeff_met_bin_edge_2016ICHEP.at(0)) return -1;
  for(auto i=0;i<trgeff_met_bin_edge_2016ICHEP.size();i++)
  {
    if(i!=trgeff_met_bin_edge_2016ICHEP.size()-1)
    {
      if(met >= trgeff_met_bin_edge_2016ICHEP.at(i) && met < trgeff_met_bin_edge_2016ICHEP.at(i+1)) return i;
      else continue;
    }
    else
    {
      return (trgeff_met_bin_edge_2016ICHEP.size()+1);
    }
  }
  return -1;
}

int TriggerEff::Get_eta_id_2016ICHEP(double eta)
{
  if(eta<trgeff_eta_bin_edge_2016ICHEP.at(0) || eta > trgeff_eta_bin_edge_2016ICHEP.at(trgeff_eta_bin_edge_2016ICHEP.size()-1) ) return -1;
  for(auto i=0;i<trgeff_eta_bin_edge_2016ICHEP.size();i++)
  {
    if(i!=trgeff_eta_bin_edge_2016ICHEP.size()-1)
    {
      if(eta >= trgeff_eta_bin_edge_2016ICHEP.at(i) && eta < trgeff_eta_bin_edge_2016ICHEP.at(i+1)) return i;
      else continue;
    }
    else
    {
      return -1;
    }
  }
  return -1;
}

int TriggerEff::Get_met_id_2017Moriond(double met)
{
  if(met<trgeff_met_bin_edge_2017Moriond.at(0)) return -1;
  for(auto i=0;i<trgeff_met_bin_edge_2017Moriond.size();i++)
  {
    if(i!=trgeff_met_bin_edge_2017Moriond.size()-1)
    {
      if(met >= trgeff_met_bin_edge_2017Moriond.at(i) && met < trgeff_met_bin_edge_2017Moriond.at(i+1)) return i;
      else continue;
    }
    else
    {
      return (trgeff_met_bin_edge_2017Moriond.size()+1);
    }
  }
  return -1;
}

