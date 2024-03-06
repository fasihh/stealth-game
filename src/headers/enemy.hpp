#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "detection.hpp"
#include "player.hpp"
#include "object.hpp"
#pragma once

class Enemy : public Entity {
protected:
    void resolveObjectCollision(Object);
private:
    Detection detection;
    Player *target;
    sf::FloatRect nextPosition;

    void movement();
public:
    Enemy(float, sf::Color, float, sf::Color);

    void setTarget(Player *);
    
    void update(Object);
    void draw();
};