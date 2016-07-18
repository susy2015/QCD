//Printing SysHeader...
  const double head_QCD_Data_CS[59] = {816.000000,70.000000,5.000000,1.000000,101.000000,19.000000,1.000000,0.000000,18.000000,27.000000,6.000000,4.000000,278.000000,28.000000,4.000000,0.000000,29.000000,0.000000,0.000000,1.000000,13.000000,0.000000,0.000000,58.000000,11.000000,0.000000,8.000000,2.000000,228.000000,13.000000,4.000000,0.000000,41.000000,8.000000,0.000000,1.000000,9.000000,10.000000,1.000000,2.000000,78.000000,10.000000,0.000000,16.000000,1.000000,0.000000,3.000000,3.000000,1.000000,12.000000,1.000000,4.000000,2.000000,10.000000,0.000000,3.000000,0.000000,0.000000,2.000000};
  const double head_QCD_otherBG_CS[59] = {146.301348,21.741818,2.931185,0.508817,14.964377,5.070901,1.096271,0.218538,2.035821,2.967380,1.134432,0.784848,112.755680,16.510969,2.098398,1.120984,5.156766,1.473081,0.362047,0.090251,2.900041,0.415710,0.168751,23.037935,2.405610,0.941445,1.321126,0.907333,59.151456,6.238190,2.123521,1.482439,5.386226,0.630033,0.212414,0.257476,3.242832,1.156132,0.980265,0.187860,32.864297,4.969636,1.588080,5.968340,4.056329,0.228988,0.487232,1.160946,2.256128,4.977975,2.499092,2.847207,0.616012,0.485723,0.358111,1.291979,0.089001,0.001427,0.004166};
  const double head_QCD_otherBG_sysup[59] = {0.057571,0.121711,0.225748,0.254399,0.133803,0.196443,0.343609,0.232746,0.311836,0.229900,0.327956,0.280063,0.064905,0.193667,0.322668,0.508241,0.199986,0.289802,0.493191,0.395637,0.368971,0.642929,0.258041,0.171820,0.308612,0.504199,0.360231,0.404088,0.084701,0.181552,0.343606,0.691532,0.210804,0.285721,0.464959,0.671877,0.627825,0.325665,0.456502,0.352629,0.112482,0.257149,0.471974,0.268335,0.405186,0.610373,0.488333,0.441721,0.501947,0.226250,0.600127,0.423777,0.522843,0.542820,0.483467,0.364354,0.408287,10.902027,0.940694};
  const double head_QCD_otherBG_sysdn[59] = {0.057607,0.121077,0.225056,0.251029,0.133772,0.196788,0.343609,0.236140,0.310919,0.230031,0.328111,0.280063,0.064860,0.193612,0.322162,0.502180,0.200245,0.289802,0.493191,0.395637,0.368971,0.642929,0.260142,0.171609,0.301157,0.501277,0.357373,0.404564,0.084491,0.181728,0.343977,0.691394,0.210760,0.285721,0.464959,0.671877,0.627793,0.325665,0.456271,0.352629,0.112470,0.257094,0.471519,0.268297,0.405108,0.608825,0.488333,0.442043,0.499719,0.225746,0.601263,0.424876,0.525658,0.542820,0.483467,0.364354,0.408287,10.902027,0.940694};
  const double head_QCD_TFactor[59] = {0.070142,0.069063,0.138523,0.138523,0.123505,0.289512,0.189574,0.189574,0.123505,0.289512,0.189574,0.189574,0.070142,0.069063,0.138523,0.138523,0.123505,0.289512,0.189574,0.189574,0.289512,0.189574,0.189574,0.070142,0.069063,0.138523,0.123505,0.289512,0.070142,0.069063,0.138523,0.138523,0.123505,0.289512,0.189574,0.189574,0.123505,0.289512,0.189574,0.189574,0.070142,0.069063,0.138523,0.123505,0.289512,0.189574,0.123505,0.289512,0.189574,0.070142,0.069063,0.123505,0.189574,0.070142,0.069063,0.070142,0.069063,0.070142,0.138523};
  const double head_QCD_TFactor_relative_err[59] = {0.186152,0.412967,0.761473,0.761473,0.361788,0.554775,0.493236,0.493236,0.361788,0.554775,0.493236,0.493236,0.186152,0.412967,0.761473,0.761473,0.361788,0.554775,0.493236,0.493236,0.554775,0.493236,0.493236,0.186152,0.412967,0.761473,0.361788,0.554775,0.186152,0.412967,0.761473,0.761473,0.361788,0.554775,0.493236,0.493236,0.361788,0.554775,0.493236,0.493236,0.186152,0.412967,0.761473,0.361788,0.554775,0.493236,0.361788,0.554775,0.493236,0.186152,0.412967,0.361788,0.493236,0.186152,0.412967,0.186152,0.412967,0.186152,0.761473};
  const double head_QCD_NonClosure_relative_err[59] = {0.172329,0.531587,1.693869,1.693869,0.386720,1.321157,2.801497,2.801497,0.474006,0.887237,1.024060,1.024060,0.403566,0.955924,0.832955,0.832955,0.935615,0.529358,0.529358,0.529358,0.554285,0.554285,0.554285,0.384897,8.308829,8.308829,8.308829,8.308829,0.442970,0.888746,0.888746,0.888746,0.569465,0.581369,0.581369,0.581369,0.534938,0.814590,1.017787,1.017787,0.321739,4.180777,4.180777,0.587695,0.587695,0.587695,0.551221,0.723420,4.103753,0.401040,1.133106,0.770427,0.770427,0.957642,0.676522,1.325801,1.325801,3.730343,3.730343};
