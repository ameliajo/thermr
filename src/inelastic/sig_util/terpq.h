#include <vector>
#include "inelastic/sig_util/terp1.h"

template <typename F>
auto terpq( F x1, F x2, F x3, F x, F y1, F y2, F y3 ){
  /*-------------------------------------------------------------------
   * Compute y(x) by quadratic interpolation,
   * except use log-lin if x < x1 and lin-lin if x > x3.
   * and use lin-lin if the function takes big steps (corners).
   *-------------------------------------------------------------------
   */
  double b, c, step = 2;

  // If desired value x is below known range (x1,x2,x3), then log-lin 
  // interpolation is used. 
   if (x < x1) {
     return (y1 > y2) ? y1 : terp1( x1, y1, x2, y2, x, 3 );
   }

  // If desired value x is above known range (x1,x2,x3), then lin-lin 
  // interpolation is used. 
   if (x > x3) {
     return (y3 > y2) ? y3 : terp1( x2, y2, x3, y3, x, 2 );
   }

   // Big steps are taken, so use lin-lin interpolation
   if (std::abs(y1-y2) > step or std::abs(y2-y3) > step) {
     return (x < x2) ? terp1(x1,y1,x2,y2,x,2) : terp1(x2,y2,x3,y3,x,2);
   }

   // Small steps are taken across a reasonable range, so we use quadratic
   // interpolation
   b = (y2-y1) * (x3-x1) / ( (x2-x1) * (x3-x2) ) - 
       (y3-y1) * (x2-x1) / ( (x3-x1) * (x3-x2) );

   c = (y3-y1) / ( (x3-x1) * (x3-x2) ) - 
       (y2-y1) / ( (x2-x1) * (x3-x2) );

   return y1 + b * (x-x1) + c * (x-x1) * (x-x1);

}

