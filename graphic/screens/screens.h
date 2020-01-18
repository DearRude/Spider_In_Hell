#ifndef SCREENS_H
#define SCREENS_H

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, Butterfly, Spider, ENDING } GameScreen;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
GameScreen currentScreen;
Font font;
Music music;
int endingStatus;       // 1 - Win, 2 - Lose

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Logo Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitLogoScreen(void);
void UpdateLogoScreen(void);
void DrawLogoScreen(void);
void UnloadLogoScreen(void);
int FinishLogoScreen(void);

//----------------------------------------------------------------------------------
// Title Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitTitleScreen(void);
void UpdateTitleScreen(void);
void DrawTitleScreen(void);
void UnloadTitleScreen(void);
int FinishTitleScreen(void);

//----------------------------------------------------------------------------------
// SpiderPlay Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitSpiderplayScreen(void);
void UpdateSpiderplayScreen(void);
void DrawSpiderplayScreen(void);
void UnloadSpiderplayScreen(void);
int FinishSpiderplayScreen(void);

//----------------------------------------------------------------------------------
// ButterflyPlay Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitButterflyplayScreen(void);
void UpdateButterflyplayScreen(void);
void DrawButterflyplayScreen(void);
void UnloadButterflyplayScreen(void);
int FinishButterflyplayScreen(void);


//----------------------------------------------------------------------------------
// Ending Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitEndingScreen(void);
void UpdateEndingScreen(void);
void DrawEndingScreen(void);
void UnloadEndingScreen(void);
int FinishEndingScreen(void);

#ifdef __cplusplus
}
#endif

#endif // SCREENS_H