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
                resolveCollision(particles[i], particles[j]);
            }
        }
    }
}

bool CollisionManager::hasCollided(const ball &firstBallState, const ball &secondBallState)
{
    float dx = secondBallState.getState().position.x - firstBallState.getState().position.x;
    float dy = secondBallState.getState().position.y - firstBallState.getState().position.y;
    mDistanceBetweenParticle = std::sqrt(dx * dx + dy * dy);

    if (mDistanceBetweenParticle < (firstBallState.getRadius() + secondBallState.getRadius()))
    {
        return true;
    }

    return false;
}

void CollisionManager::resolveCollision(ball &firstBallPos, ball &secondBallPos)
{
    position2d normal = (secondBallPos.getState().position - firstBallPos.getState().position).normalized();

    float sigmaOverlap = firstBallPos.getRadius() + secondBallPos.getRadius() - mDistanceBetweenParticle;

    if (sigmaOverlap > 0.0f) // Balls are overlapping
    {

        // Compute repulsive force magnitude
        float forceMagnitude = 5.0f * sigmaOverlap; // k * overlap

        // Apply forces to accelerations
        firstBallPos.getState().acceleration.ax -= (forceMagnitude / firstBallPos.getState().mass) * normal.x;
        firstBallPos.getState().acceleration.ay -= (forceMagnitude / firstBallPos.getState().mass) * normal.y;

        secondBallPos.getState().acceleration.ax += (forceMagnitude / secondBallPos.getState().mass) * normal.x;
        secondBallPos.getState().acceleration.ay += (forceMagnitude / secondBallPos.getState().mass) * normal.y;
    }
}
