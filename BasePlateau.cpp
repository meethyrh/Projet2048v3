#include <iostream> 
#include <vector>
#include <cstdlib>
#include <random>
using namespace std;
typedef vector<vector<int> > Plateau;
#include "Jeu2048.h"

Plateau plateauVide(){
    Plateau plateau = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    return plateau;
}

int NumberGenerator(int a, int b){
    int nRand ;
    nRand= a + (int)((float)rand() * (b-a+1) / (RAND_MAX-1)) ;
    return nRand;
}


int tireDeuxOuQuatre(){
    int probaNbr = NumberGenerator(1,10);
    if(probaNbr == 10){
        return 4;
    } else {
        return 2; 
    }
}

Plateau plateauInitial(Plateau plateau){
    int indiceI = NumberGenerator(0,plateau.size()-1);
    int indiceJ = NumberGenerator(0,plateau[0].size()-1);
                                  
    plateau[indiceI][indiceJ] = tireDeuxOuQuatre();
                                  
    int indiceI2 = NumberGenerator(0,plateau.size()-1);
    int indiceJ2 = NumberGenerator(0,plateau[0].size()-1);   
                                   
    while(indiceI2 == indiceI and indiceJ2 == indiceJ){
        int indiceI2 = NumberGenerator(0,plateau.size()-1);
        int indiceJ2 = NumberGenerator(0,plateau[0].size()-1); 
    }
                                       
    plateau[indiceI2][indiceJ2] = tireDeuxOuQuatre(); 

    return plateau;                                  
}