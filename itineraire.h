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
	void trouveChemin(int nbDep, int NbArr, const vector<int>& chemins, string &route);
	

private:
	objet o;
	vector<string> villes;
	int nbVilles;
};
