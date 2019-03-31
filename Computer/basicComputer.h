#ifndef BASICCOMPUTER_H_INCLUDED
#define BASICCOMPUTER_H_INCLUDED
#include <stdbool.h>

extern int count;
extern int programCounter;
extern bool zeroFlag;
extern bool carryFlag;
extern unsigned char a_register;
extern unsigned char b_register;

typedef char * ram;
ram makeMemory(int depth);
int write(ram myRam,unsigned int address, unsigned char data);
unsigned char read(ram myRam,unsigned int address);
int printRam(ram myRam,unsigned int startAddress,unsigned int endAddress);
int initMemory(ram myRam,char * fileName);
int initMemoryHex(ram myRam,char * fileName);
int assembler();
void checkError(char* line, int i, int j);
void checkAddress(char* line, int i, int j);
void checkData(char* line, int i, int j);
char alu(char a, char b, char op);
void controlLogic(ram myRam);


#endif // BASICCOMPUTER_H_INCLUDED

