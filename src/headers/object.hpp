#include <SFML/Graphics.hpp>
#pragma once

class Object : public sf::Drawable {
private:
    sf::VertexArray vertices;
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Color color;

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

    void initVertices();
public:
    Object(sf::Vector2f);
    Object(float, float);

    void setPosition(const sf::Vector2f);
    void setPosition(const float, const float);

    void setColor(const sf::Color);
};