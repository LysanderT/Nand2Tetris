#include <iostream>
#include "HackAssembler.h"
using namespace std;

HackAssembler::HackAssembler(string asmfile,string hackfile) {
    infile.open(asmfile);
    outfile.open(hackfile);
}

HackAssembler::~HackAssembler() {
    infile.close();
    outfile.close();
}

HackAssembler::Type HackAssembler::instructionType (string line) {
    if(line[0] == '@'){
        return A_INSTRUCTION;
    }else if(line[0] == '('){
        return L_INSTRUCTION;
    }else if(line.size()>=2 && line[0]=='/' && line[1]=='/'){
        return EMPTY;
    }

    for(int i=0;i<line.length();i++){
        if(line[i]==';' || line[i]=='='){
            return C_INSTRUCTION;
        }
    }

    return EMPTY;
}

string HackAssembler::removeComments(string line0){
    string res;
    for(int i=0;i<line0.size();i++){ // delete all spaces
        if(line0[i]==' '){continue;}
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

void HackAssembler::convert() {
    string line0;
    string line;
    int line_index = 0;
    while(getline(infile,line0)){
        line = removeComments(line0);

        HackAssembler::Type type = instructionType(line);
        if(type==EMPTY){continue;}
        if(type==L_INSTRUCTION){
            string symbol = line.substr(1,line.length()-2);
            symbol_table[symbol]=line_index;
            continue;
        }
        line_index++;
    }

    infile.clear();
    infile.seekg(0,ios::beg);

    while(getline(infile,line0)){

        line = removeComments(line0);

        HackAssembler::Type type = instructionType(line);
        if(type==EMPTY){continue;}

        if(type==A_INSTRUCTION){
            string address = line.substr(1);
            int value;
            if(address[0]>='0' && address[0]<='9'){
                value = stoi(address);
            }
            else if(symbol_table.find(address)!=symbol_table.end()){
                value = symbol_table[address];
            }else{
                symbol_table[address]=next_variable_address;
                value = next_variable_address;
                next_variable_address++;
            }
            string binary = bitset<15>(value).to_string();
            outfile << 0 << binary << endl;
        }else if(type==C_INSTRUCTION){
            string dest_str = "";
            string comp_str = "";
            string jump_str = "";
            int dest_index = line.find('=');
            int jump_index = line.find(';');
            if(dest_index!=-1){
                dest_str = line.substr(0,dest_index);
            }
            if(jump_index!=-1){
                jump_str = line.substr(jump_index+1);
            }
            if(dest_index!=-1 && jump_index!=-1){
                comp_str = line.substr(dest_index+1,jump_index-dest_index-1);
            }else if(jump_index==-1){
                comp_str = line.substr(dest_index+1);
            }else if(dest_index==-1){
                comp_str = line.substr(0,jump_index);
            }else{
                cout << "INVALID C INSTRUCTION" << endl;
            }
            string dest_binary = dest[dest_str];
            string comp_binary = comp[comp_str];
            string jump_binary = jump[jump_str];
            
            int a;
            if(comp_str.find('M')!=-1){
                a=1;
            }else{
                a=0;
            }

            outfile << 111 << a << comp_binary << dest_binary << jump_binary << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "HackAssembler: invalid number of arguments" << endl;
        cout << "Usage: HackAssembler <filename>.asm" << endl;
        return 1;
    }
    string infile(argv[1]);
    int dot_index = infile.find_last_of('.');
    if(dot_index==-1){
        cout << "HackAssembler: invalid filename" << endl;
        cout << "Usage: HackAssembler <filename>.asm" << endl;
        return 1;
    }
    string suffix = infile.substr(dot_index);
    if(suffix!=".asm"){
        cout << "HackAssembler: invalid filename" << endl;
        cout << "Usage: HackAssembler <file>.asm" << endl;
        return 1;
    }
    string outfile = infile.substr(0,dot_index)+".hack";
    HackAssembler assembler(infile,outfile);
    assembler.convert();
    return 0;
}
