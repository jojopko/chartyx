#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "../include/element.h"
#include "../include/gui.h"

#define GUI_CreateIcon      GUI_CreateContainer
#define GUI_CreateImage     GUI_CreateContainer

GUI_Element *GUI_CreateContainer(int states, SDL_Rect box, SDL_Texture *texture){
    GUI_Element *element;
    element = (GUI_Element*) calloc(1, sizeof(*element));

    element->type = GUI_ELEMENT_TYPE_CONTAINER;

    GUI_Container cont;
    cont = element->element.container;
    
    if(states > 0b11111111 || states < 0){
        free(element);
        return NULL;
    }
    cont.states = states;
    cont.box = box;

    if(!texture){
        free(element);
        return NULL;
    }
    cont.texture = texture;

    element->element.container = cont;

    return element;
}

GUI_Element *GUI_CreateButton(int states, SDL_Rect box, SDL_Texture *texture, void *func){
    GUI_Element *element;
    element = (GUI_Element*) calloc(1, sizeof(*element));
    
    element->type = GUI_ELEMENT_TYPE_BUTTON;

    GUI_Button button;
    button = element->element.button;

    if(states > 0b11111111 || states < 0){
        free(element);
        return NULL;
    }
    button.states = states;

    if(!texture){
        free(element);
        return NULL;
    }
    button.texture = texture;
    button.box = box;
    button.func = func;

    element->element.button = button;

    return element;
}

GUI_Element *GUI_CreateLabel(int states, Uint16 *text, TTF_Font *font,
                             SDL_Color fg, SDL_Rect box){
    GUI_Element *element;
    element = (GUI_Element*) calloc(1, sizeof(*element));

    element->type = GUI_ELEMENT_TYPE_LABEL;

    GUI_Label label;
    label = element->element.label;

    label.box = box;

    TTF_SizeUNICODE(font, text, &label.box.w, &label.box.h);

    label.fg  = fg;

    if(!text){
        label.text = 0;
    }
    else{
        label.text = text;
    }

    if(states > 0b11111111 || states < 0){
        free(element);
        return NULL;
    }
    label.states = states;

    if(!font){
        free(element);
        return NULL;
    }
    label.font = font;

    SDL_Surface *lsurf;
    lsurf = TTF_RenderUNICODE_Solid(font, text, fg);

    if(!lsurf){
        free(element);
        free(lsurf);
        return NULL;
    }
    label.texture = SDL_CreateTextureFromSurface(gui_render, lsurf);

    element->element.label = label;

    return element;
}

int GUI_HasState(GUI_Element *e, int state){
    int states = 0;
    if(e->type == GUI_ELEMENT_TYPE_CONTAINER){
        if(state >= GUI_CONTAINER_STATES_LIMIT){
            return 0;
        }
        states = e->element.container.states;
    }
    else if(e->type == GUI_ELEMENT_TYPE_BUTTON){
        if(state >= GUI_BUTTON_STATES_LIMIT){
            return 0;
        }
        states = e->element.button.states;
    }
    else if(e->type == GUI_ELEMENT_TYPE_LABEL){
        if(state >= GUI_LABEL_STATES_LIMIT){
            return 0;
        }
        states = e->element.label.states;
    }
    else{
        return 0;
    }

    /* FIXME: AND method is better */
    /* Defining state using XOR . Example: 
    states = 0b00010001 (17); 
    state =  0b00001000 (8);
    
    states > (states ^ state)  # 17 > 25   - false.
    */

    if(states > (states ^ state)){
        return 1;
    }
    else{
        return 0;
    }
}

int GUI_IsElementBox(GUI_Element *e, int Xpos, int Ypos){
    int w0, w1;
    int h0, h1;
    int is_element_box = 0;
    if(e->type == GUI_ELEMENT_TYPE_CONTAINER){
        w0 = e->element.container.box.x;
        w1 = e->element.container.box.w + w0;
        h0 = e->element.container.box.y;
        h1 = e->element.container.box.h + h0;
    }
    else if(e->type == GUI_ELEMENT_TYPE_BUTTON){
        w0 = e->element.button.box.x;
        w1 = e->element.button.box.w + w0;
        h0 = e->element.button.box.y;
        h1 = e->element.button.box.h + h0;
    }
    else if(e->type == GUI_ELEMENT_TYPE_LABEL){
        w0 = e->element.label.box.x;
        w1 = e->element.label.box.w + w0;
        h0 = e->element.label.box.y;
        h1 = e->element.label.box.h + h0;
    }
    else{
        return is_element_box;
    }

    if(Xpos <= w1 && Xpos >= w0){
        if(Ypos <= h1 && Ypos >= h0){
            is_element_box = 1;
        }
    }
    else{
        is_element_box = 0;
    }
    return is_element_box;
}

int GUI_UpdateElementTexture(GUI_Element *e, SDL_Surface *surf){
    if(e->type == GUI_ELEMENT_TYPE_LABEL){
        SDL_Surface *lsurf;
        SDL_Texture *texture;

        TTF_Font *font = e->element.label.font;
        Uint16 *text = e->element.label.text;
        SDL_Color fg = e->element.label.fg;
        lsurf = TTF_RenderUNICODE_Solid(font, text, fg);

        if(!lsurf){
            free(lsurf);
            return -1;
        }

        texture = SDL_CreateTextureFromSurface(gui_render, lsurf);
        if(!texture){
            SDL_DestroyTexture(texture);
            return -1;
        }
        else{
            // if(e->element.label.texture){
            //     free(e->element.label.texture);
            // }
            e->element.label.texture = texture;
        }
    }
    else if(e->type == GUI_ELEMENT_TYPE_CONTAINER){
        SDL_Texture *texture;
        texture = SDL_CreateTextureFromSurface(gui_render, surf);
        if(!texture){
            SDL_DestroyTexture(texture);
            return -1;
        }
        else{
            // if(e->element.container.texture){
            //     free(e->element.container.texture);
            // }
            e->element.container.texture = texture;
        }
    }
    else if(e->type == GUI_ELEMENT_TYPE_BUTTON){
        /* Someday it needs to be improved */
        SDL_Texture *texture;
        texture = SDL_CreateTextureFromSurface(gui_render, surf);
        if(!texture){
            SDL_DestroyTexture(texture);
            return -1;
        }
        else{
            // if(e->element.button.texture){
            //     free(e->element.button.texture);
            // }
            e->element.button.texture = texture;
        }
    }

    return 0;
}

int GUI_PresentElement(GUI_Element *e){
    /* FIXME: !Add states support! */
    SDL_Texture *texture;
    SDL_Rect dst;
    if(e->type == GUI_ELEMENT_TYPE_CONTAINER){
        dst = e->element.container.box;
        texture = e->element.container.texture;
    }
    else if(e->type == GUI_ELEMENT_TYPE_BUTTON){
        dst = e->element.button.box;
        texture = e->element.button.texture;
    }
    else if(e->type == GUI_ELEMENT_TYPE_LABEL){
        dst = e->element.label.box;
        texture = e->element.label.texture;
    }
    else{
        return -1;
    }

    if(SDL_RenderCopy(gui_render, texture, NULL, &dst)){
        SDL_DestroyTexture(texture);
        return -1;
    }

    SDL_DestroyTexture(texture);
    return 0;
}