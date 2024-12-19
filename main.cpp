#include <stdio.h>
#include <string>
#include <conio.h>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include "Menu.h"
#include "TypingSpd.h"
#include "Survival.h"
#include "TypingNinja.h"

using namespace std; // to simpfly std::string, sry I use it even though I (don't and don't have time to) understand it

/* variables I plan to use
// Global
int CurrentMode
int gameModesCount = 4
string gameModesName[gameModesCount] = {"Typing Speed", "Survival", "Typing Ninja", "Exit"};

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

int currentMode = 0; // 0>Menu, 1>TS, 2>Sur, 3>TNin, 4>Exit
const int gameModesCount = 4;
const string gameModesName[gameModesCount] = {"Typing Speed", "Survival", "Typing Ninja", "Exit"};
const int wordBankWordsCount = 247;
const string wordBank[wordBankWordsCount] = {"the", "of", "and", "to", "a", "in", "that", "is", "was", "for", "on", "with", "as", "at", "all", "this", "have", "had", "it", "but", "not", "or", "from", "by", "be", "are", "his", "her", "they", "their", "what", "which", "who", "so", "up", "out", "down", "into", "over", "through", "more", "most", "some", "such", "no", "than", "can", "could", "may", "should", "would", "will", "about", "after", "before", "during", "since", "while", "because", "although", "however", "therefore", "nevertheless", "furthermore", "moreover", "besides", "also", "too", "very", "really", "quite", "rather", "fairly", "pretty", "extremely", "incredibly", "absolutely", "totally", "completely", "entirely", "partly", "somewhat", "kindly", "gently", "slowly", "quickly", "easily", "hardly", "scarcely", "barely", "often", "usually", "sometimes", "occasionally", "seldom", "rarely", "never", "always", "oftentimes", "frequently", "generally", "normally", "typically", "usually", "commonly", "particularly", "especially", "mainly", "primarily", "chiefly", "largely", "mostly", "almost", "nearly", "quite", "rather", "fairly", "pretty", "extremely", "incredibly", "absolutely", "totally", "completely", "entirely", "partly", "somewhat", "kindly", "gently", "slowly", "quickly", "easily", "hardly", "scarcely", "barely", "often", "usually", "sometimes", "occasionally", "seldom", "rarely", "never", "always", "oftentimes", "frequently", "generally", "normally", "typically", "usually", "commonly", "particularly", "especially", "mainly", "primarily", "chiefly", "largely", "mostly", "almost", "nearly", "quite", "rather", "fairly", "pretty", "extremely", "incredibly", "absolutely", "totally", "completely", "entirely", "partly", "somewhat", "kindly", "gently", "slowly", "quickly", "easily", "hardly", "scarcely", "barely", "often", "usually", "sometimes", "occasionally", "seldom", "rarely", "never", "always", "oftentimes", "frequently", "generally", "normally", "typically", "usually", "commonly", "particularly", "especially", "mainly", "primarily", "chiefly", "largely", "mostly", "almost", "nearly", "quite", "rather", "fairly", "pretty", "extremely", "incredibly", "absolutely", "totally", "completely", "entirely", "partly", "somewhat", "kindly", "gently", "slowly", "quickly", "easily", "hardly", "scarcely", "barely", "often", "usually", "sometimes", "occasionally", "seldom", "rarely", "never", "always", "oftentimes", "frequently", "generally", "normally", "typically", "usually", "commonly", "particularly", "especially", "mainly", "primarily", "chiefly", "largely", "mostly", "almost", "nearly", "quite"}; // gen by gemini 1.5 flash, thanks
const int genCounts = 350; // generate random number queue of 350
int wordBankRandQueue[genCounts] = {0};
const auto gameRuleRemainTime = 60*1000;
auto gameRuleEndTime = chrono::steady_clock::now() + chrono::milliseconds(gameRuleRemainTime);
const int wordsCountInALine = 6;
string gameInputWord;
int wpm = 0, cpm = 0;
int clicks = 0;
int finishedWords = 0;
int wrongWords = 0;
int gameInput;
int gameInputIsWrong = 0;


int IsTimeRemain() {
    return chrono::steady_clock::now() < gameRuleEndTime;
}
void TimerReset() {
    gameRuleEndTime = chrono::steady_clock::now() + chrono::milliseconds(gameRuleRemainTime);
}
void RefreshMenu(int selectMode) {
    // clear console
    printf("\033[2J"); // ANSI bla bla bla

    // title
    printf("----------------------------------\nTyping Game 41271107H 郭語新\n----------------------------------\n\n");

    // mode selection
    printf("which mode do you want to play?\n(use \033[33mleft/right arrow key\033[0m to select, \033[1;33mSPACE\033[0m to comfirm)\n\n");
    for (int i=0;i < gameModesCount;i++) {
        if(i == selectMode) {printf("\033[31m");}
        printf("%s ", gameModesName[i].c_str());
        printf("\033[0m");
    }
    printf("\n\n");
}
void InitGame() {
    // generate random number queue of 350, since the world record is 305, longest string is 12 char
    for (int i=0;i < genCounts;i ++) {
        wordBankRandQueue[i] = rand() % wordBankWordsCount;
    }

    // reset finished words
    finishedWords = 0;

    // create two queue, one for current 6 words, another for next 6 words, %-16s to margin left
    // currentWordQueue = wordQueueA;
    // nextWordQueue = wordQueueB;

    // reset wpm count
    clicks = 0;
    finishedWords = 0;
    wrongWords = 0;

    // set timer
    TimerReset();
}
void RefreshTSPD() {
    // clear console
    printf("\033[2J"); // ANSI bla bla bla

    // title
    printf("----------------------------------\nTyping Speed Test 41271107H 郭語新\n----------------------------------\n\n");

    // remain time
    printf("remain time: %lld\n\n", std::chrono::duration_cast<std::chrono::seconds>(gameRuleEndTime - std::chrono::steady_clock::now()).count());
    
    // indicater
    printf("input words: %d, wrong words: %d\n\n", finishedWords, wrongWords);
    
    // first line of words
    for (int i=0;i < wordsCountInALine;i++) {
        printf("%s ", wordBank[wordBankRandQueue[finishedWords+i]].c_str());
    }
    printf("\n");

    // user input
    printf("%s ", gameInputWord.c_str());
    
    // indicate wrong words
    if (gameInputIsWrong) {
        printf (" (x)");
    }

    // debug
    if (gameInputIsWrong || (gameInputWord.length() != wordBank[wordBankRandQueue[finishedWords]].length())) {
        printf(" (len)");
    }

    printf("\n\n");
}
void RefreshGameEnd() {
    // clear console
    printf("\033[2J"); // ANSI bla bla bla

    // title
    printf("----------------------------------\nTyping Speed Test 41271107H 郭語新\n----------------------------------\n\n");

    // remain time
    printf("Times Up!! \n\n");
    
    // wpm status
    printf ("clicks per minute: %d, input words: %d, wrong words: %d,\nwords per minute: %d\n\n", clicks, finishedWords, wrongWords, finishedWords - wrongWords);

    // back 2 menu
    printf("press ENTER to go back to menu\n");
}
/* functions I plan to use
char GetUsrInput() {
    return ;
}

string GetRandWord() {
    return ;
}
*/

