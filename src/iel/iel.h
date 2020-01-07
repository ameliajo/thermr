#include "coh/coh_util/sigcoh_util/terp.h"
#include "iel/iel_util/terpa.h"
#include <cmath>
//#include "ENDFtk.hpp"

template <typename Range, typename Float>
auto iel( int mat, int itemp, int iold, int inew, int ne, int nex, 
  Range& tempr, Range& fl, Float za, Range& scr, Float awr, Float emax, 
  int natom, int nbin, Range& esi  ){
  /*-------------------------------------------------------------------
   * INCOHERENT ELASTIC SCATTERING
   *-------------------------------------------------------------------
   * Compute the elastic scattering from polyethylene or hydrogen
   * in zirconium hydride using the incoherent approximation.
   * The calcem energy grid is used.  If mat == 11 or 12, built-in
   * parameters from the ENDF/B-III evaluations are used.
   * If mat == 20, material parameters have been read from ENDF6.
   *-------------------------------------------------------------------
   */
   int idis,iex,iet,ix,nj,nr,np,ip,ir,ltt,nb,nw,matdp;
   int n,nup,nup1,isave,nne;
   Float dwa,c1,e,c2,uLeft,rc2,temp,tt1,ttn,tnxt,math,mth,mfh,mtref,sb;
   Float /*x1,r1x1,*/xsec,/*x2,*/uRight;
   Range ex(20), ej(20);
   int nupmax = 10;
   Range 
     tmp { 296,400,500,600,700,800,1000,1200 },
     dwh { 8.4795, 9.0854, 9.8196, 10.676, 11.625, 12.643, 14.822, 17.125 },
     dwz { 1.9957, 2.6546, 3.2946, 4.5835, 5.2302, 6.5260, 7.8236 };
   
   Float c11a=162.88, c11b=296, c11c=34.957, c11d=350, c11e=40.282, c12a=81.44,
	  c13a=6.3366, up=1.1, dn=.9;

   dwa = 0; // This is just to fix uninitialized warning. NJOY doesn't 
            // initialize dwa. No real reason why...?
   mtref = 0; // mtref is not initialized either
   matdp = 0; // matdp is not initialized either

   // initialize
   temp=tempr[itemp];
   nj=nex+1;

   // select material parameters
   if (mat == 11) {          // D in D2O
      sb=c11a;  // Characteristic bound cross section
      dwa=c11c+(temp-c11b)*(c11e-c11c)/(c11d-c11b); // Debye-Waller Coefficient
   }
   else if (mat == 12) {     // D in para D2O
      dwa=terp(tmp,dwh,temp,3);                   // Deybe-Waller Coefficient
      sb=c12a;  // Characteristic bound cross section
   }
   else if (mat == 13) {     // D in ortho D2O
      dwa=terp(tmp,dwz,temp,3);                   // Debye-Waller Coefficient
      sb=c13a;  // Characteristic bound cross section
   }
   else if (mat == 20) {
      sb=fl[0]; // Characteristic bound cross section
      nr=round(fl[4]);
      np=round(fl[5]);
      if (np == 1) {
         tt1=fl[7+2*nr-1];
         if (std::abs(temp-tt1) > temp/10){
           //call error('iel',&'bad temperature for debye-waller factor',' ')
           throw std::exception();
         }
         dwa=fl[8+2*nr];                            // Debye-Waller Coefficient
      }
      else {
         tt1=fl[7+2*nr-1];
         ttn=fl[5+2*nr+2*np-1];
         if (temp < dn*tt1 or temp > up*ttn) { 
           //call error('iel',&'bad temperature for debye-waller factor',' ')
           throw std::exception();
         }
         if (tt1 > temp) fl[7+2*nr-1]=temp;
         if (ttn < temp) fl[5+2*nr+2*np]=temp;
         ip=2;
         ir=1;
         auto out = terpa(dwa,temp,fl,ip,ir);
         tnxt = std::get<0>( out ); 
         idis = std::get<1>( out );
      }
   } 
   else {
     //call error('iel','unknown material identifier.',' ')
     throw(std::exception());
    }
   c1=sb/(2*natom);

   // check on calcem energy grid
   nne=0;
   while (true) {
     if (esi[nne+1-1] == 0) break;
     nne=nne+1;
   }
   //allocate(xie(nne))
   Range xie( nne );

   // write head and tab2 records for mf6
   // in lanl format
 
   /*
   std::vector< njoy::ENDFtk::section::Type<6>::ReactionProduct > products {
   njoy::ENDFtk::section::Type<6>::ReactionProduct(
     // multiplicity
     // ZAP     AWP    LIP  LAW  NP   Interpolants
     { 1001., 0.9986234, 0, 1, { 4 }, { 2 },
       // Energies Vector
       { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
         // Multiplicities Vector
         { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } },

          // distribution
          { njoy::ENDFtk::section::Type<6>::ContinuumEnergyAngle(
	    // LAW LEP  NE    NR
            1, 2, { 2 }, { 1 },
            { njoy::ENDFtk::section::Type<6>::ContinuumEnergyAngle::LegendreCoefficients(
	    //  1st Energy ND LANG NEP    (note that NW=12 b/c length of next vec)
                      1e-5, 0, 1, 4,
	    // These are ordered Energy, Coeff1, Coeff2, Energy, Coeff1, Coeff2 so 
	    // that E1=1.0, E2=4.0, etc.
                      { 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12. } ),
             njoy::ENDFtk::section::Type<6>::ContinuumEnergyAngle::LegendreCoefficients(
             // 2nd Energy  ND LANG NEP   (NW=6  b/c length of vec)
             2e+7, 0, 1, 2, { 1., 2., 3., 4., 5., 6.} ) } ) } ) };


    int mt = 40000000;
    int jp = 0;
    int lct = 6;
    int nk = 0;

    njoy::ENDFtk::section::Type< 6 > chunk( mt, za, awr, jp, lct, std::move( products ) );
    std::cout << chunk.ZA() << std::endl;
    std::cout << chunk.AWR() << std::endl;
    std::cout << chunk.JP() << std::endl;
    std::cout << chunk.LCT() << std::endl;
    std::cout << chunk.NK() << std::endl;
    std::cout << chunk.MT() << std::endl;
  

    */

   ltt=6;
   math=matdp;
   mfh=6;
   mth=mtref+1;
   scr[1]=za;  // ZA
   scr[2]=awr; // AWR
   scr[3]=0;   // JP
   scr[4]=ltt; // LCT       // temporary flag for incoherent inelastic data
   scr[5]=0;   // NK
   scr[6]=0;   // Zero
   nw=6;
   //call contio(0,0,nscr,scr,nb,nw)
   scr[1]=1;  // ZAP
   scr[2]=1;  // AWP
   scr[3]=-2; // LIP       // special flag for incoherent inelastic data
   scr[4]=1;  // LAW       // law=1 for incoherent inelastic data
   scr[5]=1;  // NR
   scr[6]=2;  // NP / E_int
   scr[7]=2;
   scr[8]=2;
   scr[9]=1.e-5;
   scr[10]=1;
   scr[11]=emax;
   scr[12]=1;
   nw=12;
   // call tab1io(0,0,nscr,scr,nb,nw)
   scr[1]=temp;
   scr[2]=0;
   scr[3]=3; // LANG=3 is a special flag for equally probable cosines
             // yeah buddy that's fine and all, but like that's not mentioned 
	     // at all in the ENDF manual so..
   scr[5]=1;
   scr[6]=nne;
   scr[7]=nne;
   scr[8]=2;
   nw=8;
   //call tab2io(0,0,nscr,scr,nb,nw)
   n=nbin;
   nup=n;
   if (nup > nupmax) nup=nupmax;
   nup1=nup+1;
   nw=n+8;

   // compute cross sections on calcem energy grid
   // and equi-probable angles.
   for ( int iex = 0; iex < nne; ++iex ){
      e = esi[iex];
      c2 = 2*e*dwa;
      uLeft=-1;
      //rc2=1/c2;
      //x1=exp(-4*e*dwa);

      // This is the incoh. elastic xs sigma from Eq. 232. This is assuming
      // equiprobable angles. This is also the same as leapr's Eq. 547
      xsec = (sb*0.5) * ( 1.0 - exp(-4.0*e*dwa) ) / ( 2.0*e*dwa );

      scr[1] = 0;     scr[2] = e; scr[3] = 0; scr[4] = 0; scr[5] = n + 2;
      scr[6] = n + 2; scr[7] = e; scr[8] = 1;

      for ( int iu = 0; iu < n; ++iu ){

         //x2 = exp(-(2*e*dwa)*(1-uLeft));
         // This is mu_i of Eq. 234
         uRight = 1 + 1/(2*e*dwa) * log( ( 1 - exp(-4*e*dwa) ) / n + 
                                         exp( -2*e*dwa*(1-uLeft) ) );

         // This is Eq. 233, and represents the selected discrete cosine of the
         // ith bin
         scr[8+iu] = n / ( 2*e*dwa * ( 1 - exp(-4*e*dwa) ) ) *
                     ( exp( -2*e*dwa*(1-uRight) ) * ( 2*e*dwa*uRight-1 )
                     - exp( -2*e*dwa*(1-uLeft ) ) * ( 2*e*dwa*uLeft -1 ) );
 
         uLeft = uRight;
      }

      xie[iex] = xsec;
      //call listio(0,0,nscr,scr,nb,nw)
   }
   for ( int iex = 0; iex < ne; ++iex ){
      // call finda(iex,ex,nex,iold,bufo,nbuf)
      for ( int ix = 0; ix < nex; ++ix ){
         ej[ix]=ex[ix];
      }
      ej[nj] = (iex == ne) ? 0 : terp(esi,xie,ex[0],3);
      iet    = (iex == ne) ? -iex : iex;;
      //call loada(iet,ej,nj,inew,bufn,nbuf)
   }
   isave=iold;
   iold=inew;
   inew=isave;
   nex=nj;
   //call asend(0,nscr)
   auto ncdse=5+ne*((n+11)/6);
   return;
   std::cout << idis+iet+nw+nup1 << std::endl;
   std::cout << c1+c2+tnxt+math+mth+mfh << std::endl;

}

