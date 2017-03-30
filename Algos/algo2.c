//Le nombre de prédécesseurs de i est le nombre de fois où il apparaît dans fs
//dde demi-degré extérieur : nombre de successeurs d'un sommet
//ddi demi-degré intérieur : nombre de prédécesseurs d'un sommet
void ddi(int *fs, int *aps, int *&d)
{
	d = new int[aps[0]+1];
	
	for(int i = 1; i <= aps[0]; i++)
		d[i] = 0;
	for(int j = 1; j <= fs[0]; j++)
		d[fs[j]]++;
}

//index des prédécesseurs
void d2app(int *d, int *&app)
{
	int n = d[0];
	app = new int[n+1];
	app[0] = n; app[1] = 1;
	
	for(int i = 1; i < n; i++)
		app[i+1] = app[i] + d[i] + 1;
}

void fs_app2fp(int *fs, int *app, int *&fp)
{
	int n = fs[0]; int cpt = 1;
	for(int i = 1; i <= n; i++)
	{
		if(fs[i] == 0)
			cpt++;
		else
		{
			fp[app[fs[i]]] = cpt;
			app[fs[i]]++;
		}
	}
}
//Fonction qui détermine fp et app
void fs_aps2fp_app(int* fs, int* aps, int* fp, int* app)
{
	int n = aps[0]; int m = fs[0];
	
	int *d;
	ddi(fs, apps, d);
	d2app(d, app);
	fp = new int[m+1]; fp[0] = m;
	
	int s = 1;
	for(int i = 1; i < m; i++)
	{
		if(fs[i] != 0)
		{
			fp[app[fs[i]]] = s;
			app[fs[i]]++;
		}
		else
			s++;
	}
	for(int i = n; i > 1; i--)
	{
		fp[app[i]] = 0;
		app[i] = app[i-1] + 1;
	}
	app[1]=1;
}