#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "src/headers/game.hpp"
#include "src/headers/player.hpp"
#include "src/headers/enemy.hpp"
#include "src/headers/object.hpp"

int main() {
    Game::window.setFramerateLimit(60);

    Object wall(sf::Vector2f{ 100.f, 60.f });
    wall.setColor(sf::Color::Red);
    wall.setPosition({ 300.f, 400.f });

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
    font.loadFromFile("resources/Roboto-Bold.ttf");

    sf::Text vx("vx: ", font, 25), vy("vy: ", font, 25);
    vy.setPosition(sf::Vector2f{ 5.f, 2.f });
    vx.setPosition(sf::Vector2f{ 5.f, 30.f });
    
    while (Game::window.isOpen()) {
        sf::Event event;

        while (Game::window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                Game::window.close();
        }

        float velx = player.getVelocity().x, vely = player.getVelocity().y;
        vx.setString("vx: " + std::to_string(velx).substr(0, velx < 0 ? 4 : 3));
        vy.setString("vy: " + std::to_string(vely).substr(0, vely < 0 ? 4 : 3));

        Game::window.clear();

        player.update(wall);
        enemy.update(wall);
        
        enemy.draw();
        player.draw();
        wall.draw();
        Game::window.draw(vx);
        Game::window.draw(vy);

        Game::window.display();
    }

    return 0;
}


