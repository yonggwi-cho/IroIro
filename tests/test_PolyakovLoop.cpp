/* @file test_PolyakovLoop.cpp
 * @brief implementation of the Test_PolyakovLoop.cpp class
 */
#include "Measurements/GaugeM/polyakovLoop.hpp"
#include "test_PolyakovLoop.hpp"
#include <complex>
#include <cstring>
#include <iomanip>
using namespace std;

int Test_PolyakovLoop::run(){
  XML::node pnode = input_.node;
  XML::descend(pnode,"PolyakovLoop");
  const char* dir_name = pnode.attribute("dir").value();

  site_dir dir;
  if(     !strcmp(dir_name,"X")) dir = XDIR;
  else if(!strcmp(dir_name,"Y")) dir = YDIR;
  else if(!strcmp(dir_name,"Z")) dir = ZDIR;
  else if(!strcmp(dir_name,"T")) dir = TDIR;
  else {
    CCIO::cout<<"No valid direction available"<<endl;
    abort();
  }
  PolyakovLoop plp(dir);

  complex<double> pf = plp.calc_SUN(*(input_.gconf));
  double          pa = plp.calc_SUNadj(*(input_.gconf));
  
  CCIO::cout<<"fundamental representation:"<<endl;
  CCIO::cout<< setw(20)<<pf.real()<<" "<< setw(20)<<pf.imag()<<endl;
  CCIO::cout<<"adjoint representation:"<<endl;
  CCIO::cout<< setw(20)<<pa<<endl;
  
  return 0;
}
