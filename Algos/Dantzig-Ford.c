Pour k=1 à n
	Pour i allant de 1 à k
		Pour j allant de 1 à k
			M[i][k+1]=min(M[i][j]+M[j][k+1]); //1 <= k <= k
			M[k+1][i]=min(M[k+1][j]+M[j]+M[j][i]); //1 <= k <= k
		fait
	fait
	t=min(M[k+1][i]+M[i][k+1]);
	Si t<0 alors circuit absorbant
	Sinon
		Pour i allant de 1 à n faire
			Pour j allant de 1 à n faire
				M[i][j]=min(M[i][j],M[i][k+1]+M[k+1][j]);
			fait
		fait
	finSi
finPour

//Et la version C :
bool dantzig(double C[][MAX]) {
	double x;
	int n = C[0][0];
	for(int k=1; k<n; k++) {
		for(int i=1; i<=k; i++) {
			for(int j=1; j<=k; j++) {
				if((x=C[i][j]+C[j][k+1]) < C[i][k+1])
					C[i][k+1]=x;
				if((x=C[k+1][j]+C[j][i]) < C[k+1][i])
					C[k+1][i]=x;
			}
			if(C[k+1][i]+C[i][k+1] < 0) 
				return false; //circuit absorbant
		}
		for(int i=1; i<=k; i++)
			for(int j=1; j<=k; j++)
				if((x=C[i][k+1]+C[k+1][j]) < C[i][j])
					C[i][j]=x;
	}
	return true;
}
void Ford(...) 
{
	for(int i=1; i<=n; i++)
		d[i]-MAXPOIDS;
	d[s]=0;
	do 
	{
		k++;
		for(int i=1;i<=n; i++) 
		{
			stabilise=true;
			if(d[i]!=MAXPOIDS)
				for(l=aps[i]; (j=fs[l])>0; l++)
					if(d[j]>d[i]+cout[i][j]) 
					{
						d[j]=d[i]+ccout[i][j];
						stabilise=false;
					}
	} while((k<n) && (!stabilise));
	if(k==n)
		cout<<"Le graphe contient un circuit absorbant"<<endl;
}