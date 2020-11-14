#ifndef ROTOR_H
#define ROTOR_H

class Rotor{
  int rotor_mapping[26];  // 26 alphabets
  int input_mapping[26];  // to handle rotational of rotor
  int notch[26];
  int start_pos;
  int rotor_pos;
  Rotor* ptr_to_right_rotor;            // pointer to left rotor  
  
  void load_rotor_setting(const char* filename, const int pos_array[], const int pos);
  void rotate_rotor();           // to rotate rotor by one position
  
 public:
 
  // default constructor. Note that rotor_pos starts from 0 for the left most rotor.
  Rotor(const char*filename, const int pos_array[], const int rotor_pos, const int number_of_rotors){  
    load_rotor_setting(filename, pos_array, rotor_pos);
    this -> rotor_pos = rotor_pos;
  }

  void rotor_rotation(Rotor enigma_rotors[], int number_of_rotors, int rotor_num);
  void print_rotor_setting();    // print rotor details for debugging purposes
  int right_to_left(int right_input);    //to read in char from right and output to left
  int left_to_right(int left_input);    //to read in char from left and output to right
};

// non-member functions
void load_rotor_pos(const char* filename, int pos_array[], int number_of_rotors);
void initialise_enigma_rotors(int pos_array[], Rotor enigma_rotors[], int number_of_rotors, char* argv[]);


#endif
