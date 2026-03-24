#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Player.h"
#include <SFML/Audio.hpp>
#include "Coinanimation.h"
#include "Enemy.h""
#include "UI.h"
#include "weapon.h"
#include "Block.h"
#include <vector>
#include "Coin.h"
#include "KeyUtils.h"
#include "LevelManager.h"
#include "Shop.h"
#include "EndFlag.h"

float volumePercentage = 25;
float effectsPercentage = 25;
sf::Sound music;
sf::Sound menuMusic;
sf::Sound jumpSound;
sf::Sound coinSound;

void showControls(sf::RenderWindow& window, Player& player)
{
    sf::Font font;
    if (!font.loadFromFile("MedievalSharp-Regular.ttf")) {
        std::cerr << "Blad!" << std::endl;
        return;
    }

    // Wczytanie tekstury t³a
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("menu.png")) // Œcie¿ka do obrazka
    {
        std::cerr << "B³¹d wczytywania tekstury t³a!" << std::endl;
        return;
    }

    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    background.setTexture(&backgroundTexture);

    // Teksty dla akcji sterowania
    sf::Text leftLabel("Ruch w lewo", font, 30);
    sf::Text rightLabel("Ruch w prawo", font, 30);
    sf::Text jumpLabel("Skok", font, 30);
    sf::Text backButton("Powrot", font, 30);

    // Pozycje tekstów
    leftLabel.setPosition(100, 200);
    rightLabel.setPosition(100, 300);
    jumpLabel.setPosition(100, 400);
    backButton.setPosition(100, 600);

    // Pola dla klawiszy
    sf::RectangleShape leftBox(sf::Vector2f(50, 50));
    sf::RectangleShape rightBox(sf::Vector2f(50, 50));
    sf::RectangleShape jumpBox(sf::Vector2f(50, 50));

    leftBox.setPosition(400, 200);
    rightBox.setPosition(400, 300);
    jumpBox.setPosition(400, 400);

    leftBox.setFillColor(sf::Color::Black);
    rightBox.setFillColor(sf::Color::Black);
    jumpBox.setFillColor(sf::Color::Black);

    // Teksty aktualnych klawiszy
    sf::Text leftKey(KeyUtils::KeyToString(player.getControl("Ruch w lewo")), font, 30);
    sf::Text rightKey(KeyUtils::KeyToString(player.getControl("Ruch w prawo")), font, 30);
    sf::Text jumpKey(KeyUtils::KeyToString(player.getControl("Skok")), font, 30);

    leftKey.setPosition(420, 210);
    rightKey.setPosition(420, 310);
    jumpKey.setPosition(420, 410);

    // Zmienna œledz¹ca edycjê klawiszy
    std::string activeEdit = "";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Wciœniêcie myszki
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    return; // Powrót do menu
                }

                if (leftBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    activeEdit = "Ruch w lewo";
                    leftBox.setFillColor(sf::Color::Cyan);
                }
                else if (rightBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    activeEdit = "Ruch w prawo";
                    rightBox.setFillColor(sf::Color::Cyan);
                }
                else if (jumpBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    activeEdit = "Skok";
                    jumpBox.setFillColor(sf::Color::Cyan);
                }
                else {
                    activeEdit = "";
                    leftBox.setFillColor(sf::Color::Black);
                    rightBox.setFillColor(sf::Color::Black);
                    jumpBox.setFillColor(sf::Color::Black);
                }
            }

            // Wciœniêcie klawisza
            if (event.type == sf::Event::KeyPressed && !activeEdit.empty()) {
                sf::Keyboard::Key newKey = event.key.code;
                player.setControl(activeEdit, newKey);

                // Aktualizacja wyœwietlanego klawisza
                if (activeEdit == "Ruch w lewo") {
                    leftKey.setString(KeyUtils::KeyToString(newKey));
                }
                else if (activeEdit == "Ruch w prawo") {
                    rightKey.setString(KeyUtils::KeyToString(newKey));
                }
                else if (activeEdit == "Skok") {
                    jumpKey.setString(KeyUtils::KeyToString(newKey));
                }

                // Zakoñczenie edycji
                activeEdit = "";
                leftBox.setFillColor(sf::Color::Black);
                rightBox.setFillColor(sf::Color::Black);
                jumpBox.setFillColor(sf::Color::Black);
            }
        }

        // Rysowanie na ekranie
        window.clear();
        window.draw(background);
        window.draw(leftLabel);
        window.draw(rightLabel);
        window.draw(jumpLabel);
        window.draw(backButton);

        window.draw(leftBox);
        window.draw(rightBox);
        window.draw(jumpBox);

        window.draw(leftKey);
        window.draw(rightKey);
        window.draw(jumpKey);
        window.display();
    }
}

