//Dans A[0] est stocké n nombre de sommets
//Dans A[1] est stocké m nombre d'arcs
//La taille de fs est donc n+m+1 et aps n+1
//Passage de la matrice d'adjacence à FS et APS
void Mat2fs_aps(int **A, int *fs, int *aps)
{
	int n = A[0][0]; int m = A[0][1];
	fs = new int[n+m+1]; aps = new int[n+1];
	
	fs[0] = n+m;
	aps[0] = m;
	int c = 1;
	
	for(int i = 1; i <= n; i++)
	{
		aps[i] = c;
		for(int j = 1; j <= n; j++)
		{
			if(A[i][j] == 1)
			{
				fs[c] = j;
				c++;
			}
		}
		fs[c] = 0;
		c++;
	}
}

void fs_aps2Mat(int *fs, int *aps, int **A)
{
	int n = aps[0]; int m = fs[0] - n;
	int tailleFS = fs[0];
	
	A = new int*[n+1]; //On initialise la matrice A à 0
	for(int i = 0; i <= n; i++)
	{
		A[i] = new int[n+1];
		for(int j = 0; j <= n; j++)
			A[i][j]=0;			
	}
	
	A[0][0] = n;
	A[0][1] = m;
	
	int c = 1;
	for(int i = 1; i <= tailleFS; i++)
	{
		if(fs[i] != 0)
			A[c][fs[i]] = 1;
		else
			c++;
	}
}


