#include "LLHadTauFactors.h"

void LLHadTauFactors::NumbertoTFactor()
{
  //LLHadTau Effs calculation in each search bin
  for(int i = 0 ; i < NSEARCH_BINS ; i++)
  {
    dphi_singleMu_Eff_sb[i] = SR_dphi_MC_sb[i]/CR_dphi_singleMu_MC_sb[i];
    dphi_singleEl_Eff_sb[i] = SR_dphi_MC_sb[i]/CR_dphi_singleEl_MC_sb[i];

    invdphi_singleMu_Eff_sb[i] = SR_invdphi_MC_sb[i]/CR_invdphi_singleMu_MC_sb[i];
    invdphi_singleEl_Eff_sb[i] = SR_invdphi_MC_sb[i]/CR_invdphi_singleEl_MC_sb[i];
  }

  return ;
}

void LLHadTauFactors::printInfo()
{
  std::cout << "LLHadTau MC in Search Bins: " << std::endl;
  for( int i = 0 ; i < NSEARCH_BINS ; i++ )
  {
    std::cout << "Search Bin Id:" << i << "; SR dphi: " << SR_dphi_MC_sb[i] << "; CR dphi Mu: " << CR_dphi_singleMu_MC_sb[i]  << "; CR dphi El: " << CR_dphi_singleEl_MC_sb[i] << "; Eff dphi Mu: " << dphi_singleMu_Eff_sb[i] << "; Eff dphi El: " << dphi_singleEl_Eff_sb[i] << std::endl;
   
    std::cout << "Search Bin Id:" << i << "; SR invdphi: " << SR_invdphi_MC_sb[i] << "; CR invdphi Mu: " << CR_invdphi_singleMu_MC_sb[i]  << "; CR invdphi El: " << CR_invdphi_singleEl_MC_sb[i] << "; Eff invdphi Mu: " << invdphi_singleMu_Eff_sb[i] << "; Eff invdphi El: " << invdphi_singleEl_Eff_sb[i] << std::endl;
  }
  return ;
}
