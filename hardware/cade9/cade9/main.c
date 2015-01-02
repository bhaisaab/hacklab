#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "cocoos.h"

#include "clock.h"
#include "main.h"

unsigned char gameState;
unsigned char displayCounter;

static void system_init(void);

//Display Routines
void welcomeScreen(void);
void renderScreen(void);

//Tasks
static int display_task(void);
static int ball_task(void);
static int ai_task(void);
static int button_task(void);

//Task Helpers
void moveComputerBat(void);
void movePlayerBat(int y);
static os_sem_type* buttonSem;
//uint8_t buttonPressed = 0;

const static unsigned char scoreBoard[11] =
{
    0b01111110, //0
	0b00010010, //1
	0b10111100, //2
	0b10110110, //3
	0b11010010, //4
	0b11100110, //5
	0b11101110, //6
	0b00110010, //7
	0b11111110, //8
	0b11110110, //9
    0b11110111  //9.
};

static uint8_t displayBuffer[7][2] =
{
     //PORTC     //PORTA
    {0b11111111, 0b00001111}, //Line 0
    {0b11111111, 0b00011111}, //Line 1
    {0b11111111, 0b00101111}, //Line 2
    {0b11111111, 0b00111111}, //Line 3
    {0b11111111, 0b01001111}, //Line 4
    {0b11111111, 0b01011111}, //Line 5
    {0b11111111, 0b01101111}  //Line 6
};


static struct score gameScore;
static struct object ball;
static struct bat playerBat;
static struct bat computerBat;

static int score_task(void)
{
    OS_BEGIN;

    //Check and update Game Status
    if( (gameScore.computer > 9) ||
        (gameScore.player > 9) )
        gameState = GAME_OVER;

    //Update Players's Score
    SB_TOGGLE;
    PORTD = scoreBoard[gameScore.player];
    OS_WAIT_TICKS(2);

    //Update Computer's Score
    SB_TOGGLE;
    PORTD = scoreBoard[gameScore.computer];
    OS_WAIT_TICKS(2);

    OS_END;

    return 0;
}

static int display_task(void)
{
    OS_BEGIN;

    switch(gameState)
    {
        case GAME_INIT:  welcomeScreen(); break;
        case GAME_START: renderScreen();  break;
        case GAME_OVER:  welcomeScreen(); break;

        default: welcomeScreen(); break;
    }

    OS_WAIT_TICKS(1);

    OS_END;

    return 0;
}

static int button_task(void)
{
    OS_BEGIN;

        if( (gameState == GAME_INIT) ||
            (gameState == GAME_OVER) )
        {
            if( (BUTTONS & FIRE) == 0 )
            {

                OS_WAIT_SEM( buttonSem );

                BUZZER_ON;
                gameState = GAME_START;
                gameScore.computer = 0;
                gameScore.player = 0;
                movePlayerBat(0);
		OS_WAIT_TICKS( 15 );
                BUZZER_OFF;

                OS_SIGNAL_SEM( buttonSem );
            }
        }

        if(gameState == GAME_START)
        {
            //Refresh bat :D
            movePlayerBat(0);
            if( (BUTTONS & UP) == 0 )
            {

                //OS_WAIT_SEM( buttonSem );

                movePlayerBat(1);

                //OS_SIGNAL_SEM( buttonSem );
            }

            if( (BUTTONS & DOWN) == 0 )
            {

                //OS_WAIT_SEM( buttonSem );

                movePlayerBat(-1);

                //OS_SIGNAL_SEM( buttonSem );
            }
        }

	OS_WAIT_TICKS( 15 );

    OS_END;
    return 0;
}

static int ball_task(void)
{
    OS_BEGIN;

    if(gameState == GAME_START)
    {
        if( ball.x < 8 )
        {
            displayBuffer[ball.y][0] |= (1<<(ball.x));
        }
        else
        {
            int temp = ball.x - 8;
            displayBuffer[ball.y][1] |= (1<<(temp));
        }

        ball.x += ball.vx;

        if(ball.x==11)
        {
            int temp = ball.y - playerBat.y;
            if( (temp>=0) && (temp < playerBat.len) )
                BUZZER_ON;
            else
                gameScore.computer++;

            ball.vx = -1;
        }

        if(ball.x==0)
        {
            int temp = ball.y - computerBat.y;
            if( (temp>=0) && (temp < computerBat.len) )
                BUZZER_ON;
            else
                gameScore.player++;

            ball.vx = 1;
        }

        if(ball.y==6)
        {
            ball.vy *= -1;
            BUZZER_ON;
        }

        if(ball.y==0)
        {
            ball.vy *= -1;
            BUZZER_ON;
        }
	OS_WAIT_TICKS( 20 );
        BUZZER_OFF;
        ball.y += ball.vy;


        if( ball.x < 8 )
        {
            displayBuffer[ball.y][0] &= ~(1<<(ball.x));
        }
        else
        {
            int temp = ball.x - 8;
            displayBuffer[ball.y][1] &= ~(1<<(temp));
        }
    }
    OS_WAIT_TICKS (30);

    OS_END;

    return 0;
}

