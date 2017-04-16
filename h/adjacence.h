#ifndef ADJACENCE_H
#define ADJACENCE_H

#include <vector>
#include <iomanip>
using namespace std;

class adjacence{
	public:
		adjacence(int taille){
			t.resize(taille+1);
			for (int i=0;i<=taille;i++)
			{
				t[i].resize(taille+1);
				for (int j=0;j<=taille;j++) t[i][j]=-1;
			}
			t[0][0]=taille;
		}
		
		void afficher() const{
			cout<<"    ";
			for (int i=1;i<=t[0][0];i++) cout<<setw(3)<<i<<' ';
			cout<<endl;
			for (int i=0;i<=t[0][0];i++) cout<<"----";
			cout<<endl;
			for (int i=1;i<=t[0][0];i++)
			{
				cout <<setw(3)<<i<<'|';
				for (int j=1;j<=t[0][0];j++) cout<<setw(3)<<t[i][j]<<' ';
				cout<<endl;
			}
		}
		
		bool dansTableau(int i, int j) const{
			if (0 <= i && i <= t[0][0] && 0 <= j && j <= t[0][0]) return true;
			return false;
		}
		
		void setValeurLien(int i, int j,int x){
			if (!dansTableau(i,j)) return;
			t[i][j]=x;
		}
		
		int getValeurLien(int i, int j) const{
			if (!dansTableau(i,j)) return -INT_MAX;
			return t[i][j];
		}
		
	private:
		vector<vector<int>>t;
};

#endif
