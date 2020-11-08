#include "Sim.h"
#include <iostream>


void ClearScreen()
{
	int n;
	for (n = 0; n < 10; n++)
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int main()
{
	bool cont = 0;

	Sim* sim;
	while(!cont) {
		ClearScreen();
		sim = new Sim();
		sim->setup();
		cont = sim->begin();
	}
	return 0;
}