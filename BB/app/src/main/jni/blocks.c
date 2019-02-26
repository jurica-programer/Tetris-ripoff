#include "blocks.h"
#include "common_functions.h"
#include "com_zoid_mega_bb_Native.h"

/***************************
 *     LOCAL VARIABLES     *
 ***************************/

short making_blocks[] = {
//  y0,y1,y2,y3,x0,x1,x2,x3,rotation // type:
    -1, 0, 1, 2, 0, 0, 0, 0, left,  // i block
    -1, 0, 1, 0, 0, 0, 0, 1, right,  // t block
    -1, 0, 0, 1, 0, 0, 1, 1, down,   // n block
    -1, 0, 0, 1, 0, 0,-1,-1, down,   // z block
    -1, 0, 1,-1, 0, 0, 0, 1, right,  // l block
    -1, 0, 1,-1, 0, 0, 0,-1, left,   // j block
    -1, 0,-1, 0, 0, 1, 1, 0, right}; // s block


short rotate_blocks[] = {
//  y0,y1,y2,y3,x0,x1,x2,x3,rotation // type:
    -1, 0, 1, 2, 2, 1, 0,-1, up,     // i block
     1, 0,-1,-2,-1, 0, 1, 2, left,
    -2,-1, 0, 1, 1, 0,-1,-2, down,
     2, 1, 0,-1,-2,-1, 0, 1, right,

    -1, 0, 1, 1, 1, 0,-1, 1, up,     // t block
     0, 0,-1, 0, 0, 0, 1, 0, left,
     0, 0, 0,-1, 0, 0, 0,-1, down,
     1, 0, 0, 0,-1, 0, 0, 0, right,

    -1, 0,-1, 0,-1, 0, 1, 2, up,     // n block
     1, 0,-1,-2,-1, 0,-1, 0, left,
     1, 0, 1, 0, 1, 0,-1,-2, down,
    -1, 0, 1, 2, 1, 0, 1, 0, right,

    -1, 0, 1, 2,-1, 0,-1, 0, up,     // z block
     1, 0, 1, 0,-1, 0, 1, 2, left,
     1, 0,-1,-2, 1, 0, 1, 0, down,
    -1, 0,-1, 0, 1, 0,-1,-2, right,

    -1, 0, 1, 0, 1, 0,-1, 2, up,     // l block
    -1, 0, 1,-2,-1, 0, 1, 0, left,
     1, 0,-1, 0,-1, 0, 1,-2, down,
     1, 0,-1, 2, 1, 0,-1, 0, right,

     1, 0,-1, 2,-1, 0, 1, 0, up,     // j block
     1, 0,-1, 0, 1, 0,-1, 2, left,
    -1, 0, 1,-2, 1, 0,-1, 0, down,
    -1, 0, 1, 0,-1, 0, 1,-2, right}; // s block does not rotate

/***************************
 *        FUNCTIONS        *
 ***************************/

/****************************************
 * field value getter
 ****************************************/
bool getFieldValue(int row, int column)
{
    short counter;
    GameContext.return_value = 0;
    for(counter = 0; counter < GAME_BLOCK_SIZE; counter++)
    {
        if( (GameContext.block.y[counter] == row) &&
            (GameContext.block.x[counter] == column) )
        {
            return true;
        }
    }

    if( GameContext.gameField[row] & (0x1 << column) )
    {
        return true;
    }
    return false;
}

/****************************************
 * block hit floor function
 ****************************************/
void touchdown(void)
{
    short counter;
    short shift_down_counter;
    short score_multiplier = 0;

    //write to field
    for(counter = 0; counter < GAME_BLOCK_SIZE; counter++)
    {
        GameContext.gameField[GameContext.block.y[counter]] += (1 << GameContext.block.x[counter]);
    }

    //check if row is full
    for(counter = GAME_MAX_ROWS; counter >= 0; counter--)
    {
        if( GameContext.gameField[counter] == 0x3FF ) //0b1111111111
        {
            //add score multiplier value
            score_multiplier++;

            //shift all block down
            for(shift_down_counter = counter; shift_down_counter > 0; shift_down_counter--)
            {
                GameContext.gameField[shift_down_counter] = GameContext.gameField[shift_down_counter - 1];
            }
            counter++;
        }
    }

    //TODO popravi rezultat da bolje prati rez i da levelaš brže
    //calculate score
    GameContext.score += score_multiplier * score_multiplier * GameContext.level * 10;
    if( GameContext.score > 1000 )
    {
        GameContext.level = GameContext.score / 1000;
    }

    //add a new bloc
    if( make_block() )
    {
        //game over
        memset(&GameContext.gameField, 0x00, GAME_MAX_ROWS * sizeof(int));
        memset(&GameContext.block, 0x00, sizeof(block));
        GameContext.score = 0;
        //sendCallback(2);
        sendCallback(0);
        make_block();
        //TODO make gameover and go to highscore menu
    }

    //send score status
    if( score_multiplier )
    {
        sendCallback(0);
    }

}

/****************************************
 * moving block function
 ****************************************/
