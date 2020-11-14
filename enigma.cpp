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

// this function reads input from from the standard input stream into an array
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

// this function brings together all the necessary parts of the enigma machine to encode/decode input to output
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
    search_array(pb_mapping, output);

    //Assign to output array
    enigma_output[i] = output;    
  }
  
  //print output
  for ( int i = 0; i < input_length; i++){
    cout << enigma_output[i] << endl;
    char letter = static_cast<char>(enigma_output[i] + 65); 
    cout << setw(2) << letter << endl;
  }
  
}

