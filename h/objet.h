#ifndef OBJET_H
#define OBJET_H

#include "adjacence.h"
#include "fileSuccesseurs.h"
#include "pointeurs.h"

class objet{
	public:
		~objet(){delete t1, t2, t3;}
		
		//Constructeurs
		objet(adjacence*a)		{type=1;t1=a;t2=0;t3=0;}
		objet(fileSuccesseurs*f){type=2;t1=0;t2=f;t3=0;}
		objet(pointeurs*p)		{type=3;t1=0;t2=0;t3=p;}
		
		//Get
		int 				getType()  const {return type;}
		adjacence* 			getType1() const {return t1;}
		fileSuccesseurs* 	getType2() const {return t2;}
		pointeurs* 			getType3() const {return t3;}
		
		//Convert
		void convertToType1(){
			if (type==1) return;
		}
		void convertToType2(){
			if (type==2) return;
		}
		void convertToType3(){
			if (type==3) return;
		}
		
		
	private:
		int type;				//Contient le type de l'objet
		adjacence* 		t1;		//type=1
		fileSuccesseurs*t2;		//type=2
		pointeurs*		t3;		//type=3
};

#endif
