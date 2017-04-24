#include "itineraire.h"

const string FICHIERVILLE="ville.txt";
////romain
itineraire::itineraire() : o{},villes()
{
}

void itineraire::initialiser()
{
	
	cout << "Nombre de villes : ";
	cin >> nbVilles;
	adjacence *a = new adjacence(nbVilles);
	string nomVille;
	cout << "Rentrez le nom de chaque ville (l'ordre est important)" << endl;
	villes.push_back(" ");
	for (int i = 0;i < nbVilles;i++)
	{
		cin >> nomVille;
		villes.push_back(nomVille);
	}
	o.chargerAdjacence(a);

}

void itineraire::modifierRoutes()
{
	int nbDep, nbArr;
	int distance,sensUnique;
	
	do 
	{
		system("cls");
		cout << "Ajout de routes" << endl;
		afficherMatrice();
		adjacence *a = o.getType1();
		do
		{
			cout << "Rentrez le numéro de la ville de depart (rentrez 0 pour quitter):" << endl;
			afficherVille();
			cin >> nbDep;
		} while (nbDep<0 || nbDep>nbVilles);
		
		if (nbDep >= 1 )
		{
			do
			{
				cout << "Rentrez le numero de la ville d'arrivee :" << endl;
				afficherVille();
				cin >> nbArr;
			} while (nbDep < 1 || nbDep == nbArr || nbDep>nbVilles);
			
			do
			{
				cout << "Rentrez la longueur de la route (>=0):" << endl;
				cin >> distance;
			} while (distance < 0);
			do
			{
				cout<<"Route a sens unique ? (1=Oui, 2=Non)"<<endl;
				cin>>sensUnique;
			}while(sensUnique<=0 && sensUnique>2);
			if(sensUnique==2)
			{
				a->setValeurLien(nbArr,nbDep,distance);
			}
			a->setValeurLien(nbDep, nbArr, distance);
			cout<<a->getValeurLien(nbDep, nbArr);
			
		}
	} while (nbDep != 0);
	
	

}

void itineraire::afficherVille()
{
	for (int i = 1;i <= nbVilles;i++)
	{
		cout << i << ". " << villes[i]<<endl;
	}
}

void itineraire::afficherMatrice()
{
	adjacence *a = o.getType1();
	cout << endl <<setw(10)<< "    |";
	for (int i = 1;i <= nbVilles;i++)
	{
		cout << setw(10) << villes[i] << ' ';
	}
	cout << endl;
	for (int i = 0;i <= nbVilles;i++)
	{
		cout <<"-----------";
	}
	cout << endl;
	for (int i = 1;i <= nbVilles;i++)
	{
		cout << setw(10) << villes[i] << '|';
		for (int j = 1;j <= nbVilles;j++) cout << setw(10) << a->getValeurLien(i,j) << ' ';
		cout << endl;
	}
}

void itineraire::calculerItineraire()
{
	int nbDep, nbArr;
	system("cls");
	cout << "Calcul d'itineraire" << endl;
	do
	{
		cout << "Rentrez le numéro de la ville de départ :" << endl;
		afficherVille();
		cin >> nbDep;
	} while (nbDep<0 || nbDep>nbVilles);
	do
	{
		cout << "Rentrez le numéro de la ville d'arrivée :" << endl;
		afficherVille();
		cin >> nbArr;
	} while (nbDep < 1 || nbDep == nbArr || nbDep>nbVilles);
	vector<int> pred;
	vector<int> chemins = o.Dijkstra(nbDep,pred);
	string s{};
	trouveChemin(nbDep, nbArr, pred,s);
	cout<<"Le chemin le plus rapide est le suivant :"<<s<<endl;
}

void itineraire::trouveChemin(int nbDep, int nbArr, const vector<int> &chemins, string &route)
{
	if (nbDep == nbArr)
	{
		route=villes[nbDep]+" "+route;
		//cout << villes[nbDep<<endl;
	}
	else
	{
		route=villes[nbArr]+" "+route;
		//cout << villes[nbArr]<< " ";
		trouveChemin(nbDep, chemins[nbArr], chemins,route);
	}
}

void itineraire::sauvegarder() 
{
	ofstream out(FICHIERVILLE);
	
	if(out)
	{
		out<<nbVilles<<endl;
		for(int i=1;i<=nbVilles;i++)
		{
			out<<villes[i]<<endl;
		}
		adjacence *a = o.getType1();
		out<<a->getNbLien()<<endl;
		for(int i=1;i<=a->getTaille();i++)
		{
			for(int j=1;j<=a->getTaille();j++)
			{
				if(a->getValeurLien(i,j)!=0)
				{
					out<<i<<" "<<j<<" "<<a->getValeurLien(i,j)<<endl;
				}
			}
		}
	}
	out.close();
}

void itineraire::charger()
{
	ifstream in(FICHIERVILLE);
	if(in)
	{
		in>>nbVilles;
		villes.resize(nbVilles+1);
		for(int i=1;i<=nbVilles;i++)
		{
			in>>villes[i];
		}
		adjacence *a= new adjacence(nbVilles);
		int nbRoutes, nbDep, nbArr, distance;
		in>>nbRoutes;
		for(int i=0;i<nbRoutes;i++)
		{
			in>>nbDep>>nbArr>>distance;
			a->setValeurLien(nbDep,nbArr,distance);
		}
		o.chargerAdjacence(a);
		afficherMatrice();
	}
	in.close();
}


//Utilise les fonctionnalités de la classe
//Avec une interface utilisateur - Julien
void itineraire::menu()
{
	int choix = -1;
	
	while(choix != 0)
	{
		//system("cls");
		cout << endl << "Charger - 1" << endl;
		cout << "Sauvegarder - 2" << endl;
		cout << "Nouvel itinéraire - 3" << endl;
		cout << "Modifier itinéraire - 4" << endl;
		cout << "Calculer itinéraire - 5" << endl;
		
		cout << "Quitter - 0" << endl;
		cout << "Choix : "; cin >> choix;
		
		switch(choix)
		{
			case 1:
				charger();
				break;
			case 2:
				sauvegarder();
				break;
			case 3:
				initialiser();
				modifierRoutes();
				break;
			case 4:
				modifierRoutes();
				break;	
			case 5:
				calculerItineraire();
				break;
		}
	}

}
