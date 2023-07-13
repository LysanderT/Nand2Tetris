#ifndef VMTRANSLATOR_H
#define VMTRANSLATOR_H

#include "Parser.h"
#include "CodeWriter.h"

class VMTranslator
{
public:
    VMTranslator(std::vector<std::string> list, std::string outpath, bool ok):infileList(list),parser(),writer(outpath),bootstrap(ok){};
    ~VMTranslator(){};
    void convert();
    bool whether_to_add_bootstrap(){return bootstrap;}

private:
    std::vector<std::string> infileList;
    Parser parser;
    CodeWriter writer;
    bool bootstrap;
};

#endif // VMTRANSLATOR_H