#include <stdio.h>
#include <stdlib.h>
#include "microprocesseur.h"

processeur_t processeur;

void PCin(){
    processeur.PC = processeur.InternalAdressBus;
}

void PCout(){
    processeur.InternalAdressBus = processeur.PC;
}

void PCHin(){
    *((int8_t*)&processeur.PC + 1) = processeur.InternalDataBus;
}

void PCLin() {
    *((int8_t*)&processeur.PC) = processeur.InternalDataBus;
}

void DLin(){
    processeur.DLatch = processeur.InternalDataBus;
}

void DLout(){
    processeur.InternalDataBus = processeur.DLatch;
}

void SR(int8_t r){
    processeur.CS = r;
}

void ALHin() {
    *((int8_t*)&processeur.AdressLatch) = processeur.InternalDataBus;
}

void ALLin() {
    *((int8_t*)&processeur.AdressLatch + 1) = processeur.InternalDataBus;
}

void AAout() {
    processeur.InternalAdressBus = processeur.AdressLatch + 1;
}

void ALin(){
    processeur.AdressLatch = processeur.InternalAdressBus;
}


void Rin(){
    processeur.R[processeur.CS] = processeur.InternalDataBus;
}

void Rout(){
    processeur.InternalDataBus = processeur.R[processeur.CS];
}

void Xin(){
    processeur.X = processeur.InternalDataBus;
}

void Yin(){
    processeur.Y = processeur.InternalDataBus;
}

void IRin(){
    processeur.IR = processeur.InternalDataBus;
}
void ALUout() {
    processeur.InternalDataBus = processeur.ALU;
}


void  NOT_ALU(){
    processeur.ALU = ~processeur.X;
}


void ADD_ALU(){
    processeur.ALU = processeur.X + processeur.Y;
    if (processeur.X + processeur.Y > 127)
        processeur.FC = 1;
    else if (processeur.X + processeur.Y == 0)
        processeur.FZ = 1;
    else {
        processeur.FC = 0;
        processeur.FZ = 0;
    }
}

void SUB_ALU(){
    processeur.ALU = processeur.X - processeur.Y;
    if (processeur.X - processeur.Y < -127)
        processeur.FC = 1;
    else if (processeur.X - processeur.Y == 0)
        processeur.FZ = 1;
    else {
        processeur.FC = 0;
        processeur.FZ = 0;
    }
}

void DEC_ALU(){
    processeur.ALU = processeur.X - 1;
    if (processeur.ALU == 0) {
        processeur.FZ = 1;
    }
    else if (processeur.X - 1 < -127)
        processeur.FC = 1;
    else {
        processeur.FC = 0;
        processeur.FZ = 0;
    }
}

void INC_ALU(){
    processeur.ALU = processeur.X + 1;
    if (processeur.X + 1 == 0) {
        processeur.FZ = 1;
    }
    else if (processeur.X + 1 > 127)
        processeur.FC = 1;
    else {
        processeur.FC = 0;
        processeur.FZ = 0;
    }
}

void RepX() {
    processeur.ALU = processeur.X;
}

void RepY() {
    processeur.ALU = processeur.Y;
}

void AND_ALU() {
    processeur.ALU = processeur.X & processeur.Y;
    if (processeur.ALU == 0)
        processeur.FZ = 1;
    else
        processeur.FZ = 0;
}

processeur_t* getMicroProcesseur() {
    return &processeur;
}


