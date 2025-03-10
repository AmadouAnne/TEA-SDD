#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "bicolor-tree.h"



struct BiTree *bitree_create(int data)
{
    struct BiTree *newNode = (struct BiTree *)malloc(sizeof(struct BiTree));
    if (!newNode)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->color = 'R';  // Default color is red for a new node
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}



// rotation gauche
void LeftRotate(struct BiTree **root, struct BiTree *x)
{
    if (!x || !x->right)
        return;
    struct BiTree *y = x->right;

    x->right = y->left;

    if (x->right != NULL)
        x->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        (*root) = y;

    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;

    x->parent = y;
}

// rotation droite
void rightRotate(struct BiTree **root, struct BiTree *y)
{
    if (!y || !y->left)
        return;
    struct BiTree *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (x->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

bool recherche(struct BiTree *root, int data)
{
    if (root == NULL)
        return false;
    if (root->data == data)
        return true;
    if (root->data < data)
        return recherche(root->right, data);
    return recherche(root->left, data);
}


// Fonction pour vérifier les propriétés de l'arbre rouge-noir
void insertFixUp(struct BiTree **root, struct BiTree *z)
{
    while (z != *root && z->parent->color == 'R')
    {
        struct BiTree *y;
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if (y && y->color == 'R')
            {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    LeftRotate(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(root, z->parent->parent);
            }
        }
        else
        {
            y = z->parent->parent->left;
            if (y && y->color == 'R')
            {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                LeftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = 'B';
}

// Insertion d'un BiTree dans l'arbre rouge-noir
void insert(struct BiTree **root, int data)
{
    struct BiTree *z = (struct BiTree *)malloc(sizeof(struct BiTree));
    z->data = data;
    z->color = 'R';
    z->left = z->right = z->parent = NULL;

    struct BiTree *y = NULL;
    struct BiTree *x = *root;

    while (x != NULL)
    {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
    {
        *root = z;
    }
    else if (z->data < y->data)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    insertFixUp(root, z);
}


// parcours inorder de l'arbre
void inorder(struct BiTree *root)
{
    static int last = 0;
    if (root == NULL)

        return;
    inorder(root->left);
    printf("%d ", root->data);
    if (root->data < last)
        printf("\nPUTE\n");
    last = root->data;
    inorder(root->right);
}

void deleteFixUp(struct BiTree **root, struct BiTree *x)
{
    while (x != *root && (x == NULL || x->color == 'B'))
    {
        if (x == x->parent->left)
        {
            struct BiTree *w = x->parent->right;

            if (w && w->color == 'R')
            {
                w->color = 'B';
                x->parent->color = 'R';
                LeftRotate(root, x->parent);
                w = x->parent->right;
            }

            if (w && (!w->left || w->left->color == 'B') && (!w->right || w->right->color == 'B'))
            {
                w->color = 'R';
                x = x->parent;
            }
            else
            {
                if (w && (!w->right || w->right->color == 'B'))
                {
                    if (w->left)
                        w->left->color = 'B';
                    w->color = 'R';
                    rightRotate(root, w);
                    w = x->parent->right;
                }

                if (w)
                {
                    w->color = x->parent->color;
                    x->parent->color = 'B';
                    if (w->right)
                        w->right->color = 'B';
                    LeftRotate(root, x->parent);
                }
                x = *root;
            }
        }
        else
        {
            struct BiTree *w = x->parent->left;

            if (w && w->color == 'R')
            {
                w->color = 'B';
                x->parent->color = 'R';
                rightRotate(root, x->parent);
                w = x->parent->left;
            }

            if (w && (!w->right || w->right->color == 'B') && (!w->left || w->left->color == 'B'))
            {
                w->color = 'R';
                x = x->parent;
            }
            else
            {
                if (w && (!w->left || w->left->color == 'B'))
                {
                    if (w->right)
                        w->right->color = 'B';
                    w->color = 'R';
                    LeftRotate(root, w);
                    w = x->parent->left;
                }

                if (w)
                {
                    w->color = x->parent->color;
                    x->parent->color = 'B';
                    if (w->left)
                        w->left->color = 'B';
                    rightRotate(root, x->parent);
                }
                x = *root;
            }
        }
    }
    if (x != NULL)
        x->color = 'B';
}


//suppression d'un BiTree dans l'arbre rouge-noir
void deleteNode(struct BiTree **root, struct BiTree *z) {
    if (z == NULL || root == NULL || *root == NULL) {
        printf("Erreur : BiTree invalide ou arbre vide.\n");
        return;
    }

    struct BiTree *y = z;
    struct BiTree *x = NULL;
    char y_original_color = y->color;

    if (z->left == NULL) {
        x = z->right;
        if (z->parent == NULL)
            *root = z->right;
        else if (z == z->parent->left)
            z->parent->left = z->right;
        else
            z->parent->right = z->right;

        if (z->right != NULL)
            z->right->parent = z->parent;
    } else if (z->right == NULL) {
        x = z->left;
        if (z->parent == NULL)
            *root = z->left;
        else if (z == z->parent->left)
            z->parent->left = z->left;
        else
            z->parent->right = z->left;

        if (z->left != NULL)
            z->left->parent = z->parent;
    } else {
        y = z->right;
        while (y->left != NULL)
            y = y->left;

        y_original_color = y->color;
        x = y->right;

        if (y->parent != z) {
            if (y->right != NULL)
                y->right->parent = y->parent;

            y->parent->left = y->right;
            y->right = z->right;
            if (z->right != NULL)
                z->right->parent = y;
        }

        if (z->parent == NULL)
            *root = y;
        else if (z == z->parent->left)
            z->parent->left = y;
        else
            z->parent->right = y;

        y->parent = z->parent;
        y->left = z->left;
        if (z->left != NULL)
            z->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == 'B')
        deleteFixUp(root, x);

    free(z); // Libère enfin le BiTree supprimé
}




//affichage de l'arbre rouge-noir en utilisant l'indentation
void affichage(struct BiTree *root, int space)
{
    if (root == NULL)
        return;
    space += 10;
    affichage(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d %c\n", root->data, root->color);
    affichage(root->left, space);
}
//affichage de l'arbre rouge-noir en utilisant l'indentation dans un ficher texte
void affichageFichier(struct BiTree *root, int space, FILE *f)
{
    if (root == NULL)
        return;
    space += 10;
    affichageFichier(root->right, space, f);
    fprintf(f, "\n");
    for (int i = 10; i < space; i++)
        fprintf(f, " ");
    fprintf(f, "%d %c\n", root->data, root->color);
    affichageFichier(root->left, space, f);
}

//fonction pour désallouer la mémoire allouée pour l'arbre
void freeNode(struct BiTree *node) {
    if (node == NULL)
        return;

    freeNode(node->left);
    freeNode(node->right);
    free(node);
}



