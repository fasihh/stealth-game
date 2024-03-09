#include <SFML/Graphics.hpp>
#include "headers/game.hpp"
#include "headers/enemy.hpp"
#include "headers/player.hpp"
#include "headers/object.hpp"

void Enemy::movement() { /* TODO */ }

Enemy::Enemy(
    float radius = 0.f,
    sf::Color color = sf::Color::Red,
    float detectionRadius = 0.f,
    sf::Color detectionColor = sf::Color::White
) : detection(detectionRadius, detectionColor), target(nullptr) {
    velocity = sf::Vector2f(0.f, 0.f);
    entity.setRadius(radius);
    entity.setFillColor(color);
}

void Enemy::setTarget(Player *target) { this->target = target; }

void Enemy::update() {
    velocity.x *= Game::frictionFactor, velocity.y *= Game::frictionFactor;

    float detectionRadius = detection.getRadius(), radius = entity.getRadius();
    detection.setPosition(
        entity.getPosition() - sf::Vector2f{ detectionRadius - radius, detectionRadius - radius }
    );

    if (detection.intersects(target->getBounds())) {
        sf::Vector2f direction = Game::normalize(target->getPosition() - entity.getPosition());

        if (!entity.getGlobalBounds().intersects(target->getBounds()))
            velocity = direction * Game::globalEntitySpeed * 0.6f;
    }
    entity.setPosition(entity.getPosition() + velocity);
}

void Enemy::draw(sf::RenderWindow& window) {
    // detection.draw(window);
    window.draw(entity);
}