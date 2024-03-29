//
// Created by Antoine MAZURE on 29/03/2024.
//

#ifndef ARCHI_DECODEUR_H
#define ARCHI_DECODEUR_H

#include "microprocesseur.h"
typedef struct Instructions {
    uint8_t code;
    int8_t mask;
    char* assembly_string;
    int nb_octet;
}instructions;

typedef struct {
    int8_t opcode;
    int16_t memory_address;
    int8_t* bytes;
    int8_t* args;
} instruction_memory;

instructions* get_instructions();

int8_t decodeInstructionCode(int8_t byte);

int16_t readFileInstructions(char* pathname);

#endif //ARCHI_DECODEUR_H
