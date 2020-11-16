#ifndef ENIGMA_H
#define ENIGMA_H


int search_array(int mapping[], int output);
void check_command_line(int argc, char* argv[]);
void read_input(int engima_input[], int& input_length);
void decoder_encoder(int input, Plugboard plugboard, Reflector reflector, Rotor enigma_rotors[], int number_of_rotors);
void enigma_machine(Plugboard plugboard, Reflector reflector, Rotor enigma_rotors[], int number_of_rotors);

#endif
