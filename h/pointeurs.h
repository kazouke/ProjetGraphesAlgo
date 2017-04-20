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
	private:
		Chainon *t;
	
	public:
		//Constructeur
		pointeurs():t(0)
		{}
		
		//Destructeur
		~pointeurs()
		{
			while(t) // t != 0
			{
				chainon *tmp=t->suiv;
				delete t;
				t = tmp;
			}
		}
		
		//Méthode qui retourne la taille de la liste
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
		//Méthode pour ajouter une valeur à la fin de la liste
		void ajouter(double val)
		{
			//Cas chaînon vide
			if(t==0)
			{
				t= new chainon(val);
				return;
			}
			//Les autres cas
			while(tmp)
			{
				tmp=tmp->suiv;
			}
			tmp->suiv = new chainon(val);
		}
		
		//Méthode pour supprimer un chainon à la position i
		void supprimer(int i)
		{
			
			//Cas de la liste vide
			if(!t)
			{
				return;
			}
			//Cas du premier
			if(i == 1)
			{
				chainon *tmp = t;
				t = t->suiv;
				delete tmp;
			}
			//Les autres cas
			else
			{
				if(i < taille() && i >= 0)
				{
					chainon *cASup = t;
					chainon *cAvant = 0;
					for(int j = 0; j < i; j++)
					{
						cAvant = cASup;
						cASup=cASup->suiv;
					}
					cAvant->suiv = cASup->suiv;
					delete cASup;
				}
				
			}		
		}
		
		//Méthode qui retourne la valeur à la position i, -1 si pas dans la liste
		double getValeur(int i) const
		{
			int val = -1;
			
			if(i < taille() && i > 0)
			{
				chainon *tmp = t;
				for(int j = 0; j < i; j++)
				{
					tmp=tmp->suiv;
				}
				val = tmp->v;
			}
			return val;
		}
		
		//Méthode pour modifier la valeur à la position i
		void setValeur(int i, int val)
		{
			if(i < taille() && i > 0)
			{
				chainon *tmp = t;
				for(int j = 0; j < i; j++)
				{
					tmp=tmp->suiv;
				}
				tmp->v = val;
			}
		}
		
		//Méthode qui affiche les pointeurs
		void afficher() const{
			int i = 0;
			int val;
			cout<<"---------------pointeurs--------------";
			cout<<endl<<"Taille de la liste : "<<taille();
			cout<<endl<<"Valeurs : "<<endl<<"[ ";
			while(i < taille())
			{
				i++;
				val = getValeur(i);
				cout << val << " ";					
			}
			cout << " ]";
			cout<<endl<<"---------------------------------------------";
		}
};

#endif














