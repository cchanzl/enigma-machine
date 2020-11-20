#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "constants.h"

/* This is a user defined class for Reflector, one of the key components in the engima machine.
   There can only be one reflector defined for an engima machine.
   Please refer to the comments beside each member for more information.
 */
class Reflector{
private:
  int rf_mapping[NUM_OF_ALPHABETS];  // Internal wiring of the reflector.

  // used in default constructor to initialise rf_mapping based on input
  void load_rf_setting(const char* filename, int rf_mapping[NUM_OF_ALPHABETS]);
  
public:
  Reflector(const char* filename){
    load_rf_setting(filename, rf_mapping);
  }

  // this function scrambles input through the reflector 
  int reflector_output(const int input) const;
};

#endif
