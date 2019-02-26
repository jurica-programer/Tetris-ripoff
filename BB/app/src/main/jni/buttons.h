#include "global_functions.h"
#include "common_functions.h"
#include "queue.h"
#include <pthread.h>

void *button_loop_thread(void *arg);
void endGame(void);
void timerTrigger(int state);