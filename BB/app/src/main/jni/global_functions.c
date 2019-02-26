#include "global_functions.h"
#include "common_functions.h"
#include "queue.h"
#include "buttons.h"
#include <pthread.h>

/****************************************
 * init resources
 ****************************************/
void init_game_res(void)
{
    sem_init(&GameContext.write_semaphore, 0, 0);
    sem_init(&GameContext.reading_semaphore, 0, 0);
    memset(&GameContext.gameField, 0x00, GAME_MAX_ROWS * sizeof(int));
    memset(&GameContext.block, 0x00, sizeof(GameContext.block));
    GameContext.level = 1;
    make_random_block();
    make_block();
}

/****************************************
 * terminate resources
 ****************************************/
tetris_error terminate_game_res(void)
{
    sem_destroy(&GameContext.write_semaphore);
    sem_destroy(&GameContext.reading_semaphore);
    memset(&GameContext, 0x00, sizeof(GameContext));
    GameContext.GameOver++;
    endGame();
    return no_error;
}

/****************************************
 * score value getter
 ****************************************/
int getScoreValue(void)
{
    return GameContext.score;
}

/****************************************
 * score value getter
 ****************************************/
int getNextBlock(void)
{
    return GameContext.nextBlock.type;
}

/****************************************
 * game loop thread function
 ****************************************/
void *game_loop_thread(void *arg)
{
    //TODO napravi spremanje rezultata
    float sleep_time = 500000;
    GameContext.fallingTimer = 0;
    while( !GameContext.GameOver)
    {
        if( GameContext.fallingTimer >= sleep_time && !GameContext.isPaused )
        {
            enqueue(block_fall, NO_DATA, no_type);
            GameContext.fallingTimer = 0;
        }
        else
        {
            //TODO napravi ovo s pravim tajmerima
            GameContext.fallingTimer += (30000 + (10 * GameContext.score));
            //sem_post(&GameContext.reading_semaphore);
        }

        //30ms refresh rate
        usleep(30000);

        if( dequeue() )
        {
            // On every event change screen
            sendCallback(1);
        }

    }
    return 0;
}

/****************************************
 * start threads
 ****************************************/
void startThread(void)
{
    pthread_t button_loop;
    pthread_t game_loop;
    pthread_create(&button_loop, NULL, button_loop_thread, NULL);
    pthread_create(&game_loop, NULL, game_loop_thread, NULL);
    pthread_join(button_loop, NULL);
    pthread_join(game_loop, NULL);
}

/****************************************
 * pause/resume game
 ****************************************/
void pauseContinue(void)
{
    GameContext.isPaused = !GameContext.isPaused;
}

/****************************************
 * reset game
 ****************************************/
int resetGame(void)
{
    memset(&GameContext.gameField, 0x00, GAME_MAX_ROWS * sizeof(int));
    memset(&GameContext.block, 0x00, sizeof(GameContext.block));
    GameContext.score = 0;
    GameContext.level = 1;
    make_random_block();
    make_block();
    return no_error;
}