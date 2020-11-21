#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "rotor.h"
#include "enigma.h"     // necessary because search_array() is used below
#include "errors.h"


// ========== functions that are not member of any user defined class ==========


// this function loads the starting rotor position setting from parameters provided
void load_rotor_pos(const char* filename, int pos_array[], const int number_of_rotors){

  // loading rotor config into rotor_mapping
  std::ifstream in(filename);
  if (!in) {
    std::cerr << "Error: Unable to open or read rotor pos config file" << std::endl;;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }
  
  int count = 0;      // counts how many rotor positions are defined
  std::string input;

  while(in >> input){

    // Exits while loop once the required number of rotor positions is read
    if ( count == number_of_rotors) break;
    
    // check for non-numeric characters
    for(char& c : input) {
      if ( !isdigit(c) ){
	std::cerr << "Non-numeric character in rotor positions file rotor.pos" << std::endl;
	throw NON_NUMERIC_CHARACTER;
      }; 
    }

    // convert string to integer if numeric
    int setting = stoi(input, nullptr);
    
    // check if it is a valid index
    if ( setting < 0 || setting > NUM_OF_ALPHABETS-1 ) {
      std::cerr << "Error: Position config contains a number not between 0 and 25" << std::endl;
      throw INVALID_INDEX;
    }

    pos_array[count] = setting;
    
    count++;
  }

  // it is not ok if number of positions is lesser than number of rotors
  // does not matter if number of positions is larger than number of rotors since you can have 0 rotors with a non-zero config file
  if ( count < number_of_rotors ){   
    std::cerr << "No starting position for rotor " << count  << " in rotor position file: rotor.pos" << std::endl;
    throw NO_ROTOR_STARTING_POSITION;
  }


  // closes ifstream
  in.close();
  in.good();
}

// this function initialises enigma_rotors based on input parameters
void initialise_enigma_rotors(Rotor* set_of_rotors, const int number_of_rotors, char* argv[]){
  
  // Initialise array containing each rotor's starting position
  int pos_array[number_of_rotors];
  load_rotor_pos(argv[number_of_rotors + FIXED_ARGV-1], pos_array, number_of_rotors);
  
  // Initialise each Rotor from right (higher number) to left (lower number)
  for ( int i = number_of_rotors - 1; i >= 0; i--){
    *(set_of_rotors+i) = Rotor(argv[FIXED_ARGV-1 + i ], pos_array, i);
  }
}


// ========== rotor class member functions ==========

// this function rotates the rotor based on the notch
void Rotor::rotor_rotation(Rotor* set_of_rotors, const int number_of_rotors, const int rotor_num){

  // if it is rightmost rotor, rotate immediately
  if ( rotor_num == number_of_rotors - 1) {
    rotate_rotor();
  }
    else {
    for ( int n = 0; n < NUM_OF_ALPHABETS; n++){
      Rotor right_rotor = *(set_of_rotors + rotor_num + 1);
      if ( right_rotor.notch[n] == right_rotor.input_mapping[0] ) rotate_rotor();     
    }
  }
}

void Rotor::update_input_mapping(int start_pos){
  int start_12 = start_pos;
  for ( int i = 0; i <  NUM_OF_ALPHABETS; i++){
    input_mapping[i] = start_12;
    if (start_12 ==  NUM_OF_ALPHABETS-1) start_12 = -1;
    start_12 += 1;
  }
}

// this function rotates rotor by one notch
void Rotor::rotate_rotor(){

  int start_12; // declare a variable to represent the 12 o'clock position
  
  // first, find new 12 o'clock position
  if ( input_mapping[0]+1 == NUM_OF_ALPHABETS ) start_12 = 0;
  else start_12 = input_mapping[0]+1;
  
  //second, +1 from 12 o'clock position to get each subsequent position
  update_input_mapping(start_12);
 
}

// this member function loads rotor settings from paramters provided, based on the rotors position in the machine
void Rotor::load_rotor_setting(const char* filename, const int pos_array[], const int rotor_pos){

  // Assign starting position of rotor
  this->start_pos = pos_array[rotor_pos];

  // Assign starting input rotor position
  update_input_mapping(start_pos);
 
  // loading internal rotor config into rotor_mapping
  std::ifstream in(filename);
  if (!in) {
    std::cerr << "Error: Unable to open or read rotor " << rotor_pos << " config file" << std::endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }
  
  int count = 0;      // counts how many rotor config are defined
  std::string input;

  // to initilise notch array
  for ( int i = 0; i < NUM_OF_ALPHABETS; i ++){
    int unutilised_setting = 99;
    notch[i] = unutilised_setting;
  }

  while(in >> input){

    // check for non-numeric characters
    for(char& c : input) {
      if ( !isdigit(c) ){
	std::cerr << "Non-numeric character for mapping in rotor file rotor.rot" << std::endl;
	throw NON_NUMERIC_CHARACTER;
      }; 
    }

    // convert string to integer if numeric
    int setting = stoi(input, nullptr);
    
    // check if it is a valid index
    if ( setting < 0 || setting > NUM_OF_ALPHABETS-1 ) {
      std::cerr << "Error: Rotor config contains a number not between 0 and 25" << std::endl;
      throw INVALID_INDEX;
    }
    
    // for all numbers after the first 26, add it to notch setting
    if ( count > NUM_OF_ALPHABETS-1 ) {
      notch[count-NUM_OF_ALPHABETS] = setting; 
    }
    else rotor_mapping[count] = setting;
    
    // check if number for rotor mapping is repeated in when going thru first 26 inputs
    if ( count < NUM_OF_ALPHABETS ){
      for ( int i = 0; i < count; i++){
	if ( rotor_mapping[count] == rotor_mapping[i] ) {
	  std::cerr << "Invalid mapping of input " << count << " to output " << rotor_mapping[count] << " (output " << rotor_mapping[count] << " is already mapped to from input " << i  << ") in rotor.rot" << std::endl; 
	  throw INVALID_ROTOR_MAPPING;
	}
      }           
    }

    // check if number for notch is repeated in next 26 positions
    else{
      for ( int i = 0; i < count - NUM_OF_ALPHABETS; i++){
	if ( notch[count - NUM_OF_ALPHABETS] == notch[i] ) {
	  std::cerr << "notch is repeated" << std::endl; 
	  throw INVALID_ROTOR_MAPPING;
	}
      }
    }
    
    count++;

  }
  
  // rotor setting must have at least 26 numbers
  if ( count < NUM_OF_ALPHABETS ) {  
    std::cerr << "Not all inputs mapped in rotor file: rotor.rot" << std::endl;
    throw INVALID_ROTOR_MAPPING;
  }

  // rotor setting must have lesser than 52 numbers (first 26 for rotor mapping and next 26 for notches)
  if ( count > 2*NUM_OF_ALPHABETS ) {  
    std::cerr << "Too many inputs in rotor file: rotor.rot" << std::endl;
    throw INVALID_ROTOR_MAPPING;
  }

  
  // closes ifstream
  in.close();
  in.good();
}

// this member function scrambles input into a rotor entering from right to left
int Rotor::right_to_left(const int right_input){

  int left_output;

  left_output = input_mapping[right_input];
  left_output = rotor_mapping[left_output];
  left_output = search_array(input_mapping, left_output);
 
  return left_output;
}

// this member function scrambles input into a rotor entering from left to right
int Rotor::left_to_right(const int left_input){

  int right_output;

  right_output = input_mapping[left_input];
  right_output = search_array(rotor_mapping, right_output);
  right_output = search_array(input_mapping, right_output);
  
  return right_output;
}
