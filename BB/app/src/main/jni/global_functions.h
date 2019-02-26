#ifndef GLOBAL_FUNCTIONS_H_
#define GLOBAL_FUNCTIONS_H_

#include "blocks.h"
#include "common_functions.h"

void init_game_res(void);
tetris_error terminate_game_res(void);

int getScoreValue(void);

void *game_loop_thread(void *arg);
void *game_falling_thread(void *arg);
void startThread(void);
void pauseContinue(void);
int resetGame(void);

#endif
