#include ".././headers/animal.h"
#include ".././headers/proie.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <time.h>

proie* proie_create() {
    /*
    Renvoie l'adresse de la proie instanciée.
    */

    proie* Proie = NULL;
    Proie = malloc(sizeof(proie));
    if (Proie == NULL) { exit(EXIT_FAILURE); }

    Proie->base = *animal_create(); // On déréférence l'animal résultant, qui possède déjà une énergie.
    
    Proie->base.typeID = ANIMAL_TYPE_PROIE;

    Proie->base.metabolisme = d_energie_proie;

    Proie->base.fertilite = p_reproduction_proie;

    Proie->base.direction = rand()%4;

    return Proie;

}

void proie_destroy(proie** adresseProie) {
    /*
    Détruit la proie.
    */

    if (*adresseProie != NULL) {
        free(*adresseProie);
        *adresseProie = NULL;
    }
}