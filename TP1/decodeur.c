//
// Created by Antoine MAZURE on 29/03/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "decodeur.h"

#define NB_INSTRUCTIONS 17

instructions instructions_micropro[NB_INSTRUCTIONS] = {
        {0b01110000,0b00000000, "JMP HHLL", 3},
        {0b01110001,0b00000000, "JZ", 3},
        {0b01110010,0b00000000, "JC", 3},
        {0b01110011,0b00000000, "JMP RX0", 1},
        {0b01111000,0b11, "ST R0,RXn", 1},
        {0b01111100,0b11, "LD R0,RXn", 1},
        {0b01000000,0b111, "ST Rn, HHLL", 3},
        {0b01001000,0b111, "LD Rn, HHLL", 3},
        {0b01010000,0b111, "MV Rn, arg", 2},
        {0b01011000,0b111, "DEC Rn", 1},
        {0b01100000,0b111, "INC Rn", 1},
        {0b01101000,0b111, "NOT Rn", 1},
        {0b10000000,0b00011111, "ADD Rn, Rm", 1},
        {0b10100000,0b00011111, "SUB Rn, Rm", 1},
        {0b11000000,0b00011111, "AND Rn, Rm", 1},
        {0b11100000,0b00011111, "SWP Rn, Rm", 1},
        {0b00000000,0b00111111, "MV Rn, Rm", 1}
};

instructions* get_instructions(){
    return instructions_micropro;
}

int8_t decodeInstructionCode(int8_t byte){
    for(int i = 0; i < NB_INSTRUCTIONS; i++){
        if((byte & ~instructions_micropro[i].mask) == instructions_micropro[i].code){
            return i;
        }
    }
    return -1;
}

int16_t readFileInstructions(char* pathname){
    FILE* file = fopen(pathname, "r");
    if (file == NULL){
        printf("ERROR");
        exit(0);
    }
    processeur_t* processeur = getMicroProcesseur();
    int8_t instruct_size;
    int16_t instruct_address;
    size_t bytes;
    char memory_buffer[5];
    memory_buffer[4] = '\0';
    char buff[3] = "  \0";
    bytes = fread(memory_buffer, 4, 1, file);
    instruction_memory instruct;
    instruct_address = strtol(memory_buffer, NULL, 16);
    processeur -> PC = instruct_address;
    int16_t  last;
    while(strcmp(memory_buffer, "FFFF") != 0 && bytes > 0){
        fseek(file, 3,SEEK_CUR);
        bytes = fread(buff, 2, 1, file);
        int8_t bytes1 = strtol(buff, NULL, 16);
        int8_t opcode = decodeInstructionCode(bytes1);
        instructions instruction_info = instructions_micropro[opcode];
        instruct_size = instruction_info.nb_octet;
        processeur->RAM[instruct_address] = bytes1;
        fseek(file, 1, SEEK_CUR);
        for (int i = 1; i < instruct_size; i ++){
            bytes = fread(buff, 2, 1, file);
            fseek(file, 1, SEEK_CUR);
            processeur->RAM[instruct_address + i] = strtol(buff, NULL, 16);
        }
        last = instruct_address;
        bytes = fread(memory_buffer, 4, 1, file);
        instruct_address = strtol(memory_buffer, NULL, 16);
    }
    memset(&processeur->RAM[instruct_address + instruct_size], 0xFF, 2);
    fseek(file, 0, SEEK_SET);
    fclose(file);
    return last + instruct_size;
}

int main(int argc, char* argv[]){
    processeur_t* proc = getMicroProcesseur();
    memset(proc->RAM, 0, 1024);
    int16_t last_address = readFileInstructions(argv[1]);
    for(int i = 0; i < 1024; i ++){
        printf("%.2X " ,(uint8_t)proc->RAM[i]);
    }
    printf("\n%.4X", last_address);
}