#include <SDL3/SDL.h>

#define WIDTH  800
#define HEIGHT 600



void draw_line(double x1, double y1, double x2, double y2, SDL_Renderer *renderer);

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow("engine", WIDTH, HEIGHT, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, NULL);
    SDL_Event e;

    typedef struct {
        double x, y;
    }vec2;

    typedef struct {
        double x, y, z;
    }vec3;

    SDL_FPoint points[5] = {
        {400.0f, 300.0f},
        {401.0f, 300.0f},
        {399.0f, 300.0f},
        {400.0f, 301.0f},
        {400.0f, 299.0f},
    };

    vec2 p1 = {200.0f, 200.0f};
    vec2 p2 = {500.0f, 500.0f};

    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e))
            if (e.type == SDL_EVENT_QUIT) running = 0;
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);


        SDL_RenderPoints(ren, points, 5);
        //SDL_RenderLine(ren, p1.x,p1.x,p2.x,p2.y);
        draw_line(p1.x,p1.x,p2.x,p2.y, ren);


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