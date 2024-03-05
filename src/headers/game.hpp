#include <SFML/Graphics.hpp>
#pragma once

class Game {
public:
    static float frictionFactor;
    static float globalEntitySpeed;

    static sf::Vector2f normalize(sf::Vector2f);
};