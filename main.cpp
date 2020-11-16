#include <iostream>
#include <iomanip>

#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"
#include "enigma.h"


using namespace std;

int main (int argc, char** argv){

  // =========== CHECK COMMAND LINE ARGUMENTS ===========
  check_command_line(argc, argv);

  // =========== SETTING PLUGBOARD ===========
  Plugboard plugboard = Plugboard(argv[1]);
  
  // =========== SETTING ROTORS ===========
  int number_of_rotors = argc-4;

  // rotor position array will always be one larger than the number of rotors to initialise an array of 1 when there are 0 rotors
  int pos_array[number_of_rotors+1];
  load_rotor_pos(argv[argc-1], pos_array, number_of_rotors);


  // rotor array will always be one larger than the number of rotors to initialise an array of 1 when there are 0 rotors  
  Rotor enigma_rotors[number_of_rotors+1];
  initialise_enigma_rotors(pos_array, enigma_rotors, number_of_rotors, argv);
  
  // =========== SETTING REFLECTOR ===========
  Reflector reflector = Reflector(argv[2]);

  // =========== ENCODING/DECODING INPUT CHARACTERS ===========
  enigma_machine(plugboard, reflector, enigma_rotors, number_of_rotors);
  
  return 0;
}
