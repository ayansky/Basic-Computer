Basic Computer program
Author: adilya.bakambekova@nu.edu.kz

The assembler parts supports the following instruction set:

Mnemonic	Operand		Hex code	Number of Bytes
NOP		None		00		1
MOV		A,B		01		1
MOV		B,A		02		1
MOV		A,#data		03		2
MOV		B,#data		04		2
MOV		A,Address	05		3
MOV		B,Address	06		3
MOV		Address,A	07		3
MOV		Address,B	08		3
ADD		A,B		09		1
SUB		A,B		0A		1
MUL		A,B		0B		1
DIV		A,B		0C		1
INC 		A 		0D 		1
INC 		B 		0E 		1
DEC 		A 		0F 		1
DEC 		B 		10 		1
AND 		A,B 		11 		1
OR 		A,B 		12 		1
XOR 		A,B 		13 		1
CMP 		A,B 		14 		1
CLR 		A 		15 		1
CLR 		B 		16 		1
JMP 		Address 	17 		3
JZ 		Address 	18 		3
JNZ 		Address 	19 		3
CPL 		A 		20 		1
CPL 		B 		21 		1
XCHG 		A,B 		22 		1
HLT 		None 		23 		1



The following operations are supported by ALU:

ADD		A,B		09		1
SUB		A,B		0A		1
MUL		A,B		0B		1
DIV		A,B		0C		1
AND 		A,B 		11 		1
OR 		A,B 		12 		1
XOR 		A,B 		13 		1
CMP 		A,B 		14 		1


Write your assembly language code in the "mycode.asm" file. Make sure it is in the same directory
as the "assembler.c" file. 

The assembler is case- and space-insensitive, however each command should start with a new line. 
There may be null lines in between the instructions or at the beginning/end of the code. You can also
add the comments (preceeded by "//"), however, they should be written only after the instruction or
on a separate line.

The data's size should be 8 bits, and address' - 16 bits. 

Compile and run the program. If the program is successfully assembled, the corresponding 
message will appear and the "output.hex" file will contain the machine code instructions. 
If the error occurs, the correspoding notification will be shown. 

Then, the machine code from output.hex will be stored in RAM and processed by the control logic. 
There are two registers A and B, each of type unsigned char. This places a limitation on the minimum
and maximum values they can hols (0 and 255 respectively). 

Control logic calls ALU to execute the instructions and increments the program counter accordingly. 


