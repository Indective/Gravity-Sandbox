#include "raylib.h"
#include "raymath.h"
#include "Body.hpp"
#include <iostream>
#include <cmath>

void Body::Draw()
{
    DrawCircleV(position, radius, color);
}

void Body::Update()
{
    position = Vector2Add(position, velocity);
}

Vector2 Body::GetAccelerationFrom(const Body &bodyB)
{
    Vector2 dir = Vector2Subtract(bodyB.position, position);
    float r2 = Vector2LengthSqr(dir);
    Vector2 dirNorm = Vector2Normalize(dir);
    float forceMag = (9.8 * radius * bodyB.radius) / r2;
    Vector2 force = Vector2Scale(dirNorm, forceMag);
    Vector2 acceleration = Vector2Scale(force, 1.0f / radius);
    return acceleration;
}
