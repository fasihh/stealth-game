#include <iostream>
#include "headers/object.hpp"

Object::Object(sf::Vector2f size) : size(size), position(0.f, 0.f), vertices(new sf::Vertex[5]), color(sf::Color::White) {
    this->initVertices();
}
Object::Object(float x, float y) : size(x, y), position(0.f, 0.f), vertices(new sf::Vertex[5]), color(sf::Color::White) {
    this->initVertices();
}

void Object::translatePosition() {
    vertices[0].position = position;
    vertices[1].position = position + sf::Vector2f{ size.x, 0.f };
    vertices[2].position = position + size;
    vertices[3].position = position + sf::Vector2f{ 0.f, size.y };
    vertices[4].position = position;
}

void Object::setAllVertexColor() {
    for (int i = 0; i < 5; i++)
        vertices[i].color = color;
}

void Object::initVertices() {
    this->translatePosition();
    this->setAllVertexColor();
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(vertices, 5, sf::TriangleFan, states);
}

void Object::setPosition(const sf::Vector2f position) {
    this->position = position;
    this->translatePosition();
}
void Object::setPosition(const float x, const float y) {
    position.x = x, position.y = y;
    this->translatePosition();
}

void Object::setSize(const sf::Vector2f size) {
    this->size = position;
    this->translatePosition();
}
void Object::setSize(const float x, const float y) {
    size.x = x, size.y = y;
    this->translatePosition();
}

void Object::setFillColor(const sf::Color color) {
    this->color = color;
    this->setAllVertexColor();
}

const sf::Vector2f Object::getPosition() const {
    return position;
}

const sf::Vector2f Object::getSize() const {
    return size;
}

std::vector<sf::Vertex> Object::getAllVertices() {
    std::vector<sf::Vertex> vect_vertices;
    for (int i = 0; i < 4; i++)
        vect_vertices.push_back(this->vertices[i]);
    return vect_vertices;
}

sf::FloatRect Object::getGlobalBounds() {
    sf::FloatRect bounds;

    bounds.left = position.x;
    bounds.top = position.y;
    bounds.width = size.x;
    bounds.height = size.y;

    return bounds;
}