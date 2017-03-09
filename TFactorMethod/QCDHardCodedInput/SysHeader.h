//Printing SysHeader...
  const double head_QCD_Data_CS[84] = {1315.000000,123.000000,27.000000,13.000000,11.000000,374.000000,29.000000,9.000000,11.000000,191.000000,45.000000,1.000000,2.000000,6.000000,20.000000,8.000000,6.000000,1.000000,3.000000,1.000000,6.000000,428.000000,48.000000,7.000000,3.000000,6.000000,97.000000,5.000000,2.000000,0.000000,28.000000,5.000000,4.000000,1.000000,1.000000,1.000000,0.000000,29.000000,7.000000,2.000000,0.000000,22.000000,11.000000,2.000000,0.000000,22.000000,9.000000,1.000000,82.000000,17.000000,6.000000,1.000000,23.000000,4.000000,6.000000,11.000000,5.000000,3.000000,42.000000,11.000000,4.000000,0.000000,6.000000,4.000000,1.000000,12.000000,0.000000,0.000000,1.000000,1.000000,5.000000,0.000000,1.000000,2.000000,2.000000,7.000000,2.000000,1.000000,1.000000,0.000000,2.000000,0.000000,2.000000,0.000000};
  const double head_QCD_otherBG_CS[84] = {365.228277,49.287766,14.545041,7.150660,4.700629,131.279854,11.455920,4.873297,2.703854,57.073722,16.054476,3.118073,1.310795,2.244967,5.245544,5.728872,2.763626,0.596754,0.232288,0.853898,1.269119,184.732108,28.312008,8.978889,4.285582,1.653257,22.148070,2.546124,0.792977,0.323267,5.970525,4.587261,1.820795,0.378277,0.442960,0.484821,0.689490,20.690546,4.373823,1.166174,0.091975,10.703568,4.205021,1.503897,1.068574,3.475062,3.430040,1.693246,29.277386,8.281393,2.940226,1.547802,8.271670,2.237415,1.826078,3.151840,1.233098,0.349165,24.679709,6.953748,2.520751,1.108137,5.507594,1.790132,0.611524,3.655179,0.297917,0.303179,0.783595,0.632741,1.418437,0.192303,0.038883,2.675395,1.392101,1.702760,1.182263,0.362442,0.220189,0.188012,0.312634,0.125569,0.236278,0.000000};
  const double head_QCD_otherBG_sysup[84] = {0.015079,0.039915,0.069502,0.102105,0.116153,0.025400,0.080713,0.120142,0.163592,0.036895,0.067335,0.148816,0.197059,0.207589,0.122148,0.115747,0.155063,0.229659,0.647588,0.251936,0.265319,0.020958,0.053824,0.090788,0.137021,0.200444,0.062503,0.193319,0.322568,0.464371,0.122081,0.143970,0.226317,0.501838,0.364167,0.448650,0.453173,0.063341,0.142318,0.276569,0.754705,0.082171,0.138367,0.223821,0.270108,0.151287,0.153351,0.236973,0.049657,0.090567,0.161459,0.248277,0.095691,0.176917,0.226228,0.144048,0.274316,0.539908,0.053858,0.100424,0.175860,0.263513,0.116948,0.207534,0.318304,0.147917,0.412280,0.458314,0.397991,0.394473,0.217701,0.623809,0.500575,0.150217,0.216903,0.189910,0.252818,0.456179,0.510082,0.533832,0.422778,0.839486,0.491035,1.000000};
  const double head_QCD_otherBG_sysdn[84] = {0.015079,0.039915,0.069502,0.102105,0.116153,0.025400,0.080713,0.120142,0.163592,0.036895,0.067335,0.148816,0.197059,0.207589,0.122148,0.115747,0.155063,0.229659,0.647588,0.251936,0.265319,0.020958,0.053824,0.090788,0.137021,0.200444,0.062503,0.193319,0.322568,0.464371,0.122081,0.143970,0.226317,0.501838,0.364167,0.448650,0.453173,0.063341,0.142318,0.276569,0.754705,0.082171,0.138367,0.223821,0.270108,0.151287,0.153351,0.236973,0.049657,0.090567,0.161459,0.248277,0.095691,0.176917,0.226228,0.144048,0.274316,0.539908,0.053858,0.100424,0.175860,0.263513,0.116948,0.207534,0.318304,0.147917,0.412280,0.458314,0.397991,0.394473,0.217701,0.623809,0.500575,0.150217,0.216903,0.189910,0.252818,0.456179,0.510082,0.533832,0.422778,0.839486,0.491035,1.000000};
  const double head_QCD_TFactor[84] = {0.191865,0.113441,0.035944,0.035944,0.035944,0.191865,0.113441,0.035944,0.035944,0.011876,0.019987,0.006364,0.006364,0.011876,0.019987,0.006364,0.006364,0.006364,0.006364,0.006364,0.006364,0.191865,0.113441,0.035944,0.035944,0.035944,0.191865,0.113441,0.006364,0.006364,0.011876,0.019987,0.006364,0.006364,0.006364,0.006364,0.006364,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.191865,0.113441,0.035944,0.035944,0.191865,0.113441,0.035944,0.019987,0.006364,0.006364,0.191865,0.113441,0.035944,0.035944,0.191865,0.113441,0.035944,0.011876,0.006364,0.006364,0.011876,0.006364,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873,0.109873};
  const double head_QCD_TFactor_relative_err[84] = {0.324356,0.944061,4.000857,4.000857,4.000857,0.324356,0.944061,4.000857,4.000857,1.076460,0.993196,1.158919,1.158919,1.076460,0.993196,1.158919,1.158919,1.158919,1.158919,1.158919,1.158919,0.324356,0.944061,4.000857,4.000857,4.000857,0.324356,0.944061,1.158919,1.158919,1.076460,0.993196,1.158919,1.158919,1.158919,1.158919,1.158919,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.324356,0.944061,4.000857,4.000857,0.324356,0.944061,4.000857,0.993196,1.158919,1.158919,0.324356,0.944061,4.000857,4.000857,0.324356,0.944061,4.000857,1.076460,1.158919,1.158919,1.076460,1.158919,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585,0.634585};
  const double head_QCD_NTopFactor[84] = {1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,2.057080,2.057080,2.057080,2.057080,2.057080,2.057080};
  const double head_QCD_NTopFactor_relative_err[84] = {0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,1.410869,1.410869,1.410869,1.410869,1.410869,1.410869};
  const double head_QCD_NonClosure_relative_err[84] = {0.304085,0.449392,0.434935,0.434935,0.432572,0.662980,1.035416,5.128221,0.487512,0.361645,0.368227,0.488849,0.488849,0.471209,0.756391,0.663625,0.663625,0.663625,5.017577,5.004489,5.004489,0.480509,1.008541,0.557046,0.557046,0.556071,2.737242,0.836085,0.592804,0.592804,0.586643,0.660612,0.668148,0.668148,5.029734,5.016678,5.016678,0.524013,0.568564,0.595169,0.857516,0.481538,0.713054,0.582136,0.848522,0.579090,2.303322,0.870871,0.904367,1.123603,1.122478,1.088487,0.507235,1.200915,1.698713,1.094571,1.202510,1.152315,0.585142,1.176703,1.175629,1.143328,1.293972,1.408306,1.651629,1.129723,1.168356,1.162987,1.269803,1.341304,1.156759,1.162905,1.179656,1.119425,1.328777,1.105627,1.128734,1.182639,0.686461,0.738162,0.769644,0.903431,0.786996,0.832476};
