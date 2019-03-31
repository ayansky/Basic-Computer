#include<stdio.h>
#include "basicComputer.h"
int programCounter = 0;

//program counter
void updatePC(int offset) {
    programCounter+=offset;
}
