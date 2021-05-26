#include "monitor.h"
#include "idt_int.h"

void kmain(void)
{
    idt_init();
    load_idt_entry(0x21, (unsigned long) keyboard_handler_int, 0x08, 0x8e);
    kb_init();

    color_t color;
    pos_t pos ;
    pos.x = 0;
    pos.y = 0;
    color.bgcolor = 13;
    color.fgcolor = 15;

    monitor_clear();

    // Write out a sample string
    monitor_write("Welcome to Init OS!\n", color.bgcolor, color.fgcolor, pos.x, pos.y);
    pos.x=0;
    pos.y=2;
    monitor_write("\nType in 'help' for a list of commands, and 'about'\nfor version info.\n\n", color.bgcolor, color.fgcolor, pos.x, pos.y);

    while(1) __asm__("hlt\n\t");
}