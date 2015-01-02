#ifndef LANGUAGE_H
#define LANGUAGE_H

#define TRUE         1
#define FALSE        0

#define ERROR_CMD    -2
#define TIMEOUT_CMD  -1

#define START_CMD    '^'
#define END_CMD      '$'

#define SPEAK_MSG    '>'
#define ERROR_MSG    '!'
#define TIMEOUT_MSG  '#'

/* Wordset 1 */
#define ACTION_CMD   0
#define MOVE_CMD     1
#define TURN_CMD     2
#define RUN_CMD      3
#define LOOK_CMD     4
#define ATTACK_CMD   5
#define STOP_CMD     6
#define HELLO_CMD    7

/* Wordset 2 */

#define LEFT_CMD     0
#define RIGHT_CMD    1
#define UP_CMD       2
#define DOWN_CMD     3
#define FORWARD_CMD  4
#define BACKWARD_CMD 5

/* Wordset 3 */
#define ZERO_CMD     0
#define ONE_CMD      1
#define TWO_CMD      2
#define THREE_CMD    3
#define FOUR_CMD     4
#define FIVE_CMD     5
#define SIX_CMD      6
#define SEVEN_CMD    7
#define EIGHT_CMD    8
#define NINE_CMD     9
#define TEN_CMD      10

#endif //LANGUAGE_H
