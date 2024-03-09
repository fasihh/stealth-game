#include <SFML/Graphics.hpp>
#include <cmath>
#include "headers/game.hpp"
#include "headers/enemy.hpp"
#include "headers/player.hpp"
#include "headers/object.hpp"

Intersection getIntersection(Line ray, Line segment){
    sf::Vector2f rayA = ray.a.position, rayB = ray.b.position;
    sf::Vector2f segmentA = segment.a.position, segmentB = segment.b.position;

	float r_px = rayA.x; // ray x
	float r_py = rayA.y; // ray y
	float r_dx = rayB.x-rayA.x; // direction of ray x
	float r_dy = rayB.y-rayA.y; // direction of ray y

	float s_px = segmentA.x; // segment x
	float s_py = segmentA.y; // segment y
	float s_dx = segmentB.x-segmentA.x; // direction of segment x
	float s_dy = segmentB.y-segmentA.y; // direction of segment y

    // finding unit vector of both ray and segment to check if they are parallel
	float r_mag = std::sqrt(r_dx*r_dx+r_dy*r_dy);
	float s_mag = std::sqrt(s_dx*s_dx+s_dy*s_dy);
    // in case they are, return a false status
	if(r_dx/r_mag==s_dx/s_mag && r_dy/r_mag==s_dy/s_mag)
		return { false };

    // SOLVE FOR T1 & T2
	// r_px+r_dx*T1 = s_px+s_dx*T2 && r_py+r_dy*T1 = s_py+s_dy*T2
	// ==> T1 = (s_px+s_dx*T2-r_px)/r_dx = (s_py+s_dy*T2-r_py)/r_dy
	// ==> s_px*r_dy + s_dx*T2*r_dy - r_px*r_dy = s_py*r_dx + s_dy*T2*r_dx - r_py*r_dx
	// ==> T2 = (r_dx*(s_py-r_py) + r_dy*(r_px-s_px))/(s_dx*r_dy - s_dy*r_dx)
	float T2 = (r_dx*(s_py-r_py) + r_dy*(r_px-s_px))/(s_dx*r_dy - s_dy*r_dx);
	float T1 = (s_px+s_dx*T2-r_px)/r_dx;

    // conditions for intersection
	if(T1<0) return { false };
	if(T2<0 || T2>1) return { false };

    // if all conditions satisfy, return an intersection with true status, point and the value T
	return {
        true,
		r_px+r_dx*T1,
		r_py+r_dy*T1,
		T1
	};
}

Enemy::Enemy(
    float radius = 0.f,
    sf::Color color = sf::Color::Red,
    float detectionRadius = 0.f,
    sf::Color detectionColor = sf::Color::White
) : detection(detectionRadius, detectionColor), target(nullptr) {
    velocity = sf::Vector2f(0.f, 0.f);
    entity.setRadius(radius);
    entity.setFillColor(color);

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(Game::window->getSize());
    lightShader.loadFromFile("resources/light.vert", "resources/light.frag");
    lightShader.setUniform("u_resolution", windowSize);

    lightTexture.create(Game::window->getSize().x, Game::window->getSize().y);
    lightTexture.setSmooth(true);
}

void Enemy::setTarget(Player *target) { this->target = target; }

