#ifndef GROUND_H
#define GROUND_H

#include <SFML/Graphics.hpp>
#include <vector>

class Ground : public sf::Drawable {
public:
    Ground(sf::Vector2u imageSize, sf::Texture* dirtTexture, sf::Texture* grassTexture, sf::Vector2f tileSize);

    void loadFromImage(const sf::Image& mapLayout);
    bool checkCollision(const sf::FloatRect& playerBounds, sf::Vector2f& push) const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2u m_imageSize;
    sf::Vector2f m_tileSize; // Rozmiar kafelka
    sf::Texture* m_dirtTexture;
    sf::Texture* m_grassTexture;
    std::vector<sf::Sprite> m_tiles;
};

#endif // GROUND_H