#include <iostream>
#include "general_util/sigfig.h"
#include "calcem/calcem_util/e_mu_ep_util/sigu.h"




template <typename Range, typename Float>
auto do_560( int& i, int& j, Range& uj, Range& sj, Range& x, Range& yy, 
             Float& sum, Float& xl, Float& yl ){
  //std::cout << " --- 560 --- " << std::endl;
  ++j;
  uj[j-1] =  x[i-1];
  sj[j-1] = yy[i-1];
  if ( j > 1 ){ 
      sum += 0.5*(yy[i-1]+yl)*(x[i-1]-xl);
      xl =  x[i-1];
      yl = yy[i-1];
  }
  --i;
}


template <typename Range, typename Float>
auto do_530_etc( Float enow, const Float& tev, const Float& tol, 
  const int lat, const int iinc, const int lasym, const Range& alphas, 
  const Range& betas, const Range& sab, const Float& az, const Float& sigma_b, 
  const Float& sigma_b2, const Float& teff ){
  std::cout.precision(15);

  int imax = 20, mumax = 300, nemax = 5000;
  Range x(imax,0.0); x[0] = 1.0; x[1] = -1.0;
  Range yy(imax,0.0), yu(2*nemax);
  Range uj(mumax,0.0), sj(mumax,0.);
  Range s1(5000,0.0);
  Range s2(5000,0.0);
  Float xm, ym, yl=0.0, xl=0.0;
  int i = 2;
  int j = 0;
  Float u = -1.0, sum = 0.0;

  u = -1.0;
  yu = sigu( enow, u, tev, alphas, betas, sab, tol, az, iinc, lat, lasym, sigma_b, sigma_b2, teff, s1, s2 );
  yy[1] = yu[0];
  xl = x[1];
  yl = yy[1];

  u = 1.0;
  yu = sigu( enow, u, tev, alphas, betas, sab, tol, az, iinc, lat, lasym, sigma_b, sigma_b2, teff, s1, s2 );
  yy[0]=yu[0];
  i = 2;

  while (true) {
    //std::cout << " --- 530 --- " << std::endl;
    if ( i != imax ){
      xm = 0.5*(x[i-2]+x[i-1]);
      xm = sigfig(xm,7,0);
      if ( xm > x[i-1] and xm < x[i-2] ){
        yu = sigu( enow, xm, tev, alphas, betas, sab, tol, az, iinc, lat, lasym, sigma_b, sigma_b2, teff, s1, s2 );
        ym = yy[i-1]+(xm-x[i-1])*(yy[i-2]-yy[i-1])/(x[i-2]-x[i-1]);
        if (x[i-2]-x[i-1] > 0.25 or (abs(yu[0]-ym ) > 2.0*tol*ym + 5e-7)) { 
            ++i;
            x[i-1] = x[i-2];
            x[i-2] = xm;
            yy[i-1] = yy[i-2];
            yy[i-2] = yu[0];
            continue;
        }
      }
    }
    do_560(i,j,uj,sj,x,yy,sum,xl,yl);
    if ( i < 2 ){ break; }

  }

  //std::cout << " --- 580 --- " << std::endl;
  ++j;
  uj[j-1] = x[0];
  sj[j-1] = yy[0];

  int nmu = j;

  sum += 0.5*(yy[0]+yl)*(x[0]-xl);

  Float xsi = sum*0.5;
  Float ubar = 0.0;

  for ( int i = 2; i <= nmu; ++i ){
    ubar += 0.5*(uj[i-1]-uj[i-2])*(sj[i-1]+sj[i-2])*(uj[i-1]+uj[i-2]);
  }
  ubar *= 0.5/sum;



  for ( int il = 0; il < nmu; ++il ){
    u = uj[il];
    yu = sigu( enow, u, tev, alphas, betas, sab, tol, az, iinc, lat, lasym, sigma_b, sigma_b2, teff, s1, s2 );
    j = 0;
    int nep = yu[1];
    for ( int i = 1; i <= nep; ++i ){
      j = nep-i;
      if (yu[2*(nep-i)+4-1]/sum > 2e-7){ 
          break;
      }
    }
    nep = j;
  }


  return std::make_tuple(xsi,ubar,uj);
}







/*
template <typename Range, typename Float>
auto mu_ep( Float enow, const Float& tev, const Float& tol, 
  const int lat, const int iinc, const int lasym, const Range& alphas, 
  const Range& betas, const Range& sab, const Float& az, const Float& sigma_b, 
  const Float& sigma_b2, const Float& teff, const int nbin, const Float& temp ){
  std::cout.precision(15);


  



}

*/










/*
auto mainLoop(const int& nep, const int& npage, int& j, int& k, int& ib,
  std::vector<double>& scr, const std::vector<double>& yu, const double& sum, 
  int& nw, int& ncds, int& nb ){
  int iend, istart = 1;
  while (true) {
    //std::cout << 595 << std::endl;
    iend=nep;
    if ((iend-istart) >= npage/2) iend=istart+npage/2-1;
    j=k-1;
    ib=istart-1;

    do {
     ///std::cout << 596 << std::endl;
     j=j+2;
     ib=ib+1;
     scr[j-1]=yu[1+2*ib-1];
     scr[j+1-1]=yu[2+2*ib-1]*2/sum;
    }
    while ( ib < iend );
    nw=j+1;
    if (k == 0) {
      std::cout << 597 << std::endl;
      //call moreio(0,0,nscr,scr,nb,nw)
      if (nb == 0) {
        std::cout << 598 << std::endl;
        ncds=ncds+1+(j*(nep+1)+5)/6;
        return std::make_tuple(istart,iend);
      }
      istart=iend+1;
      continue;
    }
    k=0;
    //call tab1io(0,0,nscr,scr,nb,nw)
    if (nb == 0) {
      std::cout << 598 << std::endl;
      ncds=ncds+1+(j*(nep+1)+5)/6;
      return std::make_tuple(istart,iend);
    } 
    istart=iend+1;
    continue;

  }
  return std::make_tuple(istart,iend);

}
*/
