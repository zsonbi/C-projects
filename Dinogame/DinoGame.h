#ifndef DINOGAME_H_INCLUDED
#define DINOGAME_H_INCLUDED

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#else
#include<unistd.h>
#include<pthread.h>
//#define NULL ((void*)0)
#define FALSE 0
#define TRUE 1
#endif


//Board constants
#define GAME_ROW_COUNT 15
#define GAME_COL_COUNT 90

//Game constants
#define BASE_REFRESH_RATE 100
#define OBSTACLE_FREQUENCY 15
#define MIN_DISTANCE_BETWEEN_OBSTACLES 18
#define MAX_CACTUS_HEIGHT 4

//Dino constants
#define DINO_MAX_JUMP_HEIGHT 13
#define STANDING 0
#define DUCKING 1
#define ASCENDING 2
#define DESCENDING 3
#define DINO_COLUMN 3
#define DO_NOTHING 0
#define DUCK 1
#define JUMP 2





typedef struct Dino Dino;
typedef struct Bird Bird;
typedef struct Cactus Cactus;
typedef unsigned char BOOLEAN;
typedef unsigned char BYTE;



void ManageDino(Dino *dino);
BOOLEAN HandleObstacles(Bird **birdHead, Cactus **cactHead, BOOLEAN canSpawn);
void DinoToFloorDucking(Dino *dino);
void DinoToFloorStanding(Dino *dino);

//Stores all the values what a dino should have
struct Dino
{
    //The coords of the dino's bodyparts n*2 -> row index, n*2+1 -> column index
    int coords[6];
    BYTE state;
    BYTE playerInput;
    int score;
    BOOLEAN alive;
    #ifndef _WIN32
    int timeSinceLastInput;
    #endif
};
//Stores all the values what a bird should have
struct Bird
{
    //The coords of the bird's bodyparts n*2 -> row index, n+1 -> column index
    int coords[8];
    Bird *nextBird;
};
//Stores all the values what a Cactus should have
struct Cactus
{
    //The coords of the cactus's parts n*2 -> row index, n+1 -> column index
    int coords[MAX_CACTUS_HEIGHT * 2];
    Cactus *nextCact;
};

unsigned int StartGame(void *inputPtr);

void FreeMemory(Bird** birdHead, Cactus** cactHead);

#endif