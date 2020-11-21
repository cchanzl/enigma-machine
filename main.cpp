#include "rotor.h"
#include "enigma.h"


int main (int argc, char** argv){
  
  // For constants defined, please see "constants.h"
  
  try{
    // =========== CHECK COMMAND LINE ARGUMENTS ===========
    check_command_line(argc, argv);
   
    // =========== ENCODING/DECODING INPUT ===========
    // Note that rotor position starts from 0 from the left.
    // Example: For three rotors, their position will be 0, 1 and 2 from left to right

    Enigma enigma = Enigma(argc, argv);
    enigma.encrypt();

  } catch(int error_code){ 
    return error_code;
  }
   
  // If no errors, exit normally
  return 0;
}
