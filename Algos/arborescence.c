//Renvoie vrai si c'est une arborescence
bool arborescence(int *fs, int *aps, int &r)
{	
	if(fs[0] != aps[0] * 2 - 1) 
		return false;
	
	int *d;
	ddi(fs,aps,d);
	for(int s = 1; s <= aps[0]; s++)
	{
		if(d[s] == 0)
			r = s;
		if(d[s] > 1)
			return false;
	}

	return true;
}

//Plus opti
bool arborescence(int *fs, int *aps, int &r)
{	
	if(fs[0] != aps[0] * 2 - 1) 
		return false;
	
	int *d = new int[aps[0]+1];
	r = 1;
	
	for(int i = 1; i <= aps[0]; i++)
		d[i] = 0;
	
	int j;
	for(j = 1; j <= fs[0]; j++)
	{
		d[fs[j]]++;
		if(d[fs[j]] > 1)
			return false;
	}
	
	while(d[r] > 0)
		r++;
	return true;
}