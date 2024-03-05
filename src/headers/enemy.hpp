#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "detection.hpp"
#include "player.hpp"

class Enemy : public Entity {
private:
    Detection detection;
    Player *target;

    void movement();
public:
    Enemy(float, sf::Color, float, sf::Color);

    void setTarget(Player *);

    void draw(sf::RenderWindow&);
};