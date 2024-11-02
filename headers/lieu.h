#ifndef LIEU_H
#define LIEU_H

typedef struct lieu lieu;
struct lieu {
    int nbProies;
    int nbPredateurs;

    animal* teteFauneLocale; // Tete de liste chainée d'animaux (lieu agit comme structure de controle)
};

void supprimeAnimalFauneLocale(animal* Animal, animal* animalPrecedent); // Suppression d'un animal de la faune locale d'un lieu
animal* ajouteAnimalFauneLocale(char type, animal* teteFauneLocale); // Creation d'un animal dans la faune locale d'un lieu

void actualiserLieu(lieu* Lieu); // Compte le nombre de naissances a effectuer, insere les animaux resultants, puis compte le nombre de proie a evorer, supprime le nombre de proies resultants
#endif // LIEU_H