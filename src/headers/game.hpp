#include <SFML/Graphics.hpp>
#pragma once

class Game {
private:
    static float q_rsqrt(float);
public:
    static float frictionFactor;
    static float globalEntitySpeed;

    static sf::Vector2f normalize(sf::Vector2f);
};