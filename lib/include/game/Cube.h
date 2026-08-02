#ifndef CUBE_H
#define CUBE_H


#include "SDL3/SDL_render.h"
#include <cstddef>
#include <vector>

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
    void set_speed( float speed);
    float get_speed() const;
    void render(SDL_Renderer* renderer);
    void update(float dt);

private:
    point3d rotate(point3d p, point3d center, float ang);
    point2d translate(point2d p);
    point2d project(point3d p);
    void draw_point(point3d p, SDL_Renderer* renderer);
    void draw_line(point3d p1, point3d p2, SDL_Renderer* renderer);
    point3d centeroid() const;
    
private:
    point3d m_model[8];
    std::vector<std::vector<size_t>> m_wir_frame;
    float m_angle;
    float m_speed;
};

#endif