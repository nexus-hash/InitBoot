#include "keyb.h"

void kb_init(void)
{
    /* This is a very basic keyboard initialization. The assumption is we have a
     * PS/2 keyboard and it is already in a proper state. This may not be the case
     * on real hardware. We simply enable the keyboard interupt */

    /* Get current master PIC interrupt mask */
    unsigned char curmask_master = read_port (0x21);

    /* 0xFD is 11111101 - enables only IRQ1 (keyboard) on master pic
       by clearing bit 1. bit is clear for enabled and bit is set for disabled */
    write_port(0x21, curmask_master & 0xFD);

    /* Initialize the input buffer: */
    memset(inp_buff, MAX_BUF_LEN, 0);
}

void keyboard_handler(void)
{
    signed char keycode;

    keycode = read_port(0x60);
    /* Only print characters on keydown event that have
     * a non-zero mapping */
    if(keycode >= 0 && keyboard_map[keycode]) {
        if (inp_buff_idx < MAX_BUF_LEN) {
            inp_buff[inp_buff_idx] = keyboard_map[keycode];
        }
    }

    /* Send End of Interrupt (EOI) to master PIC */
    write_port(0x20, 0x20);
}

char get_key() {
    char ret = inp_buff[0];

    while (inp_buff_idx <= 0) {
        ret = inp_buff[0];
    }

    // shift the values of inp_buff by one to the left
    for (int i = 1; i < inp_buff_idx; i++) {
        inp_buff[i - 1] = inp_buff[i];
    }

    if (inp_buff_idx == MAX_BUF_LEN - 1) {
        inp_buff[MAX_BUF_LEN - 1] = 0;
    }

    inp_buff_idx--;
    return ret;
}
