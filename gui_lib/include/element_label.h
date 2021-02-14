#ifndef _GUI_ELEMENT_LABEL_H_
#define _GUI_ELEMENT_LABEL_H_

#include "types.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

enum GUI_LABEL_STATES{
    GUI_LABEL_STATES_DEFAULT = 0b00000000,
    GUI_LABEL_STATES_HIDE    = 0b00000001,
    GUI_LABEL_STATES_HOVER   = 0b00000010
};

struct GUI_Label{
    Uchar            states;
    Uint16          *text;
    TTF_Font        *font;
    SDL_Color        fg;
    SDL_Rect         box;
    SDL_Texture     *texture;
};
typedef struct GUI_Label GUI_Label;

#endif