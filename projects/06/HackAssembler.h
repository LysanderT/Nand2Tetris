#include <fstream>
#include <string>
#include <map>
class HackAssembler {
public:
    HackAssembler(std::string infile,std::string outfile);
    ~HackAssembler();
    void convert();
private:
    enum Type {EMPTY,A_INSTRUCTION,C_INSTRUCTION,L_INSTRUCTION};
    std::map<std::string,std::string> comp = {
        {"0","101010"},
        {"1","111111"},
        {"-1","111010"},
        {"D","001100"},
        {"A","110000"},
        {"M","110000"},
        {"!D","001101"},
        {"!A","110001"},
        {"!M","110001"},
        {"-D","001111"},
        {"-A","110011"},
        {"-M","110011"},
        {"D+1","011111"},
        {"A+1","110111"},
        {"M+1","110111"},
        {"D-1","001110"},
        {"A-1","110010"},
        {"M-1","110010"},
        {"D+A","000010"},
        {"D+M","000010"},
        {"D-A","010011"},
        {"D-M","010011"},
        {"A-D","000111"},
        {"M-D","000111"},
        {"D&A","000000"},
        {"D&M","000000"},
        {"D|A","010101"},
        {"D|M","010101"}
    };
    std::map<std::string,std::string> dest = {
        {""   ,"000"},
        {"M"  ,"001"},
        {"D"  ,"010"},
        {"DM" ,"011"},
        {"MD","011"},
        {"A"  ,"100"},
        {"AM" ,"101"},
        {"MA","101"},
        {"AD","110"},
        {"DA","110"},
        {"ADM","111"},
        {"AMD","111"},
        {"MAD","111"},
        {"MDA","111"},
        {"DAM","111"},
        {"DMA","111"}
    };
    std::map<std::string,std::string> jump = {
        {"","000"},
        {"JGT","001"},
        {"JEQ","010"},
        {"JGE","011"},
        {"JLT","100"},
        {"JNE","101"},
        {"JLE","110"},
        {"JMP","111"}
    };
    std::map<std::string,int> symbol_table = {
        {"SP",0},
        {"LCL",1},
        {"ARG",2},
        {"THIS",3},
        {"THAT",4},
        {"R0",0},
        {"R1",1},
        {"R2",2},
        {"R3",3},
        {"R4",4},
        {"R5",5},
        {"R6",6},
        {"R7",7},
        {"R8",8},
        {"R9",9},
        {"R10",10},
        {"R11",11},
        {"R12",12},
        {"R13",13},
        {"R14",14},
        {"R15",15},
        {"SCREEN",16384},
        {"KBD",24576}
    };
    std::ifstream infile;
    std::ofstream outfile;
    int next_variable_address = 16;
    Type instructionType(std::string);
    std::string removeComments(std::string);
};