void showOptions(sf::RenderWindow& window, Player& player)
{
    sf::Font font;
    if (!font.loadFromFile("MedievalSharp-Regular.ttf")) // Za³aduj czcionkê
    {
        std::cerr << "Blad!" << std::endl;
        return;
    }

    // Wczytanie tekstury t³a
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("menu.png")) // Œcie¿ka do obrazka
    {
        std::cerr << "B³¹d wczytywania tekstury t³a!" << std::endl;
        return;
    }

    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    background.setTexture(&backgroundTexture);

    // Opcje
    sf::Text volumeLabel("Music", font, 40);
    sf::Text effectsLabel("Effects", font, 40);
    sf::Text controlsLabel("Ustawienia Sterowania", font, 40);
    sf::Text backButton("Powrot", font, 40);

    volumeLabel.setPosition(200, 200);
    backButton.setPosition(200, 800);
    effectsLabel.setPosition(200, 400);
    controlsLabel.setPosition(200, 600);
    effectsLabel.setFillColor(sf::Color::White);

    // Paseki g³oœnoœci
        //muzyka
    sf::RectangleShape volumeBar(sf::Vector2f(300, 20));
    volumeBar.setFillColor(sf::Color::White);
    volumeBar.setPosition(200, 300);
    sf::RectangleShape volumeLevel(sf::Vector2f(volumeBar.getSize().x / 100 * volumePercentage, 20));
    volumeLevel.setFillColor(sf::Color::Green);
    volumeLevel.setPosition(200, 300);


    //efekty

    sf::RectangleShape effectsBar(sf::Vector2f(300, 20));
    effectsBar.setFillColor(sf::Color::White);
    effectsBar.setPosition(200, 500);
    sf::RectangleShape effectsLevel(sf::Vector2f(effectsBar.getSize().x / 100 * effectsPercentage, 20));
    effectsLevel.setFillColor(sf::Color::Green);
    effectsLevel.setPosition(200, 500);


    bool dragging = false;
    bool draggingEffects = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    return; // Powrót do menu

                if (controlsLabel.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    showControls(window, player);

                if (volumeBar.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    dragging = true;

                if (effectsBar.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    draggingEffects = true;
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                dragging = false;
                draggingEffects = false;
            }

            if (event.type == sf::Event::MouseMoved && dragging)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                float newWidth = std::max(0.0f, std::min(300.0f, (float)(mousePos.x - 200)));
                volumeLevel.setSize(sf::Vector2f(newWidth, 20));
                volumePercentage = (volumeLevel.getSize().x / volumeBar.getSize().x) * 100;
                menuMusic.setVolume(volumePercentage);
                music.setVolume(volumePercentage);
            }
            if (event.type == sf::Event::MouseMoved && draggingEffects)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                float newWidth = std::max(0.0f, std::min(300.0f, (float)(mousePos.x - 200)));
                effectsLevel.setSize(sf::Vector2f(newWidth, 20));
                effectsPercentage = (effectsLevel.getSize().x / effectsBar.getSize().x) * 100;
                player.jumpSound.setVolume(effectsPercentage);
            }
        }




        window.clear();
        window.draw(background);
        window.draw(volumeLabel);
        window.draw(volumeBar);
        window.draw(volumeLevel);
        window.draw(backButton);
        window.draw(effectsBar);
        window.draw(effectsLevel);
        window.draw(effectsLabel);
        window.draw(controlsLabel);
        window.display();
    }
}

