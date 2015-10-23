#include "SetUpParams.h"

SetUpParams::SetUpParams() :
indRun(30), nbItRun((int)((2 * pow(10, 6)) / 30)), popsize(30), dim(30), mixrate(0.5)
{}

SetUpParams::SetUpParams(int _indRun, int _popsize, int _dim, int _mr) :
indRun(_indRun), popsize(_popsize), nbItRun((int)((2 * pow(10, 6) / _popsize))), dim(_dim), mixrate(_mr)
{}

SetUpParams::SetUpParams(const SetUpParams& p) :
indRun(p.indRun), popsize(p.popsize), nbItRun((int)((2 * pow(10, 6)) / p.popsize)), dim(p.dim), mixrate(p.mixrate)
{}

ostream& operator << (ostream& os, SetUpParams& setup){
	os << "PopSize : " << setup.getPopSize() << endl;
	os << "Dimension : ";
	os << setup.getDim() << endl;
	os << "Nb d'Execution : " << setup.getIndRun() << endl;
	os << "Nb de Generation :" << setup.getNbItRun() << endl;
	os << "Probabilite de Mutation entre 0 et 1 : ";
	if (setup.mixrate >= 1 || setup.mixrate <= 0){
		setup.defineMixRate(0.5);
		cout << " Utilisation de valeur par defaut : 0.5" << endl << endl;
	}
	else os << setup.getMixRate() << endl << endl;
	return os;
}

istream& operator >> (istream& is, SetUpParams& setup){
	cout << "PopSize : ";
	is >> setup.popsize;
	cout << "Dimension : ";
	is >> setup.dim;
	cout << "Nb d'Execution : ";
	is >> setup.indRun;
	cout << "Nb de Generation : ";
	if (setup.getPopSize() >= 30)
	{
		setup.defineNbItRun(((2 * pow(10, 6)) / setup.getPopSize()));
	}
	else{
		setup.defineNbItRun(3000);
	}
	cout << setup.getNbItRun() << endl;
	cout << "Probabilite de Mutation entre 0 et 1 : ";
	is >> setup.mixrate;
	if (setup.mixrate >= 1 || setup.mixrate <= 0)
		cout << "error" << endl;

	return is;
}

int SetUpParams::getIndRun() const
{
	return indRun;
}

int SetUpParams::getNbItRun() const
{
	return nbItRun;
}

int SetUpParams::getPopSize() const
{
	return popsize;
}

int SetUpParams::getDim() const
{
	return dim;
}

double SetUpParams::getMixRate() const
{
	return mixrate;
}

void SetUpParams::defineIndRun(int val)
{
	indRun = val;
}

void SetUpParams::defineNbItRun(int val)
{
	nbItRun = val;
}

void SetUpParams::definePopSize(int val)
{
	popsize = val;
}

void SetUpParams::defineDim(int val)
{
	dim = val;
}

void SetUpParams::defineMixRate(double val)
{
	mixrate = val;
}