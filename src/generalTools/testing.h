#include <range/v3/all.hpp>

template <typename V>
void checkVec( V y1, V y2, float tol){
  size_t size_to_check = y1.size();
  REQUIRE( y1.size() == y2.size() );
  for (size_t i = 0; i < size_to_check; ++i){
    REQUIRE( y2[i] == Approx(y1[i]).epsilon(tol) );
  }
}



template <typename V>
void checkVec( V y1, V y2, bool checkAll=true, float tol=1e-6 ){
  size_t size_to_check = y1.size();
  if (checkAll){
    REQUIRE( y1.size() == y2.size() );
  }
  else {
    size_to_check = y1.size() < y2.size() ? y1.size() : y2.size();
  }
  for (size_t i = 0; i < size_to_check; ++i){
    REQUIRE( y2[i] == Approx(y1[i]).epsilon(tol) );
  }
}

template <typename V, typename Int>
void checkVec( V y1, V y2, Int end, float tol=1e-6 ){
  for (Int i = 0; i < end; ++i){
    REQUIRE( y2[i] == Approx(y1[i]).epsilon(tol) );
  }
}

template <typename V>
void checkPartOfVec( V& y1, V& y2, int offset=0, float tol=1e-6 ){
  using std::abs;
  for (size_t i = 0; i < y2.size(); ++i){
    REQUIRE( y2[i] == Approx(y1[i+offset]).epsilon(tol) );
  }
}



template <typename V>
void restAreZero(int n, const V& vec){
  for (size_t i = n; i < vec.size(); ++i){
    REQUIRE( 0.0 == Approx(vec[i]).epsilon(1e-6) );
  }
}

template <typename Float>
auto makeGrid( int len, Float delta ){
  return ranges::view::iota(0,len) 
       | ranges::view::transform([delta](auto x){ return x*delta;});
}

auto equal = [](auto x, auto y, double tol = 1e-6){return x == Approx(y).epsilon(tol);};
auto equal_1e5 = [](auto x, auto y, double tol = 1e-5){return x == Approx(y).epsilon(tol);};
auto equal_1e4 = [](auto x, auto y, double tol = 1e-4){return x == Approx(y).epsilon(tol);};
auto equal_1e3 = [](auto x, auto y, double tol = 1e-3){return x == Approx(y).epsilon(tol);};

