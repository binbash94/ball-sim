struct position2d
{
    float x, y;

    position2d(float x_val = 0.0f, float y_val = 0.0f)
        : x(x_val), y(y_val) {}
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
    bool hasReachedFloor{false};

    state(const position2d &p, const velocity2d &v)
        : position(p), velocity(v) {}
};
