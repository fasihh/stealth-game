#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "detection.hpp"
#include "player.hpp"
#include "object.hpp"

struct Intersection {
    bool status;
    float x, y;
    float T1;
    float angle;
    Intersection(
        bool s,
        float x = 0,
        float y = 0,
        float T1 = 0.f,
        float a = 0.f
    ) 
    : status(s), x(x), y(y), angle(a), T1(T1) {}
};

class Enemy : public Entity {
protected:
    void resolveObjectCollision();
private:
    Detection detection;
    Player *target;
    sf::FloatRect nextPosition;
public:
    sf::RenderTexture lightTexture;
    sf::Shader lightShader;
    Enemy(float, sf::Color, float, sf::Color);

    void setTarget(Player *);
    
    void update();
    void draw(sf::RenderWindow&);
};