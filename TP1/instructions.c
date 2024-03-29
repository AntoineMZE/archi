//
// Created by Antoine MAZURE on 29/03/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"

#define processeur getMicroProcesseur()


void JMP(int8_t status) {
    int8_t pcl = processeur->DLatch;
    DLout(); PCLin(); AAout(); ALin();
    int8_t pch = processeur->DLatch;
    DLout();
    if (status == 0)
        printf("JMP %.2X%.2X", pcl, pch);
    else if (status == 1)
        printf("JC %.2X%.2X", pcl, pch);
    else
        printf("JZ %.2X%.2X", pcl, pch);
}


void JMP_RX0() {
    SR(0); Rout(); PCLin();
    SR(1); Rout();
    printf("JMP %%RX0");
}

void ST_R0_RXn(int8_t n) {
    SR(n); Rout(); ALLin();
    SR(n + 1); Rout(); ALHin();
    SR(0); Rout(); DLin();
    printf("ST %%R0 %%RX%d", n);
}

void LD_R0_RXn(int8_t n) {
    SR(n); Rout(); ALLin();
    SR(n + 1); Rout(); ALHin();
    SR(0); DLout(); Rin();
    printf("LD %%R0 %%RX%d", n);
}

void ST(int8_t Rn) {
    DLout(); Xin(); AAout(); ALin();
    AAout(); PCin(); DLout(); ALLin();
    RepX(); ALUout(); ALHin();
    SR(Rn); Rout(); DLin();
    printf("ST %%R%d", Rn);
}

void LD(int8_t Rn) {
    DLout(); Xin(); AAout(); ALin();
    AAout(); PCin(); DLout(); ALLin();
    RepX(); ALUout(); ALHin();
    DLout(); SR(Rn); Rin();
    printf("LD %%R%d", Rn);
}

void MV_ARG(int8_t Rn) {
    AAout(); PCin();
    int8_t arg = processeur->DLatch;
    DLout(); SR(Rn); Rin();
    printf("MV %%R%d, $%d", Rn, arg);
}

void DEC(int8_t Rn) {
    SR(Rn); Rout(); Xin();
    DEC_ALU(); ALUout(); Rin();
    printf("DEC %%R%d", Rn);
}

void INC(int8_t Rn) {
    SR(Rn); Rout(); Xin();
    INC_ALU(); ALUout(); Rin();
    printf("INC %%R%d", Rn);
}

void ADD(int8_t Rn, int8_t Rm) {
    SR(Rn); Rout(); Xin();
    SR(Rm); Rout(); Yin();
    ADD_ALU(); ALUout(); SR(Rn); Rin();
    printf("ADD %%R%d, %%R%d", Rn, Rm);
}

void SUB(int8_t Rn, int8_t Rm) {
    SR(Rn); Rout(); Xin();
    SR(Rm); Rout(); Yin();
    SUB_ALU(); ALUout(); SR(Rn); Rin();
    printf("SUB %%R%d, %%R%d", Rn, Rm);
}

void AND(int8_t Rn, int8_t Rm) {
    SR(Rn); Rout(); Xin();
    SR(Rm); Rout(); Yin();
    AND_ALU(); ALUout(); SR(Rn); Rin();
    printf("AND %%R%d, %%R%d", Rn, Rm);
}

void NOT(int8_t Rn) {
    SR(Rn); Rout(); Xin();
    NOT_ALU(); ALUout(); SR(Rn); Rin();
    printf("NOT %%R%d", Rn);
}

void SWP(int8_t Rn, int8_t Rm) {
    SR(Rn); Rout(); Xin();
    SR(Rm); Rout(); Yin();
    RepX(); ALUout(); SR(Rm); Rin();
    RepY(); ALUout(); SR(Rn); Rin();
    printf("SWP %%R%d, %%R%d", Rn, Rm);
}

void MV_Rn_Rm(int8_t Rn, int8_t Rm) {
    SR(Rm); Rout();
    SR(Rn); Rin();
    printf("MV %%R%d, %%R%d", Rn, Rm);
}