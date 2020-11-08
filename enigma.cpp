#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <string>
#include "enigma.h"
#include "errors.h"


using namespace std;

void load_pb_setting(const char* filename, int pb_mapping[26]){

  int pb_setting[26];
  
  // loading plugboard settings into pb_setting
  ifstream in(filename);
  if (!in) {
    cout << "Failed!" << '\n';
  }
  assert(in);

  int count = 0;      // counts how many pb settings are defined
  string input;

  while(in >> input){

    // check for non-numeric characters
    for(char& c : input) {
      if ( c < 48 || c > 57){
	cout << "Error: Plugboard setting contains non-numeric characters." << endl;
	exit(NON_NUMERIC_CHARACTER);
      }; 
    }

    // convert string to integer if numeric
    int setting = stoi(input, nullptr, 10);
    
    // check if a is a valid index
    if ( setting < 0 || setting > 25 ) {
      cout << "Error: Plugboard setting contains a number not between 0 and 25." << endl;
      exit(INVALID_INDEX);
    }
    
    // add to plugboard setting
    pb_setting[count] = setting;
    
    // check if plugboard connects with itself
    if ( count % 2 != 0 && pb_setting[count - 1] == pb_setting[count] ){
      cout << "Error: Plugboard attempts to connect a contact with itself." << endl;
      exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
    }

    // check if number is used before
    for ( int i = 0; i < count; i++){
      if ( pb_setting[count] == pb_setting[i] ) {
	cout << "Error: Plugboard attempts to connect with more than one contact." << endl;
	exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
      }
    }
    
    count++;

    if ( count > 26 ) {    // 26 because the last loop will increment count one more time
      cout << "Error: Plugboard Setting contains more than 26 numbers. " << endl;
      exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    }
    
  }  

  // check even number of settings
  if (count % 2 != 0) {
    cout << "Error: Plugboard setting contains an odd number of numbers." << endl;
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


void load_rotor_pos(const char* filename, int pos_array[], int number_of_rotors){

  // loading rotor config into rotor_mapping
  ifstream in(filename);
  if (!in) {
    cout << "Failed!" << '\n';
  }
  assert(in);
  
  int count = 0;      // counts how many rotor config are defined
  string input;

  while(in >> input){

    // check for non-numeric characters
    for(char& c : input) {
      if ( c < 48 || c > 57){
	cout << "Error: Position config contains non-numeric characters." << endl;
	exit(NON_NUMERIC_CHARACTER);
      }; 
    }

    // convert string to integer if numeric
    int setting = stoi(input, nullptr, 10);
    
    // check if a is a valid index
    if ( setting < 0 || setting > 25 ) {
      cout << "Error: Position config contains a number not between 0 and 25." << endl;
      exit(INVALID_INDEX);
    }

    pos_array[count] = setting;
    
    count++;
  }

  if ( count != number_of_rotors ){   // +1 as the last loop adds 1 before exiting 
    cout << "Error: Position config does not contain enough starting positions for the number of rotors specified." << endl;
    exit(NO_ROTOR_STARTING_POSITION);
  }  

}


// ========== rotor functions ==========

// to rotate rotor by one notch
void Rotor::rotate_rotor(){
  // first, find current position
  int start_12 = input_mapping[0]+1;
  int end_12 = output_mapping[0]+1;
  
  for ( int i = 0; i < 26; i++){
    input_mapping[i] = start_12;
    if (start_12 == 25) start_12 = -1;
    start_12 += 1;

    output_mapping[i] = end_12;
    if (end_12 == 25) end_12 = -1;
    end_12 += 1;

  }
}


// print function for debugging
void Rotor::print_rotor_setting(){
  cout << endl;
  cout << "Starting position for rotor " << rotor_pos << " is: " << start_pos << endl;
  cout << "Input mapping: ";
  for ( int x = 0; x<26; x++) cout << setw(2) << input_mapping[x] << " ";
  cout << endl;

  cout << "Rotor mapping: ";
  for ( int x = 0; x<26; x++) cout << setw(2) << rotor_mapping[x] << " ";
  cout << endl;

  cout << "Outpu mapping: ";
  for ( int x = 0; x<26; x++) cout << setw(2) << output_mapping[x] << " ";
  cout << endl;

  cout << "Notch for rotor number " << rotor_pos << " is at " << notch << endl;
}

// load rotor settings
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
    cout << "Failed!" << '\n';
  }
  assert(in);
  
  int count = 0;      // counts how many rotor config are defined
  string input;

  while(in >> input){

    // check for non-numeric characters
    for(char& c : input) {
      if ( c < 48 || c > 57){
	cout << "Error: Rotor config contains non-numeric characters." << endl;
	exit(NON_NUMERIC_CHARACTER);
      }; 
    }

    // convert string to integer if numeric
    int setting = stoi(input, nullptr, 10);
    
    // check if a is a valid index
    if ( setting < 0 || setting > 25 ) {
      cout << "Error: Rotor config contains a number not between 0 and 25." << endl;
      exit(INVALID_INDEX);
    }
    
    // add to rotor setting
    if ( count == 26 ) notch = setting; 
    else rotor_mapping[count] = setting;
    
    // check if number is used before
    for ( int i = 0; i < count; i++){
      if ( count == 26 ) break;    // to avoid checking notch position
      if ( rotor_mapping[count] == rotor_mapping[i] ) {
	cout << "Error: Rotor config attempts to map more than one input to the same output." << endl;
	exit(INVALID_ROTOR_MAPPING);
      }
    }
    
    count++;

    if ( count > 27 ) {   // 27 because the last loop will increment count one more time
      cout << "Error: Rotor config contains more than 27 numbers. " << endl;
      exit(INVALID_ROTOR_MAPPING);
    }
    
  }

  if ( count != 27 ) {
   cout << "Error: Rotor config does not provide a mapping for some input. " << endl;
   exit(INVALID_ROTOR_MAPPING);
  }

  // Assign starting output rotor position
  int end_12 = rotor_mapping[start_pos];
  for ( int i = 0; i < 26; i++){
    output_mapping[i] = end_12;
    if (end_12 == 25) end_12 = -1;
    end_12 += 1;
  }
  
}

