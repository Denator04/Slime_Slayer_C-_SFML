#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Coinanimation.h"
#include <vector>

class Player;

class Coin {
private:
    sf::Texture coinTexture;                   // Tekstura monety
    std::vector<sf::RectangleShape> coins;     // Lista obiektów monet
    std::vector<Coinanimation> animations;     // Lista animacji dla monet

    sf::Vector2u imageCount;                   // Liczba klatek w animacji
    float switchTime;                          // Czas prze³¹czania klatek

    sf::SoundBuffer coinSoundBuffer;
    sf::Sound coinSound;

public:
    Coin(const std::string& textureFile, sf::Vector2u imageCount, float switchTime, const std::string& soundFile);

    void add(const sf::Vector2f& position, const sf::Vector2f& size = sf::Vector2f(50.0f, 50.0f));
    void update(float deltaTime, const sf::RectangleShape& playerBody, Player& player);
    void draw(sf::RenderWindow& window);
};

