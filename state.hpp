#pragma once

#include <cmath>

struct acceleration2d
{
    float ax, ay;

    acceleration2d(float ax = 0.0f, float ay = 9.81f * 100.0f) : ax{ax}, ay{ay} {};
};

struct position2d
{
    float x, y;

    position2d(float x_val = 0.0f, float y_val = 0.0f)
        : x(x_val), y(y_val) {}

    position2d operator-(const position2d &other)
    {
        return {x - other.x, y - other.y};
    }

    position2d normalized() const
    {
        float len = sqrt(x * x + y * y);
        return (len != 0) ? position2d{x / len, y / len} : position2d{};
    }
};

struct velocity2d
{
    float vx, vy;

    velocity2d(float vx_val = 0.0f, float vy_val = 0.0f)
        : vx(vx_val), vy(vy_val) {}
};

struct state
{
    position2d position;
    velocity2d velocity;
    acceleration2d acceleration;
    bool hasReachedFloor{false};
    uint8_t mass{10};

    state(const position2d &p, const velocity2d &v, const acceleration2d &a, uint8_t m = 10)
        : position(p), velocity(v), acceleration{a}, mass(m) {}
};
