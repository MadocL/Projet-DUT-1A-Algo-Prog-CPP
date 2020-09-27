///Projet Tutoré partie 2 2019/2020 : LEFEVRE Madoc, SANNIER Florian, JACQUET Nicolas, et BIPLOB Omma Habiba

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "fonctions.h"
using namespace std;

/*Fonction "split_line_and_add" :

Description :
    Cette fonction découpe chaque ligne du fichier csv en champ délimité par un pipe. Chaque champ est une information sur un élève (son nom, son prénom...).
    Ensuite, chaque champ est ajouté au tableau 2D comme une nouvelle case du tableau de l'élève courant.

Paramètres :
    - "const string &line" représente une ligne du fichier csv
    - "vector <vector <string> > &data" représente le tableau 2D dans lequel les informations sur les élèves ou celles des entreprises sont stockées
    - "int i" représente l'identifiant de l'élève courant (sa place dans le fichier csv) pour que ses informations soient mises dans le bon tableau dans le tableau 2D
    (c'est son indice dans le tableau 2D)
*/

void split_line_and_add(const string &line, vector <vector <string> > &data, int i)
{
    stringstream ssline(line); // conversion de la ligne donnée en type "stringstream"
    string champ;
    int j=0;
    while(getline(ssline, champ, '|'))  // Je divise la ligne donnée avec comme délimiteur un pipe
    {
        data[i].push_back(champ); // et j'ajoute chaque champs dans le tableau
        j++;
    }
    if (j<=1){
        cout << "Erreur : L'un des fichiers d'entree est vide ou ne comporte qu'un seul champ sur au moins une ligne (un champ etant delimite par un caractere '|')";
        exit(1);
    }
}

/*Fonction "stock_eleve" :

Description : Stock les informations du fichier csv dans un tableau.
    Cette fonction prend en paramètre le fichier csv des élèves pour délimiter toute les lignes (le délimiteur est le retour chariot "\n").
    Pour chaque ligne, la fonction précédente "split_line_and_add" est appelée pour remplir le tableau avec la ligne donnée.
    Puis une fois qu'il n'y a plus de ligne dans le tableau (la fonction getline le reconnait toute seule), la boucle s'arrête.
    Ensuite pour chaque élève : son login et son nom sont intervertis pour pouvoir trier le tableau 2D par ordre alphabétique.
    S'ensuit la normalisation de plusieurs champs : pour tous les élèves les noms sont mis en majuscule, les prénoms sont mis en minuscule sauf la première lettre en majuscule,
    pareil pour les noms des entreprises.
    Enfin, le tableau 2D est entièrement trié à l'aide de la fonction "sort" par ordre alphabétique et par ordre des champs de chaque sous tableau (chaque élèves) : par nom puis par prénom.
    La fonction retourne le tableau 2D de chaînes de caractères.

Paramètre :
    - ifstream &csv représente un fichier csv, ici celui des élèves, sous le forme d'un "ifstream"
*/

vector <vector <string> > stock_eleve(ifstream &csv){

    string line;
    vector <vector <string> > data;
    data.push_back({}); //J'ajoute un tableau vide à la suite pour ensuite ajouter des valeurs dans ce tableau vide
    int i=0, j=0;

    while(getline(csv, line, '\n'))  // getline met chaque ligne du fichier (délimitée avec '\n' )dans la string line (tant qu'il y a encore des lignes non lues dans le csv)
    {
        split_line_and_add(line, data, i); // j'appelle la fonction pour chaque ligne
        i++;
        data.push_back({}); //J'ajoute un tableau vide à la suite pour ensuite ajoouter des valeurs dans ce tableau vide
    }
    data.pop_back();

    string temp;
    for(int i=0; i< data.size(); i++){
        temp = data[i][0]; // J'intervertis les login avec les noms pour que les noms soient les premiers champ de chaque ligne
        data[i][0] = data[i][1];
        data[i][1] = temp;

        for(int j=0; j< data[i][0].length(); j++){
            data[i][0][j] = toupper(data[i][0][j]); // les noms sont mis en maj
        }

        data[i][2][0] = toupper(data[i][2][0]); // la première lettre des prénoms est mis en maj
        for(int j=1; j< data[i][2].length(); j++){
            data[i][2][j] = tolower(data[i][2][j]); // et le reste est mis en minuscule
        }

        data[i][4][0] = toupper(data[i][4][0]); // la première lettre des entreprises est mis en maj
        for(int j=1; j< data[i][4].length(); j++){
            data[i][4][j] = tolower(data[i][4][j]); // et le reste est mis en minuscule
        }

        if(data[i][5]=="1"){ // Si l'élève a une photo
            data[i][5]=data[i][1]+".jpg"; // remplacer le booléen par le login + ".jpg"
        }
    }
    sort(data.begin(), data.end()); // Du coup maintenant je peux trier le tableau par nom vu que les noms sont au début de chaque vecteur

    return data;
}
