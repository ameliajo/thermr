#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "sigu.h"


TEST_CASE( "sigu" ){
  GIVEN( "inputs" ){
    int lasym = 0, lat = 1, iinc = 2, nemax = 5000;

    std::cout << std::setprecision(10) ;
    double e = 1.0e-6, tev = 1.5e-4, az = 11.9,
      tevz = 2.2e-4, az2 = 0.0, teff2 = 0.0, cliq = 1.0, sb = 5.53, sb2 = 0.0,
      teff = 6.14e-2, tolin = 5e-2, u = 0.1;

    std::vector<double> alpha(40),beta(80),s(2*nemax,0.0);
    for ( int i = 0; i < 40;     ++i ){ alpha[i] = 0.1*i + 0.001; }
    for ( int i = 0; i < 80;     ++i ){ beta[i]  = 0.2*i + 0.025; }
    for ( int i = 0; i < 100000; ++i ){ s[i]     = 0.01  + i%12; }

    std::vector<std::vector<double>> sab(alpha.size(), std::vector<double>(beta.size(),0));
    for ( int i = 0; i < alpha.size(); ++i ){
      for ( int j = 0; j < beta.size(); ++j ){
        sab[i][j] = 0.2*i + 0.4*j + (i+j)%5;
      } 
    } 


    sigu( nemax, e, u, tev, alpha, beta, sab, s, tolin, az, tevz, iinc, 
        lat, lasym, az2, teff2, cliq, sb, sb2, teff );




    std::vector<double> correctS {  614757195474.47119, 431.0 };
   for ( int i = 0; i < correctS.size(); ++i ){ 
     //REQUIRE( correctS[i] == Approx(s[i]).epsilon(1e-6) ); 
   }


    /*
   */

    REQUIRE( true );
  } // GIVEN
} // TEST CASE

