#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include "state.hpp"

constexpr int8_t px_per_meter = 100;
constexpr float g = 9.81f * px_per_meter; // 981 px per s^2
constexpr float dt = 0.016f;              // Time step (s) for 60FPS
constexpr float e = 1.0f;                 // elasticity [0, 1] where 0(no bounce) and 1(perfect bounce)
constexpr float ball_radius = 20.0f;

class ball
{
public:
    ball(const velocity2d &vel = velocity2d{0.0f, 0.0f}, float radius = ball_radius)
        : state_({getRandomX(), 0.0f}, vel), radius_{radius}
    {
        shape_.setRadius(radius_);
        shape_.setFillColor(sf::Color::Red);
        shape_.setOrigin(radius_, radius_);
        shape_.setPosition(state_.position.x, state_.position.y);
    }

    void draw(sf::RenderWindow &window) const;
    void update();
    state getState() const;

private:
    void updatePosition2d();
    void updateVelocity2d();
    float bounce2d();
    static float getRandomX();

    state state_;
    const float radius_;
    sf::CircleShape shape_;
};