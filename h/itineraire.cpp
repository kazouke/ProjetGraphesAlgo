#include "itineraire.h"


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
	int distance;
	
	do 
	{
		system("cls");
		cout << "Ajout de routes" << endl;
		afficherMatrice();
		adjacence *a = o.getType1();
		do
		{
			cout << "Rentrez le numéro de la ville de départ (rentrez 0 pour quitter):" << endl;
			afficherVille();
			cin >> nbDep;
		} while (nbDep<0 || nbDep>nbVilles);
		
		if (nbDep >= 1 )
		{
			do
			{
				cout << "Rentrez le numéro de la ville d'arrivée :" << endl;
				afficherVille();
				cin >> nbArr;
			} while (nbDep < 1 || nbDep == nbArr || nbDep>nbVilles);
			
			do
			{
				cout << "Rentre la distance du trajet (>=0):" << endl;
				cin >> distance;
			} while (distance < 0);
			a->setValeurLien(nbDep, nbArr, distance);
			cout<<a->getValeurLien(nbDep, nbArr);
			system("pause");
			
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
	vector<int> chemins = o.Dijkstra(nbDep);
	/*cout << "oui";
	afficheChemin(nbDep, nbArr, chemins);*/
}

void itineraire::afficheChemin(int nbDep, int nbArr, vector<int> &chemins)
{
	if (nbDep == nbArr)
	{
		cout << nbDep<<endl;
	}
	else
	{
		cout << nbArr << " ";
		afficheChemin(nbDep, chemins[nbArr], chemins);
	}
}
