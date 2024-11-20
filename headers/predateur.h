#ifndef PREDATEUR_H
#define PREDATEUR_H

#define d_energie_predateur 2
#define p_reproduction_predateur 0.5
#define p_manger 0.9

typedef struct predateur {
    animal base;                                // Héritage

    double appetit;                             // Attribut spécifique à cette classe  (p_manger), ignoré en cas de conversion explicite
    int (*devore)(struct predateur* self);      // Méthode spécifique, ignorée en cas de conversion explicite

} predateur;

// Constructeur
predateur* predateur_create();
// Destructeur
void predateur_destroy(predateur** adressePredateur);

// Méthodes                             
proie* predateurChasseProie(predateur* self, proie* victime);

#endif // PREDATEUR_H