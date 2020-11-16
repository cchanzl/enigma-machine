#ifndef REFLECTOR_H
#define REFLECTOR_H

class Reflector{
  int rf_mapping[26];

  void load_rf_setting(const char* filename, int rf_mapping[26]);
  
 public:
  Reflector(const char* filename){
    load_rf_setting(filename, rf_mapping);
  }
  int reflector_output(int input);
};

#endif
