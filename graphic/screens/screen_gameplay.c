#include "raylib.h"
#include "screens.h"
#include "../../funcHeader.h"

#include <stdlib.h>                 // Required for: malloc(), free()
#include <math.h>                   // Required for: sqrtf(), asinf()

#define MAX_SAMPLES_SPEED       7   // Max speed for samples movement
#define MIN_SAMPLES_SPEED       3   // Min speed for samples movement
#define SAMPLES_SPACING       100   // Separation between samples in pixels
#define SAMPLES_MULTIPLIER    700   // Defines sample data scaling value (it would be adjusted to MAX_GAME_HEIGHT)
#define MAX_GAME_HEIGHT       400   // Defines max possible amplitude between samples (game area)

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct Player {
    Vector2 position;
    Vector2 speed;
    int width;
    int height;
    Color color;
} Player;


typedef struct Sample {
    Vector2 position;
    float value;            // Raw audio sample value (normalized)
    int radius;
    bool active;            // Define if sample is active (can be collected)
    bool collected;         // Define if sample has been collected
    bool renderable;        // Define if sample should be rendered
    Color color;
} Sample;

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------

// Gameplay screen global variables
static int framesCounter;
static int finishScreen;
static bool pause;

// Player variables
static Player player;
static Rectangle playerArea;    // Define player movement area (and sample collection limits)

static Rectangle waveRec;

// Samples variables
static Sample *samples;         // Game samples
static int collectedSamples;    // Samples collected by player
static int currentSample;       // Last sample to go through player collect area
static float waveTime;          // Total sample time in ms

// Resources variables
static Texture2D texBackground;
static Texture2D texPlayer;
static Texture2D texSampleSmall;
static Texture2D texSampleMid;
static Texture2D texSampleBig;

static RenderTexture2D waveTarget;

