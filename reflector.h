#ifndef REFLECTOR_H
#define REFLECTOR_H


/* This is a user defined class for Reflector, one of the key components in the engima machine.
   There can only be one reflector defined for an engima machine.
   Please refer to the comments beside each member for more information.
 */
class Reflector{
  int rf_mapping[26];  // Internal wiring of the reflector.

  // used in default constructor to initialise rf_mapping based on input
  void load_rf_setting(const char* filename, int rf_mapping[26]);
  
 public:
  Reflector(const char* filename){
    load_rf_setting(filename, rf_mapping);
  }

  // this function scrambles input through the reflector 
  int reflector_output(int input) const;
};

#endif
