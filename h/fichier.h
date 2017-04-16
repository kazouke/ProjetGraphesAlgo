#ifndef FICHIER_H
#define FICHIER_H

#include "objet.h"
#include <fstream>
using namespace std;

class fichier{
	public:
		//Constructeurs - Adrien
		fichier() = delete;
		fichier(string nomFichier){
			_nomFichier=nomFichier;
			if (nomFichier.substr(nomFichier.length()-4) != ".txt") _nomFichier+=".txt";
		}
		
		//Adrien - sauvegarde le graph dans un fichier - false en cas d'erreur
		bool sauvegarder(objet & o){
			o.convertToType1();
			ofstream ecrire(_nomFichier);
			
			int taille = o.valeurLien(0,0);
			ecrire<< taille;
			for (int i = 1; i <= taille; i++)
				for (int j = 1; j <= taille; j++)
					ecrire<<' '<<o.valeurLien(i,j);
					
			ecrire.close();
		}
		
		//Adrien - charge le graph d'un fichier - false en cas d'erreur
		bool charger(objet & o){
			bool succes=false;
			int x;
			ifstream lire(_nomFichier);
			
			if (lire){
				lire>>x;
				adjacence *a =new adjacence(x);
				for (int i = 1; i <= a->getValeurLien(0,0); i++)
					for (int j = 1; j <= a->getValeurLien(0,0); j++){
						lire>>x;
						a->setValeurLien(i,j,x);
					}
				succes = true;
				o.chargerAdjacence(a);
			}
			
			lire.close();
			return succes;
		}
		
		//Adrien - Changer le nom du fichier
		void setNomFichier(string nomFichier){
			_nomFichier=nomFichier;
		}
		
		//Adrien - Retourne le nom du fichier
		string getNomFichier(){
			return _nomFichier;
		}
		
	private:
		string _nomFichier;
};

#endif
