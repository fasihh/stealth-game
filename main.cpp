#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "player.hpp"
#include "enemy.hpp"

sf::RenderWindow window(sf::VideoMode(800, 600), "SFML", sf::Style::Default, sf::ContextSettings(0, 0, 8));

int main() {
    window.setFramerateLimit(60);

    Player player(
        20.f,
        sf::Color::Green
    );
    player.setPosition({ 400 - player.getRadius(), 300 - player.getRadius() });

    Enemy enemy(
        20.f,
        sf::Color::Blue,
        80.f,
        sf::Color::White
    );
    enemy.setPosition({ 200 - enemy.getRadius(), 150 - enemy.getRadius() });
    enemy.setTarget(&player);

    sf::Font font;
    font.loadFromFile("Roboto-Bold.ttf");

    sf::Text vx("vx: ", font, 25), vy("vy: ", font, 25);
    vy.setPosition(sf::Vector2f{ 5.f, 2.f });
    vx.setPosition(sf::Vector2f{ 5.f, 30.f });

    int keyTime = 6;
    const float frictionFactor = 0.9f;
    
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float velx = player.getVelocity().x, vely = player.getVelocity().y;
        vx.setString("vx: " + std::to_string(velx).substr(0, velx < 0 ? 4 : 3));
        vy.setString("vy: " + std::to_string(vely).substr(0, vely < 0 ? 4 : 3));

        window.clear();

        enemy.draw(window);
        player.draw(window);
        
        window.draw(vx);
        window.draw(vy);

        window.display();
    }

    return 0;
}

