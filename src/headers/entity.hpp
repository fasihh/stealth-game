#pragma once
#include <SFML/Graphics.hpp>
#include "object.hpp"

class Entity {
protected:
    sf::CircleShape entity;
    sf::Vector2f velocity;

    virtual void resolveObjectCollision() = 0;
public:
    void setVelocity(const sf::Vector2f);
    void setPosition(const sf::Vector2f);
    void setRadius(const float);

    sf::FloatRect getBounds() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getPosition() const;
    float getRadius() const;

    virtual void update() = 0;
    virtual void draw(sf::RenderWindow&) = 0;
};
