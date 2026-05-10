#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#define PI 3.14159265358979323846
#include <math.h>
typedef struct {
        double x, y;
    }vec2;

typedef struct {
        double x, y, z;
    }vec3;

typedef struct{
    float m[16];
    }mat4;

vec3 SubVectors(vec3 v1, vec3 v2);

vec3 AddVectors(vec3 v1, vec3 v2);

vec3 NormVec(vec3 v);

vec3 CrossVec(vec3 v1, vec3 v2);

mat4 MulMat(mat4 a, mat4 b);

double DotVec(vec3 v1, vec3 v2);
#endif