#include <iostream>
#include <cstdio>
#include "raylib.h"

int main()
{
    int windowDimensions[2];
    windowDimensions[0] = 384;
    windowDimensions[1] = 384;


    InitWindow(windowDimensions[0], windowDimensions[1], "Classy Clash Game");

    Texture2D map = LoadTexture("nature_tileset/worldMap.png");
    float mapX{};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 mapPos{mapX, 0.0};
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
}