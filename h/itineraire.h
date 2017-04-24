#ifndef ITINERAIRE_H
#define ITINERAIRE_H


#include "objet.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
/////Romain & Julien
class itineraire
{
public:

	itineraire();
	void initialiser();
	void modifierRoutes();
	void afficherVille();
	void afficherMatrice();
	void calculerItineraire();
	void trouveChemin(int nbDep, int NbArr, const vector<int>& chemins, string &route);
	
	void sauvegarder();
	void charger();
	void menu();

private:
	objet o;
	vector<string> villes;
	int nbVilles;
};
#endif
