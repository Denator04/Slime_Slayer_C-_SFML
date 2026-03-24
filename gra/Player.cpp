#include "Player.h"
#include "weapon.h"
#include "Block.h"
#include <vector>
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
    : animation(texture, imageCount, switchTime) {
    row = 0;
    faceRight = true;

    body.setSize(sf::Vector2f(50.0f, 75.0f));
    body.setPosition(1100.0f, 2300.0f);
    body.setTexture(texture);
   // body.setOutlineThickness(2.0f); // Thickness of the outline
   // body.setOutlineColor(sf::Color::Red); // Red outline for better visibility 

    getHitSound.loadFromFile("hurt.wav");
    getHitEffect.setBuffer(getHitSound);

    jumpBuffer.loadFromFile("jump.wav");
    jumpSound.setBuffer(jumpBuffer);

    // Domyœlne przypisania klawiszy
    controls["Ruch w lewo"] = sf::Keyboard::A;
    controls["Ruch w prawo"] = sf::Keyboard::D;
    controls["Skok"] = sf::Keyboard::W;
}

void Player::setControl(const std::string& action, sf::Keyboard::Key key) {
    controls[action] = key;
}

sf::Keyboard::Key Player::getControl(const std::string& action) const {
    auto it = controls.find(action);
    if (it != controls.end()) {
        return it->second;
    }
    return sf::Keyboard::Unknown; // Zwraca nieznany klawisz, jeœli akcja nie istnieje
}

void Player::addMoney(int amount) {
    money += amount;
}

int Player::getMoney() const {
    return money;  // Zwracamy liczbê monet
}

void Player::increaseSpeed(float amount) {
    speed += amount;
}

void Player::increaseHealth(int amount) {
    health += amount;
}

void Player::increaseDamage(int amount) {
    damage += amount;
}

sf::Vector2f Player::getSize() {
    return body.getSize();
}

void Player::subtractMoney(int amount) {
    if (money >= amount) {
        money -= amount;
    }
}


