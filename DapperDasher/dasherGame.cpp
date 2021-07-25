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

int main()
{

    int windowDimensions[2];
    windowDimensions[0] = 1200;
    windowDimensions[1] = 800;


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

    const int sizeOfNebulae{3};
    AnimData nebulae[sizeOfNebulae]{};

    for(int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
    }

    nebulae[0].pos.x = windowDimensions[0];
    nebulae[1].pos.x = windowDimensions[0] + 300;
    nebulae[2].pos.x = windowDimensions[0] + 600;

    int velocity{0};

    //is the rectangle in the air
    bool isInAir{false};

    //jump velocity (pixels/sec)
    const int jumpVel{-600};

    //acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    //nebula x velocity(pixels/second)
    int nebVel{-200};



    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        //delta time (time since last frame)
        const float dT{GetFrameTime()};

        BeginDrawing();
        ClearBackground(BLACK);

        //Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        //Draw nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);

        //Draw second nebula
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);

        //DrawTextureRec(nebula, nebulae[2].rec, nebulae[2].pos, BLUE);

        //perform ground check
        if(scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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

        //update nebula position
        nebulae[0].pos.x += nebVel * dT;

        //update nebula-2 position
        nebulae[1].pos.x += nebVel * dT;

        //update scarfy position
        scarfyData.pos.y += velocity * dT;

        //update scarfy animation frame
        if (!isInAir)
        {
            //update running time
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;
                //update animation frame
                    scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                    scarfyData.frame++;
                    if (scarfyData.frame > 5)
                    {
                        scarfyData.frame = 0;
                    }
            }
        }

        
        nebulae[0].runningTime += dT;
        if(nebulae[0].runningTime >= nebulae[0].updateTime)
        {
            nebulae[0].runningTime = 0.0;
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if(nebulae[0].frame > 7)
            {
                nebulae[0].frame = 0;
            }
        }

        //update nebula-2 animation frame
        nebulae[1].runningTime += dT;
        if(nebulae[1].runningTime >= nebulae[1].updateTime)
        {
            nebulae[1].runningTime = 0.0;
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if(nebulae[1].frame > 7)
            {
                nebulae[1].frame = 0;
            }
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            //update nebula animation frame
            nebulae[i].runningTime += dT;
            if(nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0.0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if(nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }
        }
        }


        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    
} 