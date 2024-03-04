#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "game.hpp"

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

    if (keys[0] && keys[1])
        velocity.x = -diagonalSpeed, velocity.y = -diagonalSpeed;
    else if (keys[0] && keys[3])
        velocity.x = diagonalSpeed, velocity.y = -diagonalSpeed;
    else if (keys[2] && keys[1])
        velocity.x = -diagonalSpeed, velocity.y = diagonalSpeed;
    else if (keys[2] && keys[3])
        velocity.x = diagonalSpeed, velocity.y = diagonalSpeed;
    else if (keys[0])
        velocity.y = -Game::globalEntitySpeed;
    else if (keys[1])
        velocity.x = -Game::globalEntitySpeed;
    else if (keys[2])
        velocity.y = Game::globalEntitySpeed;
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

void Player::draw(sf::RenderWindow& window) {
    velocity.x *= Game::frictionFactor, velocity.y *= Game::frictionFactor;

    this->movement();
    entity.setPosition(entity.getPosition() + velocity);

    window.draw(entity);
}