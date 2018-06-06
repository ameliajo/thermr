
#include "../extra/terp1.h"
#include "../extra/legndr.h"
#include "calcem_util/sigl.h"
#include "calcem_util/sigfig.h"

auto do410( int& i, std::vector<double>& x, const double& xm, const int& nl,
  std::vector<std::vector<double>>& y, const std::vector<double>& yt, const int& j ){
  //std::cout << "410   " << i << "    " << j << std::endl;
  std::cout << "410" << std::endl;
  // 410 continue
  i=i+1;
  x[i-1]=x[i-1-1];
  x[i-1-1]=xm;
  for ( int il = 0; il < nl; ++il ){
    y[il][i-1]=y[il][i-1-1];
    y[il][i-1-1]=yt[il];
  } // enddo
}

auto do313( int& jbeta, const int& lat, double& ep, double& enow, 
  const std::vector<double>& beta, const double& tev, const double& tevz,
  const std::vector<double>& x, int& iskip){
  bool do_313 = true;
  std::cout << 313 << std::endl;
  while ( do_313 ){
    //std::cout << std::setprecision(20) << "E'     " << ep << std::endl;
    // 313 continue
    if (jbeta == 0) jbeta=1;
    if (jbeta <= 0) {
      if (lat == 1) {
   //     std::cout << enow << "    " << beta[-jbeta-1] << "    " << tevz << "    " << jbeta << std::endl;
        ep=enow-beta[-jbeta-1]*tevz;
      }
      else {
        ep=enow-beta[-jbeta-1]*tev;
      } // endif
      if (ep == enow) {
         ep=sigfig(enow,8,-1);
      }
      else {
         ep=sigfig(ep,8,0);
      }

    } 
    else {
      if (lat == 1) {
        ep=enow+beta[jbeta-1]*tevz;
      }
      else {
        ep=enow+beta[jbeta-1]*tev;
      } // endif
      if (ep == enow) {
         ep=sigfig(enow,8,+1);
         iskip=1;
      }
      else { 
         ep=sigfig(ep,8,0);
      }

    } // endif
    if (ep > x[2-1]) { return; } // go to 316
    jbeta=jbeta+1;
    // go to 313
  }

  //std::cout << std::setprecision(20) << "E'     " << ep << std::endl;
}





auto do310( int& ie, double& enow, const std::vector<double>& egrid, const double& temp,
  const double& bk, const double& break_val, const double& therm, 
  std::vector<double>& esi, std::vector<double>& xsi, std::vector<double>& ubar,
  std::vector<double>& p2, std::vector<double>& p3, double& ep, int& jbeta,
  int& iskip, int& j, std::vector<std::vector<double>>& y, 
  std::vector<double>& yt, const int nl, const int& lasym, std::vector<double>& x,
  const int& ngrid, const int& nnl, 
  const double& tev, const std::vector<double>& alpha, const std::vector<double>& beta,
  const std::vector<std::vector<double>>& sab, const double& tol,
  const double& az, const double& tevz, const int iinc, const int lat, const double& az2,
  const double& teff2, const double& cliq, const double& sb, const double& sb2, 
  const double& teff ){
     //std::cout << 310 << std::endl;
     if (temp > break_val) {
       enow = egrid[0] * 
              exp( log(                             egrid[ie] / egrid[0] ) * 
                   log( (temp*bk/therm)*egrid[egrid.size()-1] / egrid[0] ) / 
                   log(                 egrid[egrid.size()-1] / egrid[0] )
                 );
     } // endif
     else {
       enow = egrid[ie];
     }
     esi[ie]  = enow;
     xsi[ie]  = 0.0;
     ubar[ie] = 0.0;
     p2[ie]   = 0.0;
     p3[ie]   = 0.0;
     x[0]     = 0.0;
     ep       = 0.0;
     j        = 0;
     iskip    = 0;
     jbeta = lasym > 0 ? 1 : -beta.size();
     ++ie;

     sigl( nnl, yt.size(), enow, ep, tev, alpha, beta, sab, yt, tol, az, tevz, iinc, 
         lat, lasym, az2, teff2, cliq, sb, sb2, teff );

     for ( int il = 0; il < nl; ++il ){ y[il][0] = yt[il]; } // enddo
}

