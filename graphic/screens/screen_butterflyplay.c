#include "raylib.h"
#include "screens.h"
#define NUM_FRAMES  3       // Number of frames (rectangles) for the button sprite texture
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

// Gameplay screen global variables
static int framesCounter;
static int onceButton;
static int firstnode, lastnode;
static int frameHeight;
static int finishScreen;
static int btnState;
static bool btnAction;
static bool pause;

// Player variables
static Player player;
static Rectangle playerArea;    // Define player movement area (and sample collection limits)

static Rectangle waveRec;
static Rectangle sourceRec;
static Rectangle btnBounds;

// Samples variables
static Sample *samples;         // Game samples

// Resources variables
static Texture2D texBackground;
static Texture2D texPlayer;
static Texture2D texSampleMid;
static Texture2D button;
static Vector2 mousePoint;

static RenderTexture2D waveTarget;

static Sound fxSampleOn;        // Collected sample sound
static Sound fxSampleOff;       // Miss sample sound
static Sound fxPause;           // Pause sound
static Sound fxButton;

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
void expandGraphButterfly(int coordMatrix[nodeCounts][2]);

//----------------------------------------------------------------------------------
// ButterflyGame Screen Functions Definition
//----------------------------------------------------------------------------------
// Gameplay Screen Initialization logic
void InitButterflyplayScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    pause = false;
    endingStatus = 0;
    
    // Textures loading
    texBackground = LoadTexture("graphic/resources/textures/nbackground_gameplay.png");
    texPlayer = LoadTexture("graphic/resources/textures/player.png");
    texSampleMid = LoadTexture("graphic/resources/textures/sample_mid.png");
    fxButton = LoadSound("graphic/resources/audio/buttonfx.wav");   // Load button sound
    button = LoadTexture("graphic/resources/textures/button.png"); // Load button texture

    // Define frame rectangle for drawing
    frameHeight = button.height/NUM_FRAMES;
    sourceRec =(Rectangle) {0, 0, button.width, frameHeight };

    // Define button bounds on screen
    btnBounds =(Rectangle) { 1100 - button.width/2, 200 - button.height/NUM_FRAMES/2, button.width, frameHeight };

    btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    btnAction = false;         // Button action should be activated

    mousePoint = (Vector2){ 0.0f, 0.0f };
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

    // We calculate the required parameters to adjust audio time to gameplay time
    // that way samples collected correspond to audio playing
    // Synchonization is not perfect due to possible rounding issues (float to int)

    // We don't need wave any more (already got waveData)
    UnloadWave(wave);

    // Init samples
    samples = (Sample *)malloc(nodeCounts*sizeof(Sample));
    expandGraphButterfly(coordMatrix);
    // Initialize samples
    for (int i = 0; i < nodeCounts; i++)
    {
        samples[i].position.x = coordMatrix[i][0];
        samples[i].position.y = coordMatrix[i][1] + 160;
        samples[i].color = DARKBROWN;
    }
    free(waveData);
    onceButton = 1;
    // Load and start playing music
    // NOTE: Music is loaded in main code base
    StopMusicStream(music);
    PlayMusicStream(music);
}

// Gameplay Screen Update logic
void UpdateButterflyplayScreen(void){
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
        if (distToClosestButterfly(spiderIndex) == -1)
        {
            endingStatus = 1;           // Win
            finishScreen = 1;
        }

        if (isButterflyIndex(spiderIndex))
        {
            endingStatus = 2;           // Loose
            finishScreen = 1;
        }
    }

    for (int node = 0; node < nodeCounts; node++){
        if (CheckCollisionPointCircle(GetMousePosition(), samples[node].position, 12) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            firstnode = node;
        }
        if (CheckCollisionPointCircle(GetMousePosition(), samples[node].position, 12) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
            lastnode = node;
            if (adMatrix[firstnode][lastnode]){
                removeLinkBetween(firstnode, lastnode);
                spiderIndex = bestMove(spiderIndex);
            }
        }
        if (spiderIndex == node) samples[node].color = RED;
        else if (isButterflyIndex(node)) samples[node].color = GREEN;
        else samples[node].color = DARKBROWN;
    }

    mousePoint = GetMousePosition();
    btnAction = false;

    // Check button state
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) btnState = 2;
        else btnState = 1;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) btnAction = true;
    }
    else btnState = 0;

    if (btnAction && onceButton)
    {
        PlaySound(fxButton);
        spiderIndex = bestMove(spiderIndex);
        onceButton = 0;
    }

    // Calculate button frame rectangle to draw depending on button state
    sourceRec.y = btnState*frameHeight;
}

// Gameplay Screen Draw logic
void DrawButterflyplayScreen(void)
{
    // Draw background
    DrawTexture(texBackground, 0, 0, WHITE);


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


    // Draw pause message
    if (pause) DrawTextEx(font, "GAME PAUSED", (Vector2){ 235, 400 }, font.baseSize*2, 0, WHITE);
    DrawTextureRec(button, sourceRec, (Vector2){ btnBounds.x, btnBounds.y }, WHITE); // Draw button frame

}

// Gameplay Screen Unload logic
void UnloadButterflyplayScreen(void)
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
    UnloadTexture(button);  // Unload button texture
    UnloadSound(fxButton);  // Unload sound
    free(samples);   // Unload game samples
}

// Gameplay Screen should finish?
int FinishButterflyplayScreen(void)
{
    return finishScreen;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------
void expandGraphButterfly(int coordMatrix[nodeCounts][2]){
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
