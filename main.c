#include "funcHeader.h"
#include "raylib.h"
#include "graphic/screens/screens.h"    // NOTE: Defines global variable: currentScreen


//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
const int screenWidth = 1280;
const int screenHeight = 720;

// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static int transToScreen = -1;

// NOTE: Some global variables that require to be visible for all screens,
// are defined in screens.h (i.e. currentScreen)

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void ChangeToScreen(int screen);     // No transition effect
static void TransitionToScreen(int screen);
static void UpdateTransition(void);
static void DrawTransition(void);
static void UpdateDrawFrame(void);          // Update and Draw one frame



int main(int argc, char * argv[]) {
    printf("Hello, World!\n");
    fileGetMatrix();
//    resetGravityMatrix();
//    printf("%d\n", distToClosestButterfly(spiderIndex));
//    add3lengthRoutes(spiderIndex, 5);
//    makeGravitySymmetric();
//    printGravityMatrix();
//    addNlengthRoutes(spiderIndex, 4, 5);



    char terminalMode;
    printf("Run [g]raphic or remain in [t]erminal:");
    scanf(" %c", &terminalMode);
    while (1) {
        if (terminalMode == 'g') {
            // Initialization
            //---------------------------------------------------------
            InitWindow(screenWidth, screenHeight, "Spider in Hell");

            // Global data loading (assets that must be available in all screens, i.e. fonts)
            InitAudioDevice();

            font = LoadFont("graphic/resources/font.fnt");
            music = LoadMusicStream("graphic/resources/audio/wave.ogg");

            SetMusicVolume(music, 1.0f);

            // Setup and Init first screen
            currentScreen = LOGO;
            InitLogoScreen();
            //InitTitleScreen();
            //InitSpiderplayScreen();
            //InitEndingScreen();
            SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
            //--------------------------------------------------------------------------------------

            // Main game loop
            while (!WindowShouldClose())    // Detect window close button or ESC key
            {
                UpdateDrawFrame();
            }

            // De-Initialization
            //--------------------------------------------------------------------------------------
            switch (currentScreen)
            {
                case LOGO: UnloadLogoScreen(); break;
                case TITLE: UnloadTitleScreen(); break;
                case Spider: UnloadSpiderplayScreen(); break;
                case Butterfly: UnloadButterflyplayScreen(); break;
                case ENDING: UnloadEndingScreen(); break;
                default: break;
            }

            // Unload all global loaded data (i.e. fonts) here!
            UnloadFont(font);
            UnloadMusicStream(music);

            CloseAudioDevice();     // Close audio context

            CloseWindow();          // Close window and OpenGL context
            //--------------------------------------------------------------------------------------
            break;
        }
        else if (terminalMode == 't'){
            char gameMode;
            printf("Initialize game as [s]pider or [b]utterfly:");
            scanf(" %c", &gameMode);
            while (1){
                if (gameMode == 's'){
                    initTerminalSpider();
                    break;
                }
                else if (gameMode == 'b'){
                    initTerminalButterfly();
                    break;
                }
                else {
                    printf("❌ Invalid input. Try again:");
                    scanf(" %c", &gameMode);
                    continue;
                }
            }
        }
        else {
            printf("❌ Invalid input. Try again:");
            scanf(" %c", &terminalMode);
        }

    }
    return (0);
}


//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------

// Change to next screen, no transition
static void ChangeToScreen(int screen)
{
    // Unload current screen
    switch (currentScreen)
    {
        case LOGO: UnloadLogoScreen(); break;
        case TITLE: UnloadTitleScreen(); break;
        case Butterfly: UnloadButterflyplayScreen(); break;
        case Spider: UnloadSpiderplayScreen(); break;
        case ENDING: UnloadEndingScreen(); break;
        default: break;
    }

    // Init next screen
    switch (screen)
    {
        case LOGO: InitLogoScreen(); break;
        case TITLE: InitTitleScreen(); break;
        case Butterfly: InitButterflyplayScreen(); break;
        case Spider: InitSpiderplayScreen(); break;
        case ENDING: InitEndingScreen(); break;
        default: break;
    }

    currentScreen = screen;
}

// Define transition to next screen
static void TransitionToScreen(int screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect
static void UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if ((int)transAlpha >= 1)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
                case LOGO: UnloadLogoScreen(); break;
                case TITLE: UnloadTitleScreen(); break;
                case Butterfly: UnloadButterflyplayScreen(); break;
                case Spider: UnloadSpiderplayScreen(); break;
                case ENDING: UnloadEndingScreen(); break;
                default: break;
            }

            // Load next screen
            switch (transToScreen)
            {
                case LOGO: InitLogoScreen(); break;
                case TITLE: InitTitleScreen(); break;
                case Butterfly: InitButterflyplayScreen(); break;
                case Spider: InitSpiderplayScreen(); break;
                case ENDING: InitEndingScreen(); break;
                default: break;
            }

            currentScreen = transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.05f;

        if ((int)transAlpha <= 0)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = -1;
        }
    }
}

// Draw transition effect (full-screen rectangle)
static void DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, transAlpha));
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    if (!onTransition)
    {
        switch(currentScreen)
        {
            case LOGO:
            {
                UpdateLogoScreen();

                if (FinishLogoScreen()) TransitionToScreen(TITLE);

            } break;
            case TITLE:
            {
                UpdateTitleScreen();

                if (FinishTitleScreen() == 1) TransitionToScreen(Butterfly);
                else if (FinishTitleScreen() == 2) TransitionToScreen(Spider);

            } break;
            case Butterfly:
            {
                UpdateButterflyplayScreen();

                if (FinishButterflyplayScreen() == 1) TransitionToScreen(ENDING);
                //else if (FinishButterflyplayScreen() == 2) TransitionToScreen(TITLE);

            } break;
            case Spider:
            {
                UpdateSpiderplayScreen();

                if (FinishSpiderplayScreen() == 1) TransitionToScreen(ENDING);
                //else if (FinishSpiderplayScreen() == 2) TransitionToScreen(TITLE);
            } break;
            case ENDING:
            {
                UpdateEndingScreen();

                if (FinishEndingScreen() == 1) TransitionToScreen(TITLE);

            } break;
            default: break;
        }
    }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
    if (currentScreen != ENDING) UpdateMusicStream(music);
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    switch(currentScreen)
    {
        case LOGO: DrawLogoScreen(); break;
        case TITLE: DrawTitleScreen(); break;
        case Butterfly: DrawButterflyplayScreen(); break;
        case Spider: DrawSpiderplayScreen(); break;
        case ENDING: DrawEndingScreen(); break;
        default: break;
    }

    // Draw full screen rectangle in front of everything
    if (onTransition) DrawTransition();

    EndDrawing();
    //----------------------------------------------------------------------------------
}

