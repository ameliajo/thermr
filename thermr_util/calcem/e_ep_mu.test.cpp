#define CATCH_CONFIG_MAIN 
#include "../../catch.hpp"
#include "e_ep_mu.h"

void checkVecHasZeros(std::vector<double>& v, int index_0, int index_1 ){
  for ( size_t i = index_0; i < index_1; ++i ){
    REQUIRE( 0.0 == Approx(v[i]).epsilon(1e-6) );
  }
}
void checkVecHasLin(std::vector<double>& v, int index_0, int index_1 ){
  for ( size_t i = index_0; i < index_1; ++i ){
    REQUIRE( (i+1) == Approx(v[i]).epsilon(1e-6) );
  }
}

void initializeLin(std::vector<double>& v){
  for ( size_t i = 0; i < v.size(); ++i ){ 
    v[i] = i + 1;
  }
}


TEST_CASE( "310" ){
  std::vector<double> egrid { 1.e-5, 1.78e-5, 2.5e-5, 3.5e-5, 5.0e-5, 7.0e-5, 
    1.e-4, 1.26e-4, 1.6e-4, 2.0e-4, 2.53e-4, 2.97e-4, 3.5e-4, 4.2e-4, 5.06e-4,
    6.15e-4, 7.5e-4, 8.7e-4, 1.012e-3, 1.23e-3, 1.5e-3, 1.8e-3, 2.03e-3, 
    2.277e-3, 2.6e-3, 3e-3, 3.5e-3, 4.048e-3, 4.5e-3, 5e-3, 5.6e-3, 6.325e-3, 
    7.2e-3, 8.1e-3, 9.108e-3, 1e-2, 1.063e-2, 1.15e-2, 1.2397e-2, 1.33e-2, 
    1.417e-2, 1.5e-2, 1.6192e-2, 1.82e-2, 1.99e-2, 2.0493e-2, 2.15e-2, 2.28e-2,
    2.53e-2, 2.8e-2, 3.0613e-2, 3.38e-2, 3.65e-2, 3.95e-2, 4.2757e-2, 4.65e-2,
    5e-2, 5.6925e-2, 6.25e-2, 6.9e-2, 7.5e-2, 8.1972e-2, 9e-2, 9.6e-2, 0.1035,
    0.111573, 0.12, 0.128, 0.1355, 0.145728, 0.16, 0.172, 0.184437, 0.2, 0.2277, 
    0.2510392, 0.2705304, 0.2907501, 0.3011332, 0.3206421, 0.3576813, 0.39, 
    0.4170351, 0.45, 0.5032575, 0.56, 0.625, 0.7, 0.78, 0.86, 0.95, 1.05, 
    1.16, 1.28, 1.42, 1.55, 1.70, 1.855, 2.02, 2.18, 2.36, 2.59, 2.855, 3.12, 
    3.42, 3.75, 4.07, 4.46, 4.90, 5.35, 5.85, 6.40, 7.00, 7.65, 8.40, 9.15, 
    9.85, 10.0 };
    int ie = 0, jbeta = 0, iskip = 0, j = 0, nl = 9, lasym = 0,
        ngrid = 118, nnl = -9;
    double enow = 0.0, temp = 296.0, bk = 8.617385e-5, break_val = 3000.0,
           therm = 2.53e-2, ep = 0.0, tev = 2.55074596e-2, tol = 5.0e-2,
           az = 11.9, tevz = 2.53e-2, iinc = 2, lat = 1, az2 = 0.0, teff2 = 0.0, 
           cliq = 0.0, sb = 5.5348570016241778, sb2 = 0.0, teff = 6.1475562851499993E-2;
    std::vector<double> alpha(40,0.0), beta(80,0.0);
    std::vector<std::vector<double>> sab(40,std::vector<double>(80,0.0));
    for ( int i = 0; i < 40; ++i ){ 
      alpha[i] = 0.1*i; 
      for ( int j = 0; j < 80; ++j ){
        sab[i][j] = 0.01*(ie+iskip);
      }
    }
    for ( int j = 0; j < 80; ++j ){ beta[j] = 0.2*j + 0.05; }

    std::vector<double> esi(95,0.0), xsi(95,0.0), ubar(118,0.0), x(20,0.0), 
      p2(118,0.0), p3(118,0.0), yt(65,0.0);
    std::vector<std::vector<double>> y(65,std::vector<double> (20,0.0));





  GIVEN( "temperature is lower than the break value of 3000" ){
    WHEN( "lasym is zero, vector entries are zero" ){
      do310( ie, enow, egrid, temp, bk, break_val, therm, esi, xsi, ubar, p2, 
        p3, ep, jbeta, iskip, j, y, yt, nl, lasym, x, ngrid, nnl,  
        tev, alpha, beta, sab, tol, az, tevz, iinc, lat, az2, teff2, cliq, sb, 
        sb2, teff );

      THEN( "ie is incremented, jbeta = -#beta, vectors set to 0 (except esi)" ){
        REQUIRE( 1 == ie ); REQUIRE(   0 == iskip); 
        REQUIRE( 0 == j  ); REQUIRE( -80 == jbeta);

        REQUIRE( 1.0e-5 == Approx(  enow  ).epsilon(1e-6) );
        REQUIRE( 0.0    == Approx(  ep    ).epsilon(1e-6) );
        REQUIRE( 1.0e-5 == Approx( esi[0] ).epsilon(1e-6) );
  
        checkVecHasZeros( esi, 1, esi.size() );
        checkVecHasZeros( xsi, 0, xsi.size() );
        checkVecHasZeros( ubar, 0, ubar.size() );
        for ( size_t i = 0; i < y.size(); ++i ){ 
          checkVecHasZeros( y[i], 0, y[i].size() );
        }
      } // THEN
    } // WHEN


    WHEN( "lasym is some positive value" ){
      lasym = 1;
      do310( ie, enow, egrid, temp, bk, break_val, therm, esi, xsi, ubar, p2, 
        p3, ep, jbeta, iskip, j, y, yt, nl, lasym, x, ngrid, nnl,  
        tev, alpha, beta, sab, tol, az, tevz, iinc, lat, az2, teff2, cliq, sb, 
        sb2, teff );

      THEN( "jbeta is set to equal 1" ){
        REQUIRE(1 == jbeta);
      } // THEN
    } // WHEN

    WHEN( "vectors contain nonzero entries, ie is nonzero index" ){
      ie = 3, jbeta = 10, iskip = 2, j = 8; enow = 0.5, ep = 1.0, tol = 5.0e-2;

      initializeLin(esi); initializeLin(xsi); initializeLin(ubar); 
      initializeLin(x);   initializeLin(p2);  initializeLin(p3);
      initializeLin(yt);
  
      do310( ie, enow, egrid, temp, bk, break_val, therm, esi, xsi, ubar, p2,
        p3, ep, jbeta, iskip, j, y, yt, nl, lasym, x, ngrid, nnl,  
        tev, alpha, beta, sab, tol, az, tevz, iinc, lat, az2, teff2, cliq, sb, 
        sb2, teff );

      THEN( "ie -> ie+1, and the ie+1 value in each vec is changed (except x)" ){
  
        REQUIRE( 4 == ie );     REQUIRE( -80 == jbeta );
        REQUIRE( 0  == iskip ); REQUIRE(   0 == j );
  
        REQUIRE( 3.5e-5 == Approx(enow).epsilon(1e-6) );
        REQUIRE( 0.0 == Approx(ep).epsilon(1e-6) );
  
        checkVecHasLin(esi,  0, 3 );
        checkVecHasLin(xsi,  0, 3 );
        checkVecHasLin(ubar, 0, 3 );
        REQUIRE( 3.5e-5 == Approx(esi[3]).epsilon(1e-6) );
        REQUIRE( 0.0    == Approx(xsi[3]).epsilon(1e-6) );
        REQUIRE( 0.0    == Approx(ubar[3]).epsilon(1e-6) );
        checkVecHasLin(esi,  4, esi.size() );
        checkVecHasLin(xsi,  4, xsi.size() );
        checkVecHasLin(ubar, 4, ubar.size() );
  
        REQUIRE( 0.0 == Approx(x[0]).epsilon(1e-6) );
        checkVecHasLin(x, 1, x.size() );
  
        checkVecHasZeros(yt, 0, 9 ); checkVecHasLin(yt, 9, yt.size() );
  
      } // THEN
    } // WHEN
  } // GIVEN




  GIVEN( "temperature is higher than the break value of 3000" ){
    temp = 3001;
    WHEN( "lasym is zero, vector entries are zero" ){
      do310( ie, enow, egrid, temp, bk, break_val, therm, esi, xsi, ubar, p2, 
        p3, ep, jbeta, iskip, j, y, yt, nl, lasym, x, ngrid, nnl, 
        tev, alpha, beta, sab, tol, az, tevz, iinc, lat, az2, teff2, cliq, sb, 
        sb2, teff );

      THEN( "ie is incremented, jbeta = -#beta, vectors set to 0 (except esi)" ){
        REQUIRE( 1 == ie ); REQUIRE(   0 == iskip); 
        REQUIRE( 0 == j  ); REQUIRE( -80 == jbeta);

        REQUIRE( 1.0e-5 == Approx(  enow  ).epsilon(1e-6) );
        REQUIRE( 0.0    == Approx(  ep    ).epsilon(1e-6) );
        REQUIRE( 1.0e-5 == Approx( esi[0] ).epsilon(1e-6) );
  
        checkVecHasZeros( esi, 1, esi.size() );
        checkVecHasZeros( xsi, 0, xsi.size() );
        checkVecHasZeros( ubar, 0, ubar.size() );
        for ( size_t i = 0; i < y.size(); ++i ){ 
          checkVecHasZeros( y[i], 0, y[i].size() );
        }
      } // THEN
    } // WHEN


    WHEN( "lasym is some positive value" ){
      lasym = 1;
      do310( ie, enow, egrid, temp, bk, break_val, therm, esi, xsi, ubar, p2, 
        p3, ep, jbeta, iskip, j, y, yt, nl, lasym, x, ngrid, nnl, 
        tev, alpha, beta, sab, tol, az, tevz, iinc, lat, az2, teff2, cliq, sb, 
        sb2, teff );

      THEN( "jbeta is set to equal 1" ){
        REQUIRE(1 == jbeta);
      } // THEN
    } // WHEN

    WHEN( "vectors contain nonzero entries, ie is nonzero index" ){
      ie = 3, jbeta = 10, iskip = 2, j = 8; enow = 0.5, ep = 1.0, tol = 5.0e-2;

      initializeLin(esi); initializeLin(xsi); initializeLin(ubar); 
      initializeLin(x);   initializeLin(p2);  initializeLin(p3);
      initializeLin(yt);
  
      do310( ie, enow, egrid, temp, bk, break_val, therm, esi, xsi, ubar, p2,
        p3, ep, jbeta, iskip, j, y, yt, nl, lasym, x, ngrid, nnl, 
        tev, alpha, beta, sab, tol, az, tevz, iinc, lat, az2, teff2, cliq, sb, 
        sb2, teff );

      THEN( "ie -> ie+1, and the ie+1 value in each vec is changed (except x)" ){
  
        REQUIRE( 4 == ie );     REQUIRE( -80 == jbeta );
        REQUIRE( 0  == iskip ); REQUIRE(   0 == j );
  
        REQUIRE( 4.32125e-5 == Approx(enow).epsilon(1e-6) );
        REQUIRE( 0.0 == Approx(ep).epsilon(1e-6) );
  
        checkVecHasLin(esi,  0, 3 );
        checkVecHasLin(xsi,  0, 3 );
        checkVecHasLin(ubar, 0, 3 );
        REQUIRE( 4.32125e-5 == Approx(esi[3]).epsilon(1e-6)  );
        REQUIRE( 0.0        == Approx(xsi[3]).epsilon(1e-6)  );
        REQUIRE( 0.0        == Approx(ubar[3]).epsilon(1e-6) );
        checkVecHasLin(esi,  4, esi.size() );
        checkVecHasLin(xsi,  4, xsi.size() );
        checkVecHasLin(ubar, 4, ubar.size() );
  
        REQUIRE( 0.0 == Approx(x[0]).epsilon(1e-6) );
        checkVecHasLin(x, 1, x.size() );
  
        checkVecHasZeros(yt, 0, 9 ); checkVecHasLin(yt, 9, yt.size() );
  
      } // THEN
    } // WHEN
  } // GIVEN

} // TEST CASE





