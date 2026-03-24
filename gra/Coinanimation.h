#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Coinanimation
{
public:
	Coinanimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

	void Update(int row, float deltaTime);

public:
	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;

	std::vector<sf::Sprite> coins; // Kontener na monety (sprite'y)
};

