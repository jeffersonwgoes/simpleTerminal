
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "terminal.h"
typedef struct {
    void (*print_funcion_terminal)(uint8_t*, uint32_t);
    command_t commands[NUMBER_OF_COMMANDS];
    uint8_t commands_size;
} terminal_t;

static terminal_t term;
static void str_split(uint8_t * str, uint8_t params[NUMBER_OF_PARAMS][MAX_PARAM_SIZE]);
static void lower(uint8_t *original, uint32_t len, uint8_t *lowered);
static uint8_t get_size_command(uint8_t *str);

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
    term.print_funcion_terminal((uint8_t*) str, len);
    for(uint8_t i = 0U; i < term.commands_size; i++)
    {
        len = sprintf(str, "Command: (%s): %s\n", term.commands[i].cmd, term.commands[i].help);
        term.print_funcion_terminal((uint8_t*)str, len);
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

static uint8_t get_size_command(uint8_t *str)
{
    uint8_t cnt = 0U;
    for(; cnt < MAX_PARAM_SIZE && str[cnt] != ' '; cnt++);
    if (cnt == MAX_PARAM_SIZE)
    {
        return 0U;
    }
    return cnt;
}

static void lower(uint8_t *original, uint32_t len, uint8_t *lowered)
{
    uint8_t i = 0U;
    for (; i < len; i++)
    {
        if (original[i] > 0x40U && original[i] < 0x5b)
        {
            lowered[i] = original[i] + 0x20;
        }
        else
        {
            lowered[i] = original[i];
            
        }
    }
    lowered[i++] = '\0';
}

void terminal_treat_input(uint8_t* str)
{
    if(str[0] == 'h') {
        terminal_print_help();
    } else {
        uint8_t found = 0U;
        for(uint8_t i = 0U; i < term.commands_size; i++)
        {
            uint8_t command_len = get_size_command(str);
            uint8_t cmd[MAX_PARAM_SIZE];
            lower(str, command_len, cmd);
            if(strcmp(term.commands[i].cmd, cmd) == 0U) {
                found = 1U;
                str_split(&str[command_len], term.commands[i].params);
                term.commands[i].action(term.commands[i]);
                break;
            }
        }
        
        if(!found) {
            char prt[PRINT_BUFFER_SIZE];
            uint8_t len = sprintf(prt, "\nCommand Not Found: (%s)\n", str);
            term.print_funcion_terminal((uint8_t*)prt, len);
            terminal_print_help();
        }
    }
}
