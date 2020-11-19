#ifndef ENIGMA_H
#define ENIGMA_H

#include "reflector.h"  
#include "plugboard.h"
#include "rotor.h"

/* This is a user defined class for Enigma machine, which contains the individual components (plugboard, rotors (if any) and reflector).
   There can only be one reflector defined for an engima machine.
   Please refer to the comments beside each member for more information.
 */

class Enigma{
private:
  int argc;
  char** argv;
  Plugboard plugboard;
  Reflector reflector;
  int number_of_rotors;
  Rotor* enigma_rotors = new Rotor;
  
  // initialises a *group* of rotors when the objects are first created
  void initialise_rotors(Rotor* enigma_rotors, const int number_of_rotors, char* argv[]);
  
  // this is an internal helper function used in enigma_machine() that encodes/decodes the message and output it to the standard output stream.
  void decoder_encoder(int input, const Plugboard plugboard, const Reflector reflector, Rotor* enigma_rotors, int number_of_rotors);
 
public:
  Enigma(int argc, char** argv)
    : argc(argc), argv(argv), plugboard(Plugboard(argv[1])), reflector(Reflector(argv[2])), number_of_rotors(argc-4){
    if(number_of_rotors > 0){
      initialise_rotors(enigma_rotors, number_of_rotors, argv);
    }
    
  };

  // this reads input from the standard input stream and calls decoder_encoder(). It takes the key components of the enigma machine as arguments.
  void encrypt();
  
  
};

// ========= Non-member functions =========

// this function checks the arguments provided into the command line to ensure that it is of the format "engima plugboard-file reflector-file (<rotor-file>)* rotor-position" where there can be multiple or zero rotor files.
void check_command_line(int argc, char* argv[]);


//========== Internal Helper Functions ========== 

// this function searches the array for the position of the value and returns the index when it is found. It returns -1 otherwise. 
int search_array(const int mapping[], const int value);




#endif
