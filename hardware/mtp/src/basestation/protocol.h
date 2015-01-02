#ifndef PROTOCOL_H
#define PROTOCOL_H

#define CMD_BREAK       'b' // abort recog or ping
#define CMD_SLEEP       's' // go to power down
#define CMD_KNOB        'k' // set si knob <1>
#define CMD_LEVEL       'v' // set sd level <1>
#define CMD_LANGUAGE    'l' // set si language <1>
#define CMD_TIMEOUT     'o' // set timeout <1>
#define CMD_RECOG_SI    'i' // do si recog from ws <1>
#define CMD_TRAIN_SD    't' // train sd command at group <1> pos <2>
#define CMD_GROUP_SD    'g' // insert new command at group <1> pos <2>
#define CMD_UNGROUP_SD  'u' // remove command at group <1> pos <2>
#define CMD_RECOG_SD    'd' // do sd recog at group <1> (0 = trigger mixed si/sd)
#define CMD_ERASE_SD    'e' // reset command at group <1> pos <2>
#define CMD_NAME_SD     'n' // label command at group <1> pos <2> with length <3> name <4-n>
#define CMD_COUNT_SD    'c' // get command count for group <1>
#define CMD_DUMP_SD     'p' // read command data at group <1> pos <2>
#define CMD_MASK_SD     'm' // get active group mask
#define CMD_RESETALL    'r' // reset all commands and groups
#define CMD_ID          'x' // get version id
#define CMD_DELAY       'y' // set transmit delay <1> (log scale)
#define CMD_BAUDRATE    'a' // set baudrate <1> (bit time, 1=>115200)

#define STS_MASK        'k' // mask of active groups <1-8>
#define STS_COUNT       'c' // count of commands <1>
#define STS_AWAKEN      'w' // back from power down mode
#define STS_DATA        'd' // provide command length <1> label <2-11> training <12>
#define STS_ERROR       'e' // signal error code <1-2>
#define STS_INVALID     'v' // invalid command or argument
#define STS_TIMEOUT     't' // timeout expired
#define STS_INTERR      'i' // back from aborted recognition (see 'break')
#define STS_SUCCESS     'o' // no errors status
#define STS_RESULT      'r' // recognised sd command <1> - training similar to sd <1>
#define STS_SIMILAR     's' // recognised si <1> (in mixed si/sd) - training similar to si <1>
#define STS_OUT_OF_MEM  'm' // no more available commands (see 'group')
#define STS_ID          'x' // provide version id <1>

// protocol arguments are in the range 0x40 (-1) to 0x60 (+31) inclusive
#define ARG_MIN     0x40
#define ARG_MAX     0x60
#define ARG_ZERO    0x41

#define ARG_ACK     0x20    // to read more status arguments

#endif //PROTOCOL_H
