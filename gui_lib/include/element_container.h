#ifndef _GUI_ELEMENT_CONTAINER_H_
#define _GUI_ELEMENT_CONTAINER_H_

#include <SDL2/SDL.h>
#include "types.h"

enum GUI_CONTAINER_STATES{
    GUI_CONTAINER_STATES_DEFAULT = 0b00000000,
    GUI_CONTAINER_STATES_HIDE    = 0b00000001,
    GUI_CONTAINER_STATES_LIMIT
};

struct GUI_Container{
    Uchar states;
    SDL_Rect box;
    SDL_Texture *texture;
};
typedef struct GUI_Container GUI_Container;

#endif