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
void CollisionManager::handleBallCollision(std::vector<ball> &particles)
{
    for (int i = 0; i < particles.size(); i++)
    {
        for (int j = i + 1; j < particles.size(); j++)
        {
            if (hasCollided(particles[i], particles[j]))
            {
                // resolveCollision()
            }
        }
    }
}

bool CollisionManager::hasCollided(const ball &firstBallState, const ball &secondBallState)
{
    float xTerm = pow(secondBallState.getState().position.x, 2) - pow(firstBallState.getState().position.x, 2);
    float yTerm = pow(secondBallState.getState().position.y, 2) - pow(firstBallState.getState().position.y, 2);
    float particleDistance_px = sqrt(xTerm + yTerm);

    if (particleDistance_px < (firstBallState.getRadius() + secondBallState.getRadius()))
    {
        return true;
    }

    return false;
}

void CollisionManager::resolveCollision(position2d &firstBallPos, position2d &secondBallPos)
{
    position2d normal = (secondBallPos - firstBallPos).normalized();
}
