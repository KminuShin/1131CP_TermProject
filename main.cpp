#include <stdio.h>
#include <string>

void RefreshMenu(char GameModeSelect[], std::string GameModeName[], int GameModesCount) {
    // clear console
    printf("\033[2J");

    // title
    printf("----------------------------------\nTyping Game 41271107H 郭語新\n----------------------------------\n\n");

    // mode selection
    printf("which mode do you want to play?\n\n");
    for (int i=0;i < GameModesCount;i++) {
        printf("%s[%c] ", GameModeName[i], GameModeSelect[i]); // need mod: use the * as select indicator, arrow key to move
    }
    printf("\n\n");
    
    // mode info
    printf("----------------------------------\nmode info\n----------------------------------\n\n"); // need mod: show info based on selection
}

int main() {
    // const int FPS = 120;
    int debugA;
    const int GameModesCount = 4;
    const int* GameModesCountPT = &GameModesCount;
    int GameModeSelecting = 0;
    char GameModeSelect[GameModesCount] = {'\0'}; // a LLM told me I can init an empty char array like this
    std::string GameModeName[GameModesCount] = {"SpeedTest", "Survival", "TypingNinja", "ExitGame"};

    for (int i=0;i < GameModesCount;i++) {
        GameModeSelect[i] = ' ';
    }
    GameModeSelect[GameModeSelecting] = '*';

    // game loop
    while(true) {
        // check input
        debugA = getchar();
        
        // check game mode
        for (int i = 0;i < GameModesCount;i++) {
            GameModeSelect[i] = ' ';
        }
        GameModeSelect[GameModeSelecting] = '*';

        // check if time matches FPS (or maybe I can ignore fps? just wait for user input)
        // refresh screen
        RefreshMenu(GameModeSelect, GameModeName, GameModesCount);
        printf("@debug: input is %d\n", debugA);
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