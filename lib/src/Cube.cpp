#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include <cmath>
#include <game/Cube.h>
#include <numbers>

Cube::Cube() : m_angle(0), m_speed(0.2f) { init(); }

Cube::~Cube() {}

void Cube::init() {
  m_model[0] = point3d(0.5, 0.5, 0.5);
  m_model[1] = point3d(0.5, -0.5, 0.5);
  m_model[2] = point3d(-0.5, -0.5, 0.5);
  m_model[3] = point3d(-0.5, 0.5, 0.5);

  m_model[4] = point3d(0.5, 0.5, -0.5);
  m_model[5] = point3d(0.5, -0.5, -0.5);
  m_model[6] = point3d(-0.5, -0.5, -0.5);
  m_model[7] = point3d(-0.5, 0.5, -0.5);
}

void Cube::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
  for (auto &p : m_model) {
    draw_point(p, renderer);
  }
}

void Cube::draw_point(point3d p, SDL_Renderer *renderer) {
  float s = 8;
  const point3d center = centeroid();

  point2d pos = translate(project(rotate(p, center, m_angle)));
  SDL_FRect rect{pos.x - s * 0.5f, pos.y - s * 0.5f, s, s};
  SDL_RenderFillRect(renderer, &rect);
}

point2d Cube::translate(point2d p) {
  return point2d((p.x + 1) * 0.5f * 1280, (1 - (p.y + 1) * 0.5f) * 720);
}

point2d Cube::project(point3d p) {
  const float offset = 2.0f;
  return point2d(p.x / (p.z + 2.0f), p.y / (p.z + 2.0f));
}

void Cube::update(float dt) { m_angle += m_speed * std::numbers::pi * dt; }

point3d Cube::rotate(point3d p, point3d center, float ang) {
  const float cos = std::cos(ang);
  const float sin = std::sin(ang);
  return point3d{(center.x - p.x) * cos - (center.z - p.z) * sin, p.y,
                 (center.x - p.x) * sin + (center.z - p.z) * cos};
}

point3d Cube::centeroid() const {
  point3d center{0.0f, 0.0f, 0.0f};
  for (point3d p : m_model) {
    center.x += p.x;
    center.y += p.y;
    center.z += p.z;
  }

  return {center.x / 8.0f, center.y / 8.0f, center.z / 8.0f};
}

void Cube::set_speed(float speed) { this->m_speed = speed; }

float Cube::get_speed() const { return this->m_speed; }