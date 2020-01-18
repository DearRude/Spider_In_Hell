#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------

// Title screen global variables
static int framesCounter;
static int finishScreen;

static Texture2D texBackground;
static Texture2D texTitle;
static Texture2D texLogo;
static Texture2D texLogo2;

static float titleAlpha = 0.0f;

static Sound fxStart;

//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    // Initialize TITLE screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    
    texBackground = LoadTexture("graphic/resources/textures/background_title.png");
    texTitle = LoadTexture("graphic/resources/textures/ntitle.png");
    texLogo = LoadTexture("graphic/resources/textures/nlogo_raylib.png");
    texLogo2 = LoadTexture("graphic/resources/textures/nlogo_raylib2.png");
    fxStart = LoadSound("graphic/resources/audio/start.wav");
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    // Update TITLE screen variables here!
    framesCounter++;
    
    titleAlpha += 0.005f;
    
    if (titleAlpha >= 1.0f) titleAlpha = 1.0f;

    // Press enter to change to ATTIC screen
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        PlaySound(fxStart);
        StopMusicStream(music);
        finishScreen = 1;
    }
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
    {
        PlaySound(fxStart);
        StopMusicStream(music);
        finishScreen = 2;
    }
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    DrawTexture(texBackground, 0, 0, WHITE);
    DrawTexture(texTitle, GetScreenWidth()/2 - texTitle.width/2, -25, Fade(WHITE, titleAlpha));

    DrawRectangle(0, GetScreenHeight() - 70, 560, 40, Fade(RAYWHITE, 0.8f));
    DrawText("Developed by Ebrahim Nejati.", 36, GetScreenHeight() - 60, 20, DARKBLUE);
    DrawTexture(texLogo, GetScreenWidth() - 128 - 34, GetScreenHeight() - 128 - 36, WHITE);
    DrawTexture(texLogo2, GetScreenWidth() - 128 - 34, GetScreenHeight() - 300, WHITE);

    if ((framesCounter > 160) && ((framesCounter/40)%2)) DrawTextEx(font, "[L] Guardian | [R] Spider", (Vector2){ 290, 500 }, font.baseSize, 0, SKYBLUE);
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    // Unload TITLE screen variables here!
    UnloadTexture(texBackground);
    UnloadTexture(texTitle);
    UnloadTexture(texLogo);
    
    UnloadSound(fxStart);
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}