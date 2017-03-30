//Algo général
void ppp()
{
	int *pile = new int[profondeur];
	pile[0] = racine(T);
	int h = 1; //position suivante dans la pile
	int *s = fils_gauche(racine(T));
	
	while(h > 0)
	{
		if(s)
		{
			pile[h] = s;
			h++;
			traitement(s); //par exemple affichage
			s = fils_gauche(s);
		}
		else
		{
			h--;
			s = frere_droit(pile[h]);
		}
	}
}

//Parcours prioritairement en profondeur avec fs et aps
void ppp(int *fs, int *aps, int r)
{
	int *pile = new int[aps[0]+1];
	pile[0] = r;
	int h = 1;
	int k = aps[r];
	
	while(h > 0)
	{
		if(fs[k])
		{
			pile[h] = k;
			k = aps[k];
			h++;
			printf("%d", fs[k]);//affichage en préordre
		}
		else
		{
			//printf("%d", fs[k]);//affichage en postordre
			h--;
			k = pile[h] + 1;
		}
	}
}