void Player::Update(float deltaTime, const std::vector<Block>& blocks)
{
    float currentSpeed = speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        currentSpeed *= 1.5f;
    }

    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(controls["Ruch w lewo"]) && !collided)
    {
        //std::cout << speed;
        movement.x -= speed * deltaTime;
        body.move(-0.2f * (currentSpeed / speed), 0.0f);
        faceRight = false;
    }
    if (sf::Keyboard::isKeyPressed(controls["Ruch w prawo"]) && !collided)
    {
        movement.x += speed * deltaTime;
        body.move(0.2f * (currentSpeed / speed), 0.0f);
        faceRight = true;
    }




    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);




    // spacja jako teleport na gore //
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        body.setPosition(206.0f, 206.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        body.setPosition(1100.0f, 2300.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        body.setPosition(15750.0f, 1500.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
        body.setPosition(450.0f, 4750.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
        money += 10;
    }






    if (invincible && invincibilityClock.getElapsedTime().asSeconds() >= invincibilityDuration) {
        invincible = false;  // Gracz przestaje byæ nietykalny
        soundPlayed = false;
    }


    if (invincible) {
        // Co pó³ sekundy zmieniamy kolor
        if (!soundPlayed) {
            getHitEffect.play();
            soundPlayed = true;
        }


        if (blinkClock.getElapsedTime().asSeconds() >= 0.5f) {
            // Prze³¹cz kolor (miganie na szaro)
            if (body.getFillColor() == sf::Color::White) {
                body.setFillColor(sf::Color(150, 150, 150));  // Szary kolor
            }
            else {
                body.setFillColor(sf::Color::White);  // Przywróæ oryginalny kolor
            }
            blinkClock.restart();  // Zresetuj zegar migania
        }
    }




















    // ?adowanie si?y skoku przytrzymuj?c spacj?
    if (sf::Keyboard::isKeyPressed(controls["Skok"]))
    {
        if (!isJumping)
        {
            jumpCharge += 0.001f; // ?adowanie si?y skoku
            if (jumpCharge > 0.5f)
                jumpCharge = 0.5f; // Ogranicz ?adowanie
        }
    }
    else
    {
        if (!isJumping && jumpCharge > 0.0f)
        {
            float jumpForce = minJumpForce + (maxJumpForce - minJumpForce) * jumpCharge;
            velocityY = jumpForce;
            isJumping = true;
            jumpSound.play();
        }
        jumpCharge = 0.0f; // Resetuj ?adowanie po zwolnieniu
    }

    //// Zastosowanie grawitacji
    velocityY += gravity;

    //// Aktualizacja pozycji gracza w osi Y
    body.move(0.0f, velocityY);

    // Zmienne pomocnicze do nowej pozycji
    sf::Vector2f newPosition = body.getPosition();
    newPosition.x += movement.x;
    newPosition.y += movement.y;

    // Flagi detekcji kolizji
    bool isOnGround = false;

    // Detekcja kolizji z ka¿dym blokiem
    for (const auto& block : blocks) {
        sf::FloatRect blockBounds = block.getBounds();
        sf::FloatRect playerBounds(newPosition, body.getSize());

        if (block.getCollisionType() == CollisionType::TopOnly) {
            // Obs³uga kolizji tylko od góry
            if (playerBounds.top + playerBounds.height > blockBounds.top &&
                playerBounds.top + playerBounds.height <= blockBounds.top + 5 &&
                playerBounds.left + playerBounds.width - 3 > blockBounds.left &&
                playerBounds.left + 3 < blockBounds.left + blockBounds.width &&
                velocityY > 0) // Spadanie na blok
            {
                newPosition.y = blockBounds.top - body.getSize().y;
                velocityY = 0.0f;
                isOnGround = true;
                isJumping = false;
            }
        }
        else if (block.getCollisionType() == CollisionType::AllSides) {
            // Obs³uga kolizji ze wszystkich stron
            if (playerBounds.intersects(blockBounds)) {
                // Kolizja w osi Y
                if (velocityY > 0 && playerBounds.top + playerBounds.height <= blockBounds.top + 5) {
                    // Spadanie na blok
                    newPosition.y = blockBounds.top - body.getSize().y;
                    velocityY = 0.0f;
                    isOnGround = true;
                    isJumping = false;
                }
                else if (velocityY < 0 && playerBounds.top >= blockBounds.top + blockBounds.height - 5) {
                    // Uderzenie w blok od do³u
                    newPosition.y = blockBounds.top + blockBounds.height;
                    velocityY = 0.0f;
                }

                // Kolizja w osi X
                if (movement.x > 0 && playerBounds.left + playerBounds.width > blockBounds.left &&
                    playerBounds.left < blockBounds.left) {
                    // Ruch w prawo - zatrzymaj przy lewej krawêdzi bloku
                    newPosition.x = blockBounds.left - body.getSize().x;
                }
                else if (movement.x < 0 && playerBounds.left < blockBounds.left + blockBounds.width &&
                    playerBounds.left + playerBounds.width > blockBounds.left + blockBounds.width) {
                    // Ruch w lewo - zatrzymaj przy prawej krawêdzi bloku
                    newPosition.x = blockBounds.left + blockBounds.width;
                }
            }
        }
    }

    // Zaktualizowanie pozycji gracza
    body.setPosition(newPosition);

    if (movement.x == 0.0f)
    {
        row = 0;
    }
    else
    {
        row = 1;

        if (movement.x > 0.0f)
            faceRight = true;
        else
            faceRight = false;
    }
    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    //body.move(movement);


    ///////////kolizja z przeciwnikiem





}

sf::Vector2f Player::GetPosition() const {
    return body.getPosition();

}

void Player::setPosition(const sf::Vector2f& newPosition) {
    body.setPosition(newPosition);
}

bool Player::IsFacingRight() const {
    return faceRight;
}


void Player::Draw(sf::RenderWindow& window)
{
    window.draw(floor);
    window.draw(square);
    window.draw(body);
}

void Player::bounceRight() {
    if (!invincible) {
        health -= 10;  // Zmniejsz zdrowie, jeœli gracz nie jest nietykalny
        invincible = true;  // Ustaw gracza jako nietykalnego
        invincibilityClock.restart();  // Zresetuj zegar
    }
}


void Player::bounceLeft() {
    if (!invincible) {
        health -= 10;  // Zmniejsz zdrowie, jeœli gracz nie jest nietykalny
        invincible = true;  // Ustaw gracza jako nietykalnego
        invincibilityClock.restart();  // Zresetuj zegar
        std::cout << "asddddddd" << std::endl;
    }
}
