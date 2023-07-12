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
public:
    CodeWriter(std::string);
    ~CodeWriter();
    void writeArithmetic(std::string);
    void writePushPop(std::string,std::string,std::string);
    void writeEnd();
};