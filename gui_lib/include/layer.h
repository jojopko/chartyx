#ifndef _GUI_LAYER_H_
#define _GUI_LAYER_H_

#include "types.h"
#include "element.h"

enum GUI_LAYER_STATES{
    GUI_LAYER_STATES_DEFAULT    = 0b00000000,
    GUI_LAYER_STATES_HIDE       = 0b00000001,
    GUI_LAYER_STATES_LIMIT
};

struct GUI_Layer{
    Sint id;
    Uchar states;
    Sint count;
    GUI_Element *elements;
};
typedef struct GUI_Layer GUI_Layer;

extern GUI_Layer *GUI_CreateLayer(int states);

extern int GUI_PushElement(GUI_Element *el, GUI_Layer *layer);

extern GUI_Element *GUI_GetElement(int lid, GUI_Layer *layer);

extern int GUI_PresentLayer(GUI_Layer *layer);

extern int GUI_RemoveElement(int lid, GUI_Layer *layer);

#endif