auto do360(int& j, const int& jmax, std::vector<double>& xsi, 
    std::vector<double>& x, double& xlast, double& ylast, double& ulast,
    double& u2last, double& u3last, const double& tolmin,
    std::vector<std::vector<double>>& y, std::vector<double>& p2,
    std::vector<double>& p3,
    double& uu, double& u2, double& u3, int& nll, const int& nl, 
    std::vector<double>& p, std::vector<double>& ubar, const int ie, 
    const int i ){
  // 360 continue
  std::cout << 360 << std::endl;
  j=j+1;
  if (j >= jmax) std::cout << "call error('calcem','storage exceeded.',' ')" << "       " << j <<"     " << jmax  << std::endl;
  if (j > 1) xsi[ie-1]=xsi[ie-1]+(x[i-1]-xlast)*(y[0][i-1]+ylast)*0.5;
  if (j > 1) {
    uu=0;
    u2=0;
    u3=0;
    nll=3;
    for ( int il = 1; il < nl; ++il ){
      legndr( y[il][i-1], p );
      uu=uu+p[2-1];
      u2=u2+p[3-1];
      u3=u3+p[4-1];
    } // enddo
    uu=uu/(nl-1);
    uu=uu*y[0][i-1];
    u2=u2/(nl-1);
    u3=u3/(nl-1);
    u2=u2*y[0][i-1];
    u3=u3*y[0][i-1];
    ubar[ie-1]=ubar[ie-1]+0.5*(x[i-1]-xlast)*(uu+ulast);
    p2[ie-1]=p2[ie-1]+0.5*(x[i-1]-xlast)*(u2+u2last);
    p3[ie-1]=p3[ie-1]+0.5*(x[i-1]-xlast)*(u3+u3last);
  } // endif
  // if (j != 3 or xsi[ie-1] >= tolmin) go to 380
  if (j == 3 and xsi[ie-1] < tolmin){ j = 2; }
  // j=2

}