void showText(sf::RenderWindow& window, sf::Font& font) {
    sf::RectangleShape blackBackground(sf::Vector2f(window.getSize()));
    blackBackground.setFillColor(sf::Color::Black);

    // Tekst do wyœwietlenia
    std::vector<std::string> textLines = {
        "W nienazwanej krainie zyl sobie pewien rycerz ze swoim kotem.",
        "Spokoj ich zywota zakonczyl siê z momentem, kiedy slime'y zaatakowaly",
        "Kot nie ocalal z tego ataku, a rycerz poprzysiagl zemste za swojego przyjaciela",
        "Wyruszyl wiec w podroz poszukujac Krola Slime-ow, ktory stal za tym atakiem"
    };

    std::vector<sf::Text> texts;
    for (size_t i = 0; i < textLines.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(textLines[i]);
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::White);
        text.setPosition(100, 100 + i * 60); // Ustawienie pozycji tekstów
        texts.push_back(text);
    }

    // Pêtla do wyœwietlania tekstu po kolei
    for (size_t i = 0; i < texts.size(); ++i) {
        bool displayed = false;

        // Czekamy na klikniêcie, aby wyœwietliæ kolejn¹ linijkê
        while (!displayed) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    displayed = true;
                    window.clear();
                    window.draw(blackBackground); // Rysowanie t³a
                    for (size_t j = 0; j <= i; ++j) {
                        window.draw(texts[j]); // Rysowanie tekstów, które ju¿ zosta³y wyœwietlone
                    }
                    window.display();
                }
            }
        }
    }

    // Po wyœwietleniu tekstu, przechodzimy do gry
}







//**********    MENU    ************    MENU    ************//







int showMenu(sf::RenderWindow& window, Player& player)
{

    //****SOUND***//
    sf::SoundBuffer menuBuffer;
    menuBuffer.loadFromFile("MenuMusic.mp3");

    menuMusic.setBuffer(menuBuffer);
    if (menuMusic.getStatus() != sf::Music::Status::Playing) {
        menuMusic.play();
    }
    menuMusic.setVolume(volumePercentage);




    sf::Font font;
    if (!font.loadFromFile("MedievalSharp-Regular.ttf")) // Za³aduj czcionkê
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    // **** T£O MENU **** //
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("menu.png")) {
        std::cerr << "Failed to load menu background image!" << std::endl;
        return -1;
    }

    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    background.setTexture(&backgroundTexture);

    sf::Texture logoTexture;
    if (!logoTexture.loadFromFile("logo.png")) {
        std::cerr << "Failed to load logo image!" << std::endl;
        return -1;
    }
    sf::RectangleShape logo;
    logo.setTexture(&logoTexture);
    logo.setPosition(sf::Vector2f(50.0f, 50.0f));
    logo.setSize(sf::Vector2f(420.0f, 239.0f));
    


    // Przyciski menu
    sf::Text startButton("Start", font, 50);
    sf::Text optionsButton("Opcje", font, 50);
    sf::Text exitButton("Wyjscie", font, 50);

    startButton.setPosition(200, 300);
    optionsButton.setPosition(200, 400);
    exitButton.setPosition(200, 500);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    showText(window, font);
                    return 1; // Rozpocznij grê
                }

                if (optionsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    showOptions(window, player); //Przejœcie do opcji

                if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    return 0; // Wyjœcie z gry
            }
        }



        window.clear();
        window.draw(background);
        window.draw(logo);
        window.draw(startButton);
        window.draw(optionsButton);
        window.draw(exitButton);
        window.display();
    }

    return 0; // Wyjœcie domyœlne
}






//**********    MAIN    ************    MAIN    ************//







