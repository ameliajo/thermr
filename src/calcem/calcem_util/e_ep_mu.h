#include "calcem/calcem_util/e_ep_mu_util/ep_mu.h"



template <typename Range>
auto e_ep_mu( Range eVec, const double& tev, const double& tol, const int lat, 
  const int iinc, const int lasym, const Range& alphas, const Range& betas, 
  const Range& sab, const double& az, const Range& boundXsVec, 
  const double& teff, const int nbin, const double& temp ){

  Range lastVals(5,0.0);
  double eNow, ePrime;
  int imax = 20;
  Range y(20*65,0.0);

  std::vector<Range> total_SCR(eVec.size());
  std::vector<Range> total_OutputData(eVec.size());


  for ( size_t iEnergy = 0; iEnergy < eVec.size(); ++iEnergy ){
    Range scr(y.size()*5,0.0);
    eNow = eVec[iEnergy];
    if (temp > 3000.0){ eNow = highTempApprox(temp,eNow,eVec[0],eVec[eVec.size()-1]); }
    eNow = sigfig(eNow,8,0);
    eVec[iEnergy] = eNow;

    ePrime = 0.0;
    Range s(nbin,0.0);
    double pdf = sigl(0.0,eNow,tev,tol,lat,iinc,alphas,betas,sab,az,lasym,boundXsVec,
                     teff,s,true);
    y[0*imax+0] = pdf;
    for (int il = 1; il < nbin+1; ++il){y[il*imax+0] = s[il-1];}


    int j = 0, jbeta = -int(betas.size());

    
    auto out = prepareEpMu( eNow, j, tev, tol, lat, iinc, lasym, 
    alphas, betas, sab, az, boundXsVec, teff, nbin, jbeta, scr, lastVals, y);
    


    total_SCR[iEnergy]        = scr;
    total_OutputData[iEnergy] = out;


    std::cout << std::endl << std::endl << std::endl;
    std::cout << total_SCR.size() << std::endl;
    std::cout << (total_SCR[0]|ranges::view::all) << std::endl;
    //for (size_t i = 0; i < eVec.size(); ++i){
      //std::cout << i << "    " << eVec[i] << std::endl;
      //std::cout << i << "    " << total_SCR[i] << std::endl;
    //}
    std::cout << std::endl << std::endl << std::endl;

    
    return std::make_tuple(eVec,total_SCR,total_OutputData);
    //std::cout << "finished" << std::endl;
    //return std::make_tuple(eVec,total_SCR,total_OutputData);
    // 







  }
  return std::make_tuple(eVec,total_SCR,total_OutputData);

}




