#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"
#include "enigma.h"

int main (int argc, char** argv){

  // =========== CHECK COMMAND LINE ARGUMENTS ============
  check_command_line(argc, argv);

  // =========== SETTING ROTORS ===========
  /*
  int number_of_rotors = argc-4;

  // rotor array will always be one larger than the number of rotors to initialise an array of 1 when there are 0 rotors  
  Rotor enigma_rotors[number_of_rotors+1];

  // to initialise the set of enigma rotors. does nothing if there are no rotors.
  initialise_enigma_rotors(enigma_rotors, number_of_rotors, argv);
  */
  // =========== ENCODING/DECODING INPUT ===========
  Enigma enigma = Enigma(argc, argv);
  enigma.encrypt();

  // If no errors, exit normally
  return 0;
}
