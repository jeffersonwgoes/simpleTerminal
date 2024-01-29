#include <stdint.h>

#ifndef HELP_SIZE
#define HELP_SIZE 100U
#endif

#ifndef NUMBER_OF_PARAMS
#define NUMBER_OF_PARAMS 5U
#endif
#ifndef PRINT_BUFFER_SIZE
#define PRINT_BUFFER_SIZE 200U
#endif
#ifndef NUMBER_OF_COMMANDS
#define NUMBER_OF_COMMANDS 10U
#endif
#ifndef MAX_PARAM_SIZE
#define MAX_PARAM_SIZE 10U
#endif

typedef struct command{
    uint8_t cmd[MAX_PARAM_SIZE];
    uint8_t help[HELP_SIZE];
    uint8_t params[NUMBER_OF_PARAMS][MAX_PARAM_SIZE];
    void (*action)(struct command);
} command_t;

void terminal_init(void (*print_function)(uint8_t*, uint32_t));
uint8_t terminal_add_command(command_t command);
void terminal_print_help(void);
void terminal_treat_input(uint8_t* str);