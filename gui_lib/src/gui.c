#include "../include/gui.h"
#include <SDL2/SDL_image.h>

SDL_Renderer *gui_render = NULL;

int GUI_SetGUIRender(SDL_Renderer *render){
    if(!render){
        return 1;
    }

    if(gui_render){
        return 2;
    }

    gui_render = render;

    return 0;
}

SDL_Surface *GUI_LoadImage(const char *file){
    SDL_Surface *surface;
    surface = (SDL_Surface *) calloc(1, sizeof(*surface));

    if(!surface){
        return NULL;
    }

    if(!file){
        return NULL;
    }

    if(*file == '/'){
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        surface = IMG_Load(file);
        
        IMG_Quit();

        return surface;
    }

    char abpath[256];
    char *exdir;

    exdir = SDL_GetBasePath();
    if(!exdir){
        return NULL;
    }

    int pos = 0;
    int size_exdir = 0;
    while(exdir[size_exdir++]){;}
    for(;exdir[pos]; pos++){
        abpath[pos] = exdir[pos];
    }

    int size_file = 0;
    while(file[size_file++]){;}
    for(;file[pos-size_exdir+1]; pos++){
        abpath[pos] = file[pos-size_exdir+1];
    }
    abpath[pos] = 0;

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    surface = IMG_Load(abpath);

    IMG_Quit();
    SDL_free(exdir);
    return surface;
}
