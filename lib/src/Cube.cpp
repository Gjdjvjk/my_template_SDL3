#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include <cmath>
#include <game/Cube.h>
#include <numbers>


Cube::Cube() : m_angle(0)
{
    init();
}

Cube::~Cube() { }

void Cube::init() 
{
    m_model[0] = point3d(0.5, 0.5, 0.5);
    m_model[1] = point3d(0.5, -0.5, 0.5);
    m_model[2] = point3d(-0.5, -0.5, 0.5);
    m_model[3] = point3d(-0.5, 0.5, 0.5);

    m_model[4] = point3d(0.25, 0.25, -0.5);
    m_model[5] = point3d(0.25, -0.25, -0.5);
    m_model[6] = point3d(-0.25, -0.25, -0.5);
    m_model[7] = point3d(-0.25, 0.25, -0.5);
}

void Cube::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    for (auto& p: m_model) {
        draw_point(p, renderer);
    }
}

void Cube::draw_point(point3d p, SDL_Renderer* renderer) {
    float s = 8;
    point2d dot = translate(
        project(p)
    );
    SDL_FRect rect {dot.x - s/2 , dot.y - s/2, s, s};
    SDL_RenderFillRect( renderer, &rect);
}

point2d Cube::translate(point2d p) {
    return point2d(
        (p.x + 1)/2 * 1280,
        (1-(p.y + 1)/2) * 720
    );
}

point2d Cube::project(point3d p) { return point2d(p.x / p.z , p.y / p.z); }

void Cube::update(float dt) {
    m_angle = std::numbers::pi * dt;
    for (point3d& p : m_model) {
        p = rotate(p, m_angle);
    }
}

// TODO: cube rotating at wrong point. should rotate at the cube's center
point3d Cube::rotate(point3d p, float ang) {
    const float ac = std::cos(ang);
    const float as = std::sin(ang);
    return point3d {
        p.x * ac - p.z * as,
        p.y,
        p.x * as + p.z * ac
    };
}