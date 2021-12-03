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

void test_all_func(){
	ASSERT(compareTableau(plateauVide(), {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}));
	//ASSERT(plateauInitial());
	ASSERT(tireDeuxOuQuatre() == 2 or tireDeuxOuQuatre() == 4);
	//ASSERT(dessinePlateau());
	ASSERT(compareTableau(combineCases_gauche({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}), {{2,0,0,2},{4,0,0,0},{0,8,0,0},{2,4,0,4}}));
	ASSERT(compareTableau(deplacementGauche_sansCombi({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}), {{2,2,0,0},{2,2,0,0},{4,4,0,0},{2,4,4,0}}));
	ASSERT(compareTableau(deplacementGauche({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}), {{4,0,0,0},{4,0,0,0},{8,0,0,0},{2,8,0,0}}));
	ASSERT(compareTableau(flip_vertical({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}), {{2,0,0,2},{0,0,2,2},{0,4,4,0},{4,0,4,2}}));
	ASSERT(compareTableau(deplacementDroite({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}), {{0,0,0,4},{0,0,0,4},{0,0,0,8},{0,0,8,2}}));
	ASSERT(compareTableau(deplacementHaut_sansCombi({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}), {{2,2,4,4},{2,4,0,4},{2,4,0,0},{0,0,0,0}}));
	ASSERT(compareTableau(combineCases_haut({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}), {{4,0,0,2},{2,2,0,0},{0,8,4,0},{2,0,0,4}})); 
	ASSERT(compareTableau(deplacementHaut({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}), {{4,2,4,2},{2,8,0,4},{0,0,0,0},{0,0,0,0}}));
	ASSERT(compareTableau(flip_horizontal({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}), {{2,4,0,4},{0,4,4,0},{2,2,0,0},{2,0,0,2}}));
	ASSERT(compareTableau(deplacementBas({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}), {{0,0,0,0},{0,0,0,0},{2,2,0,2},{4,8,4,4}}));
	ASSERT(compareTableau(deplacement({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}, 1), deplacementHaut({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}})));
	ASSERT(compareTableau(deplacement({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}, 2), deplacementBas({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}})));
	ASSERT(compareTableau(deplacement({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}, 3), deplacementGauche({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}})));
	ASSERT(compareTableau(deplacement({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}}, 4), deplacementDroite({{2,0,0,2},{2,2,0,0},{0,4,4,0},{2,4,0,4}})));	
}

