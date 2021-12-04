#include <string>  
#include <iostream> 
#include <sstream>
#include <vector>
#include <cstdlib>
#include <random>
#include <assert.h>
using namespace std;
typedef vector<vector<int> > Plateau;

#include "Jeu2048.h"

bool compareTableau(Plateau plateau1, Plateau plateau2){
	for(int i = 0; i < plateau1.size(); i++){
		for(int j = 0; j < plateau1[i].size(); j++){
			if(plateau1[i][j] != plateau2[i][j]){
				return false;
			}
		}
	} return true;
}

//pas encore dans le .h
bool TestPlatoInit(Plateau plateau){
	int m = 0; 
	for(int i = 0; i < plateau.size(); i++){
		for (int j = 0; j < plateau[i].size(); j++){
			if (plateau[i][j] > 0){
				m+=1;
			}
		}
	} if (m > 2){
		return true;
	} else {
		return false;
	}
}

void test_all_func(){
    PS plateau; 
    plateau.plateau = {{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}};
    plateau.score = 0;
    
	CHECK(compareTableau(plateauVide(), {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}));
	CHECK(TestPlatoInit(plateauInitial(plateauVide())));
	CHECK(tireDeuxOuQuatre() == 2 or tireDeuxOuQuatre() == 4);
    
	//ASSERT(dessine());
	CHECK(compareTableau(combineCases_gauche(plateau).plateau, {{2,0,0,2},{4,0,0,0},{0,8,0,0},{2,4,0,4}}));
    
	CHECK(compareTableau(deplacementGauche_sansCombi(plateau.plateau), {{2,2,0,0},{2,2,0,0},{4,4,0,0},{2,4,4,0}}));
    
	CHECK(compareTableau(deplacementGauche(plateau).plateau, {{4,0,0,0},{4,0,0,0},{8,0,0,0},{2,8,0,0}}));
    
	CHECK(compareTableau(flip_vertical(plateau.plateau), {{2,0,0,2},{0,0,2,2},{0,4,4,0},{4,0,4,2}}));
    
	CHECK(compareTableau(deplacementDroite(plateau).plateau, {{0,0,0,4},{0,0,0,4},{0,0,0,8},{0,0,8,2}}));
    
	CHECK(compareTableau(deplacementHaut_sansCombi(plateau.plateau), {{2,2,4,4},{2,4,0,4},{2,4,0,0},{0,0,0,0}}));
    
	CHECK(compareTableau(combineCases_haut(plateau).plateau, {{4,0,0,2},{2,2,0,0},{0,8,4,0},{2,0,0,4}}));
    
	CHECK(compareTableau(deplacementHaut(plateau).plateau, {{4,2,4,2},{2,8,0,4},{0,0,0,0},{0,0,0,0}}));
    
	CHECK(compareTableau(flip_horizontal(plateau.plateau), {{2,4,0,4},{0,4,4,0},{2,2,0,0},{2,0,0,2}}));
    
	CHECK(compareTableau(deplacementBas(plateau).plateau, {{0,0,0,0},{0,0,0,0},{2,2,0,2},{4,8,4,4}}));
    
	CHECK(compareTableau(deplacement(plateau, 1).plateau, deplacementHaut(plateau).plateau));
	CHECK(compareTableau(deplacement(plateau, 2).plateau, deplacementBas(plateau).plateau));
	CHECK(compareTableau(deplacement(plateau, 3).plateau, deplacementGauche(plateau).plateau));
	CHECK(compareTableau(deplacement(plateau, 4).plateau, deplacementDroite(plateau).plateau));	
}


