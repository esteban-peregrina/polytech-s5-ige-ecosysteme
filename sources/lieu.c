#include ".././headers/animal.h"
#include ".././headers/proie.h"
#include ".././headers/predateur.h"
#include ".././headers/lieu.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <time.h>

animal* ajouteAnimalFauneLocale(int type, animal* teteFauneLocale) {
    /*
    En fonction de type, insère une proie ou un prédateur en tete de la faune locale du lieu et renvoie la nouvelle tete.
    */

    if (type == ANIMAL_TYPE_PROIE) {
        proie* Proie = proie_create();
        Proie->base.suivant = teteFauneLocale;
        return (animal*)(Proie);
    } else  { // if (type == ANIMAL_TYPE_PREDATEUR) 
        predateur* Predateur = predateur_create();
        Predateur->base.suivant = teteFauneLocale;
        return (animal*)(Predateur);
    }
}

animal* accouplementAnimal(animal* pere, animal* mere, animal* teteFauneLocale) {
    /*
    En fonction de la fertilite des parents, fait naitre un animal et renvoie la nouvelle valeur de teteFauneLocale[espece].
    */

    if (pere->estAccouple || mere->estAccouple) { 
        return teteFauneLocale; 
    } else {
        srand(time(NULL));
        float random_value = (float)rand() / RAND_MAX;
        
        if (random_value < pere->fertilite) { // Père ok
            pere->depenseEnergie(pere);
            random_value = (float)rand() / RAND_MAX;
            if (random_value < mere->fertilite) { // Mère ok
                mere->depenseEnergie(mere);

                pere->estAccouple = 1;
                mere->estAccouple = 1;
                
                if (pere->typeID == ANIMAL_TYPE_PROIE) { 
                    proie* Proie = proie_create();
                    Proie->base.suivant = teteFauneLocale;
                    return (animal*)(Proie);
                } else if (pere->typeID == ANIMAL_TYPE_PREDATEUR) { 
                    predateur* Predateur = predateur_create();
                    Predateur->base.suivant = teteFauneLocale;
                    return (animal*)(Predateur);
                }

            }
        }
        return teteFauneLocale;
    }

   
    
}

void supprimeAnimalFauneLocale(animal* Animal, animal* animalPrecedent) { 
    /*
    Supprime Animal de la faune locale du lieu. 

    Avertissement : Le nombre d'animaux (proies ou prédateurs) du lieu n'est pas décrémenté ici.
    */
    if (animalPrecedent != NULL) { animalPrecedent->suivant = Animal->suivant; }
    if (Animal->typeID == ANIMAL_TYPE_PROIE) { // Proie
        proie_destroy((proie**)&Animal);
    } else if (Animal->typeID == ANIMAL_TYPE_PREDATEUR) { // Predateur
        predateur_destroy((predateur**)&Animal);
    }
}

void actualiserLieu(lieu* Lieu) {
    /*
    Précondition : Lieu != NULL

    Actualise le lieu (naissance, décès) en fonction de la faune locale.
    */

    // Application des décès par fatigue, dénombrement des décès par chasse, dénombrement des naissances, met à jour la trajectoire des animaux
    for (int espece = 0; espece < NOMBRE_ESPECES; espece++) {
        animal* courant = Lieu->tetesFaunesLocales[espece];
        if (courant != NULL) { // Faune locale non vide
            animal* precedent = NULL; 
            while (courant != NULL) { // Parcour de la faune associée à l'espèce
                depenseEnergieAnimal(courant);
                if (courant->energie <= 0) { // L'animal meurt de fatigue
                    animal* temp = courant->suivant;
                    if (courant == Lieu->tetesFaunesLocales[espece]) { Lieu->tetesFaunesLocales[espece] = temp; }
                    supprimeAnimalFauneLocale(courant, precedent); 
                    courant = temp;
                } else { // L'animal reste en vie
                    changeDirectionAnimal(courant); // On met a jour sa trajectoire

                    // Évènements d'espèce
                    if (espece == ANIMAL_TYPE_PROIE) {
                        // Rien à faire (pour le moment ?)
                    } else if (espece == ANIMAL_TYPE_PREDATEUR) {
                        Lieu->tetesFaunesLocales[ANIMAL_TYPE_PROIE] = (animal*)predateurChasseProie((predateur*)courant, (proie*)Lieu->tetesFaunesLocales[ANIMAL_TYPE_PROIE]); // Cast de proie inutile mais sert à la lisibilité.
                    }

                    // Naissances génériques
                    if ( (precedent != NULL) ) {
                        Lieu->tetesFaunesLocales[espece] = accouplementAnimal(precedent, courant, Lieu->tetesFaunesLocales[espece]);
                    }

                    // Continuer le parcours
                    precedent = courant;
                    courant = courant->suivant;
                }
            } 
        }
    }
}