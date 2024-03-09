#include <SFML/Graphics.hpp>
#pragma once

class Object : public sf::Drawable {
private:
    sf::Vertex *vertices;
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Color color;

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

    void translatePosition();
    void setAllVertexColor();
    void initVertices();
public:
    Object(sf::Vector2f);
    Object(float, float);

    void setPosition(const sf::Vector2f);
    void setPosition(const float, const float);

    void setSize(const sf::Vector2f);
    void setSize(const float, const float);
    
    const sf::Vector2f getPosition() const;

    const sf::Vector2f getSize() const;

    std::vector<sf::Vertex> getAllVertices();

    sf::FloatRect getGlobalBounds();

    void setFillColor(const sf::Color);
};