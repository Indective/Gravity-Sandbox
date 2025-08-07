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

    const float G = 10000.0f;
    const float epsilon = 50.0f;

    void Draw();
    void VerletUpdate(const Vector2 acceleration, float dt);
    Vector2 GetAccelerationFrom(const Body& other);
    int generateRandomMass();
    Color generateRandomColor(const std::vector<Color> colors);
    float computeEnergy();
};
