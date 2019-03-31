#include<stdlib.h>
#include<stdio.h>
#include "basicComputer.h"

int maxMemSize=0; //Global variable to store memory size
char hexarr[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; //array of hex to convert from string to int

//function that converts a character to integer
int convertCharToInt(char c) {
    int integer;
    int i;
    for (i = 0; i < 16; i++) {
        if (c == hexarr[i]) {
            integer = i;
        }
    }
    return integer;
}

//Function to create a memory
//input -> depth of memory
//returns -> pointer to the memory
ram makeMemory(int depth){
    ram myRam; //type ram is stored in ram.h file
    myRam = (ram)malloc(depth*sizeof(char));
    maxMemSize = depth;//store the depth in the global variable
    return myRam;//return the pointer back
}

//Function to write to the memory
//input -> pointer to memory, address where to write, data to be written
int write(ram myRam,unsigned int address, unsigned char data){
    //Just check write address is with in the memory size
    if(address >= maxMemSize){
        printf("Write Error: Address larger than memory size");
        return -1;
    }
    myRam[address] = data;
    return 0;
}

//Address to read from the memory
//input -> pointer to memory, address from where data to be read
unsigned char read(ram myRam,unsigned int address){
    //Just check read address is with in the memory size
    if(address >= maxMemSize){
        printf("Read Error: Address larger than memory size");
        return -1;
    }
    //return data from the memory
    return myRam[address];
}

//Function to print the contents of the memory
//input -> pointer to memory, start address to print, end address to print
int printRam(ram myRam,unsigned int startAddress,unsigned int endAddress){
    int i;
    if(startAddress >= maxMemSize || endAddress >= maxMemSize){
        printf("Read Error: Address larger than memory size");
        return -1;
    }
    for(i=startAddress;i<=endAddress;i++){
        //use the read function to read from the memory
        printf("Address:%d Data:%d(%c)\n",i,read(myRam,i),read(myRam,i));//We are printing in decimal (%d) and in character (%c)
    }
    return 0;
}

//Function to initialize memory from data stored in a text file
//input -> pointer to memory, file name
int initMemory(ram myRam,char * fileName){
    unsigned char myData;
    unsigned int address=0;
    FILE *fptr;
    fptr = fopen(fileName,"r");//open the file in read mode
    if(fptr == NULL){ //check whether the file exists
        printf("File error");
        return -1;
    }
    myData = fgetc(fptr);//fgetc() function to read one character from the file at a time
    while(myData != 255){//When the end of file is reached, fgetc returns 255(unsigned) or -1(signed)
        write(myRam,address,myData);
        address++;
        myData = fgetc(fptr);
    }
    return 0;
}

//Function to initialize memory from instructions stored in HEX file
//input -> pointer to memory, file name
int initMemoryHex(ram myRam,char * fileName){
    unsigned char myData;
    int myDataInt; //integer equivalent of the instruction/data/address
    unsigned int address=0;
    FILE *fptr;
    fptr = fopen(fileName,"r");//open the file in read mode
    if(fptr == NULL){ //check whether the file exists
        printf("File error");
        return -1;
    }
    myData = fgetc(fptr);//fgetc() function to read one character from the file at a time
    while(myData != 255){//When the end of file is reached, fgetc returns 255(unsigned) or -1(signed)
        int byteSum = 0;
        //converting two characters to one-byte integer
        myDataInt = convertCharToInt(myData);
        byteSum += myDataInt*16;
        myData = fgetc(fptr);
        myDataInt = convertCharToInt(myData);
        byteSum += myDataInt;
        //write the converted data to RAM
        write(myRam,address,byteSum);
        address++;
        myData = fgetc(fptr);
    }
    return 0;
}
