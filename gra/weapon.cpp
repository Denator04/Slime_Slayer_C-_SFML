#include "weapon.h"
#include "Player.h"
#include <iostream>
#include "enemy.h"

Weapon::Weapon(sf::Texture* weaponTexture, sf::Vector2u imageCount, float switchTime) {

    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0;
    currentImage.x = 0;
    uvRect.width = weaponTexture->getSize().x / float(imageCount.x);
    uvRect.height = weaponTexture->getSize().y / float(imageCount.y);

    weaponBody.setTextureRect(uvRect);

    weaponBody.setSize(sf::Vector2f(40.0f, 20.0f));
    weaponBody.setFillColor(sf::Color::Yellow);
    weaponBody.setTexture(weaponTexture);
    //weaponBody.setOutlineThickness(2.0f); // Thickness of the outline
    //weaponBody.setOutlineColor(sf::Color::Blue); // Red outline for better visibility 

    attackEffect.loadFromFile("sword_Sound.mp3");
    attackSound.setBuffer(attackEffect);
}


Weapon::~Weapon() {

}

sf::Vector2f Weapon::getPosition() const {
    return weaponBody.getPosition();
}



void Weapon::Update(int row, float deltaTime, sf::RenderWindow& window, sf::Vector2f playerPosition, bool playerFacingRight) {

    static sf::Clock weaponClock;
    static bool isCooldown = false;
    static bool animationDone = true;

    if (!clicked && !isCooldown && sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        clicked = true;
        isCooldown = true;
        weaponClock.restart();
        currentImage.x = 0;
        attackSound.play();


        if (playerFacingRight && clicked) {
            weaponBody.setScale(3.0f, 3.0f);
            weaponBody.setPosition(playerPosition.x + 15.0f, playerPosition.y + 5.0f);

        }
        else if (!playerFacingRight && clicked) {
            weaponBody.setScale(-3.0f, 3.0f);
            weaponBody.setPosition(playerPosition.x + 30.0f, playerPosition.y + 5.0f);
        }

        currentImage.y = row;

    }

    if (clicked) {

        totalTime += deltaTime;

        if (totalTime >= switchTime) {
            totalTime -= switchTime;
            currentImage.x++;

            if (currentImage.x >= imageCount.x) {
                currentImage.x = 0;
            }


        }
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.top = currentImage.y * uvRect.height;
        weaponBody.setTextureRect(uvRect); // Przypisz nowy obszar tekstury do broni

    }



    if (clicked && weaponClock.getElapsedTime().asSeconds() >= 0.14f) {
        clicked = false;
    }

    if (isCooldown && weaponClock.getElapsedTime().asSeconds() >= 0.5f) {
        isCooldown = false; // Cooldown siê skoñczy³, mo¿na atakowaæ ponownie
    }


    if (clicked) {

        window.draw(weaponBody);
    }

}
