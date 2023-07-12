#include "Parser.h"
#include "CodeWriter.h"

using namespace std;

class VMTranslator
{
public:
    VMTranslator(string inpath, string outpath):parser(inpath),writer(outpath){};
    ~VMTranslator(){};
    void convert();

private:
    Parser parser;
    CodeWriter writer;
};


