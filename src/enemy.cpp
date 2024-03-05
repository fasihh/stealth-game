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

void Enemy::resolveObjectCollision(Object object) {
    sf::FloatRect enemyBounds = entity.getGlobalBounds();
    sf::FloatRect objectBounds = object.getBounds();

    nextPosition = enemyBounds;
    nextPosition.left += velocity.x;
    nextPosition.top += velocity.y;

    if (!objectBounds.intersects(nextPosition)) return;

    sf::Vector2f entityPos = entity.getPosition();

    // left collision
    if (
        enemyBounds.left < objectBounds.left &&
        enemyBounds.left + enemyBounds.width < objectBounds.left + objectBounds.width &&
        enemyBounds.top < objectBounds.top + objectBounds.height &&
        objectBounds.top < enemyBounds.height + enemyBounds.top
    ) {
        velocity.x = 0.f;
        entity.setPosition(objectBounds.left - enemyBounds.width, enemyBounds.top);
    }
    // right collision
    else if (
        enemyBounds.left > objectBounds.left &&
        enemyBounds.left + enemyBounds.width > objectBounds.left + objectBounds.width &&
        enemyBounds.top < objectBounds.top + objectBounds.height &&
        objectBounds.top < enemyBounds.height + enemyBounds.top
    ) {
        velocity.x = 0.f;
        entity.setPosition(objectBounds.left + objectBounds.width, enemyBounds.top);
    }
    // top collision
    else if (
        enemyBounds.top > objectBounds.top &&
        enemyBounds.top + enemyBounds.height > objectBounds.top + objectBounds.height &&
        enemyBounds.left < objectBounds.left + objectBounds.width &&
        objectBounds.left < enemyBounds.width + enemyBounds.left
    ) {
        velocity.y = 0.f;
        entity.setPosition(enemyBounds.left, objectBounds.top + objectBounds.height);
    }
    // bottom collision
    else if (
        enemyBounds.top < objectBounds.top &&
        enemyBounds.top + enemyBounds.height < objectBounds.top + objectBounds.height &&
        enemyBounds.left < objectBounds.left + objectBounds.width &&
        objectBounds.left < enemyBounds.width + enemyBounds.left
    ) {
        velocity.y = 0.f;
        entity.setPosition(enemyBounds.left, objectBounds.top - enemyBounds.height);
    }
}

void Enemy::update(Object object) {
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
    this->resolveObjectCollision(object);
    entity.setPosition(entity.getPosition() + velocity);
}

void Enemy::draw(sf::RenderWindow& window) {
    detection.draw(window);
    window.draw(entity);
}