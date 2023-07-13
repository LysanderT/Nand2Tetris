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


// functionMain.fibonacci0
//Main.fibonacci
(Main.fibonacci)

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

//pushconstant2
@2
D=A
@SP
A=M
M=D
@SP
M=M+1

// lt
@SP
AM=M-1
D=M
A=A-1
D=M-D
M=-1
@lt_0
D;JLT
@SP
A=M-1
M=0
(lt_0)

// if-gotoIF_TRUE
@SP
AM=M-1
D=M
@IF_TRUE
D;JNE

// goto IF_FALSE
@IF_FALSE
0;JMP

//IF_TRUE
(IF_TRUE)
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

// return
@LCL
D=M
@R15
M=D
@5
A=D-A
D=M
@R14
M=D
@SP
AM=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@R15
A=M-1
D=M
@THAT
M=D
@2
D=A
@R15
A=M-D
D=M
@THIS
M=D
@3
D=A
@R15
A=M-D
D=M
@ARG
M=D
@4
D=A
@R15
A=M-D
D=M
@LCL
M=D
@R14
A=M
0;JMP

//IF_FALSE
(IF_FALSE)
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

//pushconstant2
@2
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

// callMain.fibonacci1
//pushconstantfunc_1
@func_1
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
@1
D=D+A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
// goto Main.fibonacci
@Main.fibonacci
0;JMP

//func_1
(func_1)

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

// callMain.fibonacci1
//pushconstantfunc_2
@func_2
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
@1
D=D+A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
// goto Main.fibonacci
@Main.fibonacci
0;JMP

//func_2
(func_2)

// add
@SP
AM=M-1
D=M
A=A-1
M=M+D

// return
@LCL
D=M
@R15
M=D
@5
A=D-A
D=M
@R14
M=D
@SP
AM=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@R15
A=M-1
D=M
@THAT
M=D
@2
D=A
@R15
A=M-D
D=M
@THIS
M=D
@3
D=A
@R15
A=M-D
D=M
@ARG
M=D
@4
D=A
@R15
A=M-D
D=M
@LCL
M=D
@R14
A=M
0;JMP

// functionSys.init0
//Sys.init
(Sys.init)

//pushconstant4
@4
D=A
@SP
A=M
M=D
@SP
M=M+1

// callMain.fibonacci1
//pushconstantfunc_3
@func_3
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
@1
D=D+A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
// goto Main.fibonacci
@Main.fibonacci
0;JMP

//func_3
(func_3)

//WHILE
(WHILE)
// goto WHILE
@WHILE
0;JMP

(end)
@end
0;JMP
