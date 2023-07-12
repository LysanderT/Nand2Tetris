#include <iostream>
#include "VMTranslator.h"

using namespace std;
// g++ -Wall -O2 -std=gnu++17 -g -o VMTranslator VMTranslator.cpp -I .
void VMTranslator::convert(){
    while(parser.hasMoreLines()){
        bool ok = parser.advance();
        if(!ok){continue;}
        if(parser.commandType() == Parser::C_ARITHMETIC){
            writer.writeArithmetic(parser.arg1());
        }else if(parser.commandType()==Parser::C_PUSH || parser.commandType()==Parser::C_POP){
            string pp = parser.commandType()==Parser::C_PUSH?"push":"pop";
            writer.writePushPop(pp, parser.arg1(), parser.arg2());
        }
    }
    writer.writeEnd();
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        cout << "VMTranslator: invalid number of arguments" << endl;
        cout << "Usage: VMTranslator <filename>.vm" << endl;
        return 1;
    }
    string inpath(argv[1]);
    int dot_index = inpath.find_last_of('.');
    if(dot_index==-1){
        cout << "VMTranslator: invalid filename" << endl;
        cout << "Usage: VMTranslator <filename>.vm" << endl;
        return 1;
    }
    string suffix = inpath.substr(dot_index);
    if(suffix!=".vm"){
        cout << "VMTranslator: invalid filename" << endl;
        cout << "Usage: VMTranslator <file>.vm" << endl;
        return 1;
    }
    string outpath = inpath.substr(0,dot_index);
    VMTranslator translator(inpath,outpath);
    translator.convert();
    return 0;
}