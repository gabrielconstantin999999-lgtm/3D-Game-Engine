#include<math.h>
#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265358979323846
#include <SDL3/SDL.h>

typedef struct {
        double x, y;
    }vec2;

typedef struct {
        double x, y, z;
    }vec3;

typedef struct{
    float m[16];
    }mat4;

typedef struct{
    vec3 position;
    vec3 direction;
    vec3 up;
    vec3 right;
    mat4 view;
    double pitch;
    double yaw;
}Camera;

vec3 SubVectors(vec3 v1, vec3 v2){
    vec3 result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    return result;
}

vec3 AddVectors(vec3 v1, vec3 v2){
    vec3 result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    return result;
}

vec3 NormVec(vec3 v){
    double magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    vec3 result = {v.x/magnitude, v.y/magnitude, v.z/magnitude};
    return result;
}

vec3 CrossVec(vec3 v1, vec3 v2){
    vec3 result = {v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x};
    return result;
}

mat4 MulMat(mat4 a, mat4 b)
{
    mat4 result;

    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++)
        {
            result.m[row*4+col] =
                a.m[row*4+0] * b.m[0*4+col] +
                a.m[row*4+1] * b.m[1*4+col] +
                a.m[row*4+2] * b.m[2*4+col] +
                a.m[row*4+3] * b.m[3*4+col];
        }
    }
    return result;
}

vec3 TransPoint(vec3 p, mat4 m)
{
    vec3 r;
    r.x = m.m[0]*p.x + m.m[1]*p.y + m.m[2]*p.z + m.m[3];
    r.y = m.m[4]*p.x + m.m[5]*p.y + m.m[6]*p.z + m.m[7];
    r.z = m.m[8]*p.x + m.m[9]*p.y + m.m[10]*p.z + m.m[11];
    return r;
}

vec2 ProjectPoint(vec3 point){
    vec2 projected;
    projected.x = ((point.x/point.z) * WIDTH/2 + WIDTH/2);
    projected.y = ((point.y/point.z) * HEIGHT/2 + HEIGHT/2);
    return projected;
}

int DotVec(vec3 v1, vec3 v2){
    int result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return result;
}


void DrawTriangle(vec3 points3[3], SDL_Renderer *ren, float color[3]){
    vec2 points2[3];
    SDL_Vertex points[3];
    for (int i = 0; i < 3; i++){
        points2[i] = ProjectPoint(points3[i]);
        points[i] = (SDL_Vertex){{points2[i].x, points2[i].y},{color[0], color[1], color[2], 1.0f}};
    }
    SDL_RenderGeometry(ren, NULL, points, 3, NULL, 0);
}