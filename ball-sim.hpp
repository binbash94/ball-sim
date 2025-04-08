#include <iostream>
#include "state.hpp"

constexpr int8_t px_per_meter = 100;
constexpr float g = 9.81f * px_per_meter; // 981 px per s^2
constexpr float dt = 0.016f;              // Time step (s) for 60FPS
constexpr float e = 1.0f;                 // elasticity [0, 1] where 0(no bounce) and 1(perfect bounce)

class ball
{
public:
    ball(const position2d &pos, const velocity2d &vel)
        : state_(pos, vel) {}

    void update();
    state getState() const;

private:
    void updatePosition2d();
    void updateVelocity2d();
    float bounce2d();

    state state_;
};