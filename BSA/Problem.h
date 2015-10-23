#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>

#include "SetUpParams.h"

class Problem
{
public:
	Problem(); // constructeur par d�faut
	Problem(int, int); // constructeur valu�
	Problem(const Problem&); // constructeur par recopie
	~Problem(){}; // destructeur

	friend ostream& operator << (ostream&, const Problem&); // op�rateur d'�criture
	friend istream& operator >> (istream&, Problem&); // op�rateur de lecture

	// accesseurs des param�tres
	int getDim();
	int getFuncId() const;

	double LowerLimit, UpperLimit;	// l'ensemble de d�finition d�pendant de la fonction 

private:
	unsigned int dim;	// dimension du tableau
	int function_id;	// id de la fonction � utiliser
};

#endif