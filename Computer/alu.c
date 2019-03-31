#include<stdio.h>
#include "basicComputer.h"

//flags for CMP instruction
bool zeroFlag = 0;
bool carryFlag;

//Since our registers can hold values only from 0 to 255
//there is a limit on the correct result of the operation

//alu model
char alu(char a, char b, char op) {
    char result = a;
    switch (op) {
        case 9:
            result = a+b;
        break;
        case 10:
            result = a-b;
        break;
        case 11:
            result = a*b;
        break;
        case 12:
            result = a/b;
        break;
        case 17:
            result = a&b;
        break;
        case 18:
            result = a|b;
        break;
        case 19:
            result = a^b;
        break;
        case 20:
            result = a;
            if (a==b) {
                zeroFlag = 1;
                carryFlag = 0;
            } else (a>b) ? (carryFlag = 0) : (carryFlag = 1);
        break;
        default :
            printf("Error! Alu does not support this operation.\n\n");
        break;
    }
    return result;
}
