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
    Camera cam;
    vec3 up = {0.0f, 1.0f, 0.0f};
    vec3 direction = {0.0f, 0.0f, 1.0f};
    cam.position = (vec3){0.0f, 0.0f, -5.0f};
    float angle = 0.0f;
    int running = 1;
    vec3 target = {0.0f, 0.0f, 0.0f};                                                                                                                                                                                                                      
    while (running) {
        while (SDL_PollEvent(&e))
            if (e.type == SDL_EVENT_QUIT) running = 0;

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        int num;
        const bool *key_states = SDL_GetKeyboardState(&num);
        cam.direction = NormVec(SubVectors(target, cam.position));
        cam.right = CrossVec(up, cam.direction);
        cam.up = CrossVec(cam.direction, cam.right);
        cam.view = (mat4){cam.right.x, cam.right.y, cam.right.z, 0, cam.up.x, cam.up.y, cam.up.z,0, cam.direction.x, cam.direction.y, cam.direction.z,0, -(DotVec(cam.right, cam.position)), -(DotVec(cam.up, cam.position)), -(DotVec(cam.direction, cam.position)), 1};
        angle += 0.1;
        cam.position.x = sin(angle) * 10;
        cam.position.z = cos(angle) * 10;
        vec3 screen[3];
        vec3 points[3] = {{-1.0f, 1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}};
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        for (int i = 0; i < 3; i++){
            screen[i] = TransPoint(points[i], cam.view);
            printf("%d", screen[i]);
        }
        printf("x: %d, z: %d", cam.position.x, cam.position.z);
        float color[3] = {1.0f, 1.0f, 1.0f};
        DrawTriangle(screen, ren, color);
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












