#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <vector>

class Parser
{
private:
    std::ifstream infile;
    std::vector<std::string> curr;
public:
    enum ctype{C_FALSE,C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL};
    ctype type;
    Parser(){};
    ~Parser();
    bool hasMoreLines();
    void open(std::string);
    std::vector<std::string> split(const std::string&, const std::string&); 
    std::string removeComments(std::string line0);

    bool advance();
    ctype commandType();
    std::string arg1();
    std::string arg2();
};

#endif // PARSER_H