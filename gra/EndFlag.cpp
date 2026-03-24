#include "EndFlag.h"
#include <iostream>

EndFlag::EndFlag(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture& texture) {
    flag.setSize(size);
    flag.setPosition(position);
    flag.setTexture(&texture);
}

void EndFlag::checkCollision(Player& player, const sf::Vector2f& newPlayerPosition) {
    if (flag.getGlobalBounds().intersects(player.getBody().getGlobalBounds())) {
        // Przeniesienie gracza na now¹ pozycjê
        player.setPosition(newPlayerPosition);
        std::cout << "Gracz dotkn¹³ flagi i zosta³ przeniesiony!" << std::endl;
    }
}

void EndFlag::render(sf::RenderWindow& window) {
    window.draw(flag);
}