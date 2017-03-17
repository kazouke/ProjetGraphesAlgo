#include <iostream>

#include "h/objet.h"
#include "h/adjacence.h"

int main(int argc, char** argv) {
	objet o(new adjacence(10));
	o.getType1()->afficher();
	return 0;
}
