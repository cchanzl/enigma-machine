#include <iostream>
#include <iomanip>
#include "enigma.h"

using namespace std;

int main (int argc, char** argv){

  // =========== SETTING PLUGBOARD ===========
  int pb_mapping[26];

  // printing original plugboard settings
  cout << "The plugboard settings are: "<< endl;
  for ( int x = 0; x<26; x++) {
    pb_mapping[x] = x;
    cout << setw(2) << pb_mapping[x] << " ";
  }
  cout << endl;

  load_pb_setting(argv[1], pb_mapping);

  // printing updated plugboard settings
  for ( int x = 0; x<26; x++) cout << setw(2) << pb_mapping[x] << " ";
  cout << endl;

  // =========== SETTING ROTORS ===========
  int number_of_rotors = argc-4;
  int pos_array[number_of_rotors];    // argc-4 = number of rotors
  load_rotor_pos(argv[argc-1], pos_array, number_of_rotors);

  // Source: https://www.geeksforgeeks.org/how-to-initialize-array-of-objects-with-parameterized-constructors-in-c/
  Rotor* enigma_rotors = (Rotor*)malloc(sizeof(Rotor)*number_of_rotors);
  initialise_enigma_rotors(pos_array, enigma_rotors, number_of_rotors, argv);
  

  // =========== SETTING REFLECTORS ===========
  int rf_mapping[26];
  // printing original plugboard settings
  cout << endl <<  "The reflector settings are:" << endl;
  for ( int x = 0; x<26; x++) {
    rf_mapping[x] = x;
    cout << setw(2) << rf_mapping[x] << " ";
  }
  cout << endl;

  load_rf_setting(argv[2], rf_mapping);

  // printing updated reflector settings
  for ( int x = 0; x<26; x++) cout << setw(2) << rf_mapping[x] << " ";
  cout << endl;

  // =========== READING INPUT CHARACTERS ===========
  int enigma_input = new int[];
  read_input(enigma_input);

  

  // =========== OUTPUT DECODED CHARACTERS ===========
  
  return 0;
}
