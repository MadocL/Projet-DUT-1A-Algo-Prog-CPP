///Projet Tutoré partie 2 2019/2020 : LEFEVRE Madoc, SANNIER Florian, JACQUET Nicolas, et BIPLOB Omma Habiba

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "fonctions.h"
using namespace std;

int main(int argc, char **argv){
    if(argc == 1)
    {
        cout << "Veuillez mettre en parametre les fichier csv suivants :" << endl;
        cout << "\"data/perso.csv\" (1er) et \"data/entreprise.csv\" (2nd) dans l'ordre indique" << endl;
        exit(1);
    }
    if(argc != 3){
		cout << "Usage: " << argv[0] << " csv" << endl;
		exit(1);
	}

    string csv_filename1 = argv[1]; // enregistre le nom du fichier csv donné
    string csv_filename2 = argv[2];

    ifstream csv1(csv_filename1), csv2(csv_filename2); // ifstream : type pour les flots d'entrée
    if(!csv1.is_open() || !csv2.is_open())  // teste si le fichier peut être ouvert
    {
        cout << "csv file not found" << endl;
        exit(1);
    }

    char mode;
    cout << "Mode par nom : 1; mode par entreprise : 2" << endl;
    cin >> mode;

    vector <vector <string> > data_eleve = stock_eleve(csv1); //appel de la fonction pour créer le tableau 2d contenant toutes les infos des élèves

    if (mode == '1') // Mode par nom
    {
        string html_filename = "output/output.html";

        ofstream html(html_filename);
        if(!html.is_open())  // teste si le fichier html peut être ouvert
        {
            cout << "could not open html file" << endl;
            exit(1);
        }
        else{ // Si le fichier HTML peut être ouvert : début de l'écriture

            cout << "Ecriture du fichier html..." << endl;
            html << "<!DOCTYPE html><html lang=\"fr\"><head><meta charset=\"utf-8\"/><title>Mode par eleve</title></head>" << endl; // En-tête HTML
            for (int i=0; i<data_eleve.size(); i++) // Pour chaque élèves :
            {
                html << "<div class=\"eleve\">" << endl; // J'ouvre une balise div
                if(data_eleve[i][5]=="0"){ // Si l'élève n'a pas renseigné de photo, je mets celle par défaut
                    html << "<img src=\"photo_default.jpg\" width=\"105\" height=\"135\" alt=\"photo de " << data_eleve[i][0]<<"\" />" << endl;
                }
                else{ //Sinon je mets celle à l'adresse correspondant à son identifiant
                    html<<"<img src=\"../../../photos/"<<data_eleve[i][5]<<"\" width=\"105\" height=\"135\" alt=\"photo de "<<data_eleve[i][0]<<"\" />" << endl;
                }
                html << "<p>"; // J'écrire les données de l'élève courant dans un paragraphe
                html << "<strong>Nom : </strong>" << data_eleve[i][0] << "<br>";
                html << "<strong>Prénom : </strong>" << data_eleve[i][2] << "<br>";
                html << "<strong>Entreprise : </strong>" << data_eleve[i][4] << "<br>";
                html << "<strong>Métier : </strong>" << data_eleve[i][3];
                html << "</p>" << endl << "</div>" << endl; // Et je referme la section
            }
            html << "</html>" << endl;
        }
        cout << "Fait ! Vous pouvez ouvrir le fichier html dans le dossier \"output\"";
    }
    else if(mode == '2')// Mode par entreprise
    {
        string line;
        vector <vector <string> > data_entreprise;
        data_entreprise.push_back({}); //J'ajoute un tableau vide à la suite pour ensuite ajouter des valeurs dans ce tableau vide
        int i=0, j=0;

        while(getline(csv2, line, '\n'))  // getline met chaque ligne du fichier (délimiteur '\n' )dans la string "line" (tant qu'il y a encore des lignes non lues dans le csv)
        {
            split_line_and_add(line, data_entreprise, i); // j'appelle la fonction pour chaque ligne
            i++;
            data_entreprise.push_back({}); //J'ajoute un tableau vide à la suite pour ensuite ajouter des valeurs dans ce tableau vide
        }
        data_entreprise.pop_back();

        for(int i=0; i< data_entreprise.size(); i++){ //Normalisation des noms des entreprises : première lettre en majuscule et le reste en minuscule

            data_entreprise[i][0][0] = toupper(data_entreprise[i][0][0]);
            for(int j=1; j< data_entreprise[i][0].length(); j++)
            {
                data_entreprise[i][0][j] = tolower(data_entreprise[i][0][j]); // les noms sont mis en maj
            }
        }
        sort(data_entreprise.begin(), data_entreprise.end()); // je trie le tableau (par nom d'entreprise car c'est le premier champ de chaque sous tableau)



        string html_filename = "output/output_entreprise.html";
        ofstream html(html_filename);
        if(!html.is_open()) //teste si le fichier peut être ouvert
        {
            cout << "could not open html file" << endl;
            exit(1);
        }
        else /// écriture du fichier html
        {
            cout << "Ecriture du fichier html..." << endl;
            html << "<!DOCTYPE html><html lang=\"fr\"><head><meta charset=\"utf-8\"/><title>Mode par entreprise</title></head>" << endl; // En-tête HTML
            for (int i=0; i<data_entreprise.size(); i++)
            {
                html << "<img class=\"photo_entreprise\" src=\"../../../logos/" << data_entreprise[i][3] << "\" alt=\"logo de " << data_entreprise[i][0]<<"\" />" << endl; // écriture de l'image de l'entreprise

                html << "<section class=\"entreprise\">" << endl << endl; // J'ouvre une section pour chaque entreprise pour écrire ses données et les élèves membres

                html << "<h2>" << data_entreprise[i][0] << " : \"" << data_entreprise[i][2] << "\"</h2>" << endl;

                for(int j=0; j < data_eleve.size(); j++){ //pour chaque élève

                    if(data_eleve[j][4] == data_entreprise[i][0]){ // si son entreprise correspond avec l'entreprise courante

                        html << "<div class=\"eleve_entreprise\">"; //J'ouvre une balise div
                        if(data_eleve[j][5]=="0"){ // Si l'élève n'a pas renseigné de photo, je mets celle par défaut
                            html << "<img src=\"photo_default.jpg\" width=\"105\" height=\"135\" alt=\"photo de " << data_eleve[j][0]<<"\" />";
                        }
                        else{ //Sinon je mets celle à l'adresse correspondant à son identifiant
                            html<<"<img src=\"../../../photos/"<<data_eleve[j][5]<<"\" width=\"105\" height=\"135\" alt=\"photo de "<<data_eleve[j][0]<<"\" />";
                        }
                        html << "<p>"; //écriture des données de l'élève dans un paragraphe
                        html << "<strong>" << data_eleve[j][0] << " " << data_eleve[j][2] << "</strong><br>";
                        html << data_eleve[j][3];
                        html << "</p></div>" << endl;
                    }
                }
                html << "</section>" << endl << endl;
            }
            html << "</html>" << endl;
        }
        cout << "Fait ! Vous pouvez ouvrir le fichier html dans le dossier \"output\"";
    }
    else{
        cout << "Erreur : saisie incorrect";
        exit(1);
    }
    return 0;
}
