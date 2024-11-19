#ifndef PROIE_H
#define PROIE_H

#define d_energie_proie 1
#define p_reproduction_proie 0.4

typedef struct proie {
    animal base;                    // Héritage (ici, déclarer une classe "proie" n'a pas beaucoup de sens car elle n'a ni methode ni attribut specifique)
} proie;

// Constructeur
proie* proie_create();
// Destructeur
void proie_destroy(proie** adresseProie);

#endif // PROIE_H