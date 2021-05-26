#ifndef _KEYB_H
#define _KEYB_H

#include "port_io.h"
#include "keyboard_map.h"
#include "common.h"

#define MAX_BUF_LEN 1024

char inp_buff[MAX_BUF_LEN];
unsigned int inp_buff_idx = 0;

void kb_init(void);
void keyboard_handler(void);

char get_key();