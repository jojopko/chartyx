#ifndef _GUI_ELEMENT_H_
#define _GUI_ELEMENT_H_

#include "types.h"
#include "element_container.h"
#include "element_button.h"
#include "element_label.h"

enum GUI_ELEMENT_TYPE{
    GUI_EMPTY_TYPE              = 0,
    GUI_ELEMENT_TYPE_ICON       = 1,
    GUI_ELEMENT_TYPE_IMAGE      = 1,
    GUI_ELEMENT_TYPE_CONTAINER  = 1,
    GUI_ELEMENT_TYPE_LABEL      = 2,
    GUI_ELEMENT_TYPE_BUTTON     = 3
};

union GUI_Union_Element{
    GUI_Container   container;
    GUI_Button      button;
    GUI_Label       label;
};
typedef union GUI_Union_Element GUI__Element;

struct GUI_Element{
    Uchar           type;
    GUI__Element    element;
    Sint            lid;
};
typedef struct GUI_Element GUI_Element;

extern GUI_Element *GUI_CreateContainer(int states, SDL_Rect box,
                                        SDL_Texture *texture);

extern GUI_Element *GUI_CreateButton(int states, SDL_Rect box,
                                     SDL_Texture *texture, void *func);

extern GUI_Element *GUI_CreateLabel(int states, Uint16 *text, TTF_Font *font,
                                     SDL_Color fg, SDL_Rect box);

#endif