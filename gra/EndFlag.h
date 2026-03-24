#ifndef ENDFLAG_H
#define ENDFLAG_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class EndFlag {
private:
    sf::RectangleShape flag;

public:
    EndFlag(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture& texture);

    void checkCollision(Player& player, const sf::Vector2f& newPlayerPosition);
    void render(sf::RenderWindow& window);
};

#endif // ENDFLAG_H