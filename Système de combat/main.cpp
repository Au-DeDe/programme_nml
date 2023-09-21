#include "unit.hpp" 
#include "player.hpp"

#include <stdexcept>
#include <limits>

using namespace std ; 

bool checkBool(int type_t, player player) {
    switch(type_t) {
        case 0 : 
            return player.getUnitBool() ; 
        break ; 

        case 1 : 
            return player.getBatimentBool() ; 
        break ; 

        case 2 : 
            return player.getPersonnageBool() ; 
        break ; 

        case 3 : 
            return player.getQGBool() ; 
        break ; 

        default : 
            return 0 ; 
    }
}

float phase(player player1, player &player2, float points, int type_t){

    while( (points > 0) && (!(player2.isArmyEmpty())) && checkBool(type_t,player2) ){
        float lastdef = player2.fetch_def(type_t) ; 
        float lastarm = player2.fetch_arm(type_t) ; 
        float esquive = player2.fetch_esq(type_t) ;

        if(esquive > 0){
            int rng_num = (rand() % 100) +1 ; 
            // std::cout << "  esq = " << esquive << " rng_num = " << rng_num << endl ; 
            if (rng_num <= esquive){
                std::cout << "\n  ... ! ESQUIVE ! ..." << endl ; 
                points -= (lastdef + lastarm) ; 
                // On vide juste les points, mais pas touche  l'unité. 
            }
            else{
                if(lastarm > 0) { 
                    if((points - lastarm) >= 0 ){ 
                        points -= lastarm ; 
                        player2.setLastArm(0,type_t) ; 
                        if((points - lastdef) >= 0) {
                            points -= lastdef ; 
                            player2.delUnit(type_t) ; 
                        }
                        else{
                            lastdef -= points; 
                            player2.setLastDef(lastdef,type_t) ; 
                            points = 0 ; 
                        }
                    }
                    else{
                        lastarm -= points ; 
                        player2.setLastArm(lastarm,type_t) ; 
                        points = 0 ; 

                    }
                }
                else{ 
                    if((points - lastdef) >= 0) {
                            points -= lastdef ; 
                            player2.delUnit(type_t) ; 
                    }
                    else{
                            lastdef -= points; 
                            player2.setLastDef(lastdef,type_t) ; 
                            points = 0 ; // Plus de points. 
                    }
                }
            }
        }
        else{ // Pas d'esquive.  
            if(lastarm > 0) { 
                if((points - lastarm) >= 0 ){ 
                    points -= lastarm ; 
                    player2.setLastArm(0,type_t) ; 
                    if((points - lastdef) >= 0) {
                        points -= lastdef ; 
                        player2.delUnit(type_t) ; 
                    }
                    else{
                        lastdef -= points; 
                        player2.setLastDef(lastdef,type_t) ; 
                        points = 0 ; 
                    }
                }
                else{
                    lastarm -= points ; 
                    player2.setLastArm(lastarm,type_t) ; 
                    points = 0 ; 

                }
            }
            else{ 
                if((points - lastdef) >= 0) {
                        points -= lastdef ; 
                        player2.delUnit(type_t) ; 
                }
                else{
                        lastdef -= points; 
                        player2.setLastDef(lastdef,type_t) ; 
                        points = 0 ; // Plus de points. 
                }
            }
        }

    }
    std::cout << "\n" ; 
    //player2.printArmy() ; 
    return points ; 
}

