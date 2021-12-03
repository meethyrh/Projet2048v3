#include <string>  
#include <iostream> 
#include <vector>
#include <ncurses.h>
#include <assert.h>
using namespace std;
typedef vector<vector<int> > Plateau;
#include "Jeu2048.h"

int main(){

    initscr();
    keypad(stdscr, TRUE);

//TEST SI LE TERMINAL SUPPORT LES COULEURS
    if (has_colors() == FALSE){
        endwin();
        printf("Le terminal ne supporte pas les Couleurs\n ");
        exit(1);
    }

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

//DEBUT DU JEU AVEC PLATEAU INITIAL
    Plateau plateau = plateauInitial(plateauVide());
    string affichage = dessine(plateau);
    printw("Pour commencer une partie, appuyez sur Entré");
    refresh();
    getch();
    attron(COLOR_PAIR(1));
    printw(affichage.c_str());
    attron(COLOR_PAIR(1));
    refresh();
    int direction;
    bool winCondition = estGagnant(plateau);
    bool loseCondition = estTermine(plateau);

//LES TOURS DU JEU
    while (winCondition == false and loseCondition == false){
        direction = getch();
        clear();
        if (direction == KEY_UP){
            plateau = deplacement(plateau, 1);
            affichage = dessine(plateau);
            attron(COLOR_PAIR(1));
            printw(affichage.c_str());
            attron(COLOR_PAIR(1));
            refresh();
        } if (direction == KEY_DOWN){
            plateau = deplacement(plateau, 2);
            affichage = dessine(plateau);
            attron(COLOR_PAIR(1));
            printw(affichage.c_str());
            attron(COLOR_PAIR(1));
            refresh();
        } if (direction == KEY_LEFT){
            plateau = deplacement(plateau, 3);
            affichage = dessine(plateau);
            attron(COLOR_PAIR(1));
            printw(affichage.c_str());
            attron(COLOR_PAIR(1));
            refresh();
        } if (direction == KEY_RIGHT){
            plateau = deplacement(plateau, 4);
            affichage = dessine(plateau);
            attron(COLOR_PAIR(1));
            printw(affichage.c_str());
            attron(COLOR_PAIR(1));
            refresh();
        }
        winCondition = estGagnant(plateau);
        loseCondition = estTermine(plateau);
    } 
    if(estGagnant(plateau) == true){
        attron(COLOR_PAIR(2));
        printw("You defeated 2048 \nAppuyez sur F1 pour quitté\nCMD + fn + f1 sur mac");
        attron(COLOR_PAIR(2));
    } else {
        attron(COLOR_PAIR(2));
        printw("Vous avez perdu. \nAppuyez sur F1 pour quitté \nCMD + fn + f1 sur mac");
        attron(COLOR_PAIR(2));
    } refresh();

    int quitButton;
    quitButton = getch();
    while(quitButton != KEY_F(1)){
        quitButton = getch();
    }
    endwin();
    return 0;
}