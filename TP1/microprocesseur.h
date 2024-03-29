//
// Created by Antoine MAZURE on 01/02/2024.
//
#ifndef ARCHI_MICROPROCESSEUR_H
#define ARCHI_MICROPROCESSEUR_H


typedef struct {
    int16_t InternalAdressBus;
    int8_t InternalDataBus;
    int8_t R[8];
    int8_t CS;
    int8_t X;
    int8_t Y;
    int8_t PCH;
    int8_t PCL;
    int16_t PC;
    int8_t IR;
    int16_t AdressLatch;
    int8_t FZ;
    int8_t FC;
    int8_t ALU;
    int8_t DLatch;
    int8_t RAM[1024];
} processeur_t;

void PCin();

void PCout();

void PCHin();

void PCLin();

void DLin();

void DLout();

void SR(int8_t r);

void ALHin();

void ALLin();

void AAout();

void ALin();

void Rin();

void Rout();

void Xin();

void Yin();

void IRin();

void ALUout();

void  NOT_ALU();

void ADD_ALU();

void SUB_ALU();

void DEC_ALU();

void INC_ALU();

void RepX();

void RepY();

void AND_ALU();

processeur_t* getMicroProcesseur();

#endif //ARCHI_MICROPROCESSEUR_H
