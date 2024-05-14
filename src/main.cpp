#include <cstdlib>
#include <algorithm>

#include "raylib.h"
#include "config.h"
#include <cmath>
#include "Scene.h"

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(960, 520, "Das GAME");
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    // ...
    // ...
    Texture2D myTexture = LoadTexture("assets/graphics/testimage.png");
    RenderTexture2D canvas = LoadRenderTexture(Game::ScreenWidth, Game::ScreenHeight);
    float renderScale{}; // this and the line below are relevant to drawing later.
    Rectangle renderRec{};
    auto scene = new Scene(nullptr);


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) { //Fullscreen logic.
            if (IsWindowFullscreen()) {
                ToggleFullscreen();
                SetWindowSize(Game::ScreenWidth,Game::ScreenHeight);
            } else {
                SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
                ToggleFullscreen();
            }
        }
        // Updates that are made by frame are coded here
        // This is where YOUR logic code should go
        // ...
        // ...
        scene->update();
        BeginDrawing();
        // You can draw on the screen between BeginDrawing() and EndDrawing()
        // For the letterbox we draw on canvas instead


        BeginTextureMode(canvas);
        { //Within this block is where we draw our app to the canvas and YOUR code goes.
            ClearBackground(WHITE);
            scene->draw();
            /*DrawText("Hello, world!", 10, 10, 30, LIGHTGRAY);
            DrawTexture(myTexture, 10, 100, WHITE);
            DrawLine(0,0,sin(GetTime()) * 100 + 80, cos(GetTime()) * 100 + 70, RED);
             */

        }
        EndTextureMode();
        //The following lines put the canvas in the middle of the window and have the negative as black
        ClearBackground(BLACK); // If you want something else than a black void in the background
                                // then you can add stuff here.

        renderScale = std::min(GetScreenHeight() / (float) canvas.texture.height, // Calculates how big or small the canvas has to be rendered.
                               GetScreenWidth()  / (float) canvas.texture.width); // Priority is given to the smaller side.
        renderScale = floorf(renderScale);
        if (renderScale < 1) renderScale = 1; // Ensure that scale is at least 1.
        renderRec.width = canvas.texture.width * renderScale;
        renderRec.height = canvas.texture.height * renderScale;
        renderRec.x = (GetScreenWidth() - renderRec.width) / 2.0f;
        renderRec.y = (GetScreenHeight() - renderRec.height) / 2.0f;
        DrawTexturePro(canvas.texture,
                       Rectangle{0, 0, (float) canvas.texture.width, (float) -canvas.texture.height},
                       renderRec,
                       {}, 0, WHITE);
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_S)) {
            DrawText(TextFormat("Render scale: %.0f", renderScale), 10, 10, 20, LIGHTGRAY);
        }
        //Draw inputs of WASD
        Color PressedColor = RED;
        Color NotPressedColor = ColorAlpha(LIGHTGRAY,0.9f);
        DrawRectangle(30, 10, 20, 20, IsKeyDown(KEY_W) ? PressedColor : NotPressedColor);
        DrawRectangle(10, 30, 20, 20, IsKeyDown(KEY_A) ? PressedColor : NotPressedColor);
        DrawRectangle(30, 50, 20, 20, IsKeyDown(KEY_S) ? PressedColor : NotPressedColor);
        DrawRectangle(50, 30, 20, 20, IsKeyDown(KEY_D) ? PressedColor : NotPressedColor);
        EndDrawing();
    } // Main game loop end

    // De-initialization here
    // ...
    // ...
    UnloadTexture(myTexture);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
