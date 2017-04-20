#ifndef POINTEURS_H
#define POINTEURS_H

/////////////////////////LISTE CHAINEE//////////////////
class chainon
{	friend class pointeurs;
	private:
		chainon(double val):v(val),suiv(0){}
		double v;
		chainon *suiv;
};

class pointeurs
{
	public:
		pointeurs();
		~pointeurs();
		int taille() const;
		void ajouter(double val);
		void supprimer(double val);
	private:
		Chainon *t;

	//Construction et destruction de pointeurs
	pointeurs():t(0)
	{}
	
	~pointeurs()
	{
		while(t) // t != 0
		{
			chainon *tmp=t->suiv;
			delete t;
			t = tmp;
		}
	}
	
	//Méthode qui retourne la taille de la liste chainée
	int taille() const
	{
		int taille=0;
		chainon *tmp = t;
		while(tmp)
		{
			taille++;
			tmp=tmp->suiv;
		}
		return taille;
	}
	//Méthode pour ajouter une valeur à la liste chaînée
	//Les valeurs sont classées par ordre croissant
	void ajouter(double val)
	{
		//Cas chaînon vide
		if(t==0)
		{
			t= new chainon(val);
			return;
		}
		//Cas tête
		if(v<t->v)
		{
			chainon *tmp = t;		
			t = new chainon(val);
			t->suiv = tmp;
			return;
		}
		//Le reste 
		chainon *c0 = 0, *c1=t;
		while(c1!=0 && c1->v < v)
		{
			c0=c1;
			c1=c1->suiv;
		}
		
		chainon *c = new chainon(v);
		c0->suiv = c;
		c->suiv = c1;
	}
	
	//Méthode pour supprimer un chainon
	void supprimer(double val)
	{
		//Cas de la liste vide
		if(t==0)
		{
			return;
		}
		//Cas du premier
		if(t->v == v)
		{
			chainon *tmp = t;
			t = t->suiv;
			delete tmp;
			return;
		}
		//Cas milieu
		chainon *c0=0, *c1=t;
		while(c1 != 0 && v > c1->v )
		{
			c0 = c1;
			c1 = c1->suiv;
		}
		if(c1!=0 && c1->v==v)
		{
			c0->suiv = c1->suiv;
			delete c1;
		}
	}

};

#endif














