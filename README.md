# Nand2Tetris

An archive of projects implemented by my self in the course [Nand2Tetris](https://www.nand2tetris.org/).

Key words: `Nand2Tetris`, `HDL`, `Hack`, `Assembler`, `VM`, `Compiler`, `Jack`, `OS`

---

## Certificate

## Highlighted Projects:

### 0x05

Hack Computer. 

A simple Computer with a CPU (ALU, registers), a Memory (RAM, SCREEN, KEYBOARD), and a ROM (instruction memory) that can run Hack Machine Language.

### 0x06

A simple Assembler for the Hack Computer that can translate Hack Assembly Language to Hack Machine Language.

implemented in C++.

Usage:

```shell
./HackAssembler <input.asm>
```

## Testing

use the .sh files in ./tools.

```shell
# e.g.
./tools/HardwareSimulator.sh
```


If your code is right, it will output "End of script - Comparison ended successfully".

Or you can use the following command to compare the difference between two files:

```shell
diff file1 file2
```

this command will compare the difference between file1 and file2. If there is no difference, it will not output anything.

for example in project00:

```shell
diff Mux16.out Mux16.cmp -b 
```

the -b option will ignore the blank space. You can also use -B to ignore the blank line.

## Certificate

&[part1](https://www.coursera.org/account/accomplishments/certificate/FCFZFL9FEVYG)

&[part2]