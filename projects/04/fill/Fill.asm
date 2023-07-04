// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.
// pesudo code:
// kbd = RAM[keyboard]
// if (kbd == 0) {goto white}
// else {goto black}
// (white) for(i=0;i<8192;i++){RAM[i]=000...}
// (black) for(i=0;i<8192;i++){RAM[i]=111...(-1)}

(LISTEN)
    @KBD
    D=M
    @WHITE
    D;JEQ
    @BLACK
    0;JMP

(WHITE)
    @i
    M=0 // i = 0
    (LOOP1)
        @i
        D=M
        @8192
        D=D-A
        @LOOP1_END
        D;JEQ // if i == 8192, break
        @SCREEN
        D=A
        @i
        A=D+M // A = SCREEN + i
        M=0 // RAM[A] = 0
        @i
        M = M + 1 // i++
        @LOOP1
        0;JMP
    (LOOP1_END)
@LISTEN
0;JMP
(BLACK)
    @i
    M=0 // i = 0
    (LOOP2)
        @i
        D=M
        @8192
        D=D-A
        @LOOP2_END
        D;JEQ // if i == 8192, break
        @SCREEN
        D=A
        @i
        A=D+M // A = SCREEN + i
        M=-1 // RAM[A] = -1
        @i
        M = M + 1 // i++
        @LOOP2
        0;JMP
    (LOOP2_END)

@LISTEN
0;JMP