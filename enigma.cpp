#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <string>
#include "enigma.h"
#include "errors.h"


using namespace std;

void load_rf_setting(const char* filename, int rf_mapping[26]){
 int rf_setting[26];
  
  // loading reflector settings into rf_setting
  ifstream in(filename);
  if (!in) {
    cout << "Error: Unable to open or read configuration files." << endl;
    exit(ERROR_OPENING_CONFIGURATION_FILE);
  }

  int count = 0;      // counts how many rf settings are defined
  string input;

  while(in >> input){

    // check for non-numeric characters
    for(char& c : input) {
      if ( c < 48 || c > 57){
	cout << "Error: Reflector setting contains non-numeric characters." << endl;
	exit(NON_NUMERIC_CHARACTER);
      }; 
    }

    // convert string to integer if numeric
    int setting = stoi(input, nullptr, 10);
    
    // check if a is a valid index
    if ( setting < 0 || setting > 25 ) {
      cout << "Error: Reflector setting contains a number not between 0 and 25." << endl;
      exit(INVALID_INDEX);
    }
    
    // add to reflector setting
    rf_setting[count] = setting;
    
    // check if plugboard connects with itself
    if ( count % 2 != 0 && rf_setting[count - 1] == rf_setting[count] ){
      cout << "Error: Reflector attempts to connect a contact with itself." << endl;
      exit(INVALID_REFLECTOR_MAPPING);
    }

    // check if number is used before
    for ( int i = 0; i < count; i++){
      if ( rf_setting[count] == rf_setting[i] ) {
	cout << "Error: Reflector attempts to connect with more than one contact." << endl;
	exit(INVALID_REFLECTOR_MAPPING);
      }
    }
    
    count++;
  }
  
  if ( count != 26 ) {    // 26 because the last loop will increment count one more time
    cout << "Error: Reflector does not contain 26 numbers. " << endl;
    exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
  }    

  // map the entire reflector using the settings 
  for ( int x = 0; x<26; x++) rf_mapping[x] = x;
  
  for ( int i = 0; i < 26; i+=2 ) {
    rf_mapping[rf_setting[i]] = rf_setting[i+1];
    rf_mapping[rf_setting[i+1]] = rf_setting[i];
  }
  
}

void load_pb_setting(const char* filename, int pb_mapping[26]){

  int pb_setting[26];
  
  // loading plugboard settings into pb_setting
  ifstream in(filename);
  if (!in) {
    cout << "Error: Unable to open or read configuration files." << endl;
    exit(ERROR_OPENING_CONFIGURATION_FILE);
  }

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
    cout << "Error: Unable to open or read configuration files." << endl;
    exit(ERROR_OPENING_CONFIGURATION_FILE);
  }
  
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

  if ( count != number_of_rotors ){   // comparison is ok as the last loop +1 before exiting 
    cout << "Error: Position config does not contain enough starting positions for the number of rotors specified." << endl;
    exit(NO_ROTOR_STARTING_POSITION);
  }  

}

void initialise_enigma_rotors(int pos_array[], Rotor enigma_rotors[], int number_of_rotors, char* argv[]){
  // Initialise each Rotor from left to right
  for ( int i = 0; i < number_of_rotors; i++){
    enigma_rotors[i] = Rotor(argv[3+i], pos_array, i);
    enigma_rotors[i].print_rotor_setting();
    // right.rotate_rotor();
    // right.print_rotor_setting();
  }
}

void read_input(int enigma_input[], int& input_length){
  cout << "Please enter text to be encoded/decoded in UPPER case." << endl;

  int LIMIT_LENGTH = 256;
  int count = 0;
  string input;
  cin >> input;
  
  for(char& c : input){
  
    // to check if input is from A to Z
    if ( c < 65 || c > 90){
      if ( c == 32 ) continue;
      cout << "Error: Input contains invalid characters." << endl;
      exit(INVALID_INPUT_CHARACTER);
    };
    
    // convert string to integer if numeric and add to enigma_input
    if ( c == 32 )enigma_input[count] = 99;
    else enigma_input[count] = static_cast<int>(c) - 65;  

    count++;
    
    if ( count-1 == LIMIT_LENGTH ) cout << "Error: Message is longer than 256 char." << endl;
    
    }

  input_length = count;
    
}


void enigma_machine( int enigma_input[], int input_length, int pb_mapping[], int rf_mapping[26], Rotor enigma_rotors[], int number_of_rotors, int enigma_output[]){

  for ( int i = 0; i < input_length; i++){

    int output = 0;
    int input = enigma_input[i];
    
    //Scramble through Plugboard
    output = pb_mapping[input];

    //Rotate righthand most rotor once
    //enigma_rotors[number_of_rotors - 1].rotate_rotor();
    
    //Enter row of rotors from plugboard. Start from the right.
    for ( int i = number_of_rotors - 1; i >= 0; i--){
      output = enigma_rotors[i].right_to_left(output);
      /*if ( enigma_rotors[i].input_mapping[0] == enigma_rotors[i].notch && i != 0 ) {
	enigma_rotors[i].rotate_rotor();
	}*/
      cout << "The <<<< output for rotor " << i << " is " << output << endl;
    }
    cout << endl;
    //Enter reflector
    output = rf_mapping[output];
    
    //Enter set of rotors from reflector. Start from the left.
    for ( int i = 0; i < number_of_rotors ; i++){
      output = enigma_rotors[i].left_to_right(output);
      cout << "The >>>> output for rotor " << i << " is " << output << endl;
    }
    cout << endl;

    //Scramble through Plugboard
    for ( int i = 0; i < 26; i++){
      if ( pb_mapping[i] == output ) {
	output = i;
	break;
      }
    }

    //Allocate to output array
    enigma_output[i] = output;    
  }
  
  //print output
  for ( int i = 0; i < input_length; i++){
    cout << enigma_output[i] << endl;
    char letter = static_cast<char>(enigma_output[i] + 65); 
    cout << setw(2) << letter << endl;
  }
  
}


// ========== rotor class member functions ==========

// to rotate rotor by one notch
void Rotor::rotate_rotor(){
  // first, find new position
  int start_12 = input_mapping[0]+1;
  int end_12 = output_mapping[0]+1;

  //second, +1 to get each subsequent position
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
  
  cout << "reference num: ";
  for ( int i = 0; i<26; i++) cout << setw(2) << i << " ";
  cout << endl;

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
    cout << "Error: Unable to open or read configuration files." << endl;
    exit(ERROR_OPENING_CONFIGURATION_FILE);
  }
  
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
  for ( int i = 0; i < 26; i++) output_mapping[i] = i;
  
}

int Rotor::right_to_left(int right_input){

  int left_output;

  left_output = input_mapping[right_input];
  left_output = rotor_mapping[left_output];

  for ( int i = 0; i < 26; i++){
    if ( input_mapping[i] == left_output ) {
      left_output = i;
      break;
    }
  }

  return left_output;
}


int Rotor::left_to_right(int left_input){

  int right_output;

  right_output = input_mapping[left_input];

  for ( int i = 0; i < 26; i++){
    if ( rotor_mapping[i] == right_output ) {
      right_output = i;
      break;
    }
  }
  
  for ( int i = 0; i < 26; i++){
    if ( input_mapping[i] == right_output ) {
      right_output = i;
      break;
    }
  }
  
  return right_output;
}