void Enemy::update() {
    lightTexture.clear();
    lightShader.setUniform("u_mouse", entity.getPosition());

    std::vector<float> angles;
    std::vector<Intersection> intersections;
    velocity.x *= Game::frictionFactor, velocity.y *= Game::frictionFactor;

    for (sf::Vertex vertex : Game::getAllUniquePoints()) {
        float angle = std::atan2(vertex.position.y-entity.getPosition().y, vertex.position.x-entity.getPosition().x);
        angles.push_back(angle-0.0001f);
        angles.push_back(angle);
        angles.push_back(angle+0.0001f);
    }

    for (float angle : angles) {
        float dx = std::cos(angle);
        float dy = std::sin(angle);

        Line ray{ entity.getPosition(), { entity.getPosition().x+dx, entity.getPosition().y+dy } };

        Intersection closest{ false };
        for (Object object : Game::objects) {
            for (Line segment : object.getAllSegments()) {
                Intersection intersect = getIntersection(ray, segment);
                intersect.angle = angle;
                if (!intersect.status) continue;
                if (!closest.status || intersect.T1 < closest.T1)
                    closest = intersect;
            }
            intersections.push_back(closest);
        }
    }
    std::sort(intersections.begin(), intersections.end(), [&](const Intersection& a, const Intersection& b) { return a.angle < b.angle; });
    intersections.emplace_back(intersections[0]);

    std::vector<sf::Vertex> vertices;
    vertices.emplace_back(sf::Vertex(entity.getPosition()));

    for (Intersection intersect : intersections)
        vertices.emplace_back(sf::Vertex(sf::Vector2f{ intersect.x, intersect.y }));
    
    lightTexture.draw(vertices.data(), vertices.size(), sf::TriangleFan);
    lightTexture.display();

    float detectionRadius = detection.getRadius(), radius = entity.getRadius();
    detection.setPosition(
        entity.getPosition() - sf::Vector2f{ detectionRadius - radius, detectionRadius - radius }
    );

    if (detection.intersects(target->getBounds())) {
        sf::Vector2f direction = Game::normalize(target->getPosition() - entity.getPosition());

        if (!entity.getGlobalBounds().intersects(target->getBounds()))
            velocity = direction * Game::globalEntitySpeed * 0.6f;
    }
    this->resolveObjectCollision();
    entity.setPosition(entity.getPosition() + velocity);
}

void Enemy::resolveObjectCollision() {
    for (Object object : Game::objects) {
        sf::FloatRect enemyBounds = entity.getGlobalBounds();
        sf::FloatRect objectBounds = object.getGlobalBounds();

        nextPosition = enemyBounds;
        nextPosition.left += velocity.x;
        nextPosition.top += velocity.y;

        if (!objectBounds.intersects(nextPosition)) return;

        sf::Vector2f entityPos = entity.getPosition();

        // left collision
        if (
            enemyBounds.left < objectBounds.left &&
            enemyBounds.left + enemyBounds.width < objectBounds.left + objectBounds.width &&
            enemyBounds.top < objectBounds.top + objectBounds.height &&
            objectBounds.top < enemyBounds.height + enemyBounds.top
        ) {
            velocity.x = 0.f;
            entity.setPosition(objectBounds.left - enemyBounds.width, enemyBounds.top);
        }
        // right collision
        else if (
            enemyBounds.left > objectBounds.left &&
            enemyBounds.left + enemyBounds.width > objectBounds.left + objectBounds.width &&
            enemyBounds.top < objectBounds.top + objectBounds.height &&
            objectBounds.top < enemyBounds.height + enemyBounds.top
        ) {
            velocity.x = 0.f;
            entity.setPosition(objectBounds.left + objectBounds.width, enemyBounds.top);
        }
        // top collision
        else if (
            enemyBounds.top > objectBounds.top &&
            enemyBounds.top + enemyBounds.height > objectBounds.top + objectBounds.height &&
            enemyBounds.left < objectBounds.left + objectBounds.width &&
            objectBounds.left < enemyBounds.width + enemyBounds.left
        ) {
            velocity.y = 0.f;
            entity.setPosition(enemyBounds.left, objectBounds.top + objectBounds.height);
        }
        // bottom collision
        else if (
            enemyBounds.top < objectBounds.top &&
            enemyBounds.top + enemyBounds.height < objectBounds.top + objectBounds.height &&
            enemyBounds.left < objectBounds.left + objectBounds.width &&
            objectBounds.left < enemyBounds.width + enemyBounds.left
        ) {
            velocity.y = 0.f;
            entity.setPosition(enemyBounds.left, objectBounds.top - enemyBounds.height);
        }
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    // detection.draw(window);
    window.draw(entity);
}