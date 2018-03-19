//
//  main.cpp
//  Assembly Project
//
//  Created by Taymour Abdelal on 3/15/18.
//
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include <string>
#include "Formats.hpp"
using namespace std;

struct instWord
{
    string instText;
    unsigned int instMachineCode;
    unsigned int rd, rs1, rs2, funct3, funct7, opcode;
    unsigned int I_imm, S_imm, B_imm, U_imm, J_imm;
    
};

int regs[32]={0};
unsigned int pc = 0x0;

char memory[8*1024];    // 8KB of memory located at address 0

void emitError(char *s)
{
    cout << s;
    exit(0);
}

void printPrefix(unsigned int instA, unsigned int instCode)
{
    cout << "0x" << hex << std::setfill('0') << std::setw(8) << instA << "\t0x" << hex << std::setw(8) << instCode;
}
string toBinStr(unsigned int val)
{
    // mask has only the leftmost bit set.
    unsigned int mask = 1u << (std::numeric_limits<unsigned>::digits-1) ;
    
    // skip leading bits that are not set.
    while ( 0 == (val & mask) && mask != 0 )
        mask >>= 1 ; // shift all bits to the right by 1
    
    string binStr ;
    binStr.reserve(std::numeric_limits<unsigned>::digits+1) ;
    
    do
    {
        // add a '1' or '0' depending the current bit.
        binStr += static_cast<char>(val & mask) + '0' ;
        
    } while ( (mask>>=1) != 0 ) ; // next bit, when mask is 0 we've processed all bits
    
    return binStr ;
}
string format ( string funct)
{
    ifstream input;
    input.open("refrencecard.txt");
        string operand ,type ;
    if(input.is_open())
    {
        while (input.eof())
        {
            if (operand == funct)
            {
              
                if (type == "R")
                return type;
            }
            
        }
    }
    
    return "\n";
}
//void createMachineCode (Formats code){
//
//    while (!code.refrenceInput.eof())
//    {
//
//    }
//
//
//}
void parse (Formats code , string s) // Function-Parse
{

    string funct , rs, rd ,rt;
    string type;
    
   funct =  s.substr(0 , s.find(' '));
    s.erase(0 , s.find(' '));
    code.type = format(funct);
    
    if (code.type == "R")
    {
    

    code.rcode.rd= s.substr(0 ,s.find(','));
    s.erase(0 , s.find(',')+1);
    
    
    code.rcode.rs1= s.substr(0 ,s.find(','));
    s.erase(0 , s.find(',')+1);
        
    code.rcode.rs2 = s.substr(0 ,s.size());

    
    }
   
        
    
        
    
    
    
//
//
//    cout << funct << endl;
//
//
//    rd.erase(0,1);
//    rs.erase(0,2);
//    if ((rs != "") && (rt !="") && (rd != ""))
//    {
//    W.opcode = 000000;
//    W.rs1 = stoi(rs);
//    W.rd = stoi(rd);
//    W.rs2 = stoi(rt);
    
    
    
    
    //instmachinecode (W  ,funct , rs , rd ,rt);
    
    
}

void instAssembleExec(instWord&inst)
{
 
    //Generate instruction machine code is hexdecimal

    
    //execute instruction
    if(inst.opcode == 0x33)// R Instructions
    {
        switch(inst.funct3)
        {
            case 0:
                if(inst.funct7 == 32)
                    regs[inst.rd] = regs[inst.rs1] - regs[inst.rs2];
                else
                    regs[inst.rd] = regs[inst.rs1] + regs[inst.rs2];
                break;
            default:
                cout << "\tUnknown R Instruction \n";
        }
    }
    else
    {
        cout << "\tUnknown Instruction \n";
    }
    
}

int main()
{
    ifstream inFile , refrence;
    Formats formatcode;
    ofstream outFile;
    instWord W;
    string input;
   
    
    inFile.open("mult.txt");
    refrence.open("refrencecard.txt");
    if(inFile.is_open())
    {
        pc = 0x0;
        while(!inFile.eof())
        {
            getline (inFile, input);
            
            parse(formatcode, input);        //parse instText into its instruction format fields
            instAssembleExec(W);   //Generate instruction machine code and execute instruction
            printPrefix(pc, W.instMachineCode);

            pc += 4;
        }
        
        inFile.close();
        
        // print out the registers values now
        for(int i = 0; i < 32; i++)
            cout << "x" << dec << i << ": \t"<< "0x" << hex << std::setfill('0') << std::setw(8) << regs[i] << "\n";
    }
    else
        emitError("Cannot access input file\n");
}


