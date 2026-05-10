#define UP (vec3){0, 1, 0}
#include "camera.h"
#include "SDL3/SDL.h"
void CamInit(Camera *cam){
    vec3 direction = {0.0f, 0.0f, 1.0f};
    cam->position = (vec3){0.0f, 0.0f, -5.0f};
    cam->pitch = 0.0f;
    cam->yaw = 0.0f;
}

void CamUpdate(Camera *cam, float dx, float dy, const bool *key_states){
    double speed = 0.1;
    cam->yaw += dx * PI/180;
    cam->pitch += dy * PI/180;
    if (key_states[SDL_SCANCODE_W])
            cam->position = AddVectors(cam->position, (vec3){
                cam->direction.x * speed,
                cam->direction.y * speed,
                cam->direction.z * speed
            });

        if (key_states[SDL_SCANCODE_S])
            cam->position = SubVectors(cam->position, (vec3){
                cam->direction.x * speed,
                cam->direction.y * speed,
                cam->direction.z * speed
            });

        if (key_states[SDL_SCANCODE_D])
            cam->position = AddVectors(cam->position, (vec3){
                cam->right.x * speed,
                cam->right.y * speed,
                cam->right.z * speed
            });

        if (key_states[SDL_SCANCODE_A])
            cam->position = SubVectors(cam->position, (vec3){
                cam->right.x * speed,
                cam->right.y * speed,
                cam->right.z * speed
            });
        if (cam->pitch > 89.0f * PI / 180.0f) cam->pitch = 89.0f * PI / 180.0f;
        if (cam->pitch < -89.0f * PI / 180.0f) cam->pitch = -89.0f * PI / 180.0f;
        cam->direction.x = cos(cam->pitch) * sin(cam->yaw);
        cam->direction.y = sin(cam->pitch);
        cam->direction.z = cos(cam->pitch) * cos(cam->yaw);
        cam->right = NormVec(CrossVec(UP, cam->direction));
        cam->up = NormVec(CrossVec(cam->direction, cam->right));
        cam->view = (mat4){
            cam->right.x, cam->up.x, cam->direction.x, 0,
            cam->right.y, cam->up.y, cam->direction.y, 0,
            cam->right.z, cam->up.z, cam->direction.z, 0,
            -(DotVec(cam->right, cam->position)), -(DotVec(cam->up, cam->position)), -(DotVec(cam->direction, cam->position)), 1
        };


}