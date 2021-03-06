/* @file test_PolyakovLoop.cpp
 * @brief implementation of the Test_PolyakovLoop.cpp class
 */

#include <stdio.h>
#include "Measurements/GaugeM/staples.hpp"
#include "Dirac_ops/dirac_Operator_FactoryCreator.hpp"
#include "test_ChiralCondensate.hpp"
#include "Measurements/FermionicM/chiral_condensate.hpp"
#include "Measurements/FermionicM/chiral_condensate_abs.hpp"
#include "Measurements/FermionicM/sources_factory.hpp"
#include "include/timings.hpp"
#include "include/messages_macros.hpp"

using namespace std;

int Test_ChiralCondensate::run(){
  XML::node ch_node = input_.node;
  XML::descend(ch_node,"ChiralCondensate",MANDATORY);

  /************************************************************************************/
  //
  // For 5-D Inversion
  //
  XML::node Kernel_node = ch_node;
  XML::descend(Kernel_node,"KernelDWF_4d");
  auto_ptr<DiracDWF4dFactory> 
    Wilson_Kernel_4d_factory(Diracs::createDiracDWF4dFactory(Kernel_node));
  auto_ptr<Dirac_DomainWall_4D> Wilson_Kernel_4d(Wilson_Kernel_4d_factory->getDirac(input_.config));

  /************************************************************************************/
  //
  // Constructs the Chiral condensate for DWF
  //
  ChiralCondDWF ChiralCond(*Wilson_Kernel_4d);

  /************************************************************************************/
  //
  // Constructs the source
  //

  XML::node Source_node = ch_node;
  XML::descend(Source_node,"Source");
  auto_ptr<SourceFactory> SrcFactory(Sources::createSourceFactory<Format::Format_F>(Source_node));
  auto_ptr<Source> src(SrcFactory->getSource());

  /************************************************************************************/
  //
  // Compute the condensate
  //

  int noise_samples = 1; //default
  bool measure_connected = false; //default
  XML::read(ch_node, "noise_samples", noise_samples);

  XML::read(ch_node, "connected_susc", measure_connected);

  if (measure_connected){
    CCIO::cout << "---------- Measuring connected susceptibilities\n";
    double conn_pi = ChiralCond.connected_susc(*src, noise_samples);
  } else {
    CCIO::cout << "---------- Measuring disconnected susceptibilities\n";
  double psibar_psi = ChiralCond.calc(*src, noise_samples);
  CCIO::cout << "Chiral condensate: "<< psibar_psi/CommonPrms::instance()->Lvol() << "\n";
  }
 
  return 0;
}
