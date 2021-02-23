#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../include/layer.h"
#include "../include/element.h"
#include "../include/types.h"

static Sint layer_count = 0;

// size = 0 --> all element from `els`;
GUI_Layer *GUI_CreateLayer(int states, GUI_Element *els, int size){
    GUI_Layer *layer;
    GUI_Element *elements;

    layer = (GUI_Layer *) calloc(1, sizeof(*layer));
    if(!layer){
        free(layer);
        return NULL;
    }

    layer->id = layer_count;
    if(states > GUI_LAYER_STATES_LIMIT || states < 0){
        free(layer);
        return NULL;
    }
    layer->states = states;

    if(!els){
        layer->count = 0;
        layer->elements = NULL;
    }

#if 0
    else{
        elements = (GUI_Element *) calloc(size, sizeof(*els));
        if(!elements){
            free(layer);
            return NULL;
        }

        int i = 0;
        while(i < size || (els+i)){
            (els+i)->lid = i;
            *(elements+i) = *(els+i);
            i++;
        }

        layer->count = i;
        layer->elements = (GUI_Element*) elements;
    }
#endif

    layer_count++;
    return layer;
}

int GUI_PushElementTo(GUI_Element *el, GUI_Layer *layer){
    /* FIXME: possible stack overflow!
     *      # layer->elements; and _els;     
     */
    if(!el){
        return -1;
    }

    if(!layer){
        return -1;
    }

    GUI_Element *_els;
    if(!layer->count){
        _els = (GUI_Element *) calloc(1, sizeof(*el));
    }
    else{
        _els = (GUI_Element *) calloc(layer->count, sizeof(*el));
    }

    int i = 0;
    while(i < layer->count){
        *(_els+i) = *(layer->elements+i);
        (_els+i)->lid = i;
        i++;
    }
    *(_els+i) = *el;
    (_els+i)->lid = i;

    // if(!layer->elements){
    //     free(layer->elements);
    // }

    layer->elements = _els;
    layer->count = i+1;

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

int GUI_PresentLayer(GUI_Layer *layer){
    if(!layer){
        return -1;
    }
    if(!layer->count){
        return -1;
    }

    int i = 0;
    while(i < layer->count){
        if((layer->elements+i)->type){
            if(GUI_PresentElement( (layer->elements+i) )){
                return -1;
            }
        }
        i++;
    }

    return 0;
}