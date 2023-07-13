#ifndef CODEWRITER_H
#define CODEWRITER_H

#include <fstream>
#include <string>
#include <unordered_map>

class CodeWriter
{
private:
    std::ofstream outfile;
    std::unordered_map<std::string,std::string> base = 
    {
        {"local","LCL"},
        {"argument","ARG"},
        {"this","THIS"},
        {"that","THAT"}
//        {"temp","TEMP"}
    };
    std::string staticLabel;
    int eq_i = 0;
    int gt_i = 0;
    int lt_i = 0;
    int addr_i = 0;
    void saveCaller(std::string);

public:
    CodeWriter(std::string);
    ~CodeWriter();
    void writeBootstrap();
    void writeArithmetic(std::string);
    void writePushPop(std::string,std::string,std::string);
    void writeLabel(std::string);
    void writeGoTo(std::string);
    void writeIf(std::string);
    void writeFunction(std::string,int);
    void writeCall(std::string,int);
    void writeReturn();
    void writeEnd();
    void setStaticField(std::string);
};

#endif // CODEWRITER_H