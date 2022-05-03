#include "DinoGame.h"
// Starts a new game on an another thread inputPtr is to the player's dino
unsigned int StartGame(void *inputPtr)
{
#ifdef _WIN32
    // Clears the screen
    system("cls");
#else
    // Clears the screen
    system("clear");
#endif

    float refreshMultiplier = 1.0; // How quick should the game move
    Dino *player = ((Dino *)inputPtr);
    Cactus *cactHead = NULL; // A pointer to the nearest cactus
    Bird *birdHead = NULL;   // A pointer to the nearest bird
    int lastObstacle = 0;
#ifdef _WIN32
    COORD Coord;
#endif
    char board[GAME_ROW_COUNT][GAME_COL_COUNT];

    // Reset the values in the board 2d array to ' '
    for (int i = 0; i < GAME_ROW_COUNT; i++)
    {
        for (int j = 0; j < GAME_COL_COUNT; j++)
        {
            board[i][j] = ' ';
        }
    }

    // Add the string terminator character at the end of each line
    for (int i = 0; i < GAME_ROW_COUNT; i++)
    {
        board[i][GAME_COL_COUNT - 1] = '\0';
    }

    // Creates the floor for the game
    for (int i = 0; i < GAME_COL_COUNT - 1; i++)
    {
        board[(GAME_ROW_COUNT - 1)][i] = '^';
    }

    // Print our the whole board
    for (int i = 0; i < GAME_ROW_COUNT; i++)
    {
        printf("%s\n", board[i]);
    }

    // The game cyle itself
    do
    {

        #ifndef _WIN32
        // Clears the screen
        system("clear");
        #endif

        // Erase the dino
        for (int i = 0; i < 5; i += 2)
        {
            board[player->coords[i]][player->coords[i + 1]] = ' ';
            // Remove the dino from the console
#ifdef _WIN32
            Coord.X = (*player).coords[i + 1];
            Coord.Y = (*player).coords[i];
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
       printf(" ");
#endif

     
        }
        // Move the dino
        ManageDino(player);

        // Erase birds
        Bird *tempBirdPointer = birdHead;
        while (tempBirdPointer != NULL)
        {
            for (int i = 0; i < 8; i += 2)
            {
                board[tempBirdPointer->coords[i]][tempBirdPointer->coords[i + 1]] = ' ';
                // Remove the birds from the console
#ifdef _WIN32
                Coord.X = tempBirdPointer->coords[i + 1];
                Coord.Y = tempBirdPointer->coords[i];
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
                printf(" ");
#endif

            }
            tempBirdPointer = tempBirdPointer->nextBird;
        }

        // Erase cactuses
        Cactus *tempCactPointer = cactHead;

        while (tempCactPointer != NULL)
        {
            for (int i = 0; i < MAX_CACTUS_HEIGHT * 2; i += 2)
            {
                if (tempCactPointer->coords[i] != -1)
                {
                    board[tempCactPointer->coords[i]][tempCactPointer->coords[i + 1]] = ' ';

                    // Remove the cactuses from the console
#ifdef _WIN32
                    Coord.X = tempCactPointer->coords[i + 1];
                    Coord.Y = tempCactPointer->coords[i];
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
                               printf(" ");
                               #endif
         
                }
            }
            tempCactPointer = tempCactPointer->nextCact;
        }

        // Spawn and delete obstacles
        if (HandleObstacles(&birdHead, &cactHead, lastObstacle > MIN_DISTANCE_BETWEEN_OBSTACLES))
        {
            lastObstacle = 0;
        }
        else
        {
            lastObstacle++;
        }

        // Set the birds in the board array
        tempBirdPointer = birdHead;

        while (tempBirdPointer != NULL)
        {
            for (int i = 0; i < 8; i += 2)
            {
                board[tempBirdPointer->coords[i]][tempBirdPointer->coords[i + 1]] = '<';

                // Draw the birds to the console
#ifdef _WIN32
                Coord.X = tempBirdPointer->coords[i + 1];
                Coord.Y = tempBirdPointer->coords[i];
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
    printf("<");
#endif
            
            }
            tempBirdPointer = tempBirdPointer->nextBird;
        }

        // Set the cactuses in the board array
        tempCactPointer = cactHead;
        while (tempCactPointer != NULL)
        {
            for (int i = 0; i < MAX_CACTUS_HEIGHT * 2; i += 2)
            {
                if (tempCactPointer->coords[i] != -1)
                {
                    board[tempCactPointer->coords[i]][tempCactPointer->coords[i + 1]] = '%';

                    // Draw the cactuses to the console
#ifdef _WIN32
                    Coord.X = tempCactPointer->coords[i + 1];
                    Coord.Y = tempCactPointer->coords[i];
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
            printf("%%");
#endif
        
                }
            }

            tempCactPointer = tempCactPointer->nextCact;
        }

        // Set the Dino in the board array
        for (int i = 0; i < 5; i += 2)
        {
            // Collision detection
            if (board[player->coords[i]][player->coords[i + 1]] != ' ')
            {
                FreeMemory(&birdHead, &cactHead);
                player->alive = 0;
#ifndef _WIN32
                printf("GAME OVER \nScore: %d \n press r to restart or esc to exit\n", player->score);
#endif
                return 0;
            }
            board[player->coords[i]][player->coords[i + 1]] = 'D';

            // Draw the dino to the console
#ifdef _WIN32
            Coord.X = (*player).coords[i + 1];
            Coord.Y = (*player).coords[i];
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
         printf("D");
#endif
   
        }

// Park the cursor at the right bottom side
#ifdef _WIN32
        Coord.X = GAME_COL_COUNT;
        Coord.Y = GAME_ROW_COUNT;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
#else
    // Print our the whole board
    for (int i = 0; i < GAME_ROW_COUNT; i++)
    {
        printf("%s\n", board[i]);
    }
#endif

        // Wait till the next frame update
#ifdef _WIN32
        Sleep((unsigned long)(refreshMultiplier * BASE_REFRESH_RATE));
#else
        system("ps u");
        usleep((unsigned long)(refreshMultiplier * BASE_REFRESH_RATE) * 1000);
#endif

        if (refreshMultiplier >= 0.4f)
        {
            refreshMultiplier *= 0.995f;
        }
        player->score++;
    } while (1);
    return 1;
}

