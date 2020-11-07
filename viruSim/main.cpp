#include "Sim.h"

Sim* Sim::instance = 0;

int main()
{
	Sim* sim = sim->getInstance();
	sim->begin();
	return 0;
}