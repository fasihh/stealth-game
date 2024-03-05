#include <SFML/Graphics.hpp>
#include "headers/player.hpp"
#include "headers/game.hpp"
#include "headers/object.hpp"

void Player::movement() {
    if ((velocity.x > -0.1f && velocity.x < 0.f))
        velocity.x = 0.f;
    if ((velocity.y > -0.1f && velocity.y < 0.f))
        velocity.y = 0.f;

    bool keys[4] = {
        sf::Keyboard::isKeyPressed(sf::Keyboard::W),
        sf::Keyboard::isKeyPressed(sf::Keyboard::A),
        sf::Keyboard::isKeyPressed(sf::Keyboard::S),
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)
    };

    float diagonalSpeed = 70*Game::globalEntitySpeed / 99;

    // up-left
    if (keys[0] && keys[1])
        velocity.x = -diagonalSpeed, velocity.y = -diagonalSpeed;
    // up-right
    else if (keys[0] && keys[3])
        velocity.x = diagonalSpeed, velocity.y = -diagonalSpeed;
    // down-left
    else if (keys[2] && keys[1])
        velocity.x = -diagonalSpeed, velocity.y = diagonalSpeed;
    // down-right
    else if (keys[2] && keys[3])
        velocity.x = diagonalSpeed, velocity.y = diagonalSpeed;
    // up
    else if (keys[0])
        velocity.y = -Game::globalEntitySpeed;
    // left
    else if (keys[1])
        velocity.x = -Game::globalEntitySpeed;
    // down
    else if (keys[2])
        velocity.y = Game::globalEntitySpeed;
    // right
    else if (keys[3])
        velocity.x = Game::globalEntitySpeed;
}

Player::Player(
    float radius = 0.f,
    sf::Color color = sf::Color::Green
) {
    velocity = sf::Vector2f(0.f, 0.f);
    entity.setRadius(radius);
    entity.setFillColor(color);
}

void Player::resolveObjectCollision(Object object) {
    sf::FloatRect playerBounds = entity.getGlobalBounds();
    sf::FloatRect objectBounds = object.getBounds();

    nextPosition = playerBounds;
    nextPosition.left += velocity.x;
    nextPosition.top += velocity.y;

    if (!objectBounds.intersects(nextPosition)) return;

    sf::Vector2f entityPos = entity.getPosition();

    // left collision
    if (
        playerBounds.left < objectBounds.left &&
        playerBounds.left + playerBounds.width < objectBounds.left + objectBounds.width &&
        playerBounds.top < objectBounds.top + objectBounds.height &&
        objectBounds.top < playerBounds.height + playerBounds.top
    ) {
        velocity.x = 0.f;
        entity.setPosition(objectBounds.left - playerBounds.width, playerBounds.top);
    }
    // right collision
    else if (
        playerBounds.left > objectBounds.left &&
        playerBounds.left + playerBounds.width > objectBounds.left + objectBounds.width &&
        playerBounds.top < objectBounds.top + objectBounds.height &&
        objectBounds.top < playerBounds.height + playerBounds.top
    ) {
        velocity.x = 0.f;
        entity.setPosition(objectBounds.left + objectBounds.width, playerBounds.top);
    }
    // top collision
    else if (
        playerBounds.top > objectBounds.top &&
        playerBounds.top + playerBounds.height > objectBounds.top + objectBounds.height &&
        playerBounds.left < objectBounds.left + objectBounds.width &&
        objectBounds.left < playerBounds.width + playerBounds.left
    ) {
        velocity.y = 0.f;
        entity.setPosition(playerBounds.left, objectBounds.top + objectBounds.height);
    }
    // bottom collision
    else if (
        playerBounds.top < objectBounds.top &&
        playerBounds.top + playerBounds.height < objectBounds.top + objectBounds.height &&
        playerBounds.left < objectBounds.left + objectBounds.width &&
        objectBounds.left < playerBounds.width + playerBounds.left
    ) {
        velocity.y = 0.f;
        entity.setPosition(playerBounds.left, objectBounds.top - playerBounds.height);
    }
}

void Player::update(Object object) {
    velocity.x *= Game::frictionFactor, velocity.y *= Game::frictionFactor;

    this->movement();
    this->resolveObjectCollision(object);
    entity.setPosition(entity.getPosition() + velocity);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(entity);
}