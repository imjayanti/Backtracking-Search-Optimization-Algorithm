#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>

#include "SetUpParams.h"

class Problem
{
public:
	Problem(); // constructeur par défaut
	Problem(int, int); // constructeur valué
	Problem(const Problem&); // constructeur par recopie
	~Problem(){}; // destructeur

	friend ostream& operator << (ostream&, const Problem&); // opérateur d'écriture
	friend istream& operator >> (istream&, Problem&); // opérateur de lecture

	// accesseurs des paramétres
	int getDim();
	int getFuncId() const;

	double LowerLimit, UpperLimit;	// l'ensemble de définition dépendant de la fonction 

private:
	unsigned int dim;	// dimension du tableau
	int function_id;	// id de la fonction à utiliser
};

#endif