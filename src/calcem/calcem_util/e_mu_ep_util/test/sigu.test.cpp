#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "calcem/calcem_util/e_mu_ep_util/sigu.h"
#include "generalTools/testing.h"

TEST_CASE( "begin sigu (113,116)" ){
  GIVEN( "inputs" ){
    int jbeta = -7, lat = 1, iinc = 2, 
        lasym = 0;

    double tev = 1.5e-5, az = 11.9, tevz = 2.53e-2, 
      az2 = 0.0, teff2 = 0.0, sb = 5.53, sb2 = 0.0,
      teff = 6.14e-2, tolin = 5e-2, u,
      e = 1.0000000474974513E-003;
    std::vector<double> boundXsVec {sb,sb2};

    std::vector<double> alpha { 1.1, 2.2, 3.3, 4.5, 5.8 },
      beta { 0.1, 0.2, 1.3, 1.4, 2.5, 2.6, 3.7 }, x(20,0.0), y(20,0.0);
    std::vector<double> sab(alpha.size()*beta.size());
    for ( size_t i = 0; i < alpha.size(); ++i ){
      for ( size_t j = 0; j < beta.size(); ++j ){
        sab[i*beta.size()+j] = 0.01*((j+1) + 0.1*(i+1));
      } 
    } 

    std::vector<double> cosines {-1.0,-0.8,-0.5,0.1,0.9}, correct_xVals(5), 
                        correct_yVals(5), correct_x(20,0.0), correct_y(20,0.0);

    WHEN( "lat = 1" ){
      correct_xVals = { 7.1395952E-4, 7.3838244E-4, 7.7664539E-4, 
                        3.5300000E-3, 3.5300000E-3 },
      correct_yVals = { 20707918735.446129, 21731148494.832615, 23594835158.224358, 0.0, 0.0 };
      THEN("x, y, and jbeta are correctly returned for each scattering cosine"){
        for (size_t i = 0; i < cosines.size(); ++i){
          correct_x[0] = correct_xVals[i];
          correct_y[0] = correct_yVals[i];
          initializeEpXS( jbeta, lat, x, y, e, tev, tevz, cosines[i], alpha, beta, sab, 
                      az, lasym, teff, boundXsVec, iinc);
          checkVec(x,correct_x);
          checkVec(x,correct_x);
          REQUIRE( jbeta == 1 );
        }
      } // THEN
    } // WHEN

    WHEN( "lat = 0" ){
      lat = 0;
      correct_xVals = { 7.1395952E-4, 7.3838244E-4, 7.7664539E-4, 9.4450005E-4, 
                        9.4450005E-4 };
      correct_yVals = { 157.26389831, 167.22962548, 185.61792063, 252.19972257, 
                        1223152.9616};
      THEN("x, y, and jbeta are correctly returned for each scattering cosine"){
        for (size_t i = 0; i < cosines.size(); ++i){
          correct_x[0] = correct_xVals[i];
          correct_y[0] = correct_yVals[i];
          initializeEpXS( jbeta, lat, x, y, e, tev, tevz, cosines[i], alpha, beta, sab, 
                      az, lasym, teff, boundXsVec, iinc);
          REQUIRE( ranges::equal(x, correct_x, equal) );
          REQUIRE( ranges::equal(y, correct_y, equal) );
          REQUIRE( jbeta == -7 );
        }
      } // THEN

    } // WHEN





  } // GIVEN

  GIVEN( "inputs 2" ){
    int jbeta = -7, lat, iinc = 2, lasym = 0;

    std::cout << std::setprecision(10) ;
    double e = 1.0e-5, tev = 2.55E-2, az = 0.99917,
      tevz = 2.53E-2, az2 = 0.0, teff2 = 0.0, sb = 163.7, sb2 = 0.0,
      teff = 0.1204, tolin = 5e-2, u = -1.0;
    std::vector<double> boundXsVec {sb,sb2};

    std::vector<double> alpha { 1.1, 2.2, 3.3, 4.5, 5.8 },
      beta { 0.1, 0.2, 1.3, 1.4, 2.5, 2.6, 3.7 }, x(20,0.0), y(20,0.0);

    std::vector<double> sab(alpha.size()*beta.size());
    for ( size_t i = 0; i < alpha.size(); ++i ){
      for ( size_t j = 0; j < beta.size(); ++j ){
        sab[i*beta.size()+j] = 0.01*((j+1) + 0.1*(i+1));
      } 
    } 

    std::vector<double> cosines { -1.0, -0.8, -0.5, 0.1, 0.9 },
      correct_xVals(5), correct_yVals(5), correct_x(20,0.0), correct_y(20,0.0);



    WHEN( "lat = 1" ){
      lat = 1;
      correct_xVals = { 1.7236820E-12, 2.69447510E-12, 6.9118685E-12, 2.54E-3, 2.54E-3 },
      correct_yVals = { 1.23006627, 1.5379422, 2.46320561, 49048.230969, 49040.67653};
 
      THEN("x, y, and jbeta are correctly returned for each scattering cosine"){
          std::cout.precision(15);
        float tolerance = 1e-5;
        for (size_t i = 0; i < cosines.size(); ++i){
          correct_x[0] = correct_xVals[i];
          correct_y[0] = correct_yVals[i];
          initializeEpXS( jbeta, lat, x, y, e, tev, tevz, cosines[i], alpha, beta, sab, 
                      az, lasym, teff, boundXsVec, iinc);

          checkVec(x,correct_x);
          checkVec(y,correct_y,tolerance);
          REQUIRE( jbeta == 1 );
        }
      } // THEN
    } // WHEN


    WHEN( "lat = 0" ){
      lat = 0;
      cosines = { -1.0, -0.8, -0.5, 0.1, 0.9 },
      correct_xVals = { 1.7236820E-12, 2.6944751E-12, 6.91186850E-12, 2.56E-3, 
                        2.56E-3 };
      correct_yVals = { 1.22991257451, 1.53775006367, 2.46289784081, 49221.6483, 
                        49214.0986};

      THEN("x, y, and jbeta are correctly returned for each scattering cosine"){
        float tolerance = 1e-5;
        for (size_t i = 0; i < cosines.size(); ++i){
          correct_x[0] = correct_xVals[i];
          correct_y[0] = correct_yVals[i];
          initializeEpXS( jbeta, lat, x, y, e, tev, tevz, cosines[i], alpha, beta, sab, 
                      az, lasym, teff, boundXsVec, iinc);
          checkVec(x,correct_x);
          checkVec(y,correct_y,tolerance);
          REQUIRE( jbeta == 1 );
        }
      } // THEN
    } // WHEN
  } // GIVEN
} // TEST CASE




TEST_CASE( "sigu" ){

  int lasym = 0, lat = 1, iinc = 2, nemax = 60;
  double e = 1e-5, tev = 2.55e-2, az = 0.99917, sb = 4.0, sb2 = 0.0, teff = 0.12, tolin = 5e-2, u = 0.2;
  std::vector<double> boundXsVec {sb,sb2};

  std::vector<double> alphas { 1.1, 2.2, 3.3, 4.5, 5.8 },
                       betas { 0.1, 0.2, 1.3, 1.4, 2.5, 2.6, 3.7 };
  std::vector<double> sab(alphas.size()*betas.size());
  for ( size_t i = 0; i < alphas.size(); ++i ){
    for ( size_t j = 0; j < betas.size(); ++j ){
      sab[i*betas.size()+j] = 0.01*((j+1) + 0.1*(i+1));
    } 
  } 

  GIVEN( "various scattering cosines" ){
    WHEN( "u = -1.0" ){
      u = -1.0;
      std::vector<double> s1(nemax,0.0),s2(nemax,0.0),s3(2*nemax,0.0),
        correct_s {367.00063059, 51.0, 0.0, 0.0, 4.3091455E-13, 1.5028290E-2, 
        8.6182910E-013, 2.1253217E-2, 1.7236582E-012, 3.0056598E-2, 1.5472585E-7, 
        9.0062306982, 3.0944997E-7, 12.735395282, 6.1889821E-7, 18.005126622, 
        1.2377947E-6, 25.443528732, 2.4755877E-6, 35.913334585, 4.9511736E-6, 
        50.513936368, 9.9023454E-6, 67.508958284, 1.9804689E-5, 102.07193798, 
        3.9609376E-5, 146.70647404, 7.9218751E-5, 210.01613505, 1.5843750E-4, 
        300.05935520, 3.1687500E-4, 427.84044435, 6.3375000E-4, 608.02345148, 
        1.2675000E-3, 858.66585852, 2.5350000E-3, 1197.6157296, 5.0700000E-3, 
        1629.3457424, 1.2027500E-2, 2160.1978761, 1.8985000E-2, 2361.7853083, 
        3.2900000E-2, 2435.4047613, 3.5430000E-2, 2429.3914507, 6.3260000E-2, 
        1901.8474047, 6.5790000E-2, 1864.3607136, 7.9705000E-2, 1607.0867876, 
        8.6662500E-2, 1457.6959400, 9.0141250E-2, 1380.6181996, 9.1880625E-2, 
        1341.7985482, 9.2750313E-2, 1322.3552137, 9.3185157E-2, 1312.6295853, 
        9.3402579E-2, 1307.7663214, 9.3511290E-2, 1305.3346438, 9.3565645E-2, 
        1304.1188131, 9.3592823E-2, 1303.5108869, 9.3606412E-2, 1303.2069239, 
        9.3613206E-2, 1303.0549537, 9.3616603E-2, 1302.9789686, 9.3618302E-2, 
        1302.9409649, 9.3619151E-2, 1302.9219742, 9.3619576E-2, 1302.91246777, 
        9.3619788E-2, 1302.9077256, 9.3619894E-2, 1302.9053546, 9.3619947E-2, 
        1302.9041691, 9.3619974E-2, 1302.9035651, 9.3619987E-2, 1302.9032744, 
        9.3619994E-2, 1302.9031178, 9.3619997E-2, 1302.9030507, 9.3619999E-2, 
        1302.9030059, 9.3620000E-2, 12.967700565};
  
      sigu(e,u,tev,alphas,betas,sab,tolin,az,iinc,lat,lasym,boundXsVec,teff,s3);
      checkVec(correct_s,s3);

    } // WHEN 
  
    WHEN( "u = -0.2" ){
      u = -0.2;
      std::vector<double> s1(nemax,0.0),s2(nemax,0.0),s3(2*nemax,0.0),
      correct_s { 366.9823481, 51.0, 0.0, 0.0, 1.09931440E-11, 7.59057981E-2, 
      2.19862E-11, 0.107347032, 4.39725730E-11, 0.151811676, 1.54768090E-7, 
      9.00523391, 3.09492210E-7, 12.7320827, 6.18940440E-7, 17.9980862, 
      1.23783690E-6, 25.4304479, 2.47562980E-6, 35.8909269, 4.95121570E-6, 
      50.4783868, 9.90238750E-6, 67.4589504, 1.98047310E-5, 101.999639, 
      3.96094180E-5, 146.613401, 7.92187920E-5, 209.904019, 1.58437540E-4, 
      299.930970, 3.16875030E-4, 427.698924, 6.33750020E-4, 607.871970, 
      1.26750000E-3, 858.507689, 2.53500000E-3, 1197.45475, 5.07000000E-3, 
      1629.18740, 1.20275000E-2, 2160.05899, 1.89850000E-2, 2361.66359, 
      3.29000000E-2, 2435.32438, 3.54300000E-2, 2429.30824, 6.32600000E-2, 
      1901.75904, 6.57900000E-2, 1864.27301, 7.97050000E-2, 1607.00689, 
      8.66625000E-2, 1457.62248, 9.01412500E-2, 1380.54783, 9.18806250E-2, 
      1341.72979, 9.27503130E-2, 1322.28727, 9.31851570E-2, 1312.56206, 
      9.34025790E-2, 1307.69900, 9.35112900E-2, 1305.26743, 9.35656450E-2, 
      1304.05165, 9.35928230E-2, 1303.44375, 9.36064120E-2, 1303.13980, 
      9.36132060E-2, 1302.98784, 9.36166030E-2, 1302.91185, 9.36183020E-2, 
      1302.87385, 9.36191510E-2, 1302.85486, 9.36195760E-2, 1302.84536, 
      9.36197880E-2, 1302.84061, 9.36198940E-2, 1302.83824, 9.36199470E-2, 
      1302.83706, 9.36199740E-2, 1302.83645, 9.36199870E-2, 1302.83616, 
      9.36199940E-2, 1302.83601, 9.36199970E-2, 1302.83594, 9.36199990E-2, 
      1302.83590, 9.36200000E-2, 13.0751408 };
  
      sigu(e,u,tev,alphas,betas,sab,tolin,az,iinc,lat,lasym,boundXsVec,teff,s3);
      checkVec(correct_s,s3);
  
    } // WHEN

    WHEN( "u = 0.0" ){
      u = 0.0;
      std::vector<double> s1(nemax,0.0),s2(nemax,0.0),s3(2*nemax,0.0),
      correct_s {366.9781918, 48.0000000,  0.000000000, 0.00000000, 1.550293E-7, 
      9.01220481, 3.100586E-7, 12.7425038, 6.201172E-7, 18.0128293, 1.240234E-6, 
      25.4506370, 2.480468E-6, 35.9179996, 4.960937E-6, 50.5139815, 9.921875E-6, 
      67.2910661, 1.984375E-5, 102.080553, 3.968750E-5, 146.732016, 7.937500E-5, 
      210.081567, 1.587500E-4, 300.195528, 3.175000E-4, 428.087846, 6.350000E-4, 
      608.433126, 1.270000E-3, 859.295899, 2.540000E-3, 1198.51244, 5.070000E-3, 
      1629.14609, 1.202750E-2, 2160.02328, 1.898500E-2, 2361.63247, 3.290000E-2, 
      2435.30429, 3.543000E-2, 2429.28744, 6.326000E-2, 1901.73691, 6.579000E-2, 
      1864.25104, 7.970500E-2, 1606.98687, 8.666250E-2, 1457.60408, 9.014125E-2, 
      1380.53020, 9.188062E-2, 1341.71256, 9.275031E-2, 1322.27025, 9.318515E-2, 
      1312.54514, 9.340257E-2, 1307.68214, 9.351129E-2, 1305.25059, 9.356564E-2, 
      1304.03482, 9.359282E-2, 1303.42693, 9.360641E-2, 1303.12298, 9.361320E-2, 
      1302.97102, 9.361660E-2, 1302.89504, 9.361830E-2, 1302.85704, 9.361915E-2, 
      1302.83805, 9.361957E-2, 1302.82854, 9.361978E-2, 1302.82380, 9.361989E-2, 
      1302.82143, 9.361994E-2, 1302.82024, 9.361997E-2, 1302.81964, 9.361998E-2, 
      1302.81935, 9.361999E-2, 1302.81919, 9.361999E-2, 1302.81912, 9.361999E-2, 
      1302.81908, 9.362000E-2, 13.1022021 };
  
      sigu(e,u,tev,alphas,betas,sab,tolin,az,iinc,lat,lasym,boundXsVec,teff,s3);
      checkVec(correct_s,s3);
  
    } // WHEN

    WHEN( "u = 0.5" ){
      u = 0.5;
      std::vector<double> s1(nemax,0.0),s2(nemax,0.0),s3(2*nemax,0.0),
      correct_s {366.96642, 48.0, 0.0, 0.0, 1.550293E-7, 9.0105043, 3.100586E-7, 
      12.739061, 6.201172E-7, 18.005887, 1.240234E-6, 25.436839, 2.480468E-6, 
      35.891620, 4.960937E-6, 50.467627, 9.921875E-6, 67.223811, 1.984375E-5, 
      101.98653, 3.968750E-5, 146.62358, 7.937500E-5, 209.96683, 1.587500E-4, 
      300.07890, 3.175000E-4, 427.97125, 6.350000E-4, 608.31738, 1.270000E-3, 
      859.18165, 2.540000E-3, 1198.4008, 5.070000E-3, 1629.0395, 1.202750E-2, 
      2159.9321, 1.898500E-2, 2361.5534, 3.290000E-2, 2435.2540, 3.543000E-2, 
      2429.2354, 6.326000E-2, 1901.6814, 6.579000E-2, 1864.1960, 7.970500E-2, 
      1606.9367, 8.666250E-2, 1457.5580, 9.014125E-2, 1380.4860, 9.188062E-2, 
      1341.6694, 9.275031E-2, 1322.2276, 9.318515E-2, 1312.5027, 9.340257E-2, 
      1307.6399, 9.351129E-2, 1305.2084, 9.356564E-2, 1303.9926, 9.359282E-2, 
      1303.3848, 9.360641E-2, 1303.0808, 9.361320E-2, 1302.9289, 9.361660E-2, 
      1302.8529, 9.361830E-2, 1302.8149, 9.361915E-2, 1302.7959, 9.361957E-2, 
      1302.7864, 9.361978E-2, 1302.7816, 9.361989E-2, 1302.7793, 9.361994E-2, 
      1302.7781, 9.361997E-2, 1302.7775, 9.361998E-2, 1302.7772, 9.361999E-2, 
      1302.7770, 9.361999E-2, 1302.7770, 9.361999E-2, 1302.7769, 9.362000E-2, 
      13.170209};
  
      sigu(e,u,tev,alphas,betas,sab,tolin,az,iinc,lat,lasym,boundXsVec,teff,s3);
    
      checkVec(correct_s,s3);
    } // WHEN
  
  
    WHEN( "u = 0.9" ){
      u = 0.9;
      std::vector<double> s1(nemax,0.0),s2(nemax,0.0),s3(2*nemax,0.0),
      correct_s { 366.95684, 48.0, 0.0, 0.0, 1.5502930E-7, 9.0089633, 
      3.1005860E-7, 12.735752, 6.2011720E-7, 17.998586, 1.2402344E-6, 25.420179, 
      2.4804688E-6, 35.852410, 4.9609375E-6, 50.377160, 9.9218750E-6, 67.067913, 
      1.9843750E-5, 101.80190, 3.9687500E-5, 146.46151, 7.9375000E-5, 209.82774, 
      1.5875000E-4, 299.95596, 3.1750000E-4, 427.85901, 6.3500000E-4, 608.21238, 
      1.2700000E-3, 859.08202, 2.5400000E-3, 1198.3061, 5.0700000E-3, 1628.9506, 
      1.2027500E-2, 2159.8573, 1.8985000E-2, 2361.4888, 3.2900000E-2, 2435.2138, 
      3.5430000E-2, 2429.1938, 6.3260000E-2, 1901.6370, 6.5790000E-2, 1864.1519, 
      7.9705000E-2, 1606.8965, 8.6662500E-2, 1457.5210, 9.0141250E-2, 1380.4506, 
      9.1880625E-2, 1341.6348, 9.2750313E-2, 1322.1934, 9.3185157E-2, 1312.4688, 
      9.3402579E-2, 1307.6060, 9.3511290E-2, 1305.1746, 9.3565645E-2, 1303.9589, 
      9.3592823E-2, 1303.3510, 9.3606412E-2, 1303.0471, 9.3613206E-2, 1302.8951, 
      9.3616603E-2, 1302.8191, 9.3618302E-2, 1302.7811, 9.3619151E-2, 1302.7621, 
      9.3619576E-2, 1302.7526, 9.3619788E-2, 1302.7479, 9.3619894E-2, 1302.7455, 
      9.3619947E-2, 1302.7443, 9.3619974E-2, 1302.7437, 9.3619987E-2, 1302.7434, 
      9.3619994E-2, 1302.7433, 9.3619997E-2, 1302.7432, 9.3619999E-2, 1302.7432, 
      9.3620000E-2, 13.224979 };
  
      sigu(e,u,tev,alphas,betas,sab,tolin,az,iinc,lat,lasym,boundXsVec,teff,s3);
  
      checkVec(correct_s,s3);

    } // WHEN
  } // GIVEN

  GIVEN( "varying initial energies" ){
    u = -0.2;
    WHEN( "e = 1e-6" ){
      e = 1e-6;
      std::vector<double> s1(nemax,0.0),s2(nemax,0.0),s3(2*nemax,0.0),
      correct_s { 1160.21228, 52.0, 0.0, 0.0, 1.0993144E-12, 7.3169271E-2, 
      2.1986287E-12,0.1034769,4.3972573E-12, 0.1463386, 7.7229124E-8, 19.375903, 
      1.5445385E-7, 27.370602, 3.0890330E-7, 38.603630, 6.1780220E-7, 54.146871, 
      1.2356000E-6, 76.077473, 2.4711957E-6, 110.53582, 4.9423870E-6, 158.66922, 
      9.8847697E-6, 227.20450, 1.9769535E-5, 325.02853, 3.9539066E-5, 464.70894, 
      7.9078127E-5, 664.04735, 1.5815625E-4, 948.08267, 3.1631250E-4, 1351.4624, 
      6.3262500E-4, 1920.4700, 1.2652500E-3, 2712.1530, 2.5305000E-3, 3782.9646, 
      5.0610000E-3, 5147.2529, 1.2018500E-2, 6828.0584, 1.8976000E-2, 7466.3882, 
      3.2891000E-2, 7700.0700, 3.5421000E-2, 7681.1214, 6.3251000E-2, 6013.4105, 
      6.5781000E-2, 5894.8943, 7.9696000E-2, 5081.4686, 8.6653500E-2, 4609.1250, 
      9.0132250E-2, 4365.4168, 9.1871625E-2, 4242.6745, 9.2741313E-2, 4181.1973, 
      9.3176157E-2, 4150.4461, 9.3393579E-2, 4135.0691, 9.3502290E-2, 4127.3805, 
      9.3556645E-2, 4123.5362, 9.3583823E-2, 4121.6140, 9.3597412E-2, 4120.6529, 
      9.3604206E-2, 4120.1724, 9.3607603E-2, 4119.9321, 9.3609302E-2, 4119.8120, 
      9.3610151E-2, 4119.7519, 9.3610576E-2, 4119.7219, 9.3610788E-2, 4119.7069, 
      9.3610894E-2, 4119.6994, 9.3610947E-2, 4119.6956, 9.3610974E-2, 4119.6937, 
      9.3610987E-2, 4119.6928, 9.3610994E-2, 4119.6923, 9.3610997E-2, 4119.6921, 
      9.3610999E-2, 4119.6919, 9.3611000E-2, 41.407705 };
  
      sigu(e,u,tev,alphas,betas,sab,tolin,az,iinc,lat,lasym,boundXsVec,teff,s3);
      checkVec(correct_s,s3); 

    } // WHEN 


    WHEN( "e = 1e-4" ){
      e = 1e-4;
      std::vector<double> s1(nemax,0.0),s2(nemax,0.0),s3(2*nemax,0.0),
      correct_s { 116.331309, 50.0, 0.0, 0.0, 1.0993144E-10, 7.8869838E-2, 
      2.1986287E-10,0.1115388,4.3972573E-10, 0.1577397, 3.1538109E-7, 4.2243601, 
      6.3032246E-7, 5.9718590, 1.2602052E-6, 8.4433581, 2.5199706E-6, 11.937663, 
      5.0395014E-6, 16.875584, 1.0078563E-5, 23.846584, 2.0156687E-5, 33.665075, 
      4.0312935E-5, 47.403646, 8.0625430E-5, 65.932602, 1.6125042E-4, 94.704073, 
      3.2250040E-4, 136.10709, 6.4500037E-4, 193.90966, 1.2900003E-3, 274.08611, 
      2.5800002E-3, 382.30784, 5.1600000E-3, 519.79972, 1.2117500E-2, 685.65989, 
      1.9075000E-2, 748.62269, 3.2990000E-2, 771.18860, 3.5520000E-2, 769.20906, 
      6.3350000E-2, 601.83575, 6.5880000E-2, 589.95686, 7.9795000E-2, 508.48390, 
      8.6752500E-2, 461.19537, 9.0231250E-2, 436.80013, 9.1970625E-2, 424.51429, 
      9.2840313E-2, 418.36092, 9.3275157E-2, 415.28301, 9.3492579E-2, 413.74392, 
      9.3601290E-2, 412.97437, 9.3655645E-2, 412.58959, 9.3682823E-2, 412.39720, 
      9.3696412E-2, 412.30101, 9.3703206E-2, 412.25291, 9.3706603E-2, 412.22887, 
      9.3708302E-2, 412.21684, 9.3709151E-2, 412.21083, 9.3709576E-2, 412.20782, 
      9.3709788E-2, 412.20632, 9.3709894E-2, 412.20557, 9.3709947E-2, 412.20520, 
      9.3709974E-2, 412.20500, 9.3709987E-2, 412.20491, 9.3709994E-2, 412.20486, 
      9.3709997E-2, 412.20484, 9.3709999E-2, 412.20483, 9.3710000E-2, 4.1143235 };
  
      sigu(e,u,tev,alphas,betas,sab,tolin,az,iinc,lat,lasym,boundXsVec,teff,s3);
    
      checkVec(correct_s, s3);

    } // WHEN 

    WHEN( "e = 1.0" ){
      e = 1.0;
      std::vector<double> s1(nemax,0.0),s2(nemax,0.0),s3(2*nemax,0.0),
      correct_s { 0.3267346636, 39.0, 0.0, 0.0, 1.0993144E-6, 1.7065632E-3, 
      2.1986287E-6, 2.4132316E-3, 4.3972573E-6, 3.4123967E-3, 6.1417254E-5, 
      1.2737708E-2, 1.1843725E-4, 1.7676773E-2, 2.3247725E-4, 2.4741423E-2, 
      4.6055724E-4, 3.4773216E-2, 9.1671723E-4, 4.8951509E-2, 1.8290372E-3, 
      6.8909260E-2, 3.6536772E-3, 9.6858626E-2, 7.3029571E-3, 0.1356552797, 
      1.4601517E-2, 0.1885250681, 2.9198636E-2, 0.2574542078, 5.8392874E-2, 
      0.3369416490, 0.1167813500, 0.3952344790, 0.2335583000, 0.3477950173, 
      0.4671122000, 0.1468085946, 0.5838891500, 8.2364475E-2, 0.7006661000, 
      4.3525430E-2, 0.7590545800, 3.1085045E-2, 0.8174430500, 2.1980034E-2, 
      0.8758315300, 1.5404492E-2, 0.9342200000, 1.0710479E-2, 0.9367500000, 
      1.0541368E-2, 0.9645800000, 8.8407166E-3, 0.9671100000, 8.6997624E-3, 
      0.9949400000, 7.2839531E-3, 0.9974700000, 7.1667510E-3, 1.0025300000, 
      6.4162975E-3, 1.0050600000, 5.8383689E-3, 1.0189750000, 3.4732671E-3, 
      1.0328900000, 2.0655302E-3, 1.0354200000, 1.8792206E-3, 1.0493350000, 
      1.1171059E-3, 1.0632500000, 6.6384239E-4, 1.0657800000, 6.0388368E-4, 
      1.0796950000, 3.5871989E-4, 1.0936100000, 2.1301906E-4 };
  
      sigu(e,u,tev,alphas,betas,sab,tolin,az,iinc,lat,lasym,boundXsVec,teff,s3);
      checkVec(correct_s,s3);
    

    } // WHEN 
 
  } // GIVEN



  GIVEN( "Realistic-ish example" ){
      
    double tev = 2.5507297688e-2, tol = 0.05;
    std::vector<double> 
      alphas { 1.1, 2.2, 3.3, 4.5, 5.8 },
      betas { 0.1, 0.2, 1.3, 1.4, 2.5, 2.6, 3.7 },
      sab {-0.18259619, -0.30201347, -3.93654779, -3.98809174, -4.33545607, 
      -4.39515402,-5.88934921,-0.76225291,-0.81658341,-3.14161459,-3.30566186, 
      -3.90554652,-3.96233362,-5.23696660,-1.19182884,-1.23155471,-2.79610565, 
      -2.95633099,-3.74989225,-3.80837585,-4.93373911,-1.58342860,-1.61310713, 
      -2.71233943,-2.84291608,-3.69699590,-3.75199349,-4.77433858,-1.96121202, 
      -1.98720663,-2.78454600,-2.88531460,-3.71288120,-3.77142141,-4.71158392 };

    double az = 0.99917, sigma_b = 163.72792237, sigma_b2 = 0.0, 
           teff = 0.120441926;
    int imax = 20, lat = 0, iinc = 2, lasym = 0;
    int nbin = 2;
    std::vector<double> boundXsVec {sigma_b,sigma_b2};


    u = -1.0;
    e = 1e-5;
    int nemax = 1000;
    std::vector<double> s1(nemax,0.0),s2(nemax,0.0),s3(2*nemax,0.0);

    WHEN( " " ){
      sigu(e,u,tev,alphas,betas,sab,tol,az,iinc,lat,lasym,boundXsVec,teff,s3);
      std::vector<double> 
      correct_s1 { 1961.39420, 0.0, 4.3092008E-13, 8.6184015E-13, 1.7236803E-12, 
      1.9500396E-8, 3.8999068E-8, 7.7996412E-8, 1.5599110E-7, 3.1198047E-7, 
      6.2395921E-7, 1.2479167E-6, 2.4958317E-6, 4.9916616E-6, 9.9833214E-6, 
      1.9966641E-5, 3.9933281E-5, 7.9866561E-5, 1.5973312E-4, 3.1946623E-4, 
      6.3893245E-4, 1.2778649E-3, 2.5557298E-3, 5.1114595E-3, 5.1115666E-3, 
      5.1116736E-3, 5.1118877E-3, 5.1123158E-3, 5.1131721E-3, 5.1148846E-3, 
      5.1183097E-3, 5.1251598E-3, 5.1388600E-3, 5.1662604E-3, 5.2210612E-3, 
      5.3306629E-3, 5.5498662E-3, 5.9882729E-3, 6.8650862E-3, 8.6187128E-3, 
      0.0121259660, 0.0156332200, 0.0191404730, 0.0226477270, 0.0261549800, 
      0.0296622340, 0.0331694870, 0.0357202170, 0.0497492310, 0.0637782440, 
      0.0663289740, 0.0803579880, 0.0873724950, 0.0943870010, 0.0 }, 
      correct_s2 { 53.0, 0.0, 29.350193, 41.503882, 58.688237, 5981.4375, 8313.5919, 
      11478.328, 15706.137, 21237.514, 28280.161, 36942.720, 47156.023, 58611.460, 
      70756.269, 82867.650, 94178.612, 103979.62, 111609.69, 116279.17, 116709.48, 
      110675.18, 94945.727, 67280.399, 48540.369, 48539.760, 48538.540, 48536.102, 
      48531.225, 48521.472, 48501.971, 48462.986, 48385.084, 48229.555, 47919.602, 
      47304.192, 46091.829, 43743.764, 39364.949, 31851.393, 20992.188, 14047.844, 
      9558.0062, 6607.6166, 4636.2229, 3248.6850, 2341.1063, 2272.6275, 2184.8212, 
      1574.4957, 1463.6744, 832.26113, 576.51928, 380.64264, 0.0 };
      for ( size_t i = 0; i < correct_s1.size(); ++i ){
        REQUIRE( correct_s1[i] == Approx(s3[2*i]).epsilon(1e-6) );
        REQUIRE( correct_s2[i] == Approx(s3[2*i+1]).epsilon(1e-6) );

      }


    } // WHEN
  } // GIVEN



  GIVEN( "high tolerance, energy, and cosine (debugging)" ){
    int imax = 20, lat = 0, iinc = 2, lasym = 0;
    double tev = 2.5507297688e-2, tol = 5.0;
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
    std::vector<double> boundXsVec {sigma_b,sigma_b2};

    double enow = 8.6e-1;
    double u = 1.0;

    int nemax = 5000;
    std::vector<double> s1(nemax,0.0),s2(nemax,0.0), s3(nemax*2,0.0);
  
    auto out = sigu(enow,u,tev,alphas,betas,sab,tol,az,iinc,lat,lasym,boundXsVec,teff,s3);
  
    std::vector<double> correctYU_first_110 { 44.6334456177, 54.0, 0, 0, 
    0.765623, 5.979297, 0.79368103, 20.80756, 0.79623176, 20.28317, 0.82428978, 
    1.692838, 0.82684051, 0.7111114, 0.84086953, 22.83815, 0.84788404, 187.8350, 
    0.85489854, 2614.586, 0.85489855, 0, 0.85489856, 0, 0.85489858, 0, 0.85489862, 
    0, 0.85489870, 0, 0.85489886, 0, 0.85489917, 0, 0.85489979, 0, 0.85490104, 
    0, 0.85490353, 0, 0.85490851, 0, 0.85491847, 0, 0.85493840, 0, 0.85497826, 
    0, 0.85505797, 0, 0.85521739, 0, 0.85553623, 0, 0.85617391, 0, 0.85744927, 
    0, 0.86255073, 0, 0.86382610, 0, 0.86446378, 0, 0.86478262, 0, 0.86494204, 
    0, 0.86502175, 0, 0.86506161, 0, 0.86508154, 0, 0.86509150, 0, 0.86509648, 
    0, 0.86509897, 0, 0.86510022, 0, 0.86510084, 0, 0.86510115, 0, 0.86510131, 
    0, 0.86510139, 0, 0.86510143, 0, 0.86510145, 0, 0.86510146, 2153.377, 
    0.87211597, 117.9912, 0.87913048, 10.89082, 0.89315949, 0.1927072, 0.89571022,
    0.4177208, 0.92376824, 1.712638, 0.92631897, 1.591015, 0.954377, 0.1488137 };
    for (size_t i = 0; i < correctYU_first_110.size(); ++i){
      REQUIRE( correctYU_first_110[i] == Approx(out[i]).epsilon(1e-6) );
    }
    for (size_t i = correctYU_first_110.size(); i < out.size(); ++i){
      REQUIRE( 0.0 == Approx(out[i]).epsilon(1e-6) );
    }



  } // GIVEN

} // TEST CASE
