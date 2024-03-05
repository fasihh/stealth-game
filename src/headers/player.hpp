#include <SFML/Graphics.hpp>
#include "entity.hpp"
#pragma once

class Player : public Entity {
private:
    void movement();
public:
    Player(float, sf::Color);

    void draw(sf::RenderWindow&);
};