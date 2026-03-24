#include "Ground.h"

// Konstruktor
Ground::Ground(sf::Vector2u imageSize, sf::Texture* dirtTexture, sf::Texture* grassTexture, sf::Vector2f tileSize)
    : m_imageSize(imageSize), m_dirtTexture(dirtTexture), m_grassTexture(grassTexture), m_tileSize(tileSize) {}

// Metoda do za³adowania uk³adu mapy
void Ground::loadFromImage(const sf::Image& mapLayout) {
    for (unsigned int y = 0; y < m_imageSize.y; ++y) {
        for (unsigned int x = 0; x < m_imageSize.x; ++x) {
            sf::Color pixelColor = mapLayout.getPixel(x, y);

            if (pixelColor == sf::Color::Black) {
                // Czarne piksele: ziemia (dirt)
                sf::Sprite dirtTile;
                dirtTile.setTexture(*m_dirtTexture);
                dirtTile.setPosition(x * m_tileSize.x, y * m_tileSize.y);
                dirtTile.setScale(m_tileSize.x / m_dirtTexture->getSize().x, m_tileSize.y / m_dirtTexture->getSize().y);
                m_tiles.push_back(dirtTile);
            }
            // Obs³uga innych kolorów, jeœli konieczne
        }
    }
}

// Wirtualna metoda rysuj¹ca
void Ground::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& tile : m_tiles) {
        target.draw(tile, states);
    }
}

bool Ground::checkCollision(const sf::FloatRect& playerBounds, sf::Vector2f& push) const {
    for (const auto& tile : m_tiles) {
        if (tile.getGlobalBounds().intersects(playerBounds)) {
            // Oblicz ró¿nicê przesuniêcia w osi X i Y
            sf::FloatRect tileBounds = tile.getGlobalBounds();

            float deltaX = (playerBounds.left + playerBounds.width / 2) - (tileBounds.left + tileBounds.width / 2);
            float deltaY = (playerBounds.top + playerBounds.height / 2) - (tileBounds.top + tileBounds.height / 2);

            float intersectX = std::abs(deltaX) - (playerBounds.width / 2 + tileBounds.width / 2);
            float intersectY = std::abs(deltaY) - (playerBounds.height / 2 + tileBounds.height / 2);

            if (intersectX < 0.0f && intersectY < 0.0f) {
                // SprawdŸ, która oœ jest "g³êbsza" w kolizji
                if (std::abs(intersectX) > std::abs(intersectY)) {
                    if (deltaX > 0.0f)
                        push.x = intersectX;
                    else
                        push.x = -intersectX;
                }
                else {
                    if (deltaY > 0.0f)
                        push.y = intersectY;
                    else
                        push.y = -intersectY;
                }
                return true;
            }
        }
    }
    return false;
}