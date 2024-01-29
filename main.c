#include <stdio.h>
#include "terminal.h"


void print_func(uint8_t *str, uint32_t len)
{
    printf("%s", str);
}

void print_action(struct command c)
{
    printf("[DEBUG] %s ", c.cmd);
    for(uint8_t i = 0; i < 5; i++) {
        printf("%s ", c.params[i]);
    }
    printf("\n");
}

int main()
{
    terminal_init(&print_func);
    command_t com1 = {
        .cmd = "help",
        .help = "Shows Help Menu",
        .action = &print_action
    };

    command_t com2 = {
        .cmd = "date",
        .help = "Configure RTC date: date YY MM DD",
        .action = &print_action
    };

    command_t com3 = {
        .cmd = "time",
        .help = "Configure RTC time: time HH MM SS",
        .action = &print_action
    };

    terminal_add_command(com1);
    terminal_add_command(com2);
    terminal_add_command(com3);
    terminal_print_help();

    terminal_treat_input("DATE 11 22 33");
    terminal_treat_input("time 11 22 33");
    terminal_treat_input("help 11 22 33");
    terminal_treat_input("ssss ssss");
    return 0;
}
