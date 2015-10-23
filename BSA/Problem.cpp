#include "Problem.h"

Problem::Problem() :
dim(30), function_id(1), LowerLimit(-2.048), UpperLimit(2.048)
{}

Problem::Problem(int _dim, int _funId) :
dim(_dim), function_id(_funId)
{
	switch (_funId)
	{
	case 1: // Rosenbrock
		LowerLimit = -2.048;
		UpperLimit = 2.048;
		break;
	case 2: // Rastrigin
		LowerLimit = -5.12;
		UpperLimit = 5.12;
		break;
	case 3: // Ackley
		LowerLimit = -32.768;
		UpperLimit = 32.768;
		break;
	case 4: // Schwefel
		LowerLimit = -500;
		UpperLimit = 500;
		break;
	case 5: // schaffer
		LowerLimit = -100;
		UpperLimit = 100;
		break;
	case 6: // Weierstrass
		LowerLimit = -30; // a changer
		UpperLimit = 30;
		break;
	}
}

Problem::Problem(const Problem& pbm) :
dim(pbm.dim), function_id(pbm.function_id), LowerLimit(pbm.LowerLimit), UpperLimit(pbm.UpperLimit)
{}

ostream& operator << (ostream& os, const Problem& pbm){
	os << "Function Id : " << pbm.function_id << " LowerLimit : " << pbm.LowerLimit << " UpperLimit : " << pbm.UpperLimit << endl;
	return os;
}

istream& operator >> (istream& is, Problem& pbm){
	cout << "Function Id : ";
	is >> pbm.function_id;
	switch (pbm.function_id)
	{
	case 1: // Rosenbrock
		pbm.LowerLimit = -2.048;
		pbm.UpperLimit = 2.048;
		break;
	case 2: // Rastrigin
		pbm.LowerLimit = -5.12;
		pbm.UpperLimit = 5.12;
		break;
	case 3: // Ackley
		pbm.LowerLimit = -32.768;
		pbm.UpperLimit = 32.768;
		break;
	case 4: // Schwefel
		pbm.LowerLimit = -500;
		pbm.UpperLimit = 500;
		break;
	case 5: // schaffer
		pbm.LowerLimit = -100;
		pbm.UpperLimit = 100;
		break;
	case 6: // Weierstrass
		pbm.LowerLimit = -30; // a changer
		pbm.UpperLimit = 30;
		break;
	}
	return is;
}

int Problem::getDim()
{
	SetUpParams sp;
	dim = sp.getDim();
	return dim;
}

int Problem::getFuncId() const
{
	return function_id;
}