void counterphase(player &p1, player &p2, float points, int type_t){
    float rem_points ; 
    float pointsQg=0, pointsPerso =0 ; 
    while ((points > 0) && (!p2.isArmyEmpty())){ 
    // Si une attaque se vide, ou qu'un vecteur se vide, c'est la fin. 
            if ((points > 0) && (!p2.isArmyEmpty()) && (p2.getUnitBool()) ){ // Si il y'a de la Pdf et qu'il y a des unités : 
                rem_points = phase(p1,p2,points, 0) ; 
                std::cout << "  ... COUNTER -> UNITS (" << p1.getName() << ") (" << points << ") ...  \n" ; 
            }
            else if((points > 0) && (!p2.isArmyEmpty()) && (p2.getQGBool()) ){ // S'il y a de la Pdf et des personnages ; 
                pointsQg = p2.getSubPoints(3); 
                rem_points = phase(p1,p2,points, 3) ; 
                std::cout << "  ... COUNTER -> QG (" << p1.getName() << ") (" << points << ") ... \n" ; 
                // COUNTER PHASE ! 
            }
            else if((points > 0) && (!p2.isArmyEmpty()) && (p2.getPersonnageBool()) ){
                pointsPerso = p2.getSubPoints(2) ; 
                rem_points = phase(p1,p2,points, 2) ; 
                std::cout << "  ... COUNTER -> PERSONNAGES (" << p1.getName() << ") (" << points << ") ... \n" ; 
                // COUNTER PHASE ! 
            }
            else {
                std::cout << "  ... COUNTER no points (" << p1.getName() << ") \n" ; 
        }
        points = rem_points ; 
        }

        p2.setTotalStats() ; 
        p1.setSub0(type_t) ; 
        p1.setTotalStats() ; 

        if(pointsQg > 0){
            std::cout << "\n  ... CONTRE ATTAQUE DU QG (" << p2.getName() << ") ...\n" ;
            counterphase(p2,p1,pointsQg,3); 
                
        } 
        if(pointsPerso > 0){
            std::cout << "\n  ... CONTRE ATTAQUE DES PERSONNAGES (" << p2.getName() << ")  ...\n" ;
            counterphase(p2,p1,pointsPerso,2); 
                
        } 

        // On set en void, car on s'en fout de récupérer les points. Si l'unité se fait toucher elle bazarde ses points. Maintenant go test ! 

}

