#ifndef THEMES_H
#define THEMES_H

#include "colors.h"

#define MAX_THEMES 3

enum themes {PINK_YELLOW, GREEN_YELLOW, DEEPPINK_YELLOW};

typedef struct theme {
    color_t normal_text_color;
    color_t selected_text_color;
} theme_t;

theme_t avail_themes[] = [
    {
        {13, 14},
        {12, 14}
    },
    {
        {2, 14},
        {3, 14}
    },
    {
        {13, 14},
        {5, 14}
    },
];