static Sound fxSampleOn;        // Collected sample sound
static Sound fxSampleOff;       // Miss sample sound
static Sound fxPause;           // Pause sound
// Debug variables

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void DrawSamplesMap(Sample *samples, int sampleCount, int playedSamples, Rectangle bounds, Color color);

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------
void expandGraph(int coordMatrix[nodeCounts][2]){
    int leftMost = 1280, topMost = 720;
    for (int i = 0; i < nodeCounts; i++){
        if (leftMost > coordMatrix[i][0]) leftMost = coordMatrix[i][0];
        if (topMost > coordMatrix[i][1]) topMost = coordMatrix[i][1];
    }

    for (int i2 = 0; i2 < nodeCounts; i2++){
        coordMatrix[i2][0] -= (leftMost);
        coordMatrix[i2][1] -= (topMost);
    }
    int isScaleable = 0;
    for (float scale = 20.0f; !isScaleable; scale-=1){
        for (int i3 = 0; i3 < nodeCounts; i3++){
            coordMatrix[i3][0] *= scale;
            coordMatrix[i3][1] *= scale;
        }

        isScaleable = 1;
        for (int i4 = 0; i4 < nodeCounts; i4++){
            if (coordMatrix[i4][0] > (1280 - 100) || coordMatrix[i4][1] > (720-160-100)) {
                isScaleable = 0;
                break;
            }
        }
        if (isScaleable){
            for (int i4 = 0; i4 < nodeCounts; i4++){
                coordMatrix[i4][0] += 50;
                coordMatrix[i4][1] += 50;
            }
        }
        else {
            for (int i5 = 0; i5 < nodeCounts; i5++){
                coordMatrix[i5][0] /= scale;
                coordMatrix[i5][1] /= scale;
            }
        }

    }
}

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    pause = false;
    endingStatus = 0;
    
    // Textures loading
    texBackground = LoadTexture("graphic/resources/textures/nbackground_gameplay.png");
    texPlayer = LoadTexture("graphic/resources/textures/player.png");
    texSampleMid = LoadTexture("graphic/resources/textures/sample_mid.png");
    
    waveRec = (Rectangle){ 32, 32, 1280 - 64, 105 };
    waveTarget = LoadRenderTexture(waveRec.width, waveRec.height);

    // Sound loading
    fxSampleOn = LoadSound("graphic/resources/audio/sample_on.wav");
    fxSampleOff = LoadSound("graphic/resources/audio/sample_off.wav");
    fxPause = LoadSound("graphic/resources/audio/pause.wav");
    
    SetSoundVolume(fxSampleOn, 0.6f);
    SetSoundVolume(fxPause, 0.5f);

    // Initialize player data
    playerArea = (Rectangle){ 0, 0, 1280, 720 };
    
    player.width = 20;
    player.height = 60;
    player.speed = (Vector2){ 15, 15 };
    player.color = GOLD;
    player.position = (Vector2){ playerArea.x + playerArea.width/2 - texPlayer.width/2, 
                                 playerArea.y + playerArea.height/2 - texPlayer.height/2 };

    // Initialize wave and samples data
    Wave wave = LoadWave("graphic/resources/audio/wave.ogg");
    float *waveData = GetWaveData(wave);
    
    // We calculate the required parameters to adjust audio time to gameplay time
    // that way samples collected correspond to audio playing
    // Synchonization is not perfect due to possible rounding issues (float to int)

    // We don't need wave any more (already got waveData)
    UnloadWave(wave);
    
    collectedSamples = 0;

    // Init samples
    samples = (Sample *)malloc(nodeCounts*sizeof(Sample));
    expandGraph(coordMatrix);
    // Initialize samples
    for (int i = 0; i < nodeCounts; i++)
    {
        //samples[i].value = waveData[i*samplesDivision]*sampleScaleFactor;   // Normalized value [-1.0..1.0]
        samples[i].position.x = coordMatrix[i][0];
        samples[i].position.y = coordMatrix[i][1] + 160;
        
        //if (samples[i].position.y > GetScreenHeight()/2 + MAX_GAME_HEIGHT/2) samples[i].position.y = GetScreenHeight()/2 - MAX_GAME_HEIGHT/2;
        //else if (samples[i].position.y < GetScreenHeight()/2 - MAX_GAME_HEIGHT/2) samples[i].position.y = GetScreenHeight()/2 + MAX_GAME_HEIGHT/2;
        
        samples[i].radius = 6;
        samples[i].active = true;
        samples[i].collected = false;
        samples[i].color = RED;
        samples[i].renderable = true;
    }
    currentSample = 0;

    free(waveData);
    
    // Load and start playing music
    // NOTE: Music is loaded in main code base
    StopMusicStream(music);
    PlayMusicStream(music);
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    if (IsKeyPressed('P'))
    {
        PlaySound(fxPause);
        pause = !pause;

        if (pause) PauseMusicStream(music);
        else ResumeMusicStream(music);
    }


    if (!pause)
    {
        framesCounter++;        // Time starts counting to awake enemies
        
        // Player movement logic (mouse)
        player.position.y = GetMousePosition().y;
        player.position.x = GetMousePosition().x;

        // Player logic: check player area limits
        if (player.position.x < playerArea.x) player.position.x = playerArea.x;
        else if ((player.position.x + player.width) > (playerArea.x + playerArea.width)) player.position.x = playerArea.x + playerArea.width - player.width;
        
        if (player.position.y < playerArea.y) player.position.y = playerArea.y;
        else if ((player.position.y + player.height) > (playerArea.y + playerArea.height)) player.position.y = playerArea.y + playerArea.height - player.height;



        // Check ending conditions
        if (isButterflyIndex(spiderIndex))
        {
            endingStatus = 1;           // Win
            finishScreen = 1;
        }

        if (distToClosestButterfly(spiderIndex) == -1)
        {
            endingStatus = 2;           // Loose
            finishScreen = 1;
        }
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // Draw background
    DrawTexture(texBackground, 0, 0, WHITE);

    // Screen elements drawing
    //DrawRectangleLines(playerArea.x, playerArea.y, playerArea.width, playerArea.height, BLUE);
    //DrawRectangle(0, GetScreenHeight()/2 - 1, GetScreenWidth(), 2, Fade(BLUE, 0.3f));
    //DrawRectangleLines(0, GetScreenHeight()/2 - MAX_GAME_HEIGHT/2, GetScreenWidth(), MAX_GAME_HEIGHT, GRAY);

    // Draw Links
    for (int first = 0; first < nodeCounts; first++)
        for (int last = 0; last < nodeCounts; last++)
            if (isLinkBetween(first, last)){
                // Draw line between samples
                DrawLineEx(samples[first].position, samples[last].position, 3.0f, BROWN);
            }

    // Draw samples
    for (int i = 0; i < nodeCounts; i++)
    {
        Color col = DARKBROWN;
        if (isButterflyIndex(i)) col = GREEN;
        if (spiderIndex == i) col = RED;
        DrawTexture(texSampleMid, samples[i].position.x - texSampleMid.width/2, samples[i].position.y - texSampleMid.height/2, col);
        if (i < 10) DrawText(FormatText("%i", i), samples[i].position.x-2, samples[i].position.y-5, 3, WHITE);
        else DrawText(FormatText("%i", i), samples[i].position.x-7, samples[i].position.y-5, 3, WHITE);
    }


    // Draw player
    //DrawRectangle((int)player.position.x, (int)player.position.y, player.width, player.height, player.color);
    //DrawTexture(texPlayer, player.position.x - 32, player.position.y - 24, WHITE);
 
    // Draw pause message
    if (pause) DrawTextEx(font, "GAME PAUSED", (Vector2){ 235, 400 }, font.baseSize*2, 0, WHITE);

    // Draw number of samples
    //DrawText(FormatText("%05i", collectedSamples), 900, 200, 40, GRAY);
    //DrawText(FormatText("%05i", totalSamples), 900, 250, 40, GRAY);
    //DrawTextEx(font, FormatText("%05i / %05i", collectedSamples, totalSamples), (Vector2){810, 170}, font.baseSize, -2, SKYBLUE);

    // Draw synchonicity level
    //DrawRectangle(99, 622, 395, 32, Fade(RAYWHITE, 0.8f));
        
    //if (synchro <= 0.3f) DrawRectangle(99, 622, synchro*395, 32, Fade(RED, 0.8f));
    //else if (synchro <= 0.8f) DrawRectangle(99, 622, synchro*395, 32, Fade(ORANGE,0.8f));
    //else if (synchro < 1.0f) DrawRectangle(99, 622, synchro*395, 32, Fade(LIME,0.8f));
    //else DrawRectangle(99, 622, synchro*395, 32, Fade(GREEN, 0.9f));
    
    //DrawRectangleLines(99, 622, 395, 32, MAROON);

    //if (synchro == 1.0f) DrawTextEx(font, FormatText("%02i%%", (int)(synchro*100)), (Vector2){99 + 390, 600}, font.baseSize, -2, GREEN);
    //else DrawTextEx(font, FormatText("%02i%%", (int)(synchro*100)), (Vector2){99 + 390, 600}, font.baseSize, -2, SKYBLUE);
    
    // Draw time warp coool-down bar
    //DrawRectangle(754, 622, 395, 32, Fade(RAYWHITE, 0.8f));
    //DrawRectangle(754, 622, warpCounter, 32, Fade(SKYBLUE, 0.8f));
    //DrawRectangleLines(754, 622, 395, 32, DARKGRAY);
    //DrawText(FormatText("%02i%%", (int)(synchro*100)), 754 + 410, 628, 20, DARKGRAY);
    //DrawTextEx(font, FormatText("%02i%%", (int)((float)warpCounter/395.0f*100.0f)), (Vector2){754 + 390, 600}, font.baseSize, -2, SKYBLUE);

}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    StopMusicStream(music);
    
    // Unload textures
    UnloadTexture(texBackground);
    UnloadTexture(texPlayer);
    UnloadTexture(texSampleSmall);
    UnloadTexture(texSampleMid);
    UnloadTexture(texSampleBig);
    
    UnloadRenderTexture(waveTarget);

    // Unload sounds
    UnloadSound(fxSampleOn);
    UnloadSound(fxSampleOff);
    UnloadSound(fxPause);

    free(samples);   // Unload game samples
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Draw samples in wave form (including already played samples in a different color!)
// NOTE: For proper visualization, MSAA x4 is recommended, alternatively
// it should be rendered to a bigger texture and then scaled down with 
// bilinear/trilinear texture filtering
static void DrawSamplesMap(Sample *samples, int sampleCount, int playedSamples, Rectangle bounds, Color color)
{
    // NOTE: We just pick a sample to draw every increment
    float sampleIncrementX = (float)bounds.width/sampleCount;

    Color col = color;

    for (int i = 0; i < sampleCount - 1; i++)
    {
        if (i < playedSamples) col = GRAY;
        else col = color;

        DrawLineV((Vector2){ (float)bounds.x + (float)i*sampleIncrementX, (float)(bounds.y + bounds.height/2) + samples[i].value*bounds.height },
                  (Vector2){ (float)bounds.x + (float)(i + 1)*sampleIncrementX, (float)(bounds.y  + bounds.height/2) + + samples[i + 1].value*bounds.height }, col);
    }
}