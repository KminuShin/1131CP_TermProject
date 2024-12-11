#include <stdio.h>
#include <string>
#include <conio.h>
#include "Menu.h"
#include "TypingSpd.h"
#include "Survival.h"
#include "TypingNinja.h"

using namespace std; // to simpfly std::string, sry I use it even though I (don't and don't have time to) understand it

/*
// Global
int CurrentMode

// Menu
int SelctMode

// WordBank and InputBank
const string WordBank[] = { <ChatGPT can help> }
stack UsrInputGame
stack WordBankGame
string wordBankGame[]
string target[] // for Ninja500

// Input
char InputMenuBuffer[]
int InputMenuI, InputMenuCh
char InputBufferGame[]
char InputGame

// Player Score
int WPM // maybe float
int CPM
int WrongWords
int EnterWords
int clicks

// Timer // maybe I have to convert to millis
const int RoundTimeGame = 60
const int RoundTimeSurv = 5
int SysTimeStart
int SysTimeNow
int RoundTime

*/

int currentMode = 0; // 0>Menu, 1>TS, 2>Sur, 3>TNin

char GetUsrInput() {
    return ;
}

string GetRandWord() {
    return ;
}

//

int main() {

    // Menu variable
    char inputMenuBuffer[81];
    int inputMenuI, inputMenuCh;

    // init game
    // detect mode
    switch (currentMode)
    {
    case 0: // Menu
        
        // detect input
        char buffer[81];
        int i, ch;

        for (i = 0; (i < 80) && ((ch = getchar()) != EOF)
                            && (ch != '\n'); i++)
        {
            buffer[i] = (char) ch;
        }

        // Terminate string with a null character
        buffer[i] = '\0';

        while (true) {
            char buffer[81];
            int i, ch;

            for (i = 0; (i < 80) && ((ch = getchar()) != EOF)
                                && (ch != '\n'); i++)
            {
                buffer[i] = (char) ch;
            }

            // Terminate string with a null character
            buffer[i] = '\0';
        }

        // if mode change, redraw display
        break;
    
    case 1: // Typing Speed
        /* code */
        break;
    
    case 2: // Survival
        /* code */
        break;
    
    case 3: // Typing Ninja
        /* code */
        break;
    
    default: // exception: back to Menu
        currentMode = 0;
        break;
    }

    
    // OLD CODE BELOW, DON'T TOUCH
    /*
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
            // Menu(&buffer[81]);
            // get input
            // check selection on mode
            // check space clicked
                // if true, go to that mode
            break;
        case 1: // Typing Speed Test
            
            // INIT
                // 1. select random words
                // 2. reset timer, wpm, usr stack
            
            // get input
            // add to usr stack
            // add word bank words to wrd stack
            // compare two stack:
            // check sys_time
            // if timeout: quit, show score
            // display title & time > word bank > input > correction > next line of word bank
            break;

        case 2: // Survival Mode
            
            // INIT
                // 1. select random words
                // 2. reset timer, wpm, usr stack, level
            
            // get input
            // add to usr stack
            // add word bank words to wrd stack
            // compare two stack:
            // check sys_time
            // if usr wpm < target: quit, show score
            // if round time > 5: level++
            // display, same as TS
            break;

        case 3: // Typing Ninja
            
            // INIT
                // 1. select random words, target words
                // 2. reset timer, wpm, usr stack
            
            // get input
            // add to usr stack
            // add word bank words to wrd stack
                // oh shit I need to make time table for every words (or at least the words showned)
            // compare two stack:
            // check sys_time
            break;
        
        default:
            break;
        }
    }
    */
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