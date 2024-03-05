#include <iostream>
#include "headers/object.hpp"

Object::Object(sf::Vector2f size) : object(size) {}

void Object::setColor(const sf::Color color) { object.setFillColor(color); }
void Object::setSize(const sf::Vector2f size) { object.setSize(size); }
void Object::setPosition(const sf::Vector2f position) { object.setPosition(position); }

sf::FloatRect Object::getBounds() const { return object.getGlobalBounds(); }

void Object::draw(sf::RenderWindow& window) {
    window.draw(object);
}