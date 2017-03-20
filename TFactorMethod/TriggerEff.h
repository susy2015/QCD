#include<iostream>
#include<vector>

class TriggerEff
{
 public:
  //2016 ICHEP
  double GetTriggerEff_HLT_HT300_MET100_2016ICHEP(bool isRealMET, double ht, double met);
  double GetTriggerEff_HLT_Mu45_eta2p1_2016ICHEP(double eta);
  //2017 Moriond
  double GetTriggerEff_HLT_PFMET100_PFMHT100_2017Moriond(bool isRealMET, double ht, double met);
  void SelfTest();
 private:
  //2016 ICHEP
  std::vector<double> trgeff_met_bin_edge_2016ICHEP = {0,25,50,75,100,125,150,175,200,275,400,1000};
  std::vector<double> trgeff_eta_bin_edge_2016ICHEP = {-2.6,-2.2,-1.8,-1.4,-1.0,-0.6,-0.2,0.2,0.6,1.0,1.4,1.8,2.2,2.6};
  std::vector<double> trgeff_realandfake_met_ht500to1000_2016ICHEP = {0.002,0.003,0.012,0.055,0.217,0.491,0.757,0.900,0.974,0.993,1.000};
  std::vector<double> trgeff_real_met_ht1000toInf_2016ICHEP        = {0.014,0.020,0.038,0.091,0.210,0.365,0.578,0.760,0.910,0.989,1.000};
  std::vector<double> trgeff_fake_met_ht1000toInf_2016ICHEP        = {0.003,0.006,0.020,0.062,0.172,0.360,0.547,0.634,0.794,0.900,0.987};
  int Get_met_id_2016ICHEP(double met);
  std::vector<double> trgeff_mu_eta_2016ICHEP = {0.016,0.68,0.787,0.866,0.902,0.892,0.927,0.892,0.911,0.864,0.808,0.652,0.026};
  int Get_eta_id_2016ICHEP(double eta);

  //2017 Moriond
  //std::vector<double> trgeff_met_bin_edge_2017Moriond = {0,25,50,75,100,125,150,175,200,275,400,600,1000};
  std::vector<double> trgeff_met_bin_edge_2017Moriond = {0,25,50,75,100,125,150,175,200,250,300,400,600,1000};

  //std::vector<double> trgeff_real_met_ht300to1000_2017Moriond = {0.002 ,0.004,0.011,0.042,0.147,0.370,0.644,0.827,0.939,0.988,0.993,1.000};
  //std::vector<double> trgeff_fake_met_ht300to1000_2017Moriond = {0.0005,0.001,0.003,0.015,0.082,0.279,0.547,0.763,0.899,0.955,0.981,1.000};
  std::vector<double> trgeff_real_met_ht300to1000_2017Moriond = {0.001209891,0.002876833,0.008802817,0.03520886,0.1361878,0.3607832,0.6448758,0.826766,0.9329029,0.9809763,0.9947522,0.9975,1};
  std::vector<double> trgeff_fake_met_ht300to1000_2017Moriond = {0.09604437,0.1554465,0.2832484,0.4158014,0.5571772,0.6892371,0.789461,0.8659164,0.9236358,0.9532932,0.9669331,0.9864699,1};

  //std::vector<double> trgeff_real_met_ht1000toInf_2017Moriond = {0.024 ,0.032,0.047,0.076,0.160,0.287,0.473,0.680,0.858,0.958,0.987,0.980};
  //std::vector<double> trgeff_fake_met_ht1000toInf_2017Moriond = {0.017 ,0.024,0.031,0.068,0.122,0.261,0.391,0.582,0.768,0.886,0.941,0.963};
  std::vector<double> trgeff_real_met_ht1000toInf_2017Moriond = {0.02359347,0.03127875,0.03006012,0.09137709,0.1659919,0.2994924,0.6168582,0.7489177,0.8861538,0.9675676,0.9540816,0.9931034,1};
  std::vector<double> trgeff_fake_met_ht1000toInf_2017Moriond = {0.2398411,0.3132035,0.4033426,0.4960379,0.5805862,0.6688697,0.7470666,0.8121438,0.8638827,0.9100542,0.9325248,0.9620831,0.986631};

  int Get_met_id_2017Moriond(double met);
};
