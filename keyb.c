#include "keyb.h"
#include "monitor.h"

char inp_buff[MAX_BUF_LEN];
unsigned int inp_buff_idx = 0;

unsigned char keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',     /* 9 */
  '9', '0', '-', '=', '\b',     /* Backspace */
  '\t',                 /* Tab */
  'q', 'w', 'e', 'r',   /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,                  /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',     /* 39 */
 '\'', '`',   0,                /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',                    /* 49 */
  'm', ',', '.', '/',   0,                              /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

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
            inp_buff_idx++;
        }
    }

    /* Send End of Interrupt (EOI) to master PIC */
    write_port(0x20, 0x20);
}

char get_key() {

    color_t color;
    color.bgcolor = 8;
    color.fgcolor = 15;

    char ret = inp_buff[0];

    while (inp_buff_idx <= 0) {
        ret = inp_buff[0];
    }  

    // shift the values of inp_buff by one to the left
    for (unsigned int i = 1; i < inp_buff_idx; i++) {
        inp_buff[i - 1] = inp_buff[i];
    }

    if (inp_buff_idx == MAX_BUF_LEN - 1) {
        inp_buff[MAX_BUF_LEN - 1] = 0;
    }

    inp_buff_idx--;
    return ret;
}
