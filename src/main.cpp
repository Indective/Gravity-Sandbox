#include "raylib.h"
#include "raymath.h"
#include "Body.hpp"
#include <vector>
#include <iostream>

int main()
{
    const int screenWidth = 2000;
    const int screenHeight = 1250;
    InitWindow(screenWidth, screenHeight, "Simulator");

    Vector2 spawnpos = {0};
    Vector2 endpos = {0};
    float velocityfactor = 0.1f;
    bool gotmousepos = false;
    float totalKE = 0.0f;
    float totalPE = 0.0f;
    Vector2 totalAcc;

    std::vector<Body> bodies;
    std::vector<Color> colors = {BLUE, RED, PURPLE, GREEN, YELLOW, PINK};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        totalKE = 0.0f;
        totalPE = 0.0f;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            spawnpos = GetMousePosition();
            gotmousepos = true;
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && gotmousepos) 
        {
            endpos = GetMousePosition();
            DrawLineV(spawnpos, endpos, BLACK);
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && gotmousepos) 
        {
            gotmousepos = false;
            Vector2 dragvector = Vector2Subtract(endpos, spawnpos);
            Vector2 initialVelocity = Vector2Scale(dragvector, velocityfactor);

            Body newBody;
            newBody.position = spawnpos;
            newBody.velocity = initialVelocity;
            newBody.prevPosition = Vector2Subtract(spawnpos, Vector2Scale(initialVelocity, dt));
            newBody.color = newBody.generateRandomColor(colors);
            newBody.radius = 50;
            newBody.mass =  newBody.generateRandomMass();
            bodies.push_back(newBody);

            std::cout << "init vel : " << initialVelocity.x << " " << initialVelocity.y << std::endl;
            std::cout << newBody.mass << std::endl;
        }

        if (bodies.size() >= 2) 
        {
            for (int i = bodies.size() - 1; i >= 0; --i) 
            {
                totalAcc = {0};
                for (int j = bodies.size() - 1; j >= 0; --j) 
                {
                    if (i == j) continue; // skip self

                    if (bodies[i].collisionDetect(bodies[j])) 
                    {
                        bodies[i].mergeBodies(bodies[j], bodies, colors, j, i);
                        break; // Exit inner loop after merge
                    }

                    Vector2 acc = bodies[i].GetAccelerationFrom(bodies[j]);
                    totalAcc = Vector2Add(totalAcc, acc);

                    float dist = Vector2Distance(bodies[i].position, bodies[j].position);
                    totalPE += -bodies[i].G * bodies[i].mass * bodies[j].mass / dist;
                }

                if (i >= bodies.size()) continue; // Safety after erase
                totalKE += 0.5f * bodies[i].mass * Vector2LengthSqr(Vector2Scale(Vector2Subtract(bodies[i].position, bodies[i].prevPosition), 1.0f / dt));
                bodies[i].VerletUpdate(totalAcc, dt);
            }
        }
        else if (bodies.size() == 1)
        {
            bodies[0].VerletUpdate(totalAcc, dt);
            totalKE += 0.5f * bodies[0].mass * Vector2LengthSqr(Vector2Scale(Vector2Subtract(bodies[0].position, bodies[0].prevPosition), 1.0f / dt));
        }

        for (auto& b : bodies) 
        {
            b.Draw();
            
        }

        DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Energy: KE=%.2f PE=%.2f", totalKE, totalPE), 10, 50, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
