// player.hpp

#include <unit.hpp> 

#ifndef PLAYER_HPP
#define PLAYER_HPP

class player {
    friend void phase(player , player &, float) ; 
    private: 
        string name ; 
        vector<unit> army ; // Vecteur des unités. 
        float t_atk, t_def, t_pdf, t_pdc, t_arm ; // Total des points. 

        bool unit_bool = 0 , batiment_bool = 0 , personnages_bool = 0, QG_bool = 0 ;  // Indique la configuration de l'armée. 
        // (false | 0 ) = vide , (true |  1) = au moins une occurence 
    public: 
        player(string filename, string) ; 
        player(string, string, int, float, float, float, float, float) ;
        player(int) ;  

        string getName() const ; 

        // Used to fetch points from army. 

        float getTotPdf() const ; 
        float getTotPdc() const ; 
        float getTotAtk() const ; 
        float getSubPoints(int type) const ; // Return the Atk + Pdf + Pdc from a type of uni (batiment/ personnages)
        void  setSub0(int type) ; // Set to 0 all stat from a certain type of unit. 

        bool  getUnitBool() const ; 
        bool  getBatimentBool() const ; 
        bool  getPersonnageBool() const ; 
        bool  getQGBool() const ;   

        float fetch_def(int) const ; 
        float fetch_arm(int) const ; 
        float fetch_esq(int) const ; 

        bool  isArmyEmpty() const ; 

        // Manage remaining Pdf / Pdc / Atk pts
        void setUnitsPdf(float f) ; 
        void delPdf(float f) ; 

        void setUnitsPdc(float f) ; 
        void delPdc(float f) ; 

        void setUnitsAtk(float f) ; 
        void delAtk(float f) ; 

        // Set 
        void setName(string s) ; 
        void setLastDef(float f, int) ; 
        void setLastArm(float f, int) ;    

        void setTotalStats() ; 

        void setModifierStats(float pourcentage) ; 

        void setBools() ; 
        
        // Printers

        void printArmy() ; 

        // Deleting and manipulating vectors. 

            // Optionnal ? Probly

        void delUnit(int) ; 
        void addBatiment() ; 
        void addPersonnage() ; 
        void addQG() ; 

        void constructUnit(int) ; 
        void constructBat(int) ; 
        void constructPerso(int) ; 
        void constructQG() ; 
  

} ; 
#endif 