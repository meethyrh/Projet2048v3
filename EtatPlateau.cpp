#include <string>  
#include <iostream> 
#include <sstream>
#include <vector>
#include <cstdlib>
#include <iomanip>
using namespace std;
typedef vector<vector<int> > Plateau;
#include "Jeu2048.h"

bool estTermine(Plateau plateau){
    for(int i = 0; i < plateau.size(); i++){
        for(int j = 0; j < plateau[i].size(); j++){
            if(plateau[i][j] == 0){
                return false;
            }
            if(j <= 2 and plateau[i][j] == plateau[i][j+1]){
                return false;
            }
            if(i <= 2 and plateau[i][j] == plateau[i+1][j]){
                return false;
            }
        }
    } return true;
}

bool estGagnant(Plateau plateau){
    for (int i = 0; i < plateau.size(); i++){
        for (int j = 0; j < plateau.size(); j++){
            if(plateau[i][j] == 2048){
                return true; 
            }
        }
    } return false;
    
}

string dessine(Plateau plateau){
    stringstream ligne;
    for(int i = 0; i < plateau.size(); i++){
        for(int j = 0; j < plateau[i].size(); j++){
            if(j < plateau[i].size()-1){
                ligne << setw(4) << "*" << setw(4)  << plateau[i][j];  
            } else if (j == plateau[i].size()-1){
                ligne << setw(4) << "*" << setw(4) << plateau[i][j] << setw(4) << "*" << endl << "\n   *********************************\n";
            }  
        }
    }
    return "\n   *********************************\n" + ligne.str(); 
}