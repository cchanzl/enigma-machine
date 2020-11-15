#ifndef ENIGMA_H
#define ENIGMA_H


void search_array(int rotor_mapping[], int& output);
void check_command_line(int argc, char* argv[]);
void read_input(int engima_input[], int& input_length);
void enigma_machine(int enigma_input[], int input_length, int pb_mapping[], int rf_mapping[26], Rotor enigma_rotors[], int number_of_rotors, int engima_output[]);


#endif
