#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"

class Body {
public:
    Vector2 position = {0};
    Vector2 velocity = {0};
    int radius;
    int mass;
    Color color;
    const float G = 100.0f;
    const float epsilon = 10.0f;

    void Draw();
    void Update();
    int generateRandomMass();
    float computeEnergy(); 
    Color generateRandomColor(const std::vector<Color> colors);
    Vector2 GetAccelerationFrom(const Body &bodyB);
};