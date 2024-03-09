#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "src/headers/player.hpp"
#include "src/headers/enemy.hpp"
#include "src/headers/object.hpp"
#include "src/headers/game.hpp"

sf::RenderWindow window(sf::VideoMode(800, 600), "SFML", sf::Style::Default, sf::ContextSettings(0, 0, 8));


int main() {
    window.setFramerateLimit(60);
    Game::setWindowInstance(window);

    Object object(200.f, 200.f);
    object.setPosition(window.getSize().x/2 - object.getSize().x/2, window.getSize().y/2 - object.getSize().y/2);
    object.setFillColor(sf::Color::Red);

    Game::objects.push_back(object);

    Player player(
        20.f,
        sf::Color::Green
    );
    player.setPosition({ 700, 500 });

    Enemy enemy(
        20.f,
        sf::Color::Blue,
        80.f,
        sf::Color::White
    );
    enemy.setPosition({ 200 - enemy.getRadius(), 150 - enemy.getRadius() });
    enemy.setTarget(&player);

    sf::Font font;
    font.loadFromFile("resources/Roboto-Bold.ttf");

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

        player.update();
        enemy.update();
        
        enemy.draw(window);
        player.draw(window);
        window.draw(vx);
        window.draw(vy);

        for (Object object : Game::objects)
            window.draw(object);

        window.display();
    }

    return 0;
}


