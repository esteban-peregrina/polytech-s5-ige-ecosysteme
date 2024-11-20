#include ".././headers/animal.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <time.h>

animal* animal_create() {
    /*
    Renvoie l'adresse de l'animal instancié.
    */

    animal* Animal = NULL;
    Animal = malloc(sizeof(animal)); // Si on déréférence le pointeur Animal avec *Animal, on aurait sizeof(NULL) (Corriger les exercices précédents !)
    if (Animal == NULL) { exit(EXIT_FAILURE); }
    
    Animal->energie = ENERGIE;
    Animal->depenseEnergie = depenseEnergieAnimal;

    Animal->assurance = ASSURANCE;
    Animal->changeDirection = changeDirectionAnimal;
    Animal->aMigre = 0;
    Animal->estAccouple = 0;

    return Animal;
}

void animal_destroy(animal* Animal) {
    /*
    Détruit l'animal.
    */

    free(Animal);
    Animal = NULL;
}

void depenseEnergieAnimal(animal* self) {
    /*
    Dépense l'énergie de l'animal en fonction de son métabolisme.
    */

    self->energie -= self->metabolisme;
    self->estAccouple = 0;
}

void changeDirectionAnimal(animal* self) {
    /*
    Modifie la diretion de déplacement de l'animal en fonction de son assurance.
    */

    float random_value = (float)rand() / RAND_MAX;
    int ancienneDirection = self->direction;
    
    if (random_value < self->assurance) {
        while (self->direction == ancienneDirection) {
            self->direction = rand()%4; 
        }
    } 
}

    
    

    