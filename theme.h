#ifndef THEME_H
#define THEME_H

#include "themes.h"

theme_t current_theme = avail_themes[0];
enum themes current_theme_idx = 0;

// Write a single char to screen
void monitor_put_wtheme(char c, theme_t theme, int selected = 0);

void monitor_clear_wtheme(theme_t theme);

// Write a null-terminated ASCII
// string to the screen
void monitor_write_wtheme(char *c, theme_t theme, int selected = 0);
void monitor_write_dec_wtheme(u32int n, theme_t theme, int selected = 0);

/* For writing with the current theme: */

// Write a single char to screen
void monitor_put_theme(char c, int selected = 0);

// Set the current theme
void monitor_set_theme(theme_t theme);
void monitor_set_theme_name(enum themes theme);

// Write a null-terminated ASCII
// string to the screen
void monitor_write_theme(char *c, int selected = 0);
void monitor_write_dec_theme(u32int n, int selected = 0);

#endif
