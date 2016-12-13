#ifndef FITNESS_H
#define FITNESS_H

#include <vector>
#include <string>

class Fitness
{
public:
	Fitness();
	~Fitness();

	double fit(std::vector<double> &point, int type);

private:
	double lennardJones(std::vector<double> &x);

};

#endif
