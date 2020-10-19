#######################################################################
# Setup
#######################################################################

message( STATUS "Adding thermr unit testing" )
enable_testing()


#######################################################################
# Unit testing directories
#######################################################################

add_subdirectory( src/approximations/freeGas/test )
add_subdirectory( src/calcem/calcem_util/e_ep_mu_util/test )
add_subdirectory( src/calcem/calcem_util/e_mu_ep_util/test )
add_subdirectory( src/calcem/calcem_util/sig_util/test )
add_subdirectory( src/calcem/calcem_util/test )
add_subdirectory( src/calcem/test )
add_subdirectory( src/coh/coh_util/sigcoh_util/test )
add_subdirectory( src/coh/coh_util/test )
add_subdirectory( src/coh/test )
add_subdirectory( src/general_util/test )
add_subdirectory( src/iel/test )
add_subdirectory( src/temp_eff/temp_eff_util/test )
add_subdirectory( src/temp_eff/test )
add_subdirectory( src/test )