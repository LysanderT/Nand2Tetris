#include "Parser.h"
#include <cstring>

Parser::~Parser(){
    if(infile.is_open()){
        infile.close();
    }
};
bool Parser::hasMoreLines(){
    if(!infile.is_open()){
        return false;
    }
    return infile.peek()!=EOF;
};
void Parser::open(std::string path){
    if(infile.is_open()){
        infile.close();
    }
    infile.open(path);
}
std::vector<std::string> Parser::split(const std::string& str, const std::string& delim = " ") {
    std::vector<std::string> res;
    if("" == str) return res;
    //先将要切割的字符串从std::string类型转换为char*类型
    char * strs = new char[str.length() + 1] ; //不要忘了
    strcpy(strs, str.c_str()); 

    char * d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while(p) {
        std::string s = p; //分割得到的字符串转换为std::string类型
        res.push_back(s); //存入结果数组
        p = strtok(NULL, d);
    }
    return res;
}
std::string Parser::removeComments(std::string line0){
    std::string res;
    for(int i=0;i<line0.size();i++){ // delete comments
        if(line0[i]=='/' && i+1<line0.size() && line0[i+1]=='/'){break;}
        res+=line0[i];
    }
    size_t pos = res.rfind('\n'); // delete \n and \r at the end of the line
    if (pos != std::string::npos) {
        res.erase(pos, 1);
    }
    pos = res.rfind('\r');
    if (pos != std::string::npos) {
        res.erase(pos, 1);
    }
    return res;
}

bool Parser::advance(){
    std::string command;
    getline(infile,command);
    command = removeComments(command);
    // split
    curr = split(command);
    if(curr.size()==0){return false;}
    std::string first = curr[0];
    if(first=="add"||first=="sub"||first=="neg"||first=="eq"||first=="gt"||first=="lt"||first=="and"||first=="or"||first=="not"){
        type = C_ARITHMETIC;
    }else if(first=="pop"){
        type = C_POP;
    }else if(first=="push"){
        type=C_PUSH;
    }else if(first=="label"){
        type = C_LABEL;
    }else if(first=="goto"){
        type = C_GOTO;
    }else if(first=="if-goto"){
        type = C_IF;
    }else if(first=="function"){
        type = C_FUNCTION;
    }else if(first=="call"){
        type = C_CALL;
    }else if(first=="return"){
        type = C_RETURN;
    }else{
        type = C_FALSE;
    }
    return true;
};
Parser::ctype Parser::commandType(){
    return type;
}
std::string Parser::arg1(){
    if(type==C_ARITHMETIC || type==C_GOTO || type==C_IF || type==C_LABEL){
        return curr[0];
    }else if(type==C_RETURN){
        return "ERROR";
    }else{
        return curr[1];
    }
}
std::string Parser::arg2(){
    if(type==C_PUSH||type==C_POP||type==C_FUNCTION||type==C_CALL){
        return curr[2];
    }else if(type==C_IF || type==C_GOTO || type == C_LABEL){
        return curr[1];
    }else{ // e.g. C_ARITHMETIC
        return "ERROR";
    }
}
