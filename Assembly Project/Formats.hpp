//
//  Formats.hpp
//  Assembly Project
//
//  Created by Taymour Abdelal on 3/19/18.
//

#ifndef Formats_hpp
#define Formats_hpp

#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

class Formats{
    
    public:
    
    
    
    //ifstream refrenceInput;

    
    
    struct Rformat {
       
    string rd , rs1 , rs2 , funct3 , funct7, opcode;
        
    };
    
    Rformat rcode;
    
    struct Jformat {
        
    };
    
    struct Iformat{
        
    };
    
    string type;
    
    Formats ();
    
};

#endif /* Formats_hpp */
