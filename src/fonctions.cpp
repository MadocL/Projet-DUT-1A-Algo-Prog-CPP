///Projet Tutor� partie 2 2019/2020 : LEFEVRE Madoc, SANNIER Florian, JACQUET Nicolas, et BIPLOB Omma Habiba

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
    Cette fonction d�coupe chaque ligne du fichier csv en champ d�limit� par un pipe. Chaque champ est une information sur un �l�ve (son nom, son pr�nom...).
    Ensuite, chaque champ est ajout� au tableau 2D comme une nouvelle case du tableau de l'�l�ve courant.

Param�tres :
    - "const string &line" repr�sente une ligne du fichier csv
    - "vector <vector <string> > &data" repr�sente le tableau 2D dans lequel les informations sur les �l�ves ou celles des entreprises sont stock�es
    - "int i" repr�sente l'identifiant de l'�l�ve courant (sa place dans le fichier csv) pour que ses informations soient mises dans le bon tableau dans le tableau 2D
    (c'est son indice dans le tableau 2D)
*/

void split_line_and_add(const string &line, vector <vector <string> > &data, int i)
{
    stringstream ssline(line); // conversion de la ligne donn�e en type "stringstream"
    string champ;
    int j=0;
    while(getline(ssline, champ, '|'))  // Je divise la ligne donn�e avec comme d�limiteur un pipe
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
    Cette fonction prend en param�tre le fichier csv des �l�ves pour d�limiter toute les lignes (le d�limiteur est le retour chariot "\n").
    Pour chaque ligne, la fonction pr�c�dente "split_line_and_add" est appel�e pour remplir le tableau avec la ligne donn�e.
    Puis une fois qu'il n'y a plus de ligne dans le tableau (la fonction getline le reconnait toute seule), la boucle s'arr�te.
    Ensuite pour chaque �l�ve : son login et son nom sont intervertis pour pouvoir trier le tableau 2D par ordre alphab�tique.
    S'ensuit la normalisation de plusieurs champs : pour tous les �l�ves les noms sont mis en majuscule, les pr�noms sont mis en minuscule sauf la premi�re lettre en majuscule,
    pareil pour les noms des entreprises.
    Enfin, le tableau 2D est enti�rement tri� � l'aide de la fonction "sort" par ordre alphab�tique et par ordre des champs de chaque sous tableau (chaque �l�ves) : par nom puis par pr�nom.
    La fonction retourne le tableau 2D de cha�nes de caract�res.

Param�tre :
    - ifstream &csv repr�sente un fichier csv, ici celui des �l�ves, sous le forme d'un "ifstream"
*/

vector <vector <string> > stock_eleve(ifstream &csv){

    string line;
    vector <vector <string> > data;
    data.push_back({}); //J'ajoute un tableau vide � la suite pour ensuite ajouter des valeurs dans ce tableau vide
    int i=0, j=0;

    while(getline(csv, line, '\n'))  // getline met chaque ligne du fichier (d�limit�e avec '\n' )dans la string line (tant qu'il y a encore des lignes non lues dans le csv)
    {
        split_line_and_add(line, data, i); // j'appelle la fonction pour chaque ligne
        i++;
        data.push_back({}); //J'ajoute un tableau vide � la suite pour ensuite ajoouter des valeurs dans ce tableau vide
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

        data[i][2][0] = toupper(data[i][2][0]); // la premi�re lettre des pr�noms est mis en maj
        for(int j=1; j< data[i][2].length(); j++){
            data[i][2][j] = tolower(data[i][2][j]); // et le reste est mis en minuscule
        }

        data[i][4][0] = toupper(data[i][4][0]); // la premi�re lettre des entreprises est mis en maj
        for(int j=1; j< data[i][4].length(); j++){
            data[i][4][j] = tolower(data[i][4][j]); // et le reste est mis en minuscule
        }

        if(data[i][5]=="1"){ // Si l'�l�ve a une photo
            data[i][5]=data[i][1]+".jpg"; // remplacer le bool�en par le login + ".jpg"
        }
    }
    sort(data.begin(), data.end()); // Du coup maintenant je peux trier le tableau par nom vu que les noms sont au d�but de chaque vecteur

    return data;
}
