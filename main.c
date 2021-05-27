#include "monitor.h"
#include "idt_int.h"
#include "keyb.h"
#include "theme.h"

void kmain(void)
{
    idt_init();
    load_idt_entry(0x21, (unsigned long) keyboard_handler_int, 0x08, 0x8e);
    kb_init();

    monitor_set_theme_name(PINK_YELLOW);

    monitor_clear_theme();
    // Write out a sample string
    monitor_write_theme("\n   Welcome to Init Boot\n", 0);
    monitor_write_theme("\n   Select OS to boot\n\n", 0);
    monitor_write_theme("\n   Init OS\n", 1);
    monitor_write_theme("\n   Alpenite OS\n\n\n\n", 0);
    monitor_write_theme("\n   Customize", 0);

    char c = get_key();

    while(1) __asm__("hlt\n\t");
}