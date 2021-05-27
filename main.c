#include "monitor.h"
#include "idt_int.h"
#include "keyb.h"
#include "theme.h"

void kmain(void)
{
    idt_init();
    load_idt_entry(0x21, (unsigned long) keyboard_handler_int, 0x08, 0x8e);
    kb_init();

    color_t color;
    color.bgcolor = 6;
    color.fgcolor = 3;

    monitor_clear();

    // Write out a sample string
    monitor_write("Welcome to Init Boot\n", color);
    monitor_write("\nSelect OS to boot\n\n", color);
    monitor_write("\nInit OS\n", color);
    monitor_write("\nAlpenite OS\n\n\n\n", color);
    monitor_write("\nCustomize", color);

    char c = get_key();
    monitor_put(c, color);

    while(1) __asm__("hlt\n\t");
}