#include "raylib.h"
#include "raymath.h"
#include "Body.hpp"
#include <vector>
#include <iostream>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Niggas in paris");

    Vector2 spawnpos = {0};
    Vector2 endpos = {0};
    float velocityfactor = 0.1f;
    bool gotmousepos = false;

    std::vector<Body> bodies;

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            spawnpos = GetMousePosition();
            gotmousepos = true;
        }

        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && gotmousepos) {
            endpos = GetMousePosition();
            DrawLineV(spawnpos, endpos, BLACK);
        }

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && gotmousepos) {
            gotmousepos = false;
            Vector2 dragvector = Vector2Subtract(endpos, spawnpos);
            Vector2 initialVelocity = Vector2Scale(dragvector, velocityfactor);

            // Spawn a new body with position and velocity
            Body newBody;
            newBody.position = spawnpos;
            newBody.velocity = initialVelocity;
            std::cout << "init vel : " << initialVelocity.x << " " << initialVelocity.y << std::endl;
            newBody.color = MAROON;
            newBody.radius = 50.0f;
            bodies.push_back(newBody);
        }

        // Update and draw all bodies
        if(bodies.size() > 2)
        {
            for(int i = 0; i < bodies.size() - 1; i++)
            {
                Body &bodyA = bodies.at(i);
                Body &bodyB = bodies.at(i + 1);
                Vector2 acc = bodyA.GetAccelerationFrom(bodyB);
                bodyA.velocity = Vector2Add(bodyA.velocity, acc);
                std::cout << "body a velocity : " << bodyA.velocity.x << " " << bodyA.velocity.y << std::endl;
            }
        }

        for(auto& b : bodies) 
        {
            b.Update();
            b.Draw();
        }


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
