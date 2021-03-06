#include "raylib.h"
#include "screens.h"
#include "../../funcHeader.h"

#include <stdlib.h>                 // Required for: malloc(), free()

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct Player {
    Vector2 position;
    int width;
    int height;
} Player;


typedef struct Sample {
    Vector2 position;
    Color color;
} Sample;

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------

// Spiderplay screen global variables
static int framesCounter;
static int finishScreen;
static bool pause;

// Player variables
static Player player;
static Rectangle playerArea;    // Define player movement area (and sample collection limits)

static Rectangle waveRec;

// Samples variables
static Sample *samples;         // Game samples

// Resources variables
static Texture2D texBackground;
static Texture2D texPlayer;
static Texture2D texSampleMid;

static RenderTexture2D waveTarget;

static Sound fxSampleOn;        // Collected sample sound
static Sound fxSampleOff;       // Miss sample sound
static Sound fxPause;           // Pause sound

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
void expandGraphSpider(int coordMatrix[nodeCounts][2]);

//----------------------------------------------------------------------------------
// Spiderplay Screen Functions Definition
//----------------------------------------------------------------------------------
// Spiderplay Screen Initialization logic
void InitSpiderplayScreen(void)
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
    player.position = (Vector2){ playerArea.x + playerArea.width/2 - texPlayer.width/2,
                                 playerArea.y + playerArea.height/2 - texPlayer.height/2 };

    // Initialize wave and samples data
    Wave wave = LoadWave("graphic/resources/audio/wave.ogg");
    float *waveData = GetWaveData(wave);

    // We calculate the required parameters to adjust audio time to Spiderplay time
    // that way samples collected correspond to audio playing
    // Synchonization is not perfect due to possible rounding issues (float to int)

    // We don't need wave any more (already got waveData)
    UnloadWave(wave);

    // Init samples
    samples = (Sample *)malloc(nodeCounts*sizeof(Sample));
    expandGraphSpider(coordMatrix);
    // Initialize samples
    for (int i = 0; i < nodeCounts; i++)
    {
        //samples[i].value = waveData[i*samplesDivision]*sampleScaleFactor;   // Normalized value [-1.0..1.0]
        samples[i].position.x = coordMatrix[i][0];
        samples[i].position.y = coordMatrix[i][1] + 160;

        //if (samples[i].position.y > GetScreenHeight()/2 + MAX_GAME_HEIGHT/2) samples[i].position.y = GetScreenHeight()/2 - MAX_GAME_HEIGHT/2;
        //else if (samples[i].position.y < GetScreenHeight()/2 - MAX_GAME_HEIGHT/2) samples[i].position.y = GetScreenHeight()/2 + MAX_GAME_HEIGHT/2;
        samples[i].color = DARKBROWN;
    }
    free(waveData);

    // Load and start playing music
    // NOTE: Music is loaded in main code base
    StopMusicStream(music);
    PlayMusicStream(music);
}

// Spiderplay Screen Update logic
void UpdateSpiderplayScreen(void){
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

    for (int node = 0; node < nodeCounts; node++){
        if (CheckCollisionPointCircle(GetMousePosition(), samples[node].position, 12) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if (adMatrix[spiderIndex][node]){
                spiderIndex = node;
                removeLinkBetween(*bestCut(spiderIndex), *(bestCut(spiderIndex) + 1));
            }
        }
        if (spiderIndex == node) samples[node].color = RED;
        else if (isButterflyIndex(node)) samples[node].color = GREEN;
        else samples[node].color = DARKBROWN;
    }
}

// Spiderplay Screen Draw logic
void DrawSpiderplayScreen(void)
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
        DrawTexture(texSampleMid, samples[i].position.x - texSampleMid.width/2, samples[i].position.y - texSampleMid.height/2, samples[i].color);
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

// Spiderplay Screen Unload logic
void UnloadSpiderplayScreen(void)
{
    StopMusicStream(music);

    // Unload textures
    UnloadTexture(texBackground);
    UnloadTexture(texPlayer);
    UnloadTexture(texSampleMid);
    UnloadRenderTexture(waveTarget);

    // Unload sounds
    UnloadSound(fxSampleOn);
    UnloadSound(fxSampleOff);
    UnloadSound(fxPause);

    free(samples);   // Unload game samples
}

// Spiderplay Screen should finish?
int FinishSpiderplayScreen(void)
{
    return finishScreen;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------
void expandGraphSpider(int coordMatrix[nodeCounts][2]){
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
    for (float scale = 10.0f; !isScaleable; scale-=1){ // 10 would be maximum of scale
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
} // A function to scale the positions.
