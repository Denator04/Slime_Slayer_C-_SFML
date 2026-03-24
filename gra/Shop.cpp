#include "Shop.h"
#include <iostream>

Shop::Shop(sf::Font& font) 
{
    if (!butyTexture.loadFromFile("shoes.png") ||
        !grzybTexture.loadFromFile("mushroom.png") ||
        !mieczTexture.loadFromFile("sword.png")) {
        std::cerr << "Nie mo¿na za³adowaæ jednej z tekstur!" << std::endl;
    }

    // Inicjalizacja przedmiotów
    ShopItem buty;
    buty.body.setSize(sf::Vector2f(100.0f, 150.0f));
    buty.body.setPosition(550.0f, 4400.0f);
    buty.body.setTexture(&butyTexture);
    buty.price = 30;
    buty.action = [](Player& player) { player.increaseSpeed(5.0f); };

    buty.priceText.setFont(font);
    buty.priceText.setString(std::to_string(buty.price));
    buty.priceText.setCharacterSize(50);
    buty.priceText.setFillColor(sf::Color::White);
    buty.priceText.setStyle(sf::Text::Bold);
    buty.priceText.setPosition(sf::Vector2f(550.0f, 4600.0f));

    shopItems.push_back(buty);

    ShopItem grzyb;
    grzyb.body.setSize(sf::Vector2f(100.0f, 100.0f));
    grzyb.body.setPosition(800.0f, 4400.0f);
    grzyb.body.setTexture(&grzybTexture);
    grzyb.price = 20;
    grzyb.action = [](Player& player) { player.increaseHealth(10); };

    grzyb.priceText.setFont(font);
    grzyb.priceText.setString(std::to_string(grzyb.price));
    grzyb.priceText.setCharacterSize(50);
    grzyb.priceText.setFillColor(sf::Color::White);
    grzyb.priceText.setStyle(sf::Text::Bold);
    grzyb.priceText.setPosition(sf::Vector2f(800.0f, 4600.0f));

    shopItems.push_back(grzyb);

    ShopItem miecz;
    miecz.body.setSize(sf::Vector2f(100.0f, 100.0f));
    miecz.body.setPosition(1050.0f, 4400.0f);
    miecz.body.setTexture(&mieczTexture);
    miecz.price = 20;
    miecz.action = [](Player& player) { player.increaseDamage(15); };

    miecz.priceText.setFont(font);
    miecz.priceText.setString(std::to_string(miecz.price));
    miecz.priceText.setCharacterSize(50);
    miecz.priceText.setFillColor(sf::Color::White);
    miecz.priceText.setStyle(sf::Text::Bold);
    miecz.priceText.setPosition(sf::Vector2f(1050.0f, 4600.0f));

    shopItems.push_back(miecz);
}

void Shop::update(const sf::RectangleShape& playerBody, Player& player) {
    for (size_t i = 0; i < shopItems.size(); ++i) {
        if (shopItems[i].body.getGlobalBounds().intersects(playerBody.getGlobalBounds())) {
            if (player.getMoney() >= shopItems[i].price) {
                // Odejmowanie pieniêdzy
                player.subtractMoney(shopItems[i].price);

                // Wywo³anie akcji przypisanej do przedmiotu
                shopItems[i].action(player);

                std::cout << "Kupiono przedmiot za " << shopItems[i].price << " $!" << std::endl;

                // Usuwanie przedmiotu
                shopItems.erase(shopItems.begin() + i);
                --i; // Korekta indeksu
            } else {
                std::cout << "Za ma³o pieniêdzy!" << std::endl;
            }
        }
    }
}

void Shop::render(sf::RenderWindow& window) {
    for (const auto& item : shopItems) {
        window.draw(item.body);
        window.draw(item.priceText);
    }
}