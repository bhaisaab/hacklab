#ifndef MAIN_H
#define MAIN_H


#include "cocoos.h"


//extern os_event_type evRacketMove;

//Game States
#define GAME_INIT     0
#define GAME_START    1
#define GAME_RESTART  2
#define GAME_PAUSE    3
#define GAME_OVER     4

//Player Defs
#define COMPUTER 0
#define PLAYER   1

//Buttons Masks
#define UP    0x01
#define DOWN  0x02
#define LEFT  0x08
#define RIGHT 0x04
#define FIRE  0x10

#define BUTTONS PINB

#define ON  0
#define OFF 1

#define SB_TOGGLE PORTB ^= 0xC0

#define BUZZER_ON     PORTB &= 0xDF
#define BUZZER_OFF    PORTB |= 0x20

struct score
{
    unsigned char player;
    unsigned char computer;
};

struct object
{
    uint8_t x;
    uint8_t y;
    uint8_t vx;
    uint8_t vy;
};

struct bat
{
    unsigned char y;
    unsigned char len;
    unsigned char dir;
};

#endif
