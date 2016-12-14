#ifndef MOVE_H
#define MOVE_H

#include <vector>

#include "AuxMath.h"

//cartesian move, spherical move

class Move
{
public:
	Move();

	~Move();

	void moveAtom(std::vector<double> &x, int i);

private:
	AuxMath auxMath_;

	double max, min;


};

#endif
