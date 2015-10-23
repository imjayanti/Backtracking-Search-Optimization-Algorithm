#ifndef SETUPPARAMS_H
#define SETUPPARAMS_H

#include <iostream>
#include <math.h>

using namespace std;

class SetUpParams
{
private:
	int  indRun; //nombre d'�xecution (par d�faut 30)
	int  nbItRun; // nombre de generation (nb iteration par �xecution, par d�faut 3000)
	int  popsize; // nombre d'individus par population (par d�faut 30)
	int  dim; // taille d'un individu (par d�faut 30) 
	double mixrate;	// probabilit� de mutation (par d�faut 0.5)

public:
	SetUpParams(); // constructeur par d�faut
	SetUpParams(int, int, int, int); //	constructeur valu�
	SetUpParams(const SetUpParams&); // constructeur par recopie
	~SetUpParams(){}; // destructeur

	friend ostream& operator << (ostream&, SetUpParams&); // op�rateur d'�criture
	friend istream& operator >> (istream&, SetUpParams&); // op�rateur de lecture

	// accesseurs des param�tres
	int   getIndRun() const;
	int   getNbItRun() const;
	int   getPopSize() const;
	int   getDim() const;
	double   getMixRate() const;

	// mutateurs des param�tres
	void defineIndRun(int);
	void defineNbItRun(int);
	void definePopSize(int);
	void defineDim(int);
	void defineMixRate(double);
};

#endif