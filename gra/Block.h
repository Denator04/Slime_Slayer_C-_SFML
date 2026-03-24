#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

// Typy kolizji dla bloku
enum class CollisionType {
    TopOnly,    // Kolizja tylko od góry
    AllSides    // Kolizja z ka¿dej strony
};

class Block {
public:
    // Konstruktor
    Block(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, CollisionType type);

    // Zwraca granice bloku (u¿ywane do detekcji kolizji)
    sf::FloatRect getBounds() const;

    // Zwraca typ kolizji
    CollisionType getCollisionType() const;

    // Rysowanie bloku na ekranie
    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape shape; // Prostok¹t reprezentuj¹cy blok
    CollisionType collisionType; // Typ kolizji dla bloku
};

#endif // BLOCK_H