/***************************************************/
// File: monitor.h - prototypes for screen
//                   functions (write, clear, etc.)
/***************************************************/

#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"
#include "colors.h"

// Write a single char to screen
void monitor_put(char c,u8int bgcolor,u8int fgcolor,int x,int y);

// Clear the screen
void monitor_clear();

// Write a null-terminated ASCII
// string to the screen
void monitor_write(char *c,u8int bgcolor,u8int fgcolor,int x,int y);
void monitor_write_dec(u32int n,u8int bgcolor,u8int fgcolor,int x,int y);

#endif
