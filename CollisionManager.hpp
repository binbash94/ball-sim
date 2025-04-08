#pragma once

#include <cmath>

#include "BallSim.hpp"
#include "state.hpp"

class CollisionManager
{
public:
    static constexpr float LEFT_WALL_BOUNDS = 0.0f;
    static constexpr float RIGHT_WALL_BOUNDS = 800.0f;
    static constexpr float TOP_WALL_BOUNDS = 0.0f;
    static constexpr float BOTTOM_WALL_BOUNDS = 600.0f;
    static constexpr float RESTITUTION = 1.0f;

    void handleWallCollisions(ball &particleState);
    void handleBallCollision(std::vector<ball> &particles);

private:
    bool hasCollided(const ball &firstBallState, const ball &secondBallState);
    void resolveCollision(position2d &firstBallPos, position2d &secondBallPos);
};