int main() {
    // init game
    srand(time(0));

    // Global variable set
    currentMode = 0;
    
    // Menu variable
    int selectMode = 0;
    int inputMenuCh;
    int selectModeChange = 0;

    // Refresh Screen
    RefreshMenu(selectMode);

    // game loop
    while (true) {
        // detect mode
        if (currentMode == 4) { // Exit
            break;
        }
        switch (currentMode)
        {
        case 0: // Menu
            
            // detect input
            inputMenuCh = getch();
            switch (inputMenuCh)
            {
            case 75: // LEFT
                if (selectMode > 0) {
                    selectMode -= 1;
                    selectModeChange = 1;
                }
                break;
            
            case 77: // RIGHT
                if (selectMode < 3) {
                    selectMode += 1;
                    selectModeChange = 1;
                }
                break;

            case ' ': // SPACE
                if (selectMode == 3) {
                    currentMode = 4;
                } else {
                    currentMode = selectMode + 1;
                    InitGame();
                }
                
                break;

            default:
                selectModeChange = 0;
                break;
            }
            // refresh screen
            RefreshMenu(selectMode);
            // printf("%d", inputMenuCh);

            break;
        
        case 1: // Typing Speed
            while (IsTimeRemain()) {
                RefreshTSPD();

                /*rules:
                current word: the one word typing
                current word num: indicates the number of word in the line(queue)
                current line: the line(queue) of word typing
                next line: the upcomming line(queue) of word
                */
                // get input
                // if input == ' '
                // >> if current word num >= 5 (last)
                // >> >> current line and next line change
                // >> >> next line = next 6 words
                // >> >> current word num = 0
                // >> >> if isWrong
                // >> >> >> wrong word count += 1
                // >> >> isWrong = 0
                // >> else
                // >> >> current word num += 1
                // else if input == BACKSPACE
                // >> pop last input char
                // else
                // >> compare each char
                // >> if different
                // >> >> print in red
                // >> >> isWrong = 1
                // >> else 
                // >> >> isWrong = 0

                gameInput = getch();
                clicks += 1;
                if (gameInput == '\b') {
                    if (gameInputWord.length() > 0) {
                        gameInputWord.pop_back();
                    }
                } else if (gameInput == ' ') {
                    if (gameInputIsWrong || (gameInputWord.length() != wordBank[wordBankRandQueue[finishedWords]].length())) {
                        wrongWords += 1;
                    }
                    finishedWords += 1;
                    gameInputWord = "";
                } else {
                    gameInputWord += gameInput;
                }

                // compare chars
                for (int i=0;i < gameInputWord.length();i++) {
                    if (gameInputWord[i] != wordBank[wordBankRandQueue[finishedWords]][i]) {
                        gameInputIsWrong = 1;
                        break;
                    }
                    gameInputIsWrong = 0;
                }

                RefreshTSPD();
            }
            RefreshGameEnd();
            inputMenuCh = getch();
            if (inputMenuCh == '\n' || inputMenuCh == '\r') {
                currentMode = 0;
                selectMode = 0;
                RefreshMenu(selectMode);
            }
            break;
        
        case 2: // Survival
            while (IsTimeRemain()) {
                // clear console
                printf("\033[2J"); // ANSI bla bla bla

                // title
                printf("----------------------------------\nTyping Game 41271107H 郭語新\n----------------------------------\n\n");

                // mode selection
                printf("sorry, I didn't finish this mode, press \033[1;33mSPACE\033[0m to go back to menu\n\n");

                inputMenuCh = getch();
                if (inputMenuCh == ' ') {
                    currentMode = 0;
                    selectMode = 0;
                    RefreshMenu(selectMode);
                    break;
                }
            }
            break;
        
        case 3: // Typing Ninja
            while (IsTimeRemain()) {
                // clear console
                printf("\033[2J"); // ANSI bla bla bla

                // title
                printf("----------------------------------\nTyping Game 41271107H 郭語新\n----------------------------------\n\n");

                // mode selection
                printf("sorry, I didn't finish this mode, press \033[1;33mSPACE\033[0m to go back to menu\n\n");

                inputMenuCh = getch();
                if (inputMenuCh == ' ') {
                    currentMode = 0;
                    selectMode = 0;
                    RefreshMenu(selectMode);
                    break;
                }
            }
            break;
        
        default: // exception: back to Menu
            currentMode = 0;
            break;
        }
    }
    
    /* OLD CODE BELOW, DON'T TOUCH
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

/* INPUT METHOD I GET FROM MICROSOFT C++ REFERANCE

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