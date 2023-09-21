// units.cpp

#include "unit.hpp" 

    unit::unit(string STR, int TYPE, float ATK, float PDF, float PDC , float DEF ,float ARM, float ESQ) 
    {
        name = STR ; 
        type = TYPE ; 
        pdf = PDF ; 
        pdc = PDC ; 
        atk = ATK ; 
        def = DEF ; 
        arm = ARM ; 
        esquive = ESQ ; 
    }
    
    string unit::getName() const { return name ;}
    int unit::getType() const { return type ; }
    float unit::getAtk() const { return atk ; }
    float unit::getPdf() const { return pdf ; }
    float unit::getPdc() const { return pdc ; }
    float unit::getDef() const { return def ; }
    float unit::getArm() const { return arm ; }
    float unit::getEsq() const{ return esquive;} 

    void unit::setAtk(float X) { atk = X ; }
    void unit::setPdf(float X) { pdf = X ; }
    void unit::setPdc(float X) { pdc = X ; }
    void unit::setDef(float X) { def = X ; }
    void unit::setArm(float X) { arm = X ; }
    void unit::setEsq(float X) { esquive = X ;} 

    void unit::printUnit() const {

        // 0 = unité | 1 = Batiments | 2 = Lieutenant et Personnage principal | 3 = QG. 
        if (type == 0){
            if ((pdf == 0) && (pdc == 0) && (arm == 0)){
            std::cout << "  " << name << atk << " Atk / " << def << " Def + " << esquive << " Esquive.\n" ; 
            }
            else{
            std::cout << "  " << name << atk << " Atk + " << pdf << " Pdf + " << pdc << " Pdc / " << def << " Def + " << arm << " Arm + " << esquive << " Esquive.\n" ; 
            }
        } 
        else if (type == 1 || type == 3){
            if ((pdf == 0) && (pdc == 0) && (arm == 0)){
                std::cout << "  " << name << "(" << atk << " Atk / " << def << " Def).\n" ;
            }
            else
                std::cout << "  " << name << "(" << atk << " Atk + " << pdf << " Pdf + " << pdc << " Pdc / " << def << " Def + " << arm << " Arm + " << esquive << " Esquive.)\n" ; 
        }
        else if (type == 2){
            std::cout << "  " << name << "(" << atk << " Atk + " << pdf << " Pdf + " << pdc << " Pdc / " << def << " Def + " << arm << " Arm + " << esquive << " Esquive.)\n" ; 
        }
        else{
            std::cout << "  " << "Erreur de type avec l'unité, EXIT_FAILURE. \n" ; 
            exit(EXIT_FAILURE) ; 
        }
    }



    
    