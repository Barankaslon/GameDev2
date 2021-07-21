#include <iostream>
#include <cstdio>
#include "raylib.h"


int main()
{

    //window dimensions

    const int windowWidth{1200};
    const int windowHeight{800};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher Game");

    //acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    //nebula Variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    Rectangle neb2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 neb2Pos{windowWidth +300, windowHeight - nebRec.height};

    //nebula x velocity(pixels/second)
    int nebVel{-200};

    //Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec{0.0, 0.0, scarfy.width/6, scarfy.height};
    Vector2 scarfyPos{windowWidth/2 - scarfyRec.width/2, windowHeight - scarfyRec.height};

    //animation scarfy frame
    int frame{};
    const float updateTime{1.0/10.0};
    float runningTime{};

    //animation nebula frame
    int nebFrame{};
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{};

    int neb2Frame{};
    const float neb2UpdateTime{1.0/16.0};
    float neb2RunningTime{};


    int velocity{0};

    //is the rectangle in the air
    bool isInAir{false};

    //jump velocity (pixels/sec)
    const int jumpVel{-600};



    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        //delta time (time since last frame)
        const float dT{GetFrameTime()};

        BeginDrawing();
        ClearBackground(BLACK);

        //perform ground check
        if(scarfyPos.y >= windowHeight - scarfyRec.height)
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

        //Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        //Draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        //Draw second nebula
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        //update nebula position
        nebPos.x += nebVel * dT;

        //update nebula-2 position
        neb2Pos.x += nebVel * dT;

        //update scarfy position
        scarfyPos.y += velocity * dT;

        //update scarfy animation frame
        if (!isInAir)
        {
            //update running time
            runningTime += dT;
            if (runningTime >= updateTime)
            {
                runningTime = 0.0;
                //update animation frame
                    scarfyRec.x = frame * scarfyRec.width;
                    frame++;
                    if (frame > 5)
                    {
                        frame = 0;
                    }
            }
        }

        //update nebula animation frame
        nebRunningTime += dT;
        if(nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if(nebFrame > 7)
            {
                nebFrame = 0;
            }
        }

        //update nebula-2 animation frame
        neb2RunningTime += dT;
        if(neb2RunningTime >= neb2UpdateTime)
        {
            neb2RunningTime = 0.0;
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if(neb2Frame > 7)
            {
                neb2Frame = 0;
            }
        }


        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    
} 