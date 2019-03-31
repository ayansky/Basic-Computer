//This is a sample assembly language program

MOV A,#10                //regular instruction
	MOV B,#20        //indented instruction
ADD A,B
MOV 1000,A

MOV A,B234	 //Assembler does not mistake it for MOV A,B written incorrectly
                         //comment on an empty line

mov    B,  #40           //lower case and spaces
MOV ABCE,B               //address

CLR A


HLT

