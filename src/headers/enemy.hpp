#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "player.hpp"

class Enemy : public Entity {
private:
    sf::CircleShape detection;
    Player *target;

    void movement();
public:
    Enemy(float, sf::Color, float, sf::Color);

    void setTarget(Player *);

    bool checkDetection();

    void draw(sf::RenderWindow&);
};