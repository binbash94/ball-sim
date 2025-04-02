#include <iostream>
#include <SFML/Graphics.hpp>

constexpr int8_t px_per_meter = 100;
constexpr float g = 9.81f * px_per_meter; // 981 px per s^2
constexpr float dt = 0.016f;              // Time step (s) for 60FPS
constexpr float e = 1.0f;                 // elasticity [0, 1] where 0(no bounce) and 1(perfect bounce)

struct position2d
{
    float x, y;

    position2d(float x_val = 0.0f, float y_val = 0.0f)
        : x(x_val), y(y_val) {}
};

struct velocity2d
{
    float vx, vy;

    velocity2d(float vx_val = 0.0f, float vy_val = 0.0f)
        : vx(vx_val), vy(vy_val) {}
};

struct state
{
    position2d position;
    velocity2d velocity;
    bool hasReachedFloor{false};

    state(const position2d &p, const velocity2d &v)
        : position(p), velocity(v) {}
};

class ball
{
public:
    ball(const position2d &pos, const velocity2d &vel)
        : state_(pos, vel) {}

    void update()
    {
        updateVelocity2d();
        updatePosition2d();
    }

    state getState() const
    {
        return state_;
    }

private:
    void updatePosition2d()
    {
        state_.position.x += state_.velocity.vx * dt;
        state_.position.y += state_.velocity.vy * dt;

        if (state_.position.y > 600.0f - 20.0f)
        {
            state_.hasReachedFloor = true;
            state_.position.y = 600.0f - 20.0f;
        }
        else
        {
            state_.hasReachedFloor = false;
        }
    }

    void updateVelocity2d()
    {
        state_.velocity.vy = !state_.hasReachedFloor ? state_.velocity.vy + g * dt : bounce2d();
    }

    float bounce2d()
    {
        return -e * state_.velocity.vy;
    }

    state state_;
};

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
