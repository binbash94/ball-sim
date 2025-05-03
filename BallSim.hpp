#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include "state.hpp"

constexpr int8_t px_per_meter = 100;
constexpr float g = 9.81f * px_per_meter; // 981 px per s^2
constexpr float dt = 0.016f;              // Time step (s) for 60FPS
constexpr float e = 1.0f;                 // elasticity [0, 1] where 0(no bounce) and 1(perfect bounce)

class ball
{
public:
    ball()
        : state_(
              position2d{static_cast<float>(rand() % 600 + 100), static_cast<float>(rand() % 800 + 100)},
              velocity2d{50.0f, 0.0f},
              acceleration2d{0.0f, 0.0f},
              10 // mass
          )
    {

        shape_.setRadius(radius_);
        shape_.setFillColor(getRandomColor());
        shape_.setOrigin(radius_, radius_);
        shape_.setPosition(state_.position.x, state_.position.y);
    }

    void update();
    void draw(sf::RenderWindow &window);
    state &getState();
    const state &getState() const;
    const float getRadius() const;
    void updateAccel2d();
    void updatePosition2d();
    void updateVelocity2d();

private:
    float bounce2d();
    static float getRandomX();
    static sf::Color getRandomColor()
    {
        static std::vector<sf::Color> colors = {
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Blue,
            sf::Color::Yellow,
            sf::Color::Cyan,
            sf::Color::Magenta};

        return colors[rand() % colors.size()];
    }

    state state_;
    const float radius_{4.0f};
    sf::CircleShape shape_;
};
