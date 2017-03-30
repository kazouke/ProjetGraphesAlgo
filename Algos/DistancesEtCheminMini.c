void calcul_d(int *fs, int *aps, int s, int *d){
	int t = 0, q = 1, j; 
	int p = 1; //p+1 la prochaine position libre entre 
	//t+1 et q soit les sommets marqués et non traités
	int dist = 0;
	int fa[] = new int [n];
	d[s] = 0;
	
	while(t < q)
	{
		dist++;
		for(int i = t+1; i <= q; i++)
		{
			for(int l = aps[fa[i]]; (j = fs[l]) > 0; l++)
			{
				if(d[j] == -1)
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
	free(fa);
}

void mat_dist(int *fs, int *aps, int **&mat){
	int n = aps[0];
	mat = new int*[n+1];
	for(int i=1; i<=n; i++){
		calcul_d(fs, aps, i, mat[i]);
	}
}

void pred_chemin(int *fs, int *aps, int s, int* &pred){ 
	
	int n = aps[0], t;
	pred = new int[n+1];
	int d* ;
	calcul_d(fs, aps, s, d);
	for(int i=1; i<=n; i++){
		for(int j=aps[i]; (t=fs[j])!=0; j++){
			if(d[t]==d[i]+1)
				pred[t]=i;
		}
	} 
}