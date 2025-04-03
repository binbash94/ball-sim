#include "ball-sim.hpp"

void ball::update()
{
    updateVelocity2d();
    updatePosition2d();
}

state ball::getState() const
{
    return state_;
}

void ball::updatePosition2d()
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

void ball::updateVelocity2d()
{
    state_.velocity.vy = !state_.hasReachedFloor ? state_.velocity.vy + g * dt : bounce2d();
}

float ball::bounce2d()
{
    return -e * state_.velocity.vy;
}
