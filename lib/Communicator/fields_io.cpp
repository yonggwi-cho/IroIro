/*! 
 * @file fields_io.cpp 
 *
 * @brief Declarations of MPI safe read/write routines for fields
 *
 * Time-stamp: <2013-06-03 15:26:58 neo>
 */

#include "fields_io.hpp"

#include <stdio.h>
#include <string.h>

namespace CCIO {
  Text_header::Text_header(){
  };

  void Text_header::add_element(std::string key, std::string value){
    tokens.insert(std::pair<std::string, std::string>(key, value));
  }

  void Text_header::get_value(std::string key, int& value){
    value = atoi(tokens[key].c_str());
  }

  void Text_header::get_value(std::string key, double& value){
    value = atof(tokens[key].c_str());
  }

  void Text_header::get_value(std::string key, std::string& value){
    value.assign(tokens[key].c_str());
  }

  void Text_header::print_map(){
    std::map<std::string, std::string>::iterator it;
    for (it=tokens.begin(); it!=tokens.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
  }

  QCDheader* ReadNERSCheader(FILE *in, fpos_t *pos) {
#define MAX_LINE_LENGTH 1024
    Text_header* TH = new Text_header;
    char *key, *val;
    char line[MAX_LINE_LENGTH];
    int len;
    /* Begin reading, and check for "BEGIN_HEADER" token */
    fgets(line,MAX_LINE_LENGTH,in);
    if (strcmp(line,"BEGIN_HEADER\n")!=0){
      CCIO::cout << "NERSC type header not found!\nExiting...\n";
      exit(1);
    }
    
    while(1){
      fgets(line,MAX_LINE_LENGTH,in);
      if (strcmp(line,"END_HEADER\n")==0) {
	break;}

      /* Divide in tokens */
      key = strtok(line, " =");
      val = strtok(NULL, "\n");
      /* Store in the map for future search */
      TH->add_element(std::string(key), std::string(val+2));
    }
   
    TH->print_map();
    return TH;
  }

  void NERSCtoIROIRO_f(double* out, FILE* inputFile, int block, bool is3x2){
    //Allocate enough space
    float *uin = (float*) malloc(block*sizeof(float));
    size_t res = ReadStdBinary_Float(uin, inputFile, block);
#ifndef BIG_ENDIAN_TYPE
    byte_swap(uin, block);
#endif
    if (is3x2)
      reconstruct3x3<float>(out, uin, block);
    else{
      for (int i =0; i < block; i++)
	out[i] = (double) uin[i];
    }
    free(uin);
  }

  void NERSCtoIROIRO_d(double* out,FILE* inputFile, int block, bool is3x2){
    //Allocate enough space
    double *uin = (double*) malloc(block*sizeof(double));
    size_t res = ReadStdBinary(uin, inputFile, block);
#ifndef BIG_ENDIAN_TYPE
    byte_swap(uin, block);
#endif
    if (is3x2)
      reconstruct3x3<double>(out, uin, block);
    else
      memcpy(out, uin, sizeof(uin));
    free(uin);
  }

  void ReadNERSCFormat(double* buffer,FILE *inputFile,
		       int block_size,
		       int tot_vol,int tot_in,int tot_ex,
		       QCDheader* QH){
    size_t res;
    std::string datatype;
    std::string floating_point; //32 or 64
    char * uin;
    bool is3x2 = false;
    QH->get_value("DATATYPE", datatype);
    QH->get_value("FLOATING_POINT", floating_point);
    std::cout << "fl : '"<< floating_point << "'\n";
  
    int bl = 0;
    if (datatype.compare("4D_SU3_GAUGE")==0){
      bl= block_size/3*2;
      is3x2 = true;
    }
    else 
      if (datatype.compare("4D_SU3_GAUGE_3x3")==0)
	bl= block_size;
    
    if (bl == 0)
      Errors::IOErr(Errors::GenericError, "Corrupted header");
    
    if ((floating_point.compare("IEEE32")==0) ||(floating_point.compare("IEEE32BIG")==0) ){
    std::cout << "floating point\n";
      NERSCtoIROIRO_f(buffer, inputFile,  bl, is3x2);
      }
    else 
      if (floating_point.compare("IEEE64BIG")==0){
	std::cout << "double floating point\n";

	NERSCtoIROIRO_d(buffer, inputFile, bl, is3x2);
      }
    
    // perform checks against header information
  }


  QCDheader* NOheader(FILE *inputFile, fpos_t *pos){};
}