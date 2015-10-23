#include "Solution.h"
#include <time.h>

Solution::Solution(const Problem& _pbm) :
pbm(_pbm)
{}

Solution::Solution(const Solution& sol) :
currentFitness(sol.currentFitness), pbm(sol.pbm)
{}

ostream& operator << (ostream& os, const Solution& sol)
{
	os << "Current Fitness : " << sol.currentFitness << endl;
	return os;
}

void Solution::random(double upper, double lower)
{
	SetUpParams set;
	dim = set.getDim();

	int j;
	for (j = 0; j < dim; j++)
	{
		tabLine.push_back(lower + (upper - lower) * (double)rand() / RAND_MAX);
	}
}

vector<double>& Solution::_tabLine(){
	return tabLine;
}

double Solution::fitness(vector<double>& tabL)
{
	double sum = 0.0;
	currentFitness = 0.0;

	int j; // limité à la dim

	switch (pbm.getFuncId())
	{
	case 1: // Rosenbrock

		for (j = 0; j < dim - 1; j++)
		{
			sum = 100 * (pow((tabL[j + 1] - pow(tabL[j], 2)), 2)) + pow(tabL[j] - 1, 2);
		}

		currentFitness = sum;

		break;

	case 2: // Rastrigin

		for (j = 0; j < dim; j++)
		{
			sum = pow(tabL[j], 2) - (10 * cos(2 * PI*tabL[j]));
		}

		currentFitness = (10 * dim) + sum;

		break;

	case 3: // Ackley

		double A, B;

		for (j = 0; j < dim; j++)
		{
			A = pow(tabL[j], 2);
			B = cos(2 * PI*tabL[j]);
		}
		sum = -20 * exp(-0.2*sqrt((1 / dim)*A)) - exp((1 / dim)* B) + 20 + exp(1);

		currentFitness = sum;

		break;

	case 4: // Schwefel

		for (int j = 0; j < dim; j++)
		{
			sum = tabL[j] * sin(sqrt(abs(tabL[j])));
		}

		currentFitness = 418.9829*dim - sum;

		break;

	case 5: // schaffer

		for (int j = 0; j < dim - 1; j++)
		{
			sum = (pow(sin(pow(tabL[j], 2) - pow(tabL[j + 1], 2)), 2) - 0.5) / (pow(1 + 0.001*(pow(tabL[j], 2) + pow(tabL[j + 1], 2)), 2));
		}

		currentFitness = 0.5 + sum;

		break;

	case 6: // Weierstrass

		int i = 0;
		double a, b;
		unsigned int k_max;
		a = 0.5;
		b = 3.0;
		k_max = 20;

		for (int j = 0; j < dim; j++)
		{
			for (unsigned int t = 0; t <= k_max; t++)
			{
				sum += pow(a, (double)t) * cos(2.0 * PI * pow(b, (double)t) * (tabL[j] + 0.5));
			}
		}

		currentFitness = sum;

		break;
	}
	return currentFitness;
}

double Solution::getFitness(){
	return currentFitness;
}