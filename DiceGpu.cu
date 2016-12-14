
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <fstream>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cmath>

#include "InitilizeMCAtoms.h"
#include "Fitness.h"
#include "Metropolis.h"
#include "Move.h"

using namespace std;

void printAtomsVectorDouble(vector<double> & atoms, string testName);

double calculateFitness(vector<double> &x, vector< vector<double> > &allEnergies);

double calculateFitnessI(vector<double> &x, vector< vector<double> > &allEnergies, int i);

int main()
{
	cout << "comecou" << endl;

	Metropolis metrop_;

	metrop_.startMetropolis();

	double Eold, Enew;
	
	int mcSteps = 100;

	Eold = calculateFitness(metrop_.allAtoms, metrop_.allEnergies);

	for (int i = 0; i < mcSteps; i++)
	{
		do // nAtoms iterations - one MC step
		{
			metrop_.move();
			Enew = calculateFitnessI(metrop_.allAtoms, metrop_.allEnergies, metrop_.getMolMoved());
			Eold = metrop_.propagate(Eold, Enew);
		} while (metrop_.getFinished());
		metrop_.resetMetropolis();
	}

	cout << "termino" << endl;
	cin.get();

    return 0;
}


double calculateFitness(vector<double> &x, vector< vector<double> > &allEnergies)
{
	Fitness fit_;
	double total = 0.0e0;
	// x1 x2 x3 ... y1 y2 y3 ... z1 z2 z3
	int natm = x.size() / 3;
	// j > i - triangular inferiror
	for (int i = 0; i < (natm - 1); i++)
	{
		for (int j = (i + 1); j < natm; j++)
		{
			allEnergies[i][j] = fit_.lennardJonesIJ(x, i, j, natm);
			total += allEnergies[i][j];
		}
	}

	if (isnan(total))
	{
		cout << "nam no total" << endl;
		exit(1);
	}
		


	return total;
}

double calculateFitnessI(
	vector<double> &x, 
	vector< vector<double> > &allEnergies,
	int i)
{
	Fitness fit_;
	double total = 0.0e0;
	// x1 x2 x3 ... y1 y2 y3 ... z1 z2 z3
	int natm = x.size() / 3;
	// j > i - triangular inferiror
	for (int j = 0; j < natm; j++)
	{
		if (i > j)
			allEnergies[j][i] = fit_.lennardJonesIJ(x, i, j, natm);
		else if (i < j)
			allEnergies[i][j] = fit_.lennardJonesIJ(x, i, j, natm);
	}

	for (int i = 0; i < (natm - 1); i++)
	{
		for (int j = (i + 1); j < natm; j++)
		{
			total += allEnergies[i][j];
		}
	}

	if (isnan(total))
	{
		cout << "nam no total" << endl;
		exit(1);
	}

	return total;
}


void printAtomsVectorDouble(vector<double> & atoms, string testName)
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
