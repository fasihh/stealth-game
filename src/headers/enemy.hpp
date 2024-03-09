#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "detection.hpp"
#include "player.hpp"
#include "object.hpp"
#pragma once

class Enemy : public Entity {
protected:
    void resolveObjectCollision();
private:
    Detection detection;
    Player *target;
    sf::FloatRect nextPosition;
    sf::Shader lightShader;
    sf::RenderTexture lightTexture;
public:
    Enemy(float, sf::Color, float, sf::Color);

    void setTarget(Player *);
    
    void update();
    void draw(sf::RenderWindow&);
};