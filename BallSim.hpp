#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include "state.hpp"

constexpr int8_t px_per_meter = 100;
constexpr float g = 9.81f * px_per_meter; // 981 px per s^2
constexpr float dt = 0.016f;              // Time step (s) for 60FPS
constexpr float e = 0.8f;                 // elasticity [0, 1] where 0(no bounce) and 1(perfect bounce)

class ball
{
public:
    ball(const velocity2d &vel = velocity2d{10.0f, 0.0f})
        : state_({getRandomX(), 0.0f}, vel, acceleration2d{})
    {
        shape_.setRadius(radius_);
        shape_.setFillColor(sf::Color::Red);
        shape_.setOrigin(radius_, radius_);
        shape_.setPosition(state_.position.x, state_.position.y);
    }

    void update();
    void draw(sf::RenderWindow &window);
    state &getState();
    const state &getState() const;
    const float getRadius() const;

private:
    void updateAccel2d();
    void updatePosition2d();
    void updateVelocity2d();
    float bounce2d();
    static float getRandomX();

    state state_;
    const float radius_{10.0f};
    sf::CircleShape shape_;
};
