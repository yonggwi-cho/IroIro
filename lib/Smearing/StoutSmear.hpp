/*
  @file StoutSmear.hpp

  @brief Declares Stout smearing class

 */

#ifndef STOUT_SMEAR_H_
#define STOUT_SMEAR_H_

#include <valarray>

#include "include/commonPrms.h"
#include "include/common_fields.hpp"
#include "APEsmear.hpp"


class Field;

/*!
  @brief Stout smearing of link variable.

 */
class Smear_Stout: public Smear {

 private:
  const int Ndim;
  const std::valarray<double> d_rho;
  const Format::Format_G& Gformat;
  Smear_APE APEbase;


  double func_xi0(double w) const;
 public:
  Smear_Stout(Smear_APE& base,
	      const Format::Format_G& gf):
    APEbase(base),
    Ndim(CommonPrms::Ndim()),
    Gformat(gf){};

  Smear_Stout(const Format::Format_G& gf):
    APEbase(gf),
    Ndim(CommonPrms::Ndim()),
    Gformat(gf){};

  

  ~Smear_Stout(){};

  void smear(Field&,const Field&) const;
  void BaseSmear(Field&, const Field&) const;
  void BaseDerivative(Field&, const Field&, const Field&) const;
  void exponentiate_iQ(GaugeField&, const GaugeField&) const;
};

#endif  