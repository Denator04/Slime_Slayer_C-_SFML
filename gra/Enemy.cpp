#include "Enemy.h"
#include <stdexcept>
#include "Player.h"
#include <iostream>

Enemy::Enemy(const std::string& textureFile, int frameWidth, int frameHeight, float speed, float frameDuration, Player& player)
	: frameWidth(frameWidth), frameHeight(frameHeight), speed(speed), frameDuration(frameDuration), currentFrameIndex(0), player(player) {

	//ladowanie tekstur
	if (!texture.loadFromFile(textureFile)) {
		throw std::runtime_error("nie mozna zaladowac tekstury!");
	}

	sprite.setTexture(texture);
	sprite.setScale(4.0f, 4.0f); // skala


	sf::IntRect textureRect = sprite.getTextureRect();
	spriteSize.x = sprite.getTextureRect().width * sprite.getScale().x;
	spriteSize.y = sprite.getTextureRect().height * sprite.getScale().y;


	//wybieranie klatek//
	frames.push_back(sf::IntRect(0 * frameWidth, 0 * frameHeight, frameWidth, frameHeight)); // 0x0
	frames.push_back(sf::IntRect(1 * frameWidth, 0 * frameHeight, frameWidth, frameHeight)); // 0x1
	frames.push_back(sf::IntRect(2 * frameWidth, 0 * frameHeight, frameWidth, frameHeight)); // 0x2
	frames.push_back(sf::IntRect(3 * frameWidth, 0 * frameHeight, frameWidth, frameHeight)); // 0x3
	frames.push_back(sf::IntRect(1 * frameWidth, 1 * frameHeight, frameWidth, frameHeight)); // 1x1
	frames.push_back(sf::IntRect(2 * frameWidth, 1 * frameHeight, frameWidth, frameHeight)); // 1x2
	frames.push_back(sf::IntRect(2 * frameWidth, 1 * frameHeight, frameWidth, frameHeight)); // 1x2

	frames.push_back(sf::IntRect(2 * frameWidth, 1 * frameHeight, frameWidth, frameHeight)); // 1x2
	frames.push_back(sf::IntRect(1 * frameWidth, 1 * frameHeight, frameWidth, frameHeight)); // 1x1
	frames.push_back(sf::IntRect(3 * frameWidth, 0 * frameHeight, frameWidth, frameHeight)); // 0x3
	frames.push_back(sf::IntRect(2 * frameWidth, 0 * frameHeight, frameWidth, frameHeight)); // 0x2
	frames.push_back(sf::IntRect(1 * frameWidth, 0 * frameHeight, frameWidth, frameHeight)); // 0x1
	frames.push_back(sf::IntRect(0 * frameWidth, 0 * frameHeight, frameWidth, frameHeight)); // 0x0
	frames.push_back(sf::IntRect(0 * frameWidth, 0 * frameHeight, frameWidth, frameHeight)); // 0x0


	currentFrame = frames[0];
	sprite.setTextureRect(currentFrame);



}


