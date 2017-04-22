#pragma once

#include "objet.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
/////Romain
class itineraire
{
public:

	itineraire();
	void initialiser();
	void modifierRoutes();
	void afficherVille();
	void afficherMatrice();
	void calculerItineraire();
	void afficheChemin(int nbDep, int NbArr, vector<int>& chemins);
	

private:
	objet o;
	vector<string> villes;
	int nbVilles;
};