#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../include/layer.h"
#include "../include/element.h"
#include "../include/types.h"

static Sint layer_count = 0;

GUI_Layer *GUI_CreateLayer(int states){
    GUI_Layer *layer;
    layer = (GUI_Layer *) calloc(1, sizeof(*layer));

    if(!layer){
        return NULL;
    }

    if(states < 0 || states > GUI_LAYER_STATES_LIMIT){
        return NULL;
    }

    layer->states = states;
    layer->elements = NULL;
    layer->count = 0;
    layer->id = layer_count;
    layer_count++;

    return layer;
}

int GUI_PushElement(GUI_Element *el, GUI_Layer *layer){
    if(!layer){
        return 1;
    }

    if(!el){
        return 2;
    }

    if(!layer->elements){
        layer->elements = el;
        layer->elements->lid = 0;
        layer->count++;
    }
    else{
        GUI_Element *_element = layer->elements;
        GUI_Element *__element;
        int lid = 0;
        while(lid < layer->count){
            if(!_element->next){
                _element->next = el;
                __element = _element;

                _element = __element->next;
                _element->lid = lid+1;
            }
            else{
                __element = _element;
                _element = __element->next;
            }
            lid++;
        }
        layer->count++;
    }

    return 0;
}


#if 0

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

#endif