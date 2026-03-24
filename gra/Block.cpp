#include "Block.h"

// Konstruktor
Block::Block(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, CollisionType type) 
    : collisionType(type) {
    
    sf::Vector2f scaledPosition = position * 50.0f;
    sf::Vector2f scaledSize = size * 50.0f;
    
    shape.setSize(scaledSize);          // Ustaw rozmiar bloku
    shape.setPosition(scaledPosition);  // Ustaw pozycjê bloku
    shape.setTexture(texture);    // Ustaw teksturê bloku
}

// Zwraca globalne granice prostok¹ta
sf::FloatRect Block::getBounds() const {
    return shape.getGlobalBounds();
}

// Zwraca typ kolizji
CollisionType Block::getCollisionType() const {
    return collisionType;
}

// Rysowanie bloku
void Block::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}