//---------------------------------------------------------------------------------
// Frees the memory which was allocated to the obstacles
void FreeMemory(Bird **birdHead, Cactus **cactHead)
{
    Bird *tempBirdPtr;
    while ((*birdHead) != NULL)
    {
        tempBirdPtr = (*birdHead)->nextBird;
        free((*birdHead));
        (*birdHead) = tempBirdPtr;
    }

    Cactus *tempCactPtr;
    while ((*cactHead) != NULL)
    {
        tempCactPtr = (*cactHead)->nextCact;
        free((*cactHead));
        (*cactHead) = tempCactPtr;
    }
}

//-----------------------------------------------------------------------------
// Creates a new bird
void CreateNewBird(Bird **newBird)
{
    (*newBird) = (Bird *)malloc(sizeof(Bird));
    (*newBird)->nextBird = NULL;
    int rowOffSet = (rand() % ((GAME_ROW_COUNT - 1) - 2)) + 1;
    (*newBird)->coords[0] = rowOffSet;
    (*newBird)->coords[1] = GAME_COL_COUNT - 3;
    (*newBird)->coords[2] = rowOffSet;
    (*newBird)->coords[3] = GAME_COL_COUNT - 2;
    // Top of the bird
    (*newBird)->coords[4] = rowOffSet - 1;
    (*newBird)->coords[5] = GAME_COL_COUNT - 2;
    // Bottom of the bird
    (*newBird)->coords[6] = rowOffSet + 1;
    (*newBird)->coords[7] = GAME_COL_COUNT - 2;
}

