#pragma once
#include "SFMLbase.h"
#include "Human.h"

class Sim
{
	static Sim* instance;

	Sim() {
	}
public:
	static Sim* getInstance();
	void begin();
};

