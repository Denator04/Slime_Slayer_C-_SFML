#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Coin.h"
#include "Animation.h"
#include "weapon.h"
#include "Block.h"
#include <vector>
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
#include <string>

class Player
{
public:

	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	// Mo¿esz te¿ dodaæ kod dla ruchu gracza, ale tutaj nie zmieniamy tej czêœci.


	void Update(float deltaTime, const std::vector<Block>& blocks);
	void Draw(sf::RenderWindow& window);
	void addMoney(int amount);
	int getMoney() const;
	void increaseSpeed(float amount);
	void increaseHealth(int amount);
	void increaseDamage(int amount);
	void subtractMoney(int amount);


	sf::Vector2f GetPosition() { return body.getPosition(); }

	// Zwraca globalne granice gracza
	sf::FloatRect GetBounds() const {
		return body.getGlobalBounds();
	}

	sf::RectangleShape& getBody() {
		return body; // Zwracamy referencjê do cia³a gracza
	}


	/////////////////////////////////////////////////////////// getting hit 
	bool playerHit = false;
	sf::Sound getHitEffect;
	sf::SoundBuffer getHitSound;
	sf::Sound jumpSound;
	sf::SoundBuffer jumpBuffer;
	bool soundPlayed = false;

	//statystyki:
	float speed = 100.0f;
	int health = 100;
	int damage = 10;

	void update(int deltaDamage, int deltaHealth, int deltaSpeed, int deltaMoney) {
		damage += deltaDamage;
		health += deltaHealth;
		money += deltaMoney;
		speed += deltaSpeed;
		if (health < 0) health = 0;  // Zapewnienie, ¿e zdrowie nie spadnie poni¿ej 0
	}

	sf::Vector2f getSize();

	// cos z atakiem

	sf::Vector2f GetPosition() const;

	bool IsFacingRight() const;

	void setControl(const std::string& action, sf::Keyboard::Key key);
	sf::Keyboard::Key getControl(const std::string& action) const;
	void setPosition(const sf::Vector2f& newPosition);


	void bounceLeft();
	void bounceRight();


	void enemyCollision();


private:

	int money = 0;
	sf::RectangleShape body;
	sf::RectangleShape square;
	sf::RectangleShape floor;
	Animation animation;

	bool isAttacking = false;
	unsigned int row;
	bool faceRight;
	bool collided = false;
	bool invincible = false;
	float invincibilityDuration = 3.0f;
	sf::Clock invincibilityClock;
	sf::Clock blinkClock;


	std::map<std::string, sf::Keyboard::Key> controls;


	// Zmienne fizyki
	const float gravity = 0.001f; // Sta³a grawitacyjna
	const float maxJumpForce = -1.5f; // Maksymalna si³a skoku
	const float minJumpForce = -0.7f; // Minimalna si³a skoku
	float velocityY = 0.0f; // Prêdkoœæ w osi Y
	bool isJumping = false; // Czy gracz jest w powietrzu?
	bool isSpacePressed = false; // Czy klawisz spacji zosta³ wciœniêty?
	float jumpCharge = 0.0f; // £adowanie skoku
	sf::Clock jumpClock;
};
#endif // PLAYER_H