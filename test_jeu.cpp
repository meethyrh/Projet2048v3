#include <iostream> 
#include <vector>
#include <cstdlib>
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

bool TestPlatoInit(Plateau plateau){
	int m = 0; 
	for(int i = 0; i < plateau.size(); i++){
		for (int j = 0; j < plateau[i].size(); j++){
			if (plateau[i][j] > 0){
				m+=1;
			}
		}
	} if (m == 2){
		return true;
	} else {
		return false;
	}
}

void test_all_func(){
    PS plateau; 
    plateau.plateau = {{2,0,0,2},{2,2,2,2},{0,4,4,0},{2,4,0,4}};
    plateau.score = 0;

	PS plateau5;
	plateau5.plateau = {{2,2,2,2,4},{4,2,4,4,4},{0,0,0,0,0}};
	plateau5.score = 0;

	PS plateau3;
	plateau3.plateau = {{2,4},{2,0},{4,4}};
	plateau3.score = 0;
    
//-----------------------------------4x4-------------------------------------------
	assert(compareTableau(plateauVide(), {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}));
	assert(TestPlatoInit(plateauInitial(plateauVide())));

	int a = NumberGenerator(1, 2);
	assert((a == 1) or (a == 2));

	int x = tireDeuxOuQuatre();
	assert(x == 2 or x == 4);

	assert(dessine(plateau.plateau).size() > 2);

	assert(estTermine({{2,4,2,4},{4,2,4,2},{2,4,2,4},{4,2,4,2}}));
	assert(estGagnant({{0,0,0,0},{2048,0,0,0},{0,2,0,2},{0,0,0,0}}));
    
	//deplacements
	assert(compareTableau(deplacementHaut(plateau).plateau, {{4,2,2,4},{2,8,4,4},{0,0,0,0},{0,0,0,0}}));
	assert(compareTableau(deplacementBas(plateau).plateau, {{0,0,0,0},{0,0,0,0},{2,2,2,4},{4,8,4,4}}));
	assert(compareTableau(deplacementGauche(plateau).plateau, {{4,0,0,0},{4,4,0,0},{8,0,0,0},{2,8,0,0}}));
	assert(compareTableau(deplacementDroite(plateau).plateau, {{0,0,0,4},{0,0,4,4},{0,0,0,8},{0,0,2,8}}));

	//combinaison
	assert(compareTableau(combineCases_haut(plateau).plateau, {{4,0,0,4},{0,2,2,0},{0,8,4,0},{2,0,0,4}}));
	assert(compareTableau(combineCases_gauche(plateau).plateau, {{2,0,0,2},{4,0,4,0},{0,8,0,0},{2,4,0,4}}));

	//deplacement sans combinaison
	assert(compareTableau(deplacementGauche_sansCombi(plateau.plateau), {{2,2,0,0},{2,2,2,2},{4,4,0,0},{2,4,4,0}}));
	assert(compareTableau(deplacementHaut_sansCombi(plateau.plateau), {{2,2,2,2},{2,4,4,2},{2,4,0,4},{0,0,0,0}}));
	
	//retourner le plateau
	assert(compareTableau(flip_vertical(plateau.plateau), {{2,0,0,2},{2,2,2,2},{0,4,4,0},{4,0,4,2}}));
	assert(compareTableau(flip_horizontal(plateau.plateau), {{2,4,0,4},{0,4,4,0},{2,2,2,2},{2,0,0,2}}));
	
	//score
	assert(combineCases_gauche(plateau).score == 16);
	assert(deplacementGauche(plateau).score == 28);
	assert(deplacementDroite(plateau).score == 28);
	assert(combineCases_haut(plateau).score == 16);
	assert(deplacementHaut(plateau).score == 16);

	//deplacements
	assert(not compareTableau(plateau.plateau, nouvelleCase(plateau.plateau)));
	assert(not compareTableau(deplacement(plateau, 1).plateau, deplacementHaut(plateau).plateau));
	assert(not compareTableau(deplacement(plateau, 2).plateau, deplacementBas(plateau).plateau));
	assert(not compareTableau(deplacement(plateau, 3).plateau, deplacementGauche(plateau).plateau));
	assert(not compareTableau(deplacement(plateau, 4).plateau, deplacementDroite(plateau).plateau));

//-----------------------------------3x5---------------------------------------------
	assert(compareTableau(deplacementGauche(plateau5).plateau, {{4,4,4,0,0},{4,2,8,4,0},{0,0,0,0,0}}));
	assert(compareTableau(deplacementHaut(plateau5).plateau, {{2,4,2,2,8},{4,0,4,4,0},{0,0,0,0,0}}));
	assert(compareTableau(flip_horizontal(plateau5.plateau), {{0,0,0,0,0},{4,2,4,4,4},{2,2,2,2,4}}));
	assert(compareTableau(flip_vertical(plateau5.plateau), {{4,2,2,2,2},{4,4,4,2,4},{0,0,0,0,0}}));
	assert(deplacementGauche(plateau5).score == 16);
	assert(deplacementHaut(plateau5).score == 12);

//------------------------------------3x2--------------------------------------------
	assert(compareTableau(deplacementGauche(plateau3).plateau, {{2,4},{2,0},{8,0}}));
	assert(compareTableau(deplacementHaut(plateau3).plateau, {{4,8},{4,0},{0,0}}));
	assert(compareTableau(flip_horizontal(plateau3.plateau), {{4,4},{2,0},{2,4}}));
	assert(compareTableau(flip_vertical(plateau3.plateau), {{4,2},{0,2},{4,4}}));
	assert(deplacementGauche(plateau3).score == 8);
	assert(deplacementHaut(plateau3).score == 12);
}


