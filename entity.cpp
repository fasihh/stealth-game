#include <SFML/Graphics.hpp>
#include "entity.hpp"

void Entity::setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }
void Entity::setPosition(sf::Vector2f position) { entity.setPosition(position); }
void Entity::setRadius(float radius) { entity.setRadius(radius); }

sf::FloatRect Entity::getBounds() const { return entity.getGlobalBounds(); }
sf::Vector2f Entity::getVelocity() const { return velocity; }
sf::Vector2f Entity::getPosition() const { return entity.getPosition(); }
float Entity::getRadius() const { return entity.getRadius(); }