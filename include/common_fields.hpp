/*!
 * @file common_fields.hpp
 *
 * @brief Code for general fields initializations
 *
 */

#ifndef COMMON_FIELDS_H_
#define COMMON_FIELDS_H_

#include "Main/gaugeConf.hpp"
#include "include/geometry.h"
#include "include/field.h"
#include "include/format_G.h"

typedef Format::Format_G GaugeFieldFormat;/**< Format of gauge field
					     at compilation time */


/*!
 * @brief A Class to handle gauge fields
 * @author <a href="http://suchix.kek.jp/guido_cossu/">Guido Cossu</a> 
 * 
 * This class handles the Format 
 * and Field class in order to bind them 
 * into a single self contained object
 * that knows the details of storage
 *
 */
class GaugeField {
public:
  GaugeFieldFormat Format;/**< Format specifier */
  Field U; /**< Configuration container */
  
  /*! 
   * Default constructor\n 
   * Takes Geometry class as input
   * @param geom Defines the lattice geometry
   */
  GaugeField(Geometry geom): 
    Format(GaugeFieldFormat( geom.parameters->Nvol() )),
    U(Field(Format.size())){}
  
  /*!
   * Initializes the gauge field with an \n
   * external configuration in file <Filename>
   *
   * Configuration type in XML: TextFile
   * @param Filename String containing the filename
   */
  void initializeTxt(const std::string &Filename) {
    GaugeConf_txt gconf(Format,Filename);
    gconf.init_conf(U);
  }

  /*!
   * Initializes the gauge field with an \n
   * external configuration in binary format
   * contained in file <Filename>
   *
   * Configuration type in XML: Binary
   * @param Filename String containing the filename
   */
  void initializeBin(const std::string &Filename) {
    GaugeConf_bin gconf(Format,Filename);
    gconf.init_conf(U);
  }

 /*!
   * Initializes the gauge field with \n
   * unit matrices
   *
   * Configuration type in XML: Unit
   */
  void initializeUnit(){
    GaugeConf_unit gconf(Format);
    gconf.init_conf(U);
  }


  int initialize(XML::node node) {
    try {
      XML::descend(node, "Configuration");
      if (!XML::attribute_compare(node,"Type","TextFile")){
	std::string filename(node.child_value());
	initializeTxt(filename);
	return 0;
      }
      if (!XML::attribute_compare(node,"Type","Unit")){
	initializeUnit();
	return 0;
      }
      if (!XML::attribute_compare(node,"Type","Binary")){
	std::string filename(node.child_value());
	initializeBin(filename);
	return 0;
      }
    } catch(...) {
      std::cout << "Error in initialization of gauge field "<< std::endl;
    }
  }


};

#endif //COMMON_FIELDS_H_
