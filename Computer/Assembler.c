#include <stdio.h>
#include <stdlib.h>
#include "basicComputer.h"

//This program takes your "mycode.asm" file with the assembly language instructions and converts them to
//the machine code (in hexadecimal format). In case a syntax error occurs, its line number will be printed out.

const char* hex = "0123456789ABCDEF"; //array of hexadecimal characters
int count = 0; //counts the number of bytes needed for the program

void checkError(char* line, int i, int j) {
    for ( ; i<10; i++) {
        if (line[i] != '0') {
            printf("Error on line %d", j);
            exit(1);
        }
    }
}

void checkAddress(char* line, int i, int j) {
    if ((strchr(hex, line[i]) == 0) || (strchr(hex, line[i+1]) == 0) || // checking that address is in hexadecimal
        (strchr(hex, line[i+2]) == 0) || (strchr(hex, line[i+3]) == 0)) {
        printf("Error on line %d", j);
        exit(1);
    }
}

void checkData(char* line, int i, int j) {
    if ((strchr(hex, line[i]) == 0) || (strchr(hex, line[i+1]) == 0) || (line[i+2] != '0')) { // checking that data is in hexadecimal
        printf("Error on line %d", j);
        exit(1);
    }
}

int assembler() {

    char NOP[] = "NOP";
    char MOVAB[] = "MOVA,B";
    char MOVBA[] = "MOVB,A";
    char MOVA[] = "MOVA,#";
    char MOVB[] = "MOVB,#";
    char MOVAaddress[] = "MOVA,";
    char MOVBaddress[] = "MOVB,";
    char MOVaddressA[] = "MOV0000,A";
    char MOVaddressB[] = "MOV0000,B";
    char ADDAB[] = "ADDA,B";
    char SUBAB[] = "SUBA,B";
    char MULAB[] = "MULA,B";
    char DIVAB[] = "DIVA,B";
    char INC[] = "INC";
    char DEC[] = "DEC";
    char ANDAB[] = "ANDA,B";
    char ORAB[] = "ORA,B";
    char XORAB[] = "XORA,B";
    char CMPAB[] = "CMPA,B";
    char CLR[] = "CLR";
    char JMP[] = "JMP";
    char JZ[] = "JZ";
    char JNZ[] = "JNZ";
    char CPL[] = "CPL";
    char XCHGAB[] = "XCHGA,B";
    char HLT[] = "HLT";

    //registers for each type of an assembly command
    int NOP_r = 0, MOVAB_r = 0, MOVBA_r = 0, MOVA_r = 0, MOVB_r = 0, MOVAaddress_r = 0, MOVBaddress_r = 0, MOVaddressA_r = 0,
        MOVaddressB_r = 0, ADDAB_r = 0, SUBAB_r = 0, MULAB_r = 0, DIVAB_r = 0, INC_r = 0, DEC_r = 0, ANDAB_r = 0, ORAB_r = 0,
        XORAB_r = 0, CMPAB_r = 0, CLR_r = 0, JMP_r = 0, JZ_r = 0, JNZ_r = 0, CPL_r = 0, XCHGAB_r = 0, HLT_r = 0;

    char line[10] = "0000000000";          //array of 10 characters to hold each command one by one

    //pointer to the input file
    FILE *fptr;
    if ((fptr = fopen("mycode.asm", "r")) == NULL) {
        printf("Error opening the file");
        exit(1);
    };

    //pointer to the output file
    FILE *fptrwrite;
    fptrwrite = fopen("output.hex", "w");

    int i, j, k; //counters

    char c; //holds the character being read from the file

    int lines = 1; //number of lines

    //counting the number of lines in the "mycode.asm"
    while(!feof(fptr))
        {
          c = fgetc(fptr);
          if(c == '\n')
          {
            lines++;
          }
        }

    rewind(fptr); //going back to the beginning of the file

    //loop that checks the whole file line by line
    for (j=1; j<=lines;j++) {

        //making all registers equal to zero every time we go to a new line
        NOP_r = 0, MOVAB_r = 0, MOVBA_r = 0, MOVA_r = 0, MOVB_r = 0, MOVAaddress_r = 0, MOVBaddress_r = 0, MOVaddressA_r = 0,
        MOVaddressB_r = 0, ADDAB_r = 0, SUBAB_r = 0, MULAB_r = 0, DIVAB_r = 0, INC_r = 0, DEC_r = 0, ANDAB_r = 0, ORAB_r = 0,
        XORAB_r = 0, CMPAB_r = 0, CLR_r = 0, JMP_r = 0, JZ_r = 0, JNZ_r = 0, CPL_r = 0, XCHGAB_r = 0, HLT_r = 0;

        //reading the line and storing it in the array line[]. The array has 10 characters,
        //because the biggest number of characters an instruction can take is 9, plus the '/n' character.
        //The program skips spaces and new lines.

        for (k = 0; k<10; ) {
            //spaces, EOF, "/", new line and tab characters are disregarded
            if (((c = getc(fptr)) != ' ') && (c != '\n') && (c != EOF) && (c != '\t') && (c != '/')) {
                //if the character is in lower case, it is converted to the upper case
                if ((c>='a') && (c<='z')) {
                    c-=32;
                }
                line[k] = c;
                k++;
            }
            //going through the comment without reading it into the array line[]
            if (c == '/') {
                if ((c = getc(fptr)) == '/') {
                    while ((c = getc(fptr)) != '\n') {};
                    if (k == 0) { //if the comment is the only thing on the line, it is not being converted
                        goto FOUND;
                    }
                } else {
                    printf("Error on line %d", j);
                    exit(1);
                }
                goto END; //stop reading the line
            }

            //if there are more than 9 characters in the line,
            // and it is not a comment, the instruction is not
            //on the list, so the program is terminated
            if ((c != '\n') && (k == 10)) {
                printf("Error on line %d", j);
                exit(1);
            }
            //skipping a null line
            if (((c == '\n') || (c == EOF)) && (k == 0)) {
                goto FOUND;
           }
           END:
           //stop reading if it is the end of a line or file
            if ((c == '\n') || (c == EOF)) {
                k = 10;
            }
        }
           //checking for NOP
            for (i=0; i<3; i++) {
                if (line[i] == NOP[i]) {
                    NOP_r++;
                }
            }
            if (NOP_r == 3) {
                checkError(line, i, j);
                fprintf(fptrwrite, "00");
                count++;
                goto FOUND;
            }

            //checking for MOV address A
            for (i=0; i<9; i++) {
                if ((line[i] == MOVaddressA[i]) && ((i<3) || (i>6))) {
                    MOVaddressA_r++;
                }
            }
            if (MOVaddressA_r == 5) {
                i = 3; //address starts at this position
                checkAddress(line, i, j);
                fprintf(fptrwrite, "07");
                //printing the address
                for ( ;i<7; i++) {
                    fprintf(fptrwrite, "%c", line[i]);
                }
                count+=3;
                goto FOUND;
            }

            //checking for MOV address B
            for (i=0; i<9; i++) {
                if ((line[i] == MOVaddressB[i]) && ((i<3) || (i>6))) {
                    MOVaddressB_r++;
                }
            }
            if (MOVaddressB_r == 5) {
                i = 3; //address starts at this position
                checkAddress(line, i, j);
                fprintf(fptrwrite, "08");
                //printing the address
                for ( ;i<7; i++) {
                    fprintf(fptrwrite, "%c", line[i]);
                }
                count+=3;
                goto FOUND;
            }

            //Checking for MOV A,#data
            for (i=0; i<6; i++) {
                if (line[i] == MOVA[i]) {
                    MOVA_r++;
                }
            }
            if (MOVA_r == 6) {
                //checking that there are only 2 characters after # and that they are both hexadecimal
                checkData(line, i, j);
                fprintf(fptrwrite, "03");
                //printing the data
                for ( ;i<8; i++) {
                    fprintf(fptrwrite, "%c", line[i]);
                }
                count+=2;
                goto FOUND;

            }

            //MOV B,#data
            for (i=0; i<6; i++) {
                if (line[i] == MOVB[i]) {
                    MOVB_r++;
                }
            }
            if (MOVB_r == 6) {
                //checking that there are only 2 characters after # and that they are both hexadecimal
                checkData(line, i, j);
                fprintf(fptrwrite, "04");
                //printing the data
                for (;i<8; i++) {
                    fprintf(fptrwrite, "%c", line[i]);
                }
                count+=2;
                goto FOUND;

            }

            //checking for MOV A,B
            for (i=0; i<6; i++) {
                if (line[i] == MOVAB[i]) {
                    MOVAB_r++;
                }
            }
            if ((MOVAB_r == 6) && (line[i] == '0')) {
                checkError(line, i, j);
                fprintf(fptrwrite, "01");
                count++;
                goto FOUND;

            }

            //checking for MOV B,A
            for (i=0; i<6; i++) {
                if (line[i] == MOVBA[i]) {
                    MOVBA_r++;
                }
            }
            if ((MOVBA_r == 6)&& (line[i] == '0')) {
                checkError(line, i, j);
                fprintf(fptrwrite, "02");
                count++;
                goto FOUND;

            }

            //checking for MOV A,address
            for (i=0; i<5; i++) {
                if (line[i] == MOVAaddress[i]) {
                    MOVAaddress_r++;
                }
            }
                if (MOVAaddress_r == 5) {
                    checkAddress(line, i, j);
                    fprintf(fptrwrite, "05");
                    //printing the address
                    for ( ;i<9; i++) {
                        fprintf(fptrwrite, "%c", line[i]);
                    }
                    count+=3;
                    goto FOUND;
                }

            //Checking for MOV B,address
            for (i=0; i<5; i++) {
                if (line[i] == MOVBaddress[i]) {
                    MOVBaddress_r++;
                }
            }
            if (MOVBaddress_r == 5) {
                checkAddress(line, i, j);
                fprintf(fptrwrite, "06");
                //printing the address
                for (;i<9; i++) {
                    fprintf(fptrwrite, "%c", line[i]);
                }
                count+=3;
                goto FOUND;
            }



            //checking for ADD A,B
            for (i=0; i<6; i++) {
                if (line[i] == ADDAB[i]) {
                    ADDAB_r++;
                }
            }
            if (ADDAB_r == 6) {
                checkError(line, i, j);
                fprintf(fptrwrite, "09");
                count++;
                goto FOUND;

            }

            //checking for SUB A,B
            for (i=0; i<6; i++) {
                if (line[i] == SUBAB[i]) {
                    SUBAB_r++;
                }
            }
            if (SUBAB_r == 6) {
                checkAddress(line, i, j);
                fprintf(fptrwrite, "0A");
                count++;
                goto FOUND;

            }

            //checking for MUL A,B
            for (i=0; i<6; i++) {
                if (line[i] == MULAB[i]) {
                    MULAB_r++;
                }
            }
            if (MULAB_r == 6) {
                checkAddress(line, i, j);
                fprintf(fptrwrite, "0B");
                count++;
                goto FOUND;
            }

            //checking for DIV A,B
            for (i=0; i<6; i++) {
                if (line[i] == DIVAB[i]) {
                    DIVAB_r++;
                }
            }
            if (DIVAB_r == 6) {
                checkError(line, i, j);
                fprintf(fptrwrite, "0C");
                count++;
                goto FOUND;

            }

             //checking for INC A/B
            for (i=0; i<3; i++) {
                if (line[i] == INC[i]) {
                    INC_r++;
                }
            }
            if (INC_r == 3) {
                i++;
                checkError(line, i, j);
                if (line[3] == 'A') {
                    fprintf(fptrwrite, "0D");
                }
                if (line[3] == 'B') {
                    fprintf(fptrwrite, "0E");
                }
                count++;
                goto FOUND;

            }

             //checking for DEC A/B
            for (i=0; i<3; i++) {
                if (line[i] == DEC[i]) {
                    DEC_r++;
                }
            }
            if (DEC_r == 3) {
                i++;
                checkError(line, i, j);
                if (line[3] == 'A') {
                    fprintf(fptrwrite, "0F");
                }
                if (line[3] == 'B') {
                    fprintf(fptrwrite, "10");
                }
                count++;
                goto FOUND;
            }

            //checking for AND A,B
            for (i=0; i<6; i++) {
                if (line[i] == ANDAB[i]) {
                    ANDAB_r++;
                }
            }
            if (ANDAB_r == 6) {
                checkError(line, i, j);
                fprintf(fptrwrite, "11");
                count++;
                goto FOUND;

            }

            //checking for OR A,B
            for (i=0; i<5; i++) {
                if (line[i] == ORAB[i]) {
                    ORAB_r++;
                }
            }
            if (ORAB_r == 5) {
                checkError(line, i, j);
                fprintf(fptrwrite, "12");
                count++;
                goto FOUND;
            }

            //checking for XOR A,B
            for (i=0; i<6; i++) {
                if (line[i] == XORAB[i]) {
                    XORAB_r++;
                }
            }
            if (XORAB_r == 6) {
                checkError(line, i, j);
                fprintf(fptrwrite, "13");
                count++;
                goto FOUND;

            }

            //checking for CMP A,B
            for (i=0; i<6; i++) {
                if (line[i] == CMPAB[i]) {
                    CMPAB_r++;
                }
            }
            if (CMPAB_r == 6) {
                checkError(line, i, j);
                fprintf(fptrwrite, "14");
                count++;
                goto FOUND;
            }

            //checking for CLR A/B
            for (i=0; i<3; i++) {
                if (line[i] == CLR[i]) {
                    CLR_r++;
                }
            }
            if (CLR_r == 3) {
                i++;
                checkError(line, i, j);
                if (line[3] == 'A') {
                    fprintf(fptrwrite, "15");
                }
                if (line[3] == 'B') {
                    fprintf(fptrwrite, "16");
                }
                count++;
                goto FOUND;
            }

            //checking for JMP address
            for (i=0; i<3; i++) {
                if (line[i] == JMP[i]) {
                    JMP_r++;
                }
            }
            if (JMP_r == 3) {
                checkAddress(line, i, j);
                i+=4;
                checkError(line, i, j);
                fprintf(fptrwrite, "17");
                //printing the address
                for (i = 3 ;i<7; i++) {
                    fprintf(fptrwrite, "%c", line[i]);
                }
                count+=3;
                goto FOUND;
            }

            //checking for JZ address
            for (i=0; i<2; i++) {
                if (line[i] == JZ[i]) {
                    JZ_r++;
                }
            }
            if (JZ_r == 2) {
                checkAddress(line, i, j);
                i+=4;
                checkError(line, i, j);
                fprintf(fptrwrite, "18");
                //printing the address
                for (i = 2; i<6; i++) {
                    fprintf(fptrwrite, "%c", line[i]);
                }
                count+=3;
                goto FOUND;

            }

            //checking for JNZ address
            for (i=0; i<3; i++) {
                if (line[i] == JNZ[i]) {
                    JNZ_r++;
                }
            }
            if (JNZ_r == 3) {
                checkAddress(line, i, j);
                i+=4;
                checkError(line, i, j);
                fprintf(fptrwrite, "19");
                //printing the address
                for (i = 3 ; i < 7; i++) {
                    fprintf(fptrwrite, "%c", line[i]);
                }
                count+=3;
                goto FOUND;

            }

            //checking for CPL A/B
            for (i=0; i<3; i++) {
                if (line[i] == CPL[i]) {
                    CPL_r++;
                }
            }
            if (CPL_r == 3) {
                i++;
                checkError(line, i, j);
                if (line[3] == 'A') {
                   fprintf(fptrwrite, "20");
                }
                if (line[3] == 'B') {
                   fprintf(fptrwrite, "21");
                }
                count++;
                goto FOUND;

            }

            //checking for XCHG A,B
            for (i=0; i<7; i++) {
                if (line[i] == XCHGAB[i]) {
                    XCHGAB_r++;
                }
            }
            if (XCHGAB_r == 7) {
                checkError(line, i, j);
                fprintf(fptrwrite, "22");
                count++;
                goto FOUND;

            }

            //checking for HLT
            for (i=0; i<3; i++) {
                if (line[i] == HLT[i]) {
                    HLT_r++;
                }
            }
                if (HLT_r == 3) {
                    checkError(line, i, j);
                    fprintf(fptrwrite, "23");
                    count++;
                    goto FOUND;
                }

            /////////////////////////////////////////////////////////
            ///////In case line matches none of the instructions
            printf("Error on line %d", j);
            exit(1);

            ///////////////////////////////////////////////////////////////
            ///////Clearing the line[] array for the next line
            FOUND:
            for (i = 0; i<10;i++) {
                line[i] = '0';
            }
    }

    printf("Code assembled!\n\n");
    fclose(fptrwrite);
    fclose(fptr);
    return 0;
}
