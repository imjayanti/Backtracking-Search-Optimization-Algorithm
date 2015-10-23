// BSA.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "MyAlgorithm.h"


void CreateFenetreBSA() // creation de la fenêtre d'affichage adapté
{
	system("mode con LINES=50 COLS=90");

	cout << endl << "				BSA Algorithm" << endl << endl << endl;
}

void Line() // séparateur
{
	cout << "------------------------------------------------------------------" << endl << endl;
}

void SelectParam() // indique les paramétres à choisir
{
	cout << "Entrez ces parametres :" << endl;
	cout << "	- dimension (la taille d'un individu)" << endl << "	- popsize (le nombre d'individus de la population)" << endl;
	cout << "	- indRun (le nombre d'executions)" << endl << "        - mixrate (la probabilite de mutation)" << endl << endl;
	Line();
}

void SelectFunction() // indique les fonctions disponibles
{
	Line();
	cout << "choisisez la fonction de Benchmark a executer : " << endl;
	cout << "	1 - Rosenbrock" << endl << "	2 - Rastragin" << endl << "        3 - Ackley" << endl;
	cout << "	4 - Schwefel" << endl << "	5 - schaffer" << endl << "	6 - Weierstrass" << endl;
	Line();
}

int _tmain(int argc, _TCHAR* argv[]) // éxecution principale du programme
{
	CreateFenetreBSA();
	SelectParam();

	SetUpParams set;
	cin >> set;

	Line();

	cout << set;

	SelectFunction();

	Problem prob;
	cin >> prob;

	Line();

	cout << "Resultat obtenu sur le nombre d'execution :" << endl << endl;
	MyAlgorithm algo(prob, set);

	cout << endl;
	Line();

	system("pause");
	return 0;
}

