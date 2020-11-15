#include <iostream>
#include <iomanip>

#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"
#include "enigma.h"


using namespace std;

int main (int argc, char** argv){

  // =========== SETTING PLUGBOARD ===========
  int pb_mapping[26];

  /*
  // printing original plugboard settings
  cout << "The plugboard settings are: "<< endl;
  for ( int x = 0; x<26; x++) {
    pb_mapping[x] = x;
    cout << setw(2) << pb_mapping[x] << " ";
  }
  cout << endl;*/

  load_pb_setting(argv[1], pb_mapping);
  /*
  // printing updated plugboard settings
  for ( int x = 0; x<26; x++) cout << setw(2) << pb_mapping[x] << " ";
  cout << endl;
  */
  // =========== SETTING ROTORS ===========
  int number_of_rotors = argc-4;
  int pos_array[number_of_rotors];    // argc-4 = number of rotors
  load_rotor_pos(argv[argc-1], pos_array, number_of_rotors);
  
  // Source: https://www.geeksforgeeks.org/how-to-initialize-array-of-objects-with-parameterized-constructors-in-c/
  //Rotor* enigma_rotors = (Rotor*)malloc(sizeof(Rotor)*number_of_rotors);
  Rotor enigma_rotors[number_of_rotors];
  initialise_enigma_rotors(pos_array, enigma_rotors, number_of_rotors, argv);
  
  // =========== SETTING REFLECTORS ===========
  int rf_mapping[26];
  /*
  // printing original plugboard settings
  cout << endl <<  "The reflector settings are:" << endl;
  for ( int x = 0; x<26; x++) {
    rf_mapping[x] = x;
    cout << setw(2) << rf_mapping[x] << " ";
  }
  cout << endl;*/
  
  load_rf_setting(argv[2], rf_mapping);

  /*
  // printing updated reflector settings
  for ( int x = 0; x<26; x++) cout << setw(2) << rf_mapping[x] << " ";
  cout << endl;
  */
  // =========== READING INPUT CHARACTERS ===========
  int input_length;
  int enigma_input[256];
  read_input(enigma_input, input_length);
  
  // =========== OUTPUT DECODED CHARACTERS ===========
  int enigma_output[input_length];
  enigma_machine(enigma_input, input_length, pb_mapping, rf_mapping, enigma_rotors, number_of_rotors, enigma_output);
  
  return 0;
}
