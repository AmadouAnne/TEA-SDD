#ifndef _BICOLOR_TREE_H_
#define _BICOLOR_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


// structure d'un BiTree d'un arbre rouge-noir
struct BiTree
{
    int data;
    char color;
    struct BiTree *left, *right, *parent;
};


void LeftRotate(struct BiTree **root, struct BiTree *x);
void rightRotate(struct BiTree **root, struct BiTree *y);
void insertFixUp(struct BiTree **root, struct BiTree *z);
void insert(struct BiTree **root, int data);
void inorder(struct BiTree *root);
void affichage(struct BiTree *root, int space);
void affichageFichier(struct BiTree *root, int space, FILE *f);
void freeNode(struct BiTree *root);
bool recherche(struct BiTree *root, int data);
void deleteFixUp(struct BiTree **root, struct BiTree *x);
void deleteNode(struct BiTree **root, struct BiTree *z);
#endif
