#ifndef _GUI_LAYER_H_
#define _GUI_LAYER_H_

#include "types.h"
#include "element.h"

enum GUI_LAYER_STATES{
    GUI_LAYER_STATES_DEFAULT    = 0b00000000,
    GUI_LAYER_STATES_HIDE       = 0b00000001
};

struct GUI_Layer{
    Sint id;
    Sint count;
    Uchar states;
    GUI_Element *elements;
};
typedef struct GUI_Layer GUI_Layer;

extern GUI_Layer *GUI_CreateLayer(int states, GUI_Element *els, int size);

extern int GUI_PushElementTo(GUI_Element *el, GUI_Layer *layer);

extern int GUI_RemoveElementTo(int lid, GUI_Layer *layer);

#endif