#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.hpp"
#include "enemy.hpp"
#include "player.hpp"

void Enemy::movement() {

}

Enemy::Enemy(
    float radius = 0.f,
    sf::Color color = sf::Color::Red,
    float detectionRadius = 0.f,
    sf::Color detectionColor = sf::Color::White
) : detection(detectionRadius), target(nullptr) {
    velocity = sf::Vector2f(0.f, 0.f);
    entity.setRadius(radius);
    entity.setFillColor(color);
    detection.setFillColor(detectionColor);
}

void Enemy::setTarget(Player *target) { this->target = target; }

bool Enemy::checkDetection() {
    sf::FloatRect detectionBounds = detection.getGlobalBounds();

    return detectionBounds.intersects(target->getBounds());
}

void Enemy::draw(sf::RenderWindow& window) {
    velocity.x *= Game::frictionFactor, velocity.y *= Game::frictionFactor;

    float detectionRadius = detection.getRadius(), radius = entity.getRadius();
    detection.setPosition(
        entity.getPosition() - sf::Vector2f{ detectionRadius - radius, detectionRadius - radius }
    );

    if (checkDetection()) {
        sf::Vector2f direction = Game::normalize(target->getPosition() - entity.getPosition());

        if (!entity.getGlobalBounds().intersects(target->getBounds()))
            velocity = direction * Game::globalEntitySpeed * 0.6f;
    }
    entity.setPosition(entity.getPosition() + velocity);

    window.draw(detection);
    window.draw(entity);
}