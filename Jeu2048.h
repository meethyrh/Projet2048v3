#include <iostream> 
#include <vector>
#include <cstdlib>
using namespace std;
typedef vector<vector<int> > Plateau;

//une structure de donnée formé d'un tableau 2D associé a un score.
typedef struct {
    Plateau plateau;
    int score;
} PS;

/** génère un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide
 * une fonction qui devrais marché a chaque fois qu'elle est appellée
 TESTÉ
 **/
Plateau plateauVide();


/** genere aleatoirement un nombre dans un interval [a,b]
 @param a representant le plus petit élément de l'interval
 @param b représentant le plus grand élément de l'interval
 @return un entier compris entre les bornes de l'interval
 TESTÉ 
**/ 
int NumberGenerator(int a, int b);


/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 *  @return un Plateau en début de jeu
 * une fonction qui devrais marcher pour n'importe quel plateau de 2048 non vide et pour lesquels le jeu n'est pas fini 
 (DONC TANT QU'IL RESTE DES CASES LIBRES) 
 * TESTÉ UNIQUEMENT DANS CES CAS
 **/
Plateau plateauInitial(Plateau plateau);
                         

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 * TESTÉ
 **/
int tireDeuxOuQuatre();
                                       
                                       
/** affiche un Plateau
 * @param p le Plateau
 * TESTÉ (LE TEST NE COUVRE PAS TOUTES LES POSSIBILITÉ D'AFFICHAGE 
 MAIS TESTE UNIQUEMENT SI LA FONCTION RENVOIE AU MOIN 3 CARACTÈRES)
 * cette fonction affiche mal les plateau autres que 4x4
 **/
string dessine(Plateau plateau);


/**
 * une fonction qui combine deux cases cote a cote d'un tableau si les deux cases sont identiques.
 * note: cette fonction ne marche que pour la combinaison de cases apres deplacement a gauche;
 * car la case la plus a gauche va etre comparer avec celle a sa droite. 
 * @param plateau une structure de données représentant le plateau du jeu et son score associé
 * @return une structure composé d'un plateau avec les cases côte à côtes combinées et la combinaison prennant 
 * la place de la case qui etait à gauche ainsi que d'un score associé au plateau s'ajoutant à la valeur de la combinaison des cases  
 * TESTÉ SUR 4 CAS 
 * */ 
PS combineCases_gauche(PS plateau);

/** deplace les tuiles d'un plateau vers la gauche sans les combiner
 * @param plateau Le Plateau
 * @return Le plateau deplacé vers la gauche
 * TESTÉ SUR 4 CAS
 * */
Plateau deplacementGauche_sansCombi(Plateau plateau);
    

/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau une structure de données représentant le plateau du jeu et son score associé
 *  @return La structure de donnée avec le nouveau plateau et le score lui étant associé
 * TESTÉ SUR 4 CAS
 **/
PS deplacementGauche(PS plateau);

/** une fonction qui retourne le tableau sur lui pour que la gauche devienne la droite et vice-versa
 * @param plateau le plateau du jeu
 * @return le plateau retourné du jeu
 * TESTÉ 
 * */
Plateau flip_vertical(Plateau plateau);
                                       
/** déplace les tuiles d'un Plateau vers la droite et les combine si possible
 *  @param plateau une structure de données représentant le plateau du jeu et son score associé
 *  @return Une structure de données avec le nouveau plateau et le score lui étant associé
 * TESTÉ SUR 4 CAS
 **/
PS deplacementDroite(PS plateau);

/** déplace les tuiles d'un Plateau vers le haut sans combiner les cases.
 *  @param plateau une structure de données représentant le plateau du jeu et son score associé
 *  @return le Plateau une fois déplacé vers le haut
 * TESTÉ SUR 4 CAS
 **/
Plateau deplacementHaut_sansCombi(Plateau plateau);

/** Une fonction qui combine les tuiles cote a cote de haut en bas et 
 * remplace la tuile du haut par cette fusion
 * @param plateau une structure de données représentant le plateau du jeu et son score associé
 * @return une structure composé d'un plateau avec les cases côte à côtes (haut bas) combinées et la combinaison prennant 
 * la place de la case qui était en haut ainsi que d'un score associé au plateau s'ajoutant à la valeur de la combinaison des cases
 * TESTÉ SUR 4 CAS
 * */
PS combineCases_haut(PS plateau);

/** déplace les tuiles d'un Plateau vers le haut et les combine si possible
 *  @param plateau une structure de données représentant le plateau du jeu et son score associé
 *  @return une strucure de données avec le nouveau plateau et son score associé
 * TESTÉ SUR 4 CAS
 **/
PS deplacementHaut(PS plateau);

/** flip_horizontal
 * definition: une fonction qui flip le plateau sur un axe horizontal
 * @param plateau Le plateau 
 * @return le plateau retourner sur un axe horizontal
 * note: tab_flipH = tableau fliped sur l'axe Horizontal
 * TESTÉ
 * */
Plateau flip_horizontal(Plateau plateau);


/** déplace les tuiles d'un Plateau vers le bas et les combine si possible
 *  @param plateau le Plateau
 *  @return Une structure de données avec le nouveau plateau et le score lui étant associé
 * TESTÉ SUR 4 CAS
 **/
PS deplacementBas(PS plateau);


//NOTE IMPORTANT: POUR CETTE FONCTION J'AI CHANGÉ LE TYPE int DE direction EN string
/** déplace les tuiles d'un Plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le Plateau
 *  @param direction la direction
 *  @return Une structure de données composé du plateau ayant été déplacé et du score lui étant associé
 * NOTE: on aurait pu utiliser la fonction plateauInitial(plateau) mais j'ai voulu directement implanté la fonction
 * pour génerer des nombres aléatoires après un déplacement pour garder le "contrôle" sur mon code
 * TESTÉ EN COMPARANT UN PLATEAU DÉPLACÉ UNIQUEMENT ET UN PLATEAU DÉPLACÉ AUQUEL LA FONCTION nouvelleCase AURAIT ÉTÉ AJOUTÉ.
 **/
PS deplacement(PS plateau, int direction);

/** @brief une fonction qui ajoute un 2 ou un 4 sur une des cases vide d'un tableau
* @param plateau Le plateau de jeu
* @return un nouveau plateau avec un 2 ou un 4 en plus dans l'une des cases précédement vide
TESTÉ MAIS NE COUVRE QU'UNE PARTIE DES POSSIBILITÉES. ON NE TESTE QUE LA DIFFÉRENCE ENTRE 
UN PLATEAU AVANT ET APRÈS L'APPEL DE LA FONCTION. 
*/
Plateau nouvelleCase(Plateau plateau);


/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si le plateau est vide, false sinon
 * TESTÉ SUR 4 CAS
 **/
bool estTermine(Plateau plateau);



/** permet de savoir si une partie est gagnée
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 * TESTÉ
 **/
bool estGagnant(Plateau plateau);

/** Teste toutes le fonction du jeu sauf les fonctions qui fond appelle a des nombres aléatoire.
**/
void test_all_func();

/**
 * @brief compare deux tableau 2D et renvoie vrai si 
 * les cases de mêmes indices i et j portent les mêmes valeurs
 * @param plateau un plateau de jeu 2048
 * @param plateau un autre plateau de jeu 2048
 * @return true si les plateaux sont égaux
 * @return false si elles ne le sont pas.
 * TESTÉ MEME TEMPS QUE TOUTES LES AUTRES FONCTIONS DANS LE JUPYTER HUB 
 */
bool compareTableau(Plateau plateau1, Plateau plateau2);

/**
* @brief teste si la fonction plateau initial possède au moins 2 élements > 0
* @param plateau un plateau initial 
* @return vrai si le plateau possède au moins 2 élements superieures à 0
* @return faux si le plateau n'en possède qu'un ou est vide
* TESTÉ DANS LE JUPYTER HUB 
*/
bool TestPlatoInit(Plateau plateau);

