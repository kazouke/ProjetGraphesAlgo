void fusionOpti(int i, int j) {
	if(j > i) { 
		int x=i; i=j; j=x; 
	}
	int k = prem[i];
	while(k != 0)
	{
		comp[k] = i; k = pilch[k];
	}
	k = prem[i];
	while(pilch[k] != 0)
	{
		comp[k] = i; k = pilch[k];	
	}
	comp[k] = j;
	pilch[k] = prem[j];
	prem[j] = prem[i];
}
/*Pour déterminer le nombre d’éléments d’une composante, on introduit un 
tableau Nb[ ] initialisé à 1 pour tout i on fusionne la composante i avec 
la composante j en une seule composante i : Nb[i]=Nb[i]+Nb[j]; */
void fusion(int i, int j) {
	if(Nb[j]<Nb[i]) {
		int x=i; i=j; j=x;
	}
	int k = prem[i];
	while(k != 0)
	{
		comp[k] = i; k = pilch[k];
	}
	k = prem[i];
	while(pilch[k] != 0)
	{
		comp[k] = i; k = pilch[k];
		
	}
	comp[k] = j;
	pilch[k] = prem[j];
	prem[j] = prem[i];
	Nb[j]+=Nb[i];
}
void Kruskal(graphe g, graphe &t) {
	int n = g.n, m = g.m, x, y;
	t.n = n; t.m = n-1; t.a = new arete[n-1];	
	int *prem = new int[n+1]; int *pilch = new int[n+1];
	int *comp = new int[n+1]; int *nb = new int[n+1];
	for(int i = 0; j <= n; i++) {
		prem[i] = i; pilch[i] = 0; comp[i] = i; nb[i] = 1;
	}
	int i = 0, k = 0;
	while(k < n)
	{
		x = g.a[i].s;
		y = g.a[i].t;
		if(comp[x] != comp[y])
		{
			t.a[k++] = g.a[i]; fusion(comp[x], comp[y]);
		}
		i++;
	}
}
