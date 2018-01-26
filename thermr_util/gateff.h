#include <iostream>

auto gateff( std::vector<double>& temp, std::vector<double>& eftemp, 
  int ntemp, int mat){ 
 /*-------------------------------------------------------------------
  * Default effective temperatures to values from General Atomic
  * report, if available.
  *       1002      h(h2o)
  *       1004      d(d2o)
  *       1064      be
  *       1065      graphite
  *       1095      benzine (c6h6)
  *       1096      zr(zrh)
  *       1097      h(zrh)
  *       1099      beo
  *       1114      h(ch2)
  *-------------------------------------------------------------------
  */
  int i, j, jmat;
  double diff, test;
  int ntabl = 67;
  std::vector<double> tabl = { 1002, 296, 1396.8, 1002, 350, 1411.6, 1002, 400,
    1427.4, 1002, 450, 1444.9, 1002, 500, 1464.1, 1002, 600, 
    1506.8, 1002, 800, 1605.8, 1002, 1000, 1719.8, 1004, 296, 940.91, 
    1004, 350, 961.62, 1004, 400, 982.93, 1004, 450, 1006.1, 1004, 500, 
    1030.9, 1004, 600, 1085.1, 1004, 800, 1209, 1004, 1000, 1350, 1064, 
    296, 405.64, 1064, 400, 484.22, 1064, 500, 568.53, 1064, 600, 657.66, 
    1064, 700, 749.69, 1064, 800, 843.63, 1064, 1000, 1035, 1064, 1220, 1229.3, 
    1065, 296, 713.39, 1065, 400, 754.68, 1065, 500, 806.67, 1065, 600, 
    868.38, 1065, 700, 937.64, 1065, 800, 1012.7, 1065, 1000, 1174.9, 1065, 
    1200, 1348.2, 1065, 1600, 1712.9, 1065, 2000, 2091, 1095, 296, 1165.9, 
    1095, 350, 1177.8, 1095, 400, 1191.4, 1095, 450, 1207.7, 1095, 500, 
    1226, 1095, 600, 1268.7, 1095, 800, 1373.4, 1095, 1000, 1497.7, 1096, 
    296, 317.27, 1096, 400, 416.29, 1096, 500, 513.22, 1096, 600, 
    611.12, 1096, 700, 709.60, 1096, 800, 808.43, 1096, 1000, 1006.8, 1096, 
    1200, 1205.7, 1097, 296, 806.79, 1097, 400, 829.98, 1097, 500, 868.44, 1097, 600, 920.08, 1097, 700, 981.82, 1097, 800, 1051.1, 1097, 1000, 1205.4, 1097, 1200, 1373.4, 1099, 296, 596.4, 1099, 400, 643.9, 1099, 500, 704.6, 1099, 600, 775.3, 1099, 800, 935.4, 1099, 1000, 1109.8, 1099, 1200, 1292.3, 1114, 296, 1222, 1114, 350, 1239.0 }

   for ( size_t i = 0; i < ntemp; ++i ){
      if (eftemp(i) == 0) {
        for ( size_t j = 0; j < ntabl; ++j ){
            jmat=nint(tabl(1,j))
            if (jmat.eq.mat) then
               test=5
               diff=tabl(2,j)-temp(i)
               if (abs(diff).le.test) then
                  eftemp(i)=tabl(3,j)
              } // end if 
            } // end if 
          } // end for 
         if (eftemp[i] == 0) eftemp[i]=temp[i];
      } // end if 
   } // end do 
   return;
}




