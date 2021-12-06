#include <string>  
#include <iostream> 
#include <vector>
#include <cstdlib>
using namespace std;
typedef vector<vector<int> > Plateau;

#include "Jeu2048.h"


PS combineCases_gauche(PS plateau){
    for(int i = 0; i < plateau.plateau.size(); i++){
        for(int j = 0; j < plateau.plateau[i].size(); j++){
            if(plateau.plateau[i][j] > 0 and plateau.plateau[i][j] == plateau.plateau[i][j+1] and j+1 <= 3){
                plateau.plateau[i][j] = plateau.plateau[i][j] + plateau.plateau[i][j+1];
                plateau.plateau[i][j+1] = 0;
                plateau.score += plateau.plateau[i][j];
            }
        }
    } return plateau;
}

Plateau deplacementGauche_sansCombi(Plateau plateau){
    for(int i = 0; i < plateau.size(); i++){
        for(int j = 0; j < plateau[i].size(); j++){
            if(plateau[i][j] > 0){
                for(int k = 0; k < j; k++){
                    while(plateau[i][j-1-k] == 0){
                        plateau[i][j-1-k] = plateau[i][j-k];
                        plateau[i][j-k] = 0;
                    }
                }
                
            }
        }
    } return plateau;
}



PS deplacementGauche(PS plateau){
    plateau.plateau = deplacementGauche_sansCombi(plateau.plateau);
    plateau = combineCases_gauche(plateau);
    plateau.plateau = deplacementGauche_sansCombi(plateau.plateau);
    return plateau;
}


Plateau flip_vertical(Plateau plateau){
    int m = plateau.size();
    int n = plateau[1].size();
    Plateau plateau_fliped(m, vector<int> (n));
    for(int i = 0; i < plateau.size(); i++){
        int k = plateau[i].size() -1;
        for(int j = 0; j < plateau[i].size(); j++){
            plateau_fliped[i][j] = plateau[i][k];
            k-=1;
        }
    } return plateau_fliped;
}                                
                                       

PS deplacementDroite(PS plateau){
    plateau.plateau = flip_vertical(plateau.plateau);
    plateau = deplacementGauche(plateau);
    plateau.plateau = flip_vertical(plateau.plateau);
    return plateau;
}



Plateau deplacementHaut_sansCombi(Plateau plateau){
    for(int i = 0; i < plateau.size(); i++){
        for(int j = 0; j < plateau[i].size(); j++){
            if(plateau[i][j] > 0){
                for(int k = 0; k < i; k++){
                    while(plateau[i-1-k][j] == 0){
                        plateau[i-k-1][j] = plateau[i-k][j];
                        plateau[i-k][j] = 0;
                    }
                }
            }
        }
    } return plateau;
}


PS combineCases_haut(PS plateau){
    for(int i = 1; i < plateau.plateau.size(); i++){
        for (int j = 0; j < plateau.plateau[i].size(); j++){
            if(plateau.plateau[i-1][j] > 0 and plateau.plateau[i][j] == plateau.plateau[i-1][j]){
                plateau.plateau[i-1][j] = plateau.plateau[i-1][j] + plateau.plateau[i-1][j];
                plateau.plateau[i][j] = 0;
                plateau.score += plateau.plateau[i-1][j];
            }
        }
    } return plateau;
}


PS deplacementHaut(PS plateau){
    plateau.plateau = deplacementHaut_sansCombi(plateau.plateau);
    plateau = combineCases_haut(plateau);
    plateau.plateau = deplacementHaut_sansCombi(plateau.plateau);
    return plateau;
}


Plateau flip_horizontal(Plateau plateau){
    int m = plateau.size();
    int n = plateau[1].size();
    Plateau plat_flipH (m, vector<int> (n));

    //note: tab_flipH = tableau fliped sur l'axe Horizontal
    int k = plateau.size() - 1;
    for(int i = 0; i < plateau.size(); i++){
        plat_flipH[i] = plateau[k];
        k-=1;
    } return plat_flipH;
}

PS deplacementBas(PS plateau){
    plateau.plateau = flip_horizontal(plateau.plateau);
    plateau = deplacementHaut(plateau);
    plateau.plateau = flip_horizontal(plateau.plateau);
    return plateau;
}

Plateau nouvelleCase(Plateau plateau){
    int indiceI = NumberGenerator(0, plateau.size()-1);
    int indiceJ = NumberGenerator(0, plateau[0].size()-1);
    if(plateau[indiceI][indiceJ] == 0){
        plateau[indiceI][indiceJ] = tireDeuxOuQuatre();
    } else {
        while (plateau[indiceI][indiceJ] > 0){
            indiceI = NumberGenerator(0, plateau.size()-1);
            indiceJ = NumberGenerator(0, plateau[0].size()-1);
        } plateau[indiceI][indiceJ] = tireDeuxOuQuatre();
    } return plateau;
}

PS deplacement(PS plateau, int direction){
    //HAUT
    if(direction == 1 ){
        Plateau plateauOriginal = plateau.plateau;
        plateau = deplacementHaut(plateau);
        for(int i = 0; i < plateau.plateau.size(); i++){
            for(int j = 0; j < plateau.plateau[i].size(); j++){
                if(plateau.plateau == plateauOriginal){
                    return plateau;
                }
            }

        } plateau.plateau = nouvelleCase(plateau.plateau);
        return plateau;
    //BAS
    } else if(direction == 2) {
        Plateau plateauOriginal = plateau.plateau;
        plateau = deplacementBas(plateau);
        for(int i = 0; i < plateau.plateau.size(); i++){
            for(int j = 0; j < plateau.plateau[i].size(); j++){
                if(plateau.plateau == plateauOriginal){
                    return plateau;
                }
            }

        } plateau.plateau = nouvelleCase(plateau.plateau);
        return plateau;
    //GAUCHE
    } else if (direction == 3){
        Plateau plateauOriginal = plateau.plateau;
        plateau = deplacementGauche(plateau);
        for(int i = 0; i < plateau.plateau.size(); i++){
            for(int j = 0; j < plateau.plateau[i].size(); j++){
                if(plateau.plateau == plateauOriginal){
                    return plateau;
                }
            }

        } plateau.plateau = nouvelleCase(plateau.plateau);
        return plateau;
    //DROITE
    } else if(direction == 4){
        Plateau plateauOriginal = plateau.plateau;
        plateau = deplacementDroite(plateau);
        for(int i = 0; i < plateau.plateau.size(); i++){
            for(int j = 0; j < plateau.plateau[i].size(); j++){
                if(plateau.plateau == plateauOriginal){
                    return plateau;
                }
            }

        } plateau.plateau = nouvelleCase(plateau.plateau);
        return plateau;
    }
    return plateau;
}
