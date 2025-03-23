#include <cstdio>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream>
using namespace std;

const int n = 80; // nombre de sommets
int G[n][n] = {0};  // matrice d'adjacence du graphe
vector<int> R; // sous-ensemble des sommets de la potentielle clique
vector<int> P; // ensemble des sommets candidats pour être ajoutés à la potentielle clique
vector<int> X; // sommets déjà traités ou appartenant déjà à une clique maximale
vector<vector<int>> Voisins; // structure pour stocker les voisins d'un sommet
set<vector<int>> cliquesTrouvees; // structure pour stocker les cliques maximales pour éviter les doublons
int maxCliqueSize = 0; // taille de la clique maximale
const int MAX_N = 10; // Taille maximale de la matrice G
    /*
     * Générer les données d'un graphe
     */
    void genererGraphe(int p) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (rand() % 100 < p) {
                    G[i][j] = 1;
                    G[j][i] = 1;
                }
            }
        }
    }

    /*
     *  Fonction qui génère des graphes aléatoires, avec n nombre de sommets et p la probabilité d’arête par le biais d’un entier
    p (entre 0 et 100)
     */
    void grapheAleat(int n, int p)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                if(rand()%100 < p)
                {
                    G[i][j]= 1;
                    G[j][i]= 1;
                }
                else
                {
                    G[i][j]= 0;
                    G[j][i]= 0;
                }
            }
        }
    }

    /*
     * Générer l'image du graphe
     */
    void ecrireDOT() {
        std::ofstream out("graphe.dot");
        out << "graph G {" << std::endl;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (G[i][j]) {
                    out << "    " << i << " -- " << j << ";" << std::endl;
                }
            }
        }
        out << "}" << std::endl;
        out.close();

        system("dot -Tpng graphe.dot -o graphe.png"); // Exécute Graphviz pour créer l'image
        cout << "[INFORMATION] Le graphe a été généré et sauvegardé en tant que 'graphe.png' !" << endl;
    }


    /*
     * Insérer les voisins dans le tableau
     */
    void remplirVoisins() {
        Voisins.resize(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; j++) {
                if (G[i][j] == 1) {
                    Voisins[i].push_back(j);
                    Voisins[j].push_back(i); // Ensure symmetry
                }
            }
        }
    }

    /*
     * Afficher les voisins dans la console
     */
    void afficherVoisins() {
        for (int i = 0; i < n; i++) {
            printf("Sommet %d: ", i);
            for (int j: Voisins[i]) {
                printf("%d ", j);
            }
            printf("\n");
        }
    }

    /*
     * Fonction pour l'intersection de deux ensembles
     */
    vector<int> intersection(const vector<int>& ensemble1, const vector<int>& ensemble2) {
        vector<int> resultat;
        set<int> set1(ensemble1.begin(), ensemble1.end());
        for (int elem : ensemble2) {
            if (set1.find(elem) != set1.end()) {
                resultat.push_back(elem);
            }
        }
        return resultat;
    }

    /*
     * Fonction pour la différence de deux ensembles
     */
    vector<int> difference(const vector<int>& ensemble1, const vector<int>& ensemble2) {
        vector<int> resultat;
        set<int> set2(ensemble2.begin(), ensemble2.end());
        for (int elem : ensemble1) {
            if (set2.find(elem) == set2.end()) {
                resultat.push_back(elem);
            }
        }
        return resultat;
    }

    /*
     * Fonction pour l'union de deux ensembles
     */
    vector<int> unionEnsembles(const vector<int>& ensemble1, const vector<int>& ensemble2) {
        vector<int> resultat(ensemble1);
        resultat.insert(resultat.end(), ensemble2.begin(), ensemble2.end());
        sort(resultat.begin(), resultat.end());
        resultat.erase(unique(resultat.begin(), resultat.end()), resultat.end());
        return resultat;
    }

    /*
     * Fonction récursive de l'algorithme de Bron-Kerbosch
     */
    void BronKerbosch(vector<int> R, vector<int> P, vector<int> X) {
        if (P.empty() && X.empty()) {
            // Si P et X sont vides, R est une clique maximale
            sort(R.begin(), R.end());  // Tri des sommets
            if (cliquesTrouvees.find(R) == cliquesTrouvees.end()) {  // Si la clique n'a pas encore été trouvée
                cliquesTrouvees.insert(R);
                cout << "Clique maximale trouvée: ";
                for (int sommet : R) {
                    cout << sommet << " ";
                }
                cout << endl;

                // Écrire dans un fichier
                ofstream myfile;
                myfile.open("../fichiers/cliques.txt", ios::app);
                myfile << "Clique maximale de taille " << R.size() << " : ";
                for (int v: R) {
                    myfile << v << " ";
                }
                myfile << "\n";
                myfile.close();
            }
            return;
        }

        vector<int> P_copie = P;
        for (int v : P) {
            vector<int> R_ajout = R;
            R_ajout.push_back(v);

            vector<int> P_voisins = intersection(P, Voisins[v]);
            vector<int> X_voisins = intersection(X, Voisins[v]);

            BronKerbosch(R_ajout, P_voisins, X_voisins);

            P_copie = difference(P_copie, vector<int>{v});
            X = unionEnsembles(X, vector<int>{v});
        }
    }

int main() {
        srand(NULL);
        ofstream ofs;
        // Ouvrir le fichier “cliques.txt” en mode écriture/ tronque (trunc) efface tout contenu existant
        ofs.open("../fichiers/cliques.txt", std::ofstream::out | std::ofstream::trunc);
//        ofs.open("../fichiers/resultats.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
//        genererGraphe(n);
//        ecrireDOT();
//        remplirVoisins(); // Remplir la liste des voisins pour chaque sommet
//        afficherVoisins(); // Afficher les voisins de chaque sommet
//        for (int i = 0; i < n; i++) {
//            P.push_back(i); // Ajouter tous les sommets à l'ensemble P
//        }
//        printf("Algorithme de BronKerbosh :\n");
//        BronKerbosch(R, P, X); // Appeler l'algorithme de Bron-Kerbosch

    // Tableau pour stocker les tailles des cliques maximales
    vector<vector<double>> taillesCliques(MAX_N + 1, vector<double>(MAX_N + 1, 0.0));

    // Boucle pour chaque valeur de n
    for (int m = 1; m <= MAX_N; m++) {
        // Boucle pour chaque valeur de p
        for (int p = 0; p <= 100; p++) {
            // Répéter l'expérience plusieurs fois (par exemple 100 fois)
            const int cpt = 100;
            int totalCliqueSize = 0;
            for (int q = 0; q < cpt ; q++) {
                // Générer le graphe aléatoire G(n, p)
                grapheAleat(n, p);
                // Initialiser R, P et X
                vector<int> R1, P1, X1;
                for (int i = 0; i < n; ++i) {
                    P.push_back(i);
                }
                // Calculer la taille de la clique maximale
                BronKerbosch(R1, P1, X1);
                int taille_clique;
                taille_clique= R1.size();
                totalCliqueSize += taille_clique;
            }
            // Calculer la taille moyenne de la clique maximale
            int moyenneTaille_clique = totalCliqueSize / cpt;
            // Enregistrer la taille moyenne dans le tableau
            taillesCliques[n][p] = moyenneTaille_clique;
        }
    }

    // Affichage des résultats
    for (int m = 1; m <= MAX_N; m++) {
        for (int p = 0; p <= 100; p++) {
            cout << "Taille moyenne de la clique maximale pour G(" << n << ", " << p << "): " << taillesCliques[n][p] << endl;
        }
    }
    return 0;
}