void Enemy::update(sf::Vector2f playerPosition, bool facingRight, sf::Vector2f playerSize, int damage, int a, int b, std::function<void()> playerBounceLeft, std::function<void()> playerBounceRight) {
	if (animationClock.getElapsedTime().asSeconds() >= frameDuration) {
		animationClock.restart();

		//zmiana na nastepna klatke
		currentFrameIndex = (currentFrameIndex + 1) % frames.size();
		currentFrame = frames[currentFrameIndex];

		sprite.setTextureRect(currentFrame);
	}
	enemyBody.setPosition(sprite.getPosition());

	/////////  Kontakt Z Bronią  //////////

	sf::FloatRect bounds = sprite.getGlobalBounds();


	if (attackCooldownClock.getElapsedTime().asSeconds() >= 0.5f) {
		canAttack = true; // Po 0.5 sekundy możemy ponownie atakować
	}

	playerCollision(playerPosition, playerSize, playerBounceLeft, playerBounceRight);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {

		if ((sprite.getPosition().x + 25 >= playerPosition.x + playerSize.x) && (sprite.getPosition().x + 25 < playerPosition.x + playerSize.x + 75) && (facingRight)
			&& (sprite.getPosition().y <= playerPosition.y + (playerSize.y / 2)) && (sprite.getPosition().y + spriteSize.y >= playerPosition.y + (playerSize.y / 2)) && canAttack && !hit) {
			attackCooldownClock.restart(); // Resetowanie zegara cooldownu
			canAttack = false;
			hp -= damage;
			hit = true;
			hitClock.restart();

		}
		else if ((sprite.getPosition().x + 25 + bounds.width - 50 <= playerPosition.x) && (sprite.getPosition().x + 25 + bounds.width - 50 > playerPosition.x - 75) && (!facingRight)
			&& (sprite.getPosition().y <= playerPosition.y + (playerSize.y / 2) - 40) && (sprite.getPosition().y + bounds.height + 40 >= playerPosition.y + (playerSize.y / 2)) && canAttack && !hit) {
			attackCooldownClock.restart(); // Resetowanie zegara cooldownu
			canAttack = false;
			hp -= damage;
			hit = true;
			hitClock.restart();



		}

	}


	if (hitClock.getElapsedTime().asSeconds() >= 0.3) {
		hit = false;
	}

	if (hit) {

		if (hitItClock.getElapsedTime().asSeconds() < 0.15f) {
			// Pierwsze 0.15 sekundy zmieniamy na czarny
			sprite.setColor(sf::Color::Black);
		}
		else if (hitItClock.getElapsedTime().asSeconds() < 0.3f && hitItClock.getElapsedTime().asSeconds() > 0.15f) {
			// Kolejne 0.15 sekundy wracamy do białego
			sprite.setColor(sf::Color::White);
		}

	}


	if (hp <= 0) {

		if (!dead) {
			dead = true;
			totalDeathClock.restart();
		}
	}

	if (dead) {

		if (deathClock.getElapsedTime().asSeconds() >= 0.1f) {
			deathClock.restart();
			isRed = !isRed; // Zmieniamy kolor między czerwonym a "normalnym"
			sprite.setColor(isRed ? sf::Color::Red : sf::Color::White);
		}

		// Po 1 sekundzie od śmierci przeciwnik znika
		if (totalDeathClock.getElapsedTime().asSeconds() >= 1.0f) {
			isAlive = false; // Flaga mówi, że przeciwnik jest martwy
		}


	}

	moveIt(a, b);

}


void Enemy::draw(sf::RenderWindow& window) {

	if (isAlive) {
		window.draw(sprite);
		window.draw(enemyBody);
		//DrawSpriteWithOutline(window, sprite, 2.0f, sf::Color::Magenta);
	}

}


void Enemy::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}


sf::Vector2i Enemy::getFrameSize() const {
	return sf::Vector2i(currentFrame.width, currentFrame.height);
}

sf::Vector2f Enemy::getPosition() const {
	return sprite.getPosition();
}


void Enemy::moveIt(int a, int b) {

	if (isRight && (sprite.getPosition().x <= b) && !hit) {
		sprite.setScale(4.0f, 4.0f);
		sprite.setPosition(sprite.getPosition().x + 0.03f, sprite.getPosition().y);
	}
	if (sprite.getPosition().x >= b) {
		isRight = false;
	}

	if (!isRight && sprite.getPosition().x >= a && !hit) {
		sprite.setPosition(sprite.getPosition().x - 0.03f, sprite.getPosition().y);
	}
	if (sprite.getPosition().x <= a) {
		isRight = true;
	}


}







void Enemy::DrawSpriteWithOutline(sf::RenderWindow& window, sf::Sprite& sprite, float outlineThickness, sf::Color outlineColor) {
	// Stwórz prostokąt na podstawie granic sprite'a
	sf::FloatRect bounds = sprite.getGlobalBounds();

	sf::RectangleShape outline(sf::Vector2f(bounds.width + 2 * outlineThickness - 50, bounds.height + 2 * outlineThickness - 40));
	outline.setPosition(bounds.left - outlineThickness + 25, bounds.top - outlineThickness + 40);
	outline.setFillColor(sf::Color::Transparent); // Kontur tylko na krawędziach
	outline.setOutlineThickness(outlineThickness);
	outline.setOutlineColor(outlineColor);

	// Rysuj kontur
	window.draw(outline);
}


void Enemy::playerCollision(sf::Vector2f playerPos, sf::Vector2f playerSize, std::function<void()> playerBounceLeft, std::function<void()> playerBounceRight) {

	sf::FloatRect bounds = sprite.getGlobalBounds();
	int rightX = playerPos.x + playerSize.x - 20;
	int topY = playerPos.y;
	int spriteBottomY = sprite.getPosition().y + bounds.height - 40;
	int bottomY = playerPos.y + playerSize.y;
	int leftX = playerPos.x;
	int middle = (rightX + leftX) / 2;


	if (((rightX > sprite.getPosition().x) && (rightX < sprite.getPosition().x + 30) ||
		(leftX < sprite.getPosition().x + 75) && (leftX > sprite.getPosition().x + 45) ||
		middle >= sprite.getPosition().x + 5 && middle <= sprite.getPosition().x + 65)
		&& (topY < spriteBottomY) && (bottomY - 40 > sprite.getPosition().y) && !dead) {
		playerBounceLeft();
	}


}