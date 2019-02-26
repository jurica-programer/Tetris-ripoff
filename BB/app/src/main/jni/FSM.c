/*
 * U ovom modulu napravi state mašinu kao ulazni meni
 * highscore
 * namještanje ekrana
 * namještanje blokova, tema
 * namještanje retro emulator look ili ovaj trenutni za bolju gameplay
 *
 * highscore spremanje i čitanje
 * spajanje na server i update baze napraviti
 * napravi raspberry da drži rezultate ili nešto drugo za spremanje
 *
 * FSM finate state machine za stanja
 *
 * stanja:
 * MENU
 * GAMEPLAY
 * SETTINGS
 * PAUSE
 * EXIT
 *
 * */
#include "FSM.h"

int gameState = 0;

int getView(void)
{
    if( gameState == 0 )//TODO napravi enum
    {
        return 1;
    }
    return 0;
}

