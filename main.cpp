#include "rotor.h"
#include "enigma.h"


int main (int argc, char** argv){
  
  
  
  // =========== CHECK COMMAND LINE ARGUMENTS ===========
  check_command_line(argc, argv);
  
  
  // =========== SETTING ROTORS ===========
  int number_of_rotors = argc-4;
  Enigma enigma = Enigma(argc, argv);
 
  // to initialise the set of enigma rotors. does nothing if there are no rotors.
  if ( number_of_rotors > 0) {
    Rotor enigma_rotors[number_of_rotors];
    initialise_enigma_rotors(enigma_rotors, number_of_rotors, argv);
    enigma.encrypt(enigma_rotors);
  }
  else {
    enigma.encrypt(nullptr);
  }
  
  
  // =========== ENCODING/DECODING INPUT ===========
  
  // If no errors, exit normally
  return 0;
}
