#include "InitilizeMCAtoms.h"

#include <vector>

#include "AuxMath.h"

InitilizeMCAtoms::~InitilizeMCAtoms(){}

InitilizeMCAtoms::InitilizeMCAtoms(){}

void InitilizeMCAtoms::init()
{
	init(100, 30, 30, 30);
}

void InitilizeMCAtoms::init(int nAtoms, double lx, double ly, double lz)
{
	nAtoms = 100;
	lx = ly = lz = 30;

	AuxMath aux_;
	mcAtoms.resize(nAtoms * 3);
	for (int i = 0; i < nAtoms; i++)
	{
		mcAtoms[i] = aux_.randomNumber(0.0e0, lx);
		mcAtoms[i + nAtoms] = aux_.randomNumber(0.0e0, ly);
		mcAtoms[i + 2 * nAtoms] = aux_.randomNumber(0.0e0, lz);
	}
	
	// falta rotacao

}

