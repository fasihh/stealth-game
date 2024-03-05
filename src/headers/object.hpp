#include <SFML/Graphics.hpp>
#pragma once

class Object {
private:
    sf::RectangleShape object;
public:
    Object(sf::Vector2f);

    void setColor(const sf::Color);
    void setSize(const sf::Vector2f);
    void setPosition(const sf::Vector2f);

    sf::FloatRect getBounds() const;

    void draw(sf::RenderWindow&);
};