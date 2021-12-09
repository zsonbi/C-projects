#include "DinoGame.h"

#ifdef _WIN32

DWORD WINAPI StartDinoGame(void *inputPtr)
{
    StartGame(inputPtr);
}

//Start of the code
int main()
{
    Dino player;
Start:
    DinoToFloorStanding(&player);
    player.state = STANDING;
    player.playerInput = DO_NOTHING;
    player.score = 0;
    player.alive = 1;
    //Creates a new thread
    DWORD threadID;
    HANDLE thread = CreateThread(

        NULL, // default security attributes

        0, // use default stack size

        StartDinoGame, // thread function

        (void *)&player, // argument to thread function

        0, // use default creation flags

        &threadID); // returns the thread identifier

    //The interaction for the user
    do
    {
        //Reads in key press
        //Jumping check
        if ((GetAsyncKeyState(87) & (1 << 15)) || (GetAsyncKeyState(38) & (1 << 15)))
        {

            player.playerInput = JUMP;
        }
        //Ducking check
        else if ((GetAsyncKeyState(83) & (1 << 15)) || GetAsyncKeyState(40) & (1 << 15))
        {
            player.playerInput = DUCK;
        }
        //Exit the game
        else if (GetAsyncKeyState(27) & (1 << 15))
        {
            return 0;
        }
        //Do nothing
        else
        {
            player.playerInput = DO_NOTHING;
        }
        Sleep(100);
    } while (player.alive);
    printf("GAME OVER \nScore: %d\n", player.score);
    printf("Press esc to exit or r to retry: ");
    while (1)
    {

        switch (getch())
        {
        case 27:
            return 0;
            break;
        case 114:
            printf("pressed r");
            goto Start;
            break;
        default:
            break;
        }
    }
}
#else
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>

void *StartDinoGame(void *inputPtr)
{
    StartGame(inputPtr);
}

void *ResetKeyPressForPlayer(void *dino)
{
    while (((Dino *)dino)->alive)
    {
        if(((Dino *)dino)->playerInput != DO_NOTHING){
            ((Dino *)dino)->timeSinceLastInput++;
        }
        usleep(40000);
      
    }
}

//Start of the code
int main()
{
    int jndex;
    int result;

    char in_buffer[1];

    struct termios tp1;
    struct termios tp2;

    tcgetattr(0, &tp1);

    tp2 = tp1;

    tp2.c_iflag &= ~ICRNL;
    tp2.c_lflag &= ~ICANON;
    tp2.c_lflag &= ~ECHO;
    tp2.c_cc[VMIN] = 1;
    tp2.c_cc[VTIME] = 0;
    tp2.c_cc[VINTR] = 0xFF;
    tp2.c_cc[VSUSP] = 0xFF;
    tp2.c_cc[VQUIT] = 0xFF;

    tcsetattr(0, TCSANOW, &tp2);



    Dino player;
Start:
    DinoToFloorStanding(&player);
    player.state = STANDING;
    player.playerInput = DO_NOTHING;
    player.score = 0;
    player.alive = 1;
    //Creates a new thread
    pthread_t threadID;
    pthread_t resetThreadID;
    //Creates game thread
   pthread_create(&threadID, NULL, &StartDinoGame, (void *)&player);
    //Creates reset key thread
    pthread_create(&resetThreadID, NULL, &ResetKeyPressForPlayer, (void *)&player);

    do
    {

        in_buffer[0] = 0;
        read(0, in_buffer, 1);

        fflush(stdout);



        switch ((unsigned char)in_buffer[0])
        {
        case 119:
            player.playerInput = JUMP;
            break;

        case 32:
            player.playerInput = JUMP;
            break;

        case 38:
            player.playerInput = JUMP;
            break;

        case 40:
            player.playerInput = JUMP;
            break;

        case 115:
            player.playerInput = DUCK;
            break;
        case 27:
            goto Exit;

        case 114:
        if(!player.alive)
        goto Start;

        default:

            break;
        }
        player.timeSinceLastInput = 0;

        // usleep(20 * 1000);
    } while (1);
    Exit:
    tcsetattr(0, TCSANOW, &tp1);
}

#endif