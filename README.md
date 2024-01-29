# simpleTerminal

This terminal is supposed to be simple and lightweight to help debug in embbeded systems.

The main.c file can explaint how to use this terminal. Example of a command:

A command has only one letter and a default of 5 parameter max, example of a command to set RTC time and date:

    r 230101 121022

The max size of each parameter is 10 chars.

## Structures
The struct ``terminal_t`` holds the terminal itself, which supports commands. A command can be added using the struct ``command_t`` and the function ``terminal_add_command``. 
Also, this terminal has a function pointer to the buffer printer, which can be a uart_tx function or a printf function. This function should be:
    ``void func(uint8_t *buffer, uint32_t buffersize)``

The struct ``command_t`` holds commands, which has a help string, the letter to this command, and a function pointer to the action that will be executed when the commands is idenfied.

## Defines

To adjust this terminal to your use, there are some defines to change sizes:

- ``#define HELP_SIZE 50U``: Defines the max size of HELP String

- ``#define NUMBER_OF_PARAMS 5U``: Defines the max number of parameters

- ``#define PRINT_BUFFER_SIZE 200U``: Defines the max size of the print buffer

- ``#define NUMBER_OF_COMMANDS 10U``: Defines the number max of commands
- ``#define MAX_PARAM_SIZE 10U``: Defines the max size of the parameters


Remember to define your new limits before the line ``#include "terminal.h`` because they are declared with C preprocessor directives [Link](https://www.cprogramming.com/reference/preprocessor/ifndef.html).