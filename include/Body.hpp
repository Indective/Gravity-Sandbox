#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"

class Body {
public:
    Vector2 position = {0};
    Vector2 velocity = {0};
    int radius;
    Color color;
    // const double G = 6.674e-11; (for later use)

    void Draw();
    void Update();
    int generateRandomRadius();
    Color generateRandomColor(const std::vector<Color> colors);
    Vector2 GetAccelerationFrom(const Body &bodyB);
};