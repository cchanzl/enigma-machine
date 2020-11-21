#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "reflector.h"
#include "errors.h"


// this function scrambles input through the reflector
int Reflector::reflector_output(int input) const {
  int output;
  return output = rf_mapping[input];
}


// this function loads the reflector settings from the parameters provided
void Reflector::load_rf_setting(const char* filename, int rf_mapping[NUM_OF_ALPHABETS]){
 int rf_setting[NUM_OF_ALPHABETS];
  
  // loading reflector settings into rf_setting
 std::ifstream in(filename);
  if (!in) {
    std::cerr << "Error: Unable to open or read rf config file" << std::endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

  int count = 0;      // counts how many rf settings are defined
  std::string input;

  // cycles through each char in input and assign to reflector array
  while(in >> input){

    // check if while loop enters 27th loop, if yes, means there are 27 param
    if ( count == NUM_OF_ALPHABETS ){
      std::cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << std::endl;
      throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS; 
    }

    
    // check for non-numeric characters
    for(char& c : input) {
      if ( !isdigit(c) ){
	std::cerr << "Non-numeric character in reflector file reflector.rf" << std::endl;
	throw NON_NUMERIC_CHARACTER;
      }; 
    }

    // convert string to integer if numeric
    int setting = stoi(input, nullptr);
    
    // check if it is a valid index
    if ( setting < 0 || setting > NUM_OF_ALPHABETS ) {
      std::cerr << "Error: Reflector setting contains a number not between 0 and 25" << std::endl;
      throw INVALID_INDEX;
    }
    
    // add to reflector setting
    rf_setting[count] = setting;
    
    // check if plugboard connects with itself
    if ( count % 2 != 0 && rf_setting[count - 1] == rf_setting[count] ){
      std::cerr << "Error: Reflector attempts to connect a contact with itself" << std::endl;
      throw INVALID_REFLECTOR_MAPPING;
    }

    // check if number is used before
    for ( int i = 0; i < count; i++){
      if ( rf_setting[count] == rf_setting[i] ) {
	std::cerr << "Error: Reflector attempts to connect with more than one contact" << std::endl;
	throw INVALID_REFLECTOR_MAPPING;
      }
    }
    
    count++;
    
  }

  // check if there is an even number of settings
  if (count % 2 != 0) {
    std::cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << std::endl;
    throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS; 
  }

  // check if there are lesser than 26 parameters
  if ( count < NUM_OF_ALPHABETS ) {    // 26 because the last loop will increment count one more time
    std::cerr << "Insufficient number of mappings in reflector file: reflector.rf" << std::endl;
    throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }    

  // map the entire reflector using the settings 
  for ( int x = 0; x < NUM_OF_ALPHABETS; x++) rf_mapping[x] = x;
  
  for ( int i = 0; i < NUM_OF_ALPHABETS; i+=2 ) {
    rf_mapping[rf_setting[i]] = rf_setting[i+1];
    rf_mapping[rf_setting[i+1]] = rf_setting[i];
  }

  // closes ifstream
  in.close();  
}
