
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <fstream>
#include <vector>
#include <iostream>
#include <stdio.h>

#include "InitilizeMCAtoms.h"

using namespace std;

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

int main()
{
	cout << "comecou" << endl;

	InitilizeMCAtoms init_;
	init_.init();
	printAtomsVectorDouble(init_.getAtoms(), "test.xyz");

    return 0;
}
