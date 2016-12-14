#ifndef METROPOLIS_H
#define METROPOLIS_H

#include <vector>
#include <string>

#include "AuxMath.h"

class Metropolis
{
public:
	Metropolis();

	~Metropolis();

	void startMetropolis();

	void move();

	double propagate(double Eold, double Enew);

	void resetMetropolis();

	std::vector<double> allAtoms;

	std::vector<double> oldPositionAtomMoved;

	std::vector< std::vector<double> > allEnergies;

	bool getFinished() { return notFinished; }

	int getMolMoved() { return iMolMoved; }

private:
	double temperature;

	void savePositionBeforeMove();

	void rejectedEnergyResetPosition();

	void printAtomsVectorDouble(std::vector<double> & atoms, std::string testName);

	bool notFinished;

	int iteration;

	int nAtoms;

	int iMolMoved;

	AuxMath auxMath_;

};



#endif