#include "Body.hpp"
#include "raymath.h"
#include <random>
#include <iostream>

void Body::Draw()
{
    DrawCircleV(position, radius, color);
}

void Body::VerletUpdate(const Vector2 acceleration, float dt)
{
    Vector2 temp = position; //xn
    Vector2 delta = Vector2Subtract(position, prevPosition);
    Vector2 accelTerm = Vector2Scale(acceleration, dt * dt);
    position = Vector2Add(Vector2Add(position, delta), accelTerm);
    prevPosition = temp;
}

Vector2 Body::GetAccelerationFrom(const Body& bodyB)
{
    Vector2 dir = Vector2Subtract(bodyB.position, position);
    float r2 = Vector2LengthSqr(dir) + epsilon * epsilon;
    Vector2 dirNorm = Vector2Normalize(dir);
    float forceMag = (G * bodyB.mass) / r2;
    return Vector2Scale(dirNorm, forceMag);
}

int Body::generateRandomMass()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(20, 600);
    return distrib(gen);
}

Color Body::generateRandomColor(const std::vector<Color> colors)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, colors.size() - 1);
    return colors.at(distrib(gen));
}

float Body::computeEnergy()
{
    return 0.5f * mass * Vector2LengthSqr(velocity);
}
