# Projet : Algorithme de Bron-Kerbosch pour la recherche de k-quasi-cliques

## Auteurs
- **Meryem BELASSEL**
- **Thomas NICOLLE**
- **Groupe C**

## Introduction
Ce projet vise à implémenter une version modifiée de l'algorithme de **Bron-Kerbosch** afin de repérer la plus grande **k-quasi-clique** dans un graphe spécifique. Une **k-quasi-clique** est un ensemble de sommets formant une clique après suppression d'un minimum de **k arêtes**.

Nous avons suivi plusieurs étapes pour développer ce projet :
1. Génération d'un graphe et stockage des éléments nécessaires.
2. Modification de l'algorithme de Bron-Kerbosch pour identifier les **k-quasi-cliques**.

---

## Principe de l’algorithme de Bron-Kerbosch
L'algorithme de **Bron-Kerbosch** est une méthode efficace pour énumérer toutes les **cliques maximales** d'un graphe non orienté. Il fonctionne en parcourant récursivement les sommets pour identifier les sous-ensembles formant une clique complète.

### Pseudo-code de l'algorithme de Bron-Kerbosch
```pseudo
BronKerbosch(R, P, X) est
    si P et X sont tous les deux vides alors
        rapporter R comme une clique maximale
    pour chaque sommet v dans P faire
        BronKerbosch(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
        P := P \ {v}
        X := X ⋃ {v}
```

**Où :**
- `R` est l’ensemble des sommets formant une clique partielle.
- `P` est l’ensemble des sommets candidats pouvant être ajoutés à la clique.
- `X` contient les sommets déjà exclus.

Lorsque `P` et `X` sont vides, l’ensemble `R` est une **clique maximale**.

---

## Exemple d'application
Considérons le graphe suivant :
```
   C
  / \
 A— B—D—E
      |
      C
```
Avec les arêtes : **AB, BC, BD, CE, CD, ED**

L'algorithme trouve les cliques maximales suivantes :
- {A, B, C}
- {B, D, E}
- {C, E}

---

## Implémentation en C++
Nous avons choisi **C++** pour l’implémentation. Plusieurs fonctions ont été développées :

### Fonctions principales
- **`genererGraphe(int p)`** : Génère un graphe aléatoire avec une probabilité `p` de liaison entre chaque paire de sommets.
- **`remplirVoisins()`** : Remplit une structure `vector<vector<int>>` contenant la liste des voisins de chaque sommet.
- **`afficherVoisins()`** : Affiche les voisins de chaque sommet pour vérification.
- **`intersection(vector<int>, vector<int>)`** : Retourne l'intersection entre deux ensembles de sommets.
- **`difference(vector<int>, vector<int>)`** : Retourne la différence entre deux ensembles de sommets.
- **`unionEnsembles(vector<int>, vector<int>)`** : Retourne l'union entre deux ensembles de sommets.
- **`BronKerbosch(vector<int> R, vector<int> P, vector<int> X)`** : Implémente l’algorithme en utilisant une approche récursive de backtracking.

### Fonctionnement de `BronKerbosch`
1. Si `P` et `X` sont vides → `R` est une clique maximale.
2. Sinon, pour chaque sommet `v` dans `P` :
   - Mise à jour des ensembles `R`, `P`, et `X`.
   - Appel récursif de `BronKerbosch`.
3. Ajout des cliques trouvées dans un fichier `cliques.txt`.

---

## Utilisation
### **Compilation et exécution**
1. Compiler le programme :
```bash
g++ -o bronkerbosch bronkerbosch.cpp
```
2. Exécuter le programme :
```bash
./bronkerbosch
```
ou lancer le Makefile.
3. Les cliques maximales trouvées seront enregistrées dans **cliques.txt**.

---

## Conclusion
Ce projet explore l'algorithme de **Bron-Kerbosch** en l'adaptant pour détecter les **k-quasi-cliques**. L'implémentation en C++ permet une exécution efficace sur des graphes de taille variable.

🚀 **Prochaines améliorations** : Optimisation de l'algorithme et ajout d'une interface graphique pour une meilleure visualisation des résultats.

---