movement_allow move_block(int data)
{
    short counter;

    //validation check
    for(counter = 0; counter < GAME_BLOCK_SIZE; counter++)
    {
        if( (GameContext.block.x[counter] + data < 0) ||
            (GameContext.block.x[counter] + data > 9) ||
            (GameContext.gameField[GameContext.block.y[counter]] & (1 << GameContext.block.x[counter] + data))){
            return not_allowed;
        }
    }

    //move block
    for(counter = 0; counter < GAME_BLOCK_SIZE; counter++)
    {
        GameContext.block.x[counter] += data;
    }
    return allowed;
}

/****************************************
 * slamming block down function
 ****************************************/
tetris_error slam_block(void)
{
    while( 1 )
    {
        if( block_fall() )
        {
            break;
        }
    }
    return no_error;
}

tetris_error block_fall(void)
{
    short counter;

    //block has fallen
    for(counter = 0; counter < GAME_BLOCK_SIZE; counter++)
    {
        if((GameContext.gameField[GameContext.block.y[counter] + 1] & (1 << GameContext.block.x[counter]))
           || (GameContext.block.y[counter] + 1 > 19))
        {
            touchdown();
            return error;
        }
    }

    // move block down
    for(counter = 0; counter < GAME_BLOCK_SIZE; counter++)
    {
        GameContext.block.y[counter]++;
    }
    return no_error;
}

/****************************************
 * make new block function
 ****************************************/
tetris_error make_block(void)
{
    short counter;
    srand(time(NULL));
    tetris_error state = no_error;

    //TODO memkopi treba
    GameContext.block.type = GameContext.nextBlock.type;
    GameContext.block.rotation = GameContext.nextBlock.rotation;

    for (counter = 0; counter < GAME_BLOCK_SIZE; counter++) {
        GameContext.block.y[counter] = GameContext.nextBlock.y[counter];
        GameContext.block.x[counter] = GameContext.nextBlock.x[counter];

        if (GameContext.gameField[GameContext.block.y[counter]] & (0x1 << GameContext.block.x[counter])) {
            state = error;
        }
    }
    make_random_block();

    //populate block struct
    return state;
}

/****************************************
 * rotate block function
 ****************************************/
void rotate_block(void)
{
    short x[4];
    short y[4];
    short counter;

    //s block does not rotate
    if( GameContext.block.type != s_block )
    {
        //populate temp block
        for(counter = 0; counter < GAME_BLOCK_SIZE; counter++)
        {
            y[counter] = GameContext.block.y[counter] + rotate_blocks[(9 * ((4 * GameContext.block.type) + GameContext.block.rotation)) + counter];
            x[counter] = GameContext.block.x[counter] + rotate_blocks[(9 * ((4 * GameContext.block.type) + GameContext.block.rotation)) + counter + 4];
        }

        //validation check
        if( !check_rotation(x, y) )
        {
            //rotation setup, check enum
            if( GameContext.block.rotation == up)
            {
                GameContext.block.rotation = num_rotation;
            }
            GameContext.block.rotation--;

            //make move
            for(counter = 0; counter < GAME_BLOCK_SIZE; counter++)
            {
                GameContext.block.y[counter] = y[counter];
                GameContext.block.x[counter] = x[counter];
            }
        }
    }
}

/****************************************
 * check rotation function
 ****************************************/
tetris_error check_rotation(short* x, short* y)
{
    short counter;
    short move = 0;

    //moving temp block to empty space
    for(counter = 0; counter < GAME_BLOCK_SIZE; counter++)
    {
        //move right from blocks or edge
        if( (GameContext.gameField[y[counter]] & (1 << x[counter]) &&
                (x[counter] < GameContext.block.x[counter])) || (x[counter] < 0) )
        {
            move++;
        }
        //move left from blocks or edge
        else if( (GameContext.gameField[y[counter]] & (1 << x[counter]) &&
                 (x[counter] > GameContext.block.x[counter])) || (x[counter] > 9) )
        {
            move--;
        }
    }

    //check temp block validity
    for(counter = 0; counter < GAME_BLOCK_SIZE; counter++)
    {
        x[counter] += move;
        if( (GameContext.gameField[y[counter]] & (1 << x[counter])) ||
                (y[counter] < 0) || (y[counter] > 19) ||
                (x[counter] < 0) || (x[counter] > 9) )
        {
            return error;
        }
    }
    return no_error;
}

void make_random_block(void)
{
    short counter;
    srand(time(NULL) + (int)&counter);
    GameContext.nextBlock.type = rand() % 7;
    GameContext.nextBlock.rotation = making_blocks[(GameContext.nextBlock.type * 9) + 8];
    for (counter = 0; counter < GAME_BLOCK_SIZE; counter++) {
        GameContext.nextBlock.y[counter] = GAME_BLOCK_START_Y + making_blocks[(9 * GameContext.nextBlock.type) + counter];
        GameContext.nextBlock.x[counter] = GAME_BLOCK_START_X + making_blocks[(9 * GameContext.nextBlock.type) + counter + 4];
    }
}