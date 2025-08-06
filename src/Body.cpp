#include "raylib.h"
#include "raymath.h"
#include "Body.hpp"
#include <iostream>
#include <cmath>
#include <random>

void Body::Draw()
{
    DrawCircleV(position, radius, color);
}

void Body::Update()
{
    position = Vector2Add(position, velocity);
}

int Body::generateRandomRadius()
{
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(10, 180);
    int rand = distrib(gen);

    return rand;
}

Color Body::generateRandomColor(const std::vector<Color> colors)
{
    std::random_device rd_device; 
    std::mt19937 gen(rd_device()); 
    std::cout << colors.size();
    std::uniform_int_distribution<> distrib(1, colors.size() - 1);
    int rand = distrib(gen);

    return colors.at(rand);
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
