# Nand2Tetris

>An archive of projects implemented by my self in the course series [Nand2Tetris](https://www.nand2tetris.org/).

Key words: `Nand2Tetris`, `HDL`, `Hack`, `Assembler`, `VMTranslator`, `Compiler`, `Jack`, `OS`

---

## Table of Contents

- [Nand2Tetris](#nand2tetris)
  - [Table of Contents](#table-of-contents)
  - [Highlighted Projects:](#highlighted-projects)
    - [0x05](#0x05)
    - [0x06](#0x06)
    - [0x07 \& 0x08](#0x07--0x08)
    - [0x0A \& 0x0B](#0x0a--0x0b)
  - [Debugging](#debugging)
  - [Testing](#testing)
  - [Certificate](#certificate)

## Highlighted Projects:

### 0x05

[-> Hack Computer](./projects/05)

> A simple Computer with a CPU (ALU, registers), a Memory (RAM, SCREEN, KEYBOARD), and a ROM (instruction memory) that can run Hack Machine Language.

- The computer process a fetch-decode-execute cycle and can handle I/O operations.
- No pipelining, no cache, no virtual memory since this is not a architecture course.
- implemented using HDL. (score: 100/100)

### 0x06 

[-> HackAssembler](./projects/06)

> A simple Assembler for the Hack Computer that can translate Hack Assembly Language to Hack Machine Language.

- The Hack Assembly Language supports symbolic labels, symbolic variables, symbolic arithmetic and logical operations, jump instructions, register assignment, and I/O operations.
- implemented using C++. (score: 100/100)

Compile command:

```shell 
$ g++ -Wall -O2 -std=gnu++17 HackAssembler.cpp -o HackAssembler 
```

Usage:

```shell
$ ./HackAssembler <fileName.asm>
```

### 0x07 & 0x08

[-> VMTranslator](./projects/08)

> A VM-to-Hack Translator that can translate VM Language to Hack Assembly Language.
>
> Consist of a parser and a code generator.

- The VM Language supports arithmetic and logical operations, memory access, program flow, function calling, and function return using stack frames.
- implemented using C++. (score: 200/200)

Compile command:

```shell
$ make
# can clean the .o files & the VMTranslator file using:
$ make clean
```

Usage:

```shell
$ ./VMTranslator <fileName.vm>
# or
$ ./VMTranslator <dirName>
```

### 0x0A & 0x0B

[-> JackCompiler](./projects/10)

> A Jack-to-VM Compiler that can translate Jack Language to VM Language.

- Jack is a high level language that supports class (constructor, method, function), variable (static, field, argument, local), types (int, char, boolean, class), statements (let, if, while, do, return), expressions (term, unaryOp, binaryOp) and so on.
- Implemented using C++. (score: 200/200)

```shell
# structure 
JackCompiler
│
├── JackAnalyzer
│   │
│   ├── Tokenizer
│   │
|   └── CompilationEngine
|
└── VMWriter
```

## Debugging

1. add `-g` option when compiling the code.
2. use the following command to trigger the debugger:

```shell
# on x86_64
$ gdb <executable file> <core dump file>
# or on arm64 (mac m1)
$ lldb <executable file> <core dump file>
```

## Testing

use the .sh scripts in [tools](./tools) to test your code.

```shell
# e.g.
$ ./tools/HardwareSimulator.sh
```

If your code is right, it will output "End of script - Comparison ended successfully".

Or you can use the following command to compare the difference between two files:

```shell
$ diff file1 file2
```

this command will compare the difference between file1 and file2. If there is no difference, it will not output anything.

for example in project00:

```shell
$ diff Mux16.out Mux16.cmp -b 
```

the -b option will ignore the blank space. You can also use -B to ignore the blank line.

## Certificate

&[part1](https://www.coursera.org/account/accomplishments/certificate/FCFZFL9FEVYG)

&[part2]