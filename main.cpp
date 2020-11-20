#include "rotor.h"
#include "enigma.h"


int main (int argc, char** argv){
  
  // For global constants, please see "constants.h"
  
  try{
    // =========== CHECK COMMAND LINE ARGUMENTS ===========
    check_command_line(argc, argv);
  
  
    // =========== ENCODING/DECODING INPUT ===========
    // Note that rotor position starts from 0 from the left.
    // Example: For three rotors, their position will be 0, 1 and 2 from left to right
    int number_of_rotors = argc - FIXED_ARGV;
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
  } catch(int e){
    return e;
  }
  
  
  // If no errors, exit normally
  return 0;
}
