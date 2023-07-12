# Nand2Tetris

An archive of projects implemented by my self in the course [Nand2Tetris](https://www.nand2tetris.org/).

Key words: `Nand2Tetris`, `HDL`, `Hack`, `Assembler`, `VMTranslator`, `Compiler`, `Jack`, `OS`

---

## Highlighted Projects:

### 0x05

[Hack Computer](./projects/05)

A simple Computer with a CPU (ALU, registers), a Memory (RAM, SCREEN, KEYBOARD), and a ROM (instruction memory) that can run Hack Machine Language.

implemented using HDL. (score: 100/100)

### 0x06 

[HackAssembler](./projects/06)

A simple Assembler for the Hack Computer that can translate Hack Assembly Language to Hack Machine Language.

implemented using C++. (score: 100/100)

Compile command:

```shell 
$ g++ -Wall -O2 -std=gnu++17 HackAssembler.cpp -o HackAssembler 
```

Usage:

```shell
$ ./HackAssembler <input.asm>
```

### 0x07 & 0x08

[VMTranslator](./projects/08)

A simple VM Translator for the Hack Computer that can translate VM Language to Hack Assembly Language.

implemented using C++. (score: 100/100)

Compile command:

```shell
$ make
# can clean the .o files using:
$ make clean
```

Usage:

```shell
$ ./VMTranslator <input.vm>
```

## Testing

use the .sh files in ./tools.

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