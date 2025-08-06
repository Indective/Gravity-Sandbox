#pragma once
#include <iostream>
#include "raylib.h"

class Body {
public:
    Vector2 position = {0};
    Vector2 velocity = {0};
    float radius;
    Color color;

    void Draw();
    void Update();
    Vector2 GetAccelerationFrom(const Body &bodyB);
};