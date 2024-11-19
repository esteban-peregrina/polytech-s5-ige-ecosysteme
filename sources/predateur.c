#include ".././headers/animal.h"
#include ".././headers/proie.h"
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
    
    Predateur->base.typeID = ANIMAL_TYPE_PREDATEUR;
    Predateur->base.forme = 'O';

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

proie* predateurChasseProie(predateur* self, proie* victime) {
    /*
    En fonction de son appétit, chasse une proie et renvoie la nouvelle valeur de teteFauneLocale[ANIMAL_TYPE_PROIE].
    */

    if (victime == NULL) { return NULL; }

    float random_value = (float)rand() / RAND_MAX;
    
    if (random_value < self->appetit) { // Succès de la chasse
        self->base.energie += victime->base.energie; 
        return (proie*)victime->base.suivant;
    } else { // Echec de la chasse
        self->base.depenseEnergie((animal*)self); 
        return victime;
    }
    return 0;
}