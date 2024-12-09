#include <stdio.h>
#include <string>
#include <conio.h>
#include "Menu.h"
#include "TypingSpd.h"
#include "Survival.h"
#include "TypingNinja.h"

using namespace std;

int CurrentMode = 0; // 0>Menu, 1>TS, 2>Sur, 3>TNin

int main() {
    
    
    while (true) {
        // get input
        char buffer[81];
        int i, ch;

        for (i = 0; (i < 80) && ((ch = getchar()) != EOF)
                            && (ch != '\n'); i++)
        {
            buffer[i] = (char) ch;
        }

        // Terminate string with a null character
        buffer[i] = '\0';

        switch (CurrentMode)
        {
        case 0: // Menu
            Menu(&buffer[81]);
            break;
        case 1: // Typing Speed Test
            break;

        case 2: // Survival Mode
            break;

        case 3: // Typing Ninja
            break;
        
        default:
            break;
        }
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