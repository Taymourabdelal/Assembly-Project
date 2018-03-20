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


string BinToHex(string s) // bin to hex fn
{
     string binToHex = "0x";
for(int i = 0; i < 32; i+=4)
{
   string tmp = "0000";
   
        tmp = s.substr(i,4);
        if      (tmp == ("0000")) binToHex += "0";
                else if (tmp == ("0001")) binToHex = binToHex + "1";
                else if (tmp == ("0010")) binToHex += "2";
                else if (tmp == ("0011")) binToHex += "3";
                else if (tmp == ("0100")) binToHex += "4";
                else if (tmp == ("0101")) binToHex += "5";
                else if (tmp == ("0110")) binToHex += "6";
                else if (tmp == ("0111")) binToHex += "7";
                else if (tmp == ("1000")) binToHex += "8";
                else if (tmp == ("1001")) binToHex += "9";
                else if (tmp == ("1010")) binToHex += "A";
                else if (tmp == ("1011")) binToHex += "B";
                else if (tmp == ("1100")) binToHex += "C";
                else if (tmp == ("1101")) binToHex += "D";
                else if (tmp == ("1110")) binToHex += "E";
                else if (tmp == ("1111")) binToHex += "F";
                                else continue;

    }

    return binToHex;
}
struct instWord
{
    string instText;
    unsigned int instMachineCode;
    unsigned int rd, rs1, rs2, funct3, funct7, opcode;
    unsigned int I_imm, S_imm, B_imm, U_imm, J_imm;
    
};

int regs[32]={0};
unsigned int pc = 0x0;

char memory[8*1024];    // 8KB of memory located at address 00

void emitError(char *s)
{
    cout << s;
    exit(0);
}

void printPrefix(unsigned int instA, unsigned int instCode)
{
    cout << "0x" << hex << std::setfill('0') << std::setw(8) << instA << "\t0x" << hex << std::setw(8) << instCode;
}

string removeExtras(string s)
{
    for (int i = 0 ; i < s.size() ; i++)
    {
        if( s[i] == 'x' || s[i] == '/r')
        {
            s.erase(i, 1);
        }
    }
    
    return s;
}

string paddingRegisters(string s)
{   int  max = s.size();
    if ( s.length() < 5)
        {
            for (int i = 0; i < 5 - max ; i ++)
                {
                    s = "0"+s;
                }
        }
    
    return s;
}

string toBinStr(int n)
{
    int binaryNumber = 0;
    int remainder, i = 1;
    
    while (n!=0)
    {
        remainder = n%2;
                n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    return to_string(binaryNumber);
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
//        get the opcode , funct
//    }
//
//
//}
string parse (Formats code , string &  s) // Function-Parse
{

    string funct , rs, rd ,rt;
    string type;
    
   funct =  s.substr(0 , s.find(' '));
    s.erase(0 , s.find(' '));
    
    return funct;
    //code.type = format(funct);
    
//    if (code.type == "R")
//    {
//
//
//    rs1 = s.substr(0 ,s.find(','));
//    s.erase(0 , s.find(',')+1);
//
//
//    code.rcode.rs1= s.substr(0 ,s.find(','));
//    s.erase(0 , s.find(',')+1);
//
//    code.rcode.rs2 = s.substr(0 ,s.size());
//
//
//    }
   
        
    
        
    
    
    
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
string machinecode (string s ,string input) //machinecode
{
    string opcode ,zero = "0";
    string funct3 , funct7 ,machinecode ,rs1 , rs2, rd;
    if( s == "add")
    {
        opcode = "0110011";
        funct3 ="000";
        funct7 = "0000000";
        
        rd = input.substr(0 ,input.find(','));
           input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
            input.erase(0 , input.find(',')+1);
        
        rs2 = input.substr(0 ,input.size());
        
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] + regs[stoi(rs2)];
        
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters(rs2);
          rs1 = paddingRegisters(rs1);
          rd = paddingRegisters(rd);
        
         machinecode = funct7 + rs2+ rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    
    else if ( s == "sub")
    {
         opcode = "0110011";
        funct7 =  "0100000";
        funct3 = "000";
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2 = input.substr(0 ,input.size());
        
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] - regs[stoi(rs2)];
        
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters(rs2);
        rs1 = paddingRegisters(rs1);
        rd = paddingRegisters(rd);
        
        machinecode = funct7 + rs2+ rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
        
        
        
    }
    
    return machinecode;
}

int main()
{
    ifstream inFile , refrence;
    Formats formatcode;
    ofstream outFile;
    instWord W;
    string input;
    string funct;
   
    
    inFile.open("mult.txt");
    refrence.open("refrencecard.txt");
    if(inFile.is_open())
    {
        pc = 0x0;
        while(!inFile.eof())
        {
            getline (inFile, input);
            
            funct = parse(formatcode, input);
           string machinecodes = machinecode (funct, input);//parse instText into its instruction format fields
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


