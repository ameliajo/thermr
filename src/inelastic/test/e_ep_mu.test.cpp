#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "inelastic/e_ep_mu.h"
#include <range/v3/all.hpp>
#include "generalTools/testing.h"
#include <range/v3/all.hpp>


TEST_CASE( "main E E' mu function" ){
  int imax = 20, lat = 0, iinc = 2, lasym = 0;
  double tev = 2.5507297688e-2, tol = 2.0;
  std::vector<double> 
  alphas { 1.1, 2.2, 3.3, 4.5, 5.8 },
  betas { 0.1, 0.2, 1.3, 1.4, 2.5, 2.6, 3.7 },
  sab {-0.18259619, -0.30201347, -3.93654779, -3.98809174, -4.33545607, 
  -4.39515402, -5.88934921, -0.76225291, -0.81658341, -3.14161459, -3.30566186, 
  -3.90554652, -3.96233362, -5.23696660, -1.19182884, -1.23155471, -2.79610565, 
  -2.95633099, -3.74989225, -3.80837585, -4.93373911, -1.58342860, -1.61310713, 
  -2.71233943, -2.84291608, -3.69699590, -3.75199349, -4.77433858, -1.96121202, 
  -1.98720663, -2.78454600, -2.88531460, -3.71288120, -3.77142141, -4.71158392 };

  double az = 0.99917, sigma_b = 163.72792237, sigma_b2 = 0.0, teff = 0.120441926;
  int nbin = 2;
  std::vector<double> eVec, correctEnergies;
  std::vector<double> boundXsVec {sigma_b,sigma_b2};

  GIVEN( "temperature is reasonable (doesn't need scaling)" ){
    double temp = 296.0;

    WHEN( "small energies are considered" ){
      eVec = {1E-5, 1.78E-5, 2.5E-5, 3.5E-5, 5E-5, 7E-5, 1E-4, 1.26E-4, 1.6E-4, 2E-4};
      auto out = e_ep_mu(eVec,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,boundXsVec,teff,nbin,temp);
      auto outputEnergy = std::get<0>(out);
      auto totalSCR     = std::get<1>(out);
      auto totalOutput  = std::get<2>(out);

      std::vector<std::vector<double>> correct_total_SCR { 
      { 0, 0, 0, 0, 2.56073E-3, 94.35762,  -0.4926988,  0.50702073, 5.11146E-3, 
        64.66135,  -0.5043178,  0.49512214, 0.01914047, 9.059714,  -0.5086284, 
        0.49115746, 0.03316949, 2.191982,  -0.5126771,  0.48701264, 0.03572022, 
        2.140833,  -0.5106526,  0.48912311, 0.06377824, 1.515964,  -0.5033707, 
        0.49658435, 0.06632897, 1.409929,  -0.5032132,  0.49674364, 0.094387,0,0,0},
      { 0, 0, 0, 0, 2.56853E-3, 94.30815,  -0.4902113,  0.50929044, 5.11926E-3, 
        64.63746,  -0.5056231,  0.49338288, 0.01914827, 9.058707,  -0.5114592, 
        0.48815991, 0.03317729, 2.192063,  -0.5168388,  0.48260931, 0.03572802, 
        2.140591,  -0.5141586,  0.4854424,  0.06378604, 1.515084,  -0.5044856, 
        0.49543434, 0.06633677, 1.409097,  -0.5042759,  0.49564722, 0.0943948,0,0,0},
      { 0, 0, 0, 0, 2.57573E-3, 94.26242,  -0.4883609,  0.51094033, 5.12646E-3, 
        64.61543,  -0.5065413,  0.4920661,  0.01915547, 9.057789,  -0.5135336, 
        0.48593195, 0.03318449, 2.192141,  -0.5198895,  0.47933588, 0.03573522, 
        2.140370,  -0.5167316,  0.48270819, 0.06379324, 1.514275,  -0.5053057, 
        0.49458194, 0.06634397, 1.408332,  -0.5050575,  0.49483454, 0.094402,0,0,0},
      { 0, 0, 0, 0, 2.58573E-3, 94.19879,  -0.4861800,  0.51284389, 5.13646E-3, 
        64.58489,  -0.5075672,  0.49049006, 0.01916547, 9.056531,  -0.5159469, 
        0.48330575, 0.03319449, 2.192253,  -0.5234399,  0.47547642, 0.03574522, 
        2.140068,  -0.5197296,  0.47948656, 0.06380324, 1.513156,  -0.5062631, 
        0.49357962, 0.06635397, 1.407273,  -0.5059700,  0.49387893, 0.094412,0,0,0},
      { 0, 0, 0, 0, 2.60073E-3, 94.10312,  -0.4834184,  0.51519255, 5.15146E-3, 
        64.53916,  -0.5087807,  0.48845856, 0.01918047, 9.054681,  -0.5189583, 
        0.47997602, 0.03320949, 2.192429,  -0.5278725,  0.4705813,  0.03576022, 
        2.139625,  -0.5234780,  0.47540335, 0.06381824, 1.511486,  -0.5074630, 
        0.49231238, 0.06636897, 1.405693,  -0.5071135,  0.49267075, 0.094427,0,0,0},
      { 0, 0, 0, 0, 2.62073E-3, 93.97513,  -0.4803104,  0.51775321, 5.17146E-3, 
        64.47837,  -0.5100343,  0.48612735, 0.01920047, 9.052286,  -0.5222935, 
        0.4762183, 0.03322949,  2.192680,  -0.5327848,  0.46505399, 0.03578022, 
        2.139051,  -0.5276395,  0.47079634, 0.06383824, 1.509275,  -0.5087989, 
        0.49088673, 0.06638897, 1.403602,  -0.5083865,  0.49131157, 0.094447,0,0,0},
      { 0, 0, 0, 0, 2.65073E-3, 93.78224,  -0.4763895,  0.52086152, 5.20146E-3, 
        64.38756,  -0.5114516,  0.48312106, 0.01923047, 9.048842,  -0.5264320, 
        0.47144972, 0.03325949, 2.193090,  -0.5388859,  0.45803424, 0.03581022, 
        2.138227,  -0.5328197,  0.4649500,  0.06386824, 1.505996,  -0.5104675, 
        0.4890838, 0.06641897,  1.400499,  -0.5099763,  0.48959275, 0.094477,0,0,0},
      { 0, 0, 0, 0, 2.67673E-3, 93.61421,  -0.4734570,  0.52309729, 5.22746E-3, 
        64.30924,  -0.5123949,  0.48082638, 0.01925647, 9.046001,  -0.5294858, 
        0.46785364, 0.03328549, 2.193479,  -0.5433919,  0.45273561, 0.03583622, 
        2.137548,  -0.5366544,  0.46053992, 0.06389424, 1.503188,  -0.5117066, 
        0.48772833, 0.06644497, 1.397842,  -0.5111567,  0.48830057, 0.094503,0,0,0},
      { 0, 0, 0, 0, 2.71073E-3, 93.39333,  -0.4700682,  0.52558526, 5.26146E-3, 
        64.20733,  -0.5133637,  0.47812535, 0.01929047, 9.042484,  -0.5329809, 
        0.46365451, 0.03331949, 2.194033,  -0.5485538,  0.44654224, 0.03587022, 
        2.136709,  -0.5410573,  0.4553876,  0.06392824, 1.499563,  -0.5131335, 
        0.48614958, 0.06647897, 1.394412,  -0.5125158,  0.48679561, 0.094537,0,0,0},
      { 0, 0, 0, 0, 2.75073E-3, 93.13188,  -0.4665525,  0.52805509, 5.30146E-3, 
        64.08820,  -0.5142339,  0.47526615, 0.01933047, 9.038626,  -0.5365800, 
        0.45923451, 0.03335949, 2.194749,  -0.5538749,  0.44001502, 0.03591022, 
        2.135792,  -0.5456076,  0.44995969, 0.06396824, 1.495366,  -0.5146128, 
        0.48449194, 0.06651897, 1.390439,  -0.5139245,  0.48521554, 0.094577,0,0,0}},

      correct_total_Output { { 2056.435, -2.5824E-3, -0.12525, -9.6387E-4 },
                             { 1542.454, -3.4364E-3, -0.12544, -1.2780E-3 },
                             { 1302.372, -4.0629E-3, -0.12561, -1.5059E-3 },
                             { 1101.699, -4.7918E-3, -0.12585, -1.7679E-3 },
                             { 922.9913, -5.6999E-3, -0.12621, -2.0884E-3 },
                             { 781.4661, -6.7021E-3, -0.12669, -2.4332E-3 },
                             { 655.5641, -7.9377E-3, -0.12739, -2.8428E-3 },
                             { 585.3601, -8.8421E-3, -0.12798, -3.1300E-3 },
                             { 520.9973, -9.8679E-3, -0.12875, -3.4408E-3 },
                             { 467.6034, -1.0913E-2, -0.12962, -3.7394E-3 } };

      REQUIRE( ranges::equal(eVec, outputEnergy, equal) );
      for ( size_t i = 0; i < totalSCR.size(); ++i ){
        REQUIRE( ranges::equal(correct_total_SCR[i], totalSCR[i], equal) );
        REQUIRE( ranges::equal(correct_total_Output[i], totalOutput[i], equal) );
      } // for
    } // WHEN 

    WHEN( "larger energies are considered" ){
      tol = 1.0;
      nbin = 2;
      std::vector<double> eVec { 0.0115, 0.015, 0.020493, 0.028, 0.0395, 
      0.056925, 0.081972, 0.111573, 0.145728, 0.20, 0.2907501, 0.39, 0.56, 0.86, 
      1.28, 1.855, 2.59, 3.75, 5.35, 7.65 };
      auto out = e_ep_mu(eVec,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,boundXsVec,teff,nbin,temp);
      auto outputEnergy = std::get<0>(out);
      auto totalSCR     = std::get<1>(out);
      auto totalOutput  = std::get<2>(out);

      std::vector<std::vector<double>> correct_total_SCR { 
      { 0, 0, 0, 0, 6.398541E-3, 36.28738, -0.4317826, 0.51249933, 8.949270E-3, 
        45.09310, -0.3926510, 0.53815258, 0.01405073, 46.22503, -0.3571359, 
        0.5681522, 0.01660146, 38.21418, -0.3953514, 0.55440468, 0.03063047, 
        7.040806, -0.5747132, 0.34454098, 0.04465949, 2.208489, -0.6768230, 
        0.15515612, 0.04721022, 1.946307, -0.6671452, 0.19041559, 0.07526824, 
        0.8563056, -0.5557080, 0.39481736, 0.07781897, 0.7493823, -0.4942598, 
        0.42622434, 0.1058770, 0, 0, 0 },
      { 0, 0, 0, 0, 9.898541E-3, 38.52044, -0.3765761, 0.55880904, 0.01244927, 
        43.94412, -0.3428890, 0.58035946, 0.01755073, 44.01530, -0.3044423, 
        0.61389523, 0.02010146, 36.10908, -0.3475009, 0.59241827, 0.02711597, 
        14.64557, -0.4704007, 0.46192239, 0.03413047, 7.112052, -0.5604148, 
        0.35624525, 0.04815949, 2.322411, -0.6661511, 0.15829574, 0.05071022, 
        2.030124, -0.6588685, 0.18837294, 0.07876824, 0.7826559, -0.4891976, 
        0.41901407, 0.08131897, 0.7205178, -0.4854422, 0.42471355, 0.09534799, 
        0.3671796, -0.4273185, 0.46910122, 0.1093770, 0, 0, 0 },
      { 0, 0, 0, 0, 7.695770E-3, 10.70036, -0.5266456, 0.40725125, 0.01539154, 
        32.82015, -0.3421611, 0.59624361, 0.01794227, 44.50565, -0.1880718, 
        0.73615942, 0.02304373, 42.46749, -0.1601981, 0.75039111, 0.02559446, 
        31.02043, -0.2750449, 0.63859501, 0.03962347, 6.605940, -0.5427613, 
        0.36534374, 0.05365249, 2.261055, -0.6411365, 0.17754496, 0.05620322, 
        1.967274, -0.6367670, 0.2010955, 0.08426124, 0.6145196, -0.3909882, 
        0.47379349,0.08681197, 0.5653507, -0.3872436, 0.47848829, 0.11487,0,0,0},
      { 0, 0, 0, 0, 0.01144927, 8.341378, -0.5456032, 0.37994874, 0.02289854, 
        31.67260, -0.2442249, 0.65474694, 0.02544927, 40.27454, -0.1084076, 
        0.77350515, 0.03055073, 37.94571, -0.08173495, 0.78202488, 0.03310146, 
        28.10760, -0.1922193, 0.68197238, 0.04713047, 6.417074, -0.5000787, 
        0.39598439, 0.06115949, 2.012141, -0.4683233, 0.27927992, 0.06371022, 
        1.749414, -0.4729295, 0.29288266, 0.09176824, 0.5802289, -0.3584118, 
        0.48452824,0.09431897, 0.5320859, -0.3556089, 0.48902252,0.122377,0,0,0},
      { 0, 0, 0, 0, 3.789783E-3, 1.157238, -0.6489744, 0.27630555, 6.340513E-3, 
        1.712094, -0.6809856, 0.18672994, 0.03439854, 27.22864, -0.1415189, 
        0.71036165, 0.03694927, 33.82671, 0.01131044, 0.81488242, 0.04205073, 
        30.77215, 0.05912458, 0.82512736, 0.04460146, 22.31601, -0.03635077, 
        0.73985494, 0.05863047, 5.062007, -0.2492075, 0.50195012, 0.07265949, 
        1.718527, -0.3224060, 0.3875177, 0.07521022, 1.477772, -0.3373421, 
        0.39918795, 0.10326824, 0.4557948, -0.3033841, 0.55659041, 0.10581897, 
        0.4181661, -0.2992540, 0.55983285, 0.1338770, 0, 0, 0 },
      { 0, 0, 0, 0, 0.02121478, 4.269682, -0.6331391, 0.20382196, 0.02376551, 
        4.448254, -0.5370628, 0.23669986, 0.05182354, 24.02381, 0.13217548, 
        0.79209647, 0.05437427, 32.67034, 0.28059685, 0.87683804, 0.05947573, 
        29.96160, 0.30423497, 0.88238004, 0.06202646, 19.78025, 0.18066817, 
        0.80797822, 0.07605547, 4.518938, -0.07694625, 0.59627511, 0.09008449, 
        1.489502, -0.2308740, 0.53638962, 0.09263522, 1.310093, -0.2473291, 
        0.53751703, 0.12069324, 0.4813005, -0.2326615, 0.58766779, 0.12324397, 
        0.4407610, -0.2296444, 0.59006298, 0.1513020, 0, 0, 0 },
      { 0, 0, 0, 0, 0.01565303, 3.233576, -0.4836543, 0.42477796, 0.01820376, 
        3.476273, -0.4804152, 0.41995552, 0.04626178, 4.622980, -0.2741256, 
        0.45460566, 0.04881251, 4.981716, -0.2469309, 0.45988893, 0.07687054, 
        20.89443, 0.31901262, 0.85395368, 0.07942127, 27.79268, 0.42984828, 
        0.91256933, 0.08452273, 25.29343, 0.44139689, 0.91534987, 0.08707346, 
        17.27746, 0.34404011, 0.86151342, 0.10110248, 4.006830, 0.04287871, 
        0.67328024, 0.11513149, 1.548209, -0.1179739, 0.61332584, 0.11768222, 
        1.360818, -0.1360470, 0.61084483, 0.14574024, 0.4915897, -0.1492664, 
        0.62287275, 0.14829097, 0.448185, -0.1482247, 0.62502728,0.176349,0,0,0},
      { 0, 0, 0, 0, 0.01719600, 2.145949, -0.4858456, 0.41844226, 0.04525403, 
        3.871455, -0.2750113, 0.57050522, 0.04780476, 3.928764, -0.2683035, 
        0.57225657, 0.07586278, 4.490384, -0.1655133, 0.59860007, 0.07841351, 
        4.727712, -0.1350897, 0.60622905, 0.10647154, 18.77258, 0.43132542, 
        0.88839302, 0.10902227, 25.47915, 0.53628052, 0.93576237, 0.11412373, 
        23.12614, 0.54332921, 0.93714417, 0.11667446, 15.40619, 0.44387581, 
        0.89281633, 0.13070348, 3.293169, 0.09223047, 0.7311362, 0.14473249, 
        1.520431, -0.02001876, 0.67865287, 0.14728322, 1.318884, -0.04366942, 
        0.67775026, 0.17534124, 0.3754433, -0.1644709, 0.68340855, 0.17789197, 
        0.3441914, -0.1600043, 0.68679304, 0.2059500, 0, 0, 0 },
      { 0, 0, 0, 0, 0.05135100, 2.936101, -0.3582598, 0.50413119, 0.07940903, 
        4.340420, -0.1556312, 0.62177827, 0.08195976, 4.370313, -0.1493023, 
        0.62285747, 0.11001778, 4.501803, -0.04954721, 0.67548471, 0.11256851, 
        4.696989, -0.02167709, 0.68271999, 0.14062654, 16.24565, 0.50329213, 
        0.91259438, 0.14317727, 22.67246, 0.6050416, 0.94889024, 0.14827873, 
        20.34551, 0.61096683, 0.95031172, 0.15082946, 13.15554, 0.51136832, 
        0.91674373, 0.16485848, 3.397643, 0.2283139, 0.7966064, 0.17888749, 
        1.385736, 0.05507391, 0.73641637, 0.18143822, 1.165856, 0.01188555, 
        0.7345713, 0.20949624, 0.3425790, -0.08623449, 0.72571446, 0.21204697, 
        0.3144484, -0.08113379, 0.72860868, 0.2401050, 0, 0, 0 },
      { 0, 0, 0, 0, 0.1056230, 3.155985, -0.2421205, 0.6010158, 0.13368103, 
        3.671941, -0.1077529, 0.71582519, 0.13623176, 3.638367, -0.1070169, 
        0.71558129, 0.16428978, 4.226491, 0.04034963, 0.76031088, 0.16684051, 
        4.366441, 0.06458265, 0.76766615, 0.19489854, 14.83107, 0.58539219, 
        0.9353764, 0.19744927, 19.22757, 0.65779255, 0.96115611, 0.20255073, 
        17.39126, 0.6607692, 0.96167217, 0.20510146, 12.14366, 0.59069232, 
        0.93682481, 0.21913048, 2.913675, 0.28890089, 0.83534432, 0.23315949, 
        1.259227, 0.13752084, 0.79738614, 0.23571022, 1.111729, 0.12145143, 
        0.79287743, 0.26376824, 0.3260070, 0.02600583, 0.77311625, 0.26631897, 
        0.2997675, 0.03175208, 0.77522934, 0.2943770, 0, 0, 0 },
      { 0, 0, 0, 0, 0.1963731, 2.958516, -0.05794192, 0.7060898, 0.22443113, 
        3.424494, 0.07882425, 0.79152976, 0.22698186, 3.375120, 0.07768981, 
        0.79132446, 0.25503988, 2.404830, -0.01643817, 0.71606736, 0.25759061, 
        2.285796, -0.03342578, 0.69607915, 0.28564864, 12.44607, 0.66800565, 
        0.95603054, 0.28819937, 16.23798, 0.72979175, 0.97225931, 0.29330083, 
        14.70375, 0.73138219, 0.97245701, 0.29585156, 10.20920, 0.67201277, 
        0.95675351, 0.32390959, 0.6161664, 0.01250728, 0.71878731, 0.32646032, 
        0.5898517, 0.03528401, 0.74079444, 0.35451834, 0.2919937, 0.18900785, 
        0.8248884, 0.35706907, 0.269230, 0.19495565, 0.8260204,0.3851271,0,0,0},
      { 0, 0, 0, 0, 0.2956230, 2.725977, 0.11174817, 0.77696127, 0.32368103, 
        3.139963, 0.23252378, 0.84067524, 0.32623176, 3.102699, 0.23265251, 
        0.84023785, 0.35428978, 2.069226, 0.12091278, 0.77832926, 0.35684051, 
        1.931478, 0.09768801, 0.75849373, 0.38489854, 11.09803, 0.73104686, 
        0.96688709, 0.38744927, 14.48290, 0.78222291, 0.97827583, 0.39255073, 
        13.11649, 0.78331722, 0.97837902, 0.39510146, 9.089791, 0.73362812, 
        0.96731129, 0.40913048, 2.274010, 0.51339611, 0.91044444, 0.42315949, 
        0.5063194, 0.1431849, 0.78199589, 0.42571022, 0.4945567, 0.17257693, 
        0.8014971, 0.45376824, 0.2586329, 0.3118883, 0.86185834, 0.45631897, 
        0.2373237, 0.3153745, 0.8630514, 0.4843770, 0, 0, 0 },
      { 0, 0, 0, 0, 0.4656230, 2.193209, 0.34353563, 0.84530044, 0.49368103, 
        2.488061, 0.4340457, 0.88999315, 0.49623176, 2.449960, 0.43298434, 
        0.88984699, 0.52428978, 1.530775, 0.32699535, 0.85007531, 0.52684051, 
        1.372849, 0.30562751, 0.83788218, 0.55489854, 8.730070, 0.79961248, 
        0.97712732, 0.55744927, 10.71143, 0.8305158, 0.98478894, 0.56255073, 
        9.692920, 0.83116833, 0.98485235, 0.56510146, 7.155492, 0.80127578, 
        0.97732544, 0.59315949, 0.3721529, 0.33808778, 0.84750823, 0.59571022, 
        0.3755976, 0.37076658, 0.86003403, 0.62376824, 0.2035768, 0.48718298, 
        0.90083019, 0.6263189, 0.1874404, 0.4906165, 0.9013995, 0.654377,0,0,0},
      { 0, 0, 0, 0, 0.7656230, 1.681170, 0.55974401, 0.90037393, 0.79368103, 
        1.910521, 0.61879077, 0.92828046, 0.79623176, 1.884655, 0.61823804, 
        0.92799118, 0.82428978, 1.202787, 0.55316979, 0.90130082, 0.82684051, 
        1.111810, 0.53724227, 0.89195446, 0.85489854, 6.756075, 0.86401174, 
        0.98518245, 0.85744927, 8.274472, 0.8848299, 0.98965552, 0.86255073, 
        7.488522, 0.88515132, 0.98968216, 0.86510146, 5.534898, 0.86479825, 
        0.98526815, 0.87913048, 1.301852, 0.75390266, 0.95804595, 0.89315949, 
        0.3003485, 0.55215972, 0.89618548, 0.89571022, 0.2948551, 0.5694757, 
        0.90549965, 0.92376824, 0.1525852, 0.64867094, 0.93419803, 0.92631897, 
        0.1401063, 0.65033504, 0.93461477, 0.9543770, 0, 0, 0 },
      { 0,0,0,0, 1.185623, 1.237254, 0.70911904, 0.93423084, 1.213681, 1.433694, 
        0.75057591, 0.9524167, 1.21623180, 1.408567, 0.74956879, 0.95232408, 
        1.24428980, 0.9538225, 0.71281748, 0.93286846, 1.24684050, 0.7668874, 
        0.68491029, 0.93014278, 1.27489850, 5.082023, 0.90731847, 0.99014784, 
        1.27744930, 5.966053, 0.91904715, 0.99319491, 1.28255070, 5.398922, 
        0.9192062, 0.99320742, 1.28510150, 4.162772, 0.90770301, 0.99018557, 
        1.29913050, 1.056866, 0.83133817, 0.97306279, 1.31315950, 0.2087964, 
        0.69295276, 0.93198037, 1.31571020, 0.2339720, 0.71968125, 0.93458524, 
        1.34376820, 0.1163431, 0.76210402, 0.95445472, 1.346319, 0.1085892, 
        0.74869008, 0.95400781, 1.374377, 0, 0, 0 },
      { 0,0,0,0, 1.760623, 0.9155039, 0.79235217, 0.95499277, 1.788681, 1.035789, 
        0.81939101, 0.96755617, 1.79123180, 1.020559, 0.81886322, 0.96742782, 
        1.81928980, 0.6536328, 0.78106091, 0.95442136, 1.82184050, 0.6001188, 
        0.77188182, 0.95002097, 1.84989850, 3.718084, 0.93514054, 0.99284934, 
        1.85244930, 4.450400, 0.94408335, 0.99520436, 1.85755070, 4.027026, 
        0.94415918, 0.99521061, 1.86010150, 3.043644, 0.93530884, 0.99286582, 
        1.87413050, 0.6933262, 0.87713363, 0.98007732, 1.88815950, 0.1628646, 
        0.77584011, 0.95098706, 1.89071020, 0.1607429, 0.78534426, 0.95536193, 
        1.91876820, 0.08383991, 0.82548941, 0.96853034, 1.921319, 0.07702142, 
        0.82629044, 0.96869273, 1.949377, 0, 0, 0 },
      { 0,0,0,0,2.495623, 0.684144, 0.85543113, 0.96786949, 2.523681, 0.7956547, 
        0.87581725, 0.97661665, 2.52623180, 0.7814250, 0.87522581, 0.97657064, 
        2.55428980, 0.5255773, 0.8552116, 0.96689836, 2.55684050, 0.4241471, 
        0.84109166, 0.96558251, 2.58489850, 2.741674, 0.95275201, 0.9946687, 
        2.58744930, 3.355743, 0.9598848, 0.99653672, 2.59255070, 3.036462, 
        0.95992447, 0.99654008, 2.59510150, 2.244593, 0.95284072, 0.99467826, 
        2.60913050, 0.5827793, 0.91477804, 0.98659835, 2.62315950, 0.1155304, 
        0.84329195, 0.96603729, 2.62571020, 0.1298201, 0.85524479, 0.96718095, 
        2.65376820, 0.06433408, 0.87857369, 0.97709849, 2.656319, 0.06003984, 
        0.87188272, 0.97686095, 2.684377, 0, 0, 0 },
      { 0,0,0,0, 3.655623, 0.4886450, 0.8984787, 0.97791496, 3.683681, 0.552028, 
        0.91130125, 0.98405792, 3.68623180, 0.5437892, 0.91099709, 0.98399342, 
        3.71428980, 0.3472842, 0.89181537, 0.97757663, 3.71684050, 0.3183987, 
        0.8871398, 0.97540763, 3.74489850, 1.870215, 0.96678093, 0.99644995, 
        3.74744930, 2.337015, 0.97230445, 0.99767512, 3.75255070, 2.114736, 
        0.97232313, 0.9976765, 3.75510150, 1.531217, 0.96682731, 0.99645484, 
        3.78315950, 0.08659501, 0.88814162, 0.97564515, 3.78571020, 0.08552579, 
        0.89289665, 0.9778072, 3.81376820, 0.04465574, 0.91265739, 0.98426427, 
        3.816319, 0.04102572, 0.91302953, 0.98433715, 3.844377, 0, 0, 0 },
      { 0, 0, 0, 0, 5.255623, 0.3509116, 0.93076576, 0.98455375, 5.283681, 
        0.4039723, 0.93581289, 0.98862296, 5.28623180, 0.4079868, 0.93653155, 
        0.98853045, 5.31428980, 0.2688878, 0.92908085, 0.98392712, 5.31684050, 
        0.2173658, 0.9235479, 0.98340795, 5.34489850, 1.363380, 0.97712199, 
        0.99750583, 5.34744930, 1.679261, 0.98071659, 0.99838439, 5.35255070, 
        1.519601, 0.98072575, 0.99838495, 5.35510150, 1.116151, 0.97714331, 
        0.99750821, 5.38315950, 0.05923303, 0.92406421, 0.98351255, 5.38571020, 
        0.06622016, 0.92952478, 0.98403008, 5.41376820, 0.03353452, 0.93737359, 
        0.98865802, 5.416319, 0.0299993, 0.9366438, 0.98876354, 5.444377, 0,0,0},
      { 0,0,0,0, 7.555623, 0.2503482, 0.95083667, 0.9891893, 7.583681, 0.2810905, 
        0.95683518, 0.99221149, 7.58623180, 0.2768268, 0.95667312, 0.99218021, 
        7.61428980, 0.1761253, 0.94716338, 0.98905354, 7.61684050, 0.1611371, 
        0.94481196, 0.98799677, 7.64489850, 0.9489814, 0.98386201, 0.99826658, 
        7.64744930, 1.180285, 0.98722153, 0.99887269, 7.65255070, 1.068031, 
        0.98722572, 0.99887297, 7.65510150, 0.7769175, 0.98387307, 0.99826788, 
        7.68315950, 0.04387216, 0.94505406, 0.98805394, 7.68571020, 0.04340566, 
        0.94742429, 0.98910877, 7.71376820, 0.02272899, 0.95707178, 0.99224522, 
        7.716319, 0.02088466, 0.95725012, 0.9922785, 7.744377, 0, 0, 0 } },

      correct_total_Output { { 120.3086, 0.038271, -0.15912,   8.9950E-3 }, 
                             { 111.7517, 0.068250, -0.15754,   0.013534  }, 
                             { 111.3492, 0.13946,  -0.12315,   0.037140  }, 
                             { 103.0490, 0.18917,  -0.11952,   0.033077  }, 
                             { 97.45028, 0.29381,  -0.095721,  0.010583  }, 
                             { 77.17683, 0.39399,  -0.019244, -0.042687  }, 
                             { 62.87854, 0.45460,   0.037278, -0.037647  }, 
                             { 53.74421, 0.49282,   0.094176, -3.5540E-3 }, 
                             { 48.46418, 0.50607,   0.11344,   0.019245  }, 
                             { 39.84313, 0.52807,   0.15251,   0.064008  }, 
                             { 33.11188, 0.57134,   0.19909,   0.10335   }, 
                             { 28.19805, 0.60826,   0.21760,   0.087852  }, 
                             { 25.34406, 0.69564,   0.32088,   0.10667   }, 
                             { 21.72389, 0.77641,   0.44855,   0.17288   }, 
                             { 19.73656, 0.84425,   0.58858,   0.31911   }, 
                             { 18.49592, 0.88522,   0.68558,   0.45103   }, 
                             { 17.67969, 0.91767,   0.76800,   0.57757   }, 
                             { 17.18447, 0.94136,   0.83166,   0.68480   }, 
                             { 16.68117, 0.95922,   0.88125,   0.77289   }, 
                             { 16.55845, 0.97079,   0.91421,   0.83379   } };

      REQUIRE( ranges::equal(eVec, outputEnergy, equal) );
      for ( size_t i = 0; i < totalSCR.size(); ++i ){
        REQUIRE( ranges::equal(correct_total_SCR[i], totalSCR[i], equal) );
        REQUIRE( ranges::equal(correct_total_Output[i], totalOutput[i], equal) );
      } // for

    } // WHEN 

  } // GIVEN 



  GIVEN( "temperature is so high we need to alter initial energies" ){
    double temp = 3001.0;

    WHEN( "small energies are considered" ){
      tol = 1.5;
      std::vector<double> eVec { 1e-4, 1e-2, 1.0, 5.0, 10.0 };
      auto out = e_ep_mu(eVec,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,boundXsVec,teff,nbin,temp);
      auto outputEnergy = std::get<0>(out);
      auto totalSCR     = std::get<1>(out);
      auto totalOutput  = std::get<2>(out);


      std::vector<std::vector<double>> correct_total_SCR 
      { { 0, 0, 0, 0, 2.650730E-3, 93.94900, -0.4763895, 0.52086152, 3.926095E-3, 
          77.83124, -0.4970172, 0.49889362, 5.201460E-3, 64.50206, -0.5114516, 
          0.48312106, 0.01923047, 9.064933, -0.5264320, 0.47144972, 0.03325949, 
          2.196990, -0.5388859, 0.45803424, 0.03581022, 2.142029, -0.5328197, 
          0.4649500, 0.06386824, 1.508674, -0.5104675, 0.4890838, 0.06641897, 
          1.402990, -0.5099763, 0.48959275, 0.09447700, 0, 0, 0 },
        { 0, 0, 0, 0, 0.02023858, 26.67955, -0.2783222, 0.63676077, 0.02278931, 
          34.63960, -0.1358991, 0.76176832, 0.02789077, 32.59977, -0.1095187, 
          0.77305165, 0.03044150, 24.41164, -0.2141499, 0.66905241, 0.05849953, 
          1.792701, -0.5440201, 0.23341011, 0.06105026, 1.520519, -0.5309060, 
          0.26204544, 0.08910828, 0.4912827, -0.3693108, 0.48052392, 0.09165901, 
          0.4509162, -0.3663501, 0.48501002, 0.11971704, 0, 0, 0 },
        { 0, 0, 0, 0, 6.326799, 0.2957128, 0.9395925, 0.98698059, 6.354857, 
          0.3351288, 0.94712664, 0.99054217, 6.35740780, 0.3306528, 0.9469835, 
          0.99049669, 6.38546580, 0.2108538, 0.94043574, 0.98694645, 6.38801650, 
          0.1957541, 0.93834763, 0.98571005, 6.41607450, 1.125553, 0.98092334, 
          0.99791534, 6.41862530, 1.405742, 0.98407766, 0.99864053, 6.42372670, 
          1.271919, 0.98408426, 0.99864113, 6.42627750, 0.9215449, 0.98093865, 
          0.99791691, 6.45433550, 0.05327966, 0.93864052, 0.98578509, 6.45688620, 
          0.05194653, 0.94075418, 0.98702221, 6.48494420, 0.02714275, 0.94753683, 
          0.99059126, 6.487495, 0.02489443, 0.94770325, 0.99064007, 6.515553,0,0,0},
        { 0, 0, 0, 0, 44.3389840, 0.04462688, 0.9924676, 0.99827418, 44.3670420, 
          0.05270311, 0.99360848, 0.9988018, 44.3695930, 0.05260747, 0.99364043, 
          0.99881068, 44.3976510, 0.05084549, 0.9939433, 0.99889839, 44.4002020, 
          0.05362081, 0.99419879, 0.99893435, 44.42826, 0.1739482, 0.99766872, 
          0.99973811, 44.43081, 0.1954884, 0.99788576, 0.9998082, 44.4359120, 
          0.1768854, 0.99788587, 0.99980821, 44.4384620, 0.1424234, 0.99766898, 
          0.99973813, 44.46652, 0.01461803, 0.99420425, 0.9989350, 44.4690710, 
          0.01254246, 0.99394939, 0.99889924, 44.4971290, 4.320176E-3, 0.99365116, 
          0.99881226, 44.49968, 3.916161E-3, 0.99361966, 0.99880347, 44.5277380, 0, 0, 0}, 
        { 0, 0, 0, 0, 102.121460, 0.01950921, 0.99714891, 0.99951808, 102.149520, 
          0.01935915, 0.99731304, 0.99946969, 102.152070, 0.01934531, 0.99732799, 
          0.99947329, 102.180130, 0.01814116, 0.99740842, 0.99952197, 102.182680, 
          0.01869469, 0.99747799, 0.99953609, 102.210740, 0.06180573, 0.99899185, 
          0.99988829, 102.213290, 0.06894141, 0.99907944, 0.99991515, 102.218390, 
          0.06238281, 0.99907946, 0.99991515, 102.220940, 0.05060571, 0.99899189, 
          0.99988829, 102.2490, 5.095442E-3, 0.99747898, 0.99953622, 102.251550, 
          4.474167E-3, 0.99740951, 0.99952212, 102.279610, 1.588171E-3, 0.9973299, 
          0.99947355, 102.28216, 1.438108E-3, 0.99731502, 0.99946997, 102.31022,0,0,0}},
      correct_total_Output { { 654.4004, -8.6082E-3, -0.12746, -3.0949E-3 },
                             { 127.0866,  0.21575,   -0.11776,  0.038419  },
                             { 16.74697,  0.96445,    0.89610,  0.80018   },
                             { 17.19724,  0.99540,    0.98623,  0.97260   },
                             { 21.15485,  0.99834,    0.99501,  0.99005   } };
 
      correctEnergies = { 1E-4,0.0253400393, 6.421176, 44.4333610, 102.215840 };
      REQUIRE( ranges::equal(correctEnergies, outputEnergy, equal) );

      for ( size_t i = 0; i < totalSCR.size(); ++i ){
        REQUIRE( ranges::equal(correct_total_SCR[i], totalSCR[i], equal) );
        REQUIRE( ranges::equal(correct_total_Output[i], totalOutput[i], equal) );
      } // for

    } // WHEN

  } // GIVEN 

} // TEST CASE 

