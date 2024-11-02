#include ".././headers/animal.h"
#include ".././headers/proie.h"
#include ".././headers/predateur.h"

#include ".././headers/lieu.h"
#include ".././headers/ecosysteme.h"


#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <time.h>

#define p_ch_dir 0.65

int main() {
    srand(time(NULL));
    lieu Ecosysteme[TAILLE][TAILLE];
    
    peupleEcosysteme(Ecosysteme);

    actualiserEcosysteme(Ecosysteme);
    
    return 0;
}