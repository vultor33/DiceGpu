#ifndef INITILIZEMCATOMS_H
#define INITILIZEMCATOMS_H

#include <vector>

class InitilizeMCAtoms
{
public:
	InitilizeMCAtoms();

	~InitilizeMCAtoms();

	void init();

	void init(int nAtoms, double lx, double ly, double lz);

	std::vector<double> getAtoms(){	return mcAtoms; }

private:
	double lx, ly, lz;

	std::vector<double> mcAtoms;


};

#endif

/*
O DICE roda sobre os eixos x,y e z.
Vou fazer rotacoes genericas.




*/

