#ifndef KEYUTILS_H
#define KEYUTILS_H

#include <SFML/Window/Keyboard.hpp>
#include <string>

class KeyUtils {
public:
    static std::string KeyToString(sf::Keyboard::Key key);
};

#endif
