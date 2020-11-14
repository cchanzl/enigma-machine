#ifndef ROTOR_H
#define ROTOR_H

class Rotor{
  int rotor_mapping[26];  // 26 alphabets
  int input_mapping[26];  // to handle rotational of rotor
  int output_mapping[26];
  int notch;
  int start_pos;
  int rotor_pos;
  Rotor* left;            // pointer to left rotor  
  
  void load_rotor_setting(const char* filename, const int pos_array[], const int pos);
  
 public:
  // default constructor. Note that rotor_pos starts from 0 for the left most rotor.
  Rotor(const char*filename, const int pos_array[], const int rotor_pos){  
    load_rotor_setting(filename, pos_array, rotor_pos);
    this -> rotor_pos = rotor_pos;
  }
  void print_rotor_setting();    // print rotor details for debugging purposes
  void rotate_rotor();           //rotate rotor BEFORE it receives signal from pb
  int right_to_left(int right_input);    //to read in char from right and output to left
  int left_to_right(int left_input);    //to read in char from left and output to right
};

// non-member functions
void load_rotor_pos(const char* filename, int pos_array[], int number_of_rotors);
void initialise_enigma_rotors(int pos_array[], Rotor enigma_rotors[], int number_of_rotors, char* argv[]);


#endif
