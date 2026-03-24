#include "UI.h"
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include "Coin.h"


UI::UI(float width, float height) {

	//wczytywanie czcionki
	if (!font.loadFromFile("MedievalSharp-Regular.ttf")) {
		throw std::runtime_error("nie mozna zaladowac czcionki");
	}

	//tlo paska UI
	sidebar.setSize(sf::Vector2f(200, height));
	sidebar.setFillColor(sf::Color(50, 50, 50, 128));
	sidebar.setPosition(0, 0);

	//text zdrowia
	healthText.setFont(font);
	healthText.setCharacterSize(24);
	healthText.setFillColor(sf::Color::White);
	healthText.setPosition(10, 50);

	//text damage
	damageText.setFont(font);
	damageText.setCharacterSize(24);
	damageText.setFillColor(sf::Color::White);
	damageText.setPosition(10, 100);

	//text movementSpeed
	speedText.setFont(font);
	speedText.setCharacterSize(24);
	speedText.setFillColor(sf::Color::White);
	speedText.setPosition(10, 150);

	//text monety
	moneyText.setFont(font);
	moneyText.setCharacterSize(24);
	moneyText.setFillColor(sf::Color::White);
	moneyText.setPosition(10, 200);


}

//funkcja aktualizacji
void UI::update(const Player& player, const sf::View& view) {

	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << player.speed;

	healthText.setString("Health: " + std::to_string(player.health));
	damageText.setString("DMG :   " + std::to_string(player.damage));
	speedText.setString("Speed: " + oss.str());
	moneyText.setString("Money: " + std::to_string(player.getMoney()));

	//pozycja kamery
	sf::Vector2f cameraCenter = view.getCenter();
	sidebar.setPosition(cameraCenter.x - 960, cameraCenter.y - 540); // Prawa i lewa strona ekranu
	healthText.setPosition(cameraCenter.x - 960 + 10, cameraCenter.y - 540 + 50);
	damageText.setPosition(cameraCenter.x - 960 + 10, cameraCenter.y - 540 + 100);
	speedText.setPosition(cameraCenter.x - 960 + 10, cameraCenter.y - 540 + 150);
	moneyText.setPosition(cameraCenter.x - 960 + 10, cameraCenter.y - 540 + 200);

}

// rysowanie 
void UI::draw(sf::RenderWindow& window) {
	window.draw(sidebar);
	window.draw(healthText);
	window.draw(damageText);
	window.draw(speedText);
	window.draw(moneyText);
}