static int ai_task(void)
{
    OS_BEGIN;

    moveComputerBat();

    OS_WAIT_TICKS( 90 );

    OS_END;

    return 0;
}

/*

		OS_WAIT_SEM( buttonSem );
        if ( buttonPressed ) {
            OS_SIGNAL_SEM( buttonSem );

		LED_TOGGLE(1);

			//OS_SUSPEND_TASK();
        }
        else {
            OS_SIGNAL_SEM( buttonSem );
}
*/

int main(void)
{
	system_init();
	os_init();

    buttonSem = os_create_sem( 1 );

    os_task_create( button_task, 1 );
    os_task_create( display_task, 2);
    os_task_create( ball_task, 3);
    os_task_create( ai_task, 4);
    os_task_create( score_task, 5);


	/* Setup clock with 1 ms tick */
    clock_init(1);

	os_start();
    return 0;
}

static void system_init(void)
{
    DDRA = 0xff;

    DDRC = 0xff;

    DDRB = 0b11100000;

    PORTA = 0b11001111;

    PORTB = 0b01100000;

    DDRD = 0xff;
    PORTD = 0xf0;

    BUZZER_OFF;
    gameScore.computer = 0;
    gameScore.player = 9;

    displayCounter = 0;
    gameState = GAME_INIT;

    //WRT PORTA PINS
    playerBat.y = 2;
    playerBat.len = 2;

    //WRT PORTC PINS
    computerBat.y = 2;
    computerBat.len = 2;

    //Ball
    ball.x = 0;
    ball.y = 2;
    ball.vx = 1;
    ball.vy = 1;
}

void welcomeScreen(void)
{
    switch(displayCounter)
    {
        case 0: PORTC = 0b10001100; PORTA = 0b00001111; break;
        case 1: PORTC = 0b11001010; PORTA = 0b00011000; break;
        case 2: PORTC = 0b10001100; PORTA = 0b00101011; break;
        case 3: PORTC = 0b11111111; PORTA = 0b00111000; break;
        case 4: PORTC = 0b10101001; PORTA = 0b01001010; break;
        case 5: PORTC = 0b10101110; PORTA = 0b01011000; break;
        case 6: PORTC = 0b11011001; PORTA = 0b01101111; break;
    }

    displayCounter++;

    if( displayCounter > 6)
        displayCounter = 0;
}

void renderScreen(void)
{
    PORTC = displayBuffer[displayCounter][0];
    PORTA = displayBuffer[displayCounter][1];

    displayCounter++;

    if(displayCounter>6)
        displayCounter = 0;
}

void movePlayerBat(int y)
{
    if( (y>0) && (playerBat.y == (7-playerBat.len)) )
        return;

    if( (y<0) && (playerBat.y == 0) )
        return;

    playerBat.y += y;

    int i = playerBat.len;
    int j = 0;

    int temp = playerBat.y + playerBat.len;

    for(; j<7; j++)
    {
        if( ( i > 0 ) && ( j == (temp - i) ) )
        {
            displayBuffer[j][1] &= 0xf7; //TURN ON
            i--;
        }
        else
        {
            displayBuffer[j][1] |= 0x08; //TURN OFF
        }
    }
}

void moveComputerBat(void)
{
    int y = ball.y - computerBat.y;

    if( (y>0) && (computerBat.y == (7-computerBat.len)) )
            return;

    if( (y<0) && (computerBat.y == 0) )
        return;

    if(ball.y > (computerBat.y + computerBat.len))
        computerBat.y++;

    if(ball.y < (computerBat.y))
        computerBat.y--;


    int i = computerBat.len;
    int j = 0;

    int temp = computerBat.y + computerBat.len;

    for(; j<7; j++)
    {
        if( ( i > 0 ) && ( j == (temp - i) ) )
        {
            displayBuffer[j][0] &= 0xfe; //TURN ON
            i--;
        }
        else
        {
            displayBuffer[j][0] |= 0x01; //TURN OFF
        }
    }
}
