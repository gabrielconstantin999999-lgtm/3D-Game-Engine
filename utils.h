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

vec3 TransPoint(vec3 p, mat4 m) {
    vec3 r;
    r.x = p.x * m.m[0] + p.y * m.m[4] + p.z * m.m[8]  + m.m[12];
    r.y = p.x * m.m[1] + p.y * m.m[5] + p.z * m.m[9]  + m.m[13];
    r.z = p.x * m.m[2] + p.y * m.m[6] + p.z * m.m[10] + m.m[14];
    return r;
}

vec2 ProjectPoint(vec3 point){
    vec2 projected;
    if (point.z < 0.1f){
        return (vec2){NAN,NAN};
    }
    projected.x = ((point.x/point.z) * WIDTH/2 + WIDTH/2);
    projected.y = ((point.y/point.z) * HEIGHT/2 + HEIGHT/2);
    return projected;
}

double DotVec(vec3 v1, vec3 v2){
    double result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
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

void DrawCrosshair(SDL_Renderer *ren){
    SDL_RenderLine(ren, WIDTH/2-10, HEIGHT/2,WIDTH/2+10, HEIGHT/2);
    SDL_RenderLine(ren, WIDTH/2,HEIGHT/2-10,WIDTH/2,HEIGHT/2+10);
}

void RenderCube(vec3 vertices[12][3],mat4 camView, SDL_Renderer *ren, float *color){
    vec3 screen[12][3];
        for (int i = 0; i < 12; i++){
            for (int j = 0; j < 3; j++){
                screen[i][j] = TransPoint(vertices[i][j], camView);
            }
            DrawTriangle(screen[i], ren, color);

        }
}

void PosToVert(vec3 cube[12][3], vec3 pos){
    double x = pos.x;
    double y = pos.y;
    double z = pos.z;

    // FRONT (+Z)
    cube[0][0] = (vec3){x,   y,   z+1};
    cube[0][1] = (vec3){x+1, y,   z+1};
    cube[0][2] = (vec3){x+1, y+1, z+1};

    cube[1][0] = (vec3){x,   y,   z+1};
    cube[1][1] = (vec3){x+1, y+1, z+1};
    cube[1][2] = (vec3){x,   y+1, z+1};

    // BACK (-Z)
    cube[2][0] = (vec3){x+1, y,   z};
    cube[2][1] = (vec3){x,   y,   z};
    cube[2][2] = (vec3){x,   y+1, z};

    cube[3][0] = (vec3){x+1, y,   z};
    cube[3][1] = (vec3){x,   y+1, z};
    cube[3][2] = (vec3){x+1, y+1, z};

    // LEFT (-X)
    cube[4][0] = (vec3){x, y,   z};
    cube[4][1] = (vec3){x, y,   z+1};
    cube[4][2] = (vec3){x, y+1, z+1};

    cube[5][0] = (vec3){x, y,   z};
    cube[5][1] = (vec3){x, y+1, z+1};
    cube[5][2] = (vec3){x, y+1, z};

    // RIGHT (+X)
    cube[6][0] = (vec3){x+1, y,   z+1};
    cube[6][1] = (vec3){x+1, y,   z};
    cube[6][2] = (vec3){x+1, y+1, z};

    cube[7][0] = (vec3){x+1, y,   z+1};
    cube[7][1] = (vec3){x+1, y+1, z};
    cube[7][2] = (vec3){x+1, y+1, z+1};

    // TOP (+Y)
    cube[8][0] = (vec3){x,   y+1, z+1};
    cube[8][1] = (vec3){x+1, y+1, z+1};
    cube[8][2] = (vec3){x+1, y+1, z};

    cube[9][0] = (vec3){x,   y+1, z+1};
    cube[9][1] = (vec3){x+1, y+1, z};
    cube[9][2] = (vec3){x,   y+1, z};

    // BOTTOM (-Y)
    cube[10][0] = (vec3){x,   y, z};
    cube[10][1] = (vec3){x+1, y, z};
    cube[10][2] = (vec3){x+1, y, z+1};

    cube[11][0] = (vec3){x,   y, z};
    cube[11][1] = (vec3){x+1, y, z+1};
    cube[11][2] = (vec3){x,   y, z+1};
}