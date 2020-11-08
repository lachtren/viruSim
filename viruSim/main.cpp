#include "Sim.h"

int main()
{
	Sim* sim;
	for (;;) {
		sim = new Sim();
		sim->setup();
		sim->begin();
	}
	return 0;
}