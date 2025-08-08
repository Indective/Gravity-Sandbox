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

Color Body::generateRandomColor(const std::vector<Color> &colors)
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

bool Body::collisionDetect(const Body &BodyB)
{
    float dist = Vector2Distance(BodyB.position, position);
    return dist < BodyB.radius + radius;
}

void Body::mergeBodies(Body &BodyB, std::vector<Body> &bodies, const std::vector<Color> &colors, const int bodyBindex, const int bodyAindex)
{
    //calculate merged velocity
    Vector2 vel = Vector2Add(Vector2Scale(velocity ,mass), Vector2Scale(BodyB.velocity, BodyB.mass));
    float combinedMass = mass + BodyB.mass;
    Vector2 mergedVelocity = Vector2Scale(vel, 1.0f / mass);
    std::cout << "merged velocity : " << mergedVelocity.x << " " << mergedVelocity.y << std::endl;
    std::cout << "body velocity : " << velocity.x << " " << velocity.y << std::endl;

    //calculate merged position
    Vector2 pos = Vector2Add(Vector2Scale(position ,mass), Vector2Scale(BodyB.position, BodyB.mass));
    Vector2 mergedPosition = Vector2Scale(pos, 1.0f / combinedMass);
    std::cout << "position : " << mergedPosition.x << " " << mergedPosition.y << std::endl;
    std::cout << "body position : " << position.x << " "  << position.y << std::endl;


    Body newBody;
    newBody.mass = BodyB.mass + mass;
    newBody.radius = radius + BodyB.radius / 2; 
    newBody.position = position;
    newBody.color = MAROON;
    newBody.velocity = mergedVelocity;
    newBody.prevPosition = prevPosition;

    bodies.push_back(newBody);
    newBody.Draw();
    if (bodyAindex > bodyBindex) {
        bodies.erase(bodies.begin() + bodyAindex);
        bodies.erase(bodies.begin() + bodyBindex);
    } else {
        bodies.erase(bodies.begin() + bodyBindex);
        bodies.erase(bodies.begin() + bodyAindex);
    }

}
