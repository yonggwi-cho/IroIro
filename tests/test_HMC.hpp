//------------------------------------------------------------------------
/*!
 * @file test_HMC.hpp
 *
 * @brief Test for %HMC update classes
 *
 * @author Jun-Ichi Noaki
 * @author <a href="http://suchix.kek.jp/guido_cossu/">Guido Cossu</a>
 */
//------------------------------------------------------------------------
#ifndef TEST_HMC_H_
#define TEST_HMC_H_

#include "include/common_code.hpp"

#include "tests/tests.hpp"


class Test_HMC: TestGeneral{
private:
  XML::node HMC_node;
  GaugeField& Gfield_;
public:
  Test_HMC(XML::node node,GaugeField& Gfield):HMC_node(node),
					      Gfield_(Gfield){}

  int run();  
};


#endif
