# Note

## HDL  

In this course, rightmost bit is the MSB, while leftmost bit is LSB, which is a confusing convention.

see [textbook](./materials/the-elements-of-computing-systems-building-a-modern-computer-from-first-principles-2nbsped-2020002671-9780262539807_compress.pdf)

## Hack Machine Code & Assembly Code

1. The A-instruction '@xxx' has 3 effects: 
   - set the A register to the value of the symbol xxx or decimal xxx
   - set the M register to RAM[A] (attention: M is not a register, but a special symbol that **always** refers to the RAM[A])
   - set the ROM register whose address is xxx to the selected instruction
2. Combine the C-instruction 'dest=comp;jump' with the A-instruction '@xxx' to form a complete instruction. The reason why 'jump' can jump to the instruction whose address is xxx is that the A-instruction '@xxx' will set the ROM register whose address is xxx to the selected instruction, and then the C-instruction 'jump' will jump to that instruction.

## VM Language

1. Different files should have different static fields, so that they won't interfere with each other.
2. The RAM segments symbols are just like the pointers in C/C++: you need to specify whether address of the segment, and then you can access the value stored in that address.
3. To implement the function logic, the stack is used to store the return address, and to save the LCL, ARG, THIS, and THAT pointers of the caller function. The stack is also used to store the local variables and the arguments of the callee function.
4. VM Language is a upper level abstraction of Hack Assembly Language, and the following table shows the relationship between them and the Hack Computer:


| Hack Computer | Hack Machine & Assembly |  VM Language |
| :----------: | :-----------: | :----------: |
| RAM |   registers, symbols   |  stack, memory segments |
| ALU |  ALU instructions  |  arithmetic & logical instructions|
| ROM | jump instructions |  program flow |
| Stack (RAM[256-2047]) |  - |  function call & return |