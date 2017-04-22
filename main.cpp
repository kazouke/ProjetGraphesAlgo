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
	cout<<"Conversion type 2 : "<<endl;
	o.convertToType2();
	o.afficher();
	cout<<endl<<"Conversion type 3 : "<<endl;
	o.convertToType3();
	o.afficher();
	//-------------------
	h.sauvegarder(o);
	return 0;
}


