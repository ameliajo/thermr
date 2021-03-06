#include "inelastic/sig.h"
#include <range/v3/all.hpp>

#ifndef CALCEM_E_MU_EP_SIGU
#define CALCEM_E_MU_EP_SIGU


template <typename Range, typename Float>
inline auto initializeEpXS( int& jbeta, const int& lat, Range& epVec, Range& xsVec, 
  const Float& e, const Float& tev, const Float& tevz, const Float& u, 
  const Range& alpha, const Range& beta,  const Range& sab, const Float& az, 
  const int lasym, const Float& teff, const Range& boundXsVec,  
  const int& iinc){

  using std::abs;

  do { // 113
    if (jbeta == 0) jbeta = 1;
    epVec[0] = ( lat == 0 ) ? e + jbeta / abs(jbeta) * beta[abs(jbeta)-1]*tev 
                            : e + jbeta / abs(jbeta) * beta[abs(jbeta)-1]*tevz; 
    if ( jbeta <= 0 ){
      epVec[0] = (jbeta < 0 and epVec[0] == e) ? sigfig(epVec[0],8,-1) 
                                               : sigfig(epVec[0],8,0);
    }
    ++jbeta;
  } while(epVec[0] <= epVec[1]);
  --jbeta;
   
  // 116
  Float root1_sq = std::pow((u*sqrt(e)+sqrt(u*u*e+(az-1)*(az+1)*e))/(az+1),2);

  if (u < 0 and 1.01*epVec[1] < root1_sq and root1_sq < epVec[0]) {
    epVec[0] = root1_sq;
  }

  epVec[0] = sigfig(epVec[0],8,0);
  xsVec[0] = sig( e, epVec[0], u, tev, alpha, beta, sab, az, tevz, lasym, lat, 
                  boundXsVec, teff, iinc );

} 



template <typename Range, typename Float>
auto refineEpXS(int& i, Range& xsVec, Range& epVec, const Float& tol, 
  const Float& teff, const Float& e, const Float& u, const Float& tev, 
  const Range& alphas, const Range& betas, const Range& sab, const Float& az, 
  const Float& tevz, int lasym,int lat, const Range& boundXsVec, int iinc ){

   while ( i < int(epVec.size())-1 ){ //std::cout << " --- 150 --- " << std::endl; 
     if ( i > 2 and 0.5*(xsVec[i-1]+xsVec[i])*(epVec[i-1]-epVec[i]) < 1e-6 ){ return; }

     Float epMid = sigfig(0.5*(epVec[i-1]+epVec[i]),8,0);

     if ( epMid <= epVec[i] or epMid >= epVec[i-1] ){ return; }

     Float xsGuess = 0.5*(xsVec[i-1]+xsVec[i]),
           xsTrue = sig( e, epMid, u, tev, alphas, betas, sab, az, tevz, 
                         lasym, lat, boundXsVec, teff, iinc );

     // Point passes
     if ( std::fabs(xsTrue-xsGuess) <= tol*std::fabs(xsTrue) ){ return; }

     ++i; // We need to bisect again
     epVec[i] = epVec[i-1];
     xsVec[i] = xsVec[i-1];
     epVec[i-1] = epMid;
     xsVec[i-1] = xsTrue;
   }
}




template <typename Range, typename Float>
inline auto sigu( const Float& e, const Float& u, const Float& tev, 
  const Range& alphas, const Range& betas, const Range& sab, 
  const Float& tolin, const Float& az, const int& iinc, const int& lat, 
  const int& lasym, const Range& boundXsVec, const Float& teff, Range& s3 ){

 /*-------------------------------------------------------------------
  * Compute the secondary energy distribution scattering for cosine u.
  * Uses linear reconstruction with the cross section from function sig.
  *-------------------------------------------------------------------
  */
  Float sum = 0.0, epLeft=0.0, yl=0.0, tevz = 0.0253;
  Range epVec(20,0.0), xsVec(20,0.0);
  // xsVec[0] is the xs corresponding to E -> E'with scattering cosine u
  xsVec[0] = sig( e, epVec[0], u, tev, alphas, betas, sab, az, tevz, lasym, 
              lat, boundXsVec, teff, iinc );

  // jbeta = 1 if S(a,b) doesn't abide by normal symmetric/non-symmetric 
  // rules (e.g. cold deuterium or hydrogen)
  
  int jbeta = (lasym > 0) ? 1 : -betas.size();
  int j = 0;

  do { // 111 
    epVec[1] = epVec[0]; 
    xsVec[1] = xsVec[0];


    initializeEpXS( jbeta, lat, epVec, xsVec, e, tev, tevz, u, alphas, betas, sab, az, 
                lasym, teff, boundXsVec, iinc );

    int i = 1;
    do {
      refineEpXS( i, xsVec, epVec, tolin, teff, e, u, tev, alphas, 
              betas, sab, az, tevz, lasym, lat, boundXsVec, iinc );
      do { // 160
        if (2*j+10 >= int(s3.size())){ 
            s3.resize(2*s3.size()); 
        }
        ++j;
        s3[2*j+0] = epVec[i];
        s3[2*j+1] = xsVec[i];
        if ( j > 1 ) { 
            sum += (xsVec[i]+yl)*(epVec[i]-epLeft); 
        }
        epLeft = epVec[i];
        yl = xsVec[i];

        if (( j >= int(0.5*s3.size())-1 ) or ( jbeta > 0 and betas[jbeta-1] > 20.0 )){ 
          s3[0] = sum; 
          s3[1] = j; 
          s3.resize(2*j+2);
          return s3; // 170
        } 
        --i;
        if ( i > 0 ){ break; }
        ++jbeta;
      } while (i == 0 and jbeta > int(betas.size()));

    } while(i > 0);

  } while( jbeta <= int(betas.size()));
  s3.resize(2*j+2);
  s3[0] = sum; s3[1] = j; return s3; // 170
}
#endif

