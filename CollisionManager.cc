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

void CollisionManager::resolveCollision(ball &firstBallState, ball &secondBallState)
{
    auto &stateA = firstBallState.getState();
    auto &stateB = secondBallState.getState();

    float aMass = 10.0f;
    float bMass = 10.0f;

    position2d delta = stateB.position - stateA.position;
    float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (dist < 0.001f)
    {
        delta = {0.01f, 0.0f};
        dist = 0.01f;
    }

    position2d normal = delta.normalized();

    float rvx = stateB.velocity.vx - stateA.velocity.vx;
    float rvy = stateB.velocity.vy - stateA.velocity.vy;
    float velAlongNormal = rvx * normal.x + rvy * normal.y;

    if (velAlongNormal > 0)
        return; // Balls are moving apart

    float e = 0.8f; // restitution (perfectly elastic)
    float j = -(1 + e) * velAlongNormal;
    j /= (1 / aMass + 1 / bMass);

    float impulseX = j * normal.x;
    float impulseY = j * normal.y;

    stateA.velocity.vx -= impulseX / aMass;
    stateA.velocity.vy -= impulseY / aMass;
    stateB.velocity.vx += impulseX / bMass;
    stateB.velocity.vy += impulseY / bMass;

    // Positional correction to avoid overlap
    float overlap = (firstBallState.getRadius() + secondBallState.getRadius()) - dist;
    if (overlap > 0.0f)
    {
        float percent = 0.2f;
        float correction = overlap * percent;

        position2d correctionVec = {normal.x * correction, normal.y * correction};

        stateA.position.x -= correctionVec.x * (bMass / (aMass + bMass));
        stateA.position.y -= correctionVec.y * (bMass / (aMass + bMass));
        stateB.position.x += correctionVec.x * (aMass / (aMass + bMass));
        stateB.position.y += correctionVec.y * (aMass / (aMass + bMass));
    }
}
