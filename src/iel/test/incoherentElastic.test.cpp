#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "iel/incoherentElastic.h"
#include <range/v3/all.hpp>
#include "generalTools/testing.h"

TEST_CASE( "get equiprobable scattering angles" ){
  GIVEN( "an initial energy (which is also the final energy here)" ){
    double E = 1e-2, debyeWaller = 10.0, sigma_b = 2.5, xs;
    int numAtoms = 1, numAngles = 8;
    std::vector<double> cosines ( numAngles, 0.0 );
    std::vector<double> energies {1e-5, 1e-4, 1e-3, 1e-2, 1e-1};
    std::vector<std::vector<double>> correctCosinesVec 
    {
      {-0.8749771,-0.6249396,-0.3749146,-0.1249021, 0.1250979, 0.3750854, 0.6250604, 0.8750229 },
      {-0.8747706,-0.6243953,-0.3741454,-0.1240207, 0.1259790, 0.3758537, 0.6256037, 0.8752289 },
      {-0.8726826,-0.6189088,-0.3664165,-0.1151928, 0.1347749, 0.3834992, 0.6309923, 0.8772663 },
      {-0.8493610,-0.5596117,-0.2857415,-2.60998E-2, 0.2207195, 0.4559238, 0.6805574, 0.8955298 },
      {-0.3270719, 0.1933194, 0.4351759, 0.5967253, 0.7184233, 0.8161444, 0.8978172, 0.9679844 },
    };
    for ( size_t i = 0; i < energies.size(); ++i ){
      getIncohElasticDataSingleEnergy(energies[i],debyeWaller,cosines);
      REQUIRE( ranges::equal( cosines, correctCosinesVec[i], equal ) );
    }
  } // GIVEN
} // TEST CASE



TEST_CASE( "incoherent elastic average scattering xs" ){
    double debyeWaller = 10.0, sigma_b = 2.5, xs;
    int numAtoms = 1;

    std::vector<double> 
      energyVec { 1e-5, 1e-4, 1e-3, 1e-2, 1e-1 },
      correctXS { 2.4995001, 2.4950067, 2.4506601, 2.0604997, 0.6135527 };

    for ( size_t i = 0; i < energyVec.size(); ++i ){
      REQUIRE( correctXS[i] == Approx(getIncohElasticXS(sigma_b,debyeWaller,
                                      energyVec[i],numAtoms)).epsilon(1e-6) );
    }
    

    debyeWaller = 34.957;
    sigma_b = 162.88;
    numAtoms = 1;

    energyVec = { 0.00001, 0.0000178, 0.000025, 0.000035, 0.00005, 0.00007, 
      0.0001, 0.000126, 0.00016, 0.0002, 0.000253, 0.000297, 0.00035, 0.00042, 
      0.000506, 0.000615, 0.00075, 0.00087, 0.001012, 0.00123, 0.0015, 0.0018, 
      0.00203, 0.002277, 0.0026, 0.003, 0.0035, 0.004048, 0.0045, 0.005, 0.0056, 
      0.006325, 0.0072, 0.0081, 0.009108, 0.01, 0.01063, 0.0115, 0.012397, 
      0.0133, 0.01417, 0.015, 0.016192, 0.0182, 0.0199, 0.020493, 0.0215, 0.0228, 
      0.0253, 0.028, 0.030613, 0.0338, 0.0365, 0.0395, 0.042757, 0.0465, 0.05, 
      0.056925, 0.0625, 0.069, 0.075, 0.081972, 0.09, 0.096, 0.1035, 0.111573, 
      0.12, 0.128, 0.1355, 0.145728, 0.16, 0.172, 0.184437, 0.2, 0.2277, 
      0.2510392, 0.2705304, 0.2907501, 0.3011332, 0.3206421, 0.3576813, 0.39, 
      0.4170351, 0.45, 0.5032575, 0.56, 0.625, 0.7 };

    correctXS = { 162.766177, 162.677469, 162.595642, 162.482084, 162.311945, 
      162.085463, 161.746530, 161.453553, 161.071497, 160.623565, 160.032615, 
      159.544222, 158.958574, 158.189480, 157.251404, 156.073138, 154.630197, 
      153.362606, 151.880641, 149.642888, 146.932757, 143.999042, 141.803628, 
      139.496539, 136.556492, 133.032434, 128.801762, 124.376802, 120.885466, 
      117.181960, 112.946452, 108.114287, 102.669377, 97.475420, 92.104811, 
      87.711433, 84.795662, 81.005013, 77.362184, 73.945169, 70.871378, 
      68.123109, 64.464103, 58.980092, 54.913544, 53.604411, 51.499027, 
      48.982806, 44.702911, 40.772715, 37.524707, 34.157953, 31.720115, 
      29.372364, 27.174729, 25.013159, 23.275766, 20.455913, 18.634770, 
      16.880935, 15.531029, 14.210309, 12.942841, 12.133937, 11.254677, 
      10.440335, 9.707164, 9.100466, 8.596750, 7.993383, 7.280373, 6.772440, 
      6.315759, 5.824298, 5.115765, 4.640151, 4.305837, 4.006395, 3.868254, 
      3.632897, 3.256697, 2.986820, 2.793193, 2.588577, 2.314639, 2.080107, 
      1.863775, 1.664085 };

    for ( size_t i = 0; i < energyVec.size(); ++i ){
      REQUIRE( correctXS[i] == Approx(getIncohElasticXS(sigma_b,debyeWaller,
                                      energyVec[i],numAtoms)).epsilon(1e-6) );
    }
 


} // TEST CASE
