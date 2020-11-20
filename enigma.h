#ifndef ENIGMA_H
#define ENIGMA_H

#include "reflector.h"  
#include "plugboard.h"
#include "rotor.h"

/*
namespace enigmaConstants {
  int NUM_OF_ALPHABETS = 26;   // no. of alphabets accepted by enigma
  int ASCII_OFFSET = 65;       // offset when converting from char to int
  int FIXED_ARGV = 4;          // no. of fixed arg passed to the command line (enigma, pb, rf and pos)

}*/

class Enigma{
  int argc;
  char** argv;
  Plugboard plugboard;
  //Rotor* rotors[];
  Reflector reflector;
  int number_of_rotors;

  // this is an internal helper function used in enigma_machine() that encodes/decodes the message and output it to the standard output stream.
  void decoder_encoder(int input, const Plugboard plugboard, const Reflector reflector, Rotor enigma_rotors[], int number_of_rotors);
 
public:
  Enigma(int argc, char** argv)
    : argc(argc), argv(argv), plugboard(Plugboard(argv[1])), reflector(Reflector(argv[2])), number_of_rotors(argc - FIXED_ARGV){};

  // this reads input from the standard input stream and calls decoder_encoder(). It takes the key components of the enigma machine as arguments.
  void encrypt(Rotor* enigma_rotors);
  
  
};

// ========= Non-member functions =========

// this function checks the arguments provided into the command line to ensure that it is of the format "engima plugboard-file reflector-file (<rotor-file>)* rotor-position" where there can be multiple or zero rotor files.
void check_command_line(int argc, char* argv[]);


//========== Internal Helper Functions ========== 

// this function searches the array for the position of the value and returns the index when it is found. It returns -1 otherwise. 
int search_array(const int mapping[], const int value);




#endif
