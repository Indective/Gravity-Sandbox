#include "raylib.h"
#include "raymath.h"
#include "Body.hpp"
#include <vector>
#include <iostream>

int main()
{
    const int screenWidth = 1500;
    const int screenHeight = 750;
    InitWindow(screenWidth, screenHeight, "Simulator");

    Vector2 spawnpos = {0};
    Vector2 endpos = {0};
    float velocityfactor = 0.1f;
    bool gotmousepos = false;

    std::vector<Body> bodies;
    std::vector<Color> colors = {BLUE,RED,PURPLE,GREEN,YELLOW,PINK};

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
            newBody.color = newBody.generateRandomColor(colors);
            newBody.radius = 50;
            newBody.mass = newBody.generateRandomMass();
            bodies.push_back(newBody);
            std::cout << newBody.mass << std::endl;
        }

        // Update and draw all bodies
        if(bodies.size() >= 2)
        {
            for (int i = 0; i < bodies.size(); i++) 
            {
                for (int j = 0; j < bodies.size(); j++) 
                {
                    if (i == j) continue; // skip self
                    Vector2 acc = bodies[i].GetAccelerationFrom(bodies[j]);
                    bodies[i].velocity = Vector2Add(bodies[i].velocity, acc);
                }
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
