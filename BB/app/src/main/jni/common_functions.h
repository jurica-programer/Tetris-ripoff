/*
 * common_functions.h
 *
 *  Created on: 28. o�u 2016.
 *      Author: Jura
 */

#ifndef COMMON_FUNCTIONS_H_
#define COMMON_FUNCTIONS_H_

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

#define GAME_BLOCK_START_X 4
#define GAME_BLOCK_START_Y 1
#define GAME_BLOCK_SIZE 4
#define MOVE_LEFT -1
#define MOVE_RIGHT 1
#define NO_DATA 0

#define GAME_MAX_ROWS 20

typedef enum block_type_e
{
    i_block,
    t_block,
    n_block,
    z_block,
    l_block,
    j_block,
    s_block,
    num_block
}block_type;

typedef enum rotation_e
{
    up,
    left,
    down,
    right,
    num_rotation
}rotation;

typedef enum tetris_error_e
{
    no_error = 0,
    error,
    end_gameplay
}tetris_error;

typedef enum movement_allow_e
{
    allowed,
    not_allowed
}movement_allow;

typedef struct block_t
{
    short x[4];
    short y[4];
    block_type type;
    rotation rotation;
}block;

struct game_s
{
//TODO ovo zamijenji samo sa jednim shortom
    block block;
    block nextBlock;
    int return_value;
    int gameField[GAME_MAX_ROWS];
    short GameOver;
    sem_t write_semaphore;
    sem_t reading_semaphore;
    int score;
    int level;
    bool isPaused;
    float fallingTimer;
} GameContext;

#endif /* COMMON_FUNCTIONS_H_ */

