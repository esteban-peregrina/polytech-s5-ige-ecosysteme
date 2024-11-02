#include ".././headers/animal.h"
#include ".././headers/proie.h"
#include ".././headers/predateur.h"
#include ".././headers/lieu.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <time.h>

animal* ajouteAnimalFauneLocale(char type, animal* teteFauneLocale) {
    /*
    En fonction de type, insère une proie ou un prédateur en tete de la faune locale du lieu.
    
    Avertissement : Le nombre d'animaux (proies ou prédateurs) du lieu n'est pas incrémenté ici.
    */

    if (type == '*') { // Proie
        proie* Proie = proie_create();
        Proie->base.suivant = teteFauneLocale;
        return (animal*)(Proie);
    } else { // Prédateur
        predateur* Predateur = predateur_create();
        Predateur->base.suivant = teteFauneLocale;
        return (animal*)(Predateur);
    }
}

void supprimeAnimalFauneLocale(animal* Animal, animal* animalPrecedent) { 
    /*
    Supprime Animal de la faune locale du lieu. 

    Avertissement : Le nombre d'animaux (proies ou prédateurs) du lieu n'est pas décrémenté ici.
    */
    if (animalPrecedent != NULL) { animalPrecedent->suivant = Animal->suivant; }
    if (Animal->type == '*') { // Proie
        proie_destroy((proie**)&Animal);
    } else { // Predateur
        predateur_destroy((predateur**)&Animal);
    }
}

void actualiserLieu(lieu* Lieu) {
    /*
    Précondition : Lieu != NULL

    Actualise le lieu (naissance, décès) en fonction de la faune locale.
    */

    int indicateurCoupleProie = 0;
    int proiesAFaireNaitre = 0;

    int indicateurCouplePredateur = 0;
    int predateursAFaireNaitre = 0;
    int proiesNonDevorees = Lieu->nbProies;

    int hasPredator = 0;

    // Application des décès par fatigue, dénombrement des décès par chasse, dénombrement des naissances, met à jour la trajectoire des animaux
    animal* courant = Lieu->teteFauneLocale;
    if (courant == NULL) { return; } // Faune locale vide, rien à faire dans ce lieu 
    
    animal* precedent = NULL;
    while (courant != NULL) {
        depenseEnergieAnimal(courant); 
        if (courant->energie <= 0) { // L'animal meurt de fatigue
            if (courant->type == '*') {
                Lieu->nbProies--;
                proiesNonDevorees--; // Les prédateurs mangeront évidemment celles qui sont encore en vie
            } else {
                Lieu->nbPredateurs--;
            }
            animal* temp = courant->suivant;
            if (courant == Lieu->teteFauneLocale) { Lieu->teteFauneLocale = temp; }
            supprimeAnimalFauneLocale(courant, precedent); 
            courant = temp;
        } else { // L'animal reste en vie
            changeDirectionAnimal(courant); // On met a jour sa trajectoire
            if (courant->type == 'O') { // Prédateur
                hasPredator = 1;

                // Dénombrement des naissances de prédateurs
                indicateurCouplePredateur++;
                if (indicateurCouplePredateur == 2) { // Si un couple de predateur existe (on ne propose qu'une reproduction par couple)
                    if (donneNaissanceAnimal(courant)) {
                        predateursAFaireNaitre++;
                        indicateurCouplePredateur = 0;   
                    } else {
                        indicateurCouplePredateur--;
                    }
                }

                // Dénombrement des décès de proies par chasse
                if ((proiesNonDevorees > 0) && (devoreProie((predateur*)courant))) { // (Reconversion en prédateur)
                    proiesNonDevorees--;
                }
                
            } else { // Proie
                // Dénombrement des naissances de proies
                indicateurCoupleProie++;
                if (indicateurCoupleProie == 2) { // Si un couple de proie existe (on ne propose qu'une reproduction par couple)
                    if (donneNaissanceAnimal(courant)) {
                        proiesAFaireNaitre++;
                        indicateurCoupleProie = 0;   
                    } else {
                        indicateurCoupleProie--;
                    }
                }
            }
            // Continuer le parcours
            precedent = courant;
            courant = courant->suivant;
        } 
    }

    // Naissances des proies
    for (int i = 0; i < proiesAFaireNaitre; i++) {
        Lieu->teteFauneLocale = ajouteAnimalFauneLocale('*', Lieu->teteFauneLocale);
        Lieu->nbProies++;
    }

    // Naissances des prédateurs
    for (int i = 0; i < predateursAFaireNaitre; i++) {
        Lieu->teteFauneLocale = ajouteAnimalFauneLocale('O', Lieu->teteFauneLocale);
        Lieu->nbPredateurs++;
    }

    // Les prédateurs adultes dévorent les proies adultes A CHANGER POUR "CIBLER" LA CHASSE --> DEUX LISTES DANS UN LIEU (pour savoir ou chercher les proies) !
    courant = Lieu->teteFauneLocale;
    if (courant == NULL) { return; }  // Toute la faune locale est morte de fatigue, rien à faire dans ce lieu 

    if (hasPredator) {
        int proiesADevorer = Lieu->nbProies - proiesNonDevorees;
        precedent = NULL;

        int proiesDevorees = 0;
        while (courant != NULL && (proiesDevorees < proiesADevorer)) {
            if (courant->type == '*') { // On dévore la proie
                animal* temp = courant->suivant;
                if (courant == Lieu->teteFauneLocale) { Lieu->teteFauneLocale = temp; }
                supprimeAnimalFauneLocale(courant, precedent); // La proie est dévorée
                courant = temp; 
                
                Lieu->nbProies--;

                proiesDevorees++;
            } else { // On continu le parcours
                precedent = courant;
                courant = courant->suivant;
            }
        }
    }
    
}