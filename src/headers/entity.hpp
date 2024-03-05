#include <SFML/Graphics.hpp>
#pragma once

class Entity {
protected:
    sf::CircleShape entity;
    sf::Vector2f velocity;
public:
    void setVelocity(const sf::Vector2f);
    void setPosition(const sf::Vector2f);
    void setRadius(const float);

    sf::FloatRect getBounds() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getPosition() const;
    float getRadius() const;

    virtual void draw(sf::RenderWindow&) = 0;
};
