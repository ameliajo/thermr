#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "beginningLoop.h"

TEST_CASE( "110 120 130" ){
  std::vector<double> x(20,0.0),y(20,0.0),s(20,0.0);
  x[0] = 1.0; x[1] = 0.99; x[2] = -1.0;
  y[0] = 1.35700e5; y[1] = 1.35701e5; y[2] = 1.35809e5;

  std::vector<double> alpha { 1.1, 2.2, 3.3, 4.5, 5.8 },
    beta { 0.1, 0.2, 1.3, 1.4, 2.5, 2.6, 3.7 };
    

  // Initialize S(a,b)
  std::vector<std::vector<double>> sab(alpha.size(), 
      std::vector<double>(beta.size(),0));
  for ( int i = 0; i < alpha.size(); ++i ){
    for ( int j = 0; j < beta.size(); ++j ){
      sab[i][j] = 0.01*((j+1) + 0.1*(i+1));
    } 
  } 

  int lasym = 0, lat = 1, iinc = 2, nlmax = 65, nl = 10, i = 3, 
      j = 0, nbin = 8;

  double e = 1.0e-6, ep = 1.2e-4, tev = 1.5e-4, bbm = 0.0, az = 11.9,
    tevz = 2.2e-4, az2 = 0.0, teff2 = 0.0, cliq = 1.0, sb = 5.53, sb2 = 0.0,
    teff = 6.14e-2, tolin = 5e-2, sigmin = 1.0e-32, 
    s1bb = 1.1369180380, tol = 2.5e-2, xtol = 1.0e-5, 
    seep = 91200.0, yl = 13500, ymax = 13500, fract = 0.0, xl = -1.0, 
    eps = -1.0e-3;


  GIVEN( "inputs 1" ){

    THEN( "110-->110, 110-->120, 120-->110, 120-->130, not many iterations" ){


      auto out = do_110_120_130(i, x, y, e, ep, tev, tevz, alpha, beta, sab, bbm, az, 
      az2, lasym, teff, teff2, lat, cliq, sb, sb2, iinc, nl, sigmin, s, 
        nbin, fract, xl, j, ymax, eps, seep, yl, s1bb, tol, xtol);

      ymax = adaptiveLinearization( x, y, e, ep, tev, tevz, alpha, beta, sab, bbm, az, az2, lasym, teff, teff2, lat, cliq, sb, sb2, iinc, xl, eps, seep, s1bb );

      double gral = std::get<0>(out), sum = std::get<1>(out);
      REQUIRE( 0 == Approx(gral).epsilon(1e-6) ); 
      REQUIRE( 0 == Approx(sum).epsilon(1e-6) ); 

      REQUIRE( 3 == Approx(i).epsilon(1e-6) ); 
      REQUIRE( 0 == Approx(j).epsilon(1e-6) ); 
      REQUIRE( 9 == Approx(nbin).epsilon(1e-6) ); 
      REQUIRE(-1 == Approx(xl).epsilon(1e-6) );
      REQUIRE( 30174.6306224 == Approx(fract).epsilon(1e-6) );
      REQUIRE( 135700.0 == Approx(yl).epsilon(1e-6) );
      REQUIRE( 135829.6496457 == Approx(ymax).epsilon(1e-6) );

      std::vector<double> correctX = { 1.0, 0.99, -1.0, -0.005, -1.0 },
        correctY = { 135757.913, 135758.3455, 135829.6496, 135797.21918, 135809.0 };

      for ( int i = 0; i < x.size(); ++i ){ 
        if ( i < 5 ){ REQUIRE( correctX[i] == Approx(x[i]).epsilon(1e-6) ); }
        else        { REQUIRE( 0.0         == Approx(x[i]).epsilon(1e-6) ); }
      }


      for ( int i = 0; i < y.size(); ++i ){ 
        if ( i < 5 ){ REQUIRE( correctY[i] == Approx(y[i]).epsilon(1e-6) ); }
        else        { REQUIRE( 0.0         == Approx(y[i]).epsilon(1e-6) ); }
      }

      REQUIRE( 271571.6756021== Approx(s[0]).epsilon(1e-6) );
      for ( int i = 1; i < s.size(); ++i ){ 
        REQUIRE( 0.0 == Approx(s[i]).epsilon(1e-6) ); 
      }


    } // THEN
  } // GIVEN



  GIVEN( "inputs 2" ){
    y[0] = 1.00000e5; y[1] = 1.00001e5; y[2] = 1.00009e5;

    e = 1.0e-3; ep = 1.2e-2; tev = 1.5e-1;
      tevz = 2.2e-1; 
      teff = 6.14e-0; 


    THEN( "110-->110, 110-->120, 120-->110, 120-->120, 120-->130, many iterations" ){


      auto out = do_110_120_130(i, x, y, e, ep, tev, tevz, alpha, beta, sab, bbm, az, 
      az2, lasym, teff, teff2, lat, cliq, sb, sb2, iinc, nl, sigmin, s, 
        nbin, fract, xl, j, ymax, eps, seep, yl, s1bb, tol, xtol);

      ymax = adaptiveLinearization( x, y, e, ep, tev, tevz, alpha, beta, sab, bbm, az, az2, lasym, teff, teff2, lat, cliq, sb, sb2, iinc, xl, eps, seep, s1bb );

      double gral = std::get<0>(out), sum = std::get<1>(out);
      REQUIRE( 0 == Approx(gral).epsilon(1e-6) ); 
      REQUIRE( 0 == Approx(sum).epsilon(1e-6) ); 

      REQUIRE( 3 == Approx(i).epsilon(1e-6) ); 
      REQUIRE( 0 == Approx(j).epsilon(1e-6) ); 
      REQUIRE( 9 == Approx(nbin).epsilon(1e-6) ); 
      REQUIRE(-1 == Approx(xl).epsilon(1e-6) );
      REQUIRE( 120.57844468516407 == Approx(fract).epsilon(1e-6) );
      REQUIRE( 100000.0 == Approx(yl).epsilon(1e-6) );
      REQUIRE( 538.71588696219601 == Approx(ymax).epsilon(1e-6) );

      std::vector<double> correctX = { 1.0, 0.99, -1.0, 0.99125, 0.990625, 
        0.9903125, 0.99015625, 0.99007813, 0.99003907, 0.99001954, 0.99000977, 
        0.99, -0.99902832, -0.99951416, -0.99975708, -0.99987854, -0.99993927, 
        -0.99996963, -0.99998481, -1.0 },
      correctY = { 461.24225912, 464.2445488, 538.7158869, 463.8735389, 
        464.0591955, 464.151910, 464.198238, 464.2213947, 464.23297, 464.238758, 
        464.2416537, 100001.0, 538.74710638, 538.7314976, 538.72369255, 
        538.7197898, 538.71783, 538.7168628, 538.71637506, 100009.0 };

      for ( int i = 0; i < x.size(); ++i ){ 
        REQUIRE( correctX[i] == Approx(x[i]).epsilon(1e-6) );
      }


      for ( int i = 0; i < y.size(); ++i ){ 
        REQUIRE( correctY[i] == Approx(y[i]).epsilon(1e-6) );
      }

      REQUIRE( 1085.2060021664768 == Approx(s[0]).epsilon(1e-6) );
      for ( int i = 1; i < s.size(); ++i ){ 
        REQUIRE( 0.0 == Approx(s[i]).epsilon(1e-6) ); 
      }


    } // THEN
  } // GIVEN

  GIVEN( "inputs 2" ){
    y[0] = 1.00000e5; y[1] = 1.00001e5; y[2] = 1.00009e5;
    x[0] = 1.00; x[1] = 1.01; x[2] = -1.09;

    e = 1.0e-3; ep = 1.2e-2; tev = 1.5e-1;
      tevz = 2.2e-1; 
      teff = 6.14e-0; 


    THEN( "110-->110, 110-->120, 120-->110, 120-->120, 120-->130, many iterations" ){


      auto out = do_110_120_130(i, x, y, e, ep, tev, tevz, alpha, beta, sab, bbm, az, 
      az2, lasym, teff, teff2, lat, cliq, sb, sb2, iinc, nl, sigmin, s, 
        nbin, fract, xl, j, ymax, eps, seep, yl, s1bb, tol, xtol);


      double gral = std::get<0>(out), sum = std::get<1>(out);
      REQUIRE( 0 == Approx(gral).epsilon(1e-6) ); 
      REQUIRE( -4969.3589863 == Approx(sum).epsilon(1e-6) ); 

      REQUIRE( 0 == Approx(i).epsilon(1e-6) ); 
      REQUIRE( 0 == Approx(j).epsilon(1e-6) ); 
      REQUIRE( 8 == Approx(nbin).epsilon(1e-6) ); 
      REQUIRE( 1.0 == Approx(xl).epsilon(1e-6) );
      REQUIRE( 0.0 == Approx(fract).epsilon(1e-6) );
      REQUIRE( 100000 == Approx(yl).epsilon(1e-6) );
      REQUIRE( 13500.0 == Approx(ymax).epsilon(1e-6) );

      std::vector<double> correctX = { 1.0, 1.01, 1.00999, 1.0099839, -4.0e-2, 
        -0.95875003, -1.024375, -1.0571875, -1.0735938, -1.0817969, -1.0858985, 
        -1.0879493, -1.0889747, -1.0894874, -1.0897437, -1.0898719, -1.089936, 
        -1.089968, -1.089984, -1.09 },
      correctY = { 100000.0, 100001.0, 458.1631128, 458.16561, 559.873519, 
        540.0340460, 537.9302281, 536.8654128, 536.33012496, 536.061804, 
        535.9274772, 535.8602733, 535.8266613, 535.80985281, 535.8014495,
        535.7972461, 535.7951444, 535.7940951, 535.79357053, 100009.0 };
        

      for ( int i = 0; i < x.size(); ++i ){ 
        REQUIRE( correctX[i] == Approx(x[i]).epsilon(1e-6) );
      }


      for ( int i = 0; i < y.size(); ++i ){ 
        REQUIRE( correctY[i] == Approx(y[i]).epsilon(1e-6) );
      }

      for ( int i = 0; i < s.size(); ++i ){ 
        REQUIRE( 0.0 == Approx(s[i]).epsilon(1e-6) ); 
      }


    } // THEN
  } // GIVEN
} // TEST CASE


