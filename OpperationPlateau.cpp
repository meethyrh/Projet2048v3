#include <string>  
#include <iostream> 
#include <vector>
#include <cstdlib>
using namespace std;
typedef vector<vector<int> > Plateau;

#include "Jeu2048.h"

plateauS combineCases_gauche(plateauS plateau){
    for(int i = 0; i < plateau.plateau.size(); i++){
        for(int j = 0; j < plateau.plateau[i].size(); j++){
            if(plateau.plateau[i][j] > 0 and plateau.plateau[i][j] == plateau.plateau[i][j+1] and j+1 <= 3){
                plateau.plateau[i][j] = plateau.plateau[i][j] + plateau.plateau[i][j+1];
                plateau.plateau[i][j+1] = 0;
                plateau.score += plateau.plateau[i][j] + plateau.plateau[i][j+1];
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



plateauS deplacementGauche(plateauS plateau){
    plateau.plateau = deplacementGauche_sansCombi(plateau.plateau);
    plateau.plateau = combineCases_gauche(plateau.plateau);
    plateau.plateau = deplacementGauche_sansCombi(plateau.plateau);
    return plateau;
}


Plateau flip_vertical(Plateau plateau){
    Plateau plateau_fliped;
    plateau_fliped = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    for(int i = 0; i < plateau.size(); i++){
        int k = 3;
        for(int j = 0; j < plateau[i].size(); j++){
            plateau_fliped[i][j] = plateau[i][k];
            k-=1;
        }
    } return plateau_fliped;
}                                
                                       

plateauS deplacementDroite(plateauS plateau){
    plateau.plateau = flip_vertical(plateau.plateau);
    plateau.plateau = deplacementGauche(plateau.plateau);
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


plateauS combineCases_haut(plateauS plateau){
    plateau.plateau = deplacementHaut_sansCombi(plateau.plateau);
    for(int i = 1; i < plateau.plateau.size(); i++){
        for (int j = 0; j < plateau.plateau[i].size(); j++){
            if(plateau.plateau[i-1][j] > 0 and plateau.plateau[i][j] == plateau.plateau[i-1][j]){
                plateau.plateau[i-1][j] = plateau.plateau[i-1][j] + plateau.plateau[i-1][j];
                plateau.plateau[i][j] = 0;
                plateau.score += plateau.plateau[i-1][j] + plateau.plateau[i-1][j];
            }
        }
    } return plateau;
}


plateauS deplacementHaut(plateauS plateau){
    plateau.plateau = deplacementHaut_sansCombi(plateau.plateau);
    plateau.plateau = combineCases_haut(plateau.plateau);
    plateau.plateau = deplacementHaut_sansCombi(plateau.plateau);
    return plateau;
}


Plateau flip_horizontal(Plateau plateau){
    Plateau plat_flipH; 
    plat_flipH = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    //note: tab_flipH = tableau fliped sur l'axe Horizontal
    int k = plateau.size() - 1;
    for(int i = 0; i < plateau.size(); i++){
        plat_flipH[i] = plateau[k];
        k-=1;
    } return plat_flipH;
}

plateauS deplacementBas(plateauS plateau){
    plateau.plateau = flip_horizontal(plateau.plateau);
    plateau.plateau = deplacementHaut(plateau.plateau);
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

plateauS deplacement(plateauS plateau, int direction){
    //HAUT
    if(direction == 1 ){
        plateauS plateauOriginal;
        plateauOriginal.plateau = plateau.plateau;
        plateau.plateau = deplacementHaut(plateau.plateau);
        for(int i = 0; i < plateau.plateau.size(); i++){
            for(int j = 0; j < plateau.plateau[i].size(); j++){
                if(plateau.plateau[i][j] == plateauOriginal.plateau[i][j]){
                    return plateauOriginal;
                }
            }
            plateau.plateau = nouvelleCase(plateau.plateau);
            return plateau;
        }
    //BAS
    } else if (direction == 2) {
        plateauS plateauOriginal;
        plateauOriginal.plateau = plateau.plateau;
        plateau.plateau = deplacementBas(plateau.plateau);
        for(int i = 0; i < plateau.plateau.size(); i++){
            for(int j = 0; j < plateau.plateau[i].size(); j++){
                if(plateau.plateau[i][j] == plateauOriginal.plateau[i][j]){
                    return plateauOriginal;
                }
            }
            plateau.plateau = nouvelleCase(plateau.plateau);
            return plateau;
        }
    //GAUCHE
    } else if (direction == 3){
        plateauS plateauOriginal;
        plateauOriginal.plateau = plateau.plateau;
        plateau.plateau = deplacementGauche(plateau.plateau);
        for(int i = 0; i < plateau.plateau.size(); i++){
            for(int j = 0; j < plateau.plateau[i].size(); j++){
                if(plateau.plateau[i][j] == plateauOriginal.plateau[i][j]){
                    return plateauOriginal;
                }
            }
            plateau.plateau = nouvelleCase(plateau.plateau);
            return plateau;
        }
    //DROITE
    } else if (direction == 4){
        plateauS plateauOriginal;
        plateauOriginal.plateau = plateau.plateau;
        plateau.plateau = deplacementDroite(plateau.plateau);
        for(int i = 0; i < plateau.plateau.size(); i++){
            for(int j = 0; j < plateau.plateau[i].size(); j++){
                if(plateau.plateau[i][j] == plateauOriginal.plateau[i][j]){
                    return plateauOriginal;
                }
            }
            plateau.plateau = nouvelleCase(plateau.plateau);
            return plateau;
        }
    return plateau;
    }
}