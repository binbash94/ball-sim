#include <SFML/Graphics.hpp>
#include "ball-sim.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncing Ball Sim");
    window.setFramerateLimit(60);

    position2d pos(400.0f, 100.0f); // 400px from left, 100px from top (in px)
    velocity2d vel(0.0f, 0.0f);
    ball b(pos, vel);

    sf::CircleShape shape(20.0f); // radius in pixels
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(20.0f, 20.0f); // center origin

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        b.update();

        window.clear(sf::Color::White);

        // Get ball's updated position in pixels
        const state s = b.getState();
        shape.setPosition(s.position.x, s.position.y);

        window.draw(shape);
        window.display();
    }

    return 0;
}