#include <stdio.h>
#include <string>
#include <conio.h>

using namespace std;

void RefreshMenu(char GameModeSelect[], string GameModeName[], int GameModesCount, int GameModeSelecting) {
    // clear console
    printf("\033[2J"); // ANSI bla bla bla

    // title
    printf("----------------------------------\nTyping Game 41271107H 郭語新\n----------------------------------\n\n");

    // mode selection
    printf("which mode do you want to play?\n\n");
    for (int i=0;i < GameModesCount;i++) {
        if(i == GameModeSelecting) {printf("\033[31m");}
        printf("%s[%c] ", GameModeName[i], GameModeSelect[i]); // need mod: use the * as select indicator, arrow key to move
        printf("\033[0m");
    }
    printf("\n\n");
    
    // mode info
    printf("----------------------------------\nmode info\n----------------------------------\n\n"); // need mod: show info based on selection
}

int main() {
    // const int FPS = 120;
    // some variable need to move to global
    char MenuInput;
    const int CurrentMode = 0; // 0>Menu, 1>TS, 2>Sur, 3>TNin
    const int GameModesCount = 4;
    const int* GameModesCountPT = &GameModesCount;
    int GameModeSelecting = 0;
    int* GameModeSelectingPT = & GameModeSelecting;
    char GameModeSelect[GameModesCount] = {'\0'}; // a LLM told me I can init an empty char array like this
    string GameModeName[GameModesCount] = {"SpeedTest", "Survival", "TypingNinja", "ExitGame"};

    for (int i=0;i < GameModesCount;i++) {
        GameModeSelect[i] = ' ';
    }
    GameModeSelect[GameModeSelecting] = '*';

    RefreshMenu(GameModeSelect, GameModeName, GameModesCount, GameModeSelecting);

    // game loop
    while(true) {
        // check input
        MenuInput = getch();
        
        // check game mode
        switch (MenuInput)
        {
        case 75: // LEFT
            if (GameModeSelecting > 0) {
                GameModeSelecting -= 1;
            }
            break;
        
        case 77: //RIGHT
            if (GameModeSelecting < 3) {
                GameModeSelecting += 1;
            }
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

/*
INPUT METHOD I GET FROM MICROSOFT C++ REFERANCE

char buffer[81];
int i, ch;

for (i = 0; (i < 80) && ((ch = getchar()) != EOF)
                    && (ch != '\n'); i++)
{
    buffer[i] = (char) ch;
}

// Terminate string with a null character
buffer[i] = '\0';
printf( "Input was: %s\n", buffer);
*/