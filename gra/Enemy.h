#pragma once
#ifndef Enemy_h
#define Enemy_h

#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Weapon.h"
#include <stdio.h>
#include <functional>

class Enemy
{
private:
    //sf::RectangleShape enemyBody;
    sf::RectangleShape enemyBody;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect currentFrame;
    sf::Vector2f spriteSize;


    float speed;
    sf::Clock animationClock;
    float frameDuration;

    int frameWidth, frameHeight;

    int currentFrameIndex;
    std::vector<sf::IntRect> frames; //lista klatek animacji

    Player& player;


    sf::Clock deathClock; // Zegar do efektu migania
    sf::Clock totalDeathClock; // Zegar do znikania przeciwnika
    sf::Clock hitClock;
    sf::Clock hitItClock;
    bool isRed = false; // Czy przeciwnik jest aktualnie czerwony
    bool isAlive = true; // Czy przeciwnik jest aktywny
    bool dead = false;
    bool isRight = true;
    bool hit = false;



public:

    Enemy(const std::string& textureFile, int frameWidth, int frameHeight, float speed, float frameDuration, Player& player);

    //rysowanie
    void draw(sf::RenderWindow& window);

    //animacja
    void update(sf::Vector2f playerPosition, bool facingRight, sf::Vector2f playerSize, int damage, int a, int b, std::function<void()> playerBounceLeft, std::function<void()> playerBounceRight);

    void DrawSpriteWithOutline(sf::RenderWindow& window, sf::Sprite& sprite, float outlineThickness, sf::Color outlineColor);

    //Pozycja
    void setPosition(float x, float y);

    sf::Vector2f getPosition() const;

    sf::Vector2i getFrameSize() const;

    // ruch

    void moveIt(int a, int b);


    void hitIt();


    sf::Clock attackCooldownClock; // Zegar do śledzenia cooldownu
    bool canAttack = true;


    int hp = 100;


    void playerCollision(sf::Vector2f playerPos, sf::Vector2f playerSize, std::function<void()> playerBounceLeft, std::function<void()> playerBounceRight);

};

#endif