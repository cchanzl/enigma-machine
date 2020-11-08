#include <iostream>
#include <iomanip>
#include "enigma.h"

using namespace std;

int main (int argc, char** argv){

  // =========== SETTING PLUGBOARD ===========
  int pb_mapping[26];

  // printing original plugboard settings
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
  
  Rotor right(argv[3], pos_array, 2);
  right.print_rotor_setting();


  // =========== SETTING REFLECTORS ===========




  // =========== READING INPUT CHARACTERS ===========




  // =========== OUTPUT DECODED CHARACTERS ===========
  
  return 1;
}
