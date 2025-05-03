#include <SFML/Graphics.hpp>
#include "BallSim.hpp"
#include "CollisionManager.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncing Ball Sim");
    window.setFramerateLimit(60);

    CollisionManager cm;
    std::vector<ball> particles;

    for (int i = 0; i < 1000; i++)
    {
        particles.push_back(ball{});
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // Apply base forces (gravity)
        for (ball &b : particles)
        {
            b.updateAccel2d();
        } // only gravity, no reset after collision

        // Detect and resolve collisions — now this affects velocity properly
        cm.handleBallCollision(particles);

        // Apply velocity and update position
        for (ball &b : particles)
        {
            b.updateVelocity2d();
            b.updatePosition2d();
            cm.handleWallCollisions(b);
        }

        for (int j = 0; j < 1000; j++)
        {
            particles[j].draw(window);
        }

        window.display();
    }

    return 0;
}