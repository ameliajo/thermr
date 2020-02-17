#include "catch.hpp"
#include "calcem/calcem_util/e_mu_ep_util/mainLoop.h"
#include "generalTools/testing.h"


TEST_CASE( " mu-E' ordering " ){
  int imax = 20, lat = 0, iinc = 2, lasym = 0;
  double tev = 2.5507297688e-2, tol = 0.05;
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
  std::vector<double> correctEnergies;
  double enow = 1e-5;

  std::vector<double> correct_uj;




  enow = 1e-6; 
  auto out = do_530_etc(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
  REQUIRE( 6325.1941714771147 == Approx(std::get<0>(out)).epsilon(1e-6) );
  REQUIRE( 2.8371734942764979E-003 == Approx(std::get<1>(out)).epsilon(1e-6) );
  correct_uj = {-1, -0.75, -0.625, -0.5, -0.375, -0.25, -0.125, 0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 1 };
  for (size_t i = 0; i < correct_uj.size(); ++i){
    REQUIRE( correct_uj[i] == Approx(std::get<2>(out)[i]).epsilon(1e-6) );
  }




  enow = 1e-5;
  out = do_530_etc(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
  REQUIRE( 2004.20546598 == Approx(std::get<0>(out)).epsilon(1e-6) );
  REQUIRE( 0.00903406640 == Approx(std::get<1>(out)).epsilon(1e-6) );
  correct_uj = {-1, -0.75, -0.625, -0.5, -0.375, -0.25, -0.125, 0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 1 };
  for (size_t i = 0; i < correct_uj.size(); ++i){
    REQUIRE( correct_uj[i] == Approx(std::get<2>(out)[i]).epsilon(1e-6) );
  }



  enow = 1e-4;
  out = do_530_etc(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
  REQUIRE( 648.0310824 == Approx(std::get<0>(out)).epsilon(1e-6) );
  REQUIRE( 0.031418177 == Approx(std::get<1>(out)).epsilon(1e-6) );
  correct_uj = {-1, -0.75, -0.625, -0.5, -0.375, -0.25, -0.125, 0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 1 };
  for (size_t i = 0; i < correct_uj.size(); ++i){
    REQUIRE( correct_uj[i] == Approx(std::get<2>(out)[i]).epsilon(1e-6) );
  }


  enow = 1e-2;
  out = do_530_etc(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
  REQUIRE( 123.58909310679307 == Approx(std::get<0>(out)).epsilon(1e-6) );
  REQUIRE( 9.0734245819064419E-002 == Approx(std::get<1>(out)).epsilon(1e-6) );
  correct_uj = {-1, -0.75, -0.625, -0.5, -0.375, -0.25, -0.125, 0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 1 };
  for (size_t i = 0; i < correct_uj.size(); ++i){
    REQUIRE( correct_uj[i] == Approx(std::get<2>(out)[i]).epsilon(1e-6) );
  }


  enow = 1.0;
  out = do_530_etc(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
  REQUIRE( 40.227979467296890 == Approx(std::get<0>(out)).epsilon(1e-6) );
  REQUIRE( 0.54810870138245560  == Approx(std::get<1>(out)).epsilon(1e-6) );
  correct_uj = {-1, -0.75, -0.625, -0.5, -0.375, -0.25, -0.125, 0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 1 };
  for (size_t i = 0; i < correct_uj.size(); ++i){
    REQUIRE( correct_uj[i] == Approx(std::get<2>(out)[i]).epsilon(1e-6) );
  }





  enow = 1e-2;


  tol = 1.0;
  out = do_530_etc(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
  REQUIRE( 122.34746244407418 == Approx(std::get<0>(out)).epsilon(1e-6) );
  REQUIRE( 2.4551863335822984E-002 == Approx(std::get<1>(out)).epsilon(1e-6) );
  correct_uj = {-1, -0.75, -0.625, -0.5, -0.375, -0.25, -0.125, 0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 1 };
  for (size_t i = 0; i < correct_uj.size(); ++i){
    REQUIRE( correct_uj[i] == Approx(std::get<2>(out)[i]).epsilon(1e-6) );
  }

  tol = 5.0;
  out = do_530_etc(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
  REQUIRE( 143.75464230251364 == Approx(std::get<0>(out)).epsilon(1e-6) );
  REQUIRE( 3.8463983799896351E-002 == Approx(std::get<1>(out)).epsilon(1e-6) );
  correct_uj = {-1, -0.75, -0.625, -0.5, -0.375, -0.25, -0.125, 0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 1 };
  for (size_t i = 0; i < correct_uj.size(); ++i){
    REQUIRE( correct_uj[i] == Approx(std::get<2>(out)[i]).epsilon(1e-6) );
  }

  tol = 10.0;
  out = do_530_etc(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
  REQUIRE( 145.79479928728830 == Approx(std::get<0>(out)).epsilon(1e-6) );
  REQUIRE( 5.0169921218852623E-002 == Approx(std::get<1>(out)).epsilon(1e-6) );
  correct_uj = {-1, -0.75, -0.625, -0.5, -0.375, -0.25, -0.125, 0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 1 };
  for (size_t i = 0; i < correct_uj.size(); ++i){
    REQUIRE( correct_uj[i] == Approx(std::get<2>(out)[i]).epsilon(1e-6) );
  }



} // TEST CASE







TEST_CASE( "E-mu-E' ordering " ){
  int imax = 20, lat = 0, iinc = 2, lasym = 0;
  double tev = 2.5507297688e-2, tol = 0.05;
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
  std::vector<double> correctEnergies;
  std::vector<double> correctSCR;

  double enow = 1e-2;
  /*
  auto out = mu_ep(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
  auto totalSCR = std::get<1>(out);
  std::vector<double> 
  correctSCR_0 = { 0, 0, 4.30920E-10, 2.091391E-3, 8.61840E-10, 2.957775E-3, 
  1.723680E-9, 4.183130E-3, 2.290573E-7, 4.830791E-2, 4.563910E-7, 6.824490E-2, 
  9.110582E-7, 9.653521E-2, 1.820393E-6, 0.13668894, 3.639062E-6, 0.19374016, 
  7.276400E-6, 0.27495508, 1.455108E-5, 0.39093138, 2.910043E-5, 0.55738507, 
  5.819914E-5, 7.982454E-1, 1.163966E-4, 1.15147002, 2.327914E-4, 1.68104760, 
  4.655810E-4, 2.50435616, 9.311603E-4, 3.86118945, 1.862319E-3, 6.30801204, 
  3.724636E-3, 11.3392485, 5.586953E-3, 15.3398326, 7.449270E-3, 16.8676709, 
  1.255073E-2, 15.9593966, 1.510146E-2, 14.2240943, 1.860871E-2, 9.91032913, 
  2.211597E-2, 7.19511127, 2.562322E-2, 5.22054068, 2.913047E-2, 4.15656184, 
  3.614498E-2, 2.76220540, 4.315949E-2, 1.79919868, 4.571022E-2, 1.54023970, 
  5.973923E-2, 0.86174463, 7.376824E-2, 0.49944285, 7.631897E-2, 0.45461919, 
  7.982623E-2, 0.39474058, 8.070304E-2, 0.38027505, 8.092225E-2, 0.37669678, 
  8.092396E-2, 0.37666888, 8.092482E-2, 0.37665492, 8.092487E-2, 0.37665404, 
  8.092490E-2, 3.766536E-1, 8.092492E-2, 0.22718637, 8.092503E-2, 0.22718545, 
  8.092524E-2, 0.22718362, 8.092567E-2, 0.22717997, 8.092910E-2, 0.22715071, 
  8.093595E-2, 0.22709222, 8.094965E-2, 0.22697527, 8.097705E-2, 0.22674156, 
  8.103185E-2, 0.22627482, 8.114145E-2, 0.22534419, 8.157986E-2, 0.22165903, 
  8.333348E-2, 0.20750076, 9.034799E-2, 0.15923299 }, 
  correctSCR_2 { 0, 0, 1.104587E-9, 3.348397E-3, 2.209175E-9, 4.735512E-3, 
  4.418349E-9, 6.697354E-3, 2.317519E-7, 4.855694E-2, 4.590855E-7, 6.837779E-2, 
  9.137526E-7, 9.654190E-2, 1.823087E-6, 0.13651965, 3.641755E-6, 0.19327509, 
  7.279092E-6, 0.27394354, 1.455377E-5, 3.888738E-1, 2.910311E-5, 0.55331018, 
  5.820181E-5, 0.79030441, 1.163992E-4, 1.13623631, 2.327940E-4, 1.65242632, 
  4.655835E-4, 2.45229571, 9.311627E-4, 3.77190447, 1.862321E-3, 6.17487363, 
  3.724637E-3, 11.2340743, 5.586954E-3, 16.9101287, 7.449270E-3, 19.5371096, 
  1.255073E-2, 19.0269439, 1.510146E-2, 16.7865802, 1.860871E-2, 11.2246444, 
  2.211597E-2, 7.82352113, 2.562322E-2, 5.66216515, 2.913047E-2, 4.21384864, 
  3.614498E-2, 2.48184627, 4.315949E-2, 1.64769203, 4.571022E-2, 1.41368180, 
  5.973923E-2, 0.84270638, 7.376824E-2, 0.50196392, 7.631897E-2, 0.46014534, 
  9.034799E-2, 0.25215334 }, 
  correctSCR_5 { 0, 0, 6.981995E-9, 8.418356E-3, 1.396399E-8, 1.190578E-2, 
  2.792798E-8, 1.683818E-2, 7.449270E-3, 21.4382910, 1.255073E-2, 22.9919788, 
  1.510146E-2, 20.0251088, 1.860871E-2, 12.7658125, 2.211597E-2, 8.44229035, 
  2.562322E-2, 5.79024532, 2.913047E-2, 4.11121686, 3.263773E-2, 3.01403869, 
  3.614498E-2, 2.27463937, 4.315949E-2, 1.36850860, 4.571022E-2, 1.18190684, 
  7.376824E-2, 0.49018879, 7.631897E-2, 4.507353E-1, 9.034799E-2, 0.25055336, 
  9.736249E-2, 0.17403347 };

  std::vector<double> correct_uj = {-1, -0.75, -0.625, -0.5, -0.375, -0.25, -0.125, 0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 1 };
  REQUIRE( ranges::equal(std::get<0>(out),correct_uj,equal) );
  REQUIRE( ranges::equal(totalSCR[0],correctSCR_0,equal) );
  REQUIRE( ranges::equal(totalSCR[2],correctSCR_2,equal) );
  REQUIRE( ranges::equal(totalSCR[5],correctSCR_5,equal) );





  enow = 1e-5;
  out = mu_ep(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
  totalSCR = std::get<1>(out);
  correctSCR_0 = { 0, 0, 4.30920E-13, 1.464430E-2, 8.61840E-13, 2.070840E-2, 
1.72368E-12, 2.928255E-2, 1.950040E-8, 2.98444322, 3.899907E-8, 4.14807360, 
7.799641E-8, 5.72712134, 1.559911E-7, 7.83659052, 3.119805E-7, 10.5964754, 
6.239592E-7, 14.1104102, 1.247917E-6, 18.4326009, 2.495832E-6, 23.5285372, 
4.991662E-6, 29.2442366, 9.983321E-6, 35.3038992, 1.996664E-5, 41.3468829, 
3.993328E-5, 46.9904971, 7.986656E-5, 51.8807205, 1.597331E-4, 55.6877503, 
3.194662E-4, 58.0175919, 6.389325E-4, 58.2322955, 1.277865E-3, 55.2214749, 
2.555730E-3, 47.3732498, 5.111460E-3, 33.5696116, 5.111567E-3, 24.2192580, 
5.111674E-3, 24.2189539, 5.111888E-3, 24.2183455, 5.112316E-3, 24.2171288, 
5.113172E-3, 24.2146954, 5.114885E-3, 24.2098294, 5.118310E-3, 24.2000992, 
5.125160E-3, 24.1806475, 5.138860E-3, 24.1417783, 5.166260E-3, 24.0641767, 
5.221061E-3, 23.9095257, 5.330663E-3, 23.6024662, 5.549866E-3, 22.9975569, 
5.988273E-3, 21.8259877, 6.865086E-3, 19.6411743, 8.618713E-3, 15.8922795, 
1.212597E-2, 10.4740702, 1.563322E-2, 7.00918359, 1.914047E-2, 4.76897518, 
2.264773E-2, 3.29687586, 2.615498E-2, 2.31324729, 2.966223E-2, 1.62093411, 
3.316949E-2, 1.16809696, 3.572022E-2, 1.13392943, 4.974923E-2, 1.09011839, 
6.377824E-2, 0.78559595, 6.632897E-2, 0.73030157, 8.035799E-2, 0.41525738, 
8.737250E-2, 0.28765478 };
  std::vector<double> correctSCR_13 { 0, 0, 9.768411E-9, 2.25761851, 1.953682E-8, 3.22398909, 
3.907364E-8, 4.62270795, 7.814729E-8, 6.666377+0, 1.562946E-7, 9.69156079, 
3.125891E-7, 14.2491359, 6.251783E-7, 21.2704279, 1.250357E-6, 32.3431682, 
2.500713E-6, 49.8920806, 5.001426E-6, 75.3198649, 1.000285E-5, 99.9032758, 
2.000570E-5, 106.391691, 4.001141E-5, 99.2573739, 8.002281E-5, 90.2670263, 
1.600456E-4, 82.7329094, 3.200912E-4, 76.2677437, 6.401825E-4, 69.6252289, 
1.280365E-3, 61.1926122, 2.560730E-3, 49.1815301, 5.111460E-3, 32.8119960, 
5.111567E-3, 24.2192418, 5.111674E-3, 24.2189215, 5.111888E-3, 24.2182806, 
5.112316E-3, 24.2169991, 5.113172E-3, 24.2144359, 5.114885E-3, 24.2093106, 
5.118310E-3, 24.1990624, 5.125160E-3, 24.1785770, 5.138860E-3, 24.1376496, 
5.166260E-3, 24.0559681, 5.221061E-3, 23.8933017, 5.330663E-3, 23.5707728, 
5.549866E-3, 22.9370528, 5.988273E-3, 21.7155193, 6.865086E-3, 19.4557689, 
8.618713E-3, 15.6252269, 1.212597E-2, 10.1786295, 1.563322E-2, 6.74897279, 
1.914047E-2, 4.55633103, 2.264773E-2, 3.12844045, 2.615498E-2, 2.18163212, 
2.966223E-2, 1.53537322, 3.316949E-2, 1.09216009, 3.572022E-2, 1.07175441, 
4.974923E-2, 1.05122026, 6.377824E-2, 0.77178037, 6.632897E-2, 0.71805493, 
8.035799E-2, 0.40822819, 8.737250E-2, 0.28275704 };
  REQUIRE( ranges::equal(std::get<0>(out),correct_uj,equal) );

  REQUIRE( ranges::equal(totalSCR[0],correctSCR_0,equal) );
  REQUIRE( ranges::equal(totalSCR[13],correctSCR_13,equal) );


  enow = 5.0;
  out = mu_ep(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
  totalSCR = std::get<1>(out);
  correctSCR_0 = { 0, 0, 2.154601E-7, 1.514951E-4, 4.309201E-7, 2.142270E-4, 
8.618402E-7, 3.029235E-4, 1.968234E-5, 1.445061E-3, 3.850283E-5, 2.019164E-3, 
7.614383E-5, 2.835320E-3, 1.514258E-4, 3.989305E-3, 3.019898E-4, 5.613554E-3, 
6.031177E-4, 7.887280E-3, 1.205374E-3, 1.104333E-2, 2.409885E-3, 1.535882E-2, 
4.818909E-3, 2.109429E-2, 9.636956E-3, 2.829520E-2, 1.927305E-2, 3.628273E-2, 
3.854524E-2, 4.265231E-2, 7.708962E-2, 4.232956E-2, 0.15417837, 3.012932E-2, 
0.23126712, 1.879896E-2, 0.30835587, 1.112764E-2, 0.38544463, 6.402796E-3, 
0.46253338, 3.619745E-3, 0.53962213, 2.021977E-3, 0.61671088, 1.119722E-3, 
0.69379964, 6.160328E-4, 0.77088839, 3.371953E-4, 0.84797714, 1.838169E-4, 
0.92506589, 9.987087E-5, 1.00215460, 5.411107E-5, 1.07924340, 2.924926E-5, 
1.15633220, 1.577879E-5, 1.23342090, 8.497312E-6, 1.31050970, 4.569137E-6, 
1.38759840, 2.453644E-6, 1.46468720, 1.316070E-6 };
  std::vector<double> correctSCR_12 { 0, 0, 1.22640580, 0.34830248, 1.83960870, 5.624488E-1, 
2.14621010, 0.59573748, 2.45281150, 0.53914596, 3.06601440, 0.26240295, 
3.37261590, 1.402814E-1, 3.52591660, 9.609423E-2, 3.67921730, 6.309734E-2, 
3.83251810, 3.975582E-2, 3.98581880, 2.406462E-2, 4.13911950, 1.401192E-2, 
4.29242020, 7.858471E-3, 4.44572090, 4.251094E-3, 4.59902160, 2.221250E-3, 
4.675672, 1.585582E-3, 4.75232230, 1.122652E-3, 4.82897270, 7.885744E-4, 
4.905623, 5.496150E-4, 4.933681, 4.806588E-4, 4.93623180, 4.748123E-4, 
4.96428980, 4.147833E-4, 4.96684050, 4.096975E-4, 4.99489850, 3.575098E-4, 
4.99744930, 3.530911E-4, 5.00255070, 3.183044E-4, 5.00510150, 2.905347E-4, 
5.01913050, 1.758308E-4, 5.03315950, 1.063861E-4, 5.03571020, 9.709551E-5, 
5.04973920, 5.873042E-5, 5.06376820, 3.551576E-5, 5.066319, 3.241096E-5, 
5.080348, 1.959409E-5 };
  REQUIRE( ranges::equal(std::get<0>(out),correct_uj,equal) );
  REQUIRE( ranges::equal(totalSCR[0],correctSCR_0,equal) );
  REQUIRE( ranges::equal(totalSCR[12],correctSCR_12,equal) );

  */


  GIVEN( "higher tolerance" ){
    tol = 5.0;
    double enow = 1e-5;
    /*
    out = mu_ep(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
    std::vector<double> uj = std::get<0>(out);
    totalSCR = std::get<1>(out);

    std::vector<std::vector<double>> correctFull_SCR 
{ { 0, 0, 1.72368E-12, 2.238956E-2, 5.111460E-3, 25.6674690, 3.316949E-2, 0.89313194, 3.572022E-2, 8.670073E-1, 6.377824E-2, 0.60067003, 6.632897E-2, 0.55839171 },
{ 0, 0, 3.06630E-12, 2.986239E-2, 5.111460E-3, 25.6113338, 3.316949E-2, 0.88472242, 3.572022E-2, 8.601484E-1, 6.377824E-2, 0.59918685, 6.632897E-2, 5.570788E-1 },
{ 0, 0, 4.41835E-12, 3.584652E-2, 5.111460E-3, 25.5803635, 3.316949E-2, 0.88053174, 3.572022E-2, 0.85672717, 6.377824E-2, 0.59844196, 6.632897E-2, 5.564192E-1 },
{ 0, 0, 6.91196E-12, 4.483502E-2, 5.111460E-3, 25.5473650, 3.316949E-2, 0.87635052, 3.572022E-2, 0.85331147, 6.377824E-2, 0.59769489, 6.632897E-2, 0.55575751 },
{ 0, 0, 1.23199E-11, 5.985772E-2, 5.111460E-3, 25.5122651, 3.316949E-2, 0.87217882, 3.572022E-2, 0.84990135, 6.377824E-2, 0.59694566,  6.632897E-2, 0.55509374 },
{ 0, 0, 2.79280E-11, 9.012291E-2, 5.111460E-3, 25.4749877, 3.316949E-2, 0.86801668, 3.572022E-2, 0.84649684, 6.377824E-2, 0.59619426, 6.632897E-2, 5.544279E-1 },
{ 0, 0, 1.16497E-10, 0.18406288, 5.111460E-3, 25.4354536, 3.316949E-2, 0.86386417, 3.572022E-2, 8.430980E-1, 6.377824E-2, 0.59544071, 6.632897E-2, 5.537600E-1 },
{ 0, 0, 2.560730E-3, 37.0267220, 5.111460E-3, 25.3935807, 3.316949E-2, 0.85972133, 3.572022E-2, 0.83970486, 6.377824E-2, 0.59468503, 6.632897E-2, 0.55309006 },
{ 0, 0, 2.560730E-3, 37.1266634, 5.111460E-3, 25.3492835, 3.316949E-2, 0.85558822, 3.572022E-2, 0.83631746, 6.377824E-2, 0.59392721, 6.632897E-2, 0.55241807 },
{ 0, 0, 2.560730E-3, 37.2253718, 5.111460E-3, 25.3024730, 3.316949E-2, 0.85146488, 3.572022E-2, 0.83293584, 6.377824E-2, 0.59316728, 6.632897E-2, 0.55174406 },
{ 0, 0, 2.560730E-3, 37.3226849, 5.111460E-3, 25.2530569, 3.316949E-2, 0.84735137, 3.572022E-2, 0.82956005, 6.377824E-2, 0.59240524, 6.632897E-2, 0.55106802 },
{ 0, 0, 2.560730E-3, 37.4184261, 5.111460E-3, 25.2009388, 3.316949E-2, 0.84324773, 3.572022E-2, 0.82619012, 6.377824E-2, 5.916411E-1, 6.632897E-2, 0.55038997 },
{ 0, 0, 2.560730E-3, 37.5124036, 5.111460E-3, 25.1460188, 3.316949E-2, 0.83915402, 3.572022E-2, 8.228261E-1, 6.377824E-2, 0.59087488, 6.632897E-2, 0.54970992 },
{ 0, 0, 2.560730E-3, 37.6044088, 5.111460E-3, 25.0881928, 3.316949E-2, 0.83507029, 3.572022E-2, 0.81946802, 6.377824E-2, 0.59010658, 6.632897E-2, 0.54902788 },
{ 0, 0, 2.560730E-3, 37.7815744, 5.111460E-3, 24.9633848, 3.316949E-2, 0.82693294, 3.572022E-2, 0.81276985, 6.377824E-2, 5.885638E-1, 6.632897E-2, 0.54765785 } };


correct_uj = { -1.00E+0, -7.50E-1, -6.25E-1, -5.00E-1, -3.75E-1, -2.50E-1, -1.25E-1, 0.00E+0, 1.25E-1, 2.50E-1, 3.75E-1, 5.00E-1, 6.25E-1, 7.50E-1, 1.00E+0 };

  REQUIRE( ranges::equal(std::get<0>(out),correct_uj,equal) );
  for ( size_t i = 0; i < totalSCR.size(); ++i ){
    REQUIRE( ranges::equal(correctFull_SCR[i],totalSCR[i],equal) );
  }


  enow = 8.7e-4;
  correctFull_SCR = { 
  {0,0,1.49960E-10, 1.888562E-2, 5.971460E-3, 24.4264402, 3.402949E-2, 1.17469513, 
      3.658022E-2, 1.07918228, 6.463824E-2, 0.60579686, 6.718897E-2, 5.604804E-1}, 
  {0,0,2.66768E-10, 2.518897E-2, 5.971460E-3, 24.9209926, 3.402949E-2, 1.09149952, 
      3.658022E-2, 1.01393880, 6.463824E-2, 0.59580015, 6.718897E-2, 0.55180918}, 
  {0,0,3.84396E-10, 3.023660E-2, 5.971460E-3, 25.1559189, 3.402949E-2, 1.05046954, 
      3.658022E-2, 0.98156948, 6.463824E-2, 0.59045769, 6.718897E-2, 0.54715066}, 
  {0,0,6.01340E-10, 3.781841E-2, 5.971460E-3, 25.3761659, 3.402949E-2, 1.00991276, 
      3.658022E-2, 0.94943283, 6.463824E-2, 0.58489496, 6.718897E-2, 0.54228481}, 
  {0,0,1.071832E-9, 5.049010E-2, 5.971460E-3, 25.5747710, 3.402949E-2, 0.96989503, 
      3.658022E-2, 0.91757449, 6.463824E-2, 5.791191E-1, 6.718897E-2, 0.53721789}, 
  {0,0,2.429734E-9, 7.601891E-2, 5.971460E-3, 25.7422830, 3.402949E-2, 0.93047797, 
      3.658022E-2, 0.88603792, 6.463824E-2, 0.57313749, 6.718897E-2, 0.53195635}, 
  {0,0,1.013520E-8, 0.15525825, 5.971460E-3, 25.8657657, 3.402949E-2, 0.89171883, 
      3.658022E-2, 8.548643E-1, 6.463824E-2, 5.669577E-1, 6.718897E-2, 0.52650687}, 
  {0,0,3.420730E-3, 34.9627783, 5.971460E-3, 25.9273347, 3.402949E-2, 0.85367047, 
      3.658022E-2, 0.82409246, 6.463824E-2, 0.56058752, 6.718897E-2, 0.52087629}, 
  {0,0,3.420730E-3, 36.0696794, 5.971460E-3, 25.9019750, 3.402949E-2, 0.81638133, 
      3.658022E-2, 0.79375888, 6.463824E-2, 0.55403488, 6.718897E-2, 0.51507165}, 
  {0,0,3.420730E-3, 37.2413495, 5.971460E-3, 25.7542270, 3.402949E-2, 0.77989539, 
      3.658022E-2, 0.76389759, 6.463824E-2, 0.54730789, 6.718897E-2, 0.50910014}, 
  {0,0,3.420730E-3, 38.4558656, 5.971460E-3, 25.4330763, 3.402949E-2, 0.74425219, 
      3.658022E-2, 0.73454021, 6.463824E-2, 0.54041479, 6.718897E-2, 0.50296908}, 
  {0,0,3.420730E-3, 39.6564776, 5.971460E-3, 24.8639574, 3.402949E-2, 0.70948689, 
      3.658022E-2, 7.057159E-1, 6.463824E-2, 0.53336396, 6.718897E-2, 0.49668595}, 
  {0,0,3.420730E-3, 40.7052474, 5.971460E-3, 23.9361733, 3.402949E-2, 0.67563029, 
      3.658022E-2, 0.67745136, 6.463824E-2, 0.52616386, 6.718897E-2, 0.49025831}, 
  {0,0,3.420730E-3, 41.2609859, 5.971460E-3, 22.4834003, 3.402949E-2, 0.63843637, 
      3.658022E-2, 0.64977085, 6.463824E-2, 0.51577031, 6.718897E-2, 0.48369385}, 
  {0,0,3.420730E-3, 35.4691371, 5.971460E-3, 16.8934777, 3.402949E-2, 0.56451023, 
      3.658022E-2, 0.58997438, 6.463824E-2, 0.49357884, 6.718897E-2, 4.646163E-1} };
    out = mu_ep(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
    uj = std::get<0>(out);
    totalSCR = std::get<1>(out);


  REQUIRE( ranges::equal(std::get<0>(out),correct_uj,equal) );
  for ( size_t i = 0; i < totalSCR.size(); ++i ){
    REQUIRE( ranges::equal(correctFull_SCR[i],totalSCR[i],equal) );
  }


  enow = 7.2e-3;
  correctFull_SCR = {
  { 0, 0, 1.241050E-9, 5.013555E-3, 4.649270E-3, 15.5388696, 9.750730E-3, 
    16.9464813, 1.230146E-2, 14.9667781, 4.035949E-2, 1.54691260, 4.291022E-2, 
    1.32791341, 7.096824E-2, 0.46800709, 7.351897E-2, 4.286185E-1 },
  { 0, 0, 2.207738E-9, 6.686902E-3, 4.649270E-3, 16.5143181, 9.750730E-3, 
    18.6348420, 1.230146E-2, 16.3762003, 4.035949E-2, 1.42130813, 4.291022E-2, 
    1.22730694, 7.096824E-2, 0.46558795, 7.351897E-2, 0.42764776 },
  { 0, 0, 3.181211E-9, 8.026895E-3, 4.649270E-3, 17.0759477, 9.750730E-3, 
    18.9153492, 1.230146E-2, 17.1479632, 4.035949E-2, 1.35029946, 4.291022E-2, 
    1.16832078, 7.096824E-2, 0.46284311, 7.351897E-2, 0.42554939 },
  { 0, 0, 4.976609E-9, 1.003964E-2, 4.649270E-3, 17.6986506, 9.750730E-3, 
    19.6323369, 1.230146E-2, 17.9686976, 4.035949E-2, 1.27524130, 4.291022E-2, 
    1.10577501, 7.096824E-2, 0.45909668, 7.351897E-2, 0.42239408 },
  { 0, 0, 8.870331E-9, 1.340361E-2, 4.649270E-3, 18.3942490, 9.750730E-3, 
    20.4372365, 1.230146E-2, 18.2881934, 4.035949E-2, 1.19722302, 4.291022E-2, 
    1.04056017, 7.096824E-2, 0.45437327, 7.351897E-2, 0.41820551 },
  { 0, 0, 2.010814E-8, 2.018082E-2, 4.649270E-3, 19.1779896, 9.750730E-3, 
    21.3495186, 1.230146E-2, 18.2881934, 4.035949E-2, 1.11732153, 4.291022E-2, 
    9.735615E-1, 7.096824E-2, 0.44870373, 7.351897E-2, 0.41301494 },
  { 0, 0, 8.387749E-8, 4.121745E-2, 4.649270E-3, 20.0699043, 9.750730E-3, 
    22.3952316, 1.230146E-2, 18.2881934, 4.035949E-2, 1.01932280, 4.291022E-2, 
    0.90301708, 7.096824E-2, 0.44200608, 7.351897E-2, 4.068608E-1 },
  { 0, 0, 2.098541E-3, 12.5936173, 4.649270E-3, 21.0968669, 9.750730E-3, 
    23.6101325, 1.230146E-2, 18.2881933, 4.035949E-2, 0.92026976, 4.291022E-2, 
    8.270573E-1, 7.096824E-2, 0.43181025, 7.351897E-2, 0.39868194 },
  { 0, 0, 2.098541E-3, 12.7606090, 4.649270E-3, 22.2957788, 9.750730E-3, 
    25.0448174, 1.230146E-2, 18.2881933, 4.035949E-2, 0.82225828, 4.291022E-2, 
    0.75131328, 7.096824E-2, 0.42009618, 7.351897E-2, 3.884365E-1 },
  { 0, 0, 2.098541E-3, 12.8750256, 4.649270E-3, 23.7185889, 9.750730E-3, 
    26.7735131, 1.230146E-2, 18.2881932, 4.035949E-2, 0.72709482, 4.291022E-2, 
    0.67694342, 7.096824E-2, 4.070011E-1, 7.351897E-2, 3.768991E-1 },
  { 0, 0, 2.098541E-3, 12.8950960, 4.649270E-3, 25.4401723, 9.750730E-3, 
    28.9098936, 1.230146E-2, 18.2881932, 4.035949E-2, 0.63630238, 4.291022E-2, 
    0.60496396, 7.096824E-2, 0.39267525, 7.351897E-2, 0.36420154 },
  { 0, 0, 2.098541E-3, 12.7463067, 4.649270E-3, 27.5695971, 9.750730E-3, 
    31.6369011, 1.230146E-2, 18.2881931, 4.035949E-2, 0.55109407, 4.291022E-2, 
    0.53623168, 7.096824E-2, 0.37668418, 7.351897E-2, 3.504855E-1 },
  { 0, 0, 2.098541E-3, 12.2901140, 4.649270E-3, 30.2572090, 9.750730E-3, 
    35.2635396, 1.230146E-2, 18.2881930, 4.035949E-2, 0.46784848, 4.291022E-2, 
    4.714344E-1, 7.096824E-2, 0.35277107, 7.351897E-2, 0.33082817 } ,
  { 0, 0, 2.098541E-3, 11.2571720, 4.649270E-3, 33.6142948, 9.750730E-3, 
    40.3029367, 1.230146E-2, 18.2881929, 4.035949E-2, 0.38183412, 4.291022E-2, 
    0.39905837, 7.096824E-2, 0.32671478, 7.351897E-2, 0.30709246 } ,
  { 0, 0, 2.098541E-3, 4.95869394, 4.649270E-3, 7.26804237, 9.750730E-3, 
    3.04183145, 1.102610E-2, 1.61005652, 1.166378E-2, 1.22873834, 1.198262E-2, 
    1.08196621, 1.214204E-2, 1.01699197, 1.222175E-2, 0.98636463, 1.226161E-2, 
    0.97148904, 1.228153E-2, 0.96415743, 1.229150E-2, 0.96051784, 1.229648E-2, 
    0.95870455, 1.229897E-2, 0.95779952, 1.230022E-2, 9.573476E-1, 1.230084E-2, 
    0.95712155, 1.230115E-2, 0.95700874, 1.230131E-2, 0.95695215, 1.230138E-2, 
    0.95692387, 1.230142E-2, 0.95690972, 1.230144E-2, 0.95690283, 1.230145E-2, 
    9.568992E-1, 1.230146E-2, 0.95689739, 1.230146E-2, 0.95689666, 1.230146E-2, 
    9.568963E-1, 1.230146E-2, 18.2881922, 2.633047E-2, 1.36312085, 4.035949E-2, 
    0.21758541, 4.291022E-2, 0.25315867, 7.096824E-2, 0.27101991, 7.351897E-2, 0.25545164} } ;
  out = mu_ep(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
  uj = std::get<0>(out);
  totalSCR = std::get<1>(out);


  REQUIRE( ranges::equal(std::get<0>(out),correct_uj,equal) );
  for ( size_t i = 0; i < totalSCR.size(); ++i ){
    REQUIRE( ranges::equal(correctFull_SCR[i],totalSCR[i],equal) );
  }

*/


  enow = 8.6e-1;
  std::vector<std::vector<double>> correctFull_SCR = { { 0, 0, 1.482365E-7, 2.312238E-3, 0.79368103, 3.730728E-3, 0.79623176, 3.655504E-3, 0.82428978, 2.921107E-3, 0.82684051, 2.862101E-3, 0.85489854, 2.286195E-3, 0.85744927, 2.239937E-3, 0.86255073, 1.987217E-3, 0.86510146, 1.799419E-3, 0.89315949, 6.036890E-4, 0.89571022, 5.466214E-4, 0.92376824, 1.833259E-4, 0.92631897, 1.659910E-4 }, 
{ 0, 0, 2.637020E-7, 3.083981E-3, 0.79368103, 9.403672E-3, 0.79623176, 9.227068E-3, 0.82428978, 7.486887E-3, 0.82684051, 7.345700E-3, 0.85489854, 5.955330E-3, 0.85744927, 5.842594E-3, 0.86255073, 5.197157E-3, 0.86510146, 4.712225E-3, 0.89315949, 1.603705E-3, 0.89571022, 1.453969E-3, 0.92376824, 4.944690E-4, 0.92631897, 4.482725E-4 }, 
{ 0, 0, 3.799780E-7, 3.701980E-3, 0.79368103, 0.01498382, 0.79623176, 0.01471285, 0.82428978, 0.01203002, 0.82684051, 0.01181127, 0.85489854, 9.647091E-3, 0.85744927, 9.470764E-3, 0.86255073, 8.435686E-3, 0.86510146, 7.653625E-3, 0.89315949, 2.623430E-3, 0.89571022, 2.380006E-3, 0.92376824, 8.150289E-4, 0.92631897, 7.393425E-4 }, 
{ 0, 0, 5.944283E-7, 4.630250E-3, 0.79368103, 0.02394515, 0.79623176, 0.02352887, 0.82428978, 0.01938720, 0.82684051, 0.01904776, 0.85489854, 0.01567384, 0.85744927, 0.01539760, 0.86255073, 0.01373295, 0.86510146, 0.01246800, 0.89315949, 4.304263E-3, 0.89571022, 3.907370E-3, 0.92376824, 1.347347E-3, 0.92631897, 1.222984E-3 }, 
{ 0, 0, 1.059512E-6, 6.181690E-3, 0.79368103, 0.03839740, 0.79623176, 0.03775692, 0.82428978, 0.03135235, 0.82684051, 0.03082469, 0.85489854, 0.02555451, 0.85744927, 0.02512084, 0.86255073, 0.02243470, 0.86510146, 0.02038167, 0.89315949, 7.086564E-3, 0.89571022, 6.437211E-3, 0.92376824, 2.235007E-3, 0.92631897, 2.029957E-3 }, 
{ 0, 0, 2.401806E-6, 9.307269E-3, 0.79368103, 0.06182400, 
0.79623176, 0.06083666, 0.82428978, 0.05091179, 0.82684051, 0.05008964, 
0.85489854, 0.04183711, 0.85744927, 0.04115450, 0.86255073, 0.03680261, 
0.86510146, 0.03345681, 0.89315949, 0.01171568, 0.89571022, 0.01064889, 
0.92376824, 3.722664E-3, 0.92631897, 3.383189E-3 }, 
{ 0, 0, 1.001870E-5, 0.01900873, 0.79368103, 0.10003529, 
0.79623176, 0.09850953, 0.82428978, 0.08308778, 0.82684051, 0.08180302, 
0.85489854, 0.06883954, 0.85744927, 0.06776147, 0.86255073, 0.06067636, 
0.86510146, 0.05519649, 0.89315949, 0.01946577, 0.89571022, 0.01770445, 
0.92376824, 6.231258E-3, 0.92631897, 5.666436E-3 }, 
{ 0, 0, 0.7656230, 0.19100791, 0.79368103, 0.16285078, 
0.79623176, 0.16048557, 0.82428978, 0.1364386, 0.82684051, 0.13442323, 
0.85489854, 0.11397547, 0.85744927, 0.11226536, 0.86255073, 0.1006602, 
0.86510146, 0.09162954, 0.89315949, 0.03254318, 0.89571022, 0.02961708, 
0.92376824, 0.01049413, 0.92631897, 9.548576E-3 }, 
{ 0, 0, 0.7656230, 0.31068023, 0.79368103, 0.26715586, 
0.79623176, 0.2634743, 0.82428978, 0.22580516, 0.82684051, 0.22262763, 
0.85489854, 0.19019717, 0.85744927, 0.18746851, 0.86255073, 0.16831223, 
0.86510146, 0.15331296, 0.89315949, 0.05483388, 0.89571022, 0.04993438, 
0.92376824, 0.01781014, 0.92631897, 0.01621481 }, 
{ 0, 0, 0.7656230, 0.51027216, 0.79368103, 0.4426850, 
0.79623176, 0.43692326, 0.82428978, 0.37754883, 0.82684051, 0.3725043, 
0.85489854, 0.32068117, 0.85744927, 0.31629193, 0.86255073, 0.2843484, 
0.86510146, 0.25917848, 0.89315949, 0.09334404, 0.89571022, 0.08505527, 
0.92376824, 0.03053245, 0.92631897, 0.02781315 }, 
{ 0, 0, 0.7656230, 0.84919111, 0.79368103, 0.74361267, 
0.79623176, 0.73452899, 0.82428978, 0.64013854, 0.82684051, 0.63205203, 
0.85489854, 0.54835143, 0.85744927, 0.54120882, 0.86255073, 0.48719505, 
0.86510146, 0.44436017, 0.89315949, 0.16113707, 0.89571022, 0.1469152, 
0.92376824, 0.05306477, 0.92631897, 0.04836437 }, 
{ 0, 0, 0.7656230, 1.44002824, 0.79368103, 1.27385932, 
0.79623176, 1.25939410, 0.82428978, 1.10749519, 0.82684051, 1.09434671, 
0.85489854, 0.95698896, 0.85744927, 0.94516038, 0.86255073, 0.85195929, 
0.86510146, 0.77755973, 0.89315949, 0.28384959, 0.89571022, 0.25894261, 
0.92376824, 0.09406406, 0.92631897, 0.08577297 }, 
{ 0, 0, 0.7656230, 2.51390707, 0.79368103, 2.25023510, 
0.79623176, 2.22688835, 0.82428978, 1.97801436, 0.82684051, 1.95615749, 
0.85489854, 1.72490562, 0.85744927, 1.70474545, 0.86255073, 1.53867963, 
0.86510146, 1.40521534, 0.89315949, 0.51621972, 0.89571022, 0.47115999, 
0.92376824, 0.1719780, 0.92631897, 0.15687751 }, 
{ 0, 0, 0.7656230, 4.61756506, 0.79368103, 4.19959296, 
0.79623176, 4.16139060, 0.82428978, 3.74288879, 0.82684051, 3.70518731, 
0.85489854, 3.29754139, 0.85744927, 3.26127482, 0.86255073, 2.94748363, 
0.86510146, 2.69350989, 0.89315949, 0.99484449, 0.89571022, 0.9083311, 
0.92376824, 0.33238682, 0.92631897, 0.3032333 }, 
{ 0, 0, 0.7656230, 0.46448037, 0.79368103, 1.61636105, 
0.79623176, 1.57562571, 0.82428978, 0.13150214, 0.82684051, 0.05524015, 
0.84086953, 1.77410016, 0.84788404, 14.5912972, 0.85489854, 203.104781, 
0.85489855, 0, 0.85489856, 0, 0.85489858, 0, 
0.85489862, 0, 0.8548987, 0, 0.85489886, 0, 
0.85489917, 0, 0.85489979, 0, 0.85490104, 0, 
0.85490353, 0, 0.85490851, 0, 0.85491847, 0, 
0.8549384, 0, 0.85497826, 0, 0.85505797, 0, 
0.85521739, 0, 0.85553623, 0, 0.85617391, 0, 
0.85744927, 0, 0.86255073, 0, 0.8638261, 0, 
0.86446378, 0, 0.86478262, 0, 0.86494204, 0, 
0.86502175, 0, 0.86506161, 0, 0.86508154, 0, 
0.8650915, 0, 0.86509648, 0, 0.86509897, 0, 
0.86510022, 0, 0.86510084, 0, 0.86510115, 0, 
0.86510131, 0, 0.86510139, 0, 0.86510143, 0, 
0.86510145, 0, 0.86510146, 167.277480, 0.87211597, 9.16573122, 
0.87913048, 0.84601494, 0.89315949, 0.01496978, 0.89571022, 0.03244915, 
0.92376824, 0.13304018, 0.92631897, 0.12359235 } };
  auto out = mu_ep(enow,tev,tol,lat,iinc,lasym,alphas,betas,sab,az,sigma_b,sigma_b2,teff);
  auto uj = std::get<0>(out);
  auto totalSCR = std::get<1>(out);


  //REQUIRE( ranges::equal(std::get<0>(out),correct_uj,equal) );
  for ( size_t i = 0; i < totalSCR.size(); ++i ){
    //std::cout << (totalSCR[i]|ranges::view::all) << std::endl;
    //REQUIRE( ranges::equal(correctFull_SCR[i],totalSCR[i],equal) );
  }








  } // GIVEN



} // TEST CASE



