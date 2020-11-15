#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "plugboard.h"
#include "errors.h"


using namespace std;

// this function loads the plugboard settings from parameters provided
void load_pb_setting(const char* filename, int pb_mapping[26]){

  int pb_setting[26];
  
  // loading plugboard settings into pb_setting
  ifstream in(filename);
  if (!in) {
    cerr << "Error: Unable to open or read configuration files";
    exit(ERROR_OPENING_CONFIGURATION_FILE);
  }

  int count = 0;      // counts how many pb settings are defined
  string input;

  while(in >> input){
      
    // check for non-numeric characters
    for(char& c : input) {
      if ( c < 48 || c > 57){
	cerr << "Non-numeric character in plugboard file plugboard.pb";
	exit(NON_NUMERIC_CHARACTER);
      }; 
    }

    // convert string to integer if numeric
    int setting = stoi(input, nullptr, 10);
    
    // check if a is a valid index
    if ( setting < 0 || setting > 25 ) {
      cerr << "Error: Plugboard setting contains a number not between 0 and 25";
      exit(INVALID_INDEX);
    }
    
    // add to plugboard setting
    pb_setting[count] = setting;
    
    // check if plugboard connects with itself
    if ( count % 2 != 0 && pb_setting[count - 1] == pb_setting[count] ){
      cerr << "Error: Plugboard attempts to connect a contact with itself";
      exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
    }

    // check if number is used before
    for ( int i = 0; i < count; i++){
      if ( pb_setting[count] == pb_setting[i] ) {
	cerr << "Error: Plugboard attempts to connect with more than one contact";
	exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
      }
    }
    
    count++;

    // while loop will exit if count == 27
    if ( count == 27 ) {
      cerr << "Incorrect number of parameters in plugboard file plugboard.pb";
      exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    }
    
  }  

  // check even number of settings
  if (count % 2 != 0) {
    cerr << "Incorrect number of parameters in plugboard file plugboard.pb";
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
  
}
