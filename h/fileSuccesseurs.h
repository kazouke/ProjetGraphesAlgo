#ifndef FILESUCCESSEURS_H
#define FILESUCCESSEURS_H

#include <vector>
#include <iomanip>
using namespace std;

class fileSuccesseurs {
public:
	//Constructeurs - Adrien
	fileSuccesseurs() = delete;
	fileSuccesseurs(int nbSommets, int nbArcs) {
		fs.resize(nbArcs + 1);
		fcout.resize(nbArcs + 1);
		aps.resize(nbSommets + 1);
		fs[0] = nbArcs;
		fcout[0] = nbArcs;
		aps[0] = nbSommets;
	}

	//Set - Adrien
	void setValeur(int n, int x, int cout) { fs[n] = x; fcout[n] = cout;}
	//Get - Adrien
	int getValeur(int n) const { return fs[n]; }
	int getCout(int n) const { return fcout[n]; }
	int getNbSommets()   const { return aps[0]; }
	int getNbArcs()      const { return fs[0] - aps[0]; }
	//Get - Romain
	int getAps(int n) const { return aps[n]; }

	//Adrien - Actualise APS
	void mettreAJourAps() {
		aps[1] = 1;
		int cpt = 2;
		for (int i = 2; i <= fs[0]; i++) if (fs[i] == 0) {
			aps[cpt] = i;
			cpt++;
		}
	}

	//Adrien
	void afficher() const {
		int smt = 1;
		cout << "---------------file successeurs--------------";
		cout << endl << "i   : ";
		for (int i = 1;i <= fs[0];i++) cout << setw(8) << i << ' ';
		cout << endl << "fs  : ";
		for (int i = 1;i <= fs[0];i++) cout << setw(3) << fs[i] <<'('<< setw(3)<<fcout[i] <<')'<<' ';
		cout << endl << "aps : ";
		for (int i = 1;i <= aps[0];i++) cout << setw(8) << aps[i] << ' ';
		cout << endl << "---------------------------------------------";
	}

private:
	vector<int>fs;
	vector<int>fcout;
	vector<int>aps;
};

#endif
