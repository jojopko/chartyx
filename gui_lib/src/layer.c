#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../include/layer.h"
#include "../include/element.h"
#include "../include/types.h"

static Sint layer_count = 0;

GUI_Layer *GUI_CreateLayer(int states, GUI_Element *els, int size){
    GUI_Layer *layer;
    GUI_Element *elements;
    layer = (GUI_Layer *) calloc(1, sizeof(*layer));
    if(!layer){
        free(layer);
        return NULL;
    }

    layer->id = layer_count;
    layer->states = states;

    if(!els){
        layer->count = 0;
        layer->elements = NULL;
    }
    else{
        elements = (GUI_Element *) calloc(size, sizeof(*els));
        if(!elements){
            free(elements);
            return NULL;
        }

        int i = 0;
        while(i < size){
            (els+i)->lid = i;
            *(elements+i) = *(els+i);
            i++;
        }

        layer->count = size;
        layer->elements = (GUI_Element*) elements;
    }

    layer_count++;
    return layer;
}

int GUI_PushElementTo(GUI_Element *el, GUI_Layer *layer){
    GUI_Element *_els;
    _els = (GUI_Element *) calloc(layer->count+1, sizeof(*el));
    if(!_els){
        free(_els);
        return -1;
    }

    if(!layer){
        free(_els);
        return -1;
    }

    if(!el){
        free(_els);
        return -1;
    }

    if(!layer->count){
        layer->elements = _els;
    }
    else{
        int i = 0;
        while(i < layer->count){
            *(_els+i) = *(layer->elements+i);
            i++;
        }
        el->lid = layer_count;
        *(_els+i) = *el;
    }

    free(layer->elements);
    layer->elements = _els;

    layer_count++;
    return 0;
}

int GUI_RemoveElementTo(int lid, GUI_Layer *layer){
    if(lid < 0){
        return -1;
    }

    if(!layer){
        return -1;
    }

    (layer->elements+lid)->type = GUI_EMPTY_TYPE;


    return 0;
}