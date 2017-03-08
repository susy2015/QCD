#include "LLHadTauFactors.h"

void LLHadTauFactors::NumbertoTFactor()
{
  //LLHadTau Effs calculation in each search bin
  for(int i = 0 ; i < NSEARCH_BINS ; i++)
  {
    dphi_ll_singleMu_Eff_sb[i] = SR_dphi_ll_MC_sb[i]/CR_dphi_ll_singleMu_MC_sb[i];
    dphi_ll_singleEl_Eff_sb[i] = SR_dphi_ll_MC_sb[i]/CR_dphi_ll_singleEl_MC_sb[i];
    invdphi_ll_singleMu_Eff_sb[i] = SR_invdphi_ll_MC_sb[i]/CR_invdphi_ll_singleMu_MC_sb[i];
    invdphi_ll_singleEl_Eff_sb[i] = SR_invdphi_ll_MC_sb[i]/CR_invdphi_ll_singleEl_MC_sb[i];

    dphi_hadtau_singleMu_Eff_sb[i] = SR_dphi_hadtau_MC_sb[i]/CR_dphi_hadtau_singleMu_MC_sb[i];
    dphi_hadtau_singleEl_Eff_sb[i] = SR_dphi_hadtau_MC_sb[i]/CR_dphi_hadtau_singleEl_MC_sb[i];
    invdphi_hadtau_singleMu_Eff_sb[i] = SR_invdphi_hadtau_MC_sb[i]/CR_invdphi_hadtau_singleMu_MC_sb[i];
    invdphi_hadtau_singleEl_Eff_sb[i] = SR_invdphi_hadtau_MC_sb[i]/CR_invdphi_hadtau_singleEl_MC_sb[i];
  }

  return ;
}

void LLHadTauFactors::printInfo()
{
  std::cout << "LLHadTau MC in Search Bins: " << std::endl;
  for( int i = 0 ; i < NSEARCH_BINS ; i++ )
  {
    std::cout << "Search Bin Id:" << i << "; Eff dphi ll Mu: " << dphi_ll_singleMu_Eff_sb[i] << "; Eff dphi ll El: " << dphi_ll_singleEl_Eff_sb[i] << std::endl;
    std::cout << "Search Bin Id:" << i << "; Eff dphi hadtau Mu: " << dphi_hadtau_singleMu_Eff_sb[i] << "; Eff dphi hadtau El: " << dphi_hadtau_singleEl_Eff_sb[i] << std::endl;
  
    std::cout << "Search Bin Id:" << i << "; Eff invdphi ll Mu: " << invdphi_ll_singleMu_Eff_sb[i] << "; Eff invdphi ll El: " << invdphi_ll_singleEl_Eff_sb[i] << std::endl;
    std::cout << "Search Bin Id:" << i << "; Eff invdphi hadtau Mu: " << invdphi_hadtau_singleMu_Eff_sb[i] << "; Eff invdphi hadtau El: " << invdphi_hadtau_singleEl_Eff_sb[i] << std::endl;
  }
  return ;
}
