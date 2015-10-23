#ifndef SETUPPARAMS_H
#define SETUPPARAMS_H

#include <iostream>
#include <math.h>

using namespace std;

class SetUpParams
{
private:
	int  indRun; //nombre d'éxecution (par défaut 30)
	int  nbItRun; // nombre de generation (nb iteration par éxecution, par défaut 3000)
	int  popsize; // nombre d'individus par population (par défaut 30)
	int  dim; // taille d'un individu (par défaut 30) 
	double mixrate;	// probabilité de mutation (par défaut 0.5)

public:
	SetUpParams(); // constructeur par défaut
	SetUpParams(int, int, int, int); //	constructeur valué
	SetUpParams(const SetUpParams&); // constructeur par recopie
	~SetUpParams(){}; // destructeur

	friend ostream& operator << (ostream&, SetUpParams&); // opérateur d'écriture
	friend istream& operator >> (istream&, SetUpParams&); // opérateur de lecture

	// accesseurs des paramétres
	int   getIndRun() const;
	int   getNbItRun() const;
	int   getPopSize() const;
	int   getDim() const;
	double   getMixRate() const;

	// mutateurs des paramétres
	void defineIndRun(int);
	void defineNbItRun(int);
	void definePopSize(int);
	void defineDim(int);
	void defineMixRate(double);
};

#endif