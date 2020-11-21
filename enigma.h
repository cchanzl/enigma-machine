#ifndef ENIGMA_H
#define ENIGMA_H

#include "reflector.h"  
#include "plugboard.h"
#include "rotor.h"

/* This is a user defined class for Enigma macihne, which contains the other key components as its member function. The engima machine encrypts messages be sending it through each of these components, starting from the plugboard, through the rotors (if any) from right to left, hitting the reflector, before returning through the rotors in the opposite direction back into the plugboard and ouput the encoded message via the standard output stream. 

Please refer to the .h file for information on the other components.
 */

class Enigma{
  int argc;
  char** argv;
  Plugboard plugboard;
  //Rotor* rotors[];
  Reflector reflector;
  int number_of_rotors;

  // this is an internal helper function used in enncrypt() that encodes the message and output it to the standard output stream.
  void decoder_encoder(int input, const Plugboard plugboard, const Reflector reflector, Rotor enigma_rotors[], int number_of_rotors);
 
public:
  // Default constructor which initialises the various components of the machine
  Enigma(int argc, char** argv)
    : argc(argc), argv(argv), plugboard(Plugboard(argv[1])), reflector(Reflector(argv[2])), number_of_rotors(argc - FIXED_ARGV){};

  // this reads input from the standard input stream and calls decoder_encoder().
  void encrypt(Rotor* enigma_rotors);
  
  
};

// ========= Non-member functions =========

// this function checks the arguments provided into the command line to ensure that it is of the format "engima plugboard-file reflector-file (<rotor-file>)* rotor-position" where there can be multiple or zero rotor files.
void check_command_line(int argc, char* argv[]);


//========== Internal Helper Functions ========== 

// this function searches the array for the position of the value and returns the index when it is found. It returns -1 otherwise. 
int search_array(const int mapping[], const int value);




#endif
