#ifndef ANIMAL_H
#define ANIMAL_H

// Constantes globales
#define ENERGIE 10 
#define ASSURANCE 0.5 
#define NOMBRE_ESPECES 2

#define ANIMAL_TYPE_PROIE 0
#define ANIMAL_TYPE_PREDATEUR 1
#define ANIMALE_TYPE_MONTYPE 2

#define ANIMAL_DIRECTION_HAUT 0
#define ANIMAL_DIRECTION_DROITE 1
#define ANIMAL_DIRECTION_BAS 2
#define ANIMAL_DIRECTION_GAUCHE 3

typedef struct animal animal;
struct animal {
    int typeID;                                 // Voir defines
    char forme;                                 // Caractère affiché pour représenter l'animal

    int energie;                                // Energie de départ
    int metabolisme;                            // Energie consommée par mouvement (d)
    void (*depenseEnergie)(animal* self);       // Pointeur de fonction, parenthèses pour distinguer d'une déclaration

    double fertilite;                           // Probabilité de se reproduire (p_reproduce)
    //animal* (*accouplementAnimal)(animal* pere, animal* mere, animal* teteFauneLocale);

    int direction;                              // Voir defines
    double assurance;                           // Probabilité de changer de direction (p_ch_dir)
    void (*changeDirection)(animal* self);
    int aMigre;                                 // Booleen
    int estAccouple;                            // Booleen

    animal* suivant;
};

// Prototype d'une fonction "constructeur"
animal* animal_create();
// Prototype d'une fonction "destructeur"
void animal_destroy(animal* Animal);

// Prototype de fonctions "méthodes"
void depenseEnergieAnimal(animal* self);        // Exemple d'une fonction générique qui serait écrasée par les méthodes des héritiés.
void changeDirectionAnimal(animal* self);

#endif // ANIMAL_H