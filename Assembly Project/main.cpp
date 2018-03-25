
//  main.cpp
//  Assembly Project
//
//

#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include <string>
#include <math.h>
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
        if( s[i] == 'x' || s[i] == '\r')
        {
            s.erase(i, 1);
        }
    }
    
    return s;
}

string paddingRegisters_R(string s) //r type
{
    int  max = s.size();
    if ( s.length() < 5)
    {
        for (int i = 0; i < 5 - max ; i ++)
        {
            s = "0"+s;
        }
    }
    
    return s;
}

string findTwoscomplement(string str)
{
    int n = str.length();
    
    // Traverse the string to get first '1' from
    // the last of string
    int i;
    for (i = n ; i >= 0 ; i--)
        if (str[i] == '1')
            break;
    
    // If there exists no '1' concat 1 at the
    // starting of string
    if (i == 0)
        return '1' + str;
    
    // Continue traversal after the position of
    // first '1'
    for (int k = i-1 ; k >= 0; k--)
    {
        //Just flip the values
        if (str[k] == '1')
            str[k] = '0';
        else
            str[k] = '1';
    }
    
    // return the modified string
    return str;;
}


string paddingRegisters_I(string s) //r type
{
    int  max = s.size();
       if ( s.length() < 12)
    {
        for (int i = 0; i < 12 - max ; i ++)
        {
            s = "0"+s;
        }
    }
    
    
    
    return s;
}

string paddingRegisters_Ineg(string s) //r type
{
    int  max = s.length();
    if ( s.length() < 12)
    {
        for (int i = 0; i < 12 - max ; i ++)
        {
            s = "1"+s;
        }
    }
    
    
    
    return s;
}

