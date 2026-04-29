#include <SDL3/SDL.h>
#include <stdio.h>
#include<math.h>
#include"utils.h"








int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow("3D Game Engine", WIDTH, HEIGHT, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, NULL);
    SDL_Event e;
    Camera cam;
    vec3 up = {0.0f, 1.0f, 0.0f};
    vec3 direction = {0.0f, 0.0f, 1.0f};
    cam.position = (vec3){0.0f, 0.0f, -5.0f};
    cam.pitch = 0.0f;
    cam.yaw = 0.0f;
    float angle = 0.0f;
    int running = 1;
    float color[3] = {1.0f, 0.0f, 0.0f};
    SDL_SetWindowRelativeMouseMode(win, true);    
    float dx, dy;                                                                                                                                                                                                       
    while (running) {
        while (SDL_PollEvent(&e))
            if (e.type == SDL_EVENT_QUIT) running = 0;

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        int num;
        const bool *key_states = SDL_GetKeyboardState(&num);
        SDL_GetRelativeMouseState(&dx, &dy);
        cam.yaw += dx * PI/180;
        cam.pitch += dy * PI/180;
        double speed = 0.1;

        if (key_states[SDL_SCANCODE_W])
            cam.position = AddVectors(cam.position, (vec3){
                cam.direction.x * speed,
                cam.direction.y * speed,
                cam.direction.z * speed
            });

        if (key_states[SDL_SCANCODE_S])
            cam.position = SubVectors(cam.position, (vec3){
                cam.direction.x * speed,
                cam.direction.y * speed,
                cam.direction.z * speed
            });

        if (key_states[SDL_SCANCODE_D])
            cam.position = AddVectors(cam.position, (vec3){
                cam.right.x * speed,
                cam.right.y * speed,
                cam.right.z * speed
            });

        if (key_states[SDL_SCANCODE_A])
            cam.position = SubVectors(cam.position, (vec3){
                cam.right.x * speed,
                cam.right.y * speed,
                cam.right.z * speed
            });
        if (key_states[SDL_SCANCODE_ESCAPE])SDL_SetWindowRelativeMouseMode(win, false);
        if (cam.pitch > 89.0f * PI / 180.0f) cam.pitch = 89.0f * PI / 180.0f;
        if (cam.pitch < -89.0f * PI / 180.0f) cam.pitch = -89.0f * PI / 180.0f;
        cam.direction.x = cos(cam.pitch) * sin(cam.yaw);
        cam.direction.y = sin(cam.pitch);
        cam.direction.z = cos(cam.pitch) * cos(cam.yaw);
        cam.right = NormVec(CrossVec(up, cam.direction)); 
        cam.up = NormVec(CrossVec(cam.direction, cam.right));
        cam.view = (mat4){
            cam.right.x, cam.up.x, cam.direction.x, 0,
            cam.right.y, cam.up.y, cam.direction.y, 0,
            cam.right.z, cam.up.z, cam.direction.z, 0,
            -(DotVec(cam.right, cam.position)), -(DotVec(cam.up, cam.position)), -(DotVec(cam.direction, cam.position)), 1
        };
        //angle += 0.01;
        //cam.position.x = sin(angle) * 5;
        //cam.position.z = cos(angle) * 5;
        vec3 screen[3];
        vec3 screen2[3];
        vec3 points[3] = {{-1.0f, 1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}};
        vec3 points2[3] = {{-1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}};
        vec3 vertices[12][3] = {

            // FRONT (+Z)
            {{-1,-1, 1}, { 1,-1, 1}, { 1, 1, 1}},
            {{-1,-1, 1}, { 1, 1, 1}, {-1, 1, 1}},

            // BACK (-Z)
            {{ 1,-1,-1}, {-1,-1,-1}, {-1, 1,-1}},
            {{ 1,-1,-1}, {-1, 1,-1}, { 1, 1,-1}},

            // LEFT (-X)
            {{-1,-1,-1}, {-1,-1, 1}, {-1, 1, 1}},
            {{-1,-1,-1}, {-1, 1, 1}, {-1, 1,-1}},

            // RIGHT (+X)
            {{ 1,-1, 1}, { 1,-1,-1}, { 1, 1,-1}},
            {{ 1,-1, 1}, { 1, 1,-1}, { 1, 1, 1}},

            // TOP (+Y)
            {{-1, 1, 1}, { 1, 1, 1}, { 1, 1,-1}},
            {{-1, 1, 1}, { 1, 1,-1}, {-1, 1,-1}},

            // BOTTOM (-Y)
            {{-1,-1,-1}, { 1,-1,-1}, { 1,-1, 1}},
            {{-1,-1,-1}, { 1,-1, 1}, {-1,-1, 1}}
        };
        vec3 screen3[12][3];
        for (int i = 0; i < 12; i++){
            for (int j = 0; j < 3; j++){
                screen3[i][j] = TransPoint(vertices[i][j], cam.view);
            }
            DrawTriangle(screen3[i], ren, color);

        }
        /*
        for (int i = 0; i < 3; i++){
                screen[i] = TransPoint(points[i], cam.view);
            }
        for (int i = 0; i < 3; i++){
                screen2[i] = TransPoint(points2[i], cam.view);
            }
        DrawTriangle(screen, ren, color);
        DrawTriangle(screen2, ren, color);
*/
        printf("%f, %f, %f\n", cam.position.x, cam.position.y, cam.position.z);
        printf("%f, %f, %f\n", cam.direction.x, cam.direction.y, cam.direction.z);
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

























