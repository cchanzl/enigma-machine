#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "plugboard.h"
#include "enigma.h"
#include "errors.h"

// this function scrambles input through the plugboard from right to left
int Plugboard::right_to_left(int input) const{
  return pb_mapping[input];
}


// this function scrambles input through the plugboard from left to right
int Plugboard::left_to_right(int input) const{
  return search_array(pb_mapping, input);
}


// this function loads the plugboard settings from parameters provided
void Plugboard::load_pb_setting(const char* filename, int pb_mapping[26]){

  int pb_setting[26];
  
  // loading plugboard settings into pb_setting
  std::ifstream in(filename);
  if (!in) {
    std::cerr << "Error: Unable to open or read configuration files" << std::endl;
    exit(ERROR_OPENING_CONFIGURATION_FILE);
  }

  int count = 0;      // counts how many pb settings are defined
  std::string input;

  
  // cycles through each char in input and assign to plugboard array
  while(in >> input){

    // check if there are more than 26 parameters
    if ( count == 26 ) {
      std::cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << std::endl;
      exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    }

    
    // check for non-numeric characters
    for(char& c : input) {
      if ( !isdigit(c) ){
	std::cerr << "Non-numeric character in plugboard file plugboard.pb" << std::endl;
	exit(NON_NUMERIC_CHARACTER);
      }; 
    }

    // convert string to integer if numeric
    int setting = stoi(input, nullptr, 10);
    
    // check if a is a valid index
    if ( setting < 0 || setting > 25 ) {
      std::cerr << "Error: Plugboard setting contains a number not between 0 and 25" << std::endl;
      exit(INVALID_INDEX);
    }
    
    // add to plugboard setting
    pb_setting[count] = setting;
    
    // check if plugboard connects with itself
    if ( count % 2 != 0 && pb_setting[count - 1] == pb_setting[count] ){
      std::cerr << "Error: Plugboard attempts to connect a contact with itself" << std::endl;
      exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
    }

    // check if number is used before
    for ( int i = 0; i < count; i++){
      if ( pb_setting[count] == pb_setting[i] ) {
	std::cerr << "Invalid mapping of " << pb_setting[count] << " (it is already mapped) in plugboard.pb" << std::endl;
	exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
      }
    }
    
    count++;
    
  }  

  // check if there is an even number of settings
  if (count % 2 != 0) {
    std::cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << std::endl;
    exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS); 
  }
  
  int blank_setting = 99;          // set unused settings as 99
  for (int x = count; x < 26; x++){    
    pb_setting[x] = blank_setting;
  }

  // map the entire plugboard using the settings 
  for ( int x = 0; x<26; x++) pb_mapping[x] = x;
  
  for ( int i = 0; i < 26; i+=2 ) {
    if(pb_setting[i] == blank_setting) break; 
    pb_mapping[pb_setting[i]] = pb_setting[i+1];
    pb_mapping[pb_setting[i+1]] = pb_setting[i];
  }

  // closes ifstream
  in.close();

  
}
