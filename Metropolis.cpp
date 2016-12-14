#include "Metropolis.h"

#include <vector>
#include <string>
#include <fstream>
#include <cmath>

#include "InitilizeMCAtoms.h"
#include "Move.h"

using namespace std;

Metropolis::~Metropolis() {}

Metropolis::Metropolis() 
{
	iteration = 1;
	notFinished = true;
	oldPositionAtomMoved.resize(3);

}

void Metropolis::startMetropolis()
{
	temperature = 273.15;
	InitilizeMCAtoms init_;
	init_.init();
	allAtoms = init_.getAtoms();
	printAtomsVectorDouble(allAtoms, "initial-configuration.xyz");
	nAtoms = allAtoms.size() / 3;
	allEnergies.resize(nAtoms);
	for (int i = 0; i < nAtoms; i++)
	{
		allEnergies[i].resize(nAtoms);
	}
}

void Metropolis::move()
{
	Move move_;	
	iMolMoved = auxMath_.randomNumber(0, nAtoms-1);
	savePositionBeforeMove();
	move_.moveAtom(allAtoms, iMolMoved);
}

double Metropolis::propagate(double Eold, double Enew)
{
	double delta = Enew - Eold;
	double prob, dice;
	bool accept;
	double Eactual;
	if (delta > 0)
	{
		prob = exp(-delta / temperature);
		dice = auxMath_.randomNumber(0.0e0, 1.0e0);
		accept = prob > dice;
	}
	else
		accept = true;

	if (accept)
		Eactual = Enew;
	else
	{
		Eactual = Eold;
		rejectedEnergyResetPosition();
	}

	iteration++;
	if (iteration > nAtoms)
		notFinished = false;

	return Eactual;
}

void Metropolis::savePositionBeforeMove()
{
	oldPositionAtomMoved[0] = allAtoms[iMolMoved];
	oldPositionAtomMoved[1] = allAtoms[iMolMoved + nAtoms];
	oldPositionAtomMoved[2] = allAtoms[iMolMoved + 2 * nAtoms];
}

void Metropolis::rejectedEnergyResetPosition()
{
	allAtoms[iMolMoved] = oldPositionAtomMoved[0];
	allAtoms[iMolMoved + nAtoms] = oldPositionAtomMoved[1];
	allAtoms[iMolMoved + 2 * nAtoms] = oldPositionAtomMoved[2];
}


void Metropolis::printAtomsVectorDouble(vector<double> & atoms, string testName)
{
	int natm = atoms.size() / 3;
	ofstream teste_(testName.c_str());
	teste_ << natm << endl << "t" << endl;
	for (int i = 0; i < natm; i++)
	{
		teste_ << "H "
			<< atoms[i] << "  "
			<< atoms[i + natm] << "  "
			<< atoms[i + 2 * natm] << endl;
	}
	teste_.close();
}

void Metropolis::resetMetropolis()
{
	iteration = 1;
}