void combat(player &p1, player &p2){

    // Definitions de variables :
    float rem_pts1 = 0, rem_pts2 = 0, p1pdf = 0, p2pdf = 0, p1pdc = 0, p2pdc = 0, p1atk = 0, p2atk = 0, p1totpts, p2totpts; 

    // -- > Set des stats. 
    p1.setTotalStats() ;  p2.setTotalStats() ; 
    p1pdf = p1.getTotPdf() ;  p2pdf = p2.getTotPdf() ; 
    // -- > 
    std::cout << "\n\033[32m< -- ! DEBUT DU COMBAT : -- >\033[0m\n";
    printf("\n\x1B[35m< -- ! PHASE DE PDF : -- > \033[0m\n");
    
    if ((p1pdf > 0) && (!p2.isArmyEmpty()) && (p2.getUnitBool()) ){ // Si il y'a de la Pdf et qu'il y a des unités : 
        rem_pts1 = phase(p1,p2,p1pdf, 0) ; 
        std::cout << "  ... PDF -> UNITS (" << p1.getName() << ") (" << p1pdf << ") -> (" << rem_pts1 << ") ...  \n" ; 
        }
        else if ((p1pdf > 0) && (!p2.isArmyEmpty()) && (p2.getBatimentBool()) ){ // S'il y a de la Pdf et des batiments 
            float pointsCnt = p2.getSubPoints(1) ;
            rem_pts1 = phase(p1,p2,p1pdf, 1) ; 
            std::cout << "  ... PDF -> BATIMENTS (" << p1.getName() << ") (" << p1pdf << ") -> (" << rem_pts1 << ") ... \n" ; 
            
            if(pointsCnt > 0){
                counterphase(p2,p1,pointsCnt,1); 
                std::cout << "\n  ... CONTRE ATTAQUE DES BATIMENTS (" << p2.getName() << ") ...\n" ;
            }
        }
        else if((p1pdf > 0) && (!p2.isArmyEmpty()) && (p2.getQGBool()) ){ 
            float pointsCnt = p2.getSubPoints(3) ; 
            rem_pts1 = phase(p1,p2,p1pdf, 3) ; 
            std::cout << "  ... PDF -> QG (" << p1.getName() << ") (" << p1pdf << ") -> (" << rem_pts1 << ")... \n" ; 

            if(pointsCnt > 0){
                counterphase(p2,p1,pointsCnt,3); 
                std::cout << "\n  ... CONTRE ATTAQUE DU QG (" << p2.getName() << ") (" << pointsCnt << ")  ...\n" ;
            } 
        }
        else if((p1pdf > 0) && (!p2.isArmyEmpty()) && (p2.getPersonnageBool()) ){
            float pointsCnt = p2.getSubPoints(2) ; 
            rem_pts1 = phase(p1,p2,p1pdf, 2) ; 
            std::cout << "  ... PDF -> PERSONNAGES (" << p1.getName() << ") (" << p1pdf << ") -> (" << rem_pts1 << ") ... \n" ; 
            if(pointsCnt > 0){
                counterphase(p2,p1,pointsCnt,2); 
                std::cout << "\n  ... CONTRE ATTAQUE DES PERSONNAGES (" << p2.getName() << ") (" << pointsCnt << ")  ...\n" ;
            } 
        }
        else {
            std::cout << "\n  ... NO PDF (" << p1.getName() << ")  ... \n" ; 
    }

    if ((p2pdf > 0) && (!p1.isArmyEmpty()) && (p1.getUnitBool())){ 
        rem_pts2 = phase(p2,p1,p2pdf, 0) ; 
        std::cout << "  ... PDF -> UNITS (" << p2.getName() << ") (" << p2pdf << ") -> (" << rem_pts2 << ") ...  \n" ; 
        }
        else if ((p2pdf > 0) && (!p1.isArmyEmpty()) && (p1.getBatimentBool())){ 
            float pointsCnt = p1.getSubPoints(1) ;
            rem_pts2 = phase(p2,p1,p2pdf, 1) ; 
            std::cout << "  ... PDF -> BATIMENTS (" << p2.getName() << ") (" << p2pdf << ") -> (" << rem_pts2 << ") ... \n" ;             
            if(pointsCnt > 0){
                counterphase(p1,p2,pointsCnt,1); 
                std::cout << "\n  ... CONTRE ATTAQUE DES BATIMENTS (" << p1.getName() << ") ...\n" ;
            }
        }
        else if( (p2pdf > 0) && (!p1.isArmyEmpty()) && (p1.getQGBool())){ 
            float pointsCnt = p1.getSubPoints(3) ;
            rem_pts2 = phase(p2,p1,p2pdf, 3) ; 
            std::cout << "  ... PDF -> QG (" << p2.getName() << ") (" << p2pdf << ") -> (" << rem_pts2 << ") ... \n" ; 

            if(pointsCnt > 0){
                counterphase(p2,p1,pointsCnt,3); 
                std::cout << "\n  ... CONTRE ATTAQUE DU QG (" << p1.getName() << ") (" << pointsCnt << ")  ...\n" ;
            }
        }
        else if((p2pdf > 0) && (!p1.isArmyEmpty()) && (p1.getPersonnageBool()) ){
            float pointsCnt = p1.getSubPoints(2) ;
            rem_pts2 = phase(p2,p1,p2pdf, 2) ; 
            std::cout << "\n  ... PDF -> PERSONNAGES (" << p2.getName() << ") (" << p2pdf << ") -> (" << rem_pts2 << ") ... \n" ;

            if(pointsCnt > 0){
                counterphase(p2,p1,pointsCnt,2); 
                std::cout << "\n  ... CONTRE ATTAQUE DES PERSONNAGES (" << p1.getName() << ") (" << pointsCnt << ")  ...\n" ;
            } 
        }
        else {
            std::cout << "\n  ... NO PDF (" << p2.getName() << ") ... \n" ; 
    }

    if(rem_pts1 <= 0){ p1.setUnitsPdf(0) ; } else if(rem_pts1 < p1.getTotPdf()) { p1.delPdf(rem_pts1) ; }
    if(rem_pts2 <= 0){ p2.setUnitsPdf(0) ; } else if(rem_pts2 < p2.getTotPdf()) { p2.delPdf(rem_pts2) ; } 

    printf("\n\x1B[35m< -- ! FIN DE PDF : -- > \033[0m\n");

    p1totpts = p1.getTotPdf() + p1.getTotPdc() + p1.getTotAtk() ; p2totpts = p2.getTotPdf() + p2.getTotPdc() + p2.getTotAtk() ; 
    if((p1.isArmyEmpty() || p2.isArmyEmpty()) || ((p1totpts == 0) && (p2totpts == 0))){
        std::cout << "\n\033[31mFIN DU COMBAT\033[0m\n";
        return ; 
    }

    p1.printArmy() ; p2.printArmy() ; p1.setTotalStats() ; p2.setTotalStats() ; 

    p1pdc = p1.getTotPdf() + p1.getTotPdc() ; p2pdc = p2.getTotPdf() + p2.getTotPdc() ;

    if ((p1pdc > 0) && (!p2.isArmyEmpty()) && (p2.getBatimentBool()) ){  
        printf("\n\x1B[35m< -- ! PHASE DE BATIMENTS : -- > \033[0m\n");

        float pointsBat = p2.getSubPoints(1) ; 
        rem_pts1 = phase(p1,p2,p1pdc, 1) ; 
        std::cout << "  ... PDC -> BATIMENTS (" << p1.getName() << ") (" << p1pdc << ") -> (" << rem_pts1 << ") ...  \n" ; 
        std::cout << "\n  ... CONTRE ATTAQUE DES BATIMENTS (" << p2.getName() << ") (" << pointsBat << ") ...\n" ; 
        counterphase(p2,p1,pointsBat,1);

        if(rem_pts1 <= 0){
            p1.setUnitsPdc(0) ;
            p1.setUnitsPdf(0) ; 
        }
        else if(rem_pts1 < p1.getTotPdc()) {
            p1.delPdc(rem_pts1) ;    
        }
        printf("\n\x1B[35m< -- ! FIN DE BATIMENTS : -- > \033[0m\n");
        p1.printArmy() ; p2.printArmy() ; 
        
    }

    p1totpts = p1.getTotPdf() + p1.getTotPdc() + p1.getTotAtk() ; 
    p2totpts = p2.getTotPdf() + p2.getTotPdc() + p2.getTotAtk() ; 

    if((p1.isArmyEmpty() || p2.isArmyEmpty()) || ((p1totpts == 0) && (p2totpts == 0))){
        std::cout << "\n\033[31mFIN DU COMBAT\033[0m\n";
        return ; 
    }

    printf("\n\x1B[35m< -- ! PHASE DE PDC : -- > \033[0m\n");

    //  < -- ! PHASE DE PDC : -- > 

    p1.setTotalStats() ; 
    p2.setTotalStats() ; 

    p1pdc = p1.getTotPdf() + p1.getTotPdc() ; 
    p2pdc = p2.getTotPdf() + p2.getTotPdc() ;

    if ((p1pdc > 0) && (!p2.isArmyEmpty()) && (p2.getBatimentBool()) ){
        float pointsCnt = p2.getSubPoints(1) ;   
        rem_pts1 = phase(p1,p2,p1pdc, 1) ; 
        std::cout << "  ... PDC -> BATIMENTS (" << p1.getName() << ") (" << p1pdc << ") -> (" << rem_pts1 << ") ...  \n" ; 
        if(pointsCnt > 0){
            counterphase(p2,p1,pointsCnt,1); 
            std::cout << "\n  ... CONTRE ATTAQUE DES BATIMENTS (" << p1.getName() << ") ...\n" ;
        }
    }
    else if ((p1pdc > 0) && (!p2.isArmyEmpty()) && (p2.getUnitBool()) ){ 
        rem_pts1 = phase(p1,p2,p1pdc, 0) ; 
        std::cout << "  ... PDC -> UNITS (" << p1.getName() << ") (" << p1pdc << ") -> (" << rem_pts1 << ") ... \n" ; 
    }
    else if((p1pdc > 0) && (!p2.isArmyEmpty()) && (p2.getQGBool()) ){
        float pointsCnt = p2.getSubPoints(3) ;  
        rem_pts1 = phase(p1,p2,p1pdc, 3) ; 
        std::cout << "  ... PDC -> QG (" << p1.getName() << ") (" << p1pdc << ") -> (" << rem_pts1 << ") ... \n" ; 
        if(pointsCnt > 0){
            counterphase(p2,p1,pointsCnt,3); 
            std::cout << "\n  ... CONTRE ATTAQUE DU QG (" << p2.getName() << ") (" << pointsCnt << ")  ...\n" ;
        } 
    }
    else if((p1pdc > 0) && (!p2.isArmyEmpty()) && (p2.getPersonnageBool()) ){
        float pointsCnt = p2.getSubPoints(2) ; 
        rem_pts1 = phase(p1,p2,p1pdc, 2) ; 
        std::cout << "  ... PDC -> PERSONNAGE (" << p1.getName() << ") (" << p1pdc << ") -> (" << rem_pts1 << ") ... \n" ; 
        if(pointsCnt > 0){
            counterphase(p2,p1,pointsCnt,2); 
            std::cout << "\n  ... CONTRE ATTAQUE DES PERSONNAGES (" << p2.getName() << ") (" << pointsCnt << ")  ...\n" ;
        }     
    }
    else {
        std::cout << "\n  ... NO PDC (" << p1.getName() << ") ... \n" ; 
    }

    // Player 2 turn : 

    if ((p2pdc > 0) && (!p1.isArmyEmpty()) && (p1.getBatimentBool()) ){ 
        float pointsCnt = p1.getSubPoints(1) ;   
        rem_pts2 = phase(p2,p1,p2pdc, 1) ; 
        std::cout << "\n  ... PDC -> BATIMENTS (" << p2.getName() << ") (" << p2pdc << ") -> (" << rem_pts2 << ") ...  \n" ; 
        if(pointsCnt > 0){
            counterphase(p1,p2,pointsCnt,1); 
            std::cout << "\n  ... CONTRE ATTAQUE DES BATIMENTS (" << p1.getName() << ") ...\n" ;
        }
    }
    else if ((p2pdc > 0) && (!p1.isArmyEmpty()) && (p1.getUnitBool()) ){ 
        rem_pts2 = phase(p2,p1,p2pdc, 0) ; 
        std::cout << "\n  ... PDC -> UNIT (" << p2.getName() << ") (" << p2pdc << ") -> (" << rem_pts2 << ") ... \n" ; 
    }
    else if((p2pdc > 0) && (!p1.isArmyEmpty()) && (p1.getQGBool()) ){ 
        float pointsCnt = p1.getSubPoints(3) ; 
        rem_pts2 = phase(p2,p1,p2pdc, 3) ; 
        std::cout << "\n  ... PDC -> QG (" << p2.getName() << ") (" << p2pdc << ") -> (" << rem_pts2 << ")... \n" ; 
        if(pointsCnt > 0){
            counterphase(p1,p2,pointsCnt,3); 
            std::cout << "\n  ... CONTRE ATTAQUE DU QG (" << p1.getName() << ") ...\n" ;
        }
    }
    else if((p2pdc > 0) && (!p1.isArmyEmpty()) && (p1.getPersonnageBool()) ){
        float pointsCnt = p1.getSubPoints(2) ; 
        rem_pts2 = phase(p2,p1,p2pdc, 2) ; 
        std::cout << "\n  ... PDC -> PERSONNAGE (" << p2.getName() << ") (" << p2pdc << ") -> (" << rem_pts2 << ") ... \n" ; 
        if(pointsCnt > 0){
            counterphase(p1,p2,pointsCnt,2); 
            std::cout << "\n  ... CONTRE ATTAQUE DES PERSONNAGES (" << p1.getName() << ") ...\n" ;
        }
    }
    else {
        std::cout << "\n  ... NO PDC (" << p2.getName() << ") ... \n" ; 
    }
    
    if(rem_pts1 <= 0){ // Set remaining points 
            p1.setUnitsPdc(0) ;
            p1.setUnitsPdf(0) ; 
        }
        else if(rem_pts1 < p1.getTotPdc()) {
            p1.delPdc(rem_pts1) ;    
    }

    if(rem_pts2 <= 0){ // Set remaining points
        p2.setUnitsPdc(0) ;
        p2.setUnitsPdf(0) ;  
    }
    else if(rem_pts2 < p2.getTotPdc()) {
        p2.delPdc(rem_pts2) ;    
    }

    p1totpts = p1.getTotPdf() + p1.getTotPdc() + p1.getTotAtk() ; p2totpts = p2.getTotPdf() + p2.getTotPdc() + p2.getTotAtk() ; 

    if((p1.isArmyEmpty() || p2.isArmyEmpty()) || ((p1totpts == 0) && (p2totpts == 0))){
        std::cout << "\n\033[31mFIN DU COMBAT\033[0m\n";
        return ; 
    }

    printf("\n\x1B[35m< -- ! FIN DE PDC : -- > \033[0m\n");

    p1.printArmy() ; p2.printArmy() ; 
     
    printf("\n\x1B[35m< -- ! PHASE D'ATK : -- > \033[0m\n");

    p1.setTotalStats() ; p2.setTotalStats() ; 

    p1atk = p1.getTotPdf() + p1.getTotPdc() + p1.getTotAtk() ; 
    p2atk = p2.getTotPdf() + p2.getTotPdc() + p2.getTotAtk() ; 

    while ((p1atk > 0 || p2atk > 0) && (!p2.isArmyEmpty()) && (!p1.isArmyEmpty())){ // Tant qu'il reste de l'atk en jeu ou que les armée ne sont pas vides. 
    // Si une des attaque se vide, ou qu'un vecteur se vide, c'est la fin. 
        if ((p1atk > 0) && (!p2.isArmyEmpty()) && (p2.getBatimentBool()) ){ // S'il y a de la Pdf et des batiments 
                float pointsCnt = p2.getSubPoints(1) ;   
                rem_pts1 = phase(p1,p2,p1atk, 1) ; 
                std::cout << "  ... ATK -> BATIMENTS (" << p1.getName() << ") (" << p1atk << ") -> (" << rem_pts1 << ") ... \n" ; 
                if(pointsCnt > 0){
                    counterphase(p2,p1,pointsCnt,1); 
                    std::cout << "\n  ... CONTRE ATTAQUE DES BATIMENTS (" << p1.getName() << ") ...\n" ;
                }
            }
            else if ((p1atk > 0) && (!p2.isArmyEmpty()) && (p2.getUnitBool()) ){ // Si il y'a de la Pdf et qu'il y a des unités : 
                rem_pts1 = phase(p1,p2,p1atk, 0) ; 
                std::cout << "  ... ATK -> UNITS (" << p1.getName() << ") (" << p1atk << ") -> (" << rem_pts1 << ") ...  \n" ; 
            }
            else if((p1atk > 0) && (!p2.isArmyEmpty()) && (p2.getQGBool()) ){ // S'il y a de la Pdf et des personnages ; 
                float pointsCnt = p2.getSubPoints(3) ; 
                rem_pts1 = phase(p1,p2,p1atk, 3) ; 
                std::cout << "  ... ATK -> QG (" << p1.getName() << ") (" << p1atk << ") -> (" << rem_pts1 << ") ... \n" ; 
                if(pointsCnt > 0){
                    counterphase(p2,p1,pointsCnt,3); 
                    std::cout << "\n  ... CONTRE ATTAQUE DU QG (" << p2.getName() << ") (" << pointsCnt << ")  ...\n" ;
                } 
            }
            else if((p1atk > 0) && (!p2.isArmyEmpty()) && (p2.getPersonnageBool()) ){
                float pointsCnt = p2.getSubPoints(2) ; 
                rem_pts1 = phase(p1,p2,p1atk, 2) ; 
                std::cout << "  ... ATK -> PERSONNAGES (" << p1.getName() << ") (" << p1atk << ") -> (" << rem_pts1 << ") ... \n" ; 
                if(pointsCnt > 0){
                    counterphase(p2,p1,pointsCnt,2); 
                    std::cout << "\n  ... CONTRE ATTAQUE DES PERSONNAGES (" << p2.getName() << ") (" << pointsCnt << ")  ...\n" ;
                }  
            }
            else {
                std::cout << "  ... NO ATK (P1) ... \n" ; 
        }

        if((p2atk > 0) && (!p1.isArmyEmpty()) && (p1.getBatimentBool()) ){ // S'il y a de la Pdf et des batiments 
                float pointsCnt = p1.getSubPoints(1) ; 
                rem_pts2 = phase(p2,p1,p2atk, 1) ; 
                std::cout << "  ... ATK -> BATIMENTS (" << p2.getName() << ") (" << p2atk << ") -> (" << rem_pts2 << ") ... \n" ; 
                if(pointsCnt > 0){
                    counterphase(p1,p2,pointsCnt,1); 
                    std::cout << "\n  ... CONTRE ATTAQUE DES BATIMENTS (" << p1.getName() << ") ...\n" ;
                }
            }
            else if ((p2atk > 0) && (!p1.isArmyEmpty()) && (p1.getUnitBool()) ){ 
                rem_pts2 = phase(p2,p1,p2atk, 0) ; 
                std::cout << "  ... ATK -> UNITS (" << p2.getName() << ") (" << p2atk << ") -> (" << rem_pts2 << ") ...  \n" ; 
            }
            else if((p2atk > 0) && (!p1.isArmyEmpty()) && (p1.getQGBool()) ){ 
                float pointsCnt = p1.getSubPoints(3) ; 
                rem_pts2 = phase(p2,p1,p2atk, 3) ; 
                std::cout << "  ... ATK -> QG(" << p2.getName() << ") (" << p2atk << ") -> (" << rem_pts2 << ") ... \n" ; 
                if(pointsCnt > 0){
                    counterphase(p1,p2,pointsCnt,3); 
                    std::cout << "\n  ... CONTRE ATTAQUE DU QG (" << p1.getName() << ") ...\n" ;
                }
            }
            else if((p2atk > 0) && (!p1.isArmyEmpty()) && (p1.getPersonnageBool()) ){
                float pointsCnt = p1.getSubPoints(2) ; 
                rem_pts2 = phase(p2,p1,p2atk, 2) ; 
                std::cout << "  ... ATK -> PERSONNAGES (" << p2.getName() << ") (" << p2atk << ") -> (" << rem_pts2 << ") ... \n" ; 
                if(pointsCnt > 0){
                    counterphase(p1,p2,pointsCnt,2); 
                    std::cout << "\n  ... CONTRE ATTAQUE DES PERSONNAGES (" << p1.getName() << ") ...\n" ;
                }
            }
            else {
                std::cout << "  ... NO ATK (" << p2.getName() << ") ... \n" ; 
        }

        p1.setTotalStats() ; p2.setTotalStats() ; 

        if(rem_pts1 <= 0){ // Set remaining points 
                p1.setUnitsAtk(0) ; 
                p1.setUnitsPdc(0) ; 
                p1.setUnitsPdf(0) ; 
                p1.setTotalStats() ; 
                p1atk = p1.getTotPdf() + p1.getTotPdc() + p1.getTotAtk() ; 
            }
            else if(rem_pts1 < p1.getTotAtk()) {
                p1.delAtk(rem_pts1) ;    
                p1.setTotalStats() ; 
                p1atk = p1.getTotPdf() + p1.getTotPdc() + p1.getTotAtk() ; 
        }

        if(rem_pts2 <= 0){ // Set remaining points
            p2.setUnitsAtk(0) ; 
            p2.setUnitsPdc(0) ; 
            p2.setUnitsPdf(0) ; 
            p2.setTotalStats() ; 
            p2atk = p2.getTotPdf() + p2.getTotPdc() + p2.getTotAtk() ; 
            
        }
        else if(rem_pts2 < p2.getTotAtk()) {
            p2.delAtk(rem_pts2) ;    
            p2.setTotalStats() ; 
            p2atk = p2.getTotPdf() + p2.getTotPdc() + p2.getTotAtk() ; 
        }
        p1.printArmy() ; 
        p2.printArmy() ; 
    }

    std::cout << "\n\033[31m< -- ! FIN DU COMBAT -- >\033[0m\n";
    return ;         
}


