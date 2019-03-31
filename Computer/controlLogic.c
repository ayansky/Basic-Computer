#include<stdio.h>
#include "basicComputer.h"

//since the set of supported operations does not include MOV
//A and B registers' values are hardcoded

unsigned char a_register = 16;
unsigned char b_register = 3;

//control logic model
void controlLogic(ram myRam) {
    unsigned char operation; //holds the operation to be completed next
    while (programCounter < count) {
        operation = read(myRam, (programCounter));
        a_register = alu(a_register, b_register, operation);
        //update the program counter in accordance of the operation that was executed (1,2,3 bytes)
        if (((operation >= 5) && (operation <=8)) || ((operation >= 23) && (operation <=25))) {
            updatePC(3);
        } else if ((operation == 3) || (operation == 4)) {
            updatePC(2);
        } else updatePC(1);
    }
}
