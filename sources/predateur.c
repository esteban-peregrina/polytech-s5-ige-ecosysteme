#include ".././headers/animal.h"
#include ".././headers/predateur.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <time.h>

predateur* predateur_create() {
    /*
    Renvoie l'adresse du prédateur instancié.
    */

    predateur* Predateur = NULL;
    Predateur = malloc(sizeof(predateur));
    if (Predateur == NULL) { exit(EXIT_FAILURE); }

    Predateur->base = *animal_create(); // On déréférence l'animal résultant, qui possède déjà une énergie.
    
    Predateur->base.type = 'O';

    Predateur->base.metabolisme = d_energie_predateur;

    Predateur->base.fertilite = p_reproduction_predateur;

    Predateur->base.direction = rand()%4;

    Predateur->appetit = p_manger;

    return Predateur;

}

void predateur_destroy(predateur** adressePredateur) {
    /*
    Détruit le prédateur.
    */
    if (*adressePredateur != NULL) {
        free(*adressePredateur);
        *adressePredateur = NULL;
    }
}

int devoreProie(predateur *self) { // PROBLEME : NE DEVORE PAS UNE PROIE EN PARTICULIER
    /*
    En fonction de son appétit, renvoie 1 si le predateur devore une proie, 0 sinon.

    Avertissement : La fonction ne regarde pas si une proie est disponible !
    */

    float random_value = (float)rand() / RAND_MAX;
    
    if (random_value < self->appetit) {
        self->base.energie++;
        return 1;
    } else {
        self->base.depenseEnergie((animal*)self);
    }
    return 0;
}