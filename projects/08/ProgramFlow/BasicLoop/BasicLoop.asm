// bootstrap
@256
D=A
@SP
M=D
@1
D=A
@LCL
M=D
@2
D=A
@ARG
M=D
@3
D=A
@THIS
M=D
@4
D=A
@THAT
M=D
// callSys.init0
//pushconstantfunc_0
@func_0
D=A
@SP
A=M
M=D
@SP
M=M+1

@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@5
D=A
@0
D=D+A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
// goto Sys.init
@Sys.init
0;JMP

//func_0
(func_0)


//pushconstant0
@0
D=A
@SP
A=M
M=D
@SP
M=M+1

//poplocal0
@0
D=A
@LCL
D=M+D
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

//LOOP_START
(LOOP_START)
//pushargument0
@0
D=A
@ARG
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

//pushlocal0
@0
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

// add
@SP
AM=M-1
D=M
A=A-1
M=M+D

//poplocal0	
@0	
D=A
@LCL
D=M+D
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

//pushargument0
@0
D=A
@ARG
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

//pushconstant1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1

// sub
@SP
AM=M-1
D=M
A=A-1
M=M-D

//popargument0
@0
D=A
@ARG
D=M+D
@R15
M=D
@SP
AM=M-1
D=M
@R15
A=M
M=D

//pushargument0
@0
D=A
@ARG
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

// if-gotoLOOP_START
@SP
AM=M-1
D=M
@LOOP_START
D;JNE

//pushlocal0
@0
D=A
@LCL
A=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1

(end)
@end
0;JMP
