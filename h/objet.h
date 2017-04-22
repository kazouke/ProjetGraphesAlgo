#ifndef OBJET_H
#define OBJET_H

#include "adjacence.h"
#include "fileSuccesseurs.h"
#include "pointeurs.h"
#include <string>

const double MAXPOIDS =100.0;

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

	//Adrien - GÃ¨re la modification des sommets et des arcs du graph - Traite le type 1
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

	//Convert - Adrien - GÃ¨re la conversion entre les types de graphs
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

	//GÃ©nÃ©rique - Adrien
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
				t2->setValeur(cpt, j, t1->getValeurLien(i, j));
				cpt++;
			}
			t2->setValeur(cpt, 0, 0);
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
			else t1->setValeurLien(cpt, t2->getValeur(i), t2->getCout(i));
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
		int nbArcs = t3->getNbArcs();
		t2 = new fileSuccesseurs(nbSommet, nbArcs+nbSommet);
		int cpt = 1;
		for (int i = 1;i <= nbSommet;i++)
		{
			for (int j = 0;j < t3->getNbSuccesseur(i);j++)
			{
				t2->setValeur(cpt, t3->getSuccesseur(j, i), -5); //A MODIFIER -5 par le cout
				cpt++;
			}
			t2->setValeur(cpt, 0, 0);
			cpt++;
		}

		t2->mettreAJourAps();
	}
	
	//jp
	vector<int> Dijkstra(int s)
	{
		int cpt,v,j,k,indiceCout;
		double max;
		vector<int> d,pred;
		
		int n = this->getType2()->getNbSommets();
		
		d.resize(n+1);
		d[0] = n;
		pred.resize(n+1);
		vector<bool> dansS;
		dansS.resize(n+1);
		
		for(int i=1; i<=n; i++) 
		{
			indiceCout = this->getType2()->getAps(s);
			while(this->getType2()->getValeur(indiceCout) != 0 || this->getType2()->getValeur(indiceCout) != i)
			{
				indiceCout++;
			}
			if(indiceCout != 0)
			{
				d[i] = this->getType2()->getCout(indiceCout);
			}
			else d[i] = -INT_MAX;
			
			if(d[i] != MAXPOIDS)
				pred[i] = s;
			else
				pred[i] = -1;
			dansS[i] = true;
		}
		
		
		dansS[s] = false;
		d[s] = 0;
		cpt = n - 1;	
		while(cpt > 0)
		{
			max = MAXPOIDS;
			for(int i=1; i<=n; i++)
			{
				
				
				if(dansS[i] && d[i] < max) 
				{
					max = d[i];
					j=i;
				}
				if(max == MAXPOIDS)
				{
					break;
				}
				
				dansS[j] = false;
				cpt--;
				for(int h=this->getType2()->getAps(j); (k=this->getType2()->getValeur(h))!=0; h++) 
				{
					
					if(dansS[k]) 
					{
						indiceCout = this->getType2()->getAps(j);
						while(this->getType2()->getValeur(indiceCout) != 0 || this->getType2()->getValeur(indiceCout) != k)
						{
							indiceCout++;
						}
						if(indiceCout != 0)
						{
							v=d[j]+ this->getType2()->getCout(indiceCout);
						}
						else v = -INT_MAX;
						
						if(v<d[k]) 
						{
							d[k]=v;
							pred[k]=j;
						}
					}
				}
			}
		}
		
		return d;
	}
	
	//jp
	vector<int> ddi() //renvoie le demi degré intérieur
	{
		vector<int> d(this->getType2()->getNbSommets()+1,0);
		
		for(int j = 1; j <= this->getType2()->getValeur(0); j++)
			d[this->getType2()->getValeur(j)]++;
			
		return d;
	}
	
	//jp
	bool arborescence() // renvoie vrai si le graphe est une arborescence
	{	
		if(this->getType2()->getValeur(0) != this->getType2()->getNbSommets() * 2 - 1) 
			return false;
		
		vector<int> d(this->getType2()->getNbSommets()+1,0);
						
		for(int j = 1; j <= this->getType2()->getValeur(0); j++)
		{
			d[this->getType2()->getValeur(j)]++;
			if(d[this->getType2()->getValeur(j)] > 1)
				return false;
		}
		
		return true;
	}
	
	//jp
	vector<int> d2app() //renvoie un vecteur de l'adresse des premiers prédécesseurs à partir du ddi
	{
		vector<int> d = ddi();
		int n = d[0];
		vector<int> app;
		app.resize(n+1);
		app[0] = n; app[1] = 1;
		
		for(int i = 1; i < n; i++)
			app[i+1] = app[i] + d[i] + 1;
		
		return app;
	}
	
	//jp
	vector<int> fs_app2fp()
	{
		vector<int> fp;
		vector<int> app = d2app();
		int n = this->getType2()->getValeur(0);
		int cpt = 1;
		for(int i = 1; i <= n; i++)
		{
			if(this->getType2()->getValeur(i) == 0)
				cpt++;
			else
			{
				fp[app[this->getType2()->getValeur(i)]] = cpt;
				app[this->getType2()->getValeur(i)]++;
			}
		}
		
		return fp;
	}
	
	//jp
	void fs_aps2fp_app(vector<int> &fp, vector<int> &app) //rempli les vecteurs de la file des pred et de l'app à partir de fs et aps
	{
		int n = this->getType2()->getNbSommets();
		int m = this->getType2()->getValeur(0);
		
		vector<int> d = ddi();
		app = d2app();
		
		fp.resize(m+1);
		fp[0] = m;
		
		int s = 1;
		for(int i = 1; i < m; i++)
		{
			if(this->getType2()->getValeur(i) != 0)
			{
				fp[app[this->getType2()->getValeur(i)]] = s;
				app[this->getType2()->getValeur(i)]++;
			}
			else
				s++;
		}
		for(int i = n; i > 1; i--)
		{
			fp[app[i]] = 0;
			app[i] = app[i-1] + 1;
		}
		app[1]=1;
	}

	

	private:
	int 	type;				//Contient le type de l'objet - gÃ¨re la comptabilitÃ©
	adjacence		*t1;		//type=1 - Matrice d'Adjacence
	fileSuccesseurs	*t2;		//type=2 - File des successeurs
	pointeurs		*t3;		//type=3 - ReprÃ©sentation par pointeurs

								//Adrien - Transformer un string en entier - Ã©vite les crash avec les "cin>>"
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
