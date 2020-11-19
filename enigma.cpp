#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "rotor.h"     // necessary as Rotor class is used as an arguement below
#include "reflector.h" // necessary as Reflector class is used as an argument below
#include "plugboard.h" // necessary as Plugboard class is used as an argument below
#include "enigma.h"
#include "errors.h"


// ========== internal helper functions ==========

// this function returns the index position of the second argument in the array
int search_array(const int mapping[], const int value){

  for ( int i = 0; i < NUM_OF_ALPHABETS; i++){
    if ( mapping[i] == value ) return i;   
  }

  // return -1 if not found
  return -1;

}


// ========== functions that are not member of any user defined class ==========

// this function checks that the command line arguments are of the right format
void check_command_line(int argc, char* argv[]){

  // check for at least 4 command line arguments
  if ( argc < FIXED_ARGV ) {
    std::cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << std::endl;
    exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
  }

  // check first argument
  std::string arg_1 = "./enigma";
  if ( argv[0] != arg_1) std::cerr << "Incorrect command line arguments" << std::endl; 

}

// this function brings together all the necessary parts of the enigma machine to encode/decode input to output
void Enigma::decoder_encoder( int input, const Plugboard plugboard, const Reflector reflector, Rotor* enigma_rotors, int number_of_rotors){
  // initialise ouput as 0
  int output = 0;
    
  //Scramble through Plugboard
  output = plugboard.right_to_left(input);
  
  //Enter row of rotors from plugboard. Start from the right. Does not enter for loop if number_of_rotors = 0.
  if ( number_of_rotors > 0 ){ 
    for ( int i = number_of_rotors - 1; i >= 0; i--){
      // if not the rightmost rotor, check notch of right rotor and turn if at 12 o'clock
      enigma_rotors[i].rotor_rotation(enigma_rotors, number_of_rotors, i);
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
  
  char letter = static_cast<char>(output + ASCII_OFFSET); 
  std::cout << letter;
    
}


// this function reads input from from the standard input stream into an array
void Enigma::encrypt(Rotor* enigma_rotors){

  char character;
  while ( std::cin >> std::ws >> character){
    
    // to check if input is from A to Z
    //if ( character < 65 || character > 90){
    if( !isalpha(character) || !isupper(character)  ){
      std::cerr << character << " is not a valid input character (input characters must be upper case letters A-Z)!" << std::endl;
      exit(INVALID_INPUT_CHARACTER);
    }
   
    // convert string to integer if numeric and add to enigma_input
    int input = static_cast<int>(character) - ASCII_OFFSET;  
    
    // decode/endocde input
    decoder_encoder(input, plugboard, reflector, enigma_rotors, number_of_rotors);
	
  }
    
}

