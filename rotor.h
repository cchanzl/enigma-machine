#ifndef ROTOR_H
#define ROTOR_H

# include "constants.h"

/* This is a user defined class for Rotor, one of the key components in the engima machine.
   There can be multiple Rotors defined as required by the user.
   Please refer to the comments beside each member for more information.
 */
class Rotor{
  // Internal wiring of a rotor, using a 0-based index. If rotor_mapping[0] == "2", the rotor maps "A" to "C".
  int rotor_mapping[NUM_OF_ALPHABETS];

  // Frame of reference for the rotor, using a 0-based index. If input_mapping[0] == "25", "Z" is at the 12 o'clock position
  int input_mapping[NUM_OF_ALPHABETS];
  
  int notch[26];          // contains information on the rotor's notch position  
  int start_pos;          // Sets the rotor's starting position based on config file
  int rotor_pos;          // rotor's position in the machine (0 = lefthand most rotor)  

  // used in default constructor to initialise *one* rotor.
  void load_rotor_setting(const char* filename, const int pos_array[], const int pos);

  // to rotate (eg 'Z' becomes 'Y') input_mapping of a rotor by one position
  void rotate_rotor();

  // this function updates input_mapping with a new position when it rotate is called
  void update_input_mapping(int start_pos);
  
 public:
 
  // default constructor. Note that rotor_pos starts from 0 for the left most rotor.
  Rotor(){};
  Rotor(const char*filename, const int pos_array[], const int rotor_pos){   
    load_rotor_setting(filename, pos_array, rotor_pos);
    this -> rotor_pos = rotor_pos;
  }

  // controls the rotation of each rotor based on rotor and notch position
  void rotor_rotation(Rotor enigma_rotors[], const int number_of_rotors, const int rotor_num);  

  // to decode/encode char entering from right of rotor and output to left
  int right_to_left(const int right_input);   

  // to decode/encode char entering from left of rotor and output to right
  int left_to_right(const int left_input);   
};

// ============== non-member functions ==============

// loads rotor starting position from config file
void load_rotor_pos(const char* filename, int pos_array[], const int number_of_rotors);

// initialises a *group* of rotors when the objects are first created
void initialise_enigma_rotors(Rotor enigma_rotors[], const int number_of_rotors, char* argv[]);


#endif
