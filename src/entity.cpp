#include <SFML/Graphics.hpp>
#include "headers/entity.hpp"
#include "headers/game.hpp"

void Entity::setVelocity(const sf::Vector2f velocity) { this->velocity = velocity; }
void Entity::setPosition(const sf::Vector2f position) { entity.setPosition(position); }
void Entity::setRadius(const float radius) { entity.setRadius(radius); }

sf::FloatRect Entity::getBounds() const { return entity.getGlobalBounds(); }
sf::Vector2f Entity::getVelocity() const { return velocity; }
sf::Vector2f Entity::getPosition() const { return entity.getPosition(); }
float Entity::getRadius() const { return entity.getRadius(); }

void Entity::resolveBorderCollision() {
    sf::FloatRect entityBounds = entity.getGlobalBounds();
    sf::Vector2u windowSize = Game::window.getSize();

    if (entityBounds.left < 0.f) {
        entity.setPosition(0.f, entity.getPosition().y);
    }
    if (entityBounds.left + entityBounds.width > windowSize.x) {
        entity.setPosition(windowSize.x - entityBounds.width, entity.getPosition().y);
    }
    if (entityBounds.top < 0.f) {
        entity.setPosition(entity.getPosition().x, 0.f);
    }
    if (entityBounds.top + entityBounds.height > windowSize.y) {
        entity.setPosition(entity.getPosition().x, windowSize.y - entityBounds.height);
    }
}

void Entity::draw() {
    Game::window.draw(entity);
}