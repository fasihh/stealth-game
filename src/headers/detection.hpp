#include <SFML/Graphics.hpp>
#include "player.hpp"
#pragma once

class Detection {
private:
    sf::CircleShape detection;
public:
    Detection(float, sf::Color);

    void setPosition(const sf::Vector2f);
    
    sf::Vector2f getPosition() const;
    float getRadius() const;

    bool intersects(sf::FloatRect);

    void draw();
};