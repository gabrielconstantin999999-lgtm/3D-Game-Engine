#ifndef CAMERA_H
#define CAMERA_H
#include <stdbool.h>
#include "math_utils.h"

typedef struct{
    vec3 position;
    vec3 direction;
    vec3 up;
    vec3 right;
    mat4 view;
    double pitch;
    double yaw;
}Camera;

void CamInit(Camera *cam);
void CamUpdate(Camera *cam, float dx, float dy, const bool *key_states);
#endif