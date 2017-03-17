#ifndef ADJACENCE_H
#define ADJACENCE_H

#include <vector>
#include <iomanip>
using namespace std;

class adjacence{
	public:
		adjacence(int taille){
			cout<<"une matrice d'adjacence de taille "<<taille <<" est creee."<<endl;
			t.resize(taille+1);
			for (int i=0;i<taille;i++)
			{
				t[i].resize(taille);
				for (int j=0;j<taille;j++) t[i][j]=0;
			}
			t[0][0]=taille;
		}
		
		void afficher(){
			for (int i=0;i<t[0][0];i++)
			{
				for (int j=0;j<t[0][0];j++) cout<<setw(3)<<t[i][j]<<' ';
				cout<<endl;
			}
		}
		
	private:
		vector<vector<int>>t;
};

#endif
