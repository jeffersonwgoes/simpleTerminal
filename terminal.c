
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "terminal.h"
typedef struct {
    void (*print_funcion_terminal)(uint8_t*, uint32_t);
    command_t commands[NUMBER_OF_COMMANDS];
    uint8_t commands_size;
} terminal_t;

static terminal_t term;
static void str_split(uint8_t * str, uint8_t params[NUMBER_OF_PARAMS][MAX_PARAM_SIZE]);

void terminal_init(void (*print_function)(uint8_t*, uint32_t))
{
    term.commands_size = 0U;
    term.print_funcion_terminal = print_function;
    
}

uint8_t terminal_add_command(command_t command)
{
    if(term.commands_size == NUMBER_OF_COMMANDS) 
    {
        return 0;
    }

    memcpy((void*)&term.commands[term.commands_size], (void*)&command, sizeof(command_t));
    return ++term.commands_size;
}

void terminal_print_help(void)
{
    char str[PRINT_BUFFER_SIZE];
    uint8_t len = sprintf(str, "Terminal Help\n");
    term.print_funcion_terminal(str, len);
    for(uint8_t i = 0U; i < term.commands_size; i++)
    {
        len = sprintf(str, "Command: %c %s\n", term.commands[i].letter, term.commands[i].help);
        term.print_funcion_terminal(str, len);
    }
}

static void str_split(uint8_t * str, uint8_t params[NUMBER_OF_PARAMS][MAX_PARAM_SIZE])
{
    uint8_t cnt = 0U;
    uint8_t i = 0;
    uint8_t init = 0U;
    while(str[i] != '\0') {
        if(cnt == NUMBER_OF_PARAMS) {
            break; // reach the max number of params
        }
        if(str[i+1] == ' ' || str[i+1] == '\0') {
            memcpy((void*)&params[cnt++], (void*)&str[init], i - init + 1);
            init = i + 2;
        }
        i++;
    }
}

void terminal_treat_input(uint8_t* str)
{
    if(str[0] == 'h') {
        terminal_print_help();
    } else {
        uint8_t found = 0U;
        for(uint8_t i = 0U; i < term.commands_size; i++)
        {
            if(term.commands[i].letter == str[0]) {
                found = 1U;
                str_split(&str[2], term.commands[i].params);
                term.commands[i].action(term.commands[i]);
                break;
            }
        }
        
        if(!found) {
            char prt[PRINT_BUFFER_SIZE];
            uint8_t len = sprintf(prt, "\nCommand Not Found: (%s)\n", str);
            term.print_funcion_terminal(prt, len);
            terminal_print_help();
        }
    }
}
