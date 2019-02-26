#include "buttons.h"
#include "com_zoid_mega_bb_Native.h"
#include <time.h>

short game = 1;
short timer = 0;//TODO stavi neki timer pravi =)
short click = 0;
clock_t start = 0;
int msec = 0;

void *button_loop_thread(void *arg)
{
    while( game )
    {
        if( timer )
        {
            msec = (clock() - start) * 1000 / CLOCKS_PER_SEC;
            if( msec > 150 )
            {
                sendButtonCallback(1);
                timer = 0;
            }
        }

        if( click )
        {
            msec = (clock() - start) * 1000 / CLOCKS_PER_SEC;
            if( msec < 150 )
            {
                sendButtonCallback(1);
                click = 0;
                start = 0;
            }
            else
            {
                sendButtonCallback(0);
                click = 0;
            }
        }
        usleep(30);
    }
    return 0;
}

void endGame(void)
{
    game = 0;
}

void timerTrigger(int state)
{
    LOGD("native state %d", state);
    if( state == 1 )
    {
        start = clock();
        timer = 1;
    }
    if( state == 2 )
    {
        if( timer )
        {
            sendButtonCallback(0);
            timer = 0;
        }
    }
    if( state == 3) {
        timer = 0;
        click = 1;

        if( start == 0 )
        {
            start = clock();
            sendButtonCallback(0);
        }
        else
        {
            click = 1;
        }
    }
}