#include "LevelManager.h"
#include <SFML/Graphics.hpp>

void LevelManager::loadLevel1(std::vector<Block>& blocks, Coin& coinManager, sf::Texture& dirtTexture, sf::Texture& grassTexture, sf::Texture& woodTexture)
{
    
    //pozycja, wielkoœæ, tekstura, TopOnly, AllSides
      /*toponly*///blocks.emplace_back(sf::Vector2f(.0f, .0f), sf::Vector2f(.0f, .0f), &grassTexture, CollisionType::TopOnly);

      /*allsides*///blocks.emplace_back(sf::Vector2f(.0f, .0f), sf::Vector2f(.0f, .0f), &grassTexture, CollisionType::AllSides);

    blocks.emplace_back(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(20.0f, 60.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(20.0f, 49.0f), sf::Vector2f(32.0f, 12.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(30.0f, 43.0f), sf::Vector2f(16.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(35.0f, 36.0f), sf::Vector2f(6.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(52.0f, 43.0f), sf::Vector2f(4.0f, 6.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(52.0f, 49.0f), sf::Vector2f(4.0f, 12.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(56.0f, 49.0f), sf::Vector2f(10.0f, 12.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(66.0f, 43.0f), sf::Vector2f(4.0f, 6.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(66.0f, 49.0f), sf::Vector2f(4.0f, 12.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(70.0f, 49.0f), sf::Vector2f(65.0f, 12.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(82.0f, 42.0f), sf::Vector2f(5.0f, 4.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(100.0f, 42.0f), sf::Vector2f(5.0f, 4.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(91.0f, 42.0f), sf::Vector2f(5.0f, 4.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(87.0f, 37.0f), sf::Vector2f(4.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(96.0f, 37.0f), sf::Vector2f(4.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(92.0f, 32.0f), sf::Vector2f(3.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(117.0f, 45.0f), sf::Vector2f(13.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(117.0f, 40.0f), sf::Vector2f(13.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(117.0f, 35.0f), sf::Vector2f(13.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(135.0f, 49.0f), sf::Vector2f(20.0f, 12.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(135.0f, 33.0f), sf::Vector2f(4.0f, 16.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(139.0f, 37.0f), sf::Vector2f(4.0f, 12.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(143.0f, 41.0f), sf::Vector2f(4.0f, 2.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(135.0f, 29.0f), sf::Vector2f(4.0f, 4.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(139.0f, 33.0f), sf::Vector2f(4.0f, 4.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(143.0f, 37.0f), sf::Vector2f(4.0f, 4.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(147.0f, 41.0f), sf::Vector2f(4.0f, 2.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(143.0f, 45.0f), sf::Vector2f(12.0f, 4.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(143.0f, 49.0f), sf::Vector2f(12.0f, 12.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(155.0f, 49.0f), sf::Vector2f(12.0f, 12.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(167.0f, 45.0f), sf::Vector2f(3.0f, 4.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(167.0f, 49.0f), sf::Vector2f(3.0f, 12.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(170.0f, 49.0f), sf::Vector2f(65.0f, 12.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(149.0f, 32.0f), sf::Vector2f(6.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(161.0f, 30.0f), sf::Vector2f(6.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(173.0f, 27.0f), sf::Vector2f(6.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(210.0f, 30.0f), sf::Vector2f(8.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(223.0f, 34.0f), sf::Vector2f(8.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(252.0f, 42.0f), sf::Vector2f(3.0f, 4.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(261.0f, 42.0f), sf::Vector2f(3.0f, 4.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(270.0f, 42.0f), sf::Vector2f(3.0f, 4.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(279.0f, 42.0f), sf::Vector2f(3.0f, 4.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(287.0f, 42.0f), sf::Vector2f(3.0f, 4.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(229.0f, 44.0f), sf::Vector2f(6.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(240.0f, 44.0f), sf::Vector2f(6.0f, 2.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(261.0f, 35.0f), sf::Vector2f(3.0f, 3.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(270.0f, 35.0f), sf::Vector2f(3.0f, 3.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(279.0f, 35.0f), sf::Vector2f(3.0f, 3.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(270.0f, 27.0f), sf::Vector2f(3.0f, 3.0f), &grassTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(235.0f, 41.0f), sf::Vector2f(5.0f, 8.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(235.0f, 49.0f), sf::Vector2f(5.0f, 13.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(240.0f, 49.0f), sf::Vector2f(63.0f, 12.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(303.0f, 49.0f), sf::Vector2f(8.0f, 12.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(303.0f, 45.0f), sf::Vector2f(4.0f, 4.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(307.0f, 41.0f), sf::Vector2f(4.0f, 8.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(311.0f, 37.0f), sf::Vector2f(33.0f, 24.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(319.0f, 29.0f), sf::Vector2f(4.0f, 4.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(311.0f, 37.0f), sf::Vector2f(4.0f, 8.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(327.0f, 1.0f), sf::Vector2f(17.0f, 32.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(344.0f, 1.0f), sf::Vector2f(35.0f, 60.0f), &dirtTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(183.0f, 27.0f), sf::Vector2f(2.0f, 2.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(204.0f, 27.0f), sf::Vector2f(2.0f, 2.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(185.0f, 20.0f), sf::Vector2f(4.0f, 9.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(200.0f, 20.0f), sf::Vector2f(4.0f, 9.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(189.0f, 27.0f), sf::Vector2f(11.0f, 2.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(177.0f, 42.0f), sf::Vector2f(2.0f, 4.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(185.0f, 42.0f), sf::Vector2f(2.0f, 4.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(189.0f, 38.0f), sf::Vector2f(2.0f, 4.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(198.0f, 38.0f), sf::Vector2f(2.0f, 4.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(191.0f, 40.0f), sf::Vector2f(7.0f, 2.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(202.0f, 42.0f), sf::Vector2f(2.0f, 4.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(210.0f, 42.0f), sf::Vector2f(2.0f, 4.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(179.0f, 44.0f), sf::Vector2f(6.0f, 2.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(204.0f, 44.0f), sf::Vector2f(6.0f, 2.0f), &grassTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(323.0f, 25.0f), sf::Vector2f(4.0f, 8.0f), &dirtTexture, CollisionType::AllSides);

    // Dodanie monet //po³o¿enie (rozmiar ustawiony w klasie Coin)
    coinManager.add(sf::Vector2f(35.0f, 34.0f));
    coinManager.add(sf::Vector2f(40.0f, 34.0f));
    coinManager.add(sf::Vector2f(84.0f, 40.0f));
    coinManager.add(sf::Vector2f(93.0f, 40.0f));
    coinManager.add(sf::Vector2f(102.0f, 40.0f));
    coinManager.add(sf::Vector2f(93.0f, 30.0f));
    coinManager.add(sf::Vector2f(93.0f, 27.0f));
    coinManager.add(sf::Vector2f(117.0f, 43.0f));
    coinManager.add(sf::Vector2f(121.0f, 43.0f));
    coinManager.add(sf::Vector2f(125.0f, 43.0f));
    coinManager.add(sf::Vector2f(129.0f, 43.0f));
    coinManager.add(sf::Vector2f(117.0f, 38.0f));
    coinManager.add(sf::Vector2f(121.0f, 38.0f));
    coinManager.add(sf::Vector2f(125.0f, 38.0f));
    coinManager.add(sf::Vector2f(129.0f, 38.0f));
    coinManager.add(sf::Vector2f(117.0f, 33.0f));
    coinManager.add(sf::Vector2f(121.0f, 33.0f));
    coinManager.add(sf::Vector2f(125.0f, 33.0f));
    coinManager.add(sf::Vector2f(129.0f, 33.0f));
    coinManager.add(sf::Vector2f(143.0f, 43.0f));
    coinManager.add(sf::Vector2f(145.0f, 43.0f));
    coinManager.add(sf::Vector2f(147.0f, 43.0f));
    coinManager.add(sf::Vector2f(149.0f, 43.0f));
    coinManager.add(sf::Vector2f(168.0f, 42.0f));
    coinManager.add(sf::Vector2f(179.0f, 42.0f));
    coinManager.add(sf::Vector2f(181.0f, 42.0f));
    coinManager.add(sf::Vector2f(183.0f, 42.0f));
    coinManager.add(sf::Vector2f(191.0f, 38.0f));
    coinManager.add(sf::Vector2f(193.0f, 38.0f));
    coinManager.add(sf::Vector2f(195.0f, 38.0f));
    coinManager.add(sf::Vector2f(197.0f, 38.0f));
    coinManager.add(sf::Vector2f(204.0f, 42.0f));
    coinManager.add(sf::Vector2f(206.0f, 42.0f));
    coinManager.add(sf::Vector2f(208.0f, 42.0f));
    coinManager.add(sf::Vector2f(190.0f, 22.0f));
    coinManager.add(sf::Vector2f(194.0f, 22.0f));
    coinManager.add(sf::Vector2f(198.0f, 22.0f));
    coinManager.add(sf::Vector2f(190.0f, 24.0f));
    coinManager.add(sf::Vector2f(194.0f, 24.0f));
    coinManager.add(sf::Vector2f(198.0f, 24.0f));
    coinManager.add(sf::Vector2f(190.0f, 26.0f));
    coinManager.add(sf::Vector2f(194.0f, 26.0f));
    coinManager.add(sf::Vector2f(198.0f, 26.0f));
    coinManager.add(sf::Vector2f(229.0f, 47.0f));
    coinManager.add(sf::Vector2f(231.0f, 47.0f));
    coinManager.add(sf::Vector2f(233.0f, 47.0f));
    coinManager.add(sf::Vector2f(241.0f, 47.0f));
    coinManager.add(sf::Vector2f(243.0f, 47.0f));
    coinManager.add(sf::Vector2f(245.0f, 47.0f));
    coinManager.add(sf::Vector2f(253.0f, 40.0f));
    coinManager.add(sf::Vector2f(262.0f, 40.0f));
    coinManager.add(sf::Vector2f(271.0f, 40.0f));
    coinManager.add(sf::Vector2f(280.0f, 40.0f));
    coinManager.add(sf::Vector2f(288.0f, 40.0f));
    coinManager.add(sf::Vector2f(262.0f, 32.0f));
    coinManager.add(sf::Vector2f(271.0f, 32.0f));
    coinManager.add(sf::Vector2f(280.0f, 32.0f));
    coinManager.add(sf::Vector2f(271.0f, 24.0f));
   
    //sklep
    blocks.emplace_back(sf::Vector2f(5.0f, 69.0f), sf::Vector2f(2.0f, 30.0f), &woodTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(38.0f, 69.0f), sf::Vector2f(2.0f, 30.0f), &woodTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(7.0f, 69.0f), sf::Vector2f(31.0f, 2.0f), &woodTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(7.0f, 97.0f), sf::Vector2f(31.0f, 2.0f), &woodTexture, CollisionType::AllSides);
    blocks.emplace_back(sf::Vector2f(10.0f, 94.0f), sf::Vector2f(4.0f, 1.0f), &woodTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(15.0f, 94.0f), sf::Vector2f(4.0f, 1.0f), &woodTexture, CollisionType::TopOnly);
    blocks.emplace_back(sf::Vector2f(20.0f, 94.0f), sf::Vector2f(4.0f, 1.0f), &woodTexture, CollisionType::TopOnly);


}


