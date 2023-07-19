# Notes

## HDL  

In this course, rightmost bit is the MSB, while leftmost bit is LSB, which is a confusing convention.

For more details about HDL, see [textbook](./materials/the-elements-of-computing-systems-building-a-modern-computer-from-first-principles-2nbsped-2020002671-9780262539807_compress.pdf)

Actually HDL isn't some language between machine code and assembly. It's just a way to describe the hardware. The HDL code will be translated into circuit that tell hardware how to behave, while machine code is the binary series that tell the hardware what to do.

## Hack Machine Code & Assembly Code

1. The A-instruction '@xxx' has 3 effects: 
   - set the A register to the value of the symbol xxx or decimal xxx
   - set the M register to RAM[A] (attention: M is not a register, but a special symbol that **always** refers to the RAM[A])
   - set the ROM register whose address is xxx to the selected instruction
2. Combine the C-instruction 'dest=comp;jump' with the A-instruction '@xxx' to form a complete instruction. The reason why 'jump' can jump to the instruction whose address is xxx is that the A-instruction '@xxx' will set the ROM register whose address is xxx to the selected instruction, and then the C-instruction 'jump' will jump to that instruction.
3. The L-insturction '(xxx)' is used to define a symbol xxx, and the symbol xxx will be set to the address of the next instruction, and then be used in the A-instruction '@xxx' and the C-instruction 'dest=comp;jump'. One important thing to note is that we need to first loop the whole file to execute all the L-instructions, i.e. to map all the symbols to their addresses. Only after that can we execute the A-instruction and C-instruction normally.
4. There doesn't exist essential difference between the Hack Machine Code and the Hack Assembly Code. The Hack Assembly Code is just a more readable version of the Hack Machine Code. One line of Hack machine code can be translated into one line of Hack Assembly Code. For example, the Hack Machine Code `0000000000000000` can be translated into the Hack Assembly Code `@0`.

## VM Language

1. Different files should have different static fields, so that they won't interfere with each other.
2. The RAM segments symbols are just like the pointers in C/C++: you need to specify whether address of the segment, and then you can access the value stored in that address.
3. To implement the function logic, the stack is used to store the return address, and to save the LCL, ARG, THIS, and THAT pointers of the caller function. The stack is also used to store the local variables and the arguments of the callee function.
4. VM Language is a upper level abstraction of Hack Assembly Language & Machine Language, and the following table shows the relationship between them and the Hack Computer:

| Hack Computer | Hack Machine & Assembly |  VM Language |
| :----------: | :-----------: | :----------: |
| RAM |   registers, symbols   |  stack, memory segments |
| ALU |  ALU instructions  |  arithmetic & logical instructions|
| ROM | jump instructions |  program flow |
| Stack (RAM[256-2047]) |  - |  function call & return |

5. The ARG segment is used to store the arguments of the callee function. However, it's located in the caller function's memory space, since the caller function needs to pass the arguments to the callee function. Similarly, the caller's ARG is stored in the caller's caller function's memory space, and so on. When the callee returns, the caller function will pop its saved ARG from the stack, which points to the memory space of the caller's caller function.
6. The LCL segment is used to store the local variables of the callee function, which is at the bottom of the callee function's memory space.