#include <iostream>
#include <cstdio>
#include "raylib.h"
#include "raymath.h"

int main()
{
    int windowDimensions[2];
    windowDimensions[0] = 384;
    windowDimensions[1] = 384;


    InitWindow(windowDimensions[0], windowDimensions[1], "Classy Clash Game");

    Texture2D map = LoadTexture("nature_tileset/worldMap.png");
    Vector2 mapPos{0.0, 0.0};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
            if (IsKeyDown(KEY_A)) direction.x -= 1.0;
            if (IsKeyDown(KEY_S)) direction.y += 1.0;
            if (IsKeyDown(KEY_D)) direction.x += 1.0;
            if (IsKeyDown(KEY_W)) direction.y -= 1.0;
            if (Vector2Length(direction) != 0.0)
            {
                // set mapPos = mapPos - direction
                mapPos = Vector2Subtract(mapPos, Vector2Normalize(direction));
            }

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
}