/*

TEST_CASE( "Branch to handle E-E'-mu ordering" ){
  GIVEN( "inputs" ){
    int math = 1065, matdp = 1306, mtref = 229, ncds = 0, iinc = 2, lat = 1, 
        lasym = 0, nnl = -9, nl = 9, jmax = 55550, nne = 94, iprint=2;
    double teff = 713.39, teff2 = 0.0, za = 6000.0, awr = 11.8969, emax = 1.2, 
        cliq = 0.0, t = 296.0, tol = 5e-2, az = 11.9, az2 = 0.0, 
        sb = 5.5348570016241778, sb2 = 0.0;
    std::vector<double> scr( 500000, 0.0 ), esi( 95, 0.0 ), xsi( 95, 0.0 );

    std::vector<double> alpha { 0.25203, 0.50406, 0.75609, 1.00812, 1.26015, 1.51218, 1.76421, 2.01624, 2.27331, 2.53552, 2.80297, 3.07577, 3.35401, 3.63790, 3.92733, 4.22271, 4.52383, 4.83111, 5.14443, 5.46411, 5.79013, 6.12261, 6.46185, 6.80783, 7.16077, 7.52067, 7.88783, 8.26234, 8.64432, 9.03396, 9.43136, 9.83673, 10.2506, 10.6719, 11.1024, 11.5409, 11.9886, 12.4452, 12.911, 13.3858 }, beta { 0.0, 0.100812, 0.201624, 0.302436, 0.403248, 0.50406, 0.604872, 0.705684, 0.806496, 0.907307, 1.00812, 1.10893, 1.20974, 1.31055, 1.41137, 1.51218, 1.61299, 1.71380, 1.81461, 1.91543, 2.01624, 2.11705, 2.21786, 2.31867, 2.41949, 2.5203, 2.62111, 2.72192, 2.82273, 2.92354, 3.02436, 3.12517, 3.22598, 3.32679, 3.42760, 3.52842, 3.62923, 3.73004, 3.83085, 3.93167, 4.03248, 4.13329, 4.24378, 4.36485, 4.49762, 4.64309, 4.80248, 4.97719, 5.16873, 5.37862, 5.60867, 5.8608, 6.13713, 6.43997, 6.77184, 7.13567, 7.53438, 7.97140, 8.45036, 8.97529, 9.55052, 10.181, 10.8726, 11.6297, 12.4593, 13.3697, 14.3667, 15.4595, 16.6571, 17.9697, 19.4093, 20.9860, 22.7139, 24.6082, 26.6849, 28.9602, 31.4533, 34.1873, 37.1825, 40.4659 };
    std::vector<std::vector<double>> sab ( alpha.size(), std::vector<double> (beta.size()));
    for ( int i = 0; i < alpha.size(); ++i ){
      for ( int j = 0; j < beta.size(); ++j ){
        sab[i][j] = 0.5*i + 0.1*j;
      }
    }

    std::setprecision(15);

    e_ep_mu(math, matdp, teff, teff2, scr, mtref, za, awr, ncds, emax, cliq, iinc, lat, esi, xsi, lasym, alpha, beta, sab, t, tol, az, az2, sb, sb2, nnl, nl, jmax, nne, iprint );
    //std::cout << "okay got to here" << std::endl;
    std::vector<double> correctScr { 0.0000000000000000, 1.2800000000001279, 0.0000000000000000, 0.0000000000000000, 2170.0000000000000, 10.000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.25621273000002559, 3.7335106000003729E-006, -0.99193052500009915, -0.97452367600009737, -0.95456071000009546, -0.93060618700009312, -0.90121624900009012, -0.86217236900008620, -0.80291066700008029, -0.63468289300006342, 0.25621305000002559, 2.2863316600002286E+019, -0.98706336500009861, -0.95889077100009590, -0.92606988600009255, -0.88696309700008868, -0.83824734000008372, -0.77346470900007736, -0.67533813800006759, -0.42525435000004247, 0.25621337000002559, 2.2863269500002288E+019, -0.98706337100009867, -0.95889078900009583, -0.92606991900009250, -0.88696314800008869, -0.83824741300008376, -0.77346481100007736, -0.67533828500006754, -0.42525461300004247, 0.25621400000002559, 2.2863176700002288E+019, -0.98706338200009869, -0.95889082500009593, -0.92606998500009252, -0.88696324800008863, -0.83824755600008372, -0.77346501200007733, -0.67533857400006758, -0.42525513300004247, 0.25621527000002559, 2.2862989700002284E+019, -0.98706340500009870, -0.95889089900009583, -0.92607011700009256, -0.88696345100008867, -0.83824784600008373, -0.77346541800007729, -0.67533915600006755, -0.42525617900004248, 0.25621781000002558, 2.2862615700002284E+019, -0.98706345100009862, -0.95889104600009589, -0.92607038100009254, -0.88696385500008867, -0.83824842400008381, -0.77346622900007733, -0.67534032000006750, -0.42525827100004249, 0.25622288000002558, 2.2861869100002288E+019, -0.98706354300009869, -0.95889133900009582, -0.92607090900009259, -0.88696466300008869, -0.83824957900008379, -0.77346784900007737, -0.67534264500006758, -0.42526244800004248, 0.25623302000002557, 2.2860376000002286E+019, -0.98706372600009862, -0.95889192600009587, -0.92607196400009251, -0.88696627900008862, -0.83825188900008374, -0.77347108900007733, -0.67534729300006757, -0.42527080100004250, 0.25625330000002561, 2.2857389800002286E+019, -0.98706409200009870, -0.95889310000009587 };
    std::vector<double> correctScr1 { -0.11311445900001130, -9.9718791800009962E-002, -8.3693082700008373E-002, -6.3780962600006375E-002, -3.7311773500003725E-002, 2.7605915300002756E-003, 0.10389038300001038, 2.3037823000002300, 18200.513500001820, -0.12463170600001246, -0.11310705000001130, -9.9711369400009964E-002, -8.3685778600008365E-002, -6.3773694300006373E-002, -3.7304624500003727E-002, 2.7675867300002766E-003, 0.10389697500001038, 2.3037848000002299, 18199.853400001819, -0.12463170700001246, -0.11310705300001131, -9.9711374500009969E-002, -8.3685786400008372E-002, -6.3773705500006370E-002, -3.7304640000003726E-002, 2.7675646000002766E-003, 0.10389693600001039, 2.3037861000002300, 18199.510100001819, -0.12463170800001246, -0.11310705500001131, -9.9711377200009971E-002, -8.3685790500008378E-002, -6.3773711300006378E-002, -3.7304648000003729E-002, 2.7675531000002766E-003, 0.10389691600001039, 2.3037867000002299, 18199.351700001818, -0.12463170800001246, -0.11310705500001131, -9.9711378500009967E-002, -8.3685792300008374E-002, -6.3773713900006371E-002, -3.7304651700003730E-002, 2.7675477900002765E-003, 0.10389690700001039, 2.3037870000002298, 18199.272400001821, -0.12463170800001246, -0.11310705600001131, -9.9711379100009961E-002, -8.3685793300008374E-002, -6.3773715300006376E-002, -3.7304653600003727E-002, 2.7675451300002763E-003, 0.10389690200001039, 2.3037872000002300, 18199.219600001819, -0.12463170800001246, -0.11310705600001131, -9.9711379500009967E-002, -8.3685793900008368E-002, -6.3773716200006367E-002, -3.7304654800003730E-002, 2.7675433600002765E-003, 0.10389689900001038, 2.3037873000002298, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000 };
    std::vector<double> correctScr2 { -0.56094416800005609, -0.54287370200005436, -0.52126464800005212, -0.49439649900004945, -0.45867531100004588, -0.40459767500004046, -0.26803749500002677, 1.2672473000001265, 7377437880.0007372, -0.57498913200005741, -0.55937700600005591, -0.54132527200005409, -0.51973788800005194, -0.49289650900004928, -0.45721135300004573, -0.40318778200004035, -0.26676463800002664, 1.2697978000001267, 6350363350.0006342, -0.57341308700005733, -0.55781765300005581, -0.53978460900005398, -0.51821918300005176, -0.49140418100004918, -0.45575470700004556, -0.40178527400004016, -0.26549854800002654, 1.2723484000001273, 5465362010.0005465, -0.57183261900005722, -0.55624514000005565, -0.53823067100005373, -0.51668782600005170, -0.48989892800004897, -0.45428499500004543, -0.40037021400004003, -0.26422024600002642, 1.2748989000001274, 4704458510.0004702, -0.57026153600005702, -0.55469403700005548, -0.53669743100005363, -0.51517764300005153, -0.48841429200004882, -0.45283532400004528, -0.39897505800003991, -0.26296065100002625, 1.2774495000001276, 4049524690.0004048, -0.56869049100005686, -0.55315870900005537, -0.53517371300005356, -0.51368288000005136, -0.48694289000004864, -0.45139659100004514, -0.39759354800003976, -0.26171326400002615, 1.2799999000001279, 3485781040.0003481, -0.56712675500005660, -0.55162080500005506, -0.53364892700005329, -0.51218260100005120, -0.48546855600004857, -0.44995692600004500, -0.39620810700003961, -0.26046215000002604, 1.2800001000001278, 3485771320.0003481, -0.56712675600005669, -0.55162080600005514, -0.53364892800005337, -0.51218260300005125, -0.48546855900004854, -0.44995693100004497, -0.39620811300003961, -0.26046216000002603, 1.2825505000001280, 3664928350.0003662, -0.56557136900005656, -0.55009109200005502, -0.53213155800005318, -0.51068931600005107, -0.48400160400004838, -0.44852485900004485, -0.39482957400003948, -0.25921734400002594, 1.2851011000001282, 3853156710.0003848, -0.56401767800005642, -0.54855160900005484, -0.53061069100005309, -0.50918932400005090, -0.48252780200004824, -0.44708603600004471, -0.39344363800003934, -0.25796571500002580, 1.2876516000001286, 4051034490.0004048, -0.56246585300005625, -0.54702863400005464 };

    for ( size_t i = 0; i < correctScr.size(); ++i ){
      REQUIRE( correctScr[i] == Approx(scr[i]).epsilon(1e-6) );
    }
    for ( size_t i = 0; i < correctScr2.size(); ++i ){
      REQUIRE( correctScr2[i] == Approx(scr[i+999]).epsilon(1e-6) );
    }
    for ( size_t i = 0; i < correctScr1.size(); ++i ){
      REQUIRE( correctScr1[i] == Approx(scr[i+2099]).epsilon(1e-6) );
    }

    for ( size_t i = 2169; i < scr.size(); ++i ){
      REQUIRE( 0.0 == Approx(scr[i]).epsilon(1e-6) );
    }





  } // GIVEN
} // TEST CASE
*/
