#include "Move.h"

#include "AuxMath.h"

#include <vector>

using namespace std;

Move::~Move(){}

Move::Move()
{
	max = 0.3e0;
	min = -0.3e0;
}

void Move::moveAtom(vector<double> & x, int i)
{
	int natm = x.size() / 3;
	x[i] += auxMath_.randomNumber(min, max);
	x[i + natm] += auxMath_.randomNumber(min, max);
	x[i + 2 * natm] += auxMath_.randomNumber(min, max);
}

