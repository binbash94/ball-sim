#include "CollisionManager.hpp"

void CollisionManager::handleWallCollisions(ball &particleState)
{
    if (particleState.getState().position.y + particleState.getRadius() > BOTTOM_WALL_BOUNDS)
    {
        particleState.getState().position.y = BOTTOM_WALL_BOUNDS - particleState.getRadius();
        particleState.getState().velocity.vy = -RESTITUTION * particleState.getState().velocity.vy;
    }

    if (particleState.getState().position.y - particleState.getRadius() < TOP_WALL_BOUNDS)
    {
        particleState.getState().position.y = TOP_WALL_BOUNDS + particleState.getRadius();
        particleState.getState().velocity.vy = -RESTITUTION * particleState.getState().velocity.vy;
    }

    if (particleState.getState().position.x + particleState.getRadius() > RIGHT_WALL_BOUNDS)
    {
        particleState.getState().position.x = RIGHT_WALL_BOUNDS - particleState.getRadius();
        particleState.getState().velocity.vx = -RESTITUTION * particleState.getState().velocity.vx;
    }

    if (particleState.getState().position.x - particleState.getRadius() < LEFT_WALL_BOUNDS)
    {
        particleState.getState().position.x = LEFT_WALL_BOUNDS + particleState.getRadius();
        particleState.getState().velocity.vx = -RESTITUTION * particleState.getState().velocity.vx;
    }
}