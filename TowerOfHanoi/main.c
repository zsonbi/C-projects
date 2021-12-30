#include <stdio.h>
#include "../Stack/Stack.h"
#include <stdlib.h>
#include <time.h>
// Make it windows and Linux compatible
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Moves a brick from one tower (sourceTower) to an another tower (destTower)
void Move(Stack *towers, int brickCount, unsigned char sourceTower, unsigned char destTower)
{
    // Error detection
    if (GetStackCount(&towers[sourceTower]) == 0)
    {
        printf("ERROR source stack (%d) is empty can't move", sourceTower);
        return;
    }

    // Save the value
    int val = Pop(&towers[sourceTower]);
    // Make it windows and Linux compatible
#ifdef _WIN32

    // Deletes the brick at the top of the source tower
    COORD Coord;
    Coord.X = 2 + (sourceTower * 4);
    Coord.Y = brickCount - GetStackCount(&towers[sourceTower]);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
    printf("   ");

    // Gives the brick to the destination tower and prints it there
    Push(&towers[destTower], val);
    Coord.X = 2 + (destTower * 4);
    Coord.Y = (brickCount - GetStackCount(&towers[destTower]) + 1);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);

#else
    // Deletes the brick at the top of the source tower
    printf("\033[%d;%dH", brickCount - GetStackCount(&towers[sourceTower])+1, 3 + (sourceTower * 4));
    printf("   ");
Push(&towers[destTower], val);
    // Gives the brick to the destination tower and prints it there
    printf("\033[%d;%dH", brickCount - GetStackCount(&towers[destTower])+2, 3 + (destTower * 4));

#endif
    printf("%d", val);
}

// Generate the towers
void GenerateTowers(Stack **towers, unsigned char towerCount, int brickCount, unsigned char randomized)
{
    // Allocates memory for all the towers
    (*towers) = malloc(sizeof(Stack) * towerCount);
 
    //Clear the screen
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
 
 
    for (size_t i = 0; i < towerCount; i++)
    {
        InitStack(&((*towers)[i]));
    }
    // If it is randomized create the towers randomly
    if (randomized)
    {
        srand(time(0));
        for (size_t i = brickCount; i > 0; i--)
        {
            // Selects a random tower
            int tower = rand() % towerCount;

            Push(&((*towers)[tower]), i);

            // Make it windows and Linux compatible
#ifdef _WIN32
            // Prints out the element at the specific coordinate on the console
            COORD Coord;
            Coord.X = 2 + (tower)*4;
            Coord.Y = (brickCount - GetStackCount(&(*towers)[tower]) + 1);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);

#else
            printf("\033[%d;%dH", brickCount - GetStackCount(&(*towers)[tower]) + 2, 2 + (tower)*4 + 1);
#endif
            printf("%d", i);
        }
    }
    // Otherwise make it at the first tower
    else
    {
        for (size_t i = brickCount; i > 0; i--)
        {

            Push(&(*towers)[0], i);
            // Make it windows and Linux compatible
#ifdef _WIN32
            // Prints out the element at the specific coordinate on the console
            COORD Coord;
            Coord.X = 2;
            Coord.Y = i;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
#else
            printf("\033[%d;%dH", i + 1, 2 + 1);

#endif
            printf("%d", i);
        }
    }
}

// Builds a small tower recursively
void BuildSmallTower(Stack *towers, unsigned char towerCount, int brickCount, int n, unsigned char sourceTower, unsigned char auxTower, unsigned char destTower)
{
    if (n > 0)
    {
        BuildSmallTower(towers, towerCount, brickCount, n - 1, sourceTower, destTower, auxTower);
        // Make it windows and Linux compatible
#ifdef _WIN32
        Sleep(10);
#else
       usleep(250);
#endif
        Move(towers, brickCount, sourceTower, destTower);
        BuildSmallTower(towers, towerCount, brickCount, n - 1, auxTower, sourceTower, destTower);
    }
}

// Solves the tower of hanoi to n number of towers (not the most effiecient way, but mine)
void Solve(Stack *towers, unsigned char towerCount, int brickCount, unsigned char targetTower)
{
    int currBrickCount = brickCount;
    int bricksOnEachSMallTower = brickCount / (towerCount - 2);
    unsigned char permaAux = targetTower == 1 ? 2 : 1;
    // Divide it
    for (size_t i = 2; i < towerCount; i++)
    {
        if (i == targetTower)
        {
            continue;
        }

        currBrickCount -= bricksOnEachSMallTower;

        BuildSmallTower(towers, towerCount, brickCount, bricksOnEachSMallTower, 0, permaAux, i);
    }

    // Move everything from the start to the target
    BuildSmallTower(towers, towerCount, brickCount, currBrickCount, 0, permaAux, targetTower);
    // Stack every small tower on top of the target
    for (size_t i = towerCount - 1; i >= 2; i--)
    {
        if (i == targetTower)
        {
            continue;
        }
        BuildSmallTower(towers, towerCount, brickCount, bricksOnEachSMallTower, i, permaAux, targetTower);
    }
}

// Start of the program
int main(int argc, char *argv[])
{
    unsigned char towerCount = 3;
    int brickCount = 20;
    unsigned char randomized = 0;
    int targetTower = 2;

    // For different number of parameters
    switch (argc)
    {
    case 1:
        printf("Using default parameters: Number of towers: %d, Number of bricks: %d, Target tower: %d", towerCount, brickCount, targetTower);
        break;
    case 2:
        towerCount = atoi(argv[1]);
        break;
    case 3:
        towerCount = atoi(argv[1]);
        brickCount = atoi(argv[2]);
        break;
    case 4:
        towerCount = atoi(argv[1]);
        brickCount = atoi(argv[2]);
        targetTower = atoi(argv[3]);
        break;
    default:
        printf("Invalid input parameters");
        return 1;
        break;
    }
    // Generate a new board
    Stack *towers;
    GenerateTowers(&towers, towerCount, brickCount, randomized);

    // Solve it
    Solve(towers, towerCount, brickCount, targetTower);

    // Free the memory
    for (size_t i = 0; i < towerCount; i++)
    {
        DeleteStack(&towers[i]);
    }
    free(towers);

    return 0;
}
