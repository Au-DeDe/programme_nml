#include "player.hpp"

player::player(string filename, string name_p){
    name = name_p ; 
    string nb_to_read ; 
    string ignore, type, u_name, atk_s, pdf_s, pdc_s, def_s, arm_s, esquive_s ; 
    float atk, pdf, pdc, def, arm, esquive ; 
    int type_t ; 
    ifstream myfile ; 
    myfile.open(filename) ; 
    if(!myfile) {
        fprintf(stderr,"\n\x1B[35m< -- ! Un des fichiers n'est pas bon : -- > \033[0m\n");
        exit(EXIT_FAILURE) ; 
    }

    getline(myfile,nb_to_read, '\n') ; 
    int nb_to_iterate = stoi(nb_to_read) ; 
    //cout << "Nombre d'unité à lire = " << nb_to_iterate << " " << endl ; 

    for(int i = 0 ; i < nb_to_iterate ; i++) {
        getline(myfile, ignore, '(') ; 
        getline(myfile, type, ')') ; 
        getline(myfile, u_name, '/') ; 
        getline(myfile, ignore, ' ') ; 
        getline(myfile, atk_s , ' ') ; 
        getline(myfile, ignore, '+') ; getline(myfile, ignore, ' ') ; 
        getline(myfile, pdf_s , ' ') ; 
        getline(myfile, ignore, '+') ; getline(myfile, ignore, ' ') ; 
        getline(myfile, pdc_s , ' ') ; 
        getline(myfile, ignore, '/') ; getline(myfile, ignore, ' ') ; 
        getline(myfile, def_s , ' ') ; 
        getline(myfile, ignore, '+') ; getline(myfile, ignore, ' ') ; 
        getline(myfile, arm_s , ' ') ; 
        getline(myfile, ignore, '+') ; getline(myfile, ignore, ' ') ; 
        getline(myfile, esquive_s , ' ') ;  
        getline(myfile, ignore, '\n') ; 

        // //cout << "Ignored char : " << ignore << endl ; 
        // cout << " Type : " << type << endl ; 
        // cout << " Name : " << u_name << endl ; 
        // cout << " Atk : " << atk_s << endl ; 
        // cout << " Pdf : " << pdf_s << endl ; 
        // cout << " Pdc : " << pdc_s << endl ; 
        // cout << " Def : " << def_s << endl ; 
        // cout << " Arm : " << arm_s << endl ; 
        // cout << " Esquive : " << esquive_s << endl << endl ; 
        
        type_t = stoi(type) ;
        atk = stof(atk_s) ; 
        pdf = stof(pdf_s) ;
        pdc = stof(pdc_s) ;
        def = stof(def_s) ;
        arm = stof(arm_s) ;
        esquive = stof(esquive_s) ;
        army.push_back(unit(u_name,type_t,atk,pdf,pdc,def,arm,esquive)) ; 
    }
    myfile.close(); 
    }
    
    // player::player(string s, string un, int N, float A, float F, float C, float D, float AR){
    //         name = s ; 
    //         t_atk = t_def = t_pdf = t_pdc = t_arm = 0 ; 
    //         for(int i = 1 ; i < N+1 ; i++){
    //             army.push_back(unit(un, 0, A, F, C, D, AR,)) ;
    //         }
    // }

    // player::player(int intel) {
    //     string player_name ; 
    //     cout << "Quel est le nom du Joueur ? : " ; 
    //     // cin.clear() ; 
    //     // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input   
    //     getline(cin, player_name);
    //     stringstream ss(player_name) ; 
    //     name = player_name ; 

    //     int nb_diff_unit = 0, nb_bat  = 0, nb_perso  = 0, qg = 0 ; 
    //     cout << "\n Bonjour, je suis le constructeur d'armée. Je vais avoir besoin de collecter quelques informations !!" ; 
    //     cout << "\n Tout d'abord indique le nombre d'unités (différentes) Par exemple s'il y a 20 unités avec des kalash, et 80 à poil, indique 2." ; 
    //     cout << "\n Ensuite indique le nombre de Batiments, puis le nombre de personnages (commandants compris) et s'il y a un QG ou non." ; 
    //     cout << "\n Au format x x x x par exemple : 1 1 1 1." ; 
    //     cout << "\n Allez à ton tour champion : " ; 
    //     cin >> nb_diff_unit >> nb_bat >> nb_perso >> qg ;; 
    //     printArmy() ; 

    //     if(qg){
    //         constructQG() ; 
    //     }

    //     if (nb_perso >= 1) {
    //         constructPerso(nb_perso) ; 
    //     }

    //     if (nb_bat >= 1){
    //         constructBat(nb_bat) ; 
    //     }

    //     if( nb_diff_unit >= 1){
    //         constructUnit(nb_diff_unit) ; 
    //     }

    //     printArmy() ; 

    //     if(intel == 0){
    //         cout << "\n Bien joué Champion ! On passe au suivant.\n" ; 
    //     }
    //     else {
    //          cout << "\n Bien joué Champion ! On passe aux calculs.\n" ; 
    //     }
        
    // }

    string player::getName() const { return name ;}

    float player::getTotPdf() const { return t_pdf ;}
    float player::getTotPdc() const { return t_pdc ;}
    float player::getTotAtk() const { return t_atk ;}

    float player::getSubPoints(int type) const {
        float subpts = 0 ; 
        if(type == 0 || type == 1 || type == 2 || type == 3){
            for(int i = 0 ; i < (int) army.size() ; i++){
                if(army[i].type == type){
                    subpts += ( army[i].atk + army[i].pdf + army[i].pdc)  ; 
                }
            }
            return subpts ;  
        }
        else{
            return -1 ; 
        }
    }

    void player::setSub0(int type){
        if (type == 0 || type == 1 || type == 2 || type == 3){
            for(int i = 0 ; i < (int) army.size() ; i++){
                if(army[i].type == type){
                    army[i].atk = 0 ; 
                     army[i].pdf = 0 ; 
                      army[i].pdc = 0 ; 
                }
            }
        }
    }

    bool player::getUnitBool() const { return unit_bool ; }
    bool player::getPersonnageBool() const { return personnages_bool ; }
    bool player::getBatimentBool() const { return batiment_bool ; }
    bool player::getQGBool() const { return QG_bool ; }

    float player::fetch_def(int type = 0) const { 
        unit fetched_unit = *find_if(army.rbegin(), army.rend(), [type](auto arg) {
            return arg.type == type ;
        });
        return fetched_unit.getDef() ; 
    }
    float player::fetch_arm(int type = 0) const { 
        // Retourne la dernière unité dans le vecteur de type voulu.
        unit fetched_unit = *find_if(army.rbegin(), army.rend(), [type](auto arg) {
            return arg.type == type ;
        });

        return fetched_unit.getArm() ; 
    }

    float player::fetch_esq(int type = 0) const { 
        // Retourne la dernière unité dans le vecteur de type voulu.
        unit fetched_unit = *find_if(army.rbegin(), army.rend(), [type](auto arg) {
            return arg.type == type ;
        });

        return fetched_unit.getEsq() ; 
    }

    void player::setName(string s) { name = s ;}

    void player::setLastDef(float f, int type) { 
        auto fetched_unit = find_if(army.rbegin(), army.rend(), [type](auto arg) {
            return arg.type == type ;
        });       
        (*fetched_unit).setDef(f) ;
       
    }
    void player::setLastArm(float f, int type) { 
        auto fetched_unit = find_if(army.rbegin(), army.rend(), [type](auto arg) {
            return arg.type == type ;
        });       
        (*fetched_unit).setArm(f) ;
    }
    
    void player::delUnit(int type = 0) {
        auto fetched_unit = find_if(army.rbegin(), army.rend(), [type](auto arg) {
            return arg.type == type ;
        });
        
        army.erase(next(fetched_unit).base());
        // On oublie pas de setTotalStats(). 
        setTotalStats() ; 
    }

    void player::printArmy() {
        setTotalStats() ; // On set les stats avant de print, pour être sur d'être à jour. 
        if ((t_atk == 0) && (t_def == 0) && (t_pdf == 0) && (t_pdc == 0) && (t_arm == 0)){
            std::cout << "\nUnités de " << name << " : \n\n" ;
             std::cout << "  L'armée est vide.\n" << endl ; 
        }
        else{
             std::cout << "\nUnités de " << name << " : \n\n" ; 
            for(int i = 0 ; i < (int) army.size() ; i++){
                army[i].printUnit() ; 
            }
             std::cout << "\n Total => " << t_atk << " Atk + " << t_pdf << " Pdf + " << t_pdc << " Pdc / " << t_def << " Def + " << t_arm << " Arm.\n\n" ;
        }
    }

    void player::setTotalStats() {
        t_atk = t_def = t_pdf = t_pdc = t_arm = 0 ;
        for(int i = 0 ; i < (int) army.size() ; i++){
            t_atk += army[i].atk ; 
            t_def += army[i].def ; 
            t_pdf += army[i].pdf ; 
            t_pdc += army[i].pdc ; 
            t_arm += army[i].arm ; 
        }
        // On en profite pour mettre à jour les bools. 
        setBools() ; 
    }


    bool player::isArmyEmpty() const {return army.empty() ;} 

    void player::delPdf(float f) {
        int pos = (int) army.size() -1 ;
        float cur_Pdf = army[pos].getPdf() ; 
        float tot_Pdf = getTotPdf() ;
        if(f > tot_Pdf){
            f = 0 ; 
        }
        while (f > 0 && pos >= 0){
            cur_Pdf = army[pos].getPdf() ; 
            if((tot_Pdf - cur_Pdf) >= f) {
                    tot_Pdf -= cur_Pdf; 
                    army[pos].setPdf(0) ;
                    pos -- ; 
                }
                else{
                    army[pos].setPdf(cur_Pdf - (tot_Pdf - f)) ; 
                    f = 0 ; 
                }
            }
        }

    void player::delPdc(float f) {
        int pos = (int) army.size() -1 ;
        float cur_Pdc = army[pos].getPdc() ; 
        float tot_Pdc = getTotPdc() ;
        if(f > tot_Pdc){
            f = 0 ; 
        }
        while (f > 0 && pos >= 0){
            cur_Pdc = army[pos].getPdc() ; 
            if((tot_Pdc - cur_Pdc) >= f) {
                    tot_Pdc -= cur_Pdc; 
                    army[pos].setPdc(0) ;
                    pos -- ; 
                }
                else{
                    army[pos].setPdc(cur_Pdc - (tot_Pdc - f)) ; 
                    f = 0 ; 
                }
            }
        }

    void player::delAtk(float f) {
        int pos = (int) army.size() -1 ;
        float cur_atk = army[pos].getAtk() ; 
        float tot_atk = getTotAtk() ;
        if(f > tot_atk){
            f = 0 ; 
        }
        while (f > 0 && pos >= 0){
            cur_atk = army[pos].getAtk() ; 
            if((tot_atk - cur_atk) >= f) {
                    tot_atk -= cur_atk; 
                    army[pos].setAtk(0) ;
                    pos -- ; 
                }
                else{
                    army[pos].setAtk(cur_atk - (tot_atk - f)) ; 
                    f = 0 ; 
                }
            }
        }
    
    void player::setUnitsPdf(float f = 0) {
        for(int i = 0 ; i < (int) army.size() ; i++){
            army[i].setPdf(f) ; 
        }
    }

     void player::setUnitsPdc(float f = 0) {
        for(int i = 0 ; i < (int) army.size() ; i++){
            army[i].setPdc(f) ; 
        }
    }

    void player::setUnitsAtk(float f = 0) {
        for(int i = 0 ; i < (int) army.size() ; i++){
            army[i].setAtk(f) ; 
        }
    }

    void player::setBools() {
        int u_type = -1 ; 
        // On les reset. 
        unit_bool = batiment_bool = personnages_bool = QG_bool = 0 ; 
        // On set. 
        for(int i = 0 ; i < (int) army.size() ; i++){
            u_type = army[i].getType() ; 
            if(u_type == 0)
                unit_bool = 1 ; 
            if(u_type == 1)
                batiment_bool = 1 ; 
            if(u_type == 2)
                personnages_bool = 1 ; 
            if(u_type == 3)
                QG_bool = 1 ; 
        }

    }

    void player::setModifierStats(float pourcentage) { // Seulement les unités. 
        for(int i = 0 ; i < (int) army.size() ; i++){
            if(army[i].type == 0){
                army[i].atk += army[i].atk * pourcentage / 100 ; 
                army[i].def += army[i].def * pourcentage / 100 ; 
                army[i].pdf += army[i].pdf * pourcentage / 100 ; 
                army[i].pdc += army[i].pdc * pourcentage / 100 ; 
                army[i].arm += army[i].arm * pourcentage / 100 ; 
            }
        }
    }

    // void player::addBatiment(){
    //     army.push_back(unit("Cache d'arme", 1, 100, 0, 0, 100, 0)) ;
    //     army.push_back(unit("Banque", 1, 50, 0, 0, 50, 0)) ;
    //     // 0 = unité | 1 = Batiments | 2 = Lieutenant et Personnage principal | 3 = QG. 
    // }

    // void player::addPersonnage(){
    //     army.push_back(unit("Le Ventriloque", 2, 100, 50, 50, 100, 50)) ;
    //     army.push_back(unit("Commandant", 2, 25, 12.5, 6.25, 25, 0)) ;
    // }

    // void player::addQG(){
    //     army.push_back(unit("Quartier Général", 3, 100, 0, 0, 200, 0)) ;
    // }

    // void player::constructQG(){
    //     int a ; 
    //     cout << "C'est un QG normal ? (0 = oui / non = 1) : " ;
    //     cin >> a ; 
    //     if(a == 0){
    //         addQG() ; 
    //     }
    //     else{
    //         cout << "Tu fais chier !! \n"  ; 
    //         float a, b, c, d ; 
    //         cout << "Entre : Atk Pdf Pdc Def  "; 
    //         cin >> a >> b >> c >> d ; 
    //         army.push_back(unit("Quartier Général", 3, a, b, c, d, 0)) ;
    //         //string STR, int NUMBER, int TYPE, float ATK, float PDF, float PDC , float DEF ,float ARM
    //     }
    // }

    // void player::constructPerso(int index) {
    //     cout << "\nDébut du Constructeur de Perso.\n" ; 
    //     float a, b, c, d, e ; 
    //     string player_name ; 
    //     cout << "Tu vas devoir rentrer (" << index << ") fois les stats des perso.\n" ; 
    //     for(int i = 0 ; i < index ; i ++) {
    //         cin.clear() ; 
    //         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input    
    //         cout << "Quel est le nom du Personnage ? : " ; 
    //         getline(cin, player_name);
    //         stringstream ss(player_name) ; 
    //         cout << "\nEntre : Atk Pdf Pdc Def et Arm  "; 
    //         cin >> a >> b >> c >> d >> e ; 
    //         army.push_back(unit(player_name, 2, a, b, c, d, e)) ;
    //     }
    //     cout << "\nTerminé pour les Personnages. \n" ; 
    // }

    // void player::constructBat(int index) {
    //     cout << "\nDébut du constructeur de Batiments. \n" ; 
    //     float a, b, c, d ; 
    //     string player_name ; 

    //     int choice = 0 ; 
    //     cout << "   Est-ce qu'il y a UNIQUEMENT CA ET Banque (classique) ? (0 = oui / non = 1) : " ; 
    //     cin >> choice ; 
    //     if(choice == 0) {
    //         addBatiment() ; 
    //     } 
    //     else{
    //         cout << "Tu vas devoir rentrer (" << index << ") fois les stats des Batiments\n" ; 
    //         for(int i = 0 ; i < index ; i ++) {   
    //             cin.clear() ;   
    //             cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input   
    //             cout << "\nQuel est le nom du Batiment ? : " ; 
    //             getline(cin, player_name);
    //             stringstream ss(player_name) ; 
    //             cout << "\nEntre : Atk Pdf Pdc et Def : "; 
    //             cin >> a >> b >> c >> d ; 
    //             army.push_back(unit(player_name, 1, a, b, c, d, 0)) ;
    //         }
    //     }
    //     cout << "\nTerminé pour les Batiments. \n" ; 
    // }

    // void player::constructUnit(int index) {
    //     cout << "\nDébut du constructeur d'Unités. \n" ; 
    //     float a, b, c, d, e ; 
    //     int choice = 0 ;  
    //     int nber = 0 ; 
    //     int unit_i = 1 ; 

    //     cout << "Tu vas devoir rentrer (" << index << ") fois les stats des Unités\n" ; 
    //     cout << "Attention ! Toujours rentrer les unités avec le plus d'Exp en premier PUIS avec la def la plus haute ! " ; 
    //     for(int i = 0 ; i < index ; i++){
    //         cout << "Est-ce c'est des unités à poil (larbins ?) (0 = oui / non = 1) : " ; 
    //         cin >> choice ; 
    //         if (choice == 0){
    //             cout << "Combien d'unités à poil ? : " ; 
    //             cin >> nber ; 
    //             for(int j = 0 ; j < nber ; j++){
    //                 army.push_back(unit("Larbin", unit_i, 10, 0, 0, 10, 0)) ;
    //                 unit_i ++ ; 
    //             }
    //         }
    //         else{
    //             cout << "Combien d'unités ? : " ; 
    //             cin >> nber ; 
    //             cout << "\nEntre : Atk Pdf Pdc Def et Arm : "; 
    //             cin >> a >> b >> c >> d >> e; 
    //             for(int j = 0 ; j < nber ; j++){
    //                 army.push_back(unit("Larbin", unit_i, a, b, c, d, e)) ;
    //                 unit_i ++ ; 
    //             }
    //         }
    //         cout << "\nTerminé pour les Unités. \n" ; 
    //     }
    // }


