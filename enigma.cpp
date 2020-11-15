#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "rotor.h"    // necessary as Rotor class is used as an arguement below
#include "enigma.h"
#include "errors.h"


using namespace std;

// ========== internal helper functions ==========

// this function returns the index position of the second argument in the array
void search_array(int rotor_mapping[], int& output){

 for ( int i = 0; i < 26; i++){
   if ( rotor_mapping[i] == output ) {
     output = i;
     break;
   }
 }
 
}


// ========== functions that are not member of any user defined class ==========

// this function checks that the command line arguments are of the right format
void check_command_line(int argc, char* argv[]){

  // check for at least 4 command line arguments
  if ( argc < 4 ) {
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
    exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
  }

  // check first argument
  string arg_1 = "./enigma";
  if ( argv[0] != arg_1) cout << "Incorrect command line arguments" << endl; 
  

}


// this function reads input from from the standard input stream into an array
void read_input(int enigma_input[], int& input_length){
  //cout << "Please enter text to be encoded/decoded in UPPER case." << endl;

  int LIMIT_LENGTH = 256;
  int count = 0;
  string input;
  cin >> input;
  
  for(char& c : input){
  
    // to check if input is from A to Z
    if ( c < 65 || c > 90){
      cerr << c << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
      exit(INVALID_INPUT_CHARACTER);
    };
    
    // convert string to integer if numeric and add to enigma_input
    enigma_input[count] = static_cast<int>(c) - 65;  

    count++;
    
    if ( count-1 == LIMIT_LENGTH ) cout << "Error: Message is longer than 256 char";
    
    }

  input_length = count;
    
}

// this function brings together all the necessary parts of the enigma machine to encode/decode input to output
void enigma_machine( int enigma_input[], int input_length, int pb_mapping[], int rf_mapping[26], Rotor enigma_rotors[], int number_of_rotors, int enigma_output[]){

  for ( int i = 0; i < input_length; i++){

    int output = 0;
    int input = enigma_input[i];
    
    //Scramble through Plugboard
    output = pb_mapping[input];

    //Enter row of rotors from plugboard. Start from the right. Does not enter for loop if number_of_rotors = 0.
    if ( number_of_rotors > 0 ){ 
      for ( int i = number_of_rotors - 1; i >= 0; i--){

	// if not the rightmost rotor, check notch of right rotor and turn if at 12 o'clock
	enigma_rotors[i].rotor_rotation(enigma_rotors, number_of_rotors, i);
	/*
	  cout << input << " r " << i << " pos is ";
	  for ( int x = 0; x < 26; x++){
	  cout << setw(2) << enigma_rotors[i].input_mapping[x] << " ";
	  }
	  cout << endl;*/
	output = enigma_rotors[i].right_to_left(output);
      }
    }
    
    //Enter reflector
    output = rf_mapping[output];
    
    //Enter set of rotors from reflector. Start from the left. Does not enter for loop if number_of_rotors = 0.
    if ( number_of_rotors > 0 ){
      for ( int i = 0; i < number_of_rotors ; i++){
	output = enigma_rotors[i].left_to_right(output);
      }
    }
    
    //Scramble through Plugboard
    search_array(pb_mapping, output);

    //Assign to output array
    enigma_output[i] = output;    
  }

  for ( int i = 0; i < input_length; i++){
    char letter = static_cast<char>(enigma_output[i] + 65); 
    cout << letter;
  }
  
}

