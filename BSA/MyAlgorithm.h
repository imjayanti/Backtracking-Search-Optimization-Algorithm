#ifndef MYALGORITHM_H
#define MYALGORITHM_H

#include <iostream>
#include <fstream>
#include <cmath>
#include<random>
#include <vector>
#include <algorithm>
#include <limits>

#include "Solution.h"

class MyAlgorithm
{
private:
	Solution sol; // appel les variables de la Solution
	const SetUpParams& _setup;
	double _upper_cost, _lower_cost; // Valeur de meilleure et moins bonne fitnesse

	int randomMutants; // le nombre d'�lements n�cessaire pour la mutation chez un individu
	int tempMut; // nombre al�atoire designant un �lement n�cessaire pour la mutation chez un individu [0, dim[
	double globalMin; // meilleur fitnesse d'une it�ration

	int* mutT; // un tableau interm�diaire permettant de stocker les valeurs de tempMut
	double* globalMinimizer; // meilleur individu d'une it�ration (tabline)
	double* runTab; // meilleur individu d'une �xecution (tabline)

public:
	MyAlgorithm(const Problem&, const SetUpParams&); // constructeur o� l'algorithme est explicitement �crite 
	~MyAlgorithm(){}; // d�structeur

private:
	bool Exists(int); // v�rification de l'�xistance de la valeur dans un array
	double best_cost() const; // retourne la meilleure fitnesse
	double worst_cost() const; // retourne la moins bonne fitnesse
};

#endif