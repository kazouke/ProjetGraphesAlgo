//MAXPOIDS = 100.0
void Dijkstra(int *fs, int *aps, int **cout, int *&d, int *&pred, int s) 
{
	int cpt,v,j,k;
	float max;
	int n = aps[0];
	d = new int[n+1];
	d[0] = n;
	pred = new int[n+1];
	bool *dansS = new bool[n+1];
	for(int i=1; i<=n; i++) 
	{
		d[i] = cout[s][i];
		if(cout[s][i] != MAXPOIDS)
			pred[i] = s;
		else
			pred[i] = -1;
		dansS[i] = true;
	}
	dansS[s] = false;
	d[s] = 0;
	cpt = n - 1;	
	while(cpt > 0)
	{
		max = MAXPOIDS;
		for(int i=1; i<=n; i++)
		{
			if(dansS[i] && d[i] < max) 
			{
				max = d[i];
				j=i;
			}
			if(max == MAXPOIDS)
				break;
			dansS[j] = false;
			cpt--;
			for(int h=aps[j]; (k=fs[h])!=0; l++) 
			{
				if(dansS[k]) 
				{
					v=d[j]+cout[j][k];
					if(v<d[k]) 
					{
						d[k]=v;
						pred[k]=j;
					}
				}
			}
		}
	}
}
