#ifndef _GUI_ELEMENT_BUTTON_H_
#define _GUI_ELEMENT_BUTTON_H_

#include <SDL2/SDL.h>
#include "types.h"

enum GUI_BUTTON_STATES{
    GUI_BUTTON_STATES_DEFAULT   = 0b00000000,
    GUI_BUTTON_STATES_HOVER     = 0b00000001,
    GUI_BUTTON_STATES_CLICK     = 0b00000010,
    GUI_BUTTON_STATES_TAB       = 0b00000100,
    GUI_BUTTON_STATES_BLOCK     = 0b00001000,
    GUI_BUTTON_STATES_HIDE      = 0b00010000
};

struct GUI_Button{
    Uchar            states;
    SDL_Rect         box;
    SDL_Texture     *texture;
    void  (*func)(void *ptr);
};
typedef struct GUI_Button GUI_Button;

#endif