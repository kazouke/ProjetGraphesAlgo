#ifndef FILESUCCESSEURS_H
#define FILESUCCESSEURS_H

#include <vector>
using namespace std;

class fileSuccesseurs{
	public:
		//Constructeurs - Adrien
		fileSuccesseurs() =delete;
		fileSuccesseurs(int nbSommets){
			fs.resize(nbSommets+1);
			aps.resize(nbSommets+1);
			for(int i=1; i<=nbSommets;i++){
				fs[i]=0;
				aps[i]=i;
			}
			fs[0]=nbSommets;
			aps[0]=nbSommets;
		}
		
		//Adrien - ajoute un sommet au graph
		void ajouterUnSommet(){
			fs[0]++;
			fs.push_back(0);
			aps[0]++;
			aps.push_back(aps[0]);
		}
		
		//Adrien - renvoie vrai si l'arc existe déjà ou ne peut pas exister
		bool arcDejaExistant(int s,int t) const{
			if (0<s && 0<t && s<=fs[0] && t<=fs[0]) return true;
			int pos=aps[s];
			while (pos<= fs[0] && fs[pos]!=0 && fs[pos]!=t) pos++;
			return  fs[pos]==t;
		}
		
		//Adrien - ajoute un arc au graph
		void ajouterUnArc(int s,int t){
			if arcDejaExistant(s,t) return;
			fs[0]++;
			fs.push_back(0);
			int smt = aps[0],position=fs[0];
			do{
				fs[position]=fs[position-1];
				if (fs[position]==0){
					aps[smt]++;
					smt--;
				}
				position--;
			}while (smt>s);
			while (fs[position]>t){
				fs[position]=fs[position-1];
				position--;
			}
			fs[position]=t;
		}
		
		//Adrien
		void afficher() const{
			
		}
		
		
	private:
		vector<int>fs;
		vector<int>aps;
};

#endif
