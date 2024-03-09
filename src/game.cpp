#include <SFML/Graphics.hpp>
#include "headers/game.hpp"

float q_rsqrt(float number) {
    if (!number) return 1.f;

    float x2 = number * 0.5F;
    float y = number;
    long i = *(long *)&y;
    i = 0x5f3759df - ( i >> 1 );
    y = *(float *) &i;
    y *= ( 1.5f - ( x2 * y * y ) );

    return y;
}

float Game::frictionFactor = 0.85f;
float Game::globalEntitySpeed = 4.0f;

sf::Vector2f Game::normalize(sf::Vector2f vect) {
    float invMag = q_rsqrt(vect.x*vect.x + vect.y*vect.y);
    
    return sf::Vector2f{ vect.x*invMag, vect.y*invMag };
}
