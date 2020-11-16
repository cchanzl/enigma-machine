#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "rotor.h"
#include "reflector.h"  // necessary because enigma.h references Reflector class
#include "plugboard.h"  // necessary because enigma.h references Plugboard class
#include "enigma.h"     // necessary because search_array() is used below
#include "errors.h"


using namespace std;


// ========== functions that are not member of any user defined class ==========


// this function loads the starting rotor position setting from parameters provided
void load_rotor_pos(const char* filename, int pos_array[], int number_of_rotors){

  // loading rotor config into rotor_mapping
  ifstream in(filename);
  if (!in) {
    cerr << "Error: Unable to open or read configuration files";
    exit(ERROR_OPENING_CONFIGURATION_FILE);
  }
  
  int count = 0;      // counts how many rotor positions are defined
  string input;

  while(in >> input){

    // check for non-numeric characters
    for(char& c : input) {
      if ( c < 48 || c > 57){
	cerr << "Non-numeric character in rotor positions file rotor.pos" << endl;
	exit(NON_NUMERIC_CHARACTER);
      }; 
    }

    // convert string to integer if numeric
    int setting = stoi(input, nullptr, 10);
    
    // check if a is a valid index
    if ( setting < 0 || setting > 25 ) {
      cerr << "Error: Position config contains a number not between 0 and 25" << endl;
      exit(INVALID_INDEX);
    }

    pos_array[count] = setting;
    
    count++;
  }

  // it is not ok if number of positions is lesser than number of rotors
  // does not matter if number of posistions is larger than number of rotors since you can have 0 rotors with a non-zero config file
  if ( count < number_of_rotors ){   // comparison is ok as the last loop +1 before exiting 
    cerr << "No starting position for rotor " << count  << " in rotor position file: rotor.pos" << endl;
    exit(NO_ROTOR_STARTING_POSITION);
  }


  // closes ifstream
  in.close();

}

// this function initialises enigma_rotors based on input parameters
void initialise_enigma_rotors(int pos_array[], Rotor enigma_rotors[], int number_of_rotors, char* argv[]){

  // Initialise each Rotor from right (higher number) to left (lower number)
  for ( int i = number_of_rotors - 1; i >= 0; i--){
    enigma_rotors[i] = Rotor(argv[3+i], pos_array, i);
    //enigma_rotors[i].print_rotor_setting();
  }
}


// ========== rotor class member functions ==========

// this function rotates the rotor based on the notch
void Rotor::rotor_rotation(Rotor enigma_rotors[], int number_of_rotors, int rotor_num){

  // if it is rightmost rotor, rotate immediately
  if ( rotor_num == number_of_rotors - 1) rotate_rotor();
  else {
    for ( int n = 0; n < 26; n++){
      if ( enigma_rotors[rotor_num+1].notch[n] == enigma_rotors[rotor_num+1].input_mapping[0]) rotate_rotor();
    }
  }
}

// this function rotates rotor by one notch
void Rotor::rotate_rotor(){

  int start_12;
  
  // first, find new position
  if ( input_mapping[0]+1 == 26 ) start_12 = 0;
  else start_12 = input_mapping[0]+1;
  
  //second, +1 to get each subsequent position
  for ( int i = 0; i < 26; i++){
    input_mapping[i] = start_12;
    if (start_12 == 25) start_12 = -1;
    start_12 += 1;
  }
}

// this function prints rotor settings for debugging purposes
void Rotor::print_rotor_setting(){
  cout << endl;
  
  cout << "Starting position for rotor " << rotor_pos << " is: " << start_pos << endl;
  
  cout << "reference num: ";
  for ( int i = 0; i<26; i++) cout << setw(2) << i << " ";
  cout << endl;

  cout << "Input mapping: ";
  for ( int x = 0; x<26; x++) cout << setw(2) << input_mapping[x] << " ";
  cout << endl;

  cout << "Rotor mapping: ";
  for ( int x = 0; x<26; x++) cout << setw(2) << rotor_mapping[x] << " ";
  cout << endl;

  cout << "Notch mapping: ";
  for ( int x = 0; x<26; x++) cout << setw(2) << notch[x] << " ";
  cout << endl;
}

