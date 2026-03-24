#ifndef SHOP_H
#define SHOP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include <functional>

struct ShopItem {
    sf::RectangleShape body;
    int price;
    sf::Text priceText;

    std::function<void(Player&)> action;
};

class Shop {
private:
    std::vector<ShopItem> shopItems;

    // Tekstury przedmiotów
    sf::Texture butyTexture;
    sf::Texture grzybTexture;
    sf::Texture mieczTexture;

public:
    Shop(sf::Font& font); // Konstruktor
    void update(const sf::RectangleShape& playerBody, Player& player);
    void render(sf::RenderWindow& window);
};

#endif // SHOP_H

