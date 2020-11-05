#include <iostream>
#include <fstream>
#include <cassert>
#include "enigma.h"

using namespace std;

void load_pb_setting(const char* filename, int pb_setting[26]){

  // loading plugboard settings into pb_setting
  ifstream in(filename, std::ios_base::in);
  if (!in) {
    cout << "Failed!" << '\n';
  }
  assert(in);
    
  int i = 0;
  int a;
  while(in>>a){
    pb_setting[i] = a;
    i++;
    }

  for (int x = i; x < 26; x++){    // setting unused settings as 99
    pb_setting[x] = 99;
  }
  
}

void map_pb(int* pb_mapping, int* pb_setting){
  // map the entire plugboard using the settings 


}


char plugboard(int input, int to_rotor, int* pb_mapping){
  // match the input to the plug board and output to rotor


  return to_rotor;
}