int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Tutorial", sf::Style::Close | sf::Style::Default);
    

    // ***** Weapon ***** //

    sf::Texture weaponTexture;

    if (!weaponTexture.loadFromFile("newAttack.png")) {
        std::cout << "Warning: weapon texture not loaded!" << std::endl;
    }

    Weapon weapon1(&weaponTexture, { 2,1 }, 0.1f);


    sf::Texture playerTexture;
    playerTexture.loadFromFile("sheet_movement.png");

    Player player(&playerTexture, sf::Vector2u(8, 2), 0.3f);

    sf::Font font;
    if (!font.loadFromFile("MedievalSharp-Regular.ttf")) // Za³aduj czcionkê
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    int menuResult = showMenu(window, player);
    if (menuResult == 0)
        return 0; // Wyjœcie z gry


    //***** Interface ******//
    UI ui(window.getSize().x, window.getSize().y);

    sf::RectangleShape background_sky;
    background_sky.setSize(sf::Vector2f(16500.0f, 3000.0f));
    background_sky.setPosition(100.0f, -500.0f);
    background_sky.setFillColor(sf::Color(0, 194, 252));

    sf::RectangleShape background_cave;
    background_cave.setSize(sf::Vector2f(1450.0f, 200.0f));
    background_cave.setPosition(15750.0f, 1650.0f);
    background_cave.setFillColor(sf::Color(41, 24, 12));

    sf::RectangleShape background_shop;
    background_shop.setSize(sf::Vector2f(1550.0f, 1300.0f));
    background_shop.setPosition(350.0f, 3550.0f);
    background_shop.setFillColor(sf::Color(148, 88, 9));

    //****SOUND***//
                    //***Gameplay Music***//
    sf::SoundBuffer gameplayBuffer;
    gameplayBuffer.loadFromFile("music.mp3");
    music.setBuffer(gameplayBuffer);

    music.setVolume(volumePercentage);
    if (music.getStatus() != sf::Music::Status::Playing) {
        music.play();
    }


    //***Jump Sound***//
    
    player.jumpSound.setVolume(effectsPercentage);

    sf::View view(sf::FloatRect(0.0f, 0.0f, 1920.0f, 1080.0f));

    //coin i jego animacja

    Coin coinManager("coin_texture.png", sf::Vector2u(8, 1), 0.3f, "coin.wav");

    //Tekstury bloków

    sf::Texture grassTexture;
    grassTexture.loadFromFile("grass.png");
    sf::Texture dirtTexture;
    dirtTexture.loadFromFile("dirt.png");
    sf::Texture brickTexture;
    brickTexture.loadFromFile("brick.png");
    sf::Texture platformTexture;
    platformTexture.loadFromFile("platform.png");
    sf::Texture metaFlag;
    metaFlag.loadFromFile("meta.png");
    sf::Texture woodTexture;
    woodTexture.loadFromFile("shop_floor.png");
    

    // Tworzenie bloków
    std::vector<Block> blocks;

    LevelManager::loadLevel1(blocks, coinManager, dirtTexture, grassTexture, woodTexture);
    
    
    sf::RectangleShape meta_flag;
    meta_flag.setSize(sf::Vector2f(150.0f, 150.0f));
    meta_flag.setPosition(17000.0f, 1700.0f);
    meta_flag.setTexture(&metaFlag);

    // Tworzenie dwóch flag
    EndFlag flag1(sf::Vector2f(17000.0f, 1700.0f), sf::Vector2f(150.0f, 150.0f), metaFlag);
    EndFlag flag2(sf::Vector2f(1700.0f, 4700.0f), sf::Vector2f(150.0f, 150.0f), metaFlag);


   
    sf::RectangleShape coin(sf::Vector2f(64.0f, 64.0f));
    coin.setPosition(600.0f, 200.0f);
    sf::Texture coinTexture;
    coinTexture.loadFromFile("coin_texture.png");
    coin.setTexture(&coinTexture);
    
    Coinanimation coinanimation(&coinTexture, sf::Vector2u(8, 1), 0.3f);

    float deltaTime = 0.0f;
    sf::Clock clock;

    // Flaga stanu kolizji
    bool isCollision = false;


    // ***** Enemy ***** //   

    Enemy enemy1("slime_green.png", 24, 24, 0.1f, 0.2f, player);
    enemy1.setPosition(2200, 2350);
    Enemy enemy2("slime_green.png", 24, 24, 0.1f, 0.2f, player);
    enemy2.setPosition(1850, 2050);
    Enemy enemy3("slime_green.png", 24, 24, 0.1f, 0.2f, player);
    enemy3.setPosition(3150, 2350);
    Enemy enemy4("slime_green.png", 24, 24, 0.1f, 0.2f, player);
    enemy4.setPosition(4450, 2350);
    Enemy enemy5("slime_green.png", 24, 24, 0.1f, 0.2f, player);
    enemy5.setPosition(4900, 2350);
    Enemy enemy6("slime_green.png", 24, 24, 0.1f, 0.2f, player);
    enemy6.setPosition(6600, 2350);
    Enemy enemy7("slime_green.png", 24, 24, 0.1f, 0.2f, player);
    enemy7.setPosition(6300, 2150);
    Enemy enemy8("slime_green.png", 24, 24, 0.1f, 0.2f, player);
    enemy8.setPosition(9650, 1250);
    Enemy enemy9("slime_green.png", 24, 24, 0.1f, 0.2f, player);
    enemy9.setPosition(9800, 1900);
    Enemy enemy10("slime_green.png", 24, 24, 0.1f, 0.2f, player);
    enemy10.setPosition(11150, 2350);
    Enemy enemy11("slime_green.png", 24, 24, 0.1f, 0.2f, player);
    enemy11.setPosition(14650, 2350);

    player.getHitEffect.setVolume(effectsPercentage);
    weapon1.attackSound.setVolume(effectsPercentage);


    
    Shop shop(font);

    //  ******** Glowna petla gry ********  //



    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        enemy1.update(player.GetPosition(), player.IsFacingRight(), player.getSize(), player.damage, 1550, 2350, [&]() { player.bounceLeft(); }, [&]() { player.bounceRight(); });
        enemy2.update(player.GetPosition(), player.IsFacingRight(), player.getSize(), player.damage, 1550, 2350, [&]() { player.bounceLeft(); }, [&]() { player.bounceRight(); });
        enemy3.update(player.GetPosition(), player.IsFacingRight(), player.getSize(), player.damage, 2900, 3250, [&]() { player.bounceLeft(); }, [&]() { player.bounceRight(); });
        enemy4.update(player.GetPosition(), player.IsFacingRight(), player.getSize(), player.damage, 3750, 4450, [&]() { player.bounceLeft(); }, [&]() { player.bounceRight(); });
        enemy5.update(player.GetPosition(), player.IsFacingRight(), player.getSize(), player.damage, 4900, 2350, [&]() { player.bounceLeft(); }, [&]() { player.bounceRight(); });
        enemy6.update(player.GetPosition(), player.IsFacingRight(), player.getSize(), player.damage, 5500, 6650, [&]() { player.bounceLeft(); }, [&]() { player.bounceRight(); });
        enemy7.update(player.GetPosition(), player.IsFacingRight(), player.getSize(), player.damage, 5900, 6400, [&]() { player.bounceLeft(); }, [&]() { player.bounceRight(); });
        enemy8.update(player.GetPosition(), player.IsFacingRight(), player.getSize(), player.damage, 9500, 9900, [&]() { player.bounceLeft(); }, [&]() { player.bounceRight(); });
        enemy9.update(player.GetPosition(), player.IsFacingRight(), player.getSize(), player.damage, 9600, 9850, [&]() { player.bounceLeft(); }, [&]() { player.bounceRight(); });
        enemy10.update(player.GetPosition(), player.IsFacingRight(), player.getSize(), player.damage, 8700, 11300, [&]() { player.bounceLeft(); }, [&]() { player.bounceRight(); });
        enemy11.update(player.GetPosition(), player.IsFacingRight(), player.getSize(), player.damage, 12500, 15000, [&]() { player.bounceLeft(); }, [&]() { player.bounceRight(); });
        
        ui.update(player, view);


        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                view.setSize(evnt.size.width, evnt.size.height);
                view.setCenter(player.GetPosition());
                break;
            }
        }

        shop.update(player.getBody(), player);
        coinanimation.Update(0, deltaTime);
        coinManager.update(deltaTime, player.getBody(), player);
        coin.setTextureRect(coinanimation.uvRect);
        player.Update(deltaTime, blocks);
        view.setCenter(player.GetPosition());
        
        // Sprawdzanie kolizji z flagami
        flag1.checkCollision(player, sf::Vector2f(450.0f, 4750.0f)); // Pozycja dla flagi 1
        flag2.checkCollision(player, sf::Vector2f(1100.0f, 2300.0f)); // Pozycja dla flagi 2

        window.clear();
        window.draw(background_sky);
        window.draw(background_cave);
        window.draw(background_shop);
        
        for (const auto& block : blocks) 
        {
            block.draw(window);
        }

        window.setView(view);
        coinManager.draw(window);
        player.Draw(window);
        ui.draw(window);
        enemy1.draw(window);
        enemy2.draw(window);
        enemy3.draw(window);
        enemy4.draw(window);
        enemy5.draw(window);
        enemy6.draw(window);
        enemy7.draw(window);
        enemy8.draw(window);
        enemy9.draw(window);
        enemy10.draw(window);
        enemy11.draw(window);
        window.draw(meta_flag);
        shop.render(window);
        flag1.render(window);
        flag2.render(window);
        window.draw(coin); //wyœwietlanie coina

        weapon1.Update(0, deltaTime, window, player.GetPosition(), player.IsFacingRight()); // atak
        window.display();
    }

    return 0;
}
