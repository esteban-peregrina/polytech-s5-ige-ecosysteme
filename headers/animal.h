#ifndef ANIMAL_H
#define ANIMAL_H

// Constantes globales
#define ENERGIE 10 
#define ASSURANCE 0.5 

typedef struct animal animal;
struct animal {
    char type; // "*" pour une proie, "•" pour un prédateur

    int energie;
    int metabolisme; // Energie consommée par mouvement (d)
    void (*depenseEnergie)(animal* self); // Pointeur de fonction, parenthèses pour distinguer d'une déclaration

    double fertilite; // Probabilité de se reproduire (p_reproduce)
    int (*donneNaissance)(animal* self);

    int direction; // 0 = Haut, 1 = Droite, 2 = Bas, 3 = Gauche
    double assurance; // Probabilité de changer de direction (p_ch_dir)
    void (*changeDirection)(animal* self);
    int aMigre; // Booleen

    animal* suivant;
};

// Prototype d'une fonction "constructeur"
animal* animal_create();
// Prototype d'une fonction "destructeur"
void animal_destroy(animal* Animal);

// Prototype de fonctions "méthodes"
void depenseEnergieAnimal(animal* self); // Exemple d'une fonction générique qui serait écrasée par les méthodes des héritiés.
int donneNaissanceAnimal(animal* self);
void changeDirectionAnimal(animal* self);

#endif // ANIMAL_H