#pragma once
#ifndef UI_H
#define UI_H


#include <SFML\Graphics.hpp>
#include <string>
#include "Player.h"

class UI
{
private:
	sf::Font font;
	sf::Text healthText;
	sf::Text damageText;
	sf::Text moneyText;
	sf::Text speedText;
	sf::RectangleShape sidebar;

public:
	UI(float width, float height);

	void update(const Player& player, const sf::View& view);

	void draw(sf::RenderWindow& window);


};

#endif