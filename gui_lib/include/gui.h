#ifndef _GUI_H_
#define _GUI_H_

#include "types.h"
#include "element.h"
#include "layer.h"
#include <SDL2/SDL.h>

extern SDL_Renderer *gui_render;

extern int GUI_SetGUIRender(SDL_Renderer *render);

extern SDL_Surface *GUI_LoadImage(const char *file);

#endif