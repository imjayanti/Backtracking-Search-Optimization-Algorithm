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

	int randomMutants; // le nombre d'élements nécessaire pour la mutation chez un individu
	int tempMut; // nombre aléatoire designant un élement nécessaire pour la mutation chez un individu [0, dim[
	double globalMin; // meilleur fitnesse d'une itération

	int* mutT; // un tableau intermédiaire permettant de stocker les valeurs de tempMut
	double* globalMinimizer; // meilleur individu d'une itération (tabline)
	double* runTab; // meilleur individu d'une éxecution (tabline)

public:
	MyAlgorithm(const Problem&, const SetUpParams&); // constructeur où l'algorithme est explicitement écrite 
	~MyAlgorithm(){}; // déstructeur

private:
	bool Exists(int); // vérification de l'éxistance de la valeur dans un array
	double best_cost() const; // retourne la meilleure fitnesse
	double worst_cost() const; // retourne la moins bonne fitnesse
};

#endif