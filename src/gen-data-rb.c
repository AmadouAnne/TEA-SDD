#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bicolor-tree.h"

//NB_ELEMS : nombre d'éléments à insérer dans l'arbre
#define NB_ELEMS 10
//MAX_RAND : valeur maximale pour la génération des valeurs aléatoires
#define MAX_RAND 100
//MIN_RAND : valeur minimale pour la génération des valeurs aléatoires
#define MIN_RAND 0

// fonction main pour tester et générer les valeurs pour le rapport
int main()
{
    // initialisation de la graine pour la génération des valeurs aléatoires
    srandom(time(NULL));

    //écriture dans le fichier data.dat des valeurs de temps d'insertion pour 100, 250, 500 et 1000 éléments
    FILE *f = fopen("data_rb.dat", "w");
    for (int i = 100; i <= 1000; i += 150)
    {
        struct BiTree *root = NULL;
        clock_t t0 = clock();
        for (int j = 0; j < i; ++j)
            insert(&root, random());
        clock_t t1 = clock();
        float time_taken = (float)(t1 - t0) / CLOCKS_PER_SEC * 1000;
        fprintf(f, "%d %f\n", i, time_taken);
        freeNode(root);
    }
    fclose(f);
    //désallocation de la mémoire allouée pour l'arbre
    return 0;
}
