Prim(graphe G, graphe T)
{
	s = {1};
	B = vide;
	Tant que |S| < n
	{
		Choisir une arete {s, t} de
		coût minimal telle que 
		s appartient à S et t n'appartient pas à S
		S = S union {t};
		B = B union {{s, t}};
	}
}

supprimer s à S;
ajouter s à M;
d[s]=0;
while S≠vide
{
	Soit j ∈ S : Γ-1 (j)∈M.
	Si un tel sommet n’existe pas
	on arrête
	Sinon
	Supprimer j de S
	Ajouter j à m
	k = 1er prédécesseur de j
	min=d[k]+cout[k][j]

	pour tous les autres successeurs de j, faire
	{
		v = d[i] + cout[i][j]
		si v < min
		{
			min = v
			h = i
		}		
	}
}

entier Coloration(graphe G)
{
	pour i = 1 à n
	{
		c = 1;
		while(il existe j adjacent à 1 avec f(j)=c)
			c = c + 1;
		f(i) = c;
	}
	retourner max(f(i) : i = 1 à n);
}