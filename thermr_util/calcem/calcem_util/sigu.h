#include "sig.h"
#include "sigu_util/begin_sigu.h"


auto sigu( int nemax, double& e, double& u, double& tev, 
  std::vector<double>& alpha, std::vector<double>& beta, 
  std::vector<std::vector<double>>&sab, std::vector<double>&s, double& tolin, 
  double& az, double& tevz, int iinc, int lat, int lasym, 
  double& az2, double& teff2, double& cliq, double& sb, double& sb2, 
  double& teff ){

  /*-------------------------------------------------------------------
   * Compute the secondary energy distribution scattering for cosine u.
   * Uses linear reconstruction with the cross section from function sig.
   *-------------------------------------------------------------------
   */
   int i, j, jbeta, imax=20;
   double sum, xl, yl, xm, ym, test, yt, tol, root1, root2;
   std::vector<double> x(imax), y(imax);
   double tolmin = 1.e-6, bmax = 20;
   std::cout << std::setprecision(12);

   // constant factors
   tol=tolin;
   for ( int i = 0; i < 2*nemax; ++i ){
     s[i] = 0;
   }

   root1 = (u*sqrt(e)+sqrt(u*u*e+(az-1)*(az+1)*e))/(az+1);
   root2 = (u*sqrt(e)-sqrt(u*u*e+(az-1)*(az+1)*e))/(az+1);

   // adaptive calculation of cross section
   sum=0;
   x[1-1]=0;
   y[1-1] = sig( e, x[1-1], xl, tev, alpha, beta, sab, az, tevz, lasym, 
       az2, teff2, lat, cliq, sb, sb2, teff, iinc );
   jbeta = -beta.size();
   if (lasym > 0) jbeta=1;
   j = 0;
   xl = 0;
   yl = 0;

   // set up next panel
   while (true){  
     // 111 continue
     std::cout << 111 << std::endl;
     x[2-1]=x[1-1]; 
     y[2-1]=y[1-1];


     do_113_116( jbeta, lat, x, y, e, tev, tevz, root1, u, alpha, beta, 
         sab, az, lasym, az2, teff, teff2, cliq, sb, sb2, iinc );

     i = 2;

     std::cout << std::setprecision(15) << x[0] << "    " << x[1] << "     " << x[2] << std::endl;
     std::cout << std::setprecision(15) << y[0] << "    " << y[1] << "     " << y[2] << std::endl;

     // compare linear approximation to true function
     // 150 continue
     bool do150 = true;
     bool goTo150 = true;
     while (do150){
       // if (i == imax) go to 160
       if ( i != imax and goTo150 ){
         std::cout << std::setprecision(20) << 150 << "     " << y[0] << std::endl;
         // if (i > 3 and half*(y[i-1-1]+y[i-1])*(x[i-1-1]-x[i-1]) < tolmin) go to 160
         if (i <= 3 or 0.5*(y[i-1-1]+y[i-1])*(x[i-1-1]-x[i-1]) >= tolmin) {
           xm=0.5*(x[i-1-1]+x[i-1]);
           xm = sigfig(xm,8,0);
           //std::cout << "xm        " << xm << std::endl;
           // if (xm <= x[i-1] or xm.ge.x[i-1-1]) go to 160
           // if ( y[0] < 200000 ){ return; }
           if (xm > x[i-1] and xm < x[i-1-1]){
             ym=0.5*(y[i-1-1]+y[i-1]);
             //std::cout << "ym        " << ym << "         "<< y[0]<< std::endl;
             yt = sig( e, xm, u, tev, alpha, beta, sab, az, tevz, lasym, 
                 az2, teff2, lat, cliq, sb, sb2, teff, iinc );
             //std::cout << "yt        " << yt << std::endl;
             test = tol*abs(yt);
      
             //if (abs(yt-ym) <= test) { std::cout << "go to 160" << std::endl; }
             if (abs(yt-ym) > test) {
               // point fails
               i=i+1;
               x[i-1]=x[i-1-1];
               y[i-1]=y[i-1-1];
               x[i-1-1]=xm;
               y[i-1-1]=yt;
               // go to 150
              // return;
               continue;
             }
           }
         }
       }
       goTo150 = true;
  
       // point passes
       // 160 continue
       std::cout << 160 << "    " << i << "    " << j << "      " << sum << std::endl;
       if ( j == 20 )return;
       j=j+1;
       s[2*j+1-1]=x[i-1];
       s[2*j+2-1]=y[i-1];
       if (j > 1) sum=sum+(y[i-1]+yl)*(x[i-1]-xl);
       xl=x[i-1];
       yl=y[i-1];

       // if (j >= nemax-1) go to 170
       if (j >= nemax-1 or (jbeta > 0 and beta[jbeta-1] > bmax )) {
         std::cout << j << "    " << nemax-1 << "    " << jbeta << "     " << bmax <<std::endl;
         s[1-1]=sum;
         s[2-1]=j;
         return; 
      }

      // continue bin loop and linearization loop
      i=i-1;
      //std::cout << i << "     " << jbeta << "    " << beta.size() << std::endl;

      // if (i > 1) go to 150
      if (i > 1) {
        continue;
      }
      //std::cout << "no longer doing 150" << std::endl;
      //
      //
      if ( jbeta > beta.size() and i == 1 ){
        jbeta = jbeta + 1;
        goTo150 = false;
        continue;
      } 

      break;
    } 

    jbeta=jbeta+1;

    // if (jbeta <= nbeta) go to 111
    if (jbeta <= beta.size()) continue;
 

    // 170 continue
    std::cout << 170 << std::endl;
    s[1-1]=sum;
    s[2-1]=j;
    return; 
  }
}


