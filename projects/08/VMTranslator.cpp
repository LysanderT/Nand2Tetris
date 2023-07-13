#include <iostream>
#include <dirent.h>
#include <cstring>
#include "VMTranslator.h"

using namespace std;
// g++ -Wall -O2 -std=gnu++17 -g -o VMTranslator VMTranslator.cpp -I .
void VMTranslator::convert(){
    if(whether_to_add_bootstrap()){
        writer.writeBootstrap();
    }
    for(auto path: infileList){
        parser.open(path);
        int slash_index = path.rfind('/');
        int dot_index = path.rfind('.');
        string field = path.substr(slash_index+1,dot_index-slash_index-1);
        writer.setStaticField(field);
        while(parser.hasMoreLines()){
            bool ok = parser.advance();
            if(!ok){continue;}
            if(parser.commandType() == Parser::C_ARITHMETIC){
                writer.writeArithmetic(parser.arg1());
            }else if(parser.commandType()==Parser::C_PUSH || parser.commandType()==Parser::C_POP){
                string pp = parser.commandType()==Parser::C_PUSH?"push":"pop";
                writer.writePushPop(pp, parser.arg1(), parser.arg2());
            }else if(parser.commandType()==Parser::C_LABEL){
                writer.writeLabel(parser.arg2());
            }else if(parser.commandType()==Parser::C_GOTO){
                writer.writeGoTo(parser.arg2());
            }else if(parser.commandType()==Parser::C_IF){
                writer.writeIf(parser.arg2());
            }else if(parser.commandType()==Parser::C_FUNCTION){
                writer.writeFunction(parser.arg1(), std::stoi(parser.arg2()));
            }else if(parser.commandType()==Parser::C_CALL){
                writer.writeCall(parser.arg1(),std::stoi(parser.arg2()));
            }else if(parser.commandType()==Parser::C_RETURN){
                writer.writeReturn();
            }
        }
    }
    if(whether_to_add_bootstrap()){
        writer.writeEnd();
    }
}

vector<string> getVMFilesList(string dirpath){
    DIR *dir = opendir(dirpath.c_str());
    if (dir == NULL)
    {
        cout << "opendir error" << endl;
    }
    vector<string> allPath;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR){//It's dir
            // if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            //     continue;
            // string dirNew = dirpath + "/" + entry->d_name;
            // vector<string> tempPath = getVMFilesList(dirNew);
            // allPath.insert(allPath.end(), tempPath.begin(), tempPath.end());
            continue; // do not access subdir

        }else {
            //cout << "name = " << entry->d_name << ", len = " << entry->d_reclen << ", entry->d_type = " << (int)entry->d_type << endl;
            string name = entry->d_name;
            if(name.size()>=3 && name.substr(name.size()-3)!=".vm"){
                continue;
            }
            string imgdir = dirpath +"/"+ name;
            //sprintf("%s",imgdir.c_str());
            allPath.push_back(imgdir);
        }
    }
    closedir(dir);
    //system("pause");
    return allPath;
}


int main(int argc, char* argv[]){
    if (argc != 2) {
        cout << "VMTranslator: invalid number of arguments (should be 1)" << endl;
        cout << "Usage: ./VMTranslator <fileName.vm>" << endl;
        cout << "   or: ./VMTranslator <dirName>" << endl;
        return 1;
    }
    vector<string> infileList;
    string resultPath;
    string inpath(argv[1]);
    bool ok;

    int slash_index = inpath.rfind('/');
    if(slash_index == -1){
        inpath = "./"+inpath;
        slash_index = 1;
    }

    int vm_index = inpath.rfind(".vm");
    if(vm_index == -1 || vm_index+3<inpath.size()){ // Dir or other extension
        infileList = getVMFilesList(inpath);
        if(infileList.size()==0){
            cout << "VMTranslator: invalid directory name or invalid extension of (included) file";
            cout << "Usage: ./VMTranslator <fileName.vm>" << endl;
            cout << "   or: ./VMTranslator <dirName>" << endl;
            return 1;
        }
        resultPath = inpath + inpath.substr(slash_index) + ".asm";
        ok = true;
    }else{ // .vm File
        // string suffix = inpath.substr(dot_index);
        // if(suffix!=".vm"){
        //     cout << "VMTranslator: invalid extension of file (should be .vm)" << endl;
        //     cout << "Usage: ./VMTranslator <fileName.vm>" << endl;
        //     cout << "   or: ./VMTranslator <dirName>" << endl;
        //     return 1;
        // }else{
            infileList.push_back(inpath);
            resultPath = inpath.substr(0,vm_index) + ".asm";
            ok = false;
        // }
    }

    VMTranslator translator(infileList,resultPath,ok);
    translator.convert();
    return 0;
}