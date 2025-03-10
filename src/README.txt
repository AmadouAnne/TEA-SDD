
Projet : Arbre Bicolore (Red-Black Tree)

Auteurs
-------
 - Amadou Tidiane ANNE (B)
 - Killian DAMASCENO (B)
 - Abdel Ouakil KERRAF (B)
 - Ehoussoud N'GOUAN (B)

Ce projet implémente un arbre bicolore (Red-Black Tree) en C. Un arbre bicolore est une structure de données équilibrée 
qui garantit que les opérations d'insertion, de suppression et de recherche se font en temps O(log n).

Structure du projet
-------------------
Le projet contient les fichiers suivants :
- bicolor-tree.c : Contient l'implémentation des fonctions principales de l'arbre bicolore, y compris les rotations, 
  l'insertion et les corrections pour maintenir les propriétés de l'arbre.
- bicolor-tree.h : Déclare les structures de données et les prototypes des fonctions.
- test-insert-bicolor.c : Un fichier de test pour valider les fonctionnalités d'insertion dans l'arbre bicolore.
- test-menu-bitree.c : Un fichier de test interactif pour manipuler l'arbre bicolore via un menu.
- CMakeLists.txt : Fichier de configuration pour compiler le projet avec CMake.

Fonctionnalités principales
---------------------------
1. Création de l'arbre bicolore :
   La structure struct BiTree représente un nœud de l'arbre avec les attributs :
   - Donnée (data) : La valeur entière stockée dans le nœud.
   - Couleur (color) : Soit 'R' (Rouge) ou 'B' (Noir).
   - Pointeurs vers les enfants gauche/droite et le parent.

2. Opérations disponibles :
   - Rotations : leftRotate et rightRotate pour rééquilibrer l'arbre.
   - Insertion : Ajoute un nouveau nœud et vérifie les propriétés de l'arbre.
   - Parcours :
     - inorder : Parcours in-order pour afficher les valeurs triées.
     - affichage : Affiche l'arbre avec indentation pour mieux visualiser sa structure.

3. Tests :
   - test-insert-bicolor.c : Valide l'insertion de plusieurs nœuds dans l'arbre.
   - test-menu-bitree.c : Offre une interface simple pour ajouter, visualiser et manipuler l'arbre.

Compilation et exécution
------------------------
Avec CMake
1. Assurez-vous que CMake est installé sur votre machine.
2. Dans le répertoire du projet, créez un dossier build :
   mkdir build
   cd build

3. Générez les fichiers make et compilez :
   cmake ../src -DCMAKE_INSTALL_PREFIX=../tmp -DCMAKE_BUILD_TYPE=Debug
   make

4. Lancez les tests :
   - Pour tester l'insertion :
     ./test_insert_bicolor

   - Pour tester le menu interactif :
     ./test_menu_bitree

  - Afficher le graphe:
      gnuplot plot.cb

Compilation manuelle
--------------------
Si vous préférez compiler manuellement sans CMake :
gcc -o test_insert_bicolor test-insert-bicolor.c bicolor-tree.c
gcc -o test_menu_bitree test-menu-bitree.c bicolor-tree.c

Exemple d'utilisation
---------------------
Test d'insertion
Voici un exemple simple avec test-insert-bicolor.c :
./test_insert_bicolor
Le programme affichera les valeurs triées et l'état de l'arbre après chaque insertion.

Test interactif
Avec test-menu-bitree.c :
./test_menu_bitree
Suivez les instructions affichées pour manipuler l'arbre.

Organisation du code
--------------------
.
├── bicolor-tree.c          # Implémentation principale de l'arbre bicolore
├── bicolor-tree.h          # Déclarations des structures et fonctions
├── test-insert-bicolor.c   # Fichier de test pour l'insertion
├── test-menu-bitree.c      # Fichier de test interactif
├── CMakeLists.txt          # Fichier de configuration CMake
└── README.md               # Documentation du projet

Améliorations possibles
-----------------------
- Implémenter une fonction de suppression dans l'arbre bicolore.
- Ajouter des tests automatisés avec un framework comme CUnit.
- Exporter les résultats dans un fichier de log pour faciliter le débogage.

