#include <SFML/Graphics.hpp>
#include "object.hpp"
#pragma once

class Game {
public:
    static float frictionFactor;
    static float globalEntitySpeed;
    static sf::RenderWindow *window;
    static std::vector<Object> objects;

    static sf::Vector2f normalize(sf::Vector2f);
    static void setWindowInstance(sf::RenderWindow&);
};