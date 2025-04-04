#include <SFML/Graphics.hpp>
#include "ball-sim.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncing Ball Sim");
    window.setFramerateLimit(60);

    std::vector<ball> particles;

    for (int i = 0; i < 10; i++)
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

        window.clear(sf::Color::White);

        for (int j = 0; j < 10; j++)
        {
            particles[j].update();
            particles[j].draw(window);
        }

        window.display();
    }

    return 0;
}