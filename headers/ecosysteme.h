#ifndef ECOSYSTEME_H
#define ECOSYSTEME_H

#define TAILLE 10
#define PERIOD 1000000
#define BASEPOPULATIONMAX 5
#define p_predateur 0.4

#define REPARTITION 3

void peupleEcosysteme(lieu Ecosysteme[TAILLE][TAILLE]); // Renvoie un ecosysteme de départ généré aléatoirement

void migrationAnimal(lieu Ecosysteme[TAILLE][TAILLE], int x, int y); // Migration d'un animal de la faune locale d'un lieu à une autre (en fonction de la direction de l'animal)

void actualiserEcosysteme(lieu Ecosysteme[TAILLE][TAILLE]); // (Parcours les lieux) Réalise les migrations et actualisation locale de lieu

void afficherEcosysteme(lieu Ecosysteme[TAILLE][TAILLE]);

#endif // ECOSYSTEME_H