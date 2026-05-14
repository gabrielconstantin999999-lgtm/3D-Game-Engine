#ifndef RENDERER_H
#define RENDERER_H
#define WIDTH 800
#define HEIGHT 600
#include "math_utils.h"
#include <SDL3/SDL.h>
vec3 TransPoint(vec3 p, mat4 m);

vec2 ProjectPoint(vec3 point);


void DrawTriangle(vec3 points3[3], SDL_Renderer *ren, float color[3]);

void DrawCrosshair(SDL_Renderer *ren);

void RenderCube(vec3 vertices[12][3],mat4 camView, SDL_Renderer *ren, float *color);

void PosToVert(vec3 cube[12][3], vec3 pos);
#endif