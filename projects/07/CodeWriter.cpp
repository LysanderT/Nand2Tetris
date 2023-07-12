#include "CodeWriter.h"

CodeWriter::CodeWriter(std::string path){
    outfile.open(path+".asm");
    int slash_index = path.rfind("/");
    if(slash_index!=-1){
        staticLabel = path.substr(slash_index+1)+".";
    }else{staticLabel = path+".";}
};
CodeWriter::~CodeWriter(){
    outfile.close();
};
void CodeWriter::writeArithmetic(std::string command){
    // 0 represent true, -1 represent false
    if(command=="add"){
        outfile << "@SP" << std::endl;
        outfile << "AM=M-1" << std::endl;
        outfile << "D=M" << std::endl;
        outfile << "A=A-1" << std::endl;
        outfile << "M=M+D" << std::endl;
    }else if(command=="sub"){
        outfile << "@SP" << std::endl;
        outfile << "AM=M-1" << std::endl;
        outfile << "D=M" << std::endl;
        outfile << "A=A-1" << std::endl;
        outfile << "M=M-D" << std::endl;
    }else if(command=="neg"){
        outfile << "@SP" << std::endl;
        outfile << "A=M-1" << std::endl;
        outfile << "M=-M" << std::endl;
    }else if(command == "eq"){
        // -1 represent true; 0 represent false;
        outfile << "@SP" << std::endl;
        outfile << "AM=M-1" << std::endl;
        outfile << "D=M" << std::endl;
        outfile << "A=A-1" << std::endl;
        outfile << "D=M-D" << std::endl; 
        outfile << "M=-1" << std::endl; // eq
        outfile << "@eq_"+std::to_string(eq_i) << std::endl;
        outfile << "D;JEQ" << std::endl;
        outfile << "@SP" << std::endl; // eq
        outfile << "A=M-1" << std::endl;
        outfile << "M=0" << std::endl; // not eq
        outfile << "(eq_"+std::to_string(eq_i)+")" << std::endl;
        eq_i++;
    }else if(command == "gt"){
        outfile << "@SP" << std::endl;
        outfile << "AM=M-1" << std::endl;
        outfile << "D=M" << std::endl;
        outfile << "A=A-1" << std::endl;
        outfile << "D=M-D" << std::endl;
        outfile << "M=-1" << std::endl; // gt
        outfile << "@gt_"+std::to_string(gt_i) << std::endl;
        outfile << "D;JGT" << std::endl;
        outfile << "@SP" << std::endl; 
        outfile << "A=M-1" << std::endl;
        outfile << "M=0" << std::endl; // not gt
        outfile << "(gt_"+std::to_string(gt_i)+")" << std::endl;
        gt_i++;
    }else if(command == "lt"){
        outfile << "@SP" << std::endl;
        outfile << "AM=M-1" << std::endl;
        outfile << "D=M" << std::endl;
        outfile << "A=A-1" << std::endl;
        outfile << "D=M-D" << std::endl;
        outfile << "M=-1" << std::endl; // lt
        outfile << "@lt_"+std::to_string(lt_i) << std::endl;
        outfile << "D;JLT" << std::endl;
        outfile << "@SP" << std::endl; 
        outfile << "A=M-1" << std::endl;
        outfile << "M=0" << std::endl; // not lt
        outfile << "(lt_"+std::to_string(lt_i)+")" << std::endl;
        lt_i++;
    }else if(command == "and"){
        outfile << "@SP" << std::endl;
        outfile << "AM=M-1" << std::endl;
        outfile << "D=M" << std::endl;
        outfile << "A=A-1" << std::endl;
        outfile << "M=M&D" << std::endl;
    }else if(command == "or"){
        outfile << "@SP" << std::endl;
        outfile << "AM=M-1" << std::endl;
        outfile << "D=M" << std::endl;
        outfile << "A=A-1" << std::endl;
        outfile << "M=M|D" << std::endl;
    }else if(command == "not"){
        outfile << "@SP" << std::endl;
        outfile << "A=M-1" << std::endl;
        outfile << "M=!M" << std::endl;
    }
}
void CodeWriter::writePushPop(std::string command, std::string segment, std::string index){
    if(command=="push"){
        if(segment=="constant"){
            outfile << "@"+index << std::endl;
            outfile << "D=A" << std::endl;
        }
        else if(segment=="pointer"){
            outfile << "@"+index << std::endl;
            outfile << "D=A" << std::endl;
            outfile << "@3" << std::endl;
            outfile << "A=A+D" << std::endl;
            outfile << "D=M" << std::endl;
        }
        else if(segment=="static"){
            outfile << "@"+staticLabel+index << std::endl;
            outfile << "D=M" << std::endl;
        }
        else if(base.count(segment)){
            outfile << "@"+index << std::endl;
            outfile << "D=A" << std::endl;
            outfile << "@"+base[segment] << std::endl;
            outfile << "A=M+D" << std::endl;
            outfile << "D=M" << std::endl;
        }else if(segment == "temp"){
            outfile << "@5" << std::endl;
            outfile << "D=A" << std::endl;
            outfile << "@"+index << std::endl;
            outfile << "A=A+D" << std::endl;
            outfile << "D=M" << std::endl;
        }else{
            //error
        }
        // RAM[SP++]=D;
        outfile << "@SP" << std::endl;
        outfile << "A=M" << std::endl; // A: sp(address RAM[0])->M: address of stacktop                outfile << "A=M" << std::endl;
        outfile << "M=D" << std::endl;  // ->M:value of stacktop
        outfile << "@SP" << std::endl;
        outfile << "M=M+1" << std::endl;
    }else{ // pop
        if(segment=="pointer"){
            outfile << "@"+index << std::endl;
            outfile << "D=A" << std::endl;
            outfile << "@3" << std::endl;
            outfile << "D=A+D" << std::endl;
        }
        else if(segment=="static"){
            outfile << "@"+staticLabel+index << std::endl;
            outfile << "D=A" << std::endl;
        }
        else if(base.count(segment)){
            outfile << "@"+index << std::endl;
            outfile << "D=A" << std::endl;
            outfile << "@"+base[segment] << std::endl;
            outfile << "D=M+D" << std::endl;
        }else if(segment == "temp"){
            outfile << "@5" << std::endl;
            outfile << "D=A" << std::endl;
            outfile << "@"+index << std::endl;
            outfile << "D=A+D" << std::endl;
        }else{
            //error
        }
        outfile << "@R15" << std::endl;
        outfile << "M=D" << std::endl;

        outfile << "@SP" << std::endl;
        outfile << "AM=M-1" << std::endl; // D = RAM[--SP]
        outfile << "D=M" << std::endl;
        outfile << "@R15" << std::endl;
        outfile << "A=M" << std::endl;
        outfile << "M=D" << std::endl;
    }
}
void CodeWriter::writeEnd(){
    outfile << "(end)" << std::endl;
    outfile << "@end" << std::endl;
    outfile << "0;JMP" << std::endl;
}