#include "MyAlgorithm.h"


MyAlgorithm::MyAlgorithm(const Problem& pbm, const SetUpParams& setup) :
_setup(setup), sol(pbm)
{
	runTab = new double[setup.getIndRun()];

	//Tableaux dynamiques 2D
	double** oldP = new double*[setup.getPopSize()];
	double** P = new double*[setup.getPopSize()];
	double** Mutant = new double*[setup.getPopSize()];
	double** map = new double*[setup.getPopSize()];
	double** T = new double*[setup.getPopSize()];

	//Tableaux dynamique 1D : popsize*1
	double* fitP = new double[setup.getPopSize()];
	double* fitT = new double[setup.getPopSize()];
	globalMinimizer = new double[setup.getDim()];

	mutT = new int[setup.getDim()];

	//Initialisation des variables pour la comparaison de fitnesse
	sol.random(pbm.UpperLimit, pbm.LowerLimit);
	_lower_cost = sol.fitness(sol.tabLine);
	_upper_cost = _lower_cost;

	//Variables intermédiaires pour la fitnesse
	double min;
	double max;

	double fitBest;

	//Variable d'index du tableau
	int indexBest;
	int indexWorst;

	int i, j;

	globalMin = std::numeric_limits<double>::infinity(); //  valeur = infini

	for (int r = 0; r < setup.getIndRun(); r++)
	{
		cout << "Nb d'execution : " << r << endl;

		//Creation des tableaux
		for (i = 0; i < setup.getPopSize(); i++)
		{
			P[i] = new double[setup.getDim()];
		}

		for (i = 0; i < setup.getPopSize(); i++)
		{
			oldP[i] = new double[setup.getDim()];
		}

		for (i = 0; i < setup.getPopSize(); i++)
		{
			Mutant[i] = new double[setup.getDim()];
		}

		for (i = 0; i < setup.getPopSize(); i++)
		{
			map[i] = new double[setup.getDim()];
		}

		for (i = 0; i < setup.getPopSize(); i++)
		{
			T[i] = new double[setup.getDim()];
		}

		int flag = 0;

		//Assignés des valeurs à la Population
		for (i = 0; i < setup.getPopSize(); i++)
		{
			sol.tabLine.clear();
			sol.random(pbm.UpperLimit, pbm.LowerLimit);
			for (j = 0; j < setup.getDim(); j++)
			{
				P[i][j] = sol.tabLine[j];
			}
			fitP[i] = sol.fitness(sol.tabLine);   // initialisation du tableau de fitnesse de Population
		}

		//Assignés des valeurs à la OldPopulation
		for (i = 0; i < setup.getPopSize(); i++)
		{
			sol.tabLine.clear();
			sol.random(pbm.UpperLimit, pbm.LowerLimit);
			for (j = 0; j < setup.getDim(); j++)
			{
				oldP[i][j] = sol.tabLine[j];
			}
		}


		for (int k = 0; k < setup.getNbItRun(); k++)
		{
			min = fitP[0];
			max = fitP[0];

			int id;

			for (i = 0; i < setup.getPopSize(); i++)
			{
				if (fitP[i] == fitP[0])
				{
					_lower_cost = fitP[0];
					_upper_cost = fitP[0];
					flag = 1;
					id = i;
				}
				else if (fitP[i] < min){
					_lower_cost = fitP[i];
					min = best_cost();
					flag = 2;
					id = i;
				}
				else if (fitP[i] > max){
					_upper_cost = fitP[i];
					max = worst_cost();
					flag = 3;
					id = i;
				}
				else {}

				if (flag == 1)
				{
					indexBest = id + 1;
					indexWorst = id + 1;
				}
				else if (flag == 2)
				{
					indexBest = id + 1;
				}
				else if (flag == 3)
				{
					indexWorst = id + 1;
				}
				else{}
			}

			// valeurs aléatoires entre 0 et 1
			double a = rand() / (RAND_MAX + 1.0);
			double b = rand() / (RAND_MAX + 1.0);
			double c = rand() / (RAND_MAX + 1.0);
			double d = rand() / (RAND_MAX + 1.0);


			//selection 1
			for (i = 0; i < setup.getPopSize(); i++)
			{
				for (j = 0; j < setup.getDim(); j++)
				{
					if (a < b)
					{
						oldP[i][j] = P[i][j];
					}
				}
			}

			//permutation
			for (i = 0; i < setup.getPopSize(); i++)
			{
				for (j = 0; j < setup.getDim() / 2; j++)
				{
					// génération de 2 position aléatoires
					int randA = rand() % setup.getPopSize();
					int randB = rand() % setup.getPopSize();

					double temp;

					temp = oldP[randA][j];
					oldP[randA][j] = oldP[randB][j];
					oldP[randB][j] = temp;
				}
			}

			/*---------------------------------------------------------------------*/

			//Generation of Trial-Population

			//Mutation 

			// générer des valeurs aléatoires selon la distribution normale

			default_random_engine generator;
			normal_distribution<double> distribution(0.0, 1.0);
			double F;

			for (i = 0; i < setup.getPopSize(); i++)
			{
				for (j = 0; j < setup.getDim(); j++)
				{
					F = 3 * distribution(generator);

					Mutant[i][j] = P[i][j] + ((oldP[i][j] - P[i][j]) * F);
				}
			}

			//Crossover

			for (i = 0; i < setup.getPopSize(); i++)
			{
				for (j = 0; j < setup.getDim(); j++)
				{
					map[i][j] = 1;
				}
			}

			randomMutants = (int)ceil(setup.getMixRate() * setup.getDim() * a);
			if (c < d)
			{
				for (i = 0; i < setup.getPopSize(); i++)
				{
					tempMut = rand() % setup.getDim();
					for (j = 1; j <= randomMutants; j++)
					{
						while (Exists(tempMut) && mutT != NULL)
						{
							tempMut = rand() % setup.getDim();
						}

						mutT[j] = tempMut;

						int m = mutT[j];
						map[i][m] = 0;
					}
				}
			}
			else
			{
				int randi;
				for (i = 0; i < setup.getPopSize(); i++)
				{
					randi = rand() % setup.getDim();
					map[i][randi] = 0;
				}
			}

			// Generation of a trial population

			for (i = 0; i < setup.getPopSize(); i++)
			{
				for (j = 0; j < setup.getDim(); j++)
				{
					T[i][j] = Mutant[i][j];
				}
			}

			for (i = 0; i < setup.getPopSize(); i++)
			{
				for (j = 0; j < setup.getDim(); j++)
				{
					if (map[i][j] == 1)
					{
						T[i][j] = P[i][j];
					}
				}
			}

			//Boundary Control Mechanism

			for (i = 0; i < setup.getPopSize(); i++)
			{
				sol.tabLine.clear();

				for (j = 0; j < setup.getDim(); j++)
				{
					if (T[i][j] < pbm.LowerLimit || T[i][j] > pbm.UpperLimit)
					{
						T[i][j] = pbm.LowerLimit + (pbm.UpperLimit - pbm.LowerLimit) * (double)rand() / RAND_MAX;
					}
					sol.tabLine.push_back(T[i][j]);
				}
				fitT[i] = sol.fitness(sol.tabLine); // la modification de T change la fitnesse
			}

			/*---------------------------------------------------------------------*/

			//Selection 2

			for (i = 0; i < setup.getPopSize(); i++)
			{
				for (j = 0; j < setup.getDim(); j++)
				{

					if (fitT[i] < fitP[i])
					{
						P[i][j] = T[i][j];
						fitP[i] = fitT[i];
					}
				}

			}

			//Global fit

			fitBest = best_cost();

			if (fitBest <= globalMin)
			{
				globalMin = fitBest;
				for (i = 0; i < setup.getPopSize(); i++)
				{
					for (j = 0; j < setup.getDim(); j++)
					{
						if (i == indexBest)
						{
							globalMinimizer[j] = P[i][j];
						}
					}
				}
			}
		} // fin k 

		//cout << "Meilleur individu : " << indexBest << endl;
		for (j = 0; j < setup.getDim(); j++)
		{
			//cout << globalMinimizer[j] << " ";
		}
		//cout << endl;

		runTab[r] = globalMin;

		ofstream file;
		file.open("result.txt", ios::app);
		file << "IndexBest:" << indexBest << endl;
		file << "BestFitness:" << fitBest << endl << endl;
		file.close();

	} // fin r 


	double sum = 0.0;
	double mean = 0.0;
	double temp = 0.0;
	double variance = 0.0;
	double deviation = 0.0;

	for (i = 0; i < setup.getIndRun(); i++)
	{
		sum += runTab[i];
	}

	mean = sum / setup.getIndRun();
	cout << "Moyenne : " << mean << endl;

	for (i = 0; i < setup.getIndRun(); i++)
	{
		temp += pow((runTab[i] - mean), 2);
	}

	variance = temp / setup.getIndRun();
	cout << "Variance : " << variance << endl;

	deviation = sqrt(variance);
	cout << "Ecart-type : " << deviation << endl;

	//delete tab
	for (i = 0; i < setup.getDim(); ++i) {
		delete[] P[i];
	}
	delete[] P;

	for (i = 0; i < setup.getDim(); ++i) {
		delete[] oldP[i];
	}
	delete[] oldP;

	for (i = 0; i < setup.getDim(); ++i) {
		delete[] Mutant[i];
	}
	delete[] Mutant;

	for (i = 0; i < setup.getDim(); ++i) {
		delete[] map[i];
	}
	delete[] map;

	for (i = 0; i < setup.getDim(); ++i) {
		delete[] T[i];
	}
	delete[] T;

	delete[] fitP;
	delete[] fitT;
	delete[] globalMinimizer;
	delete[] mutT;
	delete[] runTab;
}

double MyAlgorithm::best_cost()  const
{
	return _lower_cost;
}

double MyAlgorithm::worst_cost()  const
{
	return _upper_cost;
}

bool MyAlgorithm::Exists(int tempM)
{
	int j;
	for (j = 1; j <= randomMutants; j++)
	{
		if (mutT[j] == tempM)
			return true;
	}
	return false;
}

