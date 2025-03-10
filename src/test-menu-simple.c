#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
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
    //srandom(time(NULL));

    //écriture dans le fichier data.dat des valeurs de temps d'insertion pour 100, 250, 500 et 1000 éléments
    // FILE *f = fopen("data.dat", "w");
    // for (int i = 100; i <= 1000; i += 150)
    // {
    //     struct BiTree *root = NULL;
    //     clock_t t0 = clock();
    //     for (int j = 0; j < i; ++j)
    //         insert(&root, random());
    //     clock_t t1 = clock();
    //     float time_taken = (float)(t1 - t0) / CLOCKS_PER_SEC * 1000;
    //     fprintf(f, "%d %f\n", i, time_taken);
    //     freeNode(root);
    // }
    // fclose(f);
    //désallocation de la mémoire allouée pour l'arbre

    //menu textuelle pour tester l'arbre rouge-noir
    struct BiTree *root = NULL;
    int choix = 0;
    do
    {
        printf("1- Inserer un noeud\n");
        printf("2- Afficher l'arbre\n");
        printf("3- Parcours Inorder\n");
        printf("4- rechercher une valeur\n");
        printf("5- supprimer une valeur\n");

        printf("6- Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            printf("Donner la valeur du noeud à insérer : ");
            int val;
            scanf("%d", &val);
            insert(&root, val);
            break;
        case 2:
            affichage(root, 0);
            break;
        case 3:
            inorder(root);
            printf("\n");
            break;
        case 4:
            //cas recherche
            printf("Donner la valeur à rechercher : ");
            int val2;
            scanf("%d", &val2);
            if (recherche(root, val2))
                printf("La valeur %d existe dans l'arbre\n", val2);
            else
                printf("La valeur %d n'existe pas dans l'arbre\n", val2);
            break;
        case 5:
	    // Handle node deletion
	    printf("Donner la valeur à supprimer : ");
	    int val3;
	    scanf("%d", &val3);

	    // Find the node with the specified value
	    struct BiTree *z = root;
	    while (z != NULL && z->data != val3) {
		if (z->data < val3)
		    z = z->right;
		else
		    z = z->left;
	    }

	    // If the node does not exist
	    if (z == NULL) {
		printf("La valeur %d n'existe pas dans l'arbre\n", val3);
	    } else {
		// Delete the node
		deleteNode(&root, z);
		printf("La valeur %d a été supprimée\n", val3);
	    }
	    break;

        case 6:
            freeNode(root);
            return 0;
        default:
            printf("Choix invalide\n");
            break;
        }
    } while (choix != 5);
    return 0;
}
