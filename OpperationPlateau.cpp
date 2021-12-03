#include <string>  
#include <iostream> 
#include <vector>
#include <cstdlib>
using namespace std;
typedef vector<vector<int> > Plateau;

#include "Jeu2048.h"


Plateau combineCases_gauche(Plateau plateau){
    for(int i = 0; i < plateau.size(); i++){
        for(int j = 0; j < plateau[i].size(); j++){
            if(plateau[i][j] > 0 and plateau[i][j] == plateau[i][j+1] and j+1 <= 3){
                plateau[i][j] = plateau[i][j] + plateau[i][j+1];
                plateau[i][j+1] = 0;
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



Plateau deplacementGauche(Plateau plateau){
    plateau = deplacementGauche_sansCombi(plateau);
    plateau = combineCases_gauche(plateau);
    plateau = deplacementGauche_sansCombi(plateau);
    return plateau;
}


Plateau flip_vertical(Plateau plateau){
    Plateau plateau_fliped = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    for(int i = 0; i < plateau.size(); i++){
        int k = 3;
        for(int j = 0; j < plateau[i].size(); j++){
            plateau_fliped[i][j] = plateau[i][k];
            k-=1;
        }
    } return plateau_fliped;
}                                
                                       

Plateau deplacementDroite(Plateau plateau){
    plateau = flip_vertical(plateau);
    plateau = deplacementGauche(plateau);
    plateau = flip_vertical(plateau);
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


Plateau combineCases_haut(Plateau plateau){
    plateau = deplacementHaut_sansCombi(plateau);
    for(int i = 1; i < plateau.size(); i++){
        for (int j = 0; j < plateau[i].size(); j++){
            if(plateau[i-1][j] > 0 and plateau[i][j] == plateau[i-1][j]){
                plateau[i-1][j] = plateau[i-1][j] + plateau[i-1][j];
                plateau[i][j] = 0;
            }
        }
    } return plateau;
}


Plateau deplacementHaut(Plateau plateau){
    plateau = deplacementHaut_sansCombi(plateau);
    plateau = combineCases_haut(plateau);
    plateau = deplacementHaut_sansCombi(plateau);
    return plateau;
}


Plateau flip_horizontal(Plateau plateau){
    Plateau plat_flipH = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    //note: tab_flipH = tableau fliped sur l'axe Horizontal
    int k = plateau.size() - 1;
    for(int i = 0; i < plateau.size(); i++){
        plat_flipH[i] = plateau[k];
        k-=1;
    } return plat_flipH;
}

Plateau deplacementBas(Plateau plateau){
    plateau = flip_horizontal(plateau);
    plateau = deplacementHaut(plateau);
    plateau = flip_horizontal(plateau);
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

Plateau deplacement(Plateau plateau, int direction){
    //HAUT
    if(direction == 1 ){
        Plateau plateauOriginal = plateau;
        plateau = deplacementHaut(plateau);
        Plateau plateau_deplace = plateau;
        if(plateau_deplace == plateauOriginal){
            return plateau_deplace;
        } else {
            plateau_deplace = nouvelleCase(plateau_deplace);
            return plateau_deplace;
        }
    //BAS
    } else if(direction == 2) {
        Plateau plateauOriginal = plateau;
        plateau = deplacementBas(plateau);
        Plateau plateau_deplace = plateau;
        if(plateau_deplace == plateauOriginal){
            return plateau_deplace;
        } else {
            plateau_deplace = nouvelleCase(plateau_deplace);
            return plateau_deplace;
        }
    //GAUCHE
    } else if (direction == 3){
        Plateau plateauOriginal = plateau;
        plateau = deplacementGauche(plateau);
        Plateau plateau_deplace = plateau;
        if(plateau_deplace == plateauOriginal){
            return plateau_deplace;
        } else {
            plateau_deplace = nouvelleCase(plateau_deplace);
            return plateau_deplace;
        }
    //DROITE
    } else if(direction == 4){
        Plateau plateauOriginal = plateau;
        plateau = deplacementDroite(plateau);
        Plateau plateau_deplace = plateau;
        if(plateau_deplace == plateauOriginal){
            return plateau_deplace;
        } else {
            plateau_deplace = nouvelleCase(plateau_deplace);
            return plateau_deplace;
        }
    }
    return plateau;
}
