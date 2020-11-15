#ifndef ROTOR_H
#define ROTOR_H

class Rotor{
  int rotor_mapping[26];  // 26 alphabets
  int input_mapping[26];  // to handle rotational of rotor
  int notch[26];          // contains information on the rotor's notch position  
  int start_pos;          // rotor's starting position based on config file
  int rotor_pos;          // rotor's position in the machine (0 = lefthand most rotor)  

  // used in default constructor to initialise *one* rotor
  void load_rotor_setting(const char* filename, const int pos_array[], const int pos);

  // to rotate rotor by one position
  void rotate_rotor();
  
 public:
 
  // default constructor. Note that rotor_pos starts from 0 for the left most rotor.
  Rotor(){};
  Rotor(const char*filename, const int pos_array[], const int rotor_pos, const int number_of_rotors){  
    load_rotor_setting(filename, pos_array, rotor_pos);
    this -> rotor_pos = rotor_pos;
  }

  // controls the rotation of each rotor based on rotor and notch position
  void rotor_rotation(Rotor enigma_rotors[], int number_of_rotors, int rotor_num);  

  // print rotor details for debugging purposes
  void print_rotor_setting();   

  // to decode/encode char from right of rotor and output to left
  int right_to_left(int right_input);   

  // to decode/encode char from left of rotor and output to right
  int left_to_right(int left_input);   
};

// ============== non-member functions ==============

// loads rotor starting position from config file
void load_rotor_pos(const char* filename, int pos_array[], int number_of_rotors);

// initialises a *group* of rotors when the objects are first created
void initialise_enigma_rotors(int pos_array[], Rotor enigma_rotors[], int number_of_rotors, char* argv[]);


#endif
