#include <SDL3/SDL.h>
#include <stdio.h>
#include<math.h>
#include "camera.h"
#include "math_utils.h"
#include "renderer.h"
#include <time.h>
#include <stdlib.h>


int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow("3D Game Engine", WIDTH, HEIGHT, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, NULL);
    SDL_Event e;
    srand(time(NULL));
    Camera cam;
    vec3 up = {0.0f, 1.0f, 0.0f};
    vec3 direction = {0.0f, 0.0f, 1.0f};
    CamInit(&cam);
    int running = 1;
    float color[3] = {0.0f, 0.0f, 1.0f};
    SDL_SetWindowRelativeMouseMode(win, true);    
    float dx, dy;
    int randx[50];
    int randy[50];
    int randz[50];
    for (int i = 0; i < 50; i++){
        randx[i] = rand() % 50;
    }
    for (int i = 0; i < 50; i++){
        randy[i] = rand() % 50;
    }
    for (int i = 0; i < 50; i++){
        randz[i] = rand() % 50;
    }
                                                                                                                                                                                                       
    while (running) {
        while (SDL_PollEvent(&e))
            if (e.type == SDL_EVENT_QUIT) running = 0;

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        int num;
        const bool *key_states = SDL_GetKeyboardState(&num);
        SDL_GetRelativeMouseState(&dx, &dy);
        if (key_states[SDL_SCANCODE_ESCAPE])SDL_SetWindowRelativeMouseMode(win, false);
        CamUpdate(&cam, dx, dy, key_states);
        for (int i = 0; i < 50; i++){
            for (int j = 0; j < 50; j++){
                vec3 cube[12][3];
                vec3 pos = {randx[i],randy[i],randz[j]};
                PosToVert(cube,pos);
                RenderCube(cube, cam.view, ren, color);
            }
        }
        
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}