auto e_ep_mu(int& math, int& matdp, double& teff, double& teff2, 
  std::vector<double>& scr, const int& mtref, double& za, double& awr,
  int& ncds, double& emax, double& cliq, int iinc, int lat,
  std::vector<double>& esi, std::vector<double>& xsi, const int& lasym,
  std::vector<double>& alpha, std::vector<double>& beta, 
  std::vector<std::vector<double>>& sab, const double t, const double& tol,
  const double& az, const double& az2, const double& sb, const double& sb2, 
  int& nnl, const int& nl, const int& jmax, const int& nne, int iprint ){

  int itemp,iold,inew,ne,nex;
  double temp;
  int nr,np,nwtab,nlt,nlp,nlp1;
  int i,ia,nl1,ltt,loc,l,jscr,ilog;
  int matd,itprnt,nb,nw,ni,nbeta=beta.size(),lt,it,nalpha=alpha.size();
  int itrunc,ib,ip,ir,idis,ie,nmu,nep,istart,iend;
  int jbeta=0,j=0,iskip,il,k,jnz,ll,jj,ii,nexn,ien,isave;
  int nll;
  double smz,t1,tmax,test,tempt,tt1,ttn,tnxt,xm;
  double uu,uum,ym,test2,xlast,ulast,xs;
  double b,diff,enow,ep,sabmin,tev,tevz,ylast;
  double u,xl,yl,sum;
  const int ngrid=118;
  const int nlmax=65;
  const int nemax=5000;
  const int mumax=300;
  const int imax=20;
  int numIters = 0;
  std::vector<double> ex(imax,0.0),x(imax,0.0),yt(nlmax,0.0);
  std::vector<std::vector<double>> y(nlmax,std::vector<double> (imax,0.0));
  std::vector<double> yy(imax,0.0),yu(2*nemax,0.0),ubar(ngrid,0.0),p2(ngrid,0.0),p3(ngrid,0.0),p(4,0.0),uj(mumax,0.0),sj(mumax,0.0);
  double u2=0,u2last=0,u3=0,u3last=0;
  std::vector<double> egrid { 1.e-5, 1.78e-5, 2.5e-5, 3.5e-5, 5.0e-5, 7.0e-5, 
    1.e-4, 1.26e-4, 1.6e-4, 2.0e-4, 0.000253, 0.000297, 0.000350, 0.00042, 
    0.000506, 0.000615, 0.00075, 0.00087, 0.001012, 0.00123, 0.0015, 0.0018, 
    0.00203, 0.002277, 0.0026, 0.003, 0.0035, 0.004048, 0.0045, 0.005, 0.0056, 
    0.006325, 0.0072, 0.0081, 0.009108, 0.01, 0.01063, 0.0115, 0.012397, 
    0.0133, 0.01417, 0.015, 0.016192, 0.0182, 0.0199, 0.020493, 0.0215, 0.0228, 
    0.0253, 0.028, 0.030613, 0.0338, 0.0365, 0.0395, 0.042757, 0.0465, 0.050, 
    0.056925, 0.0625, 0.069, 0.075, 0.081972, 0.09, 0.096, 0.1035, 0.111573, 
    0.120, 0.128, 0.1355, 0.145728, 0.160, 0.172, 0.184437, 0.20, 0.2277, 
    0.2510392, 0.2705304, 0.2907501, 0.3011332, 0.3206421, 0.3576813, 0.39, 
    0.4170351, 0.45, 0.5032575, 0.56, 0.625, 0.70, 0.78, 0.86, 0.95, 1.05, 
    1.16, 1.28, 1.42, 1.55, 1.70, 1.855, 2.02, 2.18, 2.36, 2.59, 2.855, 3.12, 
    3.42, 3.75, 4.07, 4.46, 4.90, 5.35, 5.85, 6.40, 7.00, 7.65, 8.40, 9.15, 
    9.85, 10.00 };
  const double sabflg = -225, eps = 1.e-4, tolmin = 5.e-7, therm = 0.0253, 
    break_val = 3000, em9 = 1e-9, up = 1.1, dn = 0.9, uumin = 0.00001, yumin = 2e-7, 
    nlpmx = 10, bk =8.617385e-5;
  int mth, mfh;
  // save nwtab,sabmin,nl,nlt,nlp,nlp1,nl1,nnl,jmax,nne
  tevz = therm;


  // compute kernel and write in special mf6 energy-angle format
  // 300 continue
  std::cout << "300" << std::endl;
  // if (iform == 1) go to 510 
  // ^^ Take care of this in the upstairs function
  // This will go to the other branch ( the E-mu-E' branch )
  ltt=5;
  math=matdp;
  mfh=6;
  mth=mtref;
  tev=t*bk;
  teff=teff*bk;
  teff2=teff2*bk;
  scr[1-1]=za;
  scr[2-1]=awr;
  scr[3-1]=0;
  scr[4-1]=ltt; // temporary flag for this format
  scr[5-1]=1;
  scr[6-1]=0;
  nw=6;
  // call contio(0,0,nscr,scr,nb,nw)
  ncds=ncds+1;
  scr[1-1]=1;
  scr[2-1]=1;
  scr[3-1]=-1; // LIP=-1 indicates incoherent inelastic data
  scr[4-1]=1; // LAW=1 for incoherent inelastic data
  scr[5-1]=1;
  scr[6-1]=2;
  scr[7-1]=2;
  scr[8-1]=2;
  scr[9-1]=1.e-5;
  scr[10-1]=1;
  scr[11-1]=emax;
  scr[12-1]=1;
  nw=12;
  //call tab1io(0,0,nscr,scr,nb,nw)
  ncds=ncds+2;
  scr[1-1]=temp;
  scr[2-1]=0;
  scr[3-1]=3; // lang=3 is a special code for equally probable cosines
  scr[4-1]=1;
  scr[5-1]=1;
  scr[6-1]=nne;
  scr[7-1]=nne;
  scr[8-1]=2;
  nw=8;
  // call tab2io(0,0,nscr,scr,nb,nwtab)
  ncds=ncds+2;
  cliq=0;

  if ( iinc != 1 and sab[0][0] > sab[0][1]){
    cliq=(sab[0][0]-sab[0][1])*alpha[0]/(beta[1]*beta[1]);
  }

  // loop over given incident energy grid.
  // 305 continue
  std::cout << 305 << std::endl;
  ie=0;

  // Loop over incident energy (green line in my drawing)
  bool loopE = true;
  while (loopE){

    // 310 continue
    //do310( ie, enow, egrid, temp, bk, break_val, therm, esi, xsi, ubar, p2, 
    //  p3, ep, jbeta, nbeta, iskip, j, y, yt, nl, lasym, x, ngrid );
    do310( ie, enow, egrid, temp, bk, break_val, therm, esi, xsi, ubar, p2, p3, ep, jbeta, iskip, j, y, yt, nl, lasym, x, ngrid, nnl, tev, alpha, beta, sab, tol, az, tevz, iinc, lat, az2, teff2, cliq, sb, sb2, teff );



    bool moreBeta = true;
    while (moreBeta) {
      // set up next panel
      // 311 continue
      std::cout << 311 << std::endl;
      x[2-1]=x[1-1];

      for (int il = 0; il < nl; ++il ){
        y[il][2-1] = y[il][1-1];
      } // enddo

      /*
      std::cout << std::setprecision(15) << std::setw(25) << x[0] << std::setw(25) << x[1] << std::setw(25) << x[2] << std::endl;
      std::cout << std::setprecision(15) << std::setw(25) << x[3] << std::setw(25) << x[4] << std::setw(25) << x[5] << std::endl;
      std::cout << std::setprecision(15) << std::setw(25) << x[6] << std::setw(25) << x[7] << std::setw(25) << x[8] << std::endl;
      std::cout << std::endl;
      std::cout << std::setprecision(15) << std::setw(25) << y[0][0] << std::setw(25) << y[0][1] << std::setw(25) << y[0][2] << std::endl;
      std::cout << std::setprecision(15) << std::setw(25) << y[0][3] << std::setw(25) << y[0][4] << std::setw(25) << y[0][5] << std::endl;
      std::cout << std::setprecision(15) << std::setw(25) << y[0][6] << std::setw(25) << y[0][7] << std::setw(25) << y[0][8] << std::endl;
      std::cout << "jbeta:  " << jbeta << std::endl;
      */



      // do 313
      do313( jbeta, lat, ep, enow, beta, tev, tevz, x, iskip);

      //std::cout << std::setprecision(15) << jbeta << "         " << ep << std::endl;

//    std::cout << "-------------  " << y[0][0] << std::endl;
      std::cout << 316 << std::endl;
      ep = sigfig(ep,8,0);
      x[1-1]=ep;

    //for ( auto entry : yt ){ std::cout << entry << std::endl;  }
    /*
      std::cout << std::setprecision(15) << nnl << "     " << nlmax << "    " << enow << std::endl;
      std::cout << std::setprecision(15) << ep << "     " << tev << std::endl;
      std::cout << std::setprecision(15) << tol << "     " << az << "    " << tevz << std::endl;
      std::cout << std::setprecision(15) << iinc << "     " << lat << "    " << lasym << std::endl;
      std::cout << std::setprecision(15) << az2 << "     " << teff2 << "    " << cliq<< std::endl;
      std::cout << std::setprecision(15) << sb << "     " << sb2 << "    " << teff << std::endl;
    */

      //std::cout << std::setprecision(15) << std::setw(25) << yt[0] << std::setw(25) << yt[1] << std::setw(25) << yt[2] << std::endl;
      sigl( nnl, nlmax, enow, ep, tev, alpha, beta, sab, yt, tol, az, 
        tevz, iinc, lat, lasym, az2, teff2, cliq, sb, sb2, teff );

//    if (numIters == 85 and i == 1 and j == 171 ){ return; }
      std::cout << std::setprecision(15) << std::setw(25) << yt[0] << std::setw(25) << yt[1] << std::setw(25) << yt[2] << std::endl;
    //  std::cout << std::setprecision(15) << std::setw(25) << yt[3] << std::setw(25) << yt[4] << std::setw(25) << yt[5] << std::endl;
    //  std::cout << std::setprecision(15) << std::setw(25) << yt[6] << std::setw(25) << yt[7] << std::setw(25) << yt[8] << std::endl;


      for (int il = 0; il < nl; ++il ){
        y[il][1-1]=yt[il];
      } // enddo


      //std::cout << std::setprecision(15) << std::setw(25) << y[0][0] << std::setw(25) << y[0][1] << std::setw(25) << y[0][2] << std::endl;
      //std::cout << std::setprecision(15) << std::setw(25) << y[0][3] << std::setw(25) << y[0][4] << std::setw(25) << y[0][5] << std::endl;
      //std::cout << std::setprecision(15) << std::setw(25) << y[0][6] << std::setw(25) << y[0][7] << std::setw(25) << y[0][8] << std::endl;
      //std::cout << std::setprecision(15) << jbeta << "    " << ep << std::endl;


     // if (i == 1 and j == 85) { std::cout << "\nalmost got there" << std::endl; return; }

      // adaptive subdivision of panel
      i=2;
      // compare linear approximation to true function
  
      //std::cout << std::setprecision(15) << std::setw(25) << x[0] << std::setw(25) << x[1] << std::setw(25) << x[2] << std::endl;
      //std::cout << std::setprecision(15) << std::setw(25) << x[3] << std::setw(25) << x[4] << std::setw(25) << x[5] << std::endl;
      //std::cout << std::setprecision(15) << std::setw(25) << x[6] << std::setw(25) << x[7] << std::setw(25) << x[8] << std::endl;

      bool passedTest = false;
      while (not passedTest){

        std::cout << 330 << "     " << i << "     " << j << "       " << jbeta << "     " << numIters << std::endl;
        //std::cout << 330 << std::endl;
    //    std::cout << i << "       " << y[0].size() << "      " << y[0][i-1-1] << "    " << y[0][0] << std::endl;
        //if (numIters == 91 ) return;


        if ( i != imax ){
          if ( iskip != 1 ){
            if (0.5*(y[0][i-1-1]+y[0][i-1])*(x[i-1-1]-x[i-1]) >= tolmin) {
              xm=0.5*(x[i-1-1]+x[i-1]);
              xm = sigfig(xm,8,0);

     //   std::cout << std::setprecision(15)<<"xm     " << xm<<  std::endl;
              if (xm > x[i-1] and xm < x[i-1-1]) {
                sigl( nnl, nlmax, enow, xm, tev, alpha, beta, sab, yt, tol, az, 
                    tevz, iinc, lat, lasym, az2, teff2, cliq, sb, sb2, teff );
                //std::cout << std::setprecision(15) << enow << "    " << xm << std::endl;
                //if (numIters == 92 ) return;
                uu = 0; uum = 0;
                bool goto330 = false;
                for ( int k = 1; k <= nl; ++k ){
                  ym = terp1(x[i-1],y[k-1][i-1],x[i-1-1],y[k-1][i-1-1],xm,2);

                  if (k > 1) uu=uu+yt[k-1];
                  if (k > 1) uum=uum+ym;
                  test=tol*abs(yt[k-1]);
                  test2=test;
                  if (k > 1) test2=tol;
                   //std::cout << yt[k-1] << "    "  << ym << "    " << test2<< std::endl; 

                  if (abs(yt[k-1]-ym) > test2){
                    do410( i, x, xm, nl, y, yt, j );

                    /*
                    std::cout<<std::setprecision(15)<<ubar[0]<<"    "<<ubar[1]<<"     "<<ubar[2]<<std::endl;
                    std::cout<<std::setprecision(15)<<ubar[3]<<"    "<<ubar[4]<<"     "<<ubar[5]<<std::endl;
                    std::cout<<std::setprecision(15)<<ubar[6]<<"    "<<ubar[7]<<"     "<<ubar[8]<<std::endl;

                    std::cout<<std::setprecision(15)<<xsi[0]<<"    "<<xsi[1]<<"     "<<xsi[2]<<std::endl;
                    std::cout<<std::setprecision(15)<<xsi[3]<<"    "<<xsi[4]<<"     "<<xsi[5]<<std::endl;
                    std::cout<<std::setprecision(15)<<xsi[6]<<"    "<<xsi[7]<<"     "<<xsi[8]<<std::endl;

                    std::cout<<std::setprecision(15)<<x[0]<<"    "<<x[1]<<"     "<<x[2]<<std::endl;
                    std::cout<<std::setprecision(15)<<x[3]<<"    "<<x[4]<<"     "<<x[5]<<std::endl;
                    std::cout<<std::setprecision(15)<<x[6]<<"    "<<x[7]<<"     "<<x[8]<<std::endl;
                    std::cout<<std::setprecision(15)<<y[0][0]<<"    "<<y[0][1]<<"     "<<y[0][2]<<std::endl;
                    std::cout<<std::setprecision(15)<<y[0][3]<<"    "<<y[0][4]<<"     "<<y[0][5]<<std::endl;
                    std::cout<<std::setprecision(15)<<y[0][6]<<"    "<<y[0][7]<<"     "<<y[0][8]<<std::endl;
                    */

                    goto330 = true;
                    break;
                  } 
                } 
                if (goto330){ continue; }
                if (not goto330){
                  std::cout << 350 << std::endl;  // 350 continue
                  test=2*tol*abs(uu-1)+uumin;
                  if (abs(uu-uum) > test){
                    // point passes.  save top point in stack and continue.
                    do410( i, x, xm, nl, y, yt, j );
                    continue;
                  }
                }
              } 
            } 
          } // iskip
          else {
            iskip = 0;
          }
        } 
      
        do360(j, jmax, xsi, x, xlast, ylast, ulast, u2last, u3last, tolmin, y, 
          p2, p3, uu, u2, u3, nll, nl, p, ubar, ie, i );
 
        /*
        std::cout<<std::setprecision(18)<<std::setw(25)<<ubar[0]<<std::setw(25)<<ubar[1]<<std::setw(25)<<ubar[2]<<std::endl;
        std::cout<<std::setprecision(18)<<std::setw(25)<<ubar[3]<<std::setw(25)<<ubar[4]<<std::setw(25)<<ubar[5]<<std::endl;
        std::cout<<std::setprecision(18)<<std::setw(25)<<ubar[6]<<std::setw(25)<<ubar[7]<<std::setw(25)<<ubar[8]<<std::endl;
        std::cout<<std::endl; 
        std::cout<<std::setprecision(18)<<std::setw(25)<<p3[0]<<std::setw(25)<<p3[1]<<std::setw(25)<<p3[2]<<std::endl;
        std::cout<<std::setprecision(18)<<std::setw(25)<<p3[3]<<std::setw(25)<<p3[4]<<std::setw(25)<<p3[5]<<std::endl;
        std::cout<<std::setprecision(18)<<std::setw(25)<<p3[6]<<std::setw(25)<<p3[7]<<std::setw(25)<<p3[8]<<std::endl;
        std::cout<<std::endl; 
        std::cout<<std::setprecision(18)<<std::setw(25)<<p2[0]<<std::setw(25)<<p2[1]<<std::setw(25)<<p2[2]<<std::endl;
        std::cout<<std::setprecision(18)<<std::setw(25)<<p2[3]<<std::setw(25)<<p2[4]<<std::setw(25)<<p2[5]<<std::endl;
        std::cout<<std::setprecision(18)<<std::setw(25)<<p2[6]<<std::setw(25)<<p2[7]<<std::setw(25)<<p2[8]<<std::endl;
        std::cout<<std::endl; 
        std::cout<<std::setprecision(18)<<std::setw(25)<<x[0]<<std::setw(25)<<x[1]<<std::setw(25)<<x[2]<<std::endl;
        std::cout<<std::setprecision(18)<<std::setw(25)<<x[3]<<std::setw(25)<<x[4]<<std::setw(25)<<x[5]<<std::endl;
        std::cout<<std::setprecision(18)<<std::setw(25)<<x[6]<<std::setw(25)<<x[7]<<std::setw(25)<<x[8]<<std::endl;
        std::cout<<std::endl; 
        std::cout<<std::setprecision(18)<<std::setw(25)<<y[0][0]<<std::setw(25)<<y[0][1]<<std::setw(25)<<y[0][2]<<std::endl;
        std::cout<<std::setprecision(18)<<std::setw(25)<<y[0][3]<<std::setw(25)<<y[0][4]<<std::setw(25)<<y[0][5]<<std::endl;
        std::cout<<std::setprecision(18)<<std::setw(25)<<y[0][6]<<std::setw(25)<<y[0][7]<<std::setw(25)<<y[0][8]<<std::endl;
        std::cout<<std::endl; 
        std::cout<<std::setprecision(15)<<xsi[0]<<"      "<<xsi[1]<<"      "<<xsi[2]<<std::endl;
        std::cout<<std::setprecision(15)<<xsi[3]<<"      "<<xsi[4]<<"      "<<xsi[5]<<std::endl;
        std::cout<<std::setprecision(15)<<xsi[6]<<"      "<<xsi[7]<<"      "<<xsi[8]<<std::endl;
       
        */

        std::cout << 380 << std::endl;
        jscr=7+(j-1)*(nl+1);
        scr[jscr-1]=x[i-1];
        if (y[1-1][i-1] >= em9) {
          scr[1+jscr-1]=sigfig(y[1-1][i-1],9,0);
        }
        else { 
          scr[1+jscr-1]=sigfig(y[1-1][i-1],8,0);
        } // endif
        for ( int il = 1; il < nl; ++ il ){
          scr[il+jscr]=sigfig(y[il][i-1],9,0);
          if (scr[il+jscr] > 1) {
            // only warn for big miss, but always fix the overflow
            //  use this same 1+0.0005 value in aceth
            if (scr[il+jscr] > 1+0.0005) {
              std::cout << "call mess('calcem',strng,'')" << std::endl;
            } // endif
            scr[il+jscr-1]=1;
          } // endif
          if (scr[il+jscr] < -1) {
            // only warn for big miss, but always fix the underflow
            if (scr[il+jscr] < -(1+0.0005)) {
              std::cout << "call mess('calcem',strng,'')" << std::endl;
            } // endif
            scr[il+jscr]=-1;
          } // endif
        } // enddo
        xlast=x[i-1];
        ylast=y[1-1][i-1];
        if (ylast != 0) jnz=j;
        ulast=0;
        u2last=0;
        u3last=0;
        nll=3;
        for ( int il = 1; il < nl; ++il ){
          legndr( y[il][i-1], p );
          ulast  = ulast  + p[2-1];
          u2last = u2last + p[3-1];
          u3last = u3last + p[4-1];
        } // enddo
        ulast  = ulast  * y[1-1][i-1]/(nl-1);
        u2last = u2last * y[1-1][i-1]/(nl-1);
        u3last = u3last * y[1-1][i-1]/(nl-1);
        i=i-1;
        //if (i >= 2) std::cout << "go to 330" << std::endl; 
        if (i >= 2) continue;
        jbeta=jbeta+1;

        //if (jbeta <= nbeta) std::cout << "go to 311" << std::endl;
        if (jbeta <= nbeta) break; // go to 311

        for ( int il = 0; il < nl; ++il ){
          y[il][i-1]=0;
        } // enddo










        // test fails.  add point to stack and continue.
        //for ( auto entry : x ){ std::cout << std::setprecision(15) << "   -        " << entry << std::endl; }
        //return;
        std::cout << 430 << "         " << ie << std::endl;
        numIters += 1;
        std::cout << "-----------------------------------------------" << std::endl;
        j=j+1;
        xsi[ie-1]=xsi[ie-1]+(x[i-1]-xlast)*(y[1-1][i-1]+ylast)*0.5;
        uu=0;
        u2=0;
        u3=0;
        ubar[ie-1]=ubar[ie-1]+0.5*(x[i-1]-xlast)*(uu+ulast);
        p2[ie-1]=p2[ie-1]+0.5*(x[i-1]-xlast)*(u2+u2last);
        p3[ie-1]=p3[ie-1]+0.5*(x[i-1]-xlast)*(u3+u3last);
        xsi[ie-1]=sigfig(xsi[ie-1],9,0);
        scr[7+(nl+1)*(j-1)-1]=x[i-1];
        jscr=7+(j-1)*(nl+1);
        if (y[1-1][i-1] >= em9) {
          scr[1+jscr-1]=sigfig(y[1-1][i-1],9,0);
        }
        else {
          scr[1+jscr-1]=sigfig(y[1-1][i-1],8,0);
        }
        for ( int il = 1; il < nl; ++il ){
          scr[il+jscr]=sigfig(y[il][i-1],9,0);
          if (scr[il+jscr] > 1.0 ) {
            // only warn for big miss, but always fix the overflow
            if (scr[il+jscr] > 1+0.0005) {
              // write(strng,'("2cos",f7.4,", set to 1.&&  enow,e''=",2(1pe12.5))')&scr(il+jscr),enow,scr(jscr)
              std::cout << "call mess('calcem',strng,'')" << std::endl;
            }
          scr[il+jscr]=1.0;
          }
          if (scr[il+jscr] < -1.0) {
            // only warn for big miss, but always fix the underflow
            if (scr[il+jscr] < -(1+0.0005)) {
              // write(strng,'("2cos",f7.4,", set to -1.&&  enow,e''=",2(1pe12.5),i3)')&scr(il+jscr),enow,scr(jscr)
              std::cout << "call mess('calcem',strng,'')" << std::endl;
            }
            scr[il+jscr]=-1.0;
          }
        }
        if (y[1-1][1-1] != 0.0) jnz=j;
        if (jnz < j) j=jnz+1;

        if (iprint == 2) {
          ubar[ie-1]=ubar[ie-1]/xsi[ie-1];
          p2[ie-1]=p2[ie-1]/xsi[ie-1];
          p3[ie-1]=p3[ie-1]/xsi[ie-1];
          //write(nsyso,'(/,1x,"incident energy =",1pe13.6,&
          //             &  5x,"cross section =",1pe13.6,&
          //             &  5x,"mubar,p2,p3 =",3(1pe12.4))')&
          //                    enow,xsi(ie),ubar(ie),p2(ie),p3(ie)
          //write(nsyso,'(/,5x,"exit energy",11x,"pdf",7x,"cosines")')
          //write(nsyso,'(  3x,"---------------",5x,"-----------",2x,88("-"))')
          ll=6;
          for ( int jj = 1; jj <= j; ++jj ){
            //write(nsyso,'(2x,1pe15.8,5x,1pe12.5,0p,8f11.6)')&
            // (scr(ll+ii),ii=1,nlp)
            // if (nl1.gt.nlp) write(nsyso,'(34x,8f11.6)')&
            // (scr(ll+ii),ii=nlp1,nl1)
            ll=ll+nl1;
          }
        }
        scr[1-1]=0;
        scr[2-1]=enow;
        scr[3-1]=0;
        scr[4-1]=0;
        scr[5-1]=(nl+1)*j;
        scr[6-1]=nl+1;
        ncds=ncds+1+(j*(nl+1)+5)/6;
        //std::cout << "ie   " << ie << "      " << nne  << std::endl;

        //std::cout << "call listio(0,0,nscr,scr,nb,nw)" << std::endl;
        loc=1;
        //while (nb != 0){
        //  loc=loc+nw;
        //  std::cout << "call moreio(0,0,nscr,scr(loc),nb,nw)" << std::endl;
        //}
        if (ie < nne) {
          // std::cout << "go to 310" << std::endl;
          passedTest = true;
          moreBeta = false;
        }
        else {
          std::cout << "go to 610" << std::endl;
          std::cout<<std::setprecision(18)<<std::setw(25)<<scr[0]<<std::setw(25)<<scr[1]<<std::setw(25)<<scr[2]<<std::endl;
          std::cout<<std::setprecision(18)<<std::setw(25)<<scr[3]<<std::setw(25)<<scr[4]<<std::setw(25)<<scr[5]<<std::endl;
          std::cout<<std::setprecision(18)<<std::setw(25)<<scr[6]<<std::setw(25)<<scr[7]<<std::setw(25)<<scr[8]<<std::endl;
          std::cout<<std::setprecision(18)<<std::setw(25)<<x[0]<<std::setw(25)<<x[1]<<std::setw(25)<<x[2]<<std::endl;
          std::cout<<std::setprecision(18)<<std::setw(25)<<x[3]<<std::setw(25)<<x[4]<<std::setw(25)<<x[5]<<std::endl;
          std::cout<<std::setprecision(18)<<std::setw(25)<<x[6]<<std::setw(25)<<x[7]<<std::setw(25)<<x[8]<<std::endl;
          std::cout<<std::setprecision(18)<<std::setw(25)<<y[0][0]<<std::setw(25)<<y[1][1]<<std::setw(25)<<y[2][2]<<std::endl;
          std::cout<<std::setprecision(18)<<std::setw(25)<<y[3][3]<<std::setw(25)<<y[4][4]<<std::setw(25)<<y[5][5]<<std::endl;
          std::cout<<std::setprecision(18)<<std::setw(25)<<y[6][6]<<std::setw(25)<<y[7][7]<<std::setw(25)<<y[8][8]<<std::endl;


          return; 
        }

      } // passedTest (going back to 330)
    } // moreBeta (311)
  } //  loopE (310)

}