// this member function loads rotor settings from paramters provided, based on the rotors position in the machine
void Rotor::load_rotor_setting(const char* filename, const int pos_array[], const int rotor_pos){

  // Assign starting position of rotor
  this->start_pos = pos_array[rotor_pos];

  // Assign starting input rotor position
  int start_12 = start_pos;
  for ( int i = 0; i < 26; i++){
    input_mapping[i] = start_12;
    if (start_12 == 25) start_12 = -1;
    start_12 += 1;
  }
 
  // loading internal rotor config into rotor_mapping
  ifstream in(filename);
  if (!in) {
    cerr << "Error: Unable to open or read configuration files" << endl;
    exit(ERROR_OPENING_CONFIGURATION_FILE);
  }
  
  int count = 0;      // counts how many rotor config are defined
  string input;

  // to initilise notch array
  for ( int i = 0; i < 26; i ++){
    notch[i] = 99;
  }

  while(in >> input){

    // check for non-numeric characters
    for(char& c : input) {
      if ( c < 48 || c > 57){
	cerr << "Non-numeric character for mapping in rotor file rotor.rot" << endl;
	exit(NON_NUMERIC_CHARACTER);
      }; 
    }

    // convert string to integer if numeric
    int setting = stoi(input, nullptr, 10);
    
    // check if a is a valid index
    if ( setting < 0 || setting > 25 ) {
      cerr << "Error: Rotor config contains a number not between 0 and 25" << endl;
      exit(INVALID_INDEX);
    }
    
    // for all numbers after the first 26, add it to notch setting
    if ( count > 25 ) {
      notch[count-26] = setting; 
    }
    else rotor_mapping[count] = setting;
    
    // check if number for rotor mapping is repeated in first 26 positions
    if ( count < 26 ){
      for ( int i = 0; i < count; i++){
	if ( rotor_mapping[count] == rotor_mapping[i] ) {
	  cerr << "Invalid mapping of input " << count << " to output " << rotor_mapping[count] << " (output " << rotor_mapping[count] << " is already mapped to from input " << i  << ") in rotor.rot" << endl; 
	  exit(INVALID_ROTOR_MAPPING);
	}
      }           
    }

    // check if number for notch is repeated in next 26 positions
    else{
      for ( int i = 0; i < count-26; i++){
	if ( notch[count-26] == notch[i] ) {
	  cerr << "notch is repeated" << endl; 
	  exit(INVALID_ROTOR_MAPPING);
	}
      }
    }
    
    count++;

  }
  
  // rotor setting must have at least 26 numbers
  if ( count < 26 ) {  
    cerr << "Not all inputs mapped in rotor file: rotor.rot" << endl;
    exit(INVALID_ROTOR_MAPPING);
  }

  // rotor setting must have lesser than 52 numbers (first 26 for rotor mapping and next 26 for notches)
  if ( count > 52 ) {  
    cerr << "Too many inputs in rotor file: rotor.rot" << endl;
    exit(INVALID_ROTOR_MAPPING);
  }

  
  // closes ifstream
  in.close();

}

// this member function scrambles input into a rotor entering from right to left
int Rotor::right_to_left(int right_input){

  int left_output;

  left_output = input_mapping[right_input];
  left_output = rotor_mapping[left_output];
  left_output = search_array(input_mapping, left_output);
 
  return left_output;
}

// this member function scrambles input into a rotor entering from left to right
int Rotor::left_to_right(int left_input){

  int right_output;

  right_output = input_mapping[left_input];
  right_output = search_array(rotor_mapping, right_output);
  right_output = search_array(input_mapping, right_output);
  
  return right_output;
}

