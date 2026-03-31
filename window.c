#include <SDL3/SDL.h>

#define WIDTH  800
#define HEIGHT 600


typedef struct {
        double x, y;
    }vec2;

typedef struct {
        double x, y, z;
    }vec3;

void draw_line(double x1, double y1, double x2, double y2, SDL_Renderer *renderer);
void draw_polygon(vec2* points, int count, SDL_Renderer* renderer);

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


    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e))
            if (e.type == SDL_EVENT_QUIT) running = 0;
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);


        draw_polygon(points, 4, ren);
        

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


