#pragma once

#include "raylib.h"
#include "raymath.h"
#include <vector>

class Body
{
public:
    Vector2 position;
    Vector2 prevPosition;
    Vector2 velocity;
    float mass;
    float radius;
    Color color;
    std::vector<Vector2> positions;

    float G = 10000.0f;
    float epsilon = 50.0f;

    void Draw();
    void VerletUpdate(const Vector2 acceleration, float dt);
    Vector2 GetAccelerationFrom(const Body& BodyB);
    int generateRandomMass();
    Color generateRandomColor(const std::vector<Color> &colors);
    float computeEnergy();
    bool collisionDetect(const Body& BodyB);
    void mergeBodies(Body& BodyB, std::vector<Body> &bodies, const std::vector<Color> &colors, const int bodyBindex, const int bodyAindex);
};
