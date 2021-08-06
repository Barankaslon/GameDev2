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

    float speed{4.0};

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        (float)windowDimensions[0]/2.0 - 4.0 * (0.5 * (float)knight.width/6.0),
        (float)windowDimensions[1]/2.0 - 4.0 * (0.5 * (float)knight.height)
    };

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
                
                mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            }
        // draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        //draw the character
        Rectangle source{0.f, 0.f, (float)knight.width/6.f, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 4.f * (float)knight.width/6.f, 4.f * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
}