/*!
 * @file test_wilson_EvenOdd.hpp
 *
 * @brief Tests for the propagators and sources
 *
 */
#ifndef TEST_WILSON_EVENODD_INCLUDED
#define TEST_WILSON_EVENODD_INCLUDED

#include "include/common_code.hpp"
#include "tests.hpp"

class Test_Wilson_EvenOdd : public TestGeneral{
private:
  XML::node Wilson_EO_node_;
  GaugeField& conf_;
public:

  Test_Wilson_EvenOdd(const XML::node node, GaugeField& conf)
    :Wilson_EO_node_(node),
     conf_(conf){}

  Test_Wilson_EvenOdd(GaugeField& conf)
    :conf_(conf){}

  int run();
};

#endif