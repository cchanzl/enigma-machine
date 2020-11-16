#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "rotor.h"     // necessary as Rotor class is used as an arguement below
#include "reflector.h" // necessary as Reflector class is used as an argument below
#include "plugboard.h" // necessary as Plugboard class is used as an argument below
#include "enigma.h"
#include "errors.h"


using namespace std;

// ========== internal helper functions ==========

// this function returns the index position of the second argument in the array
int search_array(int mapping[], int output){
  
 for ( int i = 0; i < 26; i++){
   if ( mapping[i] == output ) {
     output = i;
     break;
   }
 }

 return output;

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

// this function brings together all the necessary parts of the enigma machine to encode/decode input to output
void decoder_encoder( int input, Plugboard plugboard, Reflector reflector, Rotor enigma_rotors[], int number_of_rotors){

  int output = 0;
    
  //Scramble through Plugboard
  output = plugboard.right_to_left(input);
  
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
  output = reflector.reflector_output(output);
    
  //Enter set of rotors from reflector. Start from the left. Does not enter for loop if number_of_rotors = 0.
  if ( number_of_rotors > 0 ){
    for ( int i = 0; i < number_of_rotors ; i++){
      output = enigma_rotors[i].left_to_right(output);
    }
  }
    
  //Scramble through Plugboard
  output = plugboard.left_to_right(output);
  
  char letter = static_cast<char>(output + 65); 
  cout << letter;
    
}


// this function reads input from from the standard input stream into an array
void enigma_machine(Plugboard plugboard, Reflector reflector, Rotor enigma_rotors[], int number_of_rotors){
  //cout << "Please enter text to be encoded/decoded in UPPER case." << endl;

  string input;
  cin >> input;
  
  for(char& c : input){
  
    // to check if input is from A to Z
    if ( c < 65 || c > 90){
      cerr << c << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
      exit(INVALID_INPUT_CHARACTER);
    }
   
    // convert string to integer if numeric and add to enigma_input
    c = static_cast<int>(c) - 65;  

    // decode/endocde input
    decoder_encoder(c, plugboard, reflector, enigma_rotors, number_of_rotors);
    
      }
    
}

