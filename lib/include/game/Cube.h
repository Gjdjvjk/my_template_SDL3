#ifndef CUBE_H
#define CUBE_H


#include "SDL3/SDL_render.h"

struct point3d {
    float x, y, z;
};

struct point2d {
    float x, y;
};

class Cube {
public:
    Cube();
    ~Cube();
    void init();
    void render(SDL_Renderer* renderer);
    void update(float dt);

private:
    point3d rotate(point3d p, float ang);
    point2d translate(point2d p);
    point2d project(point3d p);
    void draw_point(point3d p, SDL_Renderer* renderer);
    
private:
    point3d m_model[8];
    float m_angle;
};

#endif