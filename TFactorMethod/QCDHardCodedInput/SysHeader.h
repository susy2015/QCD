//Printing SysHeader...
  const double head_QCD_Data_CS[84] = {1315.000000,123.000000,27.000000,13.000000,11.000000,374.000000,29.000000,9.000000,11.000000,191.000000,45.000000,1.000000,2.000000,6.000000,20.000000,8.000000,6.000000,1.000000,3.000000,1.000000,6.000000,428.000000,48.000000,7.000000,3.000000,6.000000,97.000000,5.000000,2.000000,0.000000,28.000000,5.000000,4.000000,1.000000,1.000000,1.000000,0.000000,29.000000,7.000000,2.000000,0.000000,22.000000,11.000000,2.000000,0.000000,22.000000,9.000000,1.000000,82.000000,17.000000,6.000000,1.000000,23.000000,4.000000,6.000000,11.000000,5.000000,3.000000,42.000000,11.000000,4.000000,0.000000,6.000000,4.000000,1.000000,12.000000,0.000000,0.000000,1.000000,1.000000,5.000000,0.000000,1.000000,2.000000,2.000000,7.000000,2.000000,1.000000,1.000000,0.000000,2.000000,0.000000,2.000000,0.000000};
  const double head_QCD_otherBG_CS[84] = {352.796518,47.740397,14.115211,6.849693,4.534297,125.265306,11.013703,4.732450,2.625584,54.343932,15.152429,2.953928,1.287934,2.168373,5.000935,5.487166,2.627772,0.584656,0.229789,0.814618,1.203846,177.805671,27.449280,8.709736,4.157265,1.596244,21.257100,2.486602,0.777613,0.312567,5.598017,4.379005,1.747086,0.370844,0.428623,0.461235,0.655001,20.011256,4.209974,1.121317,0.089238,10.306865,4.058144,1.462291,1.020825,3.300975,3.322576,1.566686,28.342780,7.967303,2.841008,1.498801,7.982075,2.167270,1.769203,3.071884,1.200285,0.344440,23.880131,6.676286,2.448683,1.075934,5.353306,1.737489,0.594619,3.552691,0.289050,0.294606,0.759923,0.608241,1.377377,0.186590,0.038883,2.597175,1.350982,1.652592,1.094816,0.351355,0.212630,0.183049,0.302481,0.121593,0.228956,0.000000};
  const double head_QCD_otherBG_sysup[84] = {0.015271,0.040329,0.070111,0.103610,0.117776,0.025911,0.081938,0.120946,0.165414,0.037784,0.069265,0.153040,0.197136,0.211227,0.124981,0.117952,0.158878,0.228100,0.645236,0.257190,0.273259,0.021262,0.054316,0.091641,0.138284,0.202875,0.063624,0.193755,0.323623,0.471928,0.125827,0.147373,0.231270,0.503351,0.368213,0.460473,0.466881,0.064008,0.144813,0.280462,0.757618,0.083330,0.140606,0.224730,0.276211,0.155029,0.154828,0.245962,0.050220,0.092043,0.164034,0.251458,0.096884,0.179084,0.229427,0.144848,0.276922,0.537901,0.054555,0.102049,0.177841,0.265506,0.118020,0.209808,0.318397,0.149019,0.415749,0.460779,0.403999,0.402780,0.219878,0.631092,0.500575,0.151813,0.219001,0.191802,0.263556,0.461701,0.518806,0.536777,0.427148,0.854242,0.495424,1.000000};
  const double head_QCD_otherBG_sysdn[84] = {0.015271,0.040329,0.070111,0.103610,0.117776,0.025911,0.081938,0.120946,0.165414,0.037784,0.069265,0.153040,0.197136,0.211227,0.124981,0.117952,0.158878,0.228100,0.645236,0.257190,0.273259,0.021262,0.054316,0.091641,0.138284,0.202875,0.063624,0.193755,0.323623,0.471928,0.125827,0.147373,0.231270,0.503351,0.368213,0.460473,0.466881,0.064008,0.144813,0.280462,0.757618,0.083330,0.140606,0.224730,0.276211,0.155029,0.154828,0.245962,0.050220,0.092043,0.164034,0.251458,0.096884,0.179084,0.229427,0.144848,0.276922,0.537901,0.054555,0.102049,0.177841,0.265506,0.118020,0.209808,0.318397,0.149019,0.415749,0.460779,0.403999,0.402780,0.219878,0.631092,0.500575,0.151813,0.219001,0.191802,0.263556,0.461701,0.518806,0.536777,0.427148,0.854242,0.495424,1.000000};
  const double head_QCD_TFactor[84] = {0.199119,0.117730,0.037303,0.037303,0.037303,0.199119,0.117730,0.037303,0.037303,0.011971,0.020147,0.006415,0.006415,0.011971,0.020147,0.006415,0.006415,0.006415,0.006415,0.006415,0.006415,0.199119,0.117730,0.037303,0.037303,0.037303,0.199119,0.117730,0.006415,0.006415,0.011971,0.020147,0.006415,0.006415,0.006415,0.006415,0.006415,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.199119,0.117730,0.037303,0.037303,0.199119,0.117730,0.037303,0.020147,0.006415,0.006415,0.199119,0.117730,0.037303,0.037303,0.199119,0.117730,0.037303,0.011971,0.006415,0.006415,0.011971,0.006415,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535,0.114535};
  const double head_QCD_TFactor_relative_err[84] = {0.329439,0.962922,4.097763,4.097763,4.097763,0.329439,0.962922,4.097763,4.097763,1.076460,0.986698,1.158919,1.158919,1.076460,0.986698,1.158919,1.158919,1.158919,1.158919,1.158919,1.158919,0.329439,0.962922,4.097763,4.097763,4.097763,0.329439,0.962922,1.158919,1.158919,1.076460,0.986698,1.158919,1.158919,1.158919,1.158919,1.158919,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.329439,0.962922,4.097763,4.097763,0.329439,0.962922,4.097763,0.986698,1.158919,1.158919,0.329439,0.962922,4.097763,4.097763,0.329439,0.962922,4.097763,1.076460,1.158919,1.158919,1.076460,1.158919,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098,0.649098};
  const double head_QCD_NTopFactor[84] = {1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,1.739910,2.057080,2.057080,2.057080,2.057080,2.057080,2.057080};
  const double head_QCD_NTopFactor_relative_err[84] = {0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,0.248585,1.410869,1.410869,1.410869,1.410869,1.410869,1.410869};
  const double head_QCD_NonClosure_relative_err[84] = {0.304085,0.449392,0.434935,0.434935,0.432572,0.662980,1.035416,5.128221,0.487512,0.361645,0.368227,0.488849,0.488849,0.471209,0.756391,0.663625,0.663625,0.663625,5.017577,5.004489,5.004489,0.480509,1.008541,0.557046,0.557046,0.556071,2.737242,0.836085,0.592804,0.592804,0.586643,0.660612,0.668148,0.668148,5.029734,5.016678,5.016678,0.524013,0.568564,0.595169,0.857516,0.481538,0.713054,0.582136,0.848522,0.579090,2.303322,0.870871,0.904367,1.123603,1.122478,1.088487,0.507235,1.200915,1.698713,1.094571,1.202510,1.152315,0.585142,1.176703,1.175629,1.143328,1.293972,1.408306,1.651629,1.129723,1.168356,1.162987,1.269803,1.341304,1.156759,1.162905,1.179656,1.119425,1.328777,1.105627,1.128734,1.182639,0.686461,0.738162,0.769644,0.903431,0.786996,0.832476};
