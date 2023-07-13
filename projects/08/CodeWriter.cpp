#include "CodeWriter.h"
#include <string>

CodeWriter::CodeWriter(std::string path){
    outfile.open(path);
    path = path.substr(0,path.size()-3);
    int slash_index = path.rfind("/");
    if(slash_index!=-1){
        staticLabel = path.substr(slash_index+1);
    }else{
        staticLabel = path;
    }
};
CodeWriter::~CodeWriter(){
    outfile.close();
};
void CodeWriter::setStaticField(std::string field){
    staticLabel = field;
}
void CodeWriter::writeArithmetic(std::string command){
    // 0 represent true, -1 represent false
    outfile << "// "+command << std::endl;
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
    outfile << std::endl;
}
void CodeWriter::writePushPop(std::string command, std::string segment, std::string index){
    outfile << "//" << command << segment << index << std::endl;
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
    outfile << std::endl;
}

void CodeWriter::writeLabel(std::string label){
    outfile << "//" << label << std::endl;
    outfile << "("+label+")" << std::endl;
}

void CodeWriter::writeGoTo(std::string label){
    outfile << "// goto " << label << std::endl;

    outfile << "@"+label << std::endl;
    outfile << "0;JMP" << std::endl;

    outfile << std::endl;
}

void CodeWriter::writeIf(std::string label){
    outfile << "// if-goto" << label << std::endl;

    outfile << "@SP" << std::endl;
    outfile << "AM=M-1" << std::endl;
    outfile << "D=M" << std::endl;
    outfile << "@"+label << std::endl;
    outfile << "D;JNE" << std::endl;

    outfile << std::endl;
}

void CodeWriter::writeFunction(std::string functionName, int nVars){
    outfile << "// function" << functionName << nVars << std::endl;
    writeLabel(functionName);
    for(int i=0; i<nVars; i++){
        // push 0
        outfile << "@SP" << std::endl;
        outfile << "A=M" << std::endl;
        outfile << "M=0" << std::endl;
        outfile << "@SP" << std::endl;
        outfile << "M=M+1" << std::endl;
    }
    outfile << std::endl;
}

void CodeWriter::saveCaller(std::string symbol){
    outfile << "@"+symbol << std::endl;
    outfile << "D=M" << std::endl;
    outfile << "@SP" << std::endl;
    outfile << "A=M" << std::endl;
    outfile << "M=D" << std::endl;
    outfile << "@SP" << std::endl;
    outfile << "M=M+1" << std::endl;
}

void CodeWriter::writeCall(std::string functionName, int nArgs){
    outfile << "// call" << functionName << nArgs << std::endl;

    std::string returnAddr = "func_"+std::to_string(addr_i);
    writePushPop("push","constant",returnAddr);
    saveCaller("LCL");
    saveCaller("ARG");
    saveCaller("THIS");
    saveCaller("THAT");

    // ARG=SP-5-nArgs
    outfile << "@5" << std::endl;
    outfile << "D=A" << std::endl;
    outfile << "@"+std::to_string(nArgs) << std::endl;
    outfile << "D=D+A" << std::endl;
    outfile << "@SP" << std::endl;
    outfile << "D=M-D" << std::endl;
    outfile << "@ARG" << std::endl;
    outfile << "M=D" << std::endl;
    // LCL=SP
    outfile << "@SP" << std::endl;
    outfile << "D=M" << std::endl;
    outfile << "@LCL" << std::endl;
    outfile << "M=D" << std::endl;

    writeGoTo(functionName);
    writeLabel(returnAddr);

    addr_i++;
    outfile << std::endl;
}

void CodeWriter::writeReturn(){
    outfile << "// return" << std::endl;
    // endFrame = LCL
    outfile << "@LCL" << std::endl;
    outfile << "D=M" << std::endl;
    outfile << "@R15" << std::endl;
    outfile << "M=D" << std::endl;
    // retAddr = *(endFrame-5)
    outfile << "@5" << std::endl;
    outfile << "A=D-A" << std::endl;
    outfile << "D=M" << std::endl;
    outfile << "@R14" << std::endl;
    outfile << "M=D" << std::endl;
    // *ARG = pop()
    outfile << "@SP" << std::endl;
    outfile << "AM=M-1" << std::endl;
    outfile << "D=M" << std::endl;
    outfile << "@ARG" << std::endl;
    outfile << "A=M" << std::endl;
    outfile << "M=D" << std::endl;
    // SP = ARG+1
    outfile << "@ARG" << std::endl;
    outfile << "D=M+1" << std::endl;
    outfile << "@SP" << std::endl;
    outfile << "M=D" << std::endl;
    // THAT = *(engFrame-1)
    outfile << "@R15" << std::endl;
    outfile << "A=M-1" << std::endl;
    outfile << "D=M" << std::endl;
    outfile << "@THAT" << std::endl;
    outfile << "M=D" << std::endl;
    // THIS = *(endFrame-2)
    outfile << "@2" << std::endl;
    outfile << "D=A" << std::endl;
    outfile << "@R15" << std::endl;
    outfile << "A=M-D" << std::endl;
    outfile << "D=M" << std::endl;
    outfile << "@THIS" << std::endl;
    outfile << "M=D" << std::endl;
    // ARG = *(endFrame-3)
    outfile << "@3" << std::endl;
    outfile << "D=A" << std::endl;
    outfile << "@R15" << std::endl;
    outfile << "A=M-D" << std::endl;
    outfile << "D=M" << std::endl;
    outfile << "@ARG" << std::endl;
    outfile << "M=D" << std::endl;
    // LCL = *(endFrame-4)
    outfile << "@4" << std::endl;
    outfile << "D=A" << std::endl;
    outfile << "@R15" << std::endl;
    outfile << "A=M-D" << std::endl;
    outfile << "D=M" << std::endl;
    outfile << "@LCL" << std::endl;
    outfile << "M=D" << std::endl;
    // goto retAddr
    outfile << "@R14" << std::endl;
    outfile << "A=M" << std::endl;
    outfile << "0;JMP" << std::endl;
    
    outfile << std::endl;
}

void CodeWriter::writeEnd(){
    outfile << "(end)" << std::endl;
    outfile << "@end" << std::endl;
    outfile << "0;JMP" << std::endl;
}

void CodeWriter::writeBootstrap(){
    outfile << "// bootstrap" << std::endl;
    outfile << "@256" << std::endl;
    outfile << "D=A" << std::endl;
    outfile << "@SP" << std::endl;
    outfile << "M=D" << std::endl;

    outfile << "@1" << std::endl;
    outfile << "D=A" << std::endl;
    outfile << "@LCL" << std::endl;
    outfile << "M=D" << std::endl;
    outfile << "@2" << std::endl;
    outfile << "D=A" << std::endl;
    outfile << "@ARG" << std::endl;
    outfile << "M=D" << std::endl;
    outfile << "@3" << std::endl;
    outfile << "D=A" << std::endl;
    outfile << "@THIS" << std::endl;
    outfile << "M=D" << std::endl;
    outfile << "@4" << std::endl;
    outfile << "D=A" << std::endl;
    outfile << "@THAT" << std::endl;
    outfile << "M=D" << std::endl;

    writeCall("Sys.init",0);
    outfile << std::endl;
}