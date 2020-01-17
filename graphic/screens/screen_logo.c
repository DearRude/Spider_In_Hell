#include "raylib.h"
#include "screens.h"

#define LOGO_RECS_SIDE  16

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------

// Logo screen global variables
static int framesCounter;
static int finishScreen;

static int logoPositionX;
static int logoPositionY;

static int lettersCount;

static int topSideRecWidth;
static int leftSideRecHeight;

static int bottomSideRecWidth;
static int rightSideRecHeight;

static int state;               // Tracking animation states (State Machine)
static float alpha = 1.0f;      // Useful for fading

//----------------------------------------------------------------------------------
// Logo Screen Functions Definition
//----------------------------------------------------------------------------------

// Logo Screen Initialization logic
void InitLogoScreen(void)
{
    // Initialize LOGO screen variables here!
    finishScreen = 0;
    framesCounter = 0;
    lettersCount = 0;
    
    logoPositionX = GetScreenWidth()/2 - 128;
    logoPositionY = GetScreenHeight()/2 - 128;
    
    topSideRecWidth = LOGO_RECS_SIDE;
    leftSideRecHeight = LOGO_RECS_SIDE;
    bottomSideRecWidth = LOGO_RECS_SIDE;
    rightSideRecHeight = LOGO_RECS_SIDE;

    state = 0;
    alpha = 1.0f;
}

// Logo Screen Update logic
void UpdateLogoScreen(void)
{
    // Update LOGO screen variables here!
    if (state == 0)                 // State 0: Small box blinking
    {
        framesCounter++;

        if (framesCounter == 80)
        {
            state = 1;
            framesCounter = 0;      // Reset counter... will be used later...
            
            PlayMusicStream(music); // Start playing music... ;)
        }
    }
    else if (state == 1)            // State 1: Top and left bars growing
    {
        topSideRecWidth += 8;
        leftSideRecHeight += 8;

        if (topSideRecWidth == 256) state = 2;
    }
    else if (state == 2)            // State 2: Bottom and right bars growing
    {
        bottomSideRecWidth += 8;
        rightSideRecHeight += 8;

        if (bottomSideRecWidth == 256) state = 3;
    }
    else if (state == 3)            // State 3: Letters appearing (one by one)
    {
        framesCounter++;

        if (lettersCount < 10) 
        {
            if (framesCounter/15)   // Every 12 frames, one more letter!
            {
                lettersCount++;
                framesCounter = 0;
            }
        }
        else    // When all letters have appeared, just fade out everything
        {
            if (framesCounter > 200)
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    finishScreen = 1;
                }
            }
        }
    }
}

// Logo Screen Draw logic
void DrawLogoScreen(void)
{
    if (state == 0)
    {
        if ((framesCounter/10)%2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
    }
    else if (state == 1)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
    }
    else if (state == 2)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

        DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
    }
    else if (state == 3)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

        DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

        DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(RAYWHITE, alpha));

        DrawText(SubText("Ferdowsi", 0, lettersCount), GetScreenWidth()/2 - 100, GetScreenHeight()/2 -100, 40, Fade(BLACK, alpha));
        DrawText(SubText("University", 0, lettersCount), GetScreenWidth()/2 - 100, GetScreenHeight()/2 - 50, 40, Fade(BLACK, alpha));
        DrawText(SubText("of Mashhad", 0, lettersCount), GetScreenWidth()/2 - 109, GetScreenHeight()/2 + 48, 38, Fade(BLACK, alpha));
        if (framesCounter > 20) DrawText("made in", logoPositionX, logoPositionY - 27, 20, Fade(DARKGRAY, alpha));
    }
}

// Logo Screen Unload logic
void UnloadLogoScreen(void)
{
    // Unload LOGO screen variables here!
}

// Logo Screen should finish?
int FinishLogoScreen(void)
{
    return finishScreen;
}