int main() { 
    srand(time(NULL)); 
    string p1string, p2string, p1name, p2name;
    std::cout << "1ère étape : rentre le nom du fichier dans lequel l'ATTAQUANT se situe, puis son nom." << endl ;
    std::cout << "Exemple : blackmask.txt Arthurvador " << endl ;
    std::cout << "Input : " ; 
    cin >>  p1string >> p1name ; 
    std::cout << "\n" ; 

    cin.clear() ; 
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input  

    player p1(p1string, p1name) ; 

    std::cout << "2ème étape : rentre le nom du fichier dans lequel le DEFENSEUR se situe, puis son nom." << endl ;
    std::cout << "Input : " ; 
    cin >>  p2string >> p2name ; 
    std::cout << "\n" ; 

    cin.clear() ; 
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input  

    player p2(p2string, p2name) ;  

    // player p1("examplecopy.txt", "test1") ; 
    // player p2("example.txt","Test2") ; 

    float a, b ; 
    std::cout << "3ème étape : Bonus/Malus de commandement des joueur. Ex : -25 %\'de stats  +15 % \n" ; 
    std::cout << "Input = (j1 j2) " ; 
    cin >> a >> b ; 

    std::cout << "Le combat est maintenant disponible dans Agnus_dei.txt. \n" ; 

    p1.setModifierStats(a)  ; 
    p2.setModifierStats(b) ; 

    // freopen("Agnus_dei.txt","w",stdout) ; 
    // if(freopen("Agnus_dei.txt", "w", stdout) == NULL) {
    //     fprintf(stderr, "\n\x1B[35m< -- ! Agnus_dei.txt n'existe pas ! -- > \033[0m\n");
    //     exit(1);
    // }

    p1.printArmy() ; 
    p2.printArmy() ; 

    combat(p1,p2) ;

    p1.printArmy() ; 
    p2.printArmy() ; 

    return 0 ; 
}