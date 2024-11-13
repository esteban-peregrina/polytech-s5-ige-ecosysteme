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


void peupleEcosysteme(lieu Ecosysteme[TAILLE][TAILLE]) {
    /*
    Peuple un ecosystème aléatoirement.
    */
    
    for (int x = 0; x < TAILLE; x++) {
        for (int y = 0; y < TAILLE; y++) {
            Ecosysteme[x][y].nbProies = 0;
            Ecosysteme[x][y].nbPredateurs = 0;
            Ecosysteme[x][y].teteFauneLocale = NULL;

            int population = rand()%BASEPOPULATIONMAX;
            for (int i = 0; i < population; i++) {
                float random_value = (float)rand() / RAND_MAX;
                if (random_value <= p_predateur) { // Prédateur
                    Ecosysteme[x][y].teteFauneLocale = ajouteAnimalFauneLocale('O', Ecosysteme[x][y].teteFauneLocale);
                    Ecosysteme[x][y].nbPredateurs++;
                } else { // Proie
                    Ecosysteme[x][y].teteFauneLocale = ajouteAnimalFauneLocale('*', Ecosysteme[x][y].teteFauneLocale);
                    Ecosysteme[x][y].nbProies++;
                }
            }
        }
    }
}

void migrationAnimal(lieu Ecosysteme[TAILLE][TAILLE], int x, int y) {  // PAS TERMINE
    /*
    Migre Animal vers le prochain lieu.
    */
    
    animal* courant = Ecosysteme[x][y].teteFauneLocale;
    if (courant == NULL) { return; } // Faune locale vide, rien à faire dans ce lieu 
    
    animal* precedent = NULL;
    while (courant != NULL) {
        if (!(courant->aMigre)) {
            courant->aMigre = 1;

            int xNew = x;
            int yNew = y;
            
            if (courant->direction == 0) { // Haut
                yNew = (y == 0) ? y + 1 : y - 1;
            } else if (courant->direction == 1) { // Droite
                xNew = (x == TAILLE - 1) ? x - 1 : x + 1;
            } else if (courant->direction == 2) { // Bas
                yNew = (y == TAILLE - 1) ? y - 1 : y + 1;
            } else { // Gauche
                xNew = (x == 0) ? x + 1 : x - 1;
            }
            courant->changeDirection(courant);
            
            animal* teteFauneLocaleNouveauLieu = Ecosysteme[xNew][yNew].teteFauneLocale;
            
            if (precedent == NULL) { 
                Ecosysteme[x][y].teteFauneLocale = courant->suivant; 
            } else {
                precedent->suivant = courant->suivant;
            }
            courant->suivant = teteFauneLocaleNouveauLieu;
            Ecosysteme[xNew][yNew].teteFauneLocale = courant;

            courant = (precedent == NULL) ? Ecosysteme[x][y].teteFauneLocale : precedent->suivant; 
        } else {
            precedent = courant;
            courant = courant->suivant;
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
                if (Ecosysteme[x][y].teteFauneLocale != NULL) { indicateurVie = 1; }
                actualiserLieu(&Ecosysteme[x][y]);
                
            }
        }

        // Pour chaque lieu de l'ecosysteme, effectue les migrations de sa faune locale.
        for (int x = 0; x < TAILLE; x++) {
            for (int y = 0; y < TAILLE; y++) {
                migrationAnimal(Ecosysteme, x, y);
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
            animal* courant = Ecosysteme[x][y].teteFauneLocale;
            if (courant == NULL) { printf("-"); }
            while (courant != NULL) {
                printf("%c", courant->type);
                courant = courant->suivant;
            }
            printf("\t\t\t");
        }
        printf("\n");
    }
}
