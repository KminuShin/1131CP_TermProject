#include <stdio.h>
#include <string>
#include <conio.h>

using namespace std;

/*
getch();
switch(getch) {
case left: left
case right: right
case enter: go to that mode
}
*/

const int GameModesCount = 4; //*
const int* GameModesCountPT = &GameModesCount; //*
int GameModeSelecting = 0; //*
int* GameModeSelectingPT = & GameModeSelecting; //*
char GameModeSelect[GameModesCount] = {'\0'}; //* // a LLM told me I can init an empty char array like this
string GameModeName[GameModesCount] = {"SpeedTest", "Survival", "TypingNinja", "ExitGame"}; //*

void Menu(char MenuInput) {
    

    for (int i=0;i < GameModesCount;i++) {
        GameModeSelect[i] = ' ';
    }
    GameModeSelect[GameModeSelecting] = '*';

    RefreshMenu(GameModeSelect, GameModeName, GameModesCount, GameModeSelecting);

    // game loop
    while(true) {
        // check game mode
        switch (MenuInput)
        {
        case 75: // LEFT
            if (GameModeSelecting > 0) {
                GameModeSelecting -= 1;
            }
            break;
        
        case 77: // RIGHT
            if (GameModeSelecting < 3) {
                GameModeSelecting += 1;
            }
            break;

        case 8: // SPACE
            // go to game
            break;

        default:
            break;
        }

        // following code can be simp and merge to the upper code
        for (int i = 0;i < GameModesCount;i++) {
            GameModeSelect[i] = ' ';
        }
        GameModeSelect[GameModeSelecting] = '*';

        // check if time matches FPS (or maybe I can ignore fps? just wait for user input)
        // refresh screen
        RefreshMenu(GameModeSelect, GameModeName, GameModesCount, GameModeSelecting);
    }
}

void RefreshMenu(char GameModeSelect[], string GameModeName[], int GameModesCount, int GameModeSelecting) {
    // clear console
    printf("\033[2J"); // ANSI bla bla bla

    // title
    printf("----------------------------------\nTyping Game 41271107H 郭語新\n----------------------------------\n\n");

    // mode selection
    printf("which mode do you want to play?\n(use \033[33mleft/right arrow key\033[0m to select, \033[1;33mSPACE\033[0m to comfirm)\n\n");
    for (int i=0;i < GameModesCount;i++) {
        if(i == GameModeSelecting) {printf("\033[31m");}
        printf("%s[%c] ", GameModeName[i].c_str(), GameModeSelect[i]); // need mod: use the * as select indicator, arrow key to move
        printf("\033[0m");
    }
    printf("\n\n");
    
    // mode info
    printf("----------------------------------\nmode info\n----------------------------------\n\n"); // need mod: show info based on selection
}