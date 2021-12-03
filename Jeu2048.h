#include <string>  
#include <iostream> 
#include <sstream>
#include <vector>
#include <cstdlib>
#include <random>
using namespace std;
typedef vector<vector<int> > Plateau;

// le score
extern int score;

/** génère un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide
 * une fonction qui devrais marché a chaque fois qu'elle est appellée
 **/
Plateau plateauVide();


/** genere aleatoirement un nombre dans un interval [a,b]
 @param a representant le plus petit élément de l'interval
 @param b représentant le plus grand élément de l'interval
 @return un entier compris entre les bornes de l'interval
 marche a peu près partout.
**/ 
int NumberGenerator(int a, int b);


/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 *  @return un Plateau en début de jeu
 * une fonction qui devrais marcher pour n'importe quel plateau de 2048 non vide et pour lesquels le jeu n'est pas fini 
 **/
Plateau plateauInitial(Plateau plateau);
                         

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre();
                                       
                                       
/** affiche un Plateau
 * @param p le Plateau
 **/
string dessine(Plateau plateau);


/**
 * une fonction qui combine deux cases cote a cote d'un tableau si les deux cases sont identiques.
 * note: cette fonction ne marche que pour la combinaison de cases apres deplacement a gauche;
 * car la case la plus a gauche va etre comparer avec celle a sa droite. 
 * @param plateau tableau représentant le plateau du jeu
 * @return un plateau avec les cases qui etaient cote a cote combiné et prennant la place de la case qui etait a gauche
 * */ 
Plateau combineCases_gauche(Plateau plateau);

/** deplace les tuiles d'un plateau vers la gauche sans les combiner
 * @param plateau Le Plateau
 * @return Le plateau deplacé vers la gauche
 * */
Plateau deplacementGauche_sansCombi(Plateau plateau);
    

/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/
Plateau deplacementGauche(Plateau plateau);

/** une fonction qui retourne le tableau sur lui pour que la gauche devienne la droite et vice-versa
 * @param plateau le plateau du jeu
 * @return le plateau retourné du jeu
 * */
Plateau flip_vertical(Plateau plateau);
                                       
/** déplace les tuiles d'un Plateau vers la droite et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la droite
 **/
Plateau deplacementDroite(Plateau plateau);

/** déplace les tuiles d'un Plateau vers le haut sans combiner les cases.
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le haut
 **/
Plateau deplacementHaut_sansCombi(Plateau plateau);

/** Une fonction qui combine les tuiles cote a cote de haut en bas et 
 * remplace la tuile du haut par cette fusion
 * @param plateau le Plateau
 * @return un plateau une fois les cases combiné
 * */
Plateau combineCases_haut(Plateau plateau);

/** déplace les tuiles d'un Plateau vers le haut et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le haut
 **/
Plateau deplacementHaut(Plateau plateau);

/** flip_horizontal
 * definition: une fonction qui flip le plateau sur un axe horizontal
 * @param plateau de type plateau 
 * @return le plateau retourner sur un axe horizontal
 * note: tab_flipH = tableau fliped sur l'axe Horizontal
 * */
Plateau flip_horizontal(Plateau plateau);


/** déplace les tuiles d'un Plateau vers le bas et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le bas
 **/
Plateau deplacementBas(Plateau plateau);


//NOTE IMPORTANT: POUR CETTE FONCTION J'AI CHANGÉ LE TYPE int DE direction EN string
/** déplace les tuiles d'un Plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le Plateau
 *  @param direction la direction
 *  @return le Plateau déplacé dans la direction
 * NOTE: on aurait pu utiliser la fonction plateauInitial(plateau) mais j'ai voulu directement implanté la fonction
 * pour génerer des nombres aléatoires après un déplacement pour garder le "contrôle" sur mon code
 **/
Plateau deplacement(Plateau plateau, int direction);



/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si le plateau est vide, false sinon
 **/
bool estTermine(Plateau plateau);



/** permet de savoir si une partie est gagnée
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau plateau);

/** Teste toutes le fonction du jeu sauf les fonctions qui fond appelle a des nombres aléatoire.**/
void test_all_func();

/**
 * @brief compare deux tableau 2D et renvoie vrai si 
 * les cases de mêmes indices i et j portent les mêmes valeurs
 * @param plateau un plateau de jeu 2048
 * @param plateau un autre plateau de jeu 2048
 * @return true si les plateaux sont égaux
 * @return false si elles ne le sont pas.
 */
bool compareTableau(Plateau plateau1, Plateau plateau2);

struct plateauS
{
    Plateau plateau;
    int score;
};