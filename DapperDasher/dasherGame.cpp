#include <iostream>
#include <cstdio>
#include "raylib.h"


struct AnimData 
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y > windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    //update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        //update animation frame
            data.rec.x = data.frame * data.rec.width;
            data.frame++;
            if (data.frame > maxFrame)
            {
                data.frame = 0;
            }
    }
    return data;
}

int main()
{

    int windowDimensions[2];
    windowDimensions[0] = 518;
    windowDimensions[1] = 384;


    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher Game");

    //Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0.0;
    scarfyData.rec.y = 0.0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0.0;
    scarfyData.updateTime = 1.0/10.0;
    scarfyData.runningTime = 0.0;


    //AnimData for Nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfNebulae{6};
    AnimData nebulae[sizeOfNebulae]{};

    for(int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.x = windowDimensions[0] + i * 300;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
    }

    int velocity{0};

    //is the rectangle in the air
    bool isInAir{false};

    //jump velocity (pixels/sec)
    const int jumpVel{-600};

    //acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    //nebula x velocity(pixels/second)
    int nebVel{-200};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX{};
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX{};


    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        //delta time (time since last frame)
        const float dT{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        //Scroll background
        bgX -= 20 * dT;
        if (bgX <= -background.width *2)
        {
            bgX = 0.0;
        }
        //Scroll midground
        mgX -= 40 * dT;
        if (mgX <= -midground.width *2)
        {
            mgX = 0.0;
        }
        //Scroll foreground
        fgX -= 80 * dT;
        if (fgX <= -foreground.width *2)
        {
            fgX = 0.0;
        }

        //Draw Background
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, BLUE);
        Vector2 bg2Pos{bgX + background.width * 2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, BLUE);

        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, BLUE);
        Vector2 mg2Pos{mgX + midground.width * 2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, BLUE);

        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, BLUE);
        Vector2 fg2Pos{fgX + foreground.width * 2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, BLUE);

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }


        //Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        //perform ground check
        if(isOnGround(scarfyData, windowDimensions[1]))
        {
            //rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            //rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebVel * dT;
        }

        //update scarfy position
        scarfyData.pos.y += velocity * dT;

        //update scarfy animation frame
        if (!isInAir)
        {
            //update running time
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            //update nebula animation frame
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }


        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
    
} 