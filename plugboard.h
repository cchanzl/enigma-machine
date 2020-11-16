#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class Plugboard{
  int pb_mapping[26];

  void load_pb_setting(const char* filename, int pb_mapping[26]);

 public:
  
  Plugboard(const char* filename){
    load_pb_setting(filename, pb_mapping);
  }

  int right_to_left(int input);
  int left_to_right(int input);
};


#endif
