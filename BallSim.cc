#include "BallSim.hpp"

void ball::update()
{
    updateVelocity2d();
    updatePosition2d();
}

void ball::updatePosition2d()
{
    state_.position.x += state_.velocity.vx * dt;
    state_.position.y += state_.velocity.vy * dt;
}

float ball::getRandomX()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> distrib(20.0f, 800.0f);
    return distrib(gen);
}

void ball::updateVelocity2d()
{
    state_.velocity.vy = state_.velocity.vy + g * dt;
}

void ball::draw(sf::RenderWindow &window)
{
    shape_.setPosition(state_.position.x, state_.position.y);
    window.draw(shape_);
}

float ball::bounce2d()
{
    return -e * state_.velocity.vy;
}

state &ball::getState()
{
    return state_;
}

const float ball::getRadius() const
{
    return radius_;
}

const state &ball::getState() const
{
    return state_;
}
