#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "reflector.h"
#include "errors.h"

using namespace std;


// ========== functions that are not member of any user defined class ==========

// this function loads the reflector settings from the parameters provided
void load_rf_setting(const char* filename, int rf_mapping[26]){
 int rf_setting[26];
  
  // loading reflector settings into rf_setting
  ifstream in(filename);
  if (!in) {
    cerr << "Error: Unable to open or read configuration files" << endl;
    exit(ERROR_OPENING_CONFIGURATION_FILE);
  }

  int count = 0;      // counts how many rf settings are defined
  string input;

  // cycles through each char in input and assign to reflector array
  while(in >> input){

    // check if there are more than 26 parameters
    if ( count == 26 ){
      cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << endl;
      exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS); 
    }

    
    // check for non-numeric characters
    for(char& c : input) {
      if ( c < 48 || c > 57){
	cerr << "Non-numeric character in reflector file reflector.rf" << endl;
	exit(NON_NUMERIC_CHARACTER);
      }; 
    }

    // convert string to integer if numeric
    int setting = stoi(input, nullptr, 10);
    
    // check if a is a valid index
    if ( setting < 0 || setting > 25 ) {
      cerr << "Error: Reflector setting contains a number not between 0 and 25" << endl;
      exit(INVALID_INDEX);
    }
    
    // add to reflector setting
    rf_setting[count] = setting;
    
    // check if plugboard connects with itself
    if ( count % 2 != 0 && rf_setting[count - 1] == rf_setting[count] ){
      cerr << "Error: Reflector attempts to connect a contact with itself" << endl;
      exit(INVALID_REFLECTOR_MAPPING);
    }

    // check if number is used before
    for ( int i = 0; i < count; i++){
      if ( rf_setting[count] == rf_setting[i] ) {
	cerr << "Error: Reflector attempts to connect with more than one contact" << endl;
	exit(INVALID_REFLECTOR_MAPPING);
      }
    }
    
    count++;
    
  }


  // check if there is an even number of settings
  if (count % 2 != 0) {
    cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << endl;
    exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS); 
  }

  // check if there are lesser than 26 parameters
  if ( count < 26 ) {    // 26 because the last loop will increment count one more time
    cerr << "Insufficient number of mappings in reflector file: reflector.rf" << endl;
    exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
  }    

  // map the entire reflector using the settings 
  for ( int x = 0; x<26; x++) rf_mapping[x] = x;
  
  for ( int i = 0; i < 26; i+=2 ) {
    rf_mapping[rf_setting[i]] = rf_setting[i+1];
    rf_mapping[rf_setting[i+1]] = rf_setting[i];
  }

  // closes ifstream
  in.close();

  
}
