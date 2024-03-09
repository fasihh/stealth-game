#include <iostream>
#include "headers/object.hpp"

Object::Object(sf::Vector2f size) : size(size), position(0.f, 0.f), vertices(sf::LinesStrip, 4), color(sf::Color::White) {
    this->initVertices();
}
Object::Object(float x, float y) : size(x, y), position(0.f, 0.f), vertices(sf::LinesStrip, 4), color(sf::Color::White) {
    this->initVertices();
}

void Object::initVertices() {
    vertices[0].position = position;
    vertices[1].position = position + sf::Vector2f{ size.x, 0.f };
    vertices[2].position = position + size;
    vertices[3].position = position + sf::Vector2f{ 0.f, size.y };
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(vertices, states);
}

void Object::setPosition(const sf::Vector2f position) { this->position = position; }
void Object::setPosition(const float x, const float y) { position.x = x, position.y = y; }

void Object::setColor(const sf::Color color) { this->color = color; }