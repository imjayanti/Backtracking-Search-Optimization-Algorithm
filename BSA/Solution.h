#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <vector>
#include <math.h>

#include"Problem.h"
#include "SetUpParams.h"

using namespace std;

#define PI 3.14159265  

class Solution
{
public:
	Solution(const Problem& pbm); // constructeur par recopie des paramétres du pbm
	Solution(const Solution& sol); // constructeur par recopie
	~Solution(){};

	friend ostream& operator << (ostream& os, const Solution& sol);	// opérateur d'écriture

	// accesseurs des variables
	Problem& getPbm() const;
	double getFitness();
	vector<double>& _tabLine();

	double fitness(vector<double>&);	// calcule la fitnesse d'un individu donné

	void random(double, double);	// génération des valeurs aléatoires dans une domaines de définition limité

	vector<double> tabLine;	//ligne du tab

private:
	double currentFitness; // fitnesse actuelle d'un individu
	const Problem& pbm; // appel les variables du Problem
	int dim;	// dimension d'un individu pour le calcul de fitnesse
};

#endif