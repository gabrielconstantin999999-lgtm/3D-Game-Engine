#include <SDL3/SDL.h>
#include <stdio.h>
#include<math.h>

#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265358979323846

typedef struct {
        double x, y;
    }vec2;

typedef struct {
        double x, y, z;
    }vec3;

void draw_line(double x1, double y1, double x2, double y2, SDL_Renderer *renderer);
void draw_polygon(vec2* points, int count, SDL_Renderer* renderer);
vec2 project(vec3 point, SDL_Renderer* renderer);
void bind_cube(vec2* points,SDL_Renderer* renderer);
void rotate_shape(vec3 *points, double angle, char axis, int count);

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow("3D Game Engine", WIDTH, HEIGHT, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, NULL);
    SDL_Event e;
    vec2 points[] = {
        {200.0f, 200.0f},
        {200.0f, 500.0f},
        {400.0f, 500.0f},
        {400.0f, 200.0f}
    };


    vec3 cube[8] = {
    // front face (z = 2)
    {-1,  1, 2},
    { 1,  1, 2},
    { 1, -1, 2},
    {-1, -1, 2},
    // back face (z = 4)
    {-1,  1, 4},
    { 1,  1, 4},
    { 1, -1, 4},
    {-1, -1, 4},
    };
    vec2 projected[8];
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e))
            if (e.type == SDL_EVENT_QUIT) running = 0;
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        rotate_shape(cube, 0.5, 'x', 8);
        for (int i = 0; i < 8; i++){
            projected[i] = project(cube[i], ren);
            SDL_RenderPoint(ren, projected[i].x, projected[i].y);
        }
        //draw_polygon(points, 4, ren);
        bind_cube(projected,ren);

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}







void draw_line(double x1, double y1, double x2, double y2, SDL_Renderer *renderer){
    for (double t = 0; t <= 1; t += 0.001f){
        double x = x1 + t * (x2 - x1);
        double y = y1 + t * (y2 - y1);
        SDL_RenderPoint(renderer, x, y);
    }
}

void draw_polygon(vec2* points, int count, SDL_Renderer* renderer){
    if (count < 2){
        return;
    }
    for (int i = 0; i < count; i += 1){
        vec2 a = points[i];
        vec2 b = points[(i + 1) % count];
        draw_line(a.x,a.y,b.x,b.y,renderer);
    }
}


vec2 project(vec3 point, SDL_Renderer* renderer){
    vec2 projected;
    projected.x = ((point.x/point.z) * WIDTH/2 + WIDTH/2);
    projected.y = ((point.y/point.z) * HEIGHT/2 + HEIGHT/2);
    return projected;
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

