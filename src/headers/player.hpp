#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "object.hpp"
#pragma once

class Player : public Entity {
protected:
    void resolveObjectCollision(std::vector<Object>);
private:
    sf::FloatRect nextPosition;
    void movement();
public:
    Player(float, sf::Color);

    void update(std::vector<Object>);
    void draw(sf::RenderWindow&);
};