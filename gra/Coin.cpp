#include "Coin.h"
#include <stdexcept>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Coinanimation.h"
#include <vector>
#include "Player.h"
#include <math.h>

Coin::Coin(const std::string& textureFile, sf::Vector2u imageCount, float switchTime, const std::string& soundFile)
{
    // £adowanie tekstury
    if (!coinTexture.loadFromFile(textureFile)) {
        throw std::runtime_error("Failed to load coin texture.");
    }

    // £adowanie dŸwiêku
    coinSoundBuffer.loadFromFile("coin.wav");
    coinSound.setBuffer(coinSoundBuffer);

    this->imageCount = imageCount;
    this->switchTime = switchTime;
}

void Coin::add(const sf::Vector2f& position, const sf::Vector2f& size) {
    // Tworzenie nowej monety

    sf::Vector2f scaledPosition = position * 50.0f;
    //sf::Vector2f scaledSize = size * 50.0f;

    sf::RectangleShape coin(size);
    coin.setPosition(scaledPosition);
    coin.setTexture(&coinTexture);

    // Dodawanie do wektora
    coins.push_back(coin);
    animations.emplace_back(&coinTexture, imageCount, switchTime);
}

void Coin::update(float deltaTime, const sf::RectangleShape& playerBody, Player& player)
{
    for (size_t i = 0; i < coins.size(); ++i) {
        // Aktualizacja animacji
        animations[i].Update(0, deltaTime); // Za³ó¿my, ¿e animacja jest w wierszu 0
        coins[i].setTextureRect(animations[i].uvRect);

        // Sprawdzanie kolizji z graczem
        if (coins[i].getGlobalBounds().intersects(playerBody.getGlobalBounds())) {
            // Odtwarzanie dŸwiêku
            coinSound.play();

            player.addMoney(1);

            // Usuwanie monety
            coins.erase(coins.begin() + i);
            animations.erase(animations.begin() + i);
            --i; // Korekta indeksu po usuniêciu elementu
        }
    }
}

void Coin::draw(sf::RenderWindow& window) {
    for (auto& coin : coins) {
        window.draw(coin);
    }
}
