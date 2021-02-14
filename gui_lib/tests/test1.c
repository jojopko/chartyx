#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "../include/gui.h"

void f(GUI_Element *e);
void hello(void *date);

int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    GUI_Element *el1, *el2, *el3;
    SDL_Texture *tex1   = (void*)1,
                *tex2   = (void*)1, 
                *tex3   = (void*)1;
    SDL_Rect     b1     = {0,0,10,10},
                 b2     = {0,0,10,10},
                 b3     = {0,0,10,10};

    SDL_Window *win = SDL_CreateWindow("", 0, 0, 512, 512, 0);
    gui_render = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gui_render, 255, 255, 255, 255);
    SDL_RenderClear(gui_render);
    SDL_RenderPresent(gui_render);

    el1 = GUI_CreateContainer(0b00000001, b1, tex1);
    f(el1);

    int r = 0;
    fprintf(stdout, "[i] (%d)\n", GUI_HasState(el1, 0b10000000));
    fprintf(stdout, "[i] (%d)\n", GUI_HasState(el1, 0b00000001));
    fprintf(stdout, "[i] (%d)\n", GUI_HasState(el1, 0b00001000));

    el2 = GUI_CreateButton(0, b2, tex2, &hello);
    f(el2);

    Uint16 text[] = {'h','e','l','l',0x41E,' ',0x41C,0x438,'p','!',0};
    TTF_Font *font = TTF_OpenFont("/home/jojopko/.local/share/fonts/19888.ttf\0", 16);
    if(!font){
        fprintf(stdout, "[!] font empty! %s\n", TTF_GetError());
    }

    SDL_Color fg = {0,0,0};

    el3 = GUI_CreateLabel(0, (Uint16*)text, font, fg, b3);
    f(el3);

    SDL_RenderCopy(gui_render, el3->element.label.texture, NULL, &el3->element.label.box);
    SDL_RenderPresent(gui_render);

    SDL_Delay(5000);
    return 0;
}

void f(GUI_Element *e){
    if(e->type == GUI_ELEMENT_TYPE_CONTAINER){
        fprintf(stdout, "[i] e: type=container{%d}, layer_id=%d, element=%p\n", 
            e->type, e->lid, &e->element);

        fprintf(stdout, "[i] e: element: states=%d, box={%d,%d,%d,%d}, texture=%p\n",
            e->element.container.states, e->element.container.box.x, e->element.container.box.y,
            e->element.container.box.w, e->element.container.box.h, e->element.container.texture);
    }
    if(e->type == GUI_ELEMENT_TYPE_BUTTON){
        fprintf(stdout, "[i] e: type=button{%d}, lid=%d, element=%p\n",
            e->type, e->lid, &e->element.button);

        fprintf(stdout, "[i] e: element: states=%d, box={%d,%d,%d,%d}, texture=%p, func=%p\n",
            e->element.button.states, e->element.button.box.x, e->element.button.box.y,
            e->element.button.box.w, e->element.button.box.h, e->element.button.texture,
            e->element.button.func);

        e->element.button.func(NULL);
    }
    if(e->type == GUI_ELEMENT_TYPE_LABEL){
        fprintf(stdout, "[i] e: type=label{%d}, lid=%d, element=%p\n",
            e->type, e->lid, &e->element);

        fprintf(stdout, "[i] e: element: states=%d, p_text=%p, font=%p, fg={%d,%d,%d,%d},"
                " box={%d,%d,%d,%d}, texture=%p\n",
                e->element.label.states, e->element.label.text, e->element.label.font,
                e->element.label.fg.r, e->element.label.fg.g, e->element.label.fg.b, e->element.label.fg.a,
                e->element.label.box.x, e->element.label.box.y, e->element.label.box.w, e->element.label.box.h,
                e->element.label.texture);
    }
}

void hello(void *date){
    fprintf(stdout, "[~] 'hello'\n");
}