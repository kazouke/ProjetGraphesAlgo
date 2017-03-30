void chemins_critiques(int* fp, int *app, int *d, int *&lc, int *&fpc, int *& appc){
	int kc = 1; //indice de la dernière place remplie dans fpc
	int s = 0, k = 0, max  = 0;
	int n=app[0], m=fp[0];

	fpc = new int[m+1]; 
	appc = new int[n+1];
	lc = new int[n+1];

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
					lc[i]=lg;
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
}

//Fonction qui détermine pour chaque sommets son nombre de prédécesseurs
void nb_pred(int* fs, int* aps, int* &fpred){
	fpred=new int[aps[0]+1];
	//pred[0]=aps[0];
	int k=0; 
	for(int i=1; i<aps[0]; i++)
		fpred[i]=0;
	for(int i=1; i<=fs[0]; i++)
	fpred[fs[i]]++;
}

