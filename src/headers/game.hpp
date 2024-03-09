#pragma once
#include <SFML/Graphics.hpp>
#include "object.hpp"

typedef std::vector<sf::Vertex> vertexVector;

class Game {
public:
    static float frictionFactor;
    static float globalEntitySpeed;
    static sf::RenderWindow *window;
    static std::vector<Object> objects;

    static sf::Vector2f normalize(sf::Vector2f);
    static void setWindowInstance(sf::RenderWindow&);
    static vertexVector getAllUniquePoints();
};