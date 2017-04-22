#ifndef POINTEURS_H
#define POINTEURS_H

/////////////////////////LISTE CHAINEE//////////////////
class chainonSuccesseur;
//Romain
class chainon
{
	friend class pointeurs;
private:
	chainon(double val) :v(val), suiv(nullptr),succ(nullptr)
	{}
	//rajoute un successeur
	void addSuccesseur(chainonSuccesseur* succ)
	{
		this->succ = succ;
	}
	//ajoute un suivant
	void addSuivant(chainon* suiv)
	{
		this->suiv = suiv;
	}
	//valeur du sommet
	double v;
	//sommet suivant dans la liste principale
	chainon* suiv;
	//premier successeur
	chainonSuccesseur* succ; //good succ
};
//Romain
class chainonSuccesseur
{
	friend class chainon;
	friend class pointeurs;
	private:
		chainonSuccesseur(chainon* v) : v(v), suiv(nullptr)
		{

		}
		//ajoute un suivant
		void addSuivant(chainonSuccesseur* suiv)
		{
			this->suiv = suiv;
		}
		
		//pointeur sur le sommet dans la liste principale
		chainon *v;
		//successeur suivant
		chainonSuccesseur *suiv;
};
class pointeurs
{
private:
	chainon *t;

public:
	//Constructeur
	pointeurs() :t(nullptr)
	{}

	//Destructeur
	~pointeurs()
	{
		while (t) // t != 0
		{
			chainon *tmp = t->suiv;
			chainonSuccesseur *tmp2 = t->succ;
			while (tmp2)
			{
				tmp2 = tmp2->suiv;
				delete t->succ;
				t->succ = tmp2;
			}
			delete t;
			t = tmp;
		}
	}

	//Méthode qui retourne la taille de la liste, donc nombre de sommet
	int getNbSommets() const
	{
		int taille = 0;
		chainon *tmp = t;
		while (tmp)
		{
			taille++;
			tmp = tmp->suiv;
		}
		return taille;
	}
	//renvoie le nombre d'arcs
	int getNbArcs() const
	{
		int nbArcs = 0;
		chainon *tmp = t;
		while (tmp)
		{
			chainonSuccesseur* tmp2;
			tmp2 = tmp->succ;
			while (tmp2)
			{
				nbArcs++;
				tmp2 = tmp2->suiv;
			}
		}
		return nbArcs;
	}
	//renvoie le nombre de successeur du sommet i
	int getNbSuccesseur(int i) const
	{
		int j = 1;
		chainon* tmp = t;
		while (tmp && j < i)
		{
			tmp = tmp->suiv;
			j++;
		}
		if (j == i)
		{
			chainonSuccesseur* tmp2 = tmp->succ;
			int cpt = 0;
			while (tmp2)
			{
				cpt++;
				tmp2 = tmp2->suiv;
			}
			return cpt;
		}
		return 0;
	}

	//methode pour avoir la valeur du successeur i du sommet val
	int getSuccesseur(int i, int val) const
	{
		chainon* tmp = t;
		int j = 0;
		while (tmp && j < val)
		{
			tmp = tmp->suiv;
			j++;
		}
		if (j == val)
		{
			chainonSuccesseur* tmp2 = tmp->succ;
			j = 0;
			while (tmp2 && j<i)
			{
				j++;
				tmp2 = tmp2->suiv;
			}
			if (j == i)
			{
				return tmp2->v->v;
			}
		}
		return -1;
	}
	//Méthode pour ajouter une valeur à la fin de la liste
	void ajouter(double val)
	{
		//Cas chaînon vide
		if (t == nullptr)
		{
			t = new chainon(val);
			return;
		}
		//Les autres cas
		chainon *tmp = t;
		while (tmp->suiv)
		{
			tmp = tmp->suiv;
		}
		
		tmp->addSuivant(new chainon(val));
	}
	//ajouter un successeur au sommet val
	void ajouterSuccesseur(double val, chainon* succ)
	{
		chainon* tmp = t;
		while (tmp )
		{
			if (tmp->v == val)
			{
				if (tmp->succ == nullptr)
				{
					tmp->succ = new chainonSuccesseur(succ);
				}
				else
				{
					chainonSuccesseur* tmp2 = tmp->succ;
					bool estPresent = false;
					while (tmp2)
					{
						if (tmp2->v = tmp)
						{
							tmp2 = nullptr;
							estPresent = true;
						}
						else
						{
							tmp2 = tmp2->suiv;
						}
					}
					if (!estPresent)
					{
						tmp2->addSuivant(new chainonSuccesseur(succ));
					}
				}
				tmp = nullptr;
			}
			else
			{
				tmp = tmp->suiv;
			}
			
		}
	}
	//ajoute un chainon successeur pointeur sur succ au sommet val
	void ajouterSuccesseur(double val, double succ)
	{
		chainon* tmp = t;
		while (tmp)
		{
			if (tmp->v == succ)
			{
				break;
			}
			tmp = tmp->suiv;
		}
		if (tmp->v == succ)
		{
			ajouterSuccesseur(val, tmp);
		}
	}
	//Méthode pour supprimer un chainon à la position i
	void supprimer(int i)
	{

		//Cas de la liste vide
		if (!t)
		{
			return;
		}
		
		//Cas du premier
		if (i == 1)
		{
			chainon *chainonADetruire = t;
			supprimerChainonSuccesseur(chainonADetruire);
			t = t->suiv;
			delete chainonADetruire;
		}
		//Les autres cas
		else
		{
			if (i < getNbSommets() && i >= 0)
			{
				chainon *cASup = t;
				chainon *cAvant = 0;
				for (int j = 0; j < i; j++)
				{
					cAvant = cASup;
					cASup = cASup->suiv;
				}
				cAvant->suiv = cASup->suiv;
				supprimerChainonSuccesseur(cASup);
				delete cASup;
			}

		}
	}

	//permet de chercher dans les chainonSuccesseurs ceux dont la valeur est le chainon aDetruire
	void supprimerChainonSuccesseur(chainon* aDetruire)
	{
		chainon* tmp = t;
		while (tmp)
		{
			if (tmp != aDetruire)
			{
				chainonSuccesseur* tmp2 = tmp->succ;
				while (tmp2->v == aDetruire)
				{
					tmp->succ = tmp2->suiv;
					delete tmp2;
					tmp2 = tmp->succ;
				}
				chainonSuccesseur* prec = tmp2;
				tmp2 = tmp2->suiv;
				while(tmp2)
				{
					if (tmp2->v == aDetruire)
					{
						prec->suiv = tmp2->suiv;

						delete tmp2;
						tmp2 = prec->suiv;
					}
					else 
					{
						prec = tmp2;
						tmp2 = tmp2->suiv;
					}
					
				}
				
			}
			tmp = tmp->suiv;
		}
	}
	//Méthode qui retourne la valeur à la position i, -1 si pas dans la liste
	double getValeur(int i) const
	{
		int val = -1;

		if (i < getNbSommets() && i >=0)
		{
			chainon *tmp = t;
			for (int j = 0; j < i; j++)
			{
				tmp = tmp->suiv;
			}
			val = tmp->v;
		}
		return val;
	}

	//Méthode pour modifier la valeur à la position i
	void setValeur(int i, int val)
	{
		if (i < getNbSommets() && i > 0)
		{
			chainon *tmp = t;
			for (int j = 0; j < i; j++)
			{
				tmp = tmp->suiv;
			}
			tmp->v = val;
		}
	}

	//Méthode qui affiche les pointeurs
	void afficher() const {
		int i = 0;
		int val;
		cout << "---------------pointeurs--------------";
		cout << endl << "Taille de la liste : " << getNbSommets();
		cout << endl << "Valeurs : " << endl << "[ ";
		while (i < getNbSommets())
		{
			
			val = getValeur(i);
			cout << val << " :";
			for (int j = 0;j < getNbSuccesseur(i);j++)
			{
				cout << getSuccesseur(j, i)<<" ";
			}
			cout << endl;
			i++;
		}
		cout << " ]";
		cout << endl << "---------------------------------------------";
	}
};

#endif