#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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
        return NULL;
    }
    label.texture = SDL_CreateTextureFromSurface(gui_render, lsurf);

    element->element.label = label;

    return element;
}