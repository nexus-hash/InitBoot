#include "monitor.h"
#include "idt_int.h"
#include "keyb.h"

void kmain(void)
{
    idt_init();
    load_idt_entry(0x21, (unsigned long) keyboard_handler_int, 0x08, 0x8e);
    kb_init();

    color_t color;
    color.bgcolor = 13;
    color.fgcolor = 15;

    monitor_clear();

    // Write out a sample string
    monitor_write("Welcome to Init OS!\n", color);
    monitor_write("\nType in 'help' for a list of commands, and 'about'\nfor version info.\n\n", color);

    char c = get_key();
    monitor_put(c, color);

    while(1) __asm__("hlt\n\t");
}