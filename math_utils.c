#include "math_utils.h"
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
double DotVec(vec3 v1, vec3 v2){
    double result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return result;
}