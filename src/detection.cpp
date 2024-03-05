#include "headers/detection.hpp"

Detection::Detection(
    float radius,
    sf::Color color
) {
    detection.setRadius(radius);
    detection.setFillColor(color);
}

void Detection::setPosition(const sf::Vector2f position) { detection.setPosition(position); }

sf::Vector2f Detection::getPosition() const { return detection.getPosition(); }
float Detection::getRadius() const { return detection.getRadius(); }

bool Detection::intersects(sf::FloatRect target) {
    return detection.getGlobalBounds().intersects(target);
}

void Detection::draw(sf::RenderWindow& window) {
    window.draw(detection);
}