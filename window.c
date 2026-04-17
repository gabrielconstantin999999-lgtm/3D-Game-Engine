#include <SDL3/SDL.h>
#include <stdio.h>
#include<math.h>
#include"utils.h"






void draw_polygon(vec2* points, int count, SDL_Renderer* renderer);

void bind_cube(vec2* points,SDL_Renderer* renderer);
void rotate_shape(vec3 *points, double angle, char axis, int count);


int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow("3D Game Engine", WIDTH, HEIGHT, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, NULL);
    SDL_Event e;
    
    
    
    int running = 1;
                                                                                                                                                                                                                           
    while (running) {
        while (SDL_PollEvent(&e))
            if (e.type == SDL_EVENT_QUIT) running = 0;

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        int num;
        const bool *key_states = SDL_GetKeyboardState(&num);

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        
        int lenVert = 3;
        SDL_Vertex vert[lenVert];
        vert[0].position.x = 400;
        vert[0].position.y = 50;

        vert[0].color.r = 1.0;
        vert[0].color.g = 0.0;
        vert[0].color.b = 0.0;
        vert[0].color.a = 1.0;

        vert[1].position.x = 50;
        vert[1].position.y = 550;

        vert[1].color.r = 1.0;
        vert[1].color.g = 0.0;
        vert[1].color.b = 0.0;
        vert[1].color.a = 1.0;

        vert[2].position.x = 750;
        vert[2].position.y = 550;

        vert[2].color.r = 1.0;
        vert[2].color.g = 0.0;
        vert[2].color.b = 0.0;
        vert[2].color.a = 1.0;
        SDL_RenderGeometry(ren, NULL, vert, lenVert, NULL, 0);
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}









void draw_polygon(vec2* points, int count, SDL_Renderer* renderer){
    if (count < 2){
        return;
    }
    for (int i = 0; i < count; i += 1){
        vec2 a = points[i];
        vec2 b = points[(i + 1) % count];
        SDL_RenderLine(renderer, a.x,a.y,b.x,b.y);
    }
}




void bind_cube(vec2* points,SDL_Renderer* renderer){
    int sides[4][4] = {
        {0,1,2,3},{4,5,6,7},{1,2,6,5},{0,3,7,4}
    };
    for (int i = 0; i < 4; i++){
        vec2 face[4] = {points[sides[i][0]], points[sides[i][1]],points[sides[i][2]],points[sides[i][3]]};
        draw_polygon(face, 4, renderer);
    }
}

void rotate_shape(vec3 *points, double angle, char axis, int count){
    angle *= (PI/180);
        for (int i = 0; i < count; i += 1){
            double x = points[i].x;
            double y = points[i].y;
            double z = points[i].z;
        switch(axis){
            case 'x':
                points[i].x = x * 1 + y * 0 + z * 0;
                points[i].y = x * 0 + y * cos(angle) - z * sin(angle);
                points[i].z = x * 0 + y * sin(angle) + z * cos(angle);
                
                break;
            case 'y':
                points[i].x = x * cos(angle) + y * 0 + z * sin(angle);
                points[i].y = x * 0 + y * 1 + z * 0;
                points[i].z = x * sin(angle) * -1 + y * 0 + z * cos(angle);
                    
                break;
            case 'z':
                points[i].x = x * cos(angle) - y * sin(angle) + z * 0;
                points[i].y = x * sin(angle) + y * cos(angle) + z * 0;
                points[i].z = x * 0 + y * 0 + z * 1;
                        
                break;
            }
        };
    }












