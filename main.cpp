#include <iostream>
#include "h/fichier.h"
#include "h/objet.h"
#include "h/adjacence.h"

const string nomFichier = "data";


int main(int argc, char** argv) {
	objet o(new adjacence(10));
	fichier h(nomFichier);
	h.charger(o);
	//-------------------
	o.modifierTableau();
	o.convertToType2();
	o.afficher();
	//-------------------
	h.sauvegarder(o);
	return 0;
}


