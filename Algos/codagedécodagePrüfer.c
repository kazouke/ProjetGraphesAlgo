void codagePrüfer(int A[][MAX], int *&p)
{
	int n = A[0][0];
	p = new int[n-1];
	p[0] = n - 2;
	
	for(int i = 1; i <= n; i++)
		for(int j = i+1; j <= n; j++)
			A[i][0] += A[i][j];
		
	int k = 1;
	while(k <= n)
	{
		int i = 1;
		for(i; A[i][0] != 1; i++);
		int j = 1;
		for(j; A[i][j] != 1; j++);
		p[k++] = j;
		
		A[i][0] = 0;
		A[i][j] = 0;
		A[j][i] = 0;
		A[j][0]--;
	}
}
décodagePrüfer(int *p, int **&A)
{
	int m = p[0], n = m + 2;
	A = new int *[m+1];
	
	for(int i = 0; i <= n; i++)
		A[i] = new int[m+1];
	A[0][0] = n;
	A[0][1] = n-1;
	int *s = new int[n+1];
	bool *b = new bool[n+1];
	
	for(int i = 1; i <= n; i++)
	{
		s[i] = 0;
		b[i] = true;
	}
	for(i = 1; i <= n; i++)
		s[p[i]]++;
	for(int k = 1; k <= n; k++)
		for(int i = 1; i <= n; i++)
			if((b[i]) && (s[p[i]] == 0))
			{
				A[i][p[k]] = 1;
				A[p[k]][i] = 1:
				b[i] = false;
				s[p[k]]--;
				break;
			}
	int i = 1;
	for(;!b[i]; i++);
	//b[i] = false;
	int j = i + 1;
	for(;!b[j]; j++);
	A[i][j] = 1;
	A[j][i] = 1;	
}