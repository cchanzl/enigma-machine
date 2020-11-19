#ifndef PLUGBOARD_H
#define PLUGBOARD_H

# include "constants.h"

/* This is a user defined class for Plugboard, one of the key components in the engima machine.
   There can only be one plugboard defined for an engima machine.
   Please refer to the comments beside each member for more information.
 */

class Plugboard{
private:
  int pb_mapping[NUM_OF_ALPHABETS]; // Specifies connection between two contacts. the numbers are the 0-based index into the alphabet.

  // used in default constructor to initialise pb_mapping based on input
  void load_pb_setting(const char* filename, int pb_mapping[NUM_OF_ALPHABETS]);

 public:
  Plugboard(const char* filename){
    load_pb_setting(filename, pb_mapping);
  }

  // these two functions scrambles input through the plugboard from either direction
  int right_to_left(int input) const;
  int left_to_right(int input) const;
};


#endif
