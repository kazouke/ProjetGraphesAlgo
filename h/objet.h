#ifndef OBJET_H
#define OBJET_H

#include "adjacence.h"
#include "fileSuccesseurs.h"
#include "pointeurs.h"
#include <string>
class objet {
public:
	//Adrien
	~objet() { delete t1, t2, t3; }

	//Constructeurs - Adrien
	objet() { type = 0;t1 = 0;t2 = 0;t3 = 0; }
	objet(adjacence*a) { type = 1;t1 = a;t2 = 0;t3 = 0; }
	objet(fileSuccesseurs*f) { type = 2;t1 = 0;t2 = f;t3 = 0; }
	objet(pointeurs*p) { type = 3;t1 = 0;t2 = 0;t3 = p; }

	//Get - Adrien
	adjacence*			getType1() { convertToType1();return t1; }
	fileSuccesseurs*	getType2() { convertToType2();return t2; }
	pointeurs*			getType3() { convertToType3();return t3; }

	//Set - Adrien
	void chargerAdjacence(adjacence *&a)
	{
		convertToType0();
		t1 = a;
		type = 1;
		a = 0;
	}

	//Adrien - Gère la modification des sommets et des arcs du graph - Traite le type 1
	void modifierTableau()
	{
		string mot;
		int s, t, x;
		convertToType1();
		do
		{
			system("cls");
			afficher();
			cout << "Modification du graph" << endl;
			cout << "Entrez le sommet de depart : ";
			cin >> mot;
			s = convertEntier(mot);
			if (0 < s)
			{
				cout << "Entrez le sommet d'arrive  : ";
				cin >> mot;
				t = convertEntier(mot);
				if (0 < t)
				{
					cout << "Entrez le cout du trajet   : ";
					cin >> mot;
					x = convertEntier(mot);
					if (x != -INT_MAX) t1->setValeurLien(s, t, x);
				}
			}
		} while (0<s && 0<t && s <= valeurLien(0, 0) && t <= valeurLien(0, 0) && x != -INT_MAX);
	}

	//Convert - Adrien - Gère la conversion entre les types de graphs
	//Adrien - Vide tout les graphs
	void convertToType0() { type = 0;delete t1, t2, t3; }

	void convertToType1()
	{
		if (type == 1) return;
		if (type == 3) convertToType2();
		if (type == 2) { fs_aps2Mat();type = 1;delete t2;t2 = 0; }
	}
	void convertToType2()
	{
		if (type == 1) { Mat2fs_aps();type = 2;delete t1;t1 = 0; }
		if (type == 2) return;
		if (type == 3) {
			pointeur2fs_aps(); type = 2;delete t3;t3 = nullptr;
		} 
	}

	void convertToType3()
	{
		if (type == 1) convertToType2();
		if (type == 2) { fs_aps2Pointeurs(); type = 3; delete t2;t2 = nullptr; } // A FAIRE
		if (type == 3) return;
	}

	//Générique - Adrien
	void afficher()
	{
		if (type == 0) return;
		if (type == 1) t1->afficher();
		if (type == 2) t2->afficher();
		if (type==3) t3->afficher(); 
	}

	//Adrien - Retourne la valeur du lien s|t
	int valeurLien(int s, int t)
	{
		if (type == 0) return -INT_MAX;
		if (type >= 2) convertToType1();
		return t1->getValeurLien(s, t);
	}


	//Algo de transformation - Adrien
	void Mat2fs_aps()
	{
		int cpt = 0;
		int n = t1->getValeurLien(0, 0);
		for (int i = 1;i <= n;i++) for (int j = 1;j <= n;j++) if (t1->getValeurLien(i, j)>0) cpt++;
		t2 = new fileSuccesseurs(n, cpt + n);
		cpt = 1;
		//t2->setValeur(1, 0);
		for (int i = 1;i <= n;i++)
		{
			for (int j = 1;j <= n;j++) if (t1->getValeurLien(i, j)>0)
			{
				t2->setValeur(cpt, j);
				cpt++;
			}
			t2->setValeur(cpt, 0);
			cpt++;
		}
		t2->mettreAJourAps();
	}

	void fs_aps2Mat()
	{
		int n = t2->getNbSommets();
		t1 = new adjacence(n);
		t1->setValeurLien(0, 0, n);
		n = t2->getValeur(0);
		int cpt = 1;
		for (int i = 1;i <= n;i++)
			if (t2->getValeur(i) == 0) cpt++;
			else t1->setValeurLien(cpt, t2->getValeur(i), 1);
	}
	//Romain
	void fs_aps2Pointeurs()
	{
		int nbSommet = t2->getNbSommets();
		t3 = new pointeurs();
		//construction sommets
		for (int i = 1;i <=nbSommet;i++)
		{
			cout << i << endl;
			t3->ajouter(i);
		}
		
		// construction des successeurs
		for (int i = 1;i <= nbSommet;i++)
		{
			for (int j = t2->getAps(i);int k=t2->getValeur(j) != 0;j++)
			{
				t3->ajouterSuccesseur(i, k);
			}
		}
	}
	//ROmain
	void pointeur2fs_aps()
	{
		
		int nbSommet = t3->getNbSommets();
		cout << "oui";
		int nbArcs = t3->getNbArcs();
		cout << "oui";
		t2 = new fileSuccesseurs(nbSommet, nbArcs+nbSommet);
		int cpt = 1;
		cout << "oui";
		for (int i = 1;i <= nbSommet;i++)
		{
			for (int j = 0;j < t3->getNbSuccesseur(i);j++)
			{
				t2->setValeur(cpt, t3->getSuccesseur(j, i));
				cpt++;
			}
			t2->setValeur(cpt, 0);
			cpt++;
		}

		t2->mettreAJourAps();
	}

	

	private:
	int 	type;				//Contient le type de l'objet - gère la comptabilité
	adjacence		*t1;		//type=1 - Matrice d'Adjacence
	fileSuccesseurs	*t2;		//type=2 - File des successeurs
	pointeurs		*t3;		//type=3 - Représentation par pointeurs

								//Adrien - Transformer un string en entier - évite les crash avec les "cin>>"
	int convertEntier(string n)
	{
		bool erreur = false;
		int x = 0;
		for (int i = 0; i<n.length(); i++)
		{
			if ('0' <= n[i] && n[i] <= '9') x = x * 10 + n[i] - '0';
			else erreur = true;
		}
		if (erreur) return -INT_MAX;
		return x;
	}
};

#endif
