#include <string>  
#include <iostream> 
#include <sstream>
#include <vector>
#include <cstdlib>
#include <random>
using namespace std;
typedef vector<vector<int> > Plateau;

/** Des fonctions peuvent être ajoutés à ce fichier si besoin est 
 * (fonctions pour mettre à jour le score par exemple)
**/

/** génère un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide
 **/
Plateau plateauVide(){
    Plateau plateau = {{0,0,0,0},
                       {0,0,0,0},
                       {0,0,0,0},
                       {0,0,0,0}};
    return plateau;
}



/** genere aleatoirement un nombre dans un interval [a,b]
 @param a representant le plus petit élément de l'interval
 @param b représentant le plus grand élément de l'interval
 @return un entier compris entre les bornes de l'interval
**/ 
int NumberGenerator(int a, int b){
    int nRand ;
    nRand= a + (int)((float)rand() * (b-a+1) / (RAND_MAX-1)) ;
    return nRand;
}

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 * @param aucun
 * @return 2 ou 4
 **/
int tireDeuxOuQuatre(){
    int probaNbr = NumberGenerator(1,10);
    if(probaNbr == 10){
        return 4;
    } else {
        return 2; 
    }
}



/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 * @param plateau le plateau du jeu 
 * @return un Plateau en début de jeu
 * note: ce code ne marche que pour les plateau de 2048 classics; 
 * soit, des plateau avec des lignes de la même longueur;
 **/
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



//BETA: Il reste encore le problem du decalage des colonnes lorsque les nombres sont trop grands.                                   
/** affiche un Plateau
 * @param p le Plateau
 * @return une chaine de caractères représentant un dessin du plateau du jeu
 **/
string dessine(Plateau plateau){
    stringstream ligne;
    for(int i = 0; i < plateau.size(); i++){
        for(int j = 0; j < plateau[i].size(); j++){
            if(j < 3){
                ligne << "* "<< stew (4) << plateau[i][j] << " ";  
            } else if (j == 3){
                ligne << "* "<< stew (4) << plateau[i][j] << " " << endl << "***************\n";
            }  
        }
    } return "\n***************\n" + ligne.str(); 
}

/**
 * une fonction qui combine deux cases cote a cote d'un tableau si les deux cases sont identiques.
 * note: cette fonction ne marche que pour la combinaison de cases apres deplacement a gauche;
 * car la case la plus a gauche va etre comparer avec celle a sa droite. 
 * @param plateau tableau représentant le plateau du jeu
 * @return un plateau avec les cases qui etaient cote a cote combiné et prennant la place de la case qui etait a gauche
 * */ 
Plateau combineCases_gauche(Plateau plateau){
    for(int i = 0; i < plateau.size(); i++){
        for(int j = 0; j < plateau[i].size(); j++){
            if(plateau[i][j] > 0 and plateau[i][j] == plateau[i][j+1]){
                plateau[i][j] = plateau[i][j] + plateau[i][j+1];
                plateau[i][j+1] = 0;
            }
        }
    } return plateau;
}


/** deplace les tuiles d'un plateau vers la gauche sans les combiner
 * @param plateau Le Plateau
 * @return Le plateau deplacé vers la gauche
 * */
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



/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/
Plateau deplacementGauche(Plateau plateau){
    plateau = deplacementGauche_sansCombi(plateau);
    plateau = combineCases_gauche(plateau);
    plateau = deplacementGauche_sansCombi(plateau);
    return plateau;
}

/** une fonction qui retourne le tableau sur lui pour que la gauche devienne la droite et vice-versa
 * @param plateau le plateau du jeu
 * @return le plateau retourné du jeu
 * */
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
                                       
/** déplace les tuiles d'un Plateau vers la droite et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la droite
 **/
Plateau deplacementDroite(Plateau plateau){
    plateau = flip_vertical(plateau);
    plateau = deplacementGauche(plateau);
    plateau = flip_vertical(plateau);
    return plateau;
}


/** déplace les tuiles d'un Plateau vers le haut sans combiner les cases.
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le haut
 **/
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

/** Une fonction qui combine les tuiles cote a cote de haut en bas et 
 * remplace la tuile du haut par cette fusion
 * @param plateau le Plateau
 * @return un plateau une fois les cases combiné
 * */
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

/** déplace les tuiles d'un Plateau vers le haut et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le haut
 **/
Plateau deplacementHaut(Plateau plateau){
    plateau = deplacementHaut_sansCombi(plateau);
    plateau = combineCases_haut(plateau);
    plateau = deplacementHaut_sansCombi(plateau);
    return plateau;
}



/** flip_horizontal
 * definition: une fonction qui flip le plateau sur un axe horizontal
 * @param plateau de type plateau 
 * @return le plateau retourner sur un axe horizontal
 * note: tab_flipH = tableau fliped sur l'axe Horizontal
 * */
Plateau flip_horizontal(Plateau plateau){
    Plateau plat_flipH = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    //note: tab_flipH = tableau fliped sur l'axe Horizontal
    int k = plateau.size() - 1;
    for(int i = 0; i < plateau.size(); i++){
        plat_flipH[i] = plateau[k];
        k-=1;
    } return plat_flipH;
}

/** déplace les tuiles d'un Plateau vers le bas et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le bas
 **/
Plateau deplacementBas(Plateau plateau){
    plateau = flip_horizontal(plateau);
    plateau = deplacementHaut(plateau);
    plateau = flip_horizontal(plateau);
    return plateau;
}


/**
 * Fonction qui ajoute un nombre 2 ou 4 sur une case vide aleatoire du tableau 
 * @param plateau le plateau
 * @return un plateau avec un nouveau 2 ou un 4 sur une case qui etait vide
 * Note: ce code n'est pas adapter a un 2048 avec des lignes de taille differentes. 
 * (si ce type de 2048 existe)
 * */
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


/** déplace les tuiles d'un Plateau dans la direction donnée et 
 * génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le Plateau
 *  @param direction la direction
 *  @return le Plateau déplacé dans la direction
 **/
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



/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si le plateau est vide, false sinon
 **/
bool estTermine(Plateau plateau){
    for(int i = 0; i < plateau.size(); i++){
        for(int j = 0; j < plateau[i].size(); j++){
            if(plateau[i][j] > 0){
                return false;
            }
        }
    } return true;
}



/** permet de savoir si une partie est gagnée
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau plateau){
    for (int i = 0; i < plateau.size(); i++){
        for (int j = 0; j < plateau.size(); j++){
            if(plateau[i][j] == 2048){
                return true; 
            }
        }
    } return false;
    
}

int main() {
    Plateau plateau = plateauInitial(plateauVide());
    int direction;
    int h = 1;
    int b = 2;
    int g = 3;
    int d = 4;
    cout << dessine(plateau) << endl; 
    while (estGagnant(plateau) == false or estTermine(plateau) == false){
        cout << "Veuillez saisir une direction entre h, b, g, ou d: "; 
        cin >> direction;
        cout << endl;
        plateau = deplacement(plateau, direction);
        cout << dessine(plateau) << endl;
    }
    return 0;
}
