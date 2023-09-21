// unit.hpp
#ifndef UNITS_HPP
#define UNITS_HPP

#include <iostream>
#include <vector>
#include <string> 
#include <cstdio>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std ; 

class unit{
    friend class player ; 
    private: 
        string name ; 
        int number ; 
        float atk, pdf, pdc, def, arm, esquive ; 

        int type ; // 0 = unité | 1 = Batiments | 2 = Lieutenant et Personnage principal | 3 = QG. 


    public: 

        unit(string, int, float, float, float, float, float, float) ; 
        
        string getName() const ; 
        int getType() const ; 
        float getAtk() const ; 
        float getPdf() const ; 
        float getPdc() const ; 
        float getArm() const ; 
        float getDef() const ; 
        float getEsq() const ; 

        void setAtk(float X) ; 
        void setPdf(float X) ; 
        void setPdc(float X) ;  
        void setArm(float X) ; 
        void setDef(float X) ; 
        void setEsq(float X) ; 
        
        void printUnit() const ; 

} ; 

#endif
