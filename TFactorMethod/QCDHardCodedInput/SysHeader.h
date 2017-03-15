//Printing SysHeader...
  const double head_QCD_Data_CS[84] = {1315.000000,123.000000,27.000000,13.000000,11.000000,374.000000,29.000000,9.000000,11.000000,191.000000,45.000000,1.000000,2.000000,6.000000,20.000000,8.000000,6.000000,1.000000,3.000000,1.000000,6.000000,428.000000,48.000000,7.000000,3.000000,6.000000,97.000000,5.000000,2.000000,0.000000,28.000000,5.000000,4.000000,1.000000,1.000000,1.000000,0.000000,29.000000,7.000000,2.000000,0.000000,22.000000,11.000000,2.000000,0.000000,22.000000,9.000000,1.000000,82.000000,17.000000,6.000000,1.000000,23.000000,4.000000,6.000000,11.000000,5.000000,3.000000,42.000000,11.000000,4.000000,0.000000,6.000000,4.000000,1.000000,12.000000,0.000000,0.000000,1.000000,1.000000,5.000000,0.000000,1.000000,2.000000,2.000000,7.000000,2.000000,1.000000,1.000000,0.000000,2.000000,0.000000,2.000000,0.000000};
  const double head_QCD_otherBG_CS[84] = {363.377365,49.483805,14.700472,7.302784,4.843757,131.176511,11.627084,4.986237,2.766853,55.094465,16.371144,2.954377,1.379099,1.990602,5.352899,5.713950,2.891890,0.628413,0.107787,0.871164,1.161100,182.244295,28.264339,9.032670,4.304637,1.685906,21.687524,2.439132,0.798097,0.325798,5.880077,4.644742,1.718354,0.385947,0.451064,0.507946,0.704870,20.744600,4.394029,1.179172,0.091975,10.579196,4.029571,1.513447,1.084614,2.961613,3.439900,1.711707,29.004969,8.291662,2.820617,1.407006,7.924453,2.252375,1.835426,2.902604,1.091919,0.355873,24.393136,6.946658,2.520767,1.110755,5.506763,1.788121,0.608956,3.219866,0.297917,0.306654,0.355493,0.635769,1.418557,0.192286,0.036951,2.683701,1.390087,1.703889,1.047656,0.363531,0.224038,0.187441,0.316196,0.126140,0.238531,0.000000};
  const double head_QCD_otherBG_sysup[84] = {0.014946,0.039373,0.068316,0.100488,0.113599,0.025209,0.078884,0.118052,0.160712,0.036433,0.065822,0.136761,0.190328,0.208572,0.120212,0.113350,0.150058,0.223282,0.318373,0.248444,0.257725,0.020897,0.053656,0.090363,0.136552,0.197591,0.062012,0.191634,0.320789,0.460509,0.121449,0.142474,0.223224,0.492716,0.359430,0.432524,0.444575,0.063249,0.141812,0.274218,0.754705,0.082210,0.134971,0.222690,0.267505,0.149101,0.152982,0.234877,0.049521,0.090446,0.159182,0.248022,0.094907,0.175993,0.225219,0.138636,0.273814,0.530784,0.053710,0.100480,0.175854,0.262928,0.116793,0.207651,0.319411,0.144135,0.412280,0.453641,0.436999,0.392736,0.217629,0.623556,0.500311,0.149642,0.217079,0.189655,0.248731,0.454540,0.496423,0.533994,0.417280,0.834554,0.485696,1.000000};
  const double head_QCD_otherBG_sysdn[84] = {0.014946,0.039373,0.068316,0.100488,0.113599,0.025209,0.078884,0.118052,0.160712,0.036433,0.065822,0.136761,0.190328,0.208572,0.120212,0.113350,0.150058,0.223282,0.318373,0.248444,0.257725,0.020897,0.053656,0.090363,0.136552,0.197591,0.062012,0.191634,0.320789,0.460509,0.121449,0.142474,0.223224,0.492716,0.359430,0.432524,0.444575,0.063249,0.141812,0.274218,0.754705,0.082210,0.134971,0.222690,0.267505,0.149101,0.152982,0.234877,0.049521,0.090446,0.159182,0.248022,0.094907,0.175993,0.225219,0.138636,0.273814,0.530784,0.053710,0.100480,0.175854,0.262928,0.116793,0.207651,0.319411,0.144135,0.412280,0.453641,0.436999,0.392736,0.217629,0.623556,0.500311,0.149642,0.217079,0.189655,0.248731,0.454540,0.496423,0.533994,0.417280,0.834554,0.485696,1.000000};
  const double head_QCD_TFactor[84] = {0.222734,0.131692,0.041726,0.041726,0.041726,0.222734,0.131692,0.041726,0.041726,0.013219,0.022248,0.007084,0.007084,0.013219,0.022248,0.007084,0.007084,0.007084,0.007084,0.007084,0.007084,0.222734,0.131692,0.041726,0.041726,0.041726,0.222734,0.131692,0.007084,0.007084,0.013219,0.022248,0.007084,0.007084,0.007084,0.007084,0.007084,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.222734,0.131692,0.041726,0.041726,0.222734,0.131692,0.041726,0.022248,0.007084,0.007084,0.222734,0.131692,0.041726,0.041726,0.222734,0.131692,0.041726,0.013219,0.007084,0.007084,0.013219,0.007084,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444,0.149444};
  const double head_QCD_TFactor_relative_err[84] = {0.343921,1.016240,4.369700,4.369700,4.369700,0.343921,1.016240,4.369700,4.369700,1.076460,0.911660,1.158919,1.158919,1.076460,0.911660,1.158919,1.158919,1.158919,1.158919,1.158919,1.158919,0.343921,1.016240,4.369700,4.369700,4.369700,0.343921,1.016240,1.158919,1.158919,1.076460,0.911660,1.158919,1.158919,1.158919,1.158919,1.158919,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.343921,1.016240,4.369700,4.369700,0.343921,1.016240,4.369700,0.911660,1.158919,1.158919,0.343921,1.016240,4.369700,4.369700,0.343921,1.016240,4.369700,1.076460,1.158919,1.158919,1.076460,1.158919,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076,0.744076};
  const double head_QCD_NonClosure_relative_err[84] = {0.304085,0.449392,0.434935,0.434935,0.432572,0.662980,1.035416,5.128221,0.487512,0.361645,0.368227,0.488849,0.488849,0.471209,0.756391,0.663625,0.663625,0.663625,5.017577,5.004489,5.004489,0.480509,1.008541,0.557046,0.557046,0.556071,2.737242,0.836085,0.592804,0.592804,0.586643,0.660612,0.668148,0.668148,5.029734,5.016678,5.016678,0.524013,0.568564,0.595169,0.857516,0.481538,0.713054,0.582136,0.848522,0.579090,2.303322,0.870871,0.904367,1.123603,1.122478,1.088487,0.507235,1.200915,1.698713,1.094571,1.202510,1.152315,0.585142,1.176703,1.175629,1.143328,1.293972,1.408306,1.651629,1.129723,1.168356,1.162987,1.269803,1.341304,1.156759,1.162905,1.179656,1.119425,1.328777,1.105627,1.128734,1.182639,0.686461,0.738162,0.769644,0.903431,0.786996,0.832476};
