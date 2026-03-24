#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"
//#include "weapon.cpp"

class Weapon {

public:

	Weapon(sf::Texture* weaponTexture, sf::Vector2u imageCount, float switchTime);
	~Weapon();

	void Update(int row, float deltaTime, sf::RenderWindow& window, sf::Vector2f playerPosition, bool playerFacingRight);

	sf::Vector2f getPosition() const;


private:
	sf::IntRect uvRect;
	sf::RectangleShape weaponBody;


public:
	sf::Sound attackSound;
	sf::SoundBuffer attackEffect;

	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	bool clicked = false;

	float totalTime;
	float switchTime;


};