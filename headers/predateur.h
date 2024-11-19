#ifndef PREDATEUR_H
#define PREDATEUR_H

#define d_energie_predateur 2
#define p_reproduction_predateur 0.5
#define p_manger 0.8

typedef struct predateur {
    animal base; // Héritage

    double appetit; // Attribut spécifique à cette classe, ignoré en cas de conversion explicite (p_manger)
    int (*devore)(struct predateur* self); // Méthode spécifique, ignorée en cas de conversion explicite

} predateur;

// Constructeur
predateur* predateur_create();
// Destructeur
void predateur_destroy(predateur** adressePredateur);

// Méthodes
int devoreProie(predateur* self); // Renvoie 1 si une proie est dévorée, 0 sinon
proie* predateurChasseProie(predateur* self, proie* victime);

#endif // PREDATEUR_H