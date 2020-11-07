#include "Sim.h"
#include <iostream>
Sim* Sim::instance = 0;

int main()
{
	float width;
	int pop_init;
	int infected_init;
	int mask_percent;
	
	Sim* sim = sim->getInstance();
	sim->setup();
	sim->begin();
	return 0;
}