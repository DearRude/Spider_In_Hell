#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------

// Ending screen global variables
static int framesCounter;
static int finishScreen;

static Texture2D texBackground;
static Texture2D texWin;
static Texture2D texLose;

//----------------------------------------------------------------------------------
// Ending Screen Functions Definition
//----------------------------------------------------------------------------------

// Ending Screen Initialization logic
void InitEndingScreen(void)
{
    // TODO: Initialize ENDING screen variables here!
    framesCounter = 0;
    finishScreen = 0;

    texBackground = LoadTexture("graphic/resources/textures/background.png");
    texWin = LoadTexture("graphic/resources/textures/win.png");
    texLose = LoadTexture("graphic/resources/textures/lose.png");
}

// Ending Screen Update logic
void UpdateEndingScreen(void)
{
    // TODO: Update ENDING screen variables here!
    framesCounter++;

    // Press enter to return to TITLE screen
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        finishScreen = 1;
    }
}

// Ending Screen Draw logic
void DrawEndingScreen(void)
{
    DrawTexture(texBackground, 0, 0, WHITE);

    if (endingStatus == 1)          // Win
    {
        DrawTexture(texWin, GetScreenWidth()/2 - texWin.width/2, 90, WHITE);
        DrawTextEx(font, "you are smarter than the algorithm!", (Vector2){ 100, 335 }, font.baseSize, 0, WHITE);
    }
    else if (endingStatus == 2)     // Lose
    {
        DrawTexture(texLose, GetScreenWidth()/2 - texWin.width/2, 90, WHITE);
        DrawTextEx(font, "the algorithm has won over you...", (Vector2){ 110, 335 }, font.baseSize, 0, WHITE);
    }
    
    DrawRectangle(0, GetScreenHeight() - 70, 560, 40, Fade(RAYWHITE, 0.8f));
    DrawText("Developed by Ebrahim Nejati", 36, GetScreenHeight() - 60, 20, DARKBLUE);
    

    if ((framesCounter > 80) && ((framesCounter/40)%2)) DrawTextEx(font, "mouse click to return", (Vector2){ 300, 464 }, font.baseSize, 0, SKYBLUE);
}

// Ending Screen Unload logic
void UnloadEndingScreen(void)
{
    // TODO: Unload ENDING screen variables here!
    UnloadTexture(texBackground);
    UnloadTexture(texWin);
    UnloadTexture(texLose);
}

// Ending Screen should finish?
int FinishEndingScreen(void)
{
    return finishScreen;
}