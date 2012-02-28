//---------------------------------------------------------------------
/*! @file sunMatUtils.hpp
  @brief \f$SU(N)\f$ Matrices linear algebra Utilities

  Class declarations
*/ 
//---------------------------------------------------------------------

#ifndef SUNMAT_UTILS_H_
#define SUNMAT_UTILS_H_

#include "sunMat.hpp"
#include "include/common_fields.hpp"

using namespace std;


namespace SUNmatUtils{
  SUNmat unity();
  SUNmat zero();
  double ReTr(const SUNmat&);  
  double ImTr(const SUNmat&);
  const SUNmat dag(const SUNmat&);  
  const SUNmat xI(const SUNmat&);  
  const SUNmat operator+(const SUNmat&, const SUNmat&);
  const SUNmat operator-(const SUNmat&, const SUNmat&);
  const SUNmat operator*(const SUNmat&, const SUNmat&);
  const SUNmat reunit(const SUNmat&);
  const valarray<double> trace_less(const SUNmat&);
  const SUNmat anti_hermite_traceless(const SUNmat&);
  const SUNmat anti_hermite(const SUNmat&);

  //BLAS style multiplications for optimization purposes
  // Matrix-matrix
  const SUNmat gemm(const SUNmat&, const SUNmat&);
  // Matrix-matrix^dag)
  const SUNmat gemmd(const SUNmat&, const SUNmat&);
  // (Matrix^dag)-matrix
  const SUNmat gemdm(const SUNmat&, const SUNmat&);
  //////////////////////////////////////////////////////

  void SUNprint(const SUNmat&);

}//endof namespace SUNmat_utils

#endif
