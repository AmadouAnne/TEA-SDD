#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <gtk/gtk.h>
#include "tree-avl.h"

// Déclaration globale de l'arbre
Tree racine = NULL;

// Fonction de comparaison pour les entiers
int compare_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Fonction pour afficher les nœuds avec leur balance
void monPrintF(void *a, void *b) {
    if (!a) return;
    Tree node = (Tree)a;
    int val = *(int *)node->data;

    if (node->balance < -2 || node->balance > 2) {
        printf("Valeur du noeud : %d, Balance : %d (hors de portée)\n", val, node->balance);
    } else {
        printf("Valeur du noeud : %d, Balance : %d\n", val, node->balance);
    }
}

// Fonction pour afficher la structure de l'arbre
void print_tree(Tree node, int level) {
    if (node == NULL) return;
    print_tree(node->right, level + 1);
    printf("%*s%d\n", 4 * level, "", *(int *)node->data);
    print_tree(node->left, level + 1);
}

// Fonction callback pour insérer un élément
static void on_insert_button_clicked(GtkButton *button, gpointer user_data) {
    GtkEntry *entry = GTK_ENTRY(user_data);
    const char *text = gtk_entry_get_text(entry);
    int valeur = atoi(text);

    // Insérer la valeur dans l'arbre
    Tree x = tree_create(&(valeur), sizeof(int));
    racine = insertion(racine, x);

    // Afficher un message de confirmation
    gchar *msg = g_strdup_printf("Valeur %d insérée avec succès.", valeur);
    gtk_label_set_text(GTK_LABEL(user_data), msg);
    g_free(msg);
}

// Fonction callback pour afficher la structure de l'arbre
static void on_display_tree_button_clicked(GtkButton *button, gpointer user_data) {
    GtkLabel *label = GTK_LABEL(user_data);

    if (racine == NULL) {
        gtk_label_set_text(label, "L'arbre est vide.");
    } else {
        // Réinitialiser l'affichage
        char tree_structure[1024] = "Structure de l'arbre :\n";
        print_tree(racine, 0); // afficher l'arbre dans la console
        gtk_label_set_text(label, tree_structure);
    }
}

// Fonction callback pour afficher les balances des nœuds
static void on_display_balances_button_clicked(GtkButton *button, gpointer user_data) {
    GtkLabel *label = GTK_LABEL(user_data);

    if (racine == NULL) {
        gtk_label_set_text(label, "L'arbre est vide.");
    } else {
        gtk_label_set_text(label, "Balances des nœuds :");
        tree_in_order(racine, monPrintF, NULL); // afficher les balances dans la console
    }
}

// Fonction pour initialiser et afficher l'interface GTK
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Création de la fenêtre principale
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Menu AVL");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Création du conteneur principal
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Création du champ de texte pour entrer la valeur
    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    // Création des boutons
    GtkWidget *insert_button = gtk_button_new_with_label("Insérer un élément");
    gtk_box_pack_start(GTK_BOX(vbox), insert_button, FALSE, FALSE, 0);

    GtkWidget *display_tree_button = gtk_button_new_with_label("Afficher la structure de l'arbre");
    gtk_box_pack_start(GTK_BOX(vbox), display_tree_button, FALSE, FALSE, 0);

    GtkWidget *display_balances_button = gtk_button_new_with_label("Afficher les balances des nœuds");
    gtk_box_pack_start(GTK_BOX(vbox), display_balances_button, FALSE, FALSE, 0);

    // Création d'une étiquette pour afficher des messages
    GtkWidget *label = gtk_label_new("Bienvenue dans le menu AVL");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    // Connexion des événements avec les boutons
    g_signal_connect(insert_button, "clicked", G_CALLBACK(on_insert_button_clicked), entry);
    g_signal_connect(display_tree_button, "clicked", G_CALLBACK(on_display_tree_button_clicked), label);
    g_signal_connect(display_balances_button, "clicked", G_CALLBACK(on_display_balances_button_clicked), label);

    // Affichage de la fenêtre
    gtk_widget_show_all(window);

    // Lancer la boucle principale GTK
    gtk_main();

    // Libérer la mémoire avant de quitter
    tree_delete(racine, 0);

    return 0;
}

