#include <SFML/Graphics.hpp>
#include "object.hpp"
#pragma once

class Entity {
protected:
    sf::CircleShape entity;
    sf::Vector2f velocity;

    virtual void resolveObjectCollision(Object) = 0;
public:
    void setVelocity(const sf::Vector2f);
    void setPosition(const sf::Vector2f);
    void setRadius(const float);

    sf::FloatRect getBounds() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getPosition() const;
    float getRadius() const;

    void resolveBorderCollision();
    virtual void update(Object) = 0;
    virtual void draw() = 0;
};