//----------------------------------------------------------------------------
// Creates a new cactus
void CreateNewCactus(Cactus **newCact)
{
    (*newCact) = (Cactus *)malloc(sizeof(Cactus));
    (*newCact)->nextCact = NULL;
    int cactusHeight = rand() % MAX_CACTUS_HEIGHT;
    // Set the cactus's coords
    for (int i = 0; i < MAX_CACTUS_HEIGHT * 2; i += 2)
    {
        if (i <= cactusHeight * 2)
        {
            (*newCact)->coords[i] = (GAME_ROW_COUNT - 1) - 1 - (i / 2);
            (*newCact)->coords[i + 1] = GAME_COL_COUNT - 2;
        }
        else
        {
            (*newCact)->coords[i] = -1;
            (*newCact)->coords[i + 1] = -1;
        }
    }
}
//-----------------------------------------------------------------------------------------
// Manages the obstacles spawning, moving and deleting
BOOLEAN HandleObstacles(Bird **birdHead, Cactus **cactHead, BOOLEAN canSpawn)
{
    // Moves the birds left
    for (Bird *ptr = (*birdHead); ptr != NULL; ptr = ptr->nextBird)
    {
        for (int i = 1; i < 8; i += 2)
        {
            ptr->coords[i]--;
        }
    }

    // Moves cactuses left
    for (Cactus *ptr = (*cactHead); ptr != NULL; ptr = ptr->nextCact)
    {
        for (int i = 1; i < MAX_CACTUS_HEIGHT * 2; i += 2)
        {
            if (ptr->coords[i] != -1)
            {
                ptr->coords[i]--;
            }
        }
    }

    // Free them from memory if they're already gone
    if ((*birdHead) != NULL && (*birdHead)->coords[1] == 0)
    {
        Bird *birdPtr = (*birdHead);
        (*birdHead) = (*birdHead)->nextBird;
        free(birdPtr);
    }
    if ((*cactHead) != NULL && (*cactHead)->coords[1] == 0)
    {
        Cactus *cactPtr = (*cactHead);
        (*cactHead) = (*cactHead)->nextCact;
        free(cactPtr);
    }

    int rndNum = rand();
    // Spawn the obstacles
    if (canSpawn && rndNum % (OBSTACLE_FREQUENCY * 2) <= 1)
    {

        if (rndNum % 2 == 0)
        {
            // If it's the first in the chain
            if ((*birdHead) == NULL)
            {
                CreateNewBird(birdHead);
            }
            else
            {
                Bird *tempPtr = (*birdHead);
                while (tempPtr->nextBird != NULL)
                {
                    tempPtr = tempPtr->nextBird;
                }
                CreateNewBird(&(tempPtr->nextBird));
            }
        }
        else
        {
            // If it's the first in the chain
            if ((*cactHead) == NULL)
            {
                CreateNewCactus(cactHead);
            }
            else
            {
                Cactus *tempPtr = (*cactHead);
                while (tempPtr->nextCact != NULL)
                {
                    tempPtr = tempPtr->nextCact;
                }
                CreateNewCactus(&(tempPtr->nextCact));
            }
        }
        return TRUE;
    }
    return FALSE;
}

//-------------------------------------------------------------------------------------
// Changes dino's coord's to ducking state
void DinoToFloorDucking(Dino *dino)
{
    dino->coords[0] = (GAME_ROW_COUNT - 1) - 1;
    dino->coords[1] = DINO_COLUMN;
    dino->coords[2] = (GAME_ROW_COUNT - 1) - 1;
    dino->coords[3] = DINO_COLUMN + 1;
    dino->coords[4] = (GAME_ROW_COUNT - 1) - 1;
    dino->coords[5] = DINO_COLUMN + 2;
}

//----------------------------------------------------------------------------------------
// Changes dino's coord to standing state
void DinoToFloorStanding(Dino *dino)
{
    dino->coords[0] = (GAME_ROW_COUNT - 1) - 1;
    dino->coords[1] = DINO_COLUMN;
    dino->coords[2] = (GAME_ROW_COUNT - 1) - 1;
    dino->coords[3] = DINO_COLUMN + 1;
    dino->coords[4] = (GAME_ROW_COUNT - 1) - 2;
    dino->coords[5] = DINO_COLUMN + 1;
}

//-----------------------------------------------------------------------------------------------------------------
// Manages the dinos state. Poor guy has to go through a lot of things just like jews in the minefield
void ManageDino(Dino *dino)
{

    switch (dino->playerInput)
    {
    case DUCKING:
        dino->state = DUCKING;
        break;
    case JUMP:
        if (dino->state == DESCENDING)
        {
            break;
        }
        else
        {
            if (dino->state == DUCKING)
            {
                DinoToFloorStanding(dino);
            }
            dino->state = ASCENDING;
        }

        break;

    case DO_NOTHING:

        if (dino->state == DUCKING)
        {
            dino->state = STANDING;
        }
        else if (dino->state == ASCENDING)
        {
            dino->state = DESCENDING;
        }
        break;

    default:
        break;
    }

#ifndef _WIN32
    if (dino->timeSinceLastInput > 5)
    {
        dino->playerInput = DO_NOTHING;
    }
#endif
    if (dino->state == DUCKING)
    {
        DinoToFloorDucking(dino);
    }
    else if (dino->state == STANDING)
    {
        DinoToFloorStanding(dino);
    }
    // Handle the falling and jumping
    else
    {

        if (dino->state == DESCENDING && dino->coords[0] == (GAME_ROW_COUNT - 1) - 1)
        {
            dino->state = STANDING;
            return;
        }
        else if (dino->coords[0] == (GAME_ROW_COUNT - 1) - DINO_MAX_JUMP_HEIGHT)
        {
            dino->state = DESCENDING;
        }

        for (int i = 0; i < 5; i += 2)
        {
            if (dino->state == ASCENDING)
            {
                dino->coords[0 + i]--;
            }
            else
            {
                dino->coords[0 + i]++;
            }
        }
    }
}
