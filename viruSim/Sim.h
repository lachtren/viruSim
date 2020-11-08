#pragma once
#include "SFMLbase.h"
#include "Human.h"
#include "HumanManager.h"
/*
Sim class does all heavy lifting of the simulation.
Renders objects, handles control of time and parameters once implemented
*/
class Sim
{
	float infected_rate;
	int num_inf;
	int healthy;
	int population;
	int deceased =0;
	int stats_timer = 5;
	bool quit_button = false;
	bool exit_button = false;
	float width;
	int pop_init;
	sf::Font font;
	sf::Text params;
	sf::Text stats;
	std::vector<sf::Text>s_v;
	std::vector<sf::Text>p_v;
	int infected_init;
	int mask_percent;
	static Sim* instance;
	void load_params();
	void load_stats();
	void load_buttons();
	void check_mouse();
	sf::RenderWindow* wnd;
	HumanManager* hm;
	sf::Clock clock;
	sf::Sprite new_p_spr;
	sf::Texture new_p_text;

	sf::Sprite quit_spr;
	sf::Texture quit_text;

public:
	

	Sim() {
		width = 5; pop_init = 3; infected_init = 0; mask_percent = 50;
		mask_eff = 50;
		b_rate = 20;
		f_rate = 20;

		
		std::cout << "SET PARAMETERS" << std::endl;
		std::cout << "*************************" << std::endl;
		std::cout << std::endl;

		std::cout << "Virus transmission rate: ";
		std::cin >> t_rate;

		/*
		std::cout << "Fatality rate";
		std::cin >> f_rate;
		std::cout << "Width of community: ";
		std::cin >> width;
		std::cout << "Probability of birth per colission: ";
		std::cin >> b_rate;
		std::cout << "Initial population: ";
		std::cin >> pop_init;
		std::cout << "Initial infected: ";
		std::cin >> infected_init;
		std::cout << "Percent of mask wearers: ";
		std::cin >> mask_percent;
		std::cout << "Percent mask effectiveness: ";
		std::cin >> mask_eff;
		*/
	}

public:
	

	int t_rate;
	int mask_eff;
	int f_rate;
	int b_rate;
	void setup();
	bool begin();
	void update_stats(sf::Time);
};