string paddingRegisters_lui(string s) //r type
{   int  max = s.size();
    if ( s.length() < 20)
    {
        for (int i = 0; i < 20 - max ; i ++)
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
string toBinStr_I(int n)
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
        binaryNumber= binaryNumber ^ 0;
        
        
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
    //dd
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
    string funct3 , funct7 ,machinecode ,rs1 , rs2, rd, I_imm;
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
        
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 10 ;
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] + regs[stoi(rs2)];
        
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters_R(rs2);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        

        
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
        
        rs2 = paddingRegisters_R(rs2);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = funct7 + rs2+ rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
        
        
        
    }
    else if ( s == "sll")
    {
        regs [3] = 4;
        regs[9] = 2;
        regs[10] = 2 ;
        opcode = "0110011";
        funct7 =  "0000000";
        funct3 = "001";
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2 = input.substr(0 ,input.size());
        
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] << regs[stoi(rs2)];
        
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters_R(rs2);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = funct7 + rs2+ rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "sltu")
    {
        opcode = "0110011";
        funct7 =  "0000000";
        funct3 = "010";
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2 = input.substr(0 ,input.size());
        
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        if(regs[stoi(rs1)] < regs[stoi(rs2)])
            regs[stoi(rd)] = 1;
        else
            regs[stoi(rd)] = 0;
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters_R(rs2);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = funct7 + rs2+ rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "slt")
    {
        regs [8] = -3;
        regs[9] = 2;
        regs[10] = 10 ;
        opcode = "0110011";
        funct7 =  "0000000";
        funct3 = "011";
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2 = input.substr(0 ,input.size());
        
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        if(regs[stoi(rs1)] < regs[stoi(rs2)])
            regs[stoi(rd)] = 1;
        else
            regs[stoi(rd)] = 0;
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters_R(rs2);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = funct7 + rs2+ rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
 

    else if ( s == "xor")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 10 ;
        opcode = "0110011";
        funct7 =  "0000000";
        funct3 = "100";
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2 = input.substr(0 ,input.size());
        
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] ^ regs[stoi(rs2)];
        
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters_R(rs2);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = funct7 + rs2+ rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "and")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 10 ;
        opcode = "0110011";
        funct7 =  "0000000";
        funct3 = "111";
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2 = input.substr(0 ,input.size());
        
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] & regs[stoi(rs2)];
        
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters_R(rs2);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = funct7 + rs2+ rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "or")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 10 ;
        opcode = "0110011";
        funct7 =  "0000000";
        funct3 = "110";
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2 = input.substr(0 ,input.size());
        
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] | regs[stoi(rs2)];
        
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters_R(rs2);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = funct7 + rs2+ rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "srl")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0110011";
        funct7 =  "0000000";
        funct3 = "101";
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2 = input.substr(0 ,input.size());
        
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] >> regs[stoi(rs2)];
        
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters_R(rs2);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = funct7 + rs2+ rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "sra") // check sign bit;
    {
 
        regs [8] = 2;
        regs[9] = -16;
        regs[10] = 2 ;
        opcode = "0110011";
        funct7 =  "0100000";
        funct3 = "101";
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2 = input.substr(0 ,input.size());
        
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);

            regs[stoi(rd)] = regs[stoi(rs1)] >> regs[stoi(rs2)];
    
               
        
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters_R(rs2);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = funct7 + rs2+ rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "srai") // check sign bit;
    {
        
        regs [8] = 2;
        regs[9] = -16;
        regs[10] = 2 ;
        opcode = "0010011";
        funct7 =  "0100000";
        funct3 = "101";
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2 = input.substr(0 ,input.size());
        
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] >> stoi(rs2);
        
        
        
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters_R(rs2);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = funct7 + rs2+ rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    

    
    else if ( s == "addi")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0010011";
        funct3 = "000";
        
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] + stoi(I_imm);
        
        if(stoi(I_imm)<0)
        {   I_imm=I_imm.substr(1,I_imm.length());
            I_imm = toBinStr_I(stoi(I_imm));
            I_imm= findTwoscomplement(I_imm);
            I_imm=paddingRegisters_Ineg(I_imm);
        }
        else
        {
            I_imm = toBinStr_I(stoi(I_imm));
            I_imm = paddingRegisters_I(I_imm);
        }

               rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        

        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }

    
    else if ( s == "slti")////////////slti////////////////
    {
        regs [8] = -3;
        regs[9] = 4;
        regs[10] = 2 ;
        opcode = "0010011";
        funct3 = "010";

        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
            
        if(regs[stoi(rs1)] < stoi(I_imm))
            regs[stoi(rd)] = 1;
        else
            regs[stoi(rd)] = 0;
        
        if(stoi(I_imm)<0)
        {   I_imm=I_imm.substr(1,I_imm.length());
            I_imm = toBinStr_I(stoi(I_imm));
            I_imm= findTwoscomplement(I_imm);
            I_imm=paddingRegisters_Ineg(I_imm);
        }
        else
        {
        I_imm = toBinStr_I(stoi(I_imm));
             I_imm = paddingRegisters_I(I_imm);
        }
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
       
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
        
    }
    else if ( s == "sltiu")////////////sltiu////////////////
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0010011";
        funct3 = "011";
        
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        if(regs[stoi(rs1)] < stoi(I_imm))
            regs[stoi(rd)] = 1;
        else
            regs[stoi(rd)] = 0;
        
        I_imm = toBinStr(stoi(I_imm));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }

    else if ( s == "ori") /////////////// ori//////////
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0010011";
        funct3 = "110";
        
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] | stoi(I_imm);
        
        if(stoi(I_imm)<0)
        {   I_imm=I_imm.substr(1,I_imm.length());
            I_imm = toBinStr_I(stoi(I_imm));
            I_imm= findTwoscomplement(I_imm);
            I_imm=paddingRegisters_Ineg(I_imm);
        }
        else
        {
            I_imm = toBinStr_I(stoi(I_imm));
            I_imm = paddingRegisters_I(I_imm);
        }

        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }

    else if ( s == "xori")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0010011";
        funct3 = "100";
        
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] ^ stoi(I_imm);
        
        if(stoi(I_imm)<0)
        {   I_imm=I_imm.substr(1,I_imm.length());
            I_imm = toBinStr_I(stoi(I_imm));
            I_imm= findTwoscomplement(I_imm);
            I_imm=paddingRegisters_Ineg(I_imm);
        }
        else
        {
            I_imm = toBinStr_I(stoi(I_imm));
            I_imm = paddingRegisters_I(I_imm);
        }
;
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "andi")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0010011";
        funct3 = "111";
        
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] & stoi(I_imm);
        
        if(stoi(I_imm)<0)
        {   I_imm=I_imm.substr(1,I_imm.length());
            I_imm = toBinStr_I(stoi(I_imm));
            I_imm= findTwoscomplement(I_imm);
            I_imm=paddingRegisters_Ineg(I_imm);
        }
        else
        {
            I_imm = toBinStr_I(stoi(I_imm));
            I_imm = paddingRegisters_I(I_imm);
        }

        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "slli")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0010011";
        funct3 = "001";
        
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2 = input.substr(0 ,input.size());
        
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] << stoi(rs2);
        
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters_R(rs2);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "srli")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0010011";
        funct3 = "101";
        
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs1= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2 = input.substr(0 ,input.size());
        
        rs2 = removeExtras(rs2);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = regs[stoi(rs1)] >> stoi(rs2);
        
        rs2 = toBinStr(stoi(rs2));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        rs2 = paddingRegisters_R(rs2);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "lui")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0110111";
        
        
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
      
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = stoi(I_imm) << 16;

        
        I_imm = toBinStr(stoi(I_imm));
        rd = toBinStr(stoi(rd));
        
    
        I_imm = paddingRegisters_lui(I_imm);
        
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "auipc")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0010111";
        
        
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
        
        rd = removeExtras(rd);
        
        regs[stoi(rd)] = (stoi(I_imm) +pc)<<16;
        
        I_imm = toBinStr(stoi(I_imm));
        rd = toBinStr(stoi(rd));
        
        
        I_imm = paddingRegisters_lui(I_imm);
        
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "lw")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0000011";
        funct3 = "010";
        int add =0;
        string x;
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.find('('));
         input.erase(0 , input.find('(')+1);
        
        rs1= input.substr(0 ,input.find(')'));
       
        
        
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        add=regs[stoi(rs1)]+stoi(I_imm);
        x= to_string(memory[add])+to_string(memory[add+1])+to_string(memory[add+2])+to_string(memory[add+3]);
        
        regs[stoi(rd)] = stoi(x);
        
        I_imm = toBinStr(stoi(I_imm));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "lh")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0000011";
        funct3 = "001";
        int add =0;
        string x;
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.find('('));
        input.erase(0 , input.find('(')+1);
        
        rs1= input.substr(0 ,input.find(')'));
        
        
        
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        add=regs[stoi(rs1)]+stoi(I_imm);
        x= to_string(memory[add])+to_string(memory[add+1]);
        regs[stoi(rd)] = stoi(x);
        
        I_imm = toBinStr(stoi(I_imm));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "lhu")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0000011";
        funct3 = "101";
        int add =0;
        string x;
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.find('('));
        input.erase(0 , input.find('(')+1);
        
        rs1= input.substr(0 ,input.find(')'));
        
        
        
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        
        add=regs[stoi(rs1)]+stoi(I_imm);
        
        x= to_string(memory[add])+to_string(memory[add+1]);
        regs[stoi(rd)] = stoi(x);
        
        I_imm = toBinStr(stoi(I_imm));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }

    else if ( s == "lbu")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0000011";
        funct3 = "100";
        int add =0;
        string x;
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.find('('));
        input.erase(0 , input.find('(')+1);
        
        rs1= input.substr(0 ,input.find(')'));
        
        
        
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        add= regs[stoi(rs1)]+stoi(I_imm);
        x=  to_string(memory[add]);
       
        regs[stoi(rd)] = stoi(x);
        
        I_imm = toBinStr(stoi(I_imm));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    
    else if ( s == "lb")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0000011";
        funct3 = "000";
        int add =0;
        
        rd = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.find('('));
        input.erase(0 , input.find('(')+1);
        
        rs1= input.substr(0 ,input.find(')'));
        
        
        
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rd = removeExtras(rd);
        add=pc+stoi(I_imm);
        regs[stoi(rd)] = memory[add];
        
        I_imm = toBinStr(stoi(I_imm));
        rd = toBinStr(stoi(rd));
        rs1 = toBinStr(stoi(rs1));
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rd = paddingRegisters_R(rd);
        
        machinecode = I_imm + rs1 + funct3 + rd + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    

    
    else if ( s == "sw")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0100011";
        funct3 = "010";
        int add=0;
        string imm1 ,imm2;
        rs2 = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        
        
        
        I_imm = input.substr(0 ,input.find('('));
        input.erase(0 , input.find('(')+1);
        
        rs1= input.substr(0 ,input.find(')'));
        
        
        
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rs2 = removeExtras(rs2);
        add = pc+stoi(I_imm);
        memory[stoi(rs2)] = regs[add];
        
        I_imm = toBinStr(stoi(I_imm));
        rs2 = toBinStr(stoi(rs2));
        rs1 = toBinStr(stoi(rs1));
        
      
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rs2 = paddingRegisters_R(rs2);
        imm1= I_imm.substr(0,4);
        imm2= I_imm.substr(4,7);
        machinecode = imm2 + rs2 + rs1 + funct3 + imm1 + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    
    else if ( s == "sb")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0100011";
        funct3 = "000";
        int add=0;
        string imm1 ,imm2;
        
        rs2 = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        
        
        
        I_imm = input.substr(0 ,input.find('('));
        input.erase(0 , input.find('(')+1);
        
        rs1= input.substr(0 ,input.find(')'));
        
        
        
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rs2 = removeExtras(rs2);
        add = pc+stoi(I_imm);
        memory[stoi(rs2)] = regs[add];
        
        I_imm = toBinStr(stoi(I_imm));
        rs2 = toBinStr(stoi(rs2));
        rs1 = toBinStr(stoi(rs1));
        
        
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rs2 = paddingRegisters_R(rs2);
        imm1= I_imm.substr(0,4);
        imm2= I_imm.substr(4,7);
        machinecode = imm2 + rs2 + rs1 + funct3 + imm1 + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
   
    else if ( s == "sh")
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "0100011";
        funct3 = "000";
        int add=0;
        string imm1 ,imm2;
        
        rs2 = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        
        
        
        I_imm = input.substr(0 ,input.find('('));
        input.erase(0 , input.find('(')+1);
        
        rs1= input.substr(0 ,input.find(')'));
        
        
        
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rs2 = removeExtras(rs2);
        add = pc+stoi(I_imm);
        
        memory[stoi(rs2)] = regs[add];
        
        I_imm = toBinStr(stoi(I_imm));
        rs2 = toBinStr(stoi(rs2));
        rs1 = toBinStr(stoi(rs1));
        
        
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rs2 = paddingRegisters_R(rs2);
        imm1= I_imm.substr(0,4);
        imm2= I_imm.substr(4,7);
        machinecode = imm2 + rs2 + rs1 + funct3 + imm1 + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    else if ( s == "beq") /////////////// ori//////////
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "1100011";
        funct3 = "000";
        string imm1,imm2;
        
        
        rs1 = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rs2 = removeExtras(rs2);
        
         if(regs[stoi(rs1)]==regs[stoi(rs2)])
             pc=stoi(I_imm);
             
        
        I_imm = toBinStr(stoi(I_imm));
        rs2 = toBinStr(stoi(rs2));
        rs1 = toBinStr(stoi(rs1));
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rs2 = paddingRegisters_R(rs2);
        
        imm1=I_imm.at(11)+I_imm.substr(5,6);
        imm2 =I_imm.substr(1,4)+I_imm.at(10);
        
        machinecode = imm1 + rs2 + rs1 + funct3 + imm2 + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }

    else if ( s == "bne") /////////////// ori//////////
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "1100011";
        funct3 = "001";
        string imm1,imm2;
        
        rs1 = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rs2 = removeExtras(rs2);
        
        if(regs[stoi(rs1)]!=regs[stoi(rs2)])
            pc=stoi(I_imm);
        
        
        I_imm = toBinStr(stoi(I_imm));
        rs1 = toBinStr(stoi(rs1));
        rs2 = toBinStr(stoi(rs2));
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rs2 = paddingRegisters_R(rs2);
        imm1=I_imm.at(11)+I_imm.substr(5,6);
        imm2 =I_imm.substr(1,4)+I_imm.at(10);
        
        machinecode = imm1 + rs2 + rs1 + funct3 + imm2 + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    
    else if ( s == "bltu") /////////////// ori//////////
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "1100011";
        funct3 = "110";
        string imm1,imm2;
        
        rs1 = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rs2 = removeExtras(rs2);
        
        if(regs[stoi(rs1)]<regs[stoi(rs2)])
            pc=stoi(I_imm);
        
        
        I_imm = toBinStr(stoi(I_imm));
        rs1 = toBinStr(stoi(rs1));
        rs2 = toBinStr(stoi(rs2));
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rs2 = paddingRegisters_R(rs2);
        imm1=I_imm.at(11)+I_imm.substr(5,6);
        imm2 =I_imm.substr(1,4)+I_imm.at(10);
        
        machinecode = imm1 + rs2 + rs1 + funct3 + imm2 + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    
    else if ( s == "blt") /////////////// ori//////////
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "1100011";
        funct3 = "100";
        string imm1,imm2;
        
        rs1 = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rs2 = removeExtras(rs2);
        
        if(regs[stoi(rs1)]<regs[stoi(rs2)])
            pc=stoi(I_imm);
        
        
        I_imm = toBinStr(stoi(I_imm));
        rs1 = toBinStr(stoi(rs1));
        rs2 = toBinStr(stoi(rs2));
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rs2 = paddingRegisters_R(rs2);
        imm1=I_imm.at(11)+I_imm.substr(5,6);
        imm2 =I_imm.substr(1,4)+I_imm.at(10);
        
        machinecode = imm1 + rs2 + rs1 + funct3 + imm2 + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }

    
    else if ( s == "bge") /////////////// ori//////////
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "1100011";
        funct3 = "101";
        string imm1,imm2;
        
        rs1 = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rs2 = removeExtras(rs2);
        
        if(regs[stoi(rs1)]>=regs[stoi(rs2)])
            pc=stoi(I_imm);
        
        
        I_imm = toBinStr(stoi(I_imm));
        rs1 = toBinStr(stoi(rs1));
        rs2 = toBinStr(stoi(rs2));
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rs2 = paddingRegisters_R(rs2);
        imm1=I_imm.at(11)+I_imm.substr(5,6);
        imm2 =I_imm.substr(1,4)+I_imm.at(10);
        
        machinecode = imm1 + rs2 + rs1 + funct3 + imm2 + opcode;
        
        cout << endl << machinecode<<endl;
        
        cout << BinToHex(machinecode)<<endl;
    }
    
    else if ( s == "bgeu") /////////////// ori//////////
    {
        regs [8] = 10;
        regs[9] = 5;
        regs[10] = 2 ;
        opcode = "1100011";
        funct3 = "111";
        string imm1,imm2;
        
        rs1 = input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        rs2= input.substr(0 ,input.find(','));
        input.erase(0 , input.find(',')+1);
        
        I_imm = input.substr(0 ,input.size());
        
        I_imm = removeExtras(I_imm);
        rs1 = removeExtras(rs1);
        rs2 = removeExtras(rs2);
        
        if(regs[stoi(rs1)]>=regs[stoi(rs2)])
            pc=stoi(I_imm);
        
        
        I_imm = toBinStr(stoi(I_imm));
        rs1 = toBinStr(stoi(rs1));
        rs2 = toBinStr(stoi(rs2));
        
        I_imm = paddingRegisters_I(I_imm);
        rs1 = paddingRegisters_R(rs1);
        rs2 = paddingRegisters_R(rs2);
        imm1=I_imm.at(11)+I_imm.substr(5,6);
        imm2 =I_imm.substr(1,4)+I_imm.at(10);
        
        machinecode = imm1 + rs2 + rs1 + funct3 + imm2 + opcode;
        
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
    
    
    inFile.open("/Users/Aly/Desktop/Assembly project/Assembly-Project/Assembly Project/mult.txt");
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


