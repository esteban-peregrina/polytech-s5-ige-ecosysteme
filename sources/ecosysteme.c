#include ".././headers/animal.h"
#include ".././headers/proie.h"
#include ".././headers/predateur.h"

#include ".././headers/lieu.h"
#include ".././headers/ecosysteme.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <time.h>
#include <unistd.h>

#define DEBUGGING 1


void peupleEcosysteme(lieu Ecosysteme[TAILLE][TAILLE]) {
    /*
    Peuple un ecosystème aléatoirement.
    */
    int expression = -1;
    //expression = DEBUGGING; // Commenter en utilisation normale
    switch (expression)
    {
    case 1:
        for (int x = 0; x < TAILLE; x++) {
            for (int y = 0; y < TAILLE; y++) {
                for (int espece = 0; espece < NOMBRE_ESPECES; espece++) {
                    Ecosysteme[x][y].tetesFaunesLocales[espece] = NULL;
                    if (x == 0 && y == 0) {
                        Ecosysteme[x][y].tetesFaunesLocales[espece] = ajouteAnimalFauneLocale(espece, Ecosysteme[x][y].tetesFaunesLocales[espece]);
                    }
                }
            }
        }
        break;
    
    default:
        for (int x = 0; x < TAILLE; x++) {
            for (int y = 0; y < TAILLE; y++) {
                for (int espece = 0; espece < NOMBRE_ESPECES; espece++) {
                    Ecosysteme[x][y].tetesFaunesLocales[espece] = NULL;
                    for (int i = 0; i < (rand()%BASEPOPULATIONMAX)/2; i++) {
                        Ecosysteme[x][y].tetesFaunesLocales[espece] = ajouteAnimalFauneLocale(espece, Ecosysteme[x][y].tetesFaunesLocales[espece]);
                    }
                }
            }
        }
    }
    
}

void migrationAnimal(lieu Ecosysteme[TAILLE][TAILLE], int x, int y) {
    /*
    Réalise la migration des animaux du lieu Ecosysteme[x][y]
    */

    for (int espece = 0; espece < NOMBRE_ESPECES; espece++) {
        animal* courant = Ecosysteme[x][y].tetesFaunesLocales[espece];
        if (courant != NULL) { // Faune locale associée à l'espèce non vide
            animal* precedent = NULL;
            while (courant != NULL) {
                if (!(courant->aMigre)) {
                    courant->aMigre = 1;

                    int xNew = x;
                    int yNew = y;
                    
                    if (courant->direction == ANIMAL_DIRECTION_HAUT) { 
                        yNew = (y == 0) ? y + 1 : y - 1;
                    } else if (courant->direction == ANIMAL_DIRECTION_DROITE) {
                        xNew = (x == TAILLE - 1) ? x - 1 : x + 1;
                    } else if (courant->direction == ANIMAL_DIRECTION_BAS) {
                        yNew = (y == TAILLE - 1) ? y - 1 : y + 1;
                    } else { // Gauche
                        xNew = (x == 0) ? x + 1 : x - 1;
                    }
                    courant->changeDirection(courant);
                    
                    animal* teteFauneLocaleEspeceNouveauLieu = Ecosysteme[xNew][yNew].tetesFaunesLocales[espece];
                    
                    if (precedent == NULL) { 
                        Ecosysteme[x][y].tetesFaunesLocales[espece] = courant->suivant; 
                    } else {
                        precedent->suivant = courant->suivant;
                    }
                    courant->suivant = teteFauneLocaleEspeceNouveauLieu;
                    Ecosysteme[xNew][yNew].tetesFaunesLocales[espece] = courant;

                    courant = (precedent == NULL) ? Ecosysteme[x][y].tetesFaunesLocales[espece] : precedent->suivant; 
                } else {
                    courant->aMigre = 0;
                    precedent = courant;
                    courant = courant->suivant;
                }
            }
        }
    }
}    

void actualiserEcosysteme(lieu Ecosysteme[TAILLE][TAILLE]) {
    /*
    Actualise l'ecosysteme.
    */

    int indicateurVie = 1;
    int compteur = 0;
    while(indicateurVie) {
        // Pour chaque lieu de l'ecosysteme, calcul les décès et les naissances en fonction de sa faune locale.
        indicateurVie = 0;
        printf("\nUpdate %d :\n\n", compteur);
        afficherEcosysteme(Ecosysteme);
        for (int x = 0; x < TAILLE; x++) {
            for (int y = 0; y < TAILLE; y++) {
                for (int espece = 0; espece < NOMBRE_ESPECES; espece++) { 
                    if (Ecosysteme[x][y].tetesFaunesLocales[espece] != NULL) { indicateurVie = 1; }
                }
                actualiserLieu(&Ecosysteme[x][y]); // Prend l'adresse du lieu
                
            }
        }

        // Pour chaque lieu de l'ecosysteme, effectue les migrations de sa faune locale.
        for (int x = 0; x < TAILLE; x++) {
            for (int y = 0; y < TAILLE; y++) {
                migrationAnimal(Ecosysteme, x, y); // Prend l'adresse de l'ecosysteme
            }
        }
        usleep(PERIOD);
        compteur++;
    }

    printf("Tout le monde est mort !\n");
}

void afficherEcosysteme(lieu Ecosysteme[TAILLE][TAILLE]) { 
    /*
    Affiche l'ecosysteme.
    */

   for (int x = 0; x < TAILLE; x++) {
        for (int y = 0; y < TAILLE; y++) {
            for (int espece = 0; espece < NOMBRE_ESPECES; espece++) {
                animal* courant = Ecosysteme[x][y].tetesFaunesLocales[espece];
                if (courant == NULL) { printf("-"); }
                while (courant != NULL) {
                    printf("%c", courant->forme);
                    courant = courant->suivant;
                }
            }
            printf("\t\t\t");
        }
        printf("\n");
    }
}
