#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "sigl.h"


TEST_CASE( "sigl" ){
  /*
  GIVEN( "inputs" ){
    int lasym = 0, lat = 1, iinc = 2, nlmax = 65, 
        nlin = 10;

    double e = 1.0e-6, ep = 1.2e-4, tev = 1.5e-4, az = 11.9,
      tevz = 2.2e-4, az2 = 0.0, teff2 = 0.0, cliq = 1.0, sb = 5.53, sb2 = 0.0,
      teff = 6.14e-2, tolin = 5e-2;

    std::vector<double> alpha { 1.1, 2.2, 3.3, 4.5, 5.8 },
      beta { 0.1, 0.2, 1.3, 1.4, 2.5, 2.6, 3.7 },
      s(65,0.0);

    std::vector<std::vector<double>> sab(alpha.size(), std::vector<double>(beta.size(),0));
    for ( int i = 0; i < alpha.size(); ++i ){
      for ( int j = 0; j < beta.size(); ++j ){
        sab[i][j] = 0.01*((j+1) + 0.1*(i+1));
      } 
    } 


    sigl( nlin, nlmax, e, ep, tev, alpha, beta, sab, s, tolin, az, tevz, iinc, 
        lat, lasym, az2, teff2, cliq, sb, sb2, teff );

    std::vector<double> correctS { 271591.653204, -8.776270547E-5 , 
      -6.162495039E-3, 7.1582888474E-5, -2.018780205E-2,  1.0016609703E-4, 
      -3.944407885E-2, 3.0130372017E-5, -5.459079490E-2, -9.1381657730E-5 };
   for ( int i = 0; i < 10; ++i ){ 
     REQUIRE( correctS[i] == Approx(s[i]).epsilon(1e-6) ); 
   }
   for ( int i = 10; i < s.size(); ++i ){
     REQUIRE( 0.0 == Approx(s[i]).epsilon(1e-6) ); 
   }


    REQUIRE( true );

  } // GIVEN



  GIVEN( "inputs 2" ){
    int lasym = 0, lat = 1, iinc = 2, nlmax = 65, 
        nlin = 10;

    double e = 1.0e-6, ep = 1.2e-4, tev = 1.5e-4, az = 11.9,
      tevz = 2.2e-4, az2 = 0.0, teff2 = 0.0, cliq = 1.0, sb = 5.53, sb2 = 0.0,
      teff = 6.14e-2, tolin = 5e-2;

    std::vector<double> alpha { 1.1, 2.2, 3.3, 4.5, 5.8 },
      beta { 0.1, 0.2, 1.3, 1.4, 2.5, 2.6, 3.7 },
      s(65,0.0);

    std::vector<std::vector<double>> sab(alpha.size(), std::vector<double>(beta.size(),0));
    for ( int i = 0; i < alpha.size(); ++i ){
      for ( int j = 0; j < beta.size(); ++j ){
        sab[i][j] = 0.01*((j+1) + 0.1*(i+1));
      } 
    } 


    sigl( nlin, nlmax, e, ep, tev, alpha, beta, sab, s, tolin, az, tevz, iinc, 
        lat, lasym, az2, teff2, cliq, sb, sb2, teff );

    std::vector<double> correctS { 271591.653204, -8.776270547E-5 , 
      -6.162495039E-3, 7.1582888474E-5, -2.018780205E-2,  1.0016609703E-4, 
      -3.944407885E-2, 3.0130372017E-5, -5.459079490E-2, -9.1381657730E-5 };
   for ( int i = 0; i < 10; ++i ){ 
     REQUIRE( correctS[i] == Approx(s[i]).epsilon(1e-6) ); 
   }
   for ( int i = 10; i < s.size(); ++i ){
     REQUIRE( 0.0 == Approx(s[i]).epsilon(1e-6) ); 
   }


    REQUIRE( true );

  } // GIVEN
  */

  GIVEN( "inputs 3" ){
    int lasym = 0, lat = 1, iinc = 2, nlmax = 65, 
        nlin = -9;

    double e = 1.0e-5, ep = 9.999999e-6, tev = 0.0255074596, az = 11.9,
      tevz = 0.0253, az2 = 0.0, teff2 = 0.0, cliq = 0.0, sb = 5.53486, sb2 = 0.0,
      teff = 0.0614755628515, tolin = 5e-2;

    std::vector<double> s(65,0.0);
    std::vector<double> alpha { 0.25203, 0.50406, 0.75609, 1.00812, 1.26015, 
      1.51218, 1.76421, 2.01624, 2.27331, 2.53552, 2.80297, 3.07577, 3.35401, 
      3.63790, 3.92733, 4.22271, 4.52383, 4.83111, 5.14443, 5.46411, 5.79013, 
      6.12261, 6.46185, 6.80783, 7.16077, 7.52067, 7.88783, 8.26234, 8.64432, 
      9.03396, 9.43136, 9.83673, 10.2506, 10.6719, 11.1024, 11.5409, 11.9886, 
      12.4452, 12.911, 13.3858 }, 
      beta { 0.0, 0.100812, 0.201624, 0.302436, 0.403248, 0.50406, 0.604872, 
      0.705684, 0.806496, 0.907307, 1.00812, 1.10893, 1.20974, 1.31055, 
      1.41137, 1.51218, 1.61299, 1.71380, 1.81461, 1.91543, 2.01624, 
      2.11705, 2.21786, 2.31867, 2.41949, 2.5203, 2.62111, 2.72192, 
      2.82273, 2.92354, 3.02436, 3.12517, 3.22598, 3.32679, 3.42760, 
      3.52842, 3.62923, 3.73004, 3.83085, 3.93167, 4.03248, 4.13329, 
      4.24378, 4.36485, 4.49762, 4.64309, 4.80248, 4.97719, 5.16873, 
      5.37862, 5.60867, 5.8608, 6.13713, 6.43997, 6.77184, 7.13567, 
      7.53438, 7.97140, 8.45036, 8.97529, 9.55052, 10.181, 10.8726, 
      11.6297, 12.4593, 13.3697, 14.3667, 15.4595, 16.6571, 17.9697, 
      19.4093, 20.9860, 22.7139, 24.6082, 26.6849, 28.9602, 31.4533, 
      34.1873, 37.1825, 40.4659 };
    std::vector<std::vector<double>> sab ( alpha.size(), std::vector<double> (beta.size()));
    for ( int i = 0; i < alpha.size(); ++i ){
      for ( int j = 0; j < beta.size(); ++j ){
        sab[i][j] = 0.5*i + 0.1*j;
      }
    }


    sigl( nlin, nlmax, e, ep, tev, alpha, beta, sab, s, tolin, az, tevz, iinc, 
        lat, lasym, az2, teff2, cliq, sb, sb2, teff );

    std::vector<double> correctS { 0.542594022, -0.926263996, -0.772825878, -0.609059013, -0.432353908, -0.237782881, -1.77980549E-2, 0.245718583, 0.622222118 };
   for ( int i = 0; i < 9; ++i ){ 
     REQUIRE( correctS[i] == Approx(s[i]).epsilon(1e-6) ); 
   }
   for ( int i = 9; i < s.size(); ++i ){
     REQUIRE( 0.0 == Approx(s[i]).epsilon(1e-6) ); 
   }


  } // GIVEN

} // TEST CASE

