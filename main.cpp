#include <iostream>
#include <iomanip>
#include "enigma.h"

using namespace std;

int main (int argc, char** argv){

  /* for testing inputs
  for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
	}
  */

  // =========== SETTING PLUGBOARD ===========
  int pb_mapping[26];
  int pb_setting[26];
  
  for ( int x = 0; x<26; x++){
    pb_mapping[x] = x;
    cout << setw(2) << pb_mapping[x] << " ";
  }
  cout << endl;

  load_pb_setting(argv[1], pb_setting, pb_mapping);
  
  for ( int x = 0; x<26; x++){
    cout << setw(2) << pb_setting[x] << " ";
  }
  cout << endl;

  for ( int x = 0; x<26; x++){
    cout << setw(2) << pb_mapping[x] << " ";
  }
  cout << endl;

  
  


  

  // =========== SETTING ROTORS ===========




  // =========== SETTING REFLECTORS ===========




  // =========== READING INPUT CHARACTERS ===========




  // =========== OUTPUT DECODED CHARACTERS ===========
  
  return 1;
}
