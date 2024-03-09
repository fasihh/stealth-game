#pragma once
#include <SFML/Graphics.hpp>

struct Line {
    sf::Vertex a, b;
    Line(sf::Vector2f a, sf::Vector2f b) : a(a), b(b) {}
    Line(sf::Vertex a, sf::Vertex b) : a(a), b(b) {}
};