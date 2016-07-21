#include<iostream>
#include<vector>

class TriggerEff
{
 public:
  double GetTriggerEff_HLT_HT300_MET100(bool isRealMET, double ht, double met);
  double GetTriggerEff_HLT_Mu45_eta2p1(double eta);
  void SelfTest();
 private:
  std::vector<double> trgeff_met_bin_edge = {0,25,50,75,100,125,150,175,200,275,400,1000};
  std::vector<double> trgeff_eta_bin_edge = {-2.6,-2.2,-1.8,-1.4,-1.0,-0.6,-0.2,0.2,0.6,1.0,1.4,1.8,2.2,2.6};

  std::vector<double> trgeff_realandfake_met_ht500to1000 = {0.002,0.003,0.012,0.055,0.217,0.491,0.757,0.900,0.974,0.993,1.000};
  std::vector<double> trgeff_real_met_ht1000toInf        = {0.014,0.020,0.038,0.091,0.210,0.365,0.578,0.760,0.910,0.989,1.000};
  std::vector<double> trgeff_fake_met_ht1000toInf        = {0.003,0.006,0.020,0.062,0.172,0.360,0.547,0.634,0.794,0.900,0.987};
  int Get_met_id(double met);

  std::vector<double> trgeff_mu_eta = {0.016,0.68,0.787,0.866,0.902,0.892,0.927,0.892,0.911,0.864,0.808,0.652,0.026};
  int Get_eta_id(double eta);
};
