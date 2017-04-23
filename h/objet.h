#ifndef OBJET_H
#define OBJET_H

#include "adjacence.h"
#include "fileSuccesseurs.h"
#include "pointeurs.h"
#include <string>

const int MAXPOIDS = INT_MAX;

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

	//Adrien - GÃƒÂ¨re la modification des sommets et des arcs du graph - Traite le type 1
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

	//Convert - Adrien - GÃƒÂ¨re la conversion entre les types de graphs
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

	//GÃƒÂ©nÃƒÂ©rique - Adrien
	void afficher()
	{
		if (type == 0) return;
		if (type == 1) t1->afficher();
		if (type == 2) t2->afficher();
		if (type == 3) t3->afficher();
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
		t2 = new fileSuccesseurs(n, cpt + n+1);
		cpt = 1;
		for (int i = 1;i <= n;i++)
		{
			for (int j = 1;j <= n;j++) if (t1->getValeurLien(i, j)>0)
			{
				t2->setValeur(cpt, j, t1->getValeurLien(i, j));
				cpt++;
			}
			if(i!=n)
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
		for (int i = 1;i <= nbSommet;i++)
		{
			cout << i << endl;
			t3->ajouter(i);
		}

		// construction des successeurs
		for (int i = 1;i <= nbSommet;i++)
		{
			for (int j = t2->getAps(i);int k = t2->getValeur(j) != 0;j++)
			{
				t3->ajouterSuccesseur(i, k, t2->getCout(j));
			}
		}
	}
	//ROmain
	void pointeur2fs_aps()
	{

		int nbSommet = t3->getNbSommets();
		int nbArcs = t3->getNbArcs();
		t2 = new fileSuccesseurs(nbSommet, nbArcs + nbSommet);
		int cpt = 1;
		for (int i = 1;i <= nbSommet;i++)
		{
			for (int j = 0;j < t3->getNbSuccesseur(i);j++)
			{
				t2->setValeur(cpt, t3->getSuccesseur(j, i), t3->getCout(j, i));
				cpt++;
			}
			t2->setValeur(cpt, 0, 0);
			cpt++;
		}

		t2->mettreAJourAps();
	}

	//jp,romain
	vector<int> Dijkstra(int s, vector<int> &pred)
	{
	
		convertToType2();
		int cpt, v, j, k, indiceCout;
		int max;
		vector<int> d{};
	
		int n = t2->getNbSommets();

		d.resize(n + 1);
		d[0] = n;
		pred.resize(n + 1);
		vector<bool> dansS;
		dansS.resize(n + 1);

		for (int i = 1; i <= n; i++)
		{
			
			
			indiceCout=t2->getAps(s);
			while(t2->getValeur(indiceCout)!=0 && t2->getValeur(indiceCout)!=i)
			{
				indiceCout++;
			}
			if(t2->getValeur(indiceCout)==0)
			{
				d[i]=MAXPOIDS;
				pred[i]=0;
			}
			else
			{
				d[i]=t2->getCout(indiceCout);
				pred[i]=s;
			}
			dansS[i]=true;
		}


		dansS[s] = false;
		d[s] = 0;
		pred[s]=0;
		cpt = n - 1;
		while (cpt > 0)
		{
			max = MAXPOIDS;
			for (int i = 1; i <= n; i++)
			{


				if (dansS[i] && d[i] < max)
				{
					max = d[i];
					j = i;
				}
			}
			if (max == MAXPOIDS)
			{
				break;
			}
			else
			{
				dansS[j] = false;
			
				cpt--;
				for (int h = t2->getAps(j); (k = t2->getValeur(h)) != 0; h++)
				{
						
					if (dansS[k])
					{
					
						v=d[j]+t2->getCout(h);
					
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
		convertToType2();
		vector<int> d(t2->getNbSommets() + 1, 0);

		for (int j = 1; j <= t2->getValeur(0); j++)
			d[t2->getValeur(j)]++;

		return d;
	}

	//jp
	bool arborescence() // renvoie vrai si le graphe est une arborescence
	{
		convertToType2();
		if (t2->getValeur(0) != t2->getNbSommets() * 2 - 1)
			return false;

		vector<int> d(t2->getNbSommets() + 1, 0);

		for (int j = 1; j <= t2->getValeur(0); j++)
		{
			d[t2->getValeur(j)]++;
			if (d[t2->getValeur(j)] > 1)
				return false;
		}

		return true;
	}

	//jp
	vector<int> d2app() //renvoie un vecteur de l'adresse des premiers prédécesseurs à partir du ddi
	{
		convertToType2();
		vector<int> d = ddi();
		int n = d[0];
		vector<int> app;
		app.resize(n + 1);
		app[0] = n; app[1] = 1;

		for (int i = 1; i < n; i++)
			app[i + 1] = app[i] + d[i] + 1;

		return app;
	}

	//jp
	vector<int> fs_app2fp()
	{
		convertToType2();
		vector<int> fp;
		vector<int> app = d2app();
		int n = t2->getValeur(0);
		int cpt = 1;
		for (int i = 1; i <= n; i++)
		{
			if (t2->getValeur(i) == 0)
				cpt++;
			else
			{
				fp[app[t2->getValeur(i)]] = cpt;
				app[t2->getValeur(i)]++;
			}
		}

		return fp;
	}

	//jp
	void fs_aps2fp_app(vector<int> &fp, vector<int> &app) //rempli les vecteurs de la file des pred et de l'app à partir de fs et aps
	{
		convertToType2();
		int n = t2->getNbSommets();
		int m = t2->getValeur(0);

		vector<int> d = ddi();
		app = d2app();

		fp.resize(m + 1);
		fp[0] = m;

		int s = 1;
		for (int i = 1; i < m; i++)
		{
			if (t2->getValeur(i) != 0)
			{
				fp[app[t2->getValeur(i)]] = s;
				app[t2->getValeur(i)]++;
			}
			else
				s++;
		}
		for (int i = n; i > 1; i--)
		{
			fp[app[i]] = 0;
			app[i] = app[i - 1] + 1;
		}
		app[1] = 1;
	}

	//jp
	/*	void chemins_critiques(vector<int> &lc, vector<int> &fpc, vector<int> &appc)
	{
	int kc = 1; //indice de la dernière place remplie dans fpc
	int s = 0, k = 0, max  = 0;
	vector<int> d = ddi();
	vector<int> app;
	vector<int> fp;

	fs_aps2fp_app(fp,app);

	int n=app[0], m=fp[0];

	fpc.resize(m+1);
	appc.resize(n+1);
	lc.resize(n+1);

	lc[1] = 0;
	fpc[1] = 0;
	appc[1] = 1;

	for(int i=2 ; i<=n ; i++){
	k = app[i];
	lc[i] = 0;
	appc[i] = kc+1;
	while((s=fp[k])!=0){ //tant qu’il y a un préd. du sommet i
	max=lc[s]+d[s];
	if(max>=lc[i]){
	if(max >lc[i]){
	lc[i]=lg;  //?
	kc=appc[i];
	}else{
	kc++;
	fpc[kc]=s;
	}
	}
	k++;
	}
	kc++;
	fpc[kc]=0;
	}
	}*/

	//jp
	void nb_pred() //renvoie le nb de prédécesseurs pour chaque sommet
	{
		convertToType2();
		vector<int> fpred(t2->getAps(0) + 1, 0);

		for (int i = 1; i <= t2->getValeur(0); i++)
			fpred[t2->getValeur(i)]++;
	}

	//jp
	vector<int> calcul_d(int s) //renvoie le vecteur des distances du sommet s à tous les autres
	{
		convertToType2();
		int t = 0, q = 1, j;
		int p = 1; //p+1 la prochaine position libre entre 
				   //t+1 et q soit les sommets marqués et non traités
		int n = t2->getNbSommets();
		int dist = 0;
		vector<int> d;
		d.resize(n);
		vector<int> fa;
		fa.resize(n);
		d[s] = 0;

		while (t < q)
		{
			dist++;
			for (int i = t + 1; i <= q; i++)
			{
				for (int l = t2->getAps(fa[i]); (j = t2->getValeur(l)) > 0; l++)
				{
					if (d[j] == -1)
					{
						d[j] = dist;
						p++;
						fa[p] = j;
					}
				}
			}
			t = q;
			q = p;
		}
	}

	//jp
	vector<vector<int>> mat_dist() //renvoie la matrice des distances de chaque sommet
	{
		convertToType2();
		int n = t2->getNbSommets();
		vector<vector<int>> mat;
		for (int i = 1; i <= n; i++) {
			mat[i] = calcul_d(i);
		}

		return mat;
	}

	//jp
	void pred_chemin(int s)
	{
		convertToType2();
		int n = t2->getNbSommets(), t;
		vector<int> pred;
		pred.resize(n + 1);
		vector<int> d = calcul_d(s);
		for (int i = 1; i <= n; i++) {
			for (int j = t2->getAps(i); (t = t2->getValeur(j)) != 0; j++) {
				if (d[t] == d[i] + 1)
					pred[t] = i;
			}
		}
	}

	//jp
	void ppp(int r)
	{
		convertToType2();
		vector<int> pile;
		pile.resize(t2->getAps(0) + 1);
		pile[0] = r;
		int h = 1;
		int k = t2->getAps(r);

		while (h > 0)
		{
			if (t2->getValeur(k))
			{
				pile[h] = k;
				k = t2->getAps(k);
				h++;
				cout << t2->getValeur(k); //affichage en préordre
			}
			else
			{
				//cout<<t2->getValeur(k); //affichage en postordre
				h--;
				k = pile[h] + 1;
			}
		}
	}

	//jp
	vector<int> codagePrufer()
	{
		convertToType1();
		int n = t1->getTaille();
		vector<int> p;
		p.resize(n - 1);
		p[0] = n - 2;

		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
				t1->setCase(i, 0, t1->getCase(i, 0) + t1->getCase(i, j));

		int k = 1;
		while (k <= n)
		{
			int i = 1;
			for (i; t1->getCase(i, 0) != 1; i++);
			int j = 1;
			for (j; t1->getCase(i, j) != 1; j++);
			p[k++] = j;

			t1->setCase(i, 0, 0);
			t1->setCase(i, j, 0);
			t1->setCase(j, i, 0);
			t1->setCase(j, 0, t1->getCase(j, 0) - 1);
		}
		return p;
	}

	//jp
	vector<vector<int>> decodagePrufer(vector<int> p)
	{
		convertToType1();
		int m = p[0], n = m + 2;
		vector<vector<int>> adj;

		for (int i = 0; i <= n; i++)
			adj[i].resize(m + 1);
		adj[0][0] = n;
		adj[0][1] = n - 1;
		vector<int> s;
		s.resize(n + 1);
		vector<bool> b;
		b.resize(n + 1);

		for (int i = 1; i <= n; i++)
		{
			s[i] = 0;
			b[i] = true;
		}
		for (int i = 1; i <= n; i++)
			s[p[i]]++;
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				if ((b[i]) && (s[p[i]] == 0))
				{
					adj[i][p[k]] = 1;
					adj[p[k]][i] = 1;
					b[i] = false;
					s[p[k]]--;
					break;
				}
		int i = 1;
		for (;!b[i]; i++);
		//b[i] = false;
		int j = i + 1;
		for (;!b[j]; j++);
		adj[i][j] = 1;
		adj[j][i] = 1;

		return adj;
	}


private:
	int 	type;				//Contient le type de l'objet - gÃƒÂ¨re la comptabilitÃƒÂ©
	adjacence		*t1;		//type=1 - Matrice d'Adjacence
	fileSuccesseurs	*t2;		//type=2 - File des successeurs
	pointeurs		*t3;		//type=3 - ReprÃƒÂ©sentation par pointeurs

								//Adrien - Transformer un string en entier - ÃƒÂ©vite les crash avec les "cin>>"
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
