#include<stdio.h>
#include "basicComputer.h"

int main(){
    printf("Before the execution:\n\n");
    printf("A register: %d\n", a_register);
    printf("B register: %d\n\n", b_register);
    assembler(); //call the assembler function to assemble the code and store it in output.hex
    ram myRam; //declare myRam of type ram
    myRam = makeMemory(100); //create a memory of size 100
    initMemoryHex(myRam,"output.hex");//Initialize the memory with data stored in output.hex file
    printf("Printing RAM\n");
    printf("________________________\n");
    printRam(myRam,0,(count-1));//Display the data stored in the memory from address 0 till the end
    printf("________________________\n\n");
    controlLogic(myRam); //calling the control logic
    printf("After the execution:\n\n");
    printf("A register: %d\n", a_register);
    printf("B register: %d\n\n", b_register);
    printf("Program Counter: %d\n", programCounter);

    return 0;
}
