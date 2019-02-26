#ifndef BLOCKS_H_
#define BLOCKS_H_

#include "common_functions.h"

tetris_error make_block(void);
void touchdown(void);
movement_allow move_block(int data);
tetris_error slam_block(void);
tetris_error block_fall(void);

bool getFieldValue(int row, int column);
void rotate_block(void);
tetris_error check_rotation(short* x, short* y);
void make